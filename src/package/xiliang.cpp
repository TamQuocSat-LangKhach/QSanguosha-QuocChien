/********************************************************************
    Copyright (c) 2013-2015 - Mogara

    This file is part of QSanguosha-Hegemony.

    This game is free software; you can redistribute it and/or
    modify it under the terms of the MOL General Public License as
    published by the Free Software Foundation; either version 3.0
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    See the LICENSE file for more details.

    Mogara
    *********************************************************************/

#include "xiliang.h"
#include "standard-basics.h"
#include "standard-tricks.h"
#include "standard-shu-generals.h"
#include "client.h"
#include "engine.h"
#include "structs.h"
#include "gamerule.h"
#include "settings.h"
#include "roomthread.h"
#include "json.h"

class Zhuhai : public TriggerSkill
{
public:
    Zhuhai() : TriggerSkill("zhuhai")
    {
        events << EventPhaseStart << ChoiceMade;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        //for notify skill
        if (triggerEvent == ChoiceMade && data.canConvert<CardUseStruct>()) {
            if (player->hasFlag("ZhuhaiSlash")) {
                player->setFlags("-ZhuhaiSlash");

                player->broadcastSkillInvoke(objectName());
                room->notifySkillInvoked(player, objectName());

                LogMessage log;
                log.type = "#InvokeSkill";
                log.from = player;
                log.arg = objectName();
                room->sendLog(log);

                if (player->ownSkill(objectName()) && !player->hasShownSkill(objectName()))
                    player->showGeneral(player->inHeadSkills(objectName()));

                if (player->hasShownSkill("huashen"))
                    room->dropHuashenCardbySkillName(player, objectName());
            }
        }
    }

    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == EventPhaseStart) {
            TriggerList skill_list;
            if (player == NULL || player->isDead() || player->getMark("Global_DamagePiont_Round") == 0
                    || player->getPhase() != Player::Finish) return skill_list;
            QList<ServerPlayer *> xushus = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *xushu, xushus) {
                if (xushu != player && xushu->canSlash(player, false))
                    skill_list.insert(xushu, QStringList(objectName()));
            }
            return skill_list;
        }
        return TriggerList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *owner) const
    {
        owner->setFlags("ZhuhaiSlash");
        if (!room->askForUseSlashTo(owner, player, "@zhuhai:" + player->objectName(), false))
             owner->setFlags("-ZhuhaiSlash");
        return false;
    }

    virtual bool effect(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
    {
        return false;
    }
};

class Pozhen : public TriggerSkill
{
public:
    Pozhen() : TriggerSkill("pozhen")
    {
        events << EventPhaseStart;
        frequency = Limited;
        limit_mark = "@pozhen";
    }

    virtual void record(TriggerEvent , Room *room, ServerPlayer *player, QVariant &) const
    {
        if (player->getPhase() == Player::NotActive) {
            room->setPlayerMark(player, "##pozhen", 0);
        }
    }

    virtual TriggerList triggerable(TriggerEvent , Room *room, ServerPlayer *player, QVariant &) const
    {
        TriggerList skill_list;
        if (player == NULL || player->isDead() || player->getPhase() != Player::Start) return skill_list;
        QList<ServerPlayer *> xushus = room->findPlayersBySkillName(objectName());
        foreach (ServerPlayer *xushu, xushus) {
            if (xushu != player && xushu->getMark(limit_mark) > 0)
                skill_list.insert(xushu, QStringList(objectName()));
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *xushu) const
    {
        if (xushu->askForSkillInvoke(this, QVariant::fromValue(player))) {
            room->broadcastSkillInvoke(objectName(), xushu);
            room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, xushu->objectName(), player->objectName());
            room->doSuperLightbox("xushu", objectName());
            room->setPlayerMark(xushu, limit_mark, 0);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *xushu) const
    {
        room->addPlayerMark(player, "##pozhen");
        room->setPlayerCardLimitation(player, "use,response,recast", ".|.|.|hand", true);
        QList<ServerPlayer *> all_players = room->getOtherPlayers(xushu), targets, alls = room->getAlivePlayers();
        bool can_discard = false;
        foreach (ServerPlayer *p, all_players) {

            bool inSiegeRelation = false;
            foreach (ServerPlayer *p2, alls) {
                if (player->inSiegeRelation(p, p2)) {
                    inSiegeRelation = true;
                    break;
                }
            }

            if (player->inFormationRalation(p) || inSiegeRelation) {
                targets << p;
                if (xushu->canDiscard(p, "he"))
                    can_discard = true;
            }
        }
        if (can_discard && room->askForChoice(xushu, "pozhen-discard", "yes+no", QVariant(), "@pozhen-discard::"+player->objectName()) == "yes") {
            room->sortByActionOrder(targets);
            foreach (ServerPlayer *p, targets) {
                if (xushu->canDiscard(p, "he")) {
                    room->throwCard(room->askForCardChosen(xushu, p, "he", objectName(), false, Card::MethodDiscard), p, xushu);
                }
            }
        }
        return false;
    }
};

class Jiancai : public TriggerSkill
{
public:
    Jiancai() : TriggerSkill("jiancai")
    {
        events << DamageInflicted << GeneralTransforming;
        relate_to_place = "deputy";
    }


    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (triggerEvent == DamageInflicted) {
            DamageStruct damage = data.value<DamageStruct>();
            if (damage.damage < player->getHp()) return skill_list;
        }

        QList<ServerPlayer *> xushus = room->findPlayersBySkillName(objectName());
        foreach (ServerPlayer *xushu, xushus) {
            if (xushu->isFriendWith(player))
                skill_list.insert(xushu, QStringList(objectName()));
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *xushu) const
    {
        if (triggerEvent == DamageInflicted) {
            xushu->tag["JiancaiDamagedata"] = data;
            bool invoke = xushu->askForSkillInvoke(this, "damage:"+player->objectName());
            xushu->tag.remove("JiancaiDamagedata");
            if (invoke) {
                room->broadcastSkillInvoke(objectName(), xushu);
                room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, xushu->objectName(), player->objectName());
                room->broadcastSkillInvoke(objectName(), player);
                return true;
            }
        } else {
            if (xushu->askForSkillInvoke(this, "transform:"+player->objectName())) {
                room->broadcastSkillInvoke(objectName(), xushu);
                room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, xushu->objectName(), player->objectName());
                room->broadcastSkillInvoke(objectName(), player);
                return true;
            }
        }
        return false;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *xushu) const
    {
        if (triggerEvent == DamageInflicted) {
            if (xushu->canTransform())
                room->transformDeputyGeneral(xushu);

            DamageStruct damage = data.value<DamageStruct>();
            damage.damage--;
            data = QVariant::fromValue(damage);
            if (damage.damage <= 0)
                return true;

        } else if (triggerEvent == GeneralTransforming) {
            data = data.toInt() + 2;
        }
        return false;
    }
};

class Jutian : public TriggerSkill
{
public:
    Jutian() : TriggerSkill("jutian")
    {
        events << Damage;
    }

    virtual QStringList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (TriggerSkill::triggerable(player)) {
            DamageStruct damage = data.value<DamageStruct>();
            if (damage.to && damage.to != player) {
                if (!player->hasFlag("jutian1Used")) {
                    return QStringList(objectName());
                }
                if (!player->hasFlag("jutian2Used")) {
                    foreach (ServerPlayer *p, room->getAlivePlayers()) {
                        if (p->isFriendWith(damage.to)) {
                            return QStringList(objectName());
                        }
                    }
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        DamageStruct damage = data.value<DamageStruct>();
        QList<ServerPlayer *> targets;
        foreach (ServerPlayer *p, room->getAlivePlayers()) {
            if ((!player->hasFlag("jutian1Used") && p->isFriendWith(player)) ||
                (!player->hasFlag("jutian2Used") && damage.to && p->isFriendWith(damage.to))) {
                targets << p;
            }
        }
        if (!targets.isEmpty()) {
            QString prompt = "@jutian";
            if (!player->hasFlag("jutian1Used")) {
                prompt += "-fillhandcard";
            }
            if (!player->hasFlag("jutian2Used") && damage.to) {
                prompt += "-discard::" + damage.to->objectName();
            }
            ServerPlayer *target = room->askForPlayerChosen(player, targets, objectName(), prompt, true, true);
            if (target) {
                player->tag["jutian_target"] = QVariant::fromValue(target);
                room->broadcastSkillInvoke(objectName(), player);
                return true;
            }
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        ServerPlayer *target = player->tag["jutian_target"].value<ServerPlayer *>();
        player->tag.remove("jutian_target");
        if (target && target->isAlive()) {
            DamageStruct damage = data.value<DamageStruct>();
            QStringList choices;
            if (!player->hasFlag("jutian1Used") && target->isFriendWith(player)) {
                choices << "fillhandcard";
            }
            if (!player->hasFlag("jutian2Used") && damage.to && target->isFriendWith(damage.to)) {
                choices << "discard";
            }
            QString choice = room->askForChoice(player, "jutian_choice", choices.join("+"), QVariant::fromValue(target), "@jutian-choice::" + target->objectName(), "fillhandcard+discard");
            if (choice == "fillhandcard") {
                room->setPlayerFlag(player, "jutian1Used");
                target->fillHandCards(target->getMaxHp(), objectName());
            } else if (choice == "discard") {
                room->setPlayerFlag(player, "jutian2Used");
                if (target->getHandcardNum() > target->getHp()) {
                    int x = qMin(target->getHandcardNum() - target->getHp(), 5);
                    room->askForDiscard(target, "jutian_discard", x, x, false, true);
                }
            }
        }
        return false;
    }
};

class Guojue : public TriggerSkill
{
public:
    Guojue() : TriggerSkill("guojue")
    {
        events << Dying;
    }

    virtual QStringList triggerable(TriggerEvent , Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        DyingStruct dying = data.value<DyingStruct>();
        ServerPlayer *target = dying.who;
        if (target != player && dying.damage && dying.damage->from == player) {
            if (player->canDiscard(target, "he"))
                return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        DyingStruct dying = data.value<DyingStruct>();
        ServerPlayer *target = dying.who;
        if (target && player->askForSkillInvoke(this, QVariant::fromValue(target))) {
            room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), target->objectName());
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent , Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        DyingStruct dying = data.value<DyingStruct>();
        ServerPlayer *target = dying.who;
        if (target && player->canDiscard(target, "he")) {
            int card_id = room->askForCardChosen(player, target, "he", objectName(), false, Card::MethodDiscard);
            room->throwCard(card_id, target, player);
        }
        return false;
    }
};

class GuojueDamage : public TriggerSkill
{
public:
    GuojueDamage() : TriggerSkill("#guojue-damage")
    {
        events << GeneralShowed;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent , Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (player->isAlive() && player->hasShownSkill("guojue")) {
            if (player->cheakSkillLocation("guojue", data.toStringList()) && player->getMark("guojueUsed") == 0)
                return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->sendCompulsoryTriggerLog(player, "guojue");
        room->broadcastSkillInvoke("guojue", player);
        room->addPlayerMark(player, "guojueUsed");
        return true;
    }

    virtual bool effect(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        ServerPlayer *target = room->askForPlayerChosen(player, room->getOtherPlayers(player), "guojue_damage", "@guojue-damage");
        room->damage(DamageStruct("guojue", player, target));
        return false;
    }
};

ShangshiCard::ShangshiCard()
{
    will_throw = false;
    handling_method = Card::MethodNone;
}

bool ShangshiCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *) const
{
    if (targets.isEmpty() && subcardsLength() > 0 && subcardsLength() == Self->getLostHp()) {
        return !Sanguosha->getCard(subcards.first())->isEquipped() && to_select != Self;
    }
    return false;
}

bool ShangshiCard::targetsFeasible(const QList<const Player *> &targets, const Player *Self) const
{
    if (targets.isEmpty()) {
        return (subcardsLength() == 1 && !Self->isJilei(Sanguosha->getCard(subcards.first())));
    } else if (subcardsLength() > 0 && subcardsLength() == Self->getLostHp()) {
        return !Sanguosha->getCard(subcards.first())->isEquipped();
    }
    return false;
}

void ShangshiCard::extraCost(Room *room, const CardUseStruct &card_use) const
{
    if (card_use.to.isEmpty()) {
        QString general;
        if (!card_use.card->getSkillPosition().isEmpty())
            general = card_use.card->getSkillPosition() == "left" ? card_use.from->getActualGeneral1Name() : card_use.from->getActualGeneral2Name();
        CardMoveReason reason(CardMoveReason::S_REASON_THROW, card_use.from->objectName(), QString(), card_use.card->getSkillName(), general);
        room->moveCardTo(this, card_use.from, NULL, Player::DiscardPile, reason, true);
    } else {
        ServerPlayer *target = card_use.to.first();
        CardMoveReason reason(CardMoveReason::S_REASON_GIVE, card_use.from->objectName(), target->objectName(), "shangshi", QString());
        room->obtainCard(target, this, reason, false);
    }
}

class ShangshiViewAsSkill : public ViewAsSkill
{
public:
    ShangshiViewAsSkill() : ViewAsSkill("shangshi")
    {
        response_pattern = "@@shangshi";
    }

    virtual bool viewFilter(const QList<const Card *> &selected, const Card *to_select) const
    {
        bool can_discard = false, can_give = false;

        if (selected.isEmpty() && !Self->isJilei(to_select)) {
            can_discard = true;
        }

        if (selected.length() < Self->getLostHp() && !to_select->isEquipped()) {
            can_give = true;
            foreach (const Card *c, selected) {
                if (c->isEquipped())
                    can_give = false;
            }
        }

        return (can_discard || can_give);
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        bool can_discard = false, can_give = false;

        if (cards.length() == 1 && !Self->isJilei(cards.first()))
            can_discard = true;

        if (!cards.isEmpty() && cards.length() == Self->getLostHp()) {
            can_give = true;
            foreach (const Card *c, cards) {
                if (c->isEquipped())
                    can_give = false;
            }
        }

        if (can_discard || can_give) {
            ShangshiCard *shangshiCard = new ShangshiCard;
            shangshiCard->addSubcards(cards);
            return shangshiCard;
        }
        return NULL;
    }
};

class Shangshi : public MasochismSkill
{
public:
    Shangshi() : MasochismSkill("shangshi")
    {
        view_as_skill = new ShangshiViewAsSkill;
    }

    virtual bool canPreshow() const
    {
        return true;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (TriggerSkill::triggerable(player) && !player->isNude())
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QString prompt = "@shangshi-card";
        int x = player->getLostHp();
        if (x > 0)
            prompt = prompt + ":::" + QString::number(x);
        else
            prompt += "-full";

        return room->askForUseCard(player, "@@shangshi", prompt, -1, Card::MethodNone);
    }

    virtual void onDamaged(ServerPlayer *target, const DamageStruct &) const
    {
        int x = target->getLostHp();
        if (x > 0)
            target->drawCards(x, objectName());
        return;
    }
};

ShefuCard::ShefuCard()
{
    will_throw = false;
    target_fixed = true;
    handling_method = Card::MethodNone;
}

void ShefuCard::extraCost(Room *, const CardUseStruct &card_use) const
{
    card_use.from->addToPile("ambush", subcards, false);
}

class ShefuViewAsSkill : public OneCardViewAsSkill
{
public:
    ShefuViewAsSkill() : OneCardViewAsSkill("shefu")
    {
        filter_pattern = ".|.|.|hand";
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return !player->hasUsed("ShefuCard");
    }

    virtual const Card *viewAs(const Card *originalcard) const
    {
        ShefuCard *first = new ShefuCard;
        first->addSubcard(originalcard->getId());
        first->setSkillName(objectName());
        first->setShowSkill(objectName());
        return first;
    }
};

class Shefu : public TriggerSkill
{
public:
    Shefu() : TriggerSkill("shefu")
    {
        events << CardUsed << CardResponded;
        view_as_skill = new ShefuViewAsSkill;
    }

    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if (triggerEvent == CardUsed) {
            CardUseStruct use = data.value<CardUseStruct>();
            if (player != NULL && use.card->getTypeId() != Card::TypeSkill && use.m_isHandcard) {
                QList<ServerPlayer *> owners = room->findPlayersBySkillName(objectName());
                TriggerList skill_list;
                foreach (ServerPlayer *owner, owners) {
                    if (owner == player) continue;
                    foreach (int id, owner->getPile("ambush")) {
                        if (Sanguosha->getCard(id)->sameCardNameWith(use.card)) {
                            skill_list.insert(owner, QStringList(objectName()));
                            break;
                        }
                    }
                }
                return skill_list;
            }
        } else if (triggerEvent == CardResponded) {
            CardResponseStruct response = data.value<CardResponseStruct>();
            if (response.m_isUse && player != NULL && response.m_card->getTypeId() != Card::TypeSkill && response.m_isHandcard) {
                QList<ServerPlayer *> owners = room->findPlayersBySkillName(objectName());
                TriggerList skill_list;
                foreach (ServerPlayer *owner, owners) {
                    if (owner == player) continue;
                    foreach (int id, owner->getPile("ambush")) {
                        if (Sanguosha->getCard(id)->sameCardNameWith(response.m_card)) {
                            skill_list.insert(owner, QStringList(objectName()));
                            break;
                        }
                    }
                }
                return skill_list;
            }
        }
        return TriggerList();
    }

    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
    {
        const Card *card = NULL;
        if (triggerEvent == CardUsed)
            card = data.value<CardUseStruct>().card;
        else if (triggerEvent == CardResponded)
            card = data.value<CardResponseStruct>().m_card;

        if (card == NULL) return false;

        QString pattern = "%" + card->objectName();
        if (card->isKindOf("Slash"))
            pattern = "Slash";
        else if (card->isKindOf("Nullification"))
            pattern = "Nullification";
        pattern += "|.|.|ambush";

        QString prompt = "@shefu-invoke:" + player->objectName() + "::" + card->objectName();

        ask_who->tag["ShefuUsedata"] = data;
        QList<int> ints = room->askForExchange(ask_who, objectName(), 1, 0, prompt, "ambush", pattern);
        ask_who->tag.remove("ShefuUsedata");
        if (!ints.isEmpty()) {
            LogMessage log;
            log.type = "#InvokeSkill";
            log.from = ask_who;
            log.arg = objectName();
            room->sendLog(log);
            room->notifySkillInvoked(ask_who, objectName());
            room->broadcastSkillInvoke(objectName(), 2, ask_who);
            room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, ask_who->objectName(), player->objectName());
            CardMoveReason reason(CardMoveReason::S_REASON_REMOVE_FROM_PILE, QString(), ask_who->objectName(), objectName(), QString());
            room->throwCard(Sanguosha->getCard(ints.first()), reason, NULL);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *, ServerPlayer *, QVariant &data, ServerPlayer *) const
    {
        if (triggerEvent == CardUsed) {
            CardUseStruct use = data.value<CardUseStruct>();
            use.to.clear();
            use.nullified_list << "_ALL_TARGETS";
            data = QVariant::fromValue(use);
        } else if (triggerEvent == CardResponded) {
            CardResponseStruct response = data.value<CardResponseStruct>();
            response.m_card->setTag("ResponseNegated", true);
        }
        return false;
    }

    virtual int getEffectIndex(const ServerPlayer *, const Card *card) const
    {
        return card->isKindOf("ShefuCard") ? 1 : -1;
    }
};

class ShefuCompulsory : public PhaseChangeSkill
{
public:
    ShefuCompulsory() : PhaseChangeSkill("#shefu-compulsory")
    {
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (player == NULL || player->isDead() || !player->hasShownSkill("shefu")) return QStringList();
        if (player->getPhase() == Player::Start && player->getPile("ambush").length() > 2) return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->sendCompulsoryTriggerLog(player, "shefu");
        //room->broadcastSkillInvoke("shefu", player);
        return true;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const
    {
        int x = player->getPile("ambush").length() - 2;
        if (x > 0) {
            Room *room = player->getRoom();
            QList<int> to_throw = room->askForExchange(player, "shefu_remove", x, x, "@shefu-remove:::"+QString::number(x), "ambush");
            CardMoveReason reason(CardMoveReason::S_REASON_REMOVE_FROM_PILE, QString(), player->objectName(), "shefu", QString());
            DummyCard dummy(to_throw);
            room->throwCard(&dummy, reason, NULL);
        }
        return false;
    }
};

class Benyu : public MasochismSkill
{
public:
    Benyu() : MasochismSkill("benyu")
    {

    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        DamageStruct damage = data.value<DamageStruct>();
        if (damage.from && damage.from->isAlive() && damage.from->getHandcardNum() != player->getHandcardNum())
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        DamageStruct damage = data.value<DamageStruct>();
        if (damage.from && damage.from->isAlive()) {
            if (damage.from->getHandcardNum() > player->getHandcardNum()) {
                if (player->askForSkillInvoke(this, QVariant::fromValue(damage.from))) {
                    room->broadcastSkillInvoke(objectName(), player);
                    room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), damage.from->objectName());
                    QStringList effect_list = player->tag["benyu_effect"].toStringList();
                    effect_list.append("select");
                    player->tag["benyu_effect"] = effect_list;
                    return true;
                }
            } if (damage.from->getHandcardNum() < player->getHandcardNum()) {
                int x = damage.from->getHandcardNum()+1;
                QString prompt = "@benyu-invoke::"+damage.from->objectName()+":"+QString::number(x);
                player->tag["BenyuDamagedata"] = data;
                bool invoke = room->askForDiscard(player, "benyu", 998, x, true, false, prompt, true);
                player->tag.remove("BenyuDamagedata");
                if (invoke) {
                    room->broadcastSkillInvoke(objectName(), player);
                    room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), damage.from->objectName());
                    QStringList effect_list = player->tag["benyu_effect"].toStringList();
                    effect_list.append("damage");
                    player->tag["benyu_effect"] = effect_list;
                    return true;
                }
            }
        }
        return false;
    }

    virtual void onDamaged(ServerPlayer *chengyu, const DamageStruct &damage) const
    {
        Room *room = chengyu->getRoom();
        QStringList effect_list = chengyu->tag["benyu_effect"].toStringList();
        QString effect_name = effect_list.takeLast();
        chengyu->tag["benyu_effect"] = effect_list;

        ServerPlayer *from = damage.from;
        if (from->isDead()) return;

        if (effect_name == "damage")
            room->damage(DamageStruct(objectName(), chengyu, from));
        else if (effect_name == "select" && chengyu->isAlive()) {
            QString choice = room->askForChoice(chengyu, objectName(), "draw+discard", QVariant::fromValue(from), "@benyu-choose::"+from->objectName());
            if (choice == "draw") {
                chengyu->fillHandCards(qMin(from->getHandcardNum(),5) , objectName());
            } else if (choice == "discard") {
                int x = qMin(from->getHandcardNum() - chengyu->getHandcardNum(), 5);
                room->askForDiscard(from, "benyu_discard", x, x);
            }
        }
    }
};

class Jingce : public TriggerSkill
{
public:
    Jingce() : TriggerSkill("jingce")
    {
        events << CardUsed << CardResponded << EventPhaseChanging << CardFinished;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if ((triggerEvent == CardUsed || triggerEvent == CardResponded) && player->getPhase() == Player::Play) {
            const Card *card = NULL;
            if (triggerEvent == CardUsed)
                card = data.value<CardUseStruct>().card;
            else if (triggerEvent == CardResponded) {
                CardResponseStruct response = data.value<CardResponseStruct>();
                if (response.m_isUse)
                    card = response.m_card;
            }
            if (card != NULL && card->getTypeId() != Card::TypeSkill) {
                room->addPlayerMark(player, "jingce_record");
                card->setTag("JingceRecord", QVariant::fromValue(player->getMark("jingce_record")));
            }
        } else if (triggerEvent == EventPhaseChanging) {
            PhaseChangeStruct change = data.value<PhaseChangeStruct>();
            if (change.to == Player::Play || change.from == Player::Play)
            room->setPlayerMark(player, "jingce_record", 0);
        }
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (triggerEvent == CardFinished && TriggerSkill::triggerable(player)
                && player->getPhase() == Player::Play && player->hasShownOneGeneral()) {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card->getTypeId() != Card::TypeSkill && !use.card->isKindOf("ThreatenEmperor")) {
                int x = use.card->tag["JingceRecord"].toInt();
                if (x == player->getHp()) {
                    bool can_invoke = false;
                    QList<ServerPlayer *> all_players = room->getAlivePlayers();
                    foreach (ServerPlayer *p, all_players) {
                        if (p->getHp() <= 0) return QStringList();
                        if (!player->isFriendWith(p) && p->hasShownOneGeneral())
                            can_invoke = true;
                    }
                    if (can_invoke) return QStringList(objectName());
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QList<ServerPlayer *> to_choose, all_players = room->getAlivePlayers();
        foreach (ServerPlayer *p, all_players) {
            if (!player->isFriendWith(p) && p->hasShownOneGeneral())
                to_choose << p;
        }
        if (to_choose.isEmpty()) return false;

        ServerPlayer *to = room->askForPlayerChosen(player, to_choose, objectName(), "jingce-invoke", true, true);
        if (to != NULL) {
            room->broadcastSkillInvoke(objectName(), player);
            QStringList target_list = player->tag["jingce_target"].toStringList();
            target_list.append(to->objectName());
            player->tag["jingce_target"] = target_list;
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QStringList target_list = player->tag["jingce_target"].toStringList();
        QString target_name = target_list.takeLast();
        player->tag["jingce_target"] = target_list;
        ServerPlayer *target = room->findPlayerbyobjectName(target_name);
        if (target && target->isAlive() && player->isAlive() && !player->askCommandto(objectName(), target))
            player->drawCards(2, objectName());
        return false;
    }
};

MumengCard::MumengCard()
{
    will_throw = false;
}

bool MumengCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->tag["mumeng"].toString());
    if (mutable_card) {
        mutable_card->addSubcards(subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetFilter(targets, to_select, Self) && !Self->isProhibited(to_select, mutable_card, targets);
}

bool MumengCard::targetFixed() const
{
    Card *mutable_card = Sanguosha->cloneCard(getUserString());
    if (mutable_card) {
        mutable_card->addSubcards(subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetFixed();
}

bool MumengCard::targetsFeasible(const QList<const Player *> &targets, const Player *Self) const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->tag["mumeng"].toString());
    if (mutable_card) {
        mutable_card->addSubcards(subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetsFeasible(targets, Self);
}

void MumengCard::onUse(Room *room, const CardUseStruct &card_use) const
{
    ServerPlayer *source = card_use.from;
    QString card_name = toString().split(":").last();

    Card *use_card = Sanguosha->cloneCard(card_name);
    use_card->setSkillName("mumeng");
    use_card->addSubcards(subcards);
    use_card->setCanRecast(false);
    use_card->setShowSkill("mumeng");

    if (use_card->isAvailable(source)) {
        room->useCard(CardUseStruct(use_card, source, card_use.to));
    }
}

class MumengViewAsSkill : public OneCardViewAsSkill
{
public:
    MumengViewAsSkill() : OneCardViewAsSkill("mumeng")
    {
        response_or_use = true;
    }

    virtual bool viewFilter(const Card *card) const
    {
        return (card->getSuit() == Card::Heart && !card->isEquipped());
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        QString c = Self->tag["mumeng"].toString();
        if (c != "") {
            MumengCard *card = new MumengCard;
            card->addSubcard(originalCard);
            card->setUserString(c);
            return card;
        } else
            return NULL;
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return player->usedTimes("ViewAsSkill_mumengCard") < 1;
    }

    QStringList getViewAsCardNames(const QList<const Card *> &selected) const
    {
        if (selected.length() != 1) return QStringList();
        QStringList card_names;
        card_names << "befriend_attacking" << "fight_together";
        return card_names;
    }

    bool isEnabledtoViewAsCard(const QString &button_name, const QList<const Card *> &selected) const
    {
        QStringList card_names;
        card_names << "befriend_attacking" << "fight_together";

        if (!card_names.contains(button_name))
            return false;

        return ViewAsSkill::isEnabledtoViewAsCard(button_name, selected);
    }
};

class Mumeng : public TriggerSkill
{
public:
    Mumeng() : TriggerSkill("mumeng")
    {
        view_as_skill = new MumengViewAsSkill;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer* &) const
    {
        return QStringList();
    }
};

class Naman : public TriggerSkill
{
public:
    Naman() : TriggerSkill("naman")
    {
        events << TargetChoosing;
    }

    virtual TriggerList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (player == NULL || player->isDead()) return skill_list;
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card->getTypeId() != Card::TypeSkill && use.card->isBlack() && room->getUseAliveTargets(use).length() > 1) {
            QList<ServerPlayer *> maliangs = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *maliang, maliangs) {
                if (maliang != player)
                    skill_list.insert(maliang, QStringList(objectName()));
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *owner) const
    {
        if (owner->askForSkillInvoke(this)) {
            room->broadcastSkillInvoke(objectName(), owner);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *owner) const
    {
        JudgeStruct judge;
        judge.pattern = ".|^spade";
        judge.good = true;
        judge.reason = objectName();
        judge.who = owner;
        room->judge(judge);

        if (judge.isGood()) {
            CardUseStruct use = data.value<CardUseStruct>();
            QList<ServerPlayer *> targets = room->getUseExtraTargets(use, false);
            targets << use.to;
            if (!targets.isEmpty()) {
                QString prompt = "@naman-target:"+player->objectName() + "::" + use.card->objectName();
                room->setTag("NamanUsedata", data);
                ServerPlayer *to = room->askForPlayerChosen(owner, targets, "naman_target", prompt);
                room->removeTag("NamanUsedata");
                room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, owner->objectName(), to->objectName());

                if (use.to.contains(to))
                    room->cancelTarget(use, to);
                else {
                    use.to.append(to);
                    if (use.card->isKindOf("Slash") && use.card->hasFlag("BladeEffect"))
                        room->setPlayerDisableShow(to, "hd", "Blade");
                    room->sortByActionOrder(use.to);
                }

                data = QVariant::fromValue(use);

            }


        }

        return false;
    }
};

class Dingke : public TriggerSkill
{
public:
    Dingke() : TriggerSkill("dingke")
    {
        events << CardsMoveOneTime;
    }

    virtual QStringList triggerable(TriggerEvent , Room *room, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (TriggerSkill::triggerable(player) && !player->hasFlag("DingkeUsed")) {

            ServerPlayer *current = room->getCurrent();
            if (current == NULL || current->isDead() || current->getPhase() == Player::NotActive)
                return QStringList();

            QVariantList move_datas = data.toList();
            foreach (QVariant move_data, move_datas) {
                CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                if (((move.reason.m_reason & CardMoveReason::S_MASK_BASIC_REASON) != CardMoveReason::S_REASON_USE) &&
                        ((move.reason.m_reason & CardMoveReason::S_MASK_BASIC_REASON) != CardMoveReason::S_REASON_RESPONSE) &&
                        move.reason.m_skillName != objectName()) {
                    if (move.from_places.contains(Player::PlaceHand) || move.from_places.contains(Player::PlaceEquip)) {
                        if (move.from && move.from->isAlive() && move.from->getPhase() == Player::NotActive && move.from->isFriendWith(player)) {
                            if ((!current->isKongcheng()) || (move.from != player && !player->isKongcheng()))
                                return QStringList(objectName());
                        }
                    }
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        QList<ServerPlayer *> targets;
        ServerPlayer *current = room->getCurrent();
        if (current == NULL || current->isDead() || current->getPhase() == Player::NotActive) return false;
        if (!current->isKongcheng())
            targets << current;

        if (!player->isKongcheng()) {
            QVariantList move_datas = data.toList();
            foreach (QVariant move_data, move_datas) {
                CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                if (((move.reason.m_reason & CardMoveReason::S_MASK_BASIC_REASON) != CardMoveReason::S_REASON_USE) &&
                        ((move.reason.m_reason & CardMoveReason::S_MASK_BASIC_REASON) != CardMoveReason::S_REASON_RESPONSE) &&
                        move.reason.m_skillName != objectName()) {
                    if (move.from_places.contains(Player::PlaceHand) || move.from_places.contains(Player::PlaceEquip)) {
                        if (move.from && player != move.from && move.from->getPhase() == Player::NotActive) {
                            ServerPlayer *move_from = (ServerPlayer *)move.from;
                            if (move_from && !targets.contains(move_from) && player->isFriendWith(move_from))
                                targets << move_from;
                        }
                    }
                }
            }
        }

        if (targets.isEmpty()) return false;

        ServerPlayer *to = room->askForPlayerChosen(player, targets, objectName(),
                "dingke-invoke::" + current->objectName(), true, true);
        if (to != NULL) {
            room->broadcastSkillInvoke(objectName(), player);
            player->setFlags("DingkeUsed");

            QStringList target_list = player->tag["dingke_target"].toStringList();
            target_list.append(to->objectName());
            player->tag["dingke_target"] = target_list;
            return true;
        }

        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QStringList target_list = player->tag["dingke_target"].toStringList();
        if (target_list.isEmpty()) return false;
        QString target_name = target_list.takeLast();
        player->tag["dingke_target"] = target_list;

        ServerPlayer *target = room->findPlayerbyobjectName(target_name);

        if (target && target->isAlive()) {
            if (target->getPhase() != Player::NotActive) {
                room->askForDiscard(target, "dingke_discard", 1, 1);
                if (player->isAlive() && player->getMark("@halfmaxhp") < player->getMaxHp())
                    room->addPlayerMark(player, "@halfmaxhp");
            } else if (!player->isKongcheng()) {
                target->setFlags("DingkeTarget");
                QList<int> result = room->askForExchange(player, "dingke_give", 1, 1, "@dingke-give::"+ target->objectName(), QString(), ".|.|.|hand");
                target->setFlags("-DingkeTarget");
                if (!result.isEmpty()) {
                    DummyCard dummy(result);
                    CardMoveReason reason(CardMoveReason::S_REASON_GIVE, player->objectName(), target->objectName(), objectName(), QString());
                    room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), target->objectName());
                    room->obtainCard(target, &dummy, reason, false);
                    if (player->isAlive() && player->getMark("@halfmaxhp") < player->getMaxHp())
                        room->addPlayerMark(player, "@halfmaxhp");
                }
            }
        }
        return false;
    }
};

class Jiyuan : public TriggerSkill
{
public:
    Jiyuan() : TriggerSkill("jiyuan")
    {
        events << CardsMoveOneTime << Dying;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (TriggerSkill::triggerable(player)) {
            if (triggerEvent == Dying) {
                DyingStruct dying = data.value<DyingStruct>();
                if (dying.who && dying.who->isAlive())
                    return QStringList(objectName() + "->" + dying.who->objectName());
            } else if (triggerEvent == CardsMoveOneTime) {
                QVariantList move_datas = data.toList();
                foreach (QVariant move_data, move_datas) {
                    CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                    if (move.reason.m_skillName == "dingke" && move.from == player && move.to) {
                        return QStringList(objectName() + "->" + move.to->objectName());
                    }
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *skill_target, QVariant &, ServerPlayer *player) const
    {
        if (player->askForSkillInvoke(this, QVariant::fromValue(skill_target))) {
            room->broadcastSkillInvoke(objectName(), player);
            room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), skill_target->objectName());
            return true;
        }

        return false;
    }

    virtual bool effect(TriggerEvent , Room *, ServerPlayer *skill_target, QVariant &, ServerPlayer *) const
    {
        skill_target->drawCards(1, objectName());
        return false;
    }
};

class Kangrui : public TriggerSkill
{
public:
    Kangrui() : TriggerSkill("kangrui")
    {
        events << EventPhaseChanging << ConfirmDamage << TargetChoosing;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *, QVariant &data) const
    {
        if (triggerEvent == EventPhaseChanging) {
            QList<ServerPlayer *> players = room->getAllPlayers(true);
            foreach (ServerPlayer *p, players) {
                room->setPlayerMark(p, "##kangrui", 0);
                p->setFlags("-kangruiUsed");
            }
        } else if (triggerEvent == ConfirmDamage) {
            DamageStruct damage = data.value<DamageStruct>();
            if (damage.card && damage.card->isKindOf("Duel") && damage.card->getSkillName() == objectName()) {
                damage.damage++;
                data = QVariant::fromValue(damage);
            }
        }
    }

    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (triggerEvent != TargetChoosing) return skill_list;
        if (player == NULL || player->isDead() || player->getPhase() != Player::Play) return skill_list;
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card && use.card->getTypeId() != Card::TypeSkill) {
            if (use.to.length() != 1 || use.to.contains(player)) return skill_list;
            QList<ServerPlayer *> zhangyis = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *zhangyi, zhangyis) {
                if (zhangyi->isFriendWith(player) && !zhangyi->hasFlag("kangruiUsed"))
                    skill_list.insert(zhangyi, QStringList(objectName()));
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *zhangyi) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.to.length() != 1) return false;
        ServerPlayer *target = use.to.first();
        QString prompt = "prompt:"+ player->objectName() + ":" + target->objectName() + ":" + use.card->objectName();
        zhangyi->tag["KangruiUsedata"] = data;
        bool invoke = zhangyi->askForSkillInvoke(this, prompt);
        zhangyi->tag.remove("KangruiUsedata");
        if (invoke) {
            room->broadcastSkillInvoke(objectName(), zhangyi);
            zhangyi->setFlags("kangruiUsed");
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.to.length() != 1) return false;
        ServerPlayer *target = use.to.first();
        room->cancelTarget(use, target); // Room::cancelTarget(use, player);
        data = QVariant::fromValue(use);

        QStringList choices;
        choices << "fillhandcards";
        Duel *duel = new Duel(Card::NoSuit, 0);
        duel->setSkillName(QString("_%1").arg(objectName()));

        if (!target->isCardLimited(duel, Card::MethodUse) && !target->isProhibited(player, duel)) {
            bool allsafe = true;
            foreach (ServerPlayer *p, room->getAlivePlayers()) {
                if (p->getHp() < 1) {
                    allsafe = false;
                    break;
                }
            }
            if (allsafe)
                choices << "useduel";
        }

        QString choice = room->askForChoice(player, objectName(), choices.join("+"), QVariant::fromValue(target),
                "@kangrui-choose::" + target->objectName(), "fillhandcards+useduel");
        if (choice == "fillhandcards") {
            player->fillHandCards(player->getHp(), objectName());
            room->addPlayerMark(player, "##kangrui");
        } else if (choice == "useduel") {
            room->useCard(CardUseStruct(duel, target, player));
        }
        return false;
    }

    virtual int getEffectIndex(const ServerPlayer *, const Card *card) const
    {
        return card->isKindOf("Duel") ? 0 : -1;
    }
};

class KangruiProhibit : public ProhibitSkill
{
public:
    KangruiProhibit() : ProhibitSkill("#kangrui-prohibit")
    {
    }

    virtual bool isProhibited(const Player *from, const Player *to, const Card *card, const QList<const Player *> &) const
    {
        if (from && from->getMark("##kangrui") > 0 && card->getTypeId() != Card::TypeSkill) {
            return (to && from != to);
        }
        return false;
    }
};

LifuCard::LifuCard()
{
}

bool LifuCard::targetFilter(const QList<const Player *> &targets, const Player *, const Player *) const
{
    return targets.isEmpty();
}

void LifuCard::onEffect(const CardEffectStruct &effect) const
{
    ServerPlayer *source = effect.from;
    ServerPlayer *target = effect.to;
    Room *room = source->getRoom();
    room->askForDiscard(target, "lifu_discard", 2, 2, false, true);

    if (source->isAlive() && target->isAlive()) {
        QList<int> ids = room->getNCards(1);
        const Card *card = Sanguosha->getCard(ids.first());
        room->fillAG(ids, source);
        room->askForSkillInvoke(source, "lifu_view", "prompt::"+target->objectName() + ":" + card->objectName(), false);
        room->clearAG(source);

        source->setFlags("Global_GongxinOperator");
        CardMoveReason reason(CardMoveReason::S_REASON_PREVIEWGIVE, source->objectName(), target->objectName(), "lifu", QString());
        room->moveCardTo(card, target, Player::PlaceHand, reason);
        source->setFlags("-Global_GongxinOperator");

    }
}

class Lifu : public ZeroCardViewAsSkill
{
public:
    Lifu() : ZeroCardViewAsSkill("lifu")
    {

    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return !player->hasUsed("LifuCard");
    }

    virtual const Card *viewAs() const
    {
        LifuCard *skillcard = new LifuCard;
        skillcard->setSkillName(objectName());
        skillcard->setShowSkill(objectName());
        return skillcard;
    }
};

class Yanzhong : public PhaseChangeSkill
{
public:
    Yanzhong() : PhaseChangeSkill("yanzhong")
    {

    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        if (player->getPhase() == Player::Finish) {
            Room *room = player->getRoom();
            foreach (ServerPlayer *p, room->getOtherPlayers(player)) {
                if (!p->isKongcheng()) {
                    return QStringList(objectName());
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QList<ServerPlayer *> targets, all_players = room->getOtherPlayers(player);
        foreach (ServerPlayer *p, all_players) {
            if (!p->isKongcheng())
                targets << p;
        }
        ServerPlayer *victim = room->askForPlayerChosen(player, targets, objectName(), "@yanzhong", true, true);
        if (victim != NULL) {
            room->broadcastSkillInvoke(objectName(), player);

            QStringList target_list = player->tag["yanzhong_target"].toStringList();
            target_list.append(victim->objectName());
            player->tag["yanzhong_target"] = target_list;

            return true;
        }
        return false;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const
    {
        Room *room = player->getRoom();

        Card::Suit suit = room->askForSuit(player, objectName());

        LogMessage log;
        log.type = "#ChooseSuit";
        log.from = player;
        log.arg = Card::Suit2String(suit);
        room->sendLog(log);

        QStringList target_list = player->tag["yanzhong_target"].toStringList();
        QString target_name = target_list.last();
        target_list.removeLast();
        player->tag["yanzhong_target"] = target_list;

        ServerPlayer *target = room->findPlayerbyobjectName(target_name);
        if (target != NULL && player->canDiscard(target, "h")) {
            int card_id = room->askForCardChosen(player, target, "h", objectName(), false, Card::MethodDiscard);
            Card::Suit suit2 = Sanguosha->getCard(card_id)->getSuit();
            room->throwCard(card_id, target, player);
            if (suit == suit2) {
                //Spade, Club, Heart, Diamond
                switch (suit) {
                case Card::Spade: {
                    room->loseHp(target);
                    break;
                }
                case Card::Club: {
                    if (player->isAlive() && target->isAlive() && !target->isNude() && player != target) {

                        QString prompt = QString("@yanzhong-give:%1").arg(player->objectName());
                        QList<int> ints = room->askForExchange(target, "yanzhong_give", 1, 1, prompt);

                        int card_id = -1;
                        if (ints.isEmpty()) {
                            card_id = target->getCards("he").first()->getEffectiveId();
                        } else
                            card_id = ints.first();

                        CardMoveReason reason(CardMoveReason::S_REASON_GIVE, target->objectName(), player->objectName(), objectName(), QString());
                        room->moveCardTo(Sanguosha->getCard(card_id), player, Player::PlaceHand, reason);


                    }
                    break;
                }
                case Card::Heart: {
                    room->recover(player, RecoverStruct());
                    break;
                }
                case Card::Diamond: {
                    player->drawCards(1, objectName());
                    if (player->isChained()) {
                        room->setPlayerProperty(player, "chained", false);
                    }
                    break;
                }
                default:
                    break;
                }

            } else
                room->askForDiscard(player, "yanzhong_discard", 1, 1, false, true);

        }
        return false;
    }
};

HuxunMoveCard::HuxunMoveCard()
{
    mute = true;
}

bool HuxunMoveCard::targetsFeasible(const QList<const Player *> &targets, const Player *) const
{
    return targets.length() == 2;
}

bool HuxunMoveCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *) const
{
    if (targets.isEmpty())
        return (!to_select->getJudgingArea().isEmpty() || !to_select->getEquips().isEmpty());
    else if (targets.length() == 1){
        for (int i = 0; i < S_EQUIP_AREA_LENGTH; i++) {
            if (targets.first()->getEquip(i) && to_select->canSetEquip(i))
                return true;
        }
        foreach(const Card *card, targets.first()->getJudgingArea()){
            if (!Sanguosha->isProhibited(NULL, to_select, card))
                return true;
        }

    }
    return false;
}

void HuxunMoveCard::onUse(Room *room, const CardUseStruct &card_use) const
{
    CardUseStruct use = card_use;
    ServerPlayer *caoren = use.from;
    if (use.to.length() != 2) return;

    ServerPlayer *from = use.to.first();
    ServerPlayer *to = use.to.last();

    QList<int> all, ids, disabled_ids;
    for (int i = 0; i < S_EQUIP_AREA_LENGTH; i++) {
        if (from->getEquip(i)){
            if (to->canSetEquip(i))
                ids << from->getEquip(i)->getEffectiveId();
            else
                disabled_ids << from->getEquip(i)->getEffectiveId();
            all << from->getEquip(i)->getEffectiveId();
        }
    }

    foreach(const Card *card, from->getJudgingArea()){
        if (!Sanguosha->isProhibited(NULL, to, card))
            ids << card->getEffectiveId();
        else
            disabled_ids << card->getEffectiveId();
        all << card->getEffectiveId();
    }

    room->fillAG(all, caoren, disabled_ids);
    from->setFlags("HuxunTarget");
    int card_id = room->askForAG(caoren, ids, true, "huxun");
    from->setFlags("-HuxunTarget");
    room->clearAG(caoren);

    if (card_id != -1)
        room->moveCardTo(Sanguosha->getCard(card_id), from, to, room->getCardPlace(card_id), CardMoveReason(CardMoveReason::S_REASON_TRANSFER, caoren->objectName(), "huxun", QString()));
}

class HuxunMove : public ZeroCardViewAsSkill
{
public:
    HuxunMove() : ZeroCardViewAsSkill("huxun_move")
    {
        response_pattern = "@@huxun_move";
    }

    virtual const Card *viewAs() const
    {
        return new HuxunMoveCard;
    }
};

class Huxun : public TriggerSkill
{
public:
    Huxun() : TriggerSkill("huxun")
    {
        events << EventPhaseChanging;
    }

    virtual TriggerList triggerable(TriggerEvent , Room *room, ServerPlayer *, QVariant &data) const
    {
        TriggerList skill_list;

        if (data.value<PhaseChangeStruct>().to == Player::NotActive) {
            foreach (ServerPlayer *p, room->getAllPlayers()) {
                if (p->getMark("GlobalDyingCausedCount") > 0 && TriggerSkill::triggerable(p)) {
                    skill_list.insert(p, QStringList(objectName()));
                }
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *player) const
    {
        if (player->askForSkillInvoke(this, data)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *player) const
    {
        bool maxmaxhp = true;
        foreach (ServerPlayer *p, room->getOtherPlayers(player)) {
            if (p->getMaxHp() >= player->getMaxHp())
                maxmaxhp = false;
        }
        QStringList choices;
        choices << "movecard";
        if (!maxmaxhp)
            choices << "gainmaxhp";

        QString choice = room->askForChoice(player, objectName(), choices.join("+"), QVariant(),
                                            QString(), "gainmaxhp+movecard");
        if (choice == "gainmaxhp") {
            LogMessage log;
            log.type = "#GainMaxHp";
            log.from = player;
            log.arg = QString::number(1);
            room->sendLog(log);
            room->setPlayerProperty(player, "maxhp", player->getMaxHp() + 1);
            RecoverStruct recover;
            recover.who = player;
            room->recover(player, recover);
        } else if (choice == "movecard") {
            room->askForUseCard(player, "@@huxun_move", "@huxun-move");
        }
        return false;
    }
};

class YuancongUseCard : public OneCardViewAsSkill
{
public:
    YuancongUseCard() : OneCardViewAsSkill("yuancong_usecard")
    {
        response_pattern = "@@yuancong_usecard";
        response_or_use = true;
    }

    virtual bool viewFilter(const Card *to_select) const
    {
        return to_select->isAvailable(Self) && !to_select->isEquipped();
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        return originalCard;
    }
};

class Yuancong : public TriggerSkill
{
public:
    Yuancong() : TriggerSkill("yuancong")
    {
        events << EventPhaseEnd;
    }

    virtual TriggerList triggerable(TriggerEvent , Room *room, ServerPlayer *player, QVariant &) const
    {
        TriggerList skill_list;
        if (player->getPhase() == Player::Play && player->getMark("Global_DamageTimes_Phase") == 0 && !player->isNude()) {
            QList<ServerPlayer *> owners = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *owner, owners)
                if (owner->hasShownSkill(objectName()) && player->isFriendWith(owner) && owner != player)
                    skill_list.insert(owner, QStringList(objectName()));
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *owner) const
    {
        QList<int> ints = room->askForExchange(player, "yuancong_give", 1, 0, "@yuancong:" + owner->objectName());

        if (ints.isEmpty()) return false;

        LogMessage log;
        log.type = "#InvokeOthersSkill";
        log.from = player;
        log.to << owner;
        log.arg = objectName();
        room->sendLog(log);
        room->broadcastSkillInvoke(objectName(), owner);
        room->notifySkillInvoked(owner, objectName());

        room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), owner->objectName());

        CardMoveReason reason(CardMoveReason::S_REASON_GIVE, player->objectName(), owner->objectName(), objectName(), QString());
        reason.m_playerId = owner->objectName();
        room->moveCardTo(Sanguosha->getCard(ints.first()), owner, Player::PlaceHand, reason);

        return true;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *chengpu) const
    {
        room->askForUseCard(chengpu, "@@yuancong_usecard", "@yuancong-usecard", -1, Card::MethodUse, false);
        return false;
    }
};

class Qinzhong : public TriggerSkill
{
public:
    Qinzhong() : TriggerSkill("qinzhong")
    {
        events  << EventPhaseEnd;
        relate_to_place = "deputy";
    }

    virtual QStringList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        if (player->getPhase() == Player::RoundStart) {
            QList<ServerPlayer *> allplayers = room->getOtherPlayers(player);
            foreach (ServerPlayer *p, allplayers) {
                if (p->isFriendWith(player) && p->getGeneral2())
                    return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QList<ServerPlayer *> to_choose, all_players = room->getOtherPlayers(player);
        foreach (ServerPlayer *p, all_players) {
            if (player->isFriendWith(p) && p->getGeneral2())
                to_choose << p;
        }
        if (to_choose.isEmpty()) return false;

        ServerPlayer *to = room->askForPlayerChosen(player, to_choose, objectName(), "qinzhong-invoke", true, true);
        if (to != NULL) {
            room->broadcastSkillInvoke(objectName(), player);

            QStringList target_list = player->tag["qinzhong_target"].toStringList();
            target_list.append(to->objectName());
            player->tag["qinzhong_target"] = target_list;
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QStringList target_list = player->tag["qinzhong_target"].toStringList();
        QString target_name = target_list.takeLast();
        player->tag["qinzhong_target"] = target_list;
        ServerPlayer *target = room->findPlayerbyobjectName(target_name);
        if (target == NULL) return false;

        QString name1 = player->getActualGeneral2Name(), name2 = target->getActualGeneral2Name();

        QStringList remove_marks1, remove_marks2;
        QList<const Skill *> skills1 = player->getActualGeneral2()->getVisibleSkillList();
        foreach (const Skill *skill, skills1) {
            if (skill->isAttachedLordSkill()) continue;
            if (skill->getFrequency() == Skill::Limited) {
                QString mark_name = skill->getLimitMark();
                if (!mark_name.isEmpty() && player->getMark(mark_name) == 0) {
                    remove_marks1 << mark_name;
                }
            }
            QList<const Skill *> related_skill = Sanguosha->getRelatedSkills(skill->objectName());
            foreach (const Skill *s, related_skill) {
                if (s->inherits("DetachEffectSkill")) {
                    const DetachEffectSkill *detach_skill = qobject_cast<const DetachEffectSkill *>(s);
                    QString pile_name = detach_skill->getPileName();
                    if (!player->getPile(pile_name).isEmpty()) {
                        target->addToPile(pile_name, player->getPile(pile_name), player->pileOpen(pile_name, player->objectName()));
                    }
                }

            }
        }

        QList<const Skill *> skills2 = target->getActualGeneral2()->getVisibleSkillList();
        foreach (const Skill *skill, skills2) {
            if (skill->isAttachedLordSkill()) continue;
            if (skill->getFrequency() == Skill::Limited) {
                QString mark_name = skill->getLimitMark();
                if (!mark_name.isEmpty() && target->getMark(mark_name) == 0) {
                    remove_marks2 << mark_name;
                }
            }
            QList<const Skill *> related_skill = Sanguosha->getRelatedSkills(skill->objectName());
            foreach (const Skill *s, related_skill) {
                if (s->inherits("DetachEffectSkill")) {
                    const DetachEffectSkill *detach_skill = qobject_cast<const DetachEffectSkill *>(s);
                    QString pile_name = detach_skill->getPileName();
                    if (!target->getPile(pile_name).isEmpty()) {
                        player->addToPile(pile_name, target->getPile(pile_name), target->pileOpen(pile_name, target->objectName()));
                    }
                }

            }
        }


        player->removeGeneral(false);
        target->removeGeneral(false);

        if (!name2.contains("sujiang")) {
            room->transformDeputyGeneral(player, name2);
            foreach (QString mark_name, remove_marks2) {
                room->setPlayerMark(player, mark_name, 0);
            }
        }

        if (!name1.contains("sujiang")) {
            room->transformDeputyGeneral(target, name1);
            foreach (QString mark_name, remove_marks1) {
                room->setPlayerMark(target, mark_name, 0);
            }
        }

        return false;
    }
};

ZhaofuCard::ZhaofuCard()
{
}

void ZhaofuCard::onEffect(const CardEffectStruct &effect) const
{
    QVariantList effect_list = effect.from->tag["zhaofuTag"].toList();
    effect_list << QVariant::fromValue(effect);
    effect.from->tag["zhaofuTag"] = effect_list;
}

ZhaofuVSCard::ZhaofuVSCard()
{
    will_throw = false;
}

bool ZhaofuVSCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->property("zhaofucard").toString(), Card::NoSuit, 0);
    if (mutable_card) {
        mutable_card->setSkillName("_zhaofu");
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }

    return mutable_card && mutable_card->targetFilter(targets, to_select, Self) && !Self->isProhibited(to_select, mutable_card, targets);
}

bool ZhaofuVSCard::targetFixed() const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->property("zhaofucard").toString(), Card::NoSuit, 0);
    if (mutable_card) {
        mutable_card->setSkillName("_zhaofu");
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetFixed();
}

bool ZhaofuVSCard::targetsFeasible(const QList<const Player *> &targets, const Player *Self) const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->property("zhaofucard").toString(), Card::NoSuit, 0);
    if (mutable_card) {
        mutable_card->setSkillName("_zhaofu");
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetsFeasible(targets, Self);
}

void ZhaofuVSCard::onUse(Room *, const CardUseStruct &card_use) const
{
    ServerPlayer *source = card_use.from;
    QVariantList use_list = source->tag["zhaofuUseTag"].toList();
    use_list << QVariant::fromValue(card_use);
    source->tag["zhaofuUseTag"] = use_list;
}

class ZhaofuViewAsSkill : public ViewAsSkill
{
public:
    ZhaofuViewAsSkill() : ViewAsSkill("zhaofu")
    {

    }

    virtual bool isEnabledAtPlay(const Player *) const
    {
        return false;
    }

    virtual bool isEnabledAtResponse(const Player *, const QString &pattern) const
    {
        return pattern.startsWith("@@zhaofu");
    }

    virtual bool viewFilter(const QList<const Card *> &selected, const Card *to_select) const
    {
        if (Sanguosha->currentRoomState()->getCurrentCardUsePattern().endsWith("1"))
            return selected.isEmpty() && !Self->isJilei(to_select);
        else
            return false;
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (Sanguosha->currentRoomState()->getCurrentCardUsePattern().endsWith("1")) {
            if (cards.length() == 1) {
                ZhaofuCard *zhaofuCard = new ZhaofuCard;
                zhaofuCard->addSubcards(cards);
                return zhaofuCard;
            }
        } else if (cards.isEmpty()) {
            return new ZhaofuVSCard;
        }
        return NULL;
    }
};

class Zhaofu : public TriggerSkill
{
public:
    Zhaofu() : TriggerSkill("zhaofu")
    {
        events << EventPhaseStart << CardFinished;
        view_as_skill = new ZhaofuViewAsSkill;
    }

    virtual bool canPreshow() const
    {
        return true;
    }

    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (triggerEvent == EventPhaseStart && TriggerSkill::triggerable(player)) {
            if (player->getPhase() == Player::Play && !player->isNude()) {
                QList<ServerPlayer *> allplayers = room->getAlivePlayers();
                int x = 0;
                foreach (ServerPlayer *p, allplayers) {
                    x += p->getMark("#reward");
                }
                if (x < 3)
                    skill_list.insert(player, QStringList(objectName()));
            }
        } else if (triggerEvent == CardFinished && player->getMark("#reward") > 0) {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card->getTypeId() == Card::TypeBasic || use.card->isNDTrick()) {
                Card *new_card = Sanguosha->cloneCard(use.card->objectName(), Card::NoSuit, 0);
                new_card->setSkillName("_zhaofu");
                new_card->deleteLater();

                QList<ServerPlayer *> owners = room->findPlayersBySkillName(objectName());
                foreach (ServerPlayer *owner, owners) {
                    if (new_card->isAvailable(owner))
                        skill_list.insert(owner, QStringList(objectName()));
                }
            }

        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *target, QVariant &data, ServerPlayer *player) const
    {
        if (triggerEvent == EventPhaseStart) {
            return room->askForUseCard(player, "@@zhaofu1", "@zhaofu1", -1, Card::MethodDiscard);
        } else if (triggerEvent == CardFinished) {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card->targetFixed()) {
                player->tag["ZhaofuUsedata"] = data;
                bool invoke = player->askForSkillInvoke(objectName(), "prompt:::"+use.card->objectName());
                player->tag.remove("ZhaofuUsedata");
                if (invoke) {
                    room->broadcastSkillInvoke(objectName(), player);
                    room->removePlayerMark(target, "#reward");

                    QVariantList use_list = player->tag["zhaofuUseTag"].toList();
                    use_list << QVariant::fromValue(CardUseStruct());
                    player->tag["zhaofuUseTag"] = use_list;

                    return true;
                }
            } else {
                player->tag["ZhaofuUsedata"] = data;
                room->setPlayerProperty(player, "zhaofucard", use.card->objectName());
                bool invoke = room->askForUseCard(player, "@@zhaofu2", "@zhaofu2:::"+use.card->objectName(), -1, Card::MethodNone);
                player->tag.remove("ZhaofuUsedata");
                room->setPlayerProperty(player, "zhaofucard", QVariant());
                if (invoke) {
                    LogMessage log;
                    log.type = "#InvokeSkill";
                    log.from = player;
                    log.arg = objectName();
                    room->sendLog(log);
                    room->notifySkillInvoked(player, objectName());
                    room->broadcastSkillInvoke(objectName(), player);
                    room->removePlayerMark(target, "#reward");
                    return true;
                }
            }
        }

        return false;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *player) const
    {
        if (triggerEvent == EventPhaseStart) {
            QVariantList data_list = player->tag["zhaofuTag"].toList();
            QVariant zhaofu_data = data_list.takeLast();
            CardEffectStruct effect = zhaofu_data.value<CardEffectStruct>();
            ServerPlayer *target = effect.to;
            if (target)
                room->addPlayerMark(target, "#reward");
        } else if (triggerEvent == CardFinished) {
            CardUseStruct use = data.value<CardUseStruct>();
            QVariantList data_list = player->tag["zhaofuUseTag"].toList();
            QVariant zhaofu_data = data_list.takeLast();
            CardUseStruct zhaofu_use = zhaofu_data.value<CardUseStruct>();

            Card *zhaofu_card = Sanguosha->cloneCard(use.card->objectName(), Card::NoSuit, 0);
            if (zhaofu_card) {
                zhaofu_card->setSkillName("_zhaofu");
                zhaofu_card->setCanRecast(false);
                zhaofu_card->deleteLater();
            }

            room->useCard(CardUseStruct(zhaofu_card, player, zhaofu_use.to));


        }
        return false;
    }

    virtual int getEffectIndex(const ServerPlayer *, const Card *card) const
    {
        return (card->getTypeId() == Card::TypeSkill) ? -1 : 0;
    }
};

class Qushi : public TriggerSkill
{
public:
    Qushi() : TriggerSkill("qushi")
    {
        events << CardFinished << EventPhaseChanging << SlashMissed;
        frequency = Compulsory;
    }

    virtual void record(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if (event == EventPhaseChanging) {
            PhaseChangeStruct change = data.value<PhaseChangeStruct>();
            if (change.from == Player::Play) {
                room->setPlayerMark(player, "#qushi", 0);
            }
        }
        if (event == SlashMissed) {
            SlashEffectStruct effect = data.value<SlashEffectStruct>();
            if (effect.slash) {
                room->setCardFlag(effect.slash, "GlobalSlashMissed");
            }
        }
    }

    virtual QStringList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (event == CardFinished && TriggerSkill::triggerable(player) && player->getPhase() == Player::Play) {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card->isKindOf("Slash") && use.card->hasFlag("GlobalSlashMissed")) {
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
    {
        bool invoke = false;
        if (player->hasShownSkill(this)) {
            invoke = true;
            room->sendCompulsoryTriggerLog(player, objectName());
        } else {
            invoke = player->askForSkillInvoke(this, data);
        }
        if (invoke) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
    {
        room->addPlayerMark(player, "#qushi");
        return false;
    }
};

class QushiTargetMod : public TargetModSkill
{
public:
    QushiTargetMod() : TargetModSkill("#qushi-target")
    {
        pattern = "Slash";
    }

    virtual int getResidueNum(const Player *from, const Card *, const Player *) const
    {
        return from->getMark("#qushi");
    }

    virtual int getExtraTargetNum(const Player *from, const Card *) const
    {
        return from->getMark("#qushi");
    }
};

YanxingSummon::YanxingSummon()
    : ArraySummonCard("yanxing")
{
    mute = true;
}

class Yanxing : public BattleArraySkill
{
public:
    Yanxing() : BattleArraySkill("yanxing", HegemonyMode::Formation)
    {
        events << EventPhaseStart << GeneralShown;
    }

    virtual bool canPreshow() const
    {
        return false;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if (triggerEvent == EventPhaseStart) {
            if (player != NULL && player->isAlive() && player->getPhase() == Player::RoundStart) {
                ServerPlayer *gongsunzan = room->findPlayerBySkillName("yanxing");
                if (gongsunzan && gongsunzan->isAlive() && gongsunzan->hasShownSkill("yanxing") && player->inFormationRalation(gongsunzan)) {
                    room->doBattleArrayAnimate(gongsunzan);
                    room->broadcastSkillInvoke(objectName(), gongsunzan);
                }
            }
        } else if (triggerEvent == GeneralShown) {
            if (TriggerSkill::triggerable(player) && player->hasShownSkill(objectName()) && data.toBool() == player->inHeadSkills(objectName())) {
                room->doBattleArrayAnimate(player);
                room->broadcastSkillInvoke(objectName(), player);
            }
        }
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer * &) const
    {
        return QStringList();
    }
};

class YanxingDistance : public DistanceSkill
{
public:
    YanxingDistance() : DistanceSkill("#yanxing-distance")
    {
    }

    virtual int getCorrect(const Player *from, const Player *) const
    {
        QList<const Player *> sib = from->getAliveSiblings();
        sib.append(from);
        QList<const Player *> teammates = from->getFormation();

        if (sib.length() < 4 || teammates.length() < 2)
            return 0;

        int x = 0;
        foreach (const Player *p, teammates) {
            if (p->hasShownSkill("yanxing")) {
                x -= teammates.length() - 1;
            }
        }

        return x;
    }
};

class Yicong : public TriggerSkill
{
public:
    Yicong() : TriggerSkill("yicong")
    {
        relate_to_place = "head";
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer * &) const
    {
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
    {
        return false;
    }
};

class YicongOther : public TriggerSkill
{
public:
    YicongOther() : TriggerSkill("#yicong-other")
    {
        events << CardFinished;
        frequency = Compulsory;
    }

    virtual TriggerList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (event == CardFinished && player && player->isAlive()) {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card->isKindOf("Slash") && use.card->hasFlag("GlobalSlashMissed") && room->isAllOnPlace(use.card, Player::PlaceTable)) {
                QList<ServerPlayer *> skill_owners = room->findPlayersBySkillName("yicong");
                foreach (ServerPlayer *skill_owner, skill_owners) {
                    if (TriggerSkill::triggerable(skill_owner) && skill_owner->hasShownSkill("yicong") && player->isFriendWith(skill_owner) && player != skill_owner) {
                        skill_list.insert(skill_owner, QStringList(objectName()));
                    }
                }
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *skill_owner) const
    {
        if (room->askForChoice(player, "yicong", "yes+no", data, "@yicong-choose:" + skill_owner->objectName()) == "yes") {
            LogMessage log;
            log.type = "#InvokeOthersSkill";
            log.from = player;
            log.to << skill_owner;
            log.arg = "yicong";
            room->sendLog(log);
            room->broadcastSkillInvoke("yicong", skill_owner);
            room->notifySkillInvoked(skill_owner, "yicong");
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *skill_owner) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card && room->isAllOnPlace(use.card, Player::PlaceTable)) {
            skill_owner->obtainCard(use.card);
        }
        return false;
    }
};

class Haokui : public PhaseChangeSkill
{
public:
    Haokui() : PhaseChangeSkill("haokui")
    {
    }

    virtual void record(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (player->getPhase() == Player::NotActive) {
            room->setPlayerMark(player, "##haokui", 0);
        }
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer * &) const
    {
        if (PhaseChangeSkill::triggerable(player) && player->getPhase() == Player::Play) {
            return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (player->askForSkillInvoke(this)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const
    {
        player->drawCards(2, objectName());
        player->getRoom()->addPlayerMark(player, "##haokui");
        return false;
    }
};

class HaokuiEffect : public TriggerSkill
{
public:
    HaokuiEffect() : TriggerSkill("#haokui-effect")
    {
        events << CardsMoveOneTime << EventPhaseEnd;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (!player || player->isDead() || player->getMark("##haokui") == 0 || player->getPhase() != Player::Discard) {
            return QStringList();
        }
        if (event == CardsMoveOneTime) {
            QVariantList move_datas = data.toList();
            foreach (const QVariant &move_data, move_datas) {
                CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                if (move.to_place == Player::DiscardPile) {
                    foreach (int id, move.card_ids) {
                        if (room->getCardPlace(id) == Player::DiscardPile) {
                            return QStringList(objectName());
                        }
                    }
                }
            }
        }
        if (event == EventPhaseEnd && !player->hasFlag("haokuiInvoked")) {
            return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *, ServerPlayer *, QVariant &) const
    {
        return true;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (event == CardsMoveOneTime) {
            QList<int> ids;
            QVariantList move_datas = data.toList();
            foreach (const QVariant &move_data, move_datas) {
                CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                if (move.to_place == Player::DiscardPile) {
                    foreach (int id, move.card_ids) {
                        if (room->getCardPlace(id) == Player::DiscardPile) {
                            ids << id;
                        }
                    }
                }
            }
            if (!ids.isEmpty()) {
                QList<ServerPlayer *> all_players = room->getAlivePlayers();
                QList<ServerPlayer *> to_choose;
                foreach (ServerPlayer *p, all_players) {
                    if (!p->isFriendWith(player) && p->isBigKingdomPlayer()) {
                        to_choose << p;
                    }
                }
                if (to_choose.isEmpty()) {
                    int max_hp = 0;
                    foreach (ServerPlayer *p, all_players) {
                        if (!p->isFriendWith(player) && p->getHp() >= max_hp) {
                            if (p->getHp() > max_hp) {
                                max_hp = p->getHp();
                                to_choose.clear();
                            }
                            to_choose << p;
                        }
                    }
                }
                if (!to_choose.isEmpty()) {
                    ServerPlayer *to = room->askForPlayerChosen(player, to_choose, "haokui_give", "@haokui-give");
                    if (to) {
                        CardMoveReason reason(CardMoveReason::S_REASON_GIVE, player->objectName(), to->objectName(), "haokui", "");
                        DummyCard dummy(ids);
                        room->obtainCard(to, &dummy, reason);
                        room->setPlayerFlag(player, "haokuiInvoked");
                    }
                }
            }
        }
        if (event == EventPhaseEnd) {
            if (player->getGeneral() && player->getGeneral()->hasSkill("haokui") && player->hasShownAllGenerals()) {
                if (room->askForChoice(player, "haokui_hide", "yes+no", data, "@haokui-hide1") == "yes") {
                    player->hideGeneral();
                }
            }
            if (player->getGeneral2() && player->getGeneral2()->hasSkill("haokui") && player->hasShownAllGenerals()) {
                if (room->askForChoice(player, "haokui_hide", "yes+no", data, "@haokui-hide2") == "yes") {
                    player->hideGeneral(false);
                }
            }
            if (player->getMark("haokuitransformUsed") == 0) {
                QList<ServerPlayer *> all_players = room->getAlivePlayers();
                QList<ServerPlayer *> to_choose;
                foreach (ServerPlayer *p, all_players) {
                    if (p->isFriendWith(player) && p->canTransform()) {
                        to_choose << p;
                    }
                }
                if (!to_choose.isEmpty()) {
                    ServerPlayer *to = room->askForPlayerChosen(player, to_choose, "haokui_transform", "@haokui-transform", true);
                    if (to && room->askForChoice(to, "transform_haokui", "yes+no", data, "@transform-ask:::haokui") == "yes") {
                        room->addPlayerMark(player, "haokuitransformUsed");
                        room->transformDeputyGeneral(to);
                    }
                }
            }
        }
        return false;
    }
};

class Xushi : public TriggerSkill
{
public:
    Xushi() : TriggerSkill("xushi")
    {
        events << TargetConfirming;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (TriggerSkill::triggerable(player) && !player->hasShownSkill(objectName())) {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card->getTypeId() != Card::TypeSkill && use.from != player && use.to.contains(player)) {
                foreach (ServerPlayer *p, use.to) {
                    if (p != player) {
                        return QStringList();
                    }
                }
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (player->askForSkillInvoke(this)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        room->cancelTarget(use, player);
        data = QVariant::fromValue(use);
        if (use.from && use.from->isAlive()) {
            room->askForDiscard(use.from, "xushi_discard", 1, 1, false, true);
        }
        return false;
    }
};

class Jiange : public OneCardViewAsSkill
{
public:
    Jiange() : OneCardViewAsSkill("jiange")
    {
        response_or_use = true;
    }

    virtual bool viewFilter(const Card *card) const
    {
        if (card->getTypeId() == Card::TypeBasic) return false;
        if (Sanguosha->getCurrentCardUseReason() == CardUseStruct::CARD_USE_REASON_PLAY) {
            Slash *slash = new Slash(card->getSuit(), card->getNumber());
            slash->addSubcard(card);
            slash->deleteLater();
            return slash->isAvailable(Self);
        }
        return true;
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        Slash *slash = new Slash(originalCard->getSuit(), originalCard->getNumber());
        slash->addSubcard(originalCard);
        slash->setSkillName(objectName());
        slash->setShowSkill(objectName());
        return slash;
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return Slash::IsAvailable(player);
    }

    virtual bool isEnabledAtResponse(const Player *, const QString &pattern) const
    {
        return pattern == "slash";
    }
};

MemptyCard::MemptyCard()
{
    target_fixed = true;
}


class QianxueSelect : public ViewAsSkill
{
public:
    QianxueSelect() : ViewAsSkill("qianxueselect")
    {
        expand_pile = "#qianxue";
        response_pattern = "@@qianxueselect";
    }

    virtual bool viewFilter(const QList<const Card *> &selected, const Card *to_select) const
    {
        if (selected.length() < Self->getMark("qianxuecount")) {
            QList<int> ids = Self->getPile("#qianxue");
            if (!ids.contains(to_select->getId())) return false;
            if (to_select->getTypeId() == Card::TypeBasic) {
                foreach (int id, ids) {
                    const Card *c2 = Sanguosha->getCard(id);
                    if (c2->getTypeId() != Card::TypeBasic && !selected.contains(c2)) {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (cards.isEmpty()) return NULL;
        foreach (const Card *card, cards) {
            if (card->getTypeId() == Card::TypeBasic) {
                QList<int> ids = Self->getPile("#qianxue");
                foreach (int id, ids) {
                    const Card *c2 = Sanguosha->getCard(id);
                    if (c2->getTypeId() != Card::TypeBasic && !cards.contains(c2)) {
                        return NULL;
                    }
                }
                break;
            }
        }

        MemptyCard *skillcard = new MemptyCard;
        foreach (const Card *card, cards) {
            skillcard->addSubcard(card);
        }
        return skillcard;
    }
};

class Qianxue : public TriggerSkill
{
public:
    Qianxue() : TriggerSkill("qianxue")
    {
        events << EventPhaseChanging << ConfirmMoveCards;
        relate_to_place = "head";
    }

    virtual QStringList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (event == EventPhaseChanging) {
            PhaseChangeStruct change = data.value<PhaseChangeStruct>();
            if (change.to == Player::NotActive) {
                QVariantList discardpile = room->getTag("GlobalRoundDisCardPile").toList();
                bool can_trigger_check = false;
                foreach (const QVariant &card_data, discardpile) {
                    int card_id = card_data.toInt();
                    if (room->getCardPlace(card_id) == Player::DiscardPile && !Sanguosha->getCard(card_id)->isKindOf("ThreatenEmperor")) {
                        can_trigger_check = true;
                        break;
                    }
                }
                if (can_trigger_check) {
                    QList<ServerPlayer *> skill_owners = room->findPlayersBySkillName(objectName());
                    foreach (ServerPlayer *skill_owner, skill_owners) {
                        if (TriggerSkill::triggerable(skill_owner) && (skill_owner->hasFlag("GlobalLoseAllHandCards") ||
                                skill_owner->hasFlag("GlobalLoseAllEquips") || skill_owner->hasFlag("GlobalLoseAllDelayedTricks"))) {
                            return QStringList(objectName() + "->" + skill_owner->objectName());
                        }
                    }
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *player) const
    {
        int x = 0;
        if (player->hasFlag("GlobalLoseAllHandCards")) x++;
        if (player->hasFlag("GlobalLoseAllEquips")) x++;
        if (player->hasFlag("GlobalLoseAllDelayedTricks")) x++;
        if (player->askForSkillInvoke(objectName(), QVariant("invoke:::" + QString::number(x)))) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *player) const
    {
        int x = 0;
        if (player->hasFlag("GlobalLoseAllHandCards")) x++;
        if (player->hasFlag("GlobalLoseAllEquips")) x++;
        if (player->hasFlag("GlobalLoseAllDelayedTricks")) x++;
        if (x == 0) return false;

        QList<int> cards;
        QVariantList discardpile = room->getTag("GlobalRoundDisCardPile").toList();
        foreach (const QVariant &card_data, discardpile) {
            int card_id = card_data.toInt();
            if (room->getCardPlace(card_id) == Player::DiscardPile && !Sanguosha->getCard(card_id)->isKindOf("ThreatenEmperor")) {
                cards << card_id;
            }
        }
        if (cards.isEmpty()) return false;

        room->setPlayerMark(player, "qianxuecount", x);
        room->notifyMoveToPile(player, cards, "qianxue", Player::PlaceTable, true, true);
        const Card *to_get = room->askForCard(player, "@@qianxueselect", "@qianxue-select:::" + QString::number(x), QVariant(), Card::MethodNone);
        room->setPlayerMark(player, "qianxuecount", 0);
        room->notifyMoveToPile(player, cards, "qianxue", Player::PlaceTable, false, false);

        if (to_get && to_get->subcardsLength() > 0) {
            room->obtainCard(player, to_get, true);
        }
        return false;
    }
};

class Zhuhu : public TriggerSkill
{
public:
    Zhuhu() : TriggerSkill("zhuhu")
    {
        events << DeathFinished << GeneralTransformed;
        frequency = Compulsory;
    }

    virtual TriggerList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (event == DeathFinished && TriggerSkill::triggerable(player) && player->hasSkill("zhuhu")) {
            DeathStruct death = data.value<DeathStruct>();
            if (death.who && death.who->isFriendWith(player)) {
                skill_list.insert(player, QStringList(objectName()));
            }
        } else if (event == GeneralTransformed) {
            QList<ServerPlayer *> skill_owners = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *skill_owner, skill_owners) {
                if (TriggerSkill::triggerable(skill_owner) && skill_owner->isFriendWith(player)) {
                    skill_list.insert(skill_owner, QStringList(objectName()));
                }
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *player) const
    {
        bool invoke = false;
        if (player->hasShownSkill(objectName())) {
            invoke = true;
            room->sendCompulsoryTriggerLog(player, objectName());
        } else {
            invoke = player->askForSkillInvoke(this);
        }
        if (invoke) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *player) const
    {
        if (player->getActualGeneral1()->hasSkill("zhuhu")) {
            room->exchangeHeadAndDeputyGeneral(player);
        } else if (player->getActualGeneral2()->hasSkill("zhuhu") && player->isChained()) {
            room->setPlayerProperty(player, "chained", false);
        }
        if (player->canTransform()) {
            room->transformDeputyGeneral(player);
        }
        return false;
    }
};

class Xiaolian : public TriggerSkill
{
public:
    Xiaolian() : TriggerSkill("xiaolian")
    {
    }

    virtual bool canPreshow() const
    {
        return false;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer * &) const
    {
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
    {
        return false;
    }
};

class XiaolianCompulsory : public TriggerSkill
{
public:
    XiaolianCompulsory() : TriggerSkill("#xiaolian-compulsory")
    {
        events << GeneralShowed << GeneralRemoved;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (event == GeneralShowed) {
            if (player->cheakSkillLocation("xiaolian", data) && player->getMark("xiaolianUsed") == 0) {
                return QStringList(objectName());
            }
        }
        if (event == GeneralRemoved) {
            QStringList remove_data = data.toString().split(":");
            if (remove_data.length() == 2 && remove_data[1].split("+").contains("xiaolian")) {
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        room->sendCompulsoryTriggerLog(player, "xiaolian");
        room->broadcastSkillInvoke("xiaolian", player);
        if (event == GeneralShowed) {
            room->addPlayerMark(player, "xiaolianUsed");
        }
        return true;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (event == GeneralShowed) {
            room->askForQiaobian(player, room->getAlivePlayers(), "xiaolian", "@xiaolian-move", true, false);
        }
        if (event == GeneralRemoved) {
            QList<ServerPlayer *> friends;
            foreach (ServerPlayer *p, room->getAlivePlayers()) {
                if (player->isFriendWith(p)) {
                    friends << p;
                }
            }
            if (!friends.isEmpty()) {
                room->sortByActionOrder(friends);
                foreach (ServerPlayer *p, friends) {
                    if (p->isAlive()) {
                        p->drawCards(1, "xiaolian");
                    }
                }
            }
        }
        return false;
    }
};

class Kangkai : public TriggerSkill
{
public:
    Kangkai() : TriggerSkill("kangkai")
    {
        events << TargetConfirmed;
    }

    virtual TriggerList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card && use.card->isKindOf("Slash")) {
            QList<ServerPlayer *> skill_owners = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *skill_owner, skill_owners) {
                if (TriggerSkill::triggerable(skill_owner) && skill_owner->isFriendWith(player) && skill_owner->ownSkill(objectName())) {
                    skill_list.insert(skill_owner, QStringList(objectName()));
                }
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *target, QVariant &data, ServerPlayer *player) const
    {
        QVariant source_data = QVariant::fromValue(target);
        if (player->askForSkillInvoke(objectName(), source_data)) {
            room->broadcastSkillInvoke(objectName(), player);
            player->removeGeneral(player->inHeadSkills(objectName()));
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *source) const
    {
        if (source->isDead()) return false;
        ServerPlayer *target = room->askForPlayerChosen(source, room->getAlivePlayers(), "kangkai_target", "@kangkai-target");
        if (target) {
            room->acquireSkill(target, "feiying_caoang", true, false);
            room->addPlayerMark(target, "##kangkai");
            if (target != source) {
                RecoverStruct recover;
                recover.who = source;
                room->recover(target, recover);
                if (target->isChained()) {
                    room->setPlayerProperty(target, "chained", false);
                }
            }
        }
        return false;
    }
};

class FeiyingCaoang : public DistanceSkill
{
public:
    FeiyingCaoang() : DistanceSkill("feiying_caoang")
    {
    }

    virtual int getCorrect(const Player *, const Player *to) const
    {
        if (to->hasShownSkill(objectName())) {
            return 1;
        }
        return 0;
    }
};

class Nizhan : public TriggerSkill
{
public:
    Nizhan() : TriggerSkill("nizhan")
    {
        events << EventPhaseChanging;
    }

    virtual TriggerList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;

        if (player && player->isAlive()) {
            PhaseChangeStruct change = data.value<PhaseChangeStruct>();
            if (change.to == Player::NotActive) {
                QList<ServerPlayer *> skill_owners = room->findPlayersBySkillName(objectName());
                foreach (ServerPlayer *skill_owner, skill_owners) {
                    if (TriggerSkill::triggerable(skill_owner) && player != skill_owner &&
                        (skill_owner->hasFlag("GlobalLoseAllHandCards") || skill_owner->getCardUsedTimes("Jink+Nullification") > 0)) {
                        skill_list.insert(skill_owner, QStringList(objectName()));
                    }
                }
            }
        }

        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *target, QVariant &, ServerPlayer *player) const
    {
        if (player->askForSkillInvoke(objectName(), QVariant::fromValue(target))) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *target, QVariant &, ServerPlayer *player) const
    {
        QStringList choices;
        if (player->canSlash(target, false)) {
            choices << "slash";
        }
        if (player->canGetCard(target, "he")) {
            choices << "extraction";
        }
        if (choices.isEmpty()) return false;

        QString choice = room->askForChoice(player, objectName(), choices.join("+"), QVariant(), "@nizhan-choose::" + target->objectName(), "extraction+slash");
        if (choice == "extraction") {
            int card_id = room->askForCardChosen(player, target, "he", objectName(), false, Card::MethodGet);
            CardMoveReason reason(CardMoveReason::S_REASON_EXTRACTION, player->objectName());
            room->obtainCard(player, Sanguosha->getCard(card_id), reason, false);
        } else if (choice == "slash") {
            Slash *slash = new Slash(Card::SuitToBeDecided, -1);
            slash->setSkillName(objectName());
            room->useCard(CardUseStruct(slash, player, target), false);
        }
        return false;
    }
};

class NizhanEffect : public TriggerSkill
{
public:
    NizhanEffect() : TriggerSkill("#nizhan-effect")
    {
        events << TargetChosen;
    }

    virtual QStringList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (!player || player->isDead()) return QStringList();

        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card && use.card->isKindOf("Slash") && use.card->getSkillName() == "nizhan") {
            ServerPlayer *target = use.to.at(use.index);
            if (target && target->isAlive()) {
                return QStringList(objectName() + "->" + target->objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
    {
        return true;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *target, QVariant &data, ServerPlayer *player) const
    {
        CardUseStruct use = data.value<CardUseStruct>();

        LogMessage log;
        log.type = "#NizhanEffect";
        log.from = player;
        log.to << target;
        room->sendLog(log);

        target->addQinggangTag(use.card);

        return false;
    }
};


XiliangPackage::XiliangPackage()
    : Package("xiliang")
{
    General *zhangchunhua = new General(this, "zhangchunhua", "wei", 3, false);
    zhangchunhua->addCompanion("simayi");
    zhangchunhua->addSkill(new Guojue);
    zhangchunhua->addSkill(new GuojueDamage);
    zhangchunhua->addSkill(new Shangshi);
    related_skills.insertMulti("guojue", "#guojue-damage");

    General *caoang = new General(this, "caoang", "wei");
    caoang->addCompanion("dianwei");
    caoang->addSkill(new Xiaolian);
    caoang->addSkill(new XiaolianCompulsory);
    caoang->addSkill(new Kangkai);
    related_skills.insertMulti("xiaolian", "#xiaolian-compulsory");

    General *shitao = new General(this, "shitao", "shu");
    shitao->addCompanion("wolong");
    shitao->addCompanion("xushu");
    shitao->setHeadMaxHpAdjustedValue();
    shitao->addSkill(new Jiange);
    shitao->addSkill(new Qianxue);
    shitao->addSkill(new Zhuhu);

//    General *diy_xushu = new General(this, "diy_xushu", "shu");
//    diy_xushu->addCompanion("wolong");
//    diy_xushu->addCompanion("zhaoyun");
//    diy_xushu->addCompanion("shitao");
//    diy_xushu->setDeputyMaxHpAdjustedValue();
//    diy_xushu->addSkill(new Zhuhai);
//    diy_xushu->addSkill(new Pozhen);
//    diy_xushu->addSkill(new Jiancai);

    General *chengpu = new General(this, "chengpu", "wu");
    chengpu->addCompanion("zhouyu");
    chengpu->addSkill(new Huxun);
    chengpu->addSkill(new Yuancong);

    General *guyong = new General(this, "guyong", "wu", 3);
    guyong->addSkill(new Lifu);
    guyong->addSkill(new Yanzhong);

    General *gongsunzan = new General(this, "gongsunzan", "qun");
    gongsunzan->setHeadMaxHpAdjustedValue();
    gongsunzan->addSkill(new Qushi);
    gongsunzan->addSkill(new QushiTargetMod);
    gongsunzan->addSkill(new Yanxing);
    gongsunzan->addSkill(new YanxingDistance);
    gongsunzan->addSkill(new Yicong);
    gongsunzan->addSkill(new YicongOther);
    related_skills.insertMulti("qushi", "#qushi-target");
    related_skills.insertMulti("yanxing", "#yanxing-distance");
    related_skills.insertMulti("yicong", "#yicong-other");


    General *chengyu = new General(this, "chengyu", "wei", 3);
    chengyu->addCompanion("caopi");
    chengyu->addSkill(new Shefu);
    chengyu->addSkill(new ShefuCompulsory);
    chengyu->addSkill(new DetachEffectSkill("shefu", "ambush"));
    insertRelatedSkills("shefu", 2, "#shefu-compulsory", "#shefu-clear");
    chengyu->addSkill(new Benyu);

    General *guohuai = new General(this, "guohuai", "wei");
    guohuai->addCompanion("zhanghe");
    guohuai->addSkill(new Jingce);

    General *maliang = new General(this, "maliang", "shu", 3);
    maliang->addCompanion("zhugeliang");
    maliang->addSkill(new Mumeng);
    maliang->addSkill(new Naman);

    General *quancong = new General(this, "quancong", "wu");
    quancong->addSkill(new Qinzhong);
    quancong->addSkill(new Zhaofu);

    General *chendeng = new General(this, "chendeng", "qun", 3);
    chendeng->addSkill(new Haokui);
    chendeng->addSkill(new HaokuiEffect);
    chendeng->addSkill(new Xushi);
    related_skills.insertMulti("haokui", "#haokui-effect");

    General *yijibo = new General(this, "yijibo", "shu", 3);
    yijibo->addSkill(new Dingke);
    yijibo->addSkill(new Jiyuan);

    General *sunhuan = new General(this, "sunhuan", "wu");
    sunhuan->addCompanion("luxun");
    sunhuan->addSkill(new Nizhan);
    sunhuan->addSkill(new NizhanEffect);
    related_skills.insertMulti("nizhan", "#nizhan-effect");

    General *zhangyi = new General(this, "zhangyi", "shu");
    zhangyi->addCompanion("liaohua");
    zhangyi->addSkill(new Kangrui);
    zhangyi->addSkill(new KangruiProhibit);
    insertRelatedSkills("kangrui", "#kangrui-prohibit");

    General *zhuhuan = new General(this, "zhuhuan", "wu");
    zhuhuan->addSkill(new Jutian);

    addMetaObject<ShangshiCard>();
    addMetaObject<ShefuCard>();
    addMetaObject<MumengCard>();
    addMetaObject<LifuCard>();
    addMetaObject<HuxunMoveCard>();
    addMetaObject<ZhaofuCard>();
    addMetaObject<ZhaofuVSCard>();
    addMetaObject<YanxingSummon>();
    addMetaObject<MemptyCard>();

    skills << new HuxunMove << new YuancongUseCard << new QianxueSelect << new FeiyingCaoang;
}

