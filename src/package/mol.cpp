﻿/********************************************************************
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

#include "mol.h"
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

class Wuku : public TriggerSkill
{
public:
    Wuku() : TriggerSkill("wuku")
    {
        events << CardUsed << EventLoseSkill;
        frequency = Compulsory;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if (triggerEvent == EventLoseSkill && player && data.toString().split(":").first() == objectName()) {
            room->setPlayerMark(player, "#wuku", 0);
        }
    }

    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if (triggerEvent == CardUsed && player != NULL && player->hasShownOneGeneral()) {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card->getTypeId() == Card::TypeEquip) {
                QList<ServerPlayer *> owners = room->findPlayersBySkillName(objectName());
                TriggerList skill_list;
                foreach (ServerPlayer *owner, owners)
                    if (owner->hasShownOneGeneral() && !player->isFriendWith(owner) && owner->getMark("#wuku") < 2)
                        skill_list.insert(owner, QStringList(objectName()));
                return skill_list;
            }
        }
        return TriggerList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *player) const
    {
        bool invoke = false;
        if (player->hasShownSkill(objectName())) {
            invoke = true;
            room->sendCompulsoryTriggerLog(player, objectName());
        } else
            invoke = player->askForSkillInvoke(this, data);

        if (invoke) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer *player) const
    {
        player->gainMark("#wuku");
        return false;
    }
};

MiewuCard::MiewuCard()
{
    will_throw = false;
}

bool MiewuCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->tag["miewu"].toString());
    if (mutable_card) {
        mutable_card->addSubcards(subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetFilter(targets, to_select, Self) && !Self->isProhibited(to_select, mutable_card, targets);
}

bool MiewuCard::targetFixed() const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->tag["miewu"].toString());
    if (mutable_card) {
        mutable_card->addSubcards(subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetFixed();
}

bool MiewuCard::targetsFeasible(const QList<const Player *> &targets, const Player *Self) const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->tag["miewu"].toString());
    if (mutable_card) {
        mutable_card->addSubcards(subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }

    return mutable_card && mutable_card->targetsFeasible(targets, Self);
}

const Card *MiewuCard::validate(CardUseStruct &card_use) const
{
    return validateInResponse(card_use.from);
}

const Card *MiewuCard::validateInResponse(ServerPlayer *user) const
{
    Room *room = user->getRoom();

    user->loseMark("#wuku");
    room->setPlayerFlag(user, "MiewuUsed");

    QString card_name = toString().split(":").last();   //getUserString() bug here. damn it!

    Card *c = Sanguosha->cloneCard(card_name);
    c->setSkillName("miewu");
    c->addSubcards(subcards);
    c->deleteLater();
    return c;
}

void MiewuCard::validateAfter(CardUseStruct &card_use) const
{
    validateInResponseAfter(card_use.from);
}

void MiewuCard::validateInResponseAfter(ServerPlayer *player) const
{
    player->drawCards(1, "miewu");
}

class Miewu : public OneCardViewAsSkill
{
public:
    Miewu() : OneCardViewAsSkill("miewu")
    {
        response_or_use = true;
        guhuo_type = "btd";
    }

    virtual bool viewFilter(const Card *) const
    {
        return true;
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        QString card_name = Self->tag["miewu"].toString();
        if (!card_name.isEmpty()) {
            MiewuCard *card = new MiewuCard;
            card->setUserString(card_name);
            card->addSubcard(originalCard);
            card->setShowSkill(objectName());
            return card;
        }
        return NULL;
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return player->getMark("#wuku") > 0 && !player->hasFlag("MiewuUsed");
    }

    virtual bool isEnabledAtResponse(const Player *player, const QString &) const
    {
        return player->getMark("#wuku") > 0 && !player->hasFlag("MiewuUsed");
    }

    virtual bool isEnabledAtNullification(const ServerPlayer *player) const
    {
        return player->getMark("#wuku") > 0 && !player->hasFlag("MiewuUsed") && !player->isNude();
    }
};

GuishuCard::GuishuCard()
{
    will_throw = false;
}

bool GuishuCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->tag["guishu"].toString());
    if (mutable_card) {
        mutable_card->addSubcards(subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetFilter(targets, to_select, Self) && !Self->isProhibited(to_select, mutable_card, targets);
}

bool GuishuCard::targetFixed() const
{
    Card *mutable_card = Sanguosha->cloneCard(getUserString());
    if (mutable_card) {
        mutable_card->addSubcards(subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetFixed();
}

bool GuishuCard::targetsFeasible(const QList<const Player *> &targets, const Player *Self) const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->tag["guishu"].toString());
    if (mutable_card) {
        mutable_card->addSubcards(subcards);
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetsFeasible(targets, Self);
}

void GuishuCard::onUse(Room *room, const CardUseStruct &card_use) const
{
    ServerPlayer *source = card_use.from;
    QString card_name = toString().split(":").last();

    Card *use_card = Sanguosha->cloneCard(card_name);
    use_card->setSkillName("guishu");
    use_card->addSubcards(subcards);
    use_card->setCanRecast(false);
    use_card->setShowSkill("guishu");

    if (use_card->isAvailable(source)) {
        room->setPlayerMark(source, "GuishuCardState", (card_name == "befriend_attacking")?1:2);
        room->useCard(CardUseStruct(use_card, source, card_use.to));
    }
}

class GuishuViewAsSkill : public OneCardViewAsSkill
{
public:
    GuishuViewAsSkill() : OneCardViewAsSkill("guishu")
    {
        response_or_use = true;
    }

    virtual bool viewFilter(const Card *card) const
    {
        return (card->getSuit() == Card::Spade && !card->isEquipped());
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        QString c = Self->tag["guishu"].toString();
        if (c != "") {
            GuishuCard *card = new GuishuCard;
            card->addSubcard(originalCard);
            card->setUserString(c);
            return card;
        } else
            return NULL;
    }

    virtual bool isEnabledAtPlay(const Player *) const
    {
        return true;
    }

    QStringList getViewAsCardNames(const QList<const Card *> &selected) const
    {
        if (selected.length() != 1) return QStringList();
        QStringList card_names;
        card_names << "befriend_attacking" << "known_both";
        return card_names;
    }

    bool isEnabledtoViewAsCard(const QString &button_name, const QList<const Card *> &selected) const
    {
        QStringList card_names;
        card_names << "befriend_attacking" << "known_both";

        if (!card_names.contains(button_name) || Self->getMark("GuishuCardState") == card_names.indexOf(button_name) + 1)
            return false;

        return ViewAsSkill::isEnabledtoViewAsCard(button_name, selected);
    }
};

class Guishu : public TriggerSkill
{
public:
    Guishu() : TriggerSkill("guishu")
    {
        view_as_skill = new GuishuViewAsSkill;
        events << EventPhaseStart;
    }

    virtual void record(TriggerEvent , Room *room, ServerPlayer *player, QVariant &) const
    {
        if (player->getPhase() == Player::NotActive)
            room->setPlayerMark(player, "GuishuCardState", 0);
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer* &) const
    {
        return QStringList();
    }
};

class Yuanyu : public TriggerSkill
{
public:
    Yuanyu() : TriggerSkill("yuanyu")
    {
        events << DamageInflicted;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        DamageStruct damage = data.value<DamageStruct>();
        if (damage.from && damage.from->isAlive() && !damage.from->inMyAttackRange(player))
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        bool invoke = false;
        if (player->hasShownSkill(this)) {
            room->sendCompulsoryTriggerLog(player, objectName());
            invoke = true;
        } else invoke = player->askForSkillInvoke(this, data);
        if (invoke) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *, ServerPlayer *, QVariant &data, ServerPlayer *) const
    {
        DamageStruct damage = data.value<DamageStruct>();
        damage.damage--;
        data = QVariant::fromValue(damage);
        if (damage.damage <= 0)
            return true;
        return false;
    }
};

class Sidi : public TriggerSkill
{
public:
    Sidi() : TriggerSkill("sidi")
    {
        events << Damaged << EventPhaseStart << EventPhaseEnd;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == EventPhaseStart && player->getPhase() == Player::NotActive) {
            room->setPlayerMark(player, "##sidi+BasicCard", 0);
            room->setPlayerMark(player, "##sidi+EquipCard", 0);
            room->setPlayerMark(player, "##sidi+TrickCard", 0);

            QStringList skill_list = player->property("sidi_skills").toString().split("+");
            room->setPlayerProperty(player, "sidi_skills", QVariant());
            foreach (QString skill_name, skill_list) {
                room->setPlayerMark(player, "##sidi+" + skill_name, 0);
            }


        }
    }

    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        TriggerList skill_list;
        if (player == NULL || player->isDead()) return skill_list;
        if (triggerEvent == Damaged && !player->isNude()) {
            QList<ServerPlayer *> caozhens = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *caozhen, caozhens) {
                if (!caozhen->isFriendWith(player)) continue;
                QString type_name[4] = { QString(), "BasicCard", "TrickCard", "EquipCard" };
                QStringList types;
                types << "BasicCard" << "TrickCard" << "EquipCard";
                foreach (int card_id, caozhen->getPile("drive")) {
                    types.removeOne(type_name[Sanguosha->getCard(card_id)->getTypeId()]);
                }
                if (!types.isEmpty())
                    skill_list.insert(caozhen, QStringList(objectName()));
            }
        } else if (triggerEvent == EventPhaseEnd && player->getPhase() == Player::RoundStart && player->isAlive()) {
            QList<ServerPlayer *> caozhens = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *caozhen, caozhens) {
                if (!caozhen->isFriendWith(player) && !caozhen->getPile("drive").isEmpty())
                    skill_list.insert(caozhen, QStringList(objectName()));
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        bool invoke = false;
        if (triggerEvent == Damaged) {
            if (ask_who->askForSkillInvoke(this, QVariant::fromValue(player))) {
                room->broadcastSkillInvoke(objectName(), qrand()%2+1, ask_who);
                room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, ask_who->objectName(), player->objectName());
                invoke = true;
            }
        } else if (triggerEvent == EventPhaseEnd) {
            QList<int> ints = room->askForExchange(ask_who, objectName(), 3, 0, "@sidi-remove::"+player->objectName(), "drive");
            if (!ints.isEmpty()) {
                invoke = true;
                LogMessage log;
                log.type = "#InvokeSkill";
                log.from = ask_who;
                log.arg = objectName();
                room->sendLog(log);
                room->notifySkillInvoked(ask_who, objectName());
                room->broadcastSkillInvoke(objectName(), qrand()%2+3, ask_who);
                room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, ask_who->objectName(), player->objectName());
                CardMoveReason reason(CardMoveReason::S_REASON_REMOVE_FROM_PILE, QString(), ask_who->objectName(), objectName(), QString());
                DummyCard dummy(ints);
                room->throwCard(&dummy, reason, NULL);
                QString type_name[4] = { QString(), "BasicCard", "TrickCard", "EquipCard" };
                QStringList sidi_types;
                foreach (int id, ints) {
                    sidi_types << type_name[Sanguosha->getCard(id)->getTypeId()];
                }

                ask_who->tag["sidi_types"] = sidi_types;
            }

        }

        return invoke;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        if (triggerEvent == Damaged) {
            QString type_name[4] = { QString(), "BasicCard", "TrickCard", "EquipCard" };
            QStringList types;
            types << "BasicCard" << "TrickCard" << "EquipCard";
            foreach (int card_id, ask_who->getPile("drive")) {
                types.removeOne(type_name[Sanguosha->getCard(card_id)->getTypeId()]);
            }
            if (types.isEmpty()) return false;
            QList<int> ints = room->askForExchange(player, "sidi_put", 1, 0, "@sidi-put:"+ask_who->objectName(), QString(), types.join(","));
            if (!ints.isEmpty())
                ask_who->addToPile("drive", ints);

        } else if (triggerEvent == EventPhaseEnd) {
            QStringList sidi_types = ask_who->tag["sidi_types"].toStringList();
            ask_who->tag.remove("sidi_types");
            int x = sidi_types.length();

            QStringList choices;
            choices << "cardlimit" << "skilllimit" << "recover";
            QStringList all_choices = choices;

            for (int i = 0; i < x; i++) {
                if (player->isDead() || ask_who->isDead() || choices.isEmpty()) break;
                QString choice = room->askForChoice(ask_who, "sidi_choice", choices.join("+"), QVariant(),
                                   "@sidi-choice::"+ player->objectName(), all_choices.join("+"));

                choices.removeOne(choice);

                if (choice == "recover") {
                    QList<ServerPlayer *> players = room->getOtherPlayers(ask_who), weis;
                    foreach (ServerPlayer *p, players) {
                        if (p->isFriendWith(ask_who) && p->canRecover())
                            weis << p;
                    }
                    if (!weis.isEmpty()) {
                        ServerPlayer *to = room->askForPlayerChosen(player, weis, "sidi_recover", "@sidi-recover");
                        RecoverStruct recover;
                        recover.who = player;
                        room->recover(to, recover);
                    }
                }
                if (choice == "cardlimit") {
                    QString cardtype = room->askForChoice(ask_who, "sidi_cardtype", sidi_types.join("+"),
                        QVariant(), "@sidi-cardtype::"+player->objectName(), "BasicCard+EquipCard+TrickCard");
                    room->setPlayerCardLimitation(player, "use", cardtype, true);
                    room->addPlayerMark(player, "##sidi+"+cardtype);
                }
                if (choice == "skilllimit") {
                    QStringList skill_names;
                    if (player->hasShownGeneral1()) {
                        foreach (const Skill *skill, player->getActualGeneral1()->getVisibleSkillList()) {
                            skill_names << skill->objectName();
                        }
                    }
                    if (player->getGeneral2() && player->hasShownGeneral2()) {
                        foreach (const Skill *skill, player->getActualGeneral2()->getVisibleSkillList()) {
                            skill_names << skill->objectName();
                        }
                    }
                    if (skill_names.contains("bianhua")) {
                        const General *bianhua = player->getBianhuaGeneral();
                        if (bianhua) {
                            foreach (const Skill *skill, bianhua->getVisibleSkillList()) {
                                skill_names << skill->objectName();
                            }
                        }
                    }
                    if (!skill_names.isEmpty()) {
                        QString skill_name = room->askForChoice(ask_who, "sidi_skill", skill_names.join("+"),
                                                             QVariant(), "@sidi-skill::"+player->objectName());
                        room->addPlayerMark(player, "##sidi+" + skill_name);

                        QStringList assignee_list = player->property("sidi_skills").toString().split("+");
                        assignee_list << skill_name;
                        room->setPlayerProperty(player, "sidi_skills", assignee_list.join("+"));
                    }

                }
            }
        }

        return false;
    }
};

class SidiInvalidity : public InvaliditySkill
{
public:
    SidiInvalidity() : InvaliditySkill("#sidi-invalidity")
    {

    }

    virtual bool isSkillValid(const Player *target, const Skill *skill) const
    {
        return target->getMark("##sidi+" + skill->objectName()) == 0;
    }
};

class Dangxian : public TriggerSkill
{
public:
    Dangxian() : TriggerSkill("dangxian")
    {
        events << GeneralShowed << EventPhaseEnd;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        if (triggerEvent == GeneralShowed) {
            if (player->cheakSkillLocation(objectName(), data.toStringList()) && player->getMark("dangxianUsed") == 0)
                return QStringList(objectName());
        } else if (triggerEvent == EventPhaseEnd && player->getPhase() == Player::RoundStart) {
            return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        bool invoke = false;
        if (player->hasShownSkill(objectName())) {
            invoke = true;
            room->sendCompulsoryTriggerLog(player, objectName());
        } else
            invoke = player->askForSkillInvoke(this);

        if (invoke) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (triggerEvent == GeneralShowed) {
            room->addPlayerMark(player, "dangxianUsed");
            room->addPlayerMark(player, "@firstshow");
        } else if (triggerEvent == EventPhaseEnd) {
            player->insertPhase(Player::Play);
        }
        return false;
    }
};

class Huanshi : public TriggerSkill
{
public:
    Huanshi() : TriggerSkill("huanshi")
    {
        events << AskForRetrial;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        JudgeStruct *judge = data.value<JudgeStruct *>();
        if (!player->isFriendWith(judge->who)) return QStringList();
        if (player->isNude() && player->getHandPile().isEmpty()) return QStringList();
        return QStringList(objectName());
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        JudgeStruct *judge = data.value<JudgeStruct *>();

        QStringList prompt_list;
        prompt_list << "@huanshi-card" << judge->who->objectName()
            << objectName() << judge->reason << QString::number(judge->card->getEffectiveId());
        QString prompt = prompt_list.join(":");

        const Card *card = room->askForCard(player, "..", prompt, data, Card::MethodResponse, judge->who, true);

        if (card) {
            LogMessage log;
            log.type = "#InvokeSkill";
            log.from = player;
            log.arg = objectName();
            room->sendLog(log);

            LogMessage log2;
            log2.card_str = card->toString();
            log2.from = player;
            log2.type = QString("#%1_Resp").arg(card->getClassName());
            room->sendLog(log2);

            room->notifySkillInvoked(player, objectName());
            room->broadcastSkillInvoke(objectName(), player);

            int id = card->getEffectiveId();
            bool isHandcard = (room->getCardOwner(id) == player && room->getCardPlace(id) == Player::PlaceHand);

            CardMoveReason reason(CardMoveReason::S_REASON_RESPONSE, player->objectName(), objectName(), QString());

            room->moveCardTo(card, NULL, Player::PlaceTable, reason);

            CardResponseStruct resp(card, judge->who, false);
            resp.m_isHandcard = isHandcard;
            resp.m_data = data;
            QVariant _data = QVariant::fromValue(resp);
            room->getThread()->trigger(CardResponded, room, player, _data);

            QStringList card_list = player->tag["huanshi_cards"].toStringList();
            card_list.append(card->toString());
            player->tag["huanshi_cards"] = card_list;

            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        QStringList card_list = player->tag["huanshi_cards"].toStringList();

        if (card_list.isEmpty()) return false;

        QString card_str = card_list.takeLast();
        player->tag["huanshi_cards"] = card_list;

        const Card *card = Card::Parse(card_str);
        if (card) {
            JudgeStruct *judge = data.value<JudgeStruct *>();
            room->retrial(card, player, judge, objectName(), false);
            judge->updateResult();
        }
        return false;
    }
};

HongyuanCard::HongyuanCard()
{
    will_throw = false;
    target_fixed = true;
    handling_method = Card::MethodNone;
}

void HongyuanCard::extraCost(Room *room, const CardUseStruct &card_use) const
{
    room->showCard(card_use.from, subcards);
}

void HongyuanCard::use(Room *room, ServerPlayer *source, QList<ServerPlayer *> &) const
{
    QStringList hongyuan_ids;
    if (!source->property("view_as_transferable").isNull())
        hongyuan_ids = source->property("view_as_transferable").toString().split("+");
    foreach (int id, subcards) {
        hongyuan_ids << QString::number(id);
    }
    room->setPlayerProperty(source, "view_as_transferable", hongyuan_ids);
}

class HongyuanViewAsSkill : public OneCardViewAsSkill
{
public:
    HongyuanViewAsSkill() : OneCardViewAsSkill("hongyuan")
    {
        filter_pattern = ".|.|.|hand";
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return !player->hasUsed("HongyuanCard");
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        HongyuanCard *card = new HongyuanCard;
        card->addSubcard(originalCard);
        card->setSkillName(objectName());
        card->setShowSkill(objectName());
        return card;
    }
};

class Hongyuan : public TriggerSkill
{
public:
    Hongyuan() : TriggerSkill("hongyuan")
    {
        events << BeforeCardsMove << EventPhaseChanging << PreCardsMoveOneTime;
        view_as_skill = new HongyuanViewAsSkill;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == PreCardsMoveOneTime && !player->property("view_as_transferable").isNull()) {
            QStringList hongyuan_ids = player->property("view_as_transferable").toString().split("+");
            QStringList hongyuan_copy = hongyuan_ids;
            foreach (QString card_data, hongyuan_copy) {
                int id = card_data.toInt();
                if (room->getCardOwner(id) != player || room->getCardPlace(id) != Player::PlaceHand)
                    hongyuan_ids.removeOne(card_data);
            }
            if (hongyuan_ids.isEmpty())
                room->setPlayerProperty(player, "view_as_transferable", QVariant());
            else
                room->setPlayerProperty(player, "view_as_transferable", hongyuan_ids.join("+"));
        } else if (triggerEvent == EventPhaseChanging)
            room->setPlayerProperty(player, "view_as_transferable", QVariant());
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (triggerEvent == BeforeCardsMove && TriggerSkill::triggerable(player)) {
            QVariantList move_datas = data.toList();
            foreach (QVariant move_data, move_datas) {
                CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                if (move.to == player && move.to_place == Player::PlaceHand && move.reason.m_reason == CardMoveReason::S_REASON_DRAW
                        && move.reason.m_skillName == "transfer") {
                    QList<ServerPlayer *> all_players = room->getOtherPlayers(player);
                    foreach (ServerPlayer *p, all_players) {
                        if (player->isFriendWith(p))
                            return QStringList(objectName());
                    }
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QList<ServerPlayer *> to_choose, all_players = room->getOtherPlayers(player);
        foreach (ServerPlayer *p, all_players) {
            if (player->isFriendWith(p))
                to_choose << p;
        }
        if (to_choose.isEmpty()) return false;

        ServerPlayer *to = room->askForPlayerChosen(player, to_choose, objectName(), "hongyuan-invoke", true, true);
        if (to != NULL) {
            room->broadcastSkillInvoke(objectName(), player);

            QStringList target_list = player->tag["hongyuan_target"].toStringList();
            target_list.append(to->objectName());
            player->tag["hongyuan_target"] = target_list;
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        QStringList target_list = player->tag["hongyuan_target"].toStringList();
        QString target_name = target_list.takeLast();
        player->tag["hongyuan_target"] = target_list;

        ServerPlayer *to = room->findPlayerbyobjectName(target_name);

        if (to) {
            QVariantList move_datas = data.toList();
            QVariantList new_datas;
            foreach (QVariant move_data, move_datas) {
                CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                if (move.to == player && move.to_place == Player::PlaceHand && move.reason.m_reason == CardMoveReason::S_REASON_DRAW
                        && move.reason.m_skillName == "transfer") {
                    move.to = to;
                }
                new_datas << QVariant::fromValue(move);
            }
            data = QVariant::fromValue(new_datas);
        }
        return false;
    }
};

class Mingzhe : public TriggerSkill
{
public:
    Mingzhe() : TriggerSkill("mingzhe")
    {
        events  << CardsMoveOneTime << CardUsed << CardResponded;
        frequency = Frequent;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (!TriggerSkill::triggerable(player) || player->getPhase() != Player::NotActive) return QStringList();
        if (triggerEvent == CardUsed || triggerEvent == CardResponded) {
            const Card *cardstar = NULL;
            if (triggerEvent == CardUsed) {
                CardUseStruct use = data.value<CardUseStruct>();
                cardstar = use.card;
            } else {
                CardResponseStruct resp = data.value<CardResponseStruct>();
                cardstar = resp.m_card;
            }
            if (cardstar && cardstar->getTypeId() != Card::TypeSkill && cardstar->isRed())
                return QStringList(objectName());

        } else if (triggerEvent == CardsMoveOneTime) {
            QVariantList move_datas = data.toList();
            foreach (QVariant move_data, move_datas) {
                CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                if (move.from == player && move.from_places.contains(Player::PlaceEquip)) {
                    for (int i = 0; i < move.card_ids.length(); ++i) {
                        const Card *card = Card::Parse(move.cards.at(i));
                        if (card && card->isRed() && move.from_places.at(i) == Player::PlaceEquip) {
                            return QStringList(objectName());
                        }
                    }
                }
            }
        }

        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }

        return false;
    }

    virtual bool effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        player->drawCards(1, objectName());
        return false;
    }
};

class Danlao : public TriggerSkill
{
public:
    Danlao() : TriggerSkill("danlao")
    {
        events << TargetConfirmed;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card->getTypeId() == Card::TypeTrick && TriggerSkill::triggerable(player)) {
            bool can_trigger = false;
            foreach (ServerPlayer *p, use.to) {
                if (p->isAlive() && p != player) {
                    can_trigger = true;
                    break;
                }
            }
            if (can_trigger)
                return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this, data)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }

        return false;
    }

    virtual bool effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        player->drawCards(1, objectName());
        CardUseStruct use = data.value<CardUseStruct>();
        use.nullified_list << player->objectName();
        data = QVariant::fromValue(use);
        return false;
    }
};

class Jilei : public TriggerSkill
{
public:
    Jilei() : TriggerSkill("jilei")
    {
        events << Damaged << EventPhaseStart;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == EventPhaseStart && player->getPhase() == Player::NotActive) {
            QList<ServerPlayer *> alls = room->getAlivePlayers();
            foreach (ServerPlayer *p, alls) {
                room->setPlayerMark(p, "##jilei+BasicCard", 0);
                room->setPlayerMark(p, "##jilei+EquipCard", 0);
                room->setPlayerMark(p, "##jilei+TrickCard", 0);
            }
        }
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (triggerEvent == Damaged && TriggerSkill::triggerable(player)) {
            ServerPlayer *from = data.value<DamageStruct>().from;
            return (from && from->isAlive()) ? QStringList(objectName()) : QStringList();
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        ServerPlayer *from = data.value<DamageStruct>().from;
        if (from && from->isAlive() && player->askForSkillInvoke(this, QVariant::fromValue(from))) {
            room->broadcastSkillInvoke(objectName(), player);
            room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), from->objectName());
            return true;
        }

        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *yangxiu, QVariant &data, ServerPlayer *) const
    {
        DamageStruct damage = data.value<DamageStruct>();
        QString choice = room->askForChoice(yangxiu, objectName(), "BasicCard+EquipCard+TrickCard",
                                            data, "@jilei-choose::" + damage.from->objectName());

        LogMessage log;
        log.type = "#Jilei";
        log.from = damage.from;
        log.arg = choice;
        room->sendLog(log);

        QString _type = choice + "|.|.|hand"; // Handcards only
        room->setPlayerCardLimitation(damage.from, "use,response,discard", _type, true);

        room->addPlayerMark(damage.from, "##jilei+" + choice);
        return false;
    }
};

class Wanglie : public TriggerSkill
{
public:
    Wanglie() : TriggerSkill("wanglie")
    {
        events << CardUsed << EventPhaseChanging;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == EventPhaseChanging) {
            if (player->getMark("##wanglie") > 0) {
                int x = player->getMark("##wanglie");
                for (int i = 1; i <= x; i++)
                    room->removePlayerCardLimitation(player, "use", ".");
                room->setPlayerMark(player, "##wanglie", 0);
            }
        }
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (triggerEvent != CardUsed || !TriggerSkill::triggerable(player) || player->getPhase() != Player::Play) return QStringList();
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card && (use.card->isKindOf("Slash") || use.card->isNDTrick()))
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this, data)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }

        return false;
    }

    virtual bool effect(TriggerEvent , Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        use.disresponsive_list << "_ALL_PLAYERS";
        data = QVariant::fromValue(use);
        room->setPlayerCardLimitation(player, "use", ".", false);
        room->addPlayerMark(player, "##wanglie");
        return false;
    }
};

class WanglieTarget : public TargetModSkill
{
public:
    WanglieTarget() : TargetModSkill("#wanglie-target")
    {
        frequency = NotFrequent;
        pattern = "^SkillCard";
    }

    virtual int getDistanceLimit(const Player *from, const Card *, const Player *) const
    {
        if (from->hasShownSkill("wanglie") && from->getMark("GlobalPlayCardUsedTimes")==0)
            return 1000;
        else
            return 0;
    }
};

class YinbingX : public PhaseChangeSkill
{
public:
    YinbingX() : PhaseChangeSkill("yinbingx")
    {

    }

    virtual QStringList triggerable(TriggerEvent , Room *, ServerPlayer *player, QVariant &, ServerPlayer * &) const
    {
        if (PhaseChangeSkill::triggerable(player) && player->getPhase() == Player::Finish && !player->isNude())
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QList<int> ints = room->askForExchange(player, objectName(), 998, 0, "@yinbing-put", QString(), "^BasicCard");
        if (!ints.isEmpty()) {
            player->broadcastSkillInvoke(objectName());
            room->notifySkillInvoked(player, objectName());
            LogMessage log;
            log.from = player;
            log.type = "#InvokeSkill";
            log.arg = objectName();
            room->sendLog(log);
            player->addToPile("kerchief", ints, true);
            return true;
        }
        return false;
    }

    virtual bool onPhaseChange(ServerPlayer *) const
    {
        return false;
    }
};

class YinbingXCompulsory : public MasochismSkill
{
public:
    YinbingXCompulsory() : MasochismSkill("#yinbingx-compulsory")
    {
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (player == NULL || player->isDead() || !player->hasShownSkill("yinbingx")
                || player->getPile("kerchief").isEmpty()) return QStringList();
        DamageStruct damage = data.value<DamageStruct>();
        if (damage.card && (damage.card->isKindOf("Slash") || damage.card->isKindOf("Duel")))
            return QStringList(objectName());

        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        bool invoke = false;
        if (player->hasShownSkill("yinbingx")) {
            invoke = true;
            room->sendCompulsoryTriggerLog(player, "yinbingx");
        } else {

            invoke = player->askForSkillInvoke("yinbingx", data);
        }

        if (invoke) {
            room->broadcastSkillInvoke("yinbingx", player);
            return true;
        }
        return false;
    }

    virtual void onDamaged(ServerPlayer *player, const DamageStruct &) const
    {
        Room *room = player->getRoom();
        QList<int> ids = player->getPile("kerchief");
        room->fillAG(ids, player);
        int id = room->askForAG(player, ids, false, "yinbingx");
        room->clearAG(player);
        CardMoveReason reason(CardMoveReason::S_REASON_REMOVE_FROM_PILE, QString(), player->objectName(), "yinbingx", QString());
        room->throwCard(Sanguosha->getCard(id), reason, NULL);
    }
};

class Juedi : public PhaseChangeSkill
{
public:
    Juedi() : PhaseChangeSkill("juedi")
    {
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (PhaseChangeSkill::triggerable(player) && player->getPhase() == Player::Start
                && !player->getPile("kerchief").isEmpty())
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        bool invoke = false;
        if (player->hasShownSkill(objectName())) {
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

    bool onPhaseChange(ServerPlayer *target) const
    {
        Room *room = target->getRoom();
        QStringList choices;
        choices << "self";
        QList<ServerPlayer *> playerlist;
        foreach (ServerPlayer *p, room->getOtherPlayers(target)) {
            if (p->getHp() <= target->getHp())
                playerlist << p;
        }
        if (!playerlist.isEmpty())
            choices << "give";
        if (room->askForChoice(target, objectName(), choices.join("+"), QVariant(), QString(), "self+give") == "give") {
            ServerPlayer *to_give = room->askForPlayerChosen(target, playerlist, objectName(), "@juedi");
            int len = target->getPile("kerchief").length();
            DummyCard *dummy = new DummyCard(target->getPile("kerchief"));
            dummy->deleteLater();
            CardMoveReason reason(CardMoveReason::S_REASON_GIVE, target->objectName(), to_give->objectName(), objectName(), QString());
            room->obtainCard(to_give, dummy, reason);
            RecoverStruct recover;
            recover.who = target;
            room->recover(to_give, recover);
            room->drawCards(to_give, len, objectName());
        } else {
            target->clearOnePrivatePile("kerchief");
            target->fillHandCards(target->getMaxHp(), objectName());
        }
        return false;
    }
};

class Moukui : public TriggerSkill
{
public:
    Moukui() : TriggerSkill("moukui")
    {
        events << TargetChosen;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        if (TriggerSkill::triggerable(player) && use.card != NULL && use.card->isKindOf("Slash")) {
            ServerPlayer *target = use.to.at(use.index);
            if (target)
                return QStringList(objectName() + "->" + target->objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *skill_target, QVariant &, ServerPlayer *player) const
    {
        if (player->askForSkillInvoke(this, QVariant::fromValue(skill_target))) {
            room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), skill_target->objectName());
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *target, QVariant &data, ServerPlayer *player) const
    {
        QStringList choices;
        choices << "draw";
        if (player->canDiscard(target, "he"))
            choices << "discard";
        QString choice = room->askForChoice(player, objectName(), choices.join("+"),
                QVariant::fromValue(target), "@moukui-choose::" + target->objectName(), "draw+discard");
        if (choice == "draw")
            player->drawCards(1, objectName());
        else if (choice == "discard") {
            room->setTag("MoukuiDiscard", data);
            int disc = room->askForCardChosen(player, target, "he", objectName(), false, Card::MethodDiscard);
            room->removeTag("MoukuiDiscard");
            room->throwCard(disc, target, player);
        }

        CardUseStruct use = data.value<CardUseStruct>();

        QStringList moukuiRecord = use.card->tag["moukuiRecord"].toStringList();
        moukuiRecord << player->objectName() + ":" + target->objectName();
        use.card->setTag("moukuiRecord", moukuiRecord);

        return false;
    }

};

class MoukuiEffect : public TriggerSkill
{
public:
    MoukuiEffect() : TriggerSkill("#moukui-effect")
    {
        events << SlashMissed;
        frequency = Compulsory;
    }

    virtual TriggerList triggerable(TriggerEvent , Room *room, ServerPlayer *, QVariant &data) const
    {
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        if (effect.slash && effect.to && effect.to->isAlive()) {
            TriggerList skill_list;
            QStringList moukuiRecord = effect.slash->tag["moukuiRecord"].toStringList();
            foreach (QString record, moukuiRecord) {
                QStringList names = record.split(":");
                if (names.length() == 2 && names.last() == effect.to->objectName()) {
                    ServerPlayer *fuwan = room->findPlayerbyobjectName(names.first());
                    if (fuwan && fuwan->isAlive() && effect.to->canDiscard(fuwan, "he")) {
                        skill_list.insert(fuwan, QStringList(objectName()));
                    }
                }
            }
            return skill_list;
        }
        return TriggerList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *player) const
    {
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        LogMessage log;
        log.type = "#MoukuiDiscard";
        log.from = player;
        log.to << effect.to;
        log.arg = "moukui";
        room->sendLog(log);
        room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), effect.to->objectName());
        return true;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *player) const
    {
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        if (effect.to->canDiscard(player, "he")) {
            int disc = room->askForCardChosen(effect.to, player, "he", "moukui", false, Card::MethodDiscard);
            room->throwCard(disc, player, effect.to);
        }
        return false;
    }

};

class ZhenxiTrick : public OneCardViewAsSkill
{
public:
    ZhenxiTrick() : OneCardViewAsSkill("zhenxi_trick")
    {
        filter_pattern = "BasicCard,EquipCard|diamond,club";
        response_or_use = true;
        response_pattern = "@@zhenxi_trick";
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        if (originalCard->getSuit() == Card::Diamond) {
            Indulgence *indulgence = new Indulgence(originalCard->getSuit(), originalCard->getNumber());
            indulgence->addSubcard(originalCard->getId());
            indulgence->setSkillName("_zhenxi");
            return indulgence;
        } else {
            SupplyShortage *shortage = new SupplyShortage(originalCard->getSuit(), originalCard->getNumber());
            shortage->addSubcard(originalCard->getId());
            shortage->setSkillName("_zhenxi");
            return shortage;
        }
        return NULL;
    }
};

class Zhenxi : public TriggerSkill
{
public:
    Zhenxi() : TriggerSkill("zhenxi")
    {
        events << TargetChosen;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        if (TriggerSkill::triggerable(player) && use.card != NULL && use.card->isKindOf("Slash")) {
            ServerPlayer *target = use.to.at(use.index);
            if (target)
                return QStringList(objectName() + "->" + target->objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *skill_target, QVariant &, ServerPlayer *player) const
    {
        if (player->askForSkillInvoke(this, QVariant::fromValue(skill_target))) {
            room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), skill_target->objectName());
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *target, QVariant &data, ServerPlayer *player) const
    {
        QStringList choices;
        choices << "usecard";
        if (player->canDiscard(target, "he"))
            choices << "discard";
        QString choice = room->askForChoice(player, objectName(), choices.join("+"),
                QVariant::fromValue(target), "@zhenxi-choose::" + target->objectName(), "usecard+discard");
        if (choice == "usecard") {
            room->setPlayerProperty(player, "zhenxi_target", target->objectName());
            if (room->askForUseCard(player, "@@zhenxi_trick", "@zhenxi-trick::" + target->objectName())) {
                if (player->hasShownAllGenerals() && !target->hasShownAllGenerals() && player->canDiscard(target, "he") &&
                        room->askForChoice(player, "zhenxi_discard", "yes+no", data, "@zhenxi-discard::" + target->objectName()) == "yes") {
                    room->setTag("ZhenxiDiscard", data);
                    int disc = room->askForCardChosen(player, target, "he", objectName(), false, Card::MethodDiscard);
                    room->removeTag("ZhenxiDiscard");
                    room->throwCard(disc, target, player);
                }
            }
            room->setPlayerProperty(player, "zhenxi_target", QVariant());
        } else if (choice == "discard") {
            room->setTag("ZhenxiDiscard", data);
            int disc = room->askForCardChosen(player, target, "he", objectName(), false, Card::MethodDiscard);
            room->removeTag("ZhenxiDiscard");
            room->throwCard(disc, target, player);
            if (player->hasShownAllGenerals() && !target->hasShownAllGenerals()) {
                room->setPlayerProperty(player, "zhenxi_target", target->objectName());
                room->askForUseCard(player, "@@zhenxi_trick", "@zhenxi-trick::" + target->objectName());
                room->setPlayerProperty(player, "zhenxi_target", QVariant());
            }
        }
        return false;
    }

    virtual int getEffectIndex(const ServerPlayer *, const Card *card) const
    {
        return (card->isKindOf("Indulgence") || card->isKindOf("SupplyShortage")) ? -2 : -1;
    }
};

class ZhenxiProhibit : public ProhibitSkill
{
public:
    ZhenxiProhibit() : ProhibitSkill("#zhenxi-prohibit")
    {
    }

    virtual bool isProhibited(const Player *from, const Player *to, const Card *card, const QList<const Player *> &) const
    {
        if (from && to && card->getSkillName(true) == "zhenxi")
            return from->property("zhenxi_target").toString() != to->objectName();
        return false;
    }
};

class ZhenxiTargetMod : public TargetModSkill
{
public:
    ZhenxiTargetMod() : TargetModSkill("#zhenxi-target")
    {
        pattern = "^SkillCard";
    }

    virtual int getDistanceLimit(const Player *from, const Card *card, const Player *) const
    {
        if (!Sanguosha->matchExpPattern(pattern, from, card))
            return 0;

        if (card->getSkillName(true) == "zhenxi")
            return 1000;
        else
            return 0;
    }
};

JiansuCard::JiansuCard()
{
    will_throw = true;
}

bool JiansuCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *) const
{
    return targets.isEmpty() && to_select->canRecover() && to_select->getHp() <= subcardsLength();
}

void JiansuCard::onEffect(const CardEffectStruct &effect) const
{
    QVariantList effect_list = effect.from->tag["jianshuTag"].toList();
    effect_list << QVariant::fromValue(effect);
    effect.from->tag["jianshuTag"] = effect_list;
}

class JiansuViewAsSkill : public ViewAsSkill
{
public:
    JiansuViewAsSkill() : ViewAsSkill("jiansu")
    {
        response_pattern = "@@jiansu";
    }

    virtual bool viewFilter(const QList<const Card *> &, const Card *to_select) const
    {
        QStringList jiansu_ids = Self->property("jiansu_record").toString().split("+");
        return !Self->isJilei(to_select) && jiansu_ids.contains(QString::number(to_select->getEffectiveId()));
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (cards.isEmpty())
            return NULL;

        JiansuCard *jiansu_card = new JiansuCard;
        jiansu_card->addSubcards(cards);
        return jiansu_card;
    }
};

class Jiansu : public TriggerSkill
{
public:
    Jiansu() : TriggerSkill("jiansu")
    {
        events << CardsMoveOneTime << PreCardsMoveOneTime << EventPhaseStart;
        relate_to_place = "deputy";
        view_as_skill = new JiansuViewAsSkill;
    }

    virtual bool canPreshow() const
    {
        return true;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == PreCardsMoveOneTime && !player->property("jiansu_record").isNull()) {
            QStringList jiansu_ids = player->property("jiansu_record").toString().split("+");
            QStringList jiansu_copy = jiansu_ids;
            foreach (QString card_data, jiansu_copy) {
                int id = card_data.toInt();
                if (room->getCardOwner(id) != player || room->getCardPlace(id) != Player::PlaceHand)
                    jiansu_ids.removeOne(card_data);
            }
            if (jiansu_ids.isEmpty())
                room->setPlayerProperty(player, "jiansu_record", QVariant());
            else
                room->setPlayerProperty(player, "jiansu_record", jiansu_ids.join("+"));
            room->setPlayerMark(player, "#money", jiansu_ids.length());
        }
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        if (triggerEvent == CardsMoveOneTime && player->getPhase() == Player::NotActive) {
            QVariantList move_datas = data.toList();
            foreach(QVariant move_data, move_datas) {
                CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                if (move.to == player && move.to_place == Player::PlaceHand) {
                    for (int i = 0; i < move.card_ids.length(); ++i) {
                        int id = move.card_ids.at(i);
                        if (room->getCardOwner(id) == player && room->getCardPlace(id) == Player::PlaceHand) {
                            return QStringList(objectName());
                        }
                    }
                }
            }
        } else if (triggerEvent == EventPhaseStart && player->getPhase() == Player::Play && player->getMark("#money") > 0) {
            return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (triggerEvent == CardsMoveOneTime) {
            if (player->askForSkillInvoke(this, data)) {
                room->broadcastSkillInvoke(objectName(), player);
                return true;
            }
        } else if (triggerEvent == EventPhaseStart) {
            return room->askForUseCard(player, "@@jiansu", "@jiansu-card", -1, Card::MethodDiscard);
        }
        return false;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (triggerEvent == CardsMoveOneTime) {
            QStringList jiansu_ids;

            if (!player->property("jiansu_record").isNull())
                jiansu_ids = player->property("jiansu_record").toString().split("+");

            QVariantList move_datas = data.toList();
            QList<int> card_ids;
            foreach(QVariant move_data, move_datas) {
                CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                if (move.to == player && move.to_place == Player::PlaceHand) {
                    for (int i = 0; i < move.card_ids.length(); ++i) {
                        int id = move.card_ids.at(i);
                        if (room->getCardOwner(id) == player && room->getCardPlace(id) == Player::PlaceHand) {
                            jiansu_ids << QString::number(id);
                            card_ids << id;
                        }
                    }
                }
            }
            room->showCard(player, card_ids);
            room->setPlayerProperty(player, "jiansu_record", jiansu_ids.join("+"));
            room->setPlayerMark(player, "#money", jiansu_ids.length());
        } else if (triggerEvent == EventPhaseStart) {
            QVariantList data_list = player->tag["jianshuTag"].toList();
            if (data_list.isEmpty()) return false;
            QVariant jianshu_data = data_list.takeLast();
            player->tag["jianshuTag"] = data_list;
            CardEffectStruct effect = jianshu_data.value<CardEffectStruct>();
            ServerPlayer *target = effect.to;
            if (target->isAlive()) {
                RecoverStruct recover;
                recover.who = effect.from;
                room->recover(target, recover);
            }
        }
        return false;
    }
};

class Yaowu : public TriggerSkill
{
public:
    Yaowu() : TriggerSkill("yaowu")
    {
        events << Damage;
        frequency = Limited;
        limit_mark = "@showoff";
    }

    virtual QStringList triggerable(TriggerEvent , Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (TriggerSkill::triggerable(player) && !player->hasShownSkill(objectName()) && player->getMark(limit_mark) > 0)
            return QStringList(objectName());

        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this)) {
            room->broadcastSkillInvoke(objectName(), player);
            room->doSuperLightbox("huaxiong", objectName());
            room->removePlayerMark(player, limit_mark);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->setPlayerProperty(player, "maxhp", player->getMaxHp() + 2);

        LogMessage log;
        log.type = "#GainMaxHp";
        log.from = player;
        log.arg = QString::number(2);
        room->sendLog(log);

        RecoverStruct recover;
        recover.recover = 2;
        recover.who = player;
        room->recover(player, recover);

        room->addPlayerMark(player, "##yaowu");

        return false;
    }
};

class YaowuDeath : public TriggerSkill
{
public:
    YaowuDeath() : TriggerSkill("#yaowu-death")
    {
        events << DeathFinished;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent , Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        DeathStruct death = data.value<DeathStruct>();
        ServerPlayer *dead = death.who;
        if (dead && dead->getMark("##yaowu") > 0 && player->isAlive() && player->isFriendWith(dead))
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
    {
        return true;
    }

    virtual bool effect(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->loseHp(player);
        return false;
    }
};

class Shiyong : public TriggerSkill
{
public:
    Shiyong() : TriggerSkill("shiyong")
    {
        events << DamageInflicted;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent , Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        DamageStruct damage = data.value<DamageStruct>();
        if (damage.card) {
            if (player->getMark("##yaowu") > 0) {
                if (!damage.card->isBlack() && damage.from && damage.from->isAlive())
                    return QStringList(objectName());
            } else if (!damage.card->isRed())
                return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        bool invoke = false;
        if (player->hasShownSkill(objectName())) {
            invoke = true;
            room->sendCompulsoryTriggerLog(player, objectName());
        } else
            invoke = player->askForSkillInvoke(this);

        if (invoke) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent , Room *, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (player->getMark("##yaowu") > 0) {
            DamageStruct damage = data.value<DamageStruct>();
            if (damage.from && damage.from->isAlive())
                damage.from->drawCards(1, objectName());
        } else
            player->drawCards(1, objectName());
        return false;
    }
};

class Zhuidu : public TriggerSkill
{
public:
    Zhuidu() : TriggerSkill("zhuidu")
    {
        events << DamageCaused << EventPhaseChanging;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if (triggerEvent == EventPhaseChanging && data.value<PhaseChangeStruct>().from == Player::Play) {
            room->setPlayerFlag(player, "-zhuiduUsed");
        }
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (triggerEvent == DamageCaused && TriggerSkill::triggerable(player)
                && player->getPhase() == Player::Play && !player->hasFlag("zhuiduUsed")) {
            DamageStruct damage = data.value<DamageStruct>();
            if (damage.to && damage.to->isAlive())
                return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        DamageStruct damage = data.value<DamageStruct>();
        bool invoke = player->askForSkillInvoke(this, QVariant::fromValue(damage.to));
        if (invoke) {
            room->setPlayerFlag(player, "zhuiduUsed");
            room->broadcastSkillInvoke(objectName(), player);

            return true;
        }

        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        DamageStruct damage = data.value<DamageStruct>();
        ServerPlayer *target = damage.to;

        if (target->isDead()) return false;
        bool adddamage = false, throwallequips = false;


        if (target->isFemale() && room->askForDiscard(player, "zhuidu_discard", 1, 1, true, true, "@zhuidu-both::" + target->objectName())) {
            adddamage = true;
            throwallequips = true;
        } else {
            if (!target->getEquips().isEmpty()
                && room->askForChoice(target, "zhuidu_choice", "throw+damage", data) == "throw")
                throwallequips = true;
            else
                adddamage = true;
        }

        if (throwallequips)
            target->throwAllEquips();

        if (adddamage) {
            damage.damage++;
            data = QVariant::fromValue(damage);
        }

        return false;
    }
};

class Shigong : public TriggerSkill
{
public:
    Shigong() : TriggerSkill("shigong")
    {
        events << Dying;
        frequency = Limited;
        limit_mark = "@handover";
    }

    virtual QStringList triggerable(TriggerEvent , Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (TriggerSkill::triggerable(player) && player->getPhase() == Player::NotActive) {
            DyingStruct dying = data.value<DyingStruct>();
            if (dying.who == player && player->getHp() < 1 && player->getGeneral2()
                    && !player->getActualGeneral2Name().contains("sujiang"))
                return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this)) {
            room->broadcastSkillInvoke(objectName(), player);
            room->doSuperLightbox("liufuren", objectName());
            room->setPlayerMark(player, limit_mark, 0);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent , Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        QString general_name = player->getActualGeneral2Name();
        player->removeGeneral(false);
        ServerPlayer *current = room->getCurrent();
        if (current && current->isAlive()) {
            int x = 1;
            QStringList skill_names;
            QList<const Skill *> skills = Sanguosha->getGeneral(general_name)->getVisibleSkillList();
            foreach (const Skill *skill, skills) {
                if (isNormalSkill(skill))
                    skill_names << skill->objectName();

            }

            if (!skill_names.isEmpty()) {
                skill_names << "cancel";

                QString skill_name = room->askForChoice(current, "shigong_skill", skill_names.join("+"), data, "@shigong-choose:::"+general_name);

                if (skill_name != "cancel") {
                    room->acquireSkill(current, skill_name, true, false);
                    x = player->getMaxHp();
                }

            }

            if (player->isAlive()) {
                RecoverStruct recover;
                recover.recover = x - player->getHp();
                room->recover(player, recover);
            }
        }

        return false;
    }

private:
    static bool isNormalSkill(const Skill *skill)
    {
        if (skill->isAttachedLordSkill() || skill->isLordSkill()) return false;
        if (!skill->getRelatePlace().isEmpty() || skill->inherits("BattleArraySkill")) return false;
        return (skill->getFrequency() == Skill::Frequent || skill->getFrequency() == Skill::NotFrequent);
    }
};

class Tanfeng : public PhaseChangeSkill
{
public:
    Tanfeng() : PhaseChangeSkill("tanfeng")
    {

    }

    virtual QStringList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (!PhaseChangeSkill::triggerable(player)) return QStringList();
        if (player->getPhase() == Player::Start) {
            foreach (ServerPlayer *p, room->getAlivePlayers()) {
                if (!player->willBeFriendWith(p) && player->canDiscard(p, "hej")) {
                    return QStringList(objectName());
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QList<ServerPlayer *> to_choose, all_players = room->getAlivePlayers();
        foreach (ServerPlayer *p, all_players) {
            if (!player->willBeFriendWith(p) && player->canDiscard(p, "hej"))
                to_choose << p;
        }
        if (to_choose.isEmpty()) return false;

        ServerPlayer *to = room->askForPlayerChosen(player, to_choose, objectName(), "@tanfeng-target", true, true);
        if (to != NULL) {
            room->broadcastSkillInvoke(objectName(), player);
            QStringList target_list = player->tag["tanfeng_target"].toStringList();
            target_list.append(to->objectName());
            player->tag["tanfeng_target"] = target_list;
            return true;
        }
        return false;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const
    {
        Room *room = player->getRoom();
        QStringList target_list = player->tag["tanfeng_target"].toStringList();
        QString target_name = target_list.takeLast();
        player->tag["tanfeng_target"] = target_list;
        ServerPlayer *to = room->findPlayerbyobjectName(target_name);

        if (to && player->canDiscard(to, "hej")) {
            room->throwCard(room->askForCardChosen(player, to, "hej", objectName(), false, Card::MethodDiscard), to, player);

            if (player->isAlive() && to->isAlive()) {

                QStringList phase_strings;
                phase_strings << "judge" << "draw" << "play" << "discard" << "finish" << "cancel";

                QString choice = room->askForChoice(to, objectName(), phase_strings.join("+"),
                                                    QVariant(), "@tanfeng-choose:" + player->objectName());

                if (choice != "cancel") {
                    room->damage(DamageStruct(objectName(), player, to, 1, DamageStruct::Fire));
                    player->skip((Player::Phase)(phase_strings.indexOf(choice)+2));
                }
            }
        }
        return false;
    }
};

class Jinwu : public PhaseChangeSkill
{
public:
    Jinwu() : PhaseChangeSkill("jinwu")
    {

    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (!PhaseChangeSkill::triggerable(player)) return QStringList();
        if (player->getPhase() == Player::Play) return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const
    {
        Room *room = player->getRoom();
        if (player->askCommandto(objectName(), player) && player->isAlive()) {

            QList<ServerPlayer *> targets, allplayers = room->getAlivePlayers();
            foreach (ServerPlayer *p, allplayers) {
                if (player->canSlash(p))
                    targets << p;
            }
            if (!targets.isEmpty()) {
                ServerPlayer *target = room->askForPlayerChosen(player, targets, "jinwu-slash", "@jinwu-slash");
                if (target) {
                    Slash *slash = new Slash(Card::NoSuit, 0);
                    slash->setSkillName("_jinwu");
                    room->useCard(CardUseStruct(slash, player, target), false);
                }
            }
        }
        else
            room->setPlayerFlag(player, "Global_PlayPhaseTerminated");
        return false;
    }

    virtual int getEffectIndex(const ServerPlayer *, const Card *) const
    {
        return 0;
    }
};


class Zhuke : public TriggerSkill
{
public:
    Zhuke() : TriggerSkill("zhuke")
    {
        events << CommandVerifying << TurnedOver << ChainStateChanged;
        relate_to_place = "head";
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (TriggerSkill::triggerable(player)) {
            if ((triggerEvent == TurnedOver && !player->faceUp()) || (triggerEvent == ChainStateChanged && player->isChained())) {
                return QStringList(objectName());
            } else if (triggerEvent == CommandVerifying) {
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (triggerEvent == CommandVerifying) {

            player->tag["ZhukeCommanddata"] = data;
            bool invoke = player->askForSkillInvoke(this);
            player->tag.remove("ZhukeCommanddata");

            if (invoke) {
                room->broadcastSkillInvoke(objectName(), player);
                return true;
            }
        } else if (triggerEvent == TurnedOver || triggerEvent == ChainStateChanged) {
            QList<ServerPlayer *> to_choose, all_players = room->getAlivePlayers();
            foreach (ServerPlayer *p, all_players) {
                if (player->isFriendWith(p) && p->canRecover())
                    to_choose << p;
            }
            if (to_choose.isEmpty()) return false;

            ServerPlayer *to = room->askForPlayerChosen(player, to_choose, objectName(), "zhuke-invoke", true, true);
            if (to != NULL) {
                room->broadcastSkillInvoke(objectName(), player);

                QStringList target_list = player->tag["zhuke_target"].toStringList();
                target_list.append(to->objectName());
                player->tag["zhuke_target"] = target_list;
                return true;
            }
        }
        return false;
    }


    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *source, QVariant &data, ServerPlayer *) const
    {
        if (triggerEvent == CommandVerifying) {
            QStringList list = data.toString().split(":");

            source->tag["ZhukeCommanddata"] = data;
            int index = source->startCommand(objectName());
            source->tag.remove("ZhukeCommanddata");

            QStringList allcommands;
            allcommands << "command1" << "command2" << "command3" << "command4" << "command5" << "command6";
            list[1] = allcommands.at(index);
            data = list.join(":");

        } else if (triggerEvent == TurnedOver || triggerEvent == ChainStateChanged) {
            QStringList target_list = source->tag["zhuke_target"].toStringList();
            QString target_name = target_list.takeLast();
            source->tag["zhuke_target"] = target_list;

            ServerPlayer *to = room->findPlayerbyobjectName(target_name);

            if (to) {
                RecoverStruct rec;
                rec.who = source;
                room->recover(to, rec);
            }
        }

        return false;
    }
};

class Quanjia : public TriggerSkill
{
public:
    Quanjia() : TriggerSkill("quanjia")
    {
        relate_to_place = "deputy";
    }

    virtual bool canPreshow() const
    {
        return false;
    }

    virtual QStringList triggerable(TriggerEvent , Room *, ServerPlayer *, QVariant &, ServerPlayer* &) const
    {
        return QStringList();
    }
};

class QuanjiaCompulsory : public TriggerSkill
{
public:
    QuanjiaCompulsory() : TriggerSkill("#quanjia-compulsory")
    {
        events << GeneralShowed;
        frequency = Compulsory;
        relate_to_place = "deputy";
    }

    virtual QStringList triggerable(TriggerEvent , Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (player->cheakSkillLocation("quanjia", data) && player->getMark("quanjiaUsed") == 0)
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->sendCompulsoryTriggerLog(player, "quanjia");
        room->broadcastSkillInvoke("quanjia", player);
        room->addPlayerMark(player, "quanjiaUsed");
        return true;
    }

    virtual bool effect(TriggerEvent , Room *room, ServerPlayer *source, QVariant &, ServerPlayer *) const
    {
        QList<ServerPlayer *> alls = room->getAlivePlayers();
        room->sortByActionOrder(alls);
        foreach(ServerPlayer *anjiang, alls) {
            if (source->getRole().startsWith("careerist")) break;
            if (anjiang->hasShownOneGeneral()) continue;

            QString kingdom = source->getKingdom();

            bool can_show = false, can_only_dupty = false;

            if (anjiang->getKingdom() == kingdom) {
                if (anjiang->getActualGeneral1()->getKingdom() != "careerist")
                    can_show = true;
                can_only_dupty = true;
            }

            room->setTag("GlobalQuanjiaShow", true);
            anjiang->askForGeneralShow("quanjia", can_show, can_only_dupty, can_show, true);
            room->setTag("GlobalQuanjiaShow", false);
        }
        QList<ServerPlayer *> to_draw, allplayers = room->getAlivePlayers();
        foreach (ServerPlayer *p, allplayers) {
            if (p->isFriendWith(source))
                to_draw << p;
        }
        room->sortByActionOrder(to_draw);
        foreach (ServerPlayer *p, to_draw) {
            if (p->isAlive())
                p->drawCards(1, "quanjia");
        }
        foreach (ServerPlayer *p, room->getAlivePlayers()) {
            bool head = (p->hasShownGeneral1() && p->getGeneral()->hasSkill("rende"));
            if (head || (p->hasShownGeneral2() && p->getGeneral2()->hasSkill("rende"))) {
                room->addPlayerMark(p, "##quanjia");
                room->acquireSkill(p, "zhangwu", true, head);
                room->acquireSkill(p, "shouyue", true, head);
                room->sendCompulsoryTriggerLog(p, "shouyue");
                room->broadcastSkillInvoke("shouyue", p);
            }
        }
        return false;
    }
};

class Tunchu : public DrawCardsSkill
{
public:
    Tunchu() : DrawCardsSkill("tunchu")
    {

    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer * &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        return QStringList(objectName());
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual int getDrawNum(ServerPlayer *player, int n) const
    {
        Room *room = player->getRoom();
        room->setPlayerCardLimitation(player, "use", "Slash", true);
        room->addPlayerMark(player, "##tunchu");
        return n + 2;
    }
};

class TunchuEffect : public TriggerSkill
{
public:
    TunchuEffect() : TriggerSkill("#tunchu-effect")
    {
        events << EventPhaseEnd << EventPhaseStart;
        frequency = Compulsory;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == EventPhaseStart && player->getPhase() == Player::NotActive)
            room->setPlayerMark(player, "##tunchu", 0);
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (triggerEvent == EventPhaseEnd && player->getPhase() == Player::Draw
                && player->getMark("##tunchu") > 0 && !player->isKongcheng())
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
    {
        return true;
    }

    virtual bool effect(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->isAlive() && !player->isKongcheng()) {
            QList<int> ints = room->askForExchange(player, "tunchu_push", 2, 1, "@tunchu-push", "", ".|.|.|hand");
            player->addToPile("food", ints);
        }
        return false;
    }
};

class Shuliang : public TriggerSkill
{
public:
    Shuliang() : TriggerSkill("shuliang")
    {
        events << EventPhaseStart;
    }

    virtual TriggerList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        TriggerList skill_list;
        if (player == NULL || player->isDead() || player->getPhase() != Player::Finish) return skill_list;
        QList<ServerPlayer *> owners = room->findPlayersBySkillName(objectName());
        foreach (ServerPlayer *ask_who, owners) {
            if (!ask_who->getPile("food").isEmpty() && ask_who->isFriendWith(player)
                    && ask_who->distanceTo(player) <= ask_who->getPile("food").length())
                skill_list.insert(ask_who, QStringList(objectName()));
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        QList<int> ints = room->askForExchange(ask_who, objectName(), 1, 0, "@shuliang:" + player->objectName(), "food");
        if (!ints.isEmpty()) {
            LogMessage log;
            log.type = "#InvokeSkill";
            log.from = ask_who;
            log.arg = objectName();
            room->sendLog(log);
            room->notifySkillInvoked(ask_who, objectName());
            room->broadcastSkillInvoke(objectName(), ask_who);
            room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, ask_who->objectName(), player->objectName());
            CardMoveReason reason(CardMoveReason::S_REASON_REMOVE_FROM_PILE, QString(), ask_who->objectName(), objectName(), QString());
            room->throwCard(Sanguosha->getCard(ints.first()), reason, NULL);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        player->drawCards(2, objectName());
        return false;
    }
};

class Dujin : public DrawCardsSkill
{
public:
    Dujin() : DrawCardsSkill("dujin")
    {

    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer * &) const
    {
        if (!TriggerSkill::triggerable(player) || !player->hasEquip()) return QStringList();
        return QStringList(objectName());
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual int getDrawNum(ServerPlayer *player, int n) const
    {
        return n + player->getEquips().length()/2 + player->getEquips().length()%2;
    }
};

class DujinCompulsory : public TriggerSkill
{
public:
    DujinCompulsory() : TriggerSkill("#dujin-compulsory")
    {
        events << GeneralShowed;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent , Room *room, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (player->cheakSkillLocation("dujin", data) && player->getMark("dujinUsed") == 0) {
            QList<ServerPlayer *> all_players = room->getAllPlayers(true);

            foreach (ServerPlayer *p, all_players) {
                if (p != player && p->isFriendWith(player))
                    return QStringList();
            }

            return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->sendCompulsoryTriggerLog(player, "dujin");
        room->broadcastSkillInvoke("dujin", player);
        room->addPlayerMark(player, "dujinUsed");
        return true;
    }

    virtual bool effect(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->addPlayerMark(player, "@firstshow");
        return false;
    }
};

class Kenshang : public ViewAsSkill
{
public:
    Kenshang() : ViewAsSkill("kenshang")
    {
        response_or_use = true;
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return Slash::IsAvailable(player);
    }

    virtual bool isEnabledAtResponse(const Player *, const QString &pattern) const
    {
        return Sanguosha->getCurrentCardUseReason() == CardUseStruct::CARD_USE_REASON_RESPONSE_USE && pattern == "slash";
    }

    virtual bool viewFilter(const QList<const Card *> &selected, const Card *to_select) const
    {
        Slash *slash = new Slash(Card::SuitToBeDecided, -1);
        slash->addSubcards(selected);
        slash->addSubcard(to_select);
        slash->deleteLater();
        return slash->isAvailable(Self);
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (cards.isEmpty()) return NULL;
        Card *slash = new Slash(Card::SuitToBeDecided, -1);
        slash->addSubcards(cards);
        slash->setSkillName(objectName());
        slash->setShowSkill(objectName());
        return slash;
    }
};

class KenshangEffect : public TriggerSkill
{
public:
    KenshangEffect() : TriggerSkill("#kenshang-effect")
    {
        events << TargetSelected << CardFinished;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card != NULL && use.card->isKindOf("Slash") && use.card->getSkillName() == "kenshang") {
            if (triggerEvent == TargetSelected) {
                QList<ServerPlayer *> targets = room->getUseExtraTargets(use, false);
                foreach (ServerPlayer *p, targets) {
                    if (!player->inMyAttackRange(p))
                        return QStringList(objectName());
                }

                bool cheak1 = false, cheak2 = false;
                foreach (ServerPlayer *p, use.to) {
                    if (player->inMyAttackRange(p))
                        cheak1 = true;
                    else
                        cheak2 = true;
                }
                if (cheak1 && cheak2)
                    return QStringList(objectName());

            } else if (triggerEvent == CardFinished)
                return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->sendSkillEffectTriggerLog(player, "kenshang");
        return true;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        if (triggerEvent == TargetSelected && player->askForSkillInvoke("_kenshang", "prompt")) {
            QList<ServerPlayer *> targets = room->getUseExtraTargets(use, false);
            foreach (ServerPlayer *p, targets) {
                if (!player->inMyAttackRange(p))
                    use.to.append(p);
            }
            QList<ServerPlayer *> all_players = room->getAlivePlayers();
            foreach (ServerPlayer *p, all_players) {
                if (use.to.contains(p) && player->inMyAttackRange(p))
                    room->cancelTarget(use, p);
            }
            LogMessage log;
            log.type = "#KenshangTarget";
            log.from = player;
            log.to = use.to;
            room->sendLog(log);
            room->sortByActionOrder(use.to);
            foreach (ServerPlayer *p, use.to)
                room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), p->objectName());
            data = QVariant::fromValue(use);

        } if (triggerEvent == CardFinished) {
            int damage_point = use.card->tag["GlobalCardDamagePoint"].toInt();
            if (damage_point < use.card->subcardsLength())
                player->drawCards(damage_point, "kenshang");
            else {
                QStringList limited_skills;
                QList<const Skill *> skills = player->getVisibleSkillList();
                foreach (const Skill *skill, skills) {
                    if ((skill->objectName() == "kenshang" || skill->objectName().startsWith("mashu"))) {
                        if (player->ownHeadSkill(skill) && !player->hasShownGeneral1())
                            continue;
                        if (player->ownDeputySkill(skill) && !player->hasShownGeneral2())
                            continue;
                        limited_skills.append(skill->objectName());
                    }
                }
                if (!limited_skills.isEmpty()) {
                    QString skill_name = room->askForChoice(player, "kenshang", limited_skills.join("+"), QVariant(), "@kenshang-choose");
                    room->detachSkillFromPlayer(player, skill_name, false, false, player->inHeadSkills(skill_name));
                }
            }
        }
        return false;
    }
};

class XiaoqiVS : public ZeroCardViewAsSkill
{
public:
    XiaoqiVS() : ZeroCardViewAsSkill("xiaoqi")
    {
        response_or_use = true;
    }

    virtual const Card *viewAs() const
    {
        Slash *slash = new Slash(Card::NoSuit, 0);
        slash->setSkillName(objectName());
        return slash;
    }

    virtual bool isEnabledAtPlay(const Player *) const
    {
        return false;
    }

    virtual bool isEnabledAtResponse(const Player *player, const QString &pattern) const
    {
        return pattern == "slash" && player->hasFlag("xiaoqi_duel") && player->hasFlag("xiaoqi_slash");
    }
};

class Xiaoqi : public TriggerSkill
{
public:
    Xiaoqi() : TriggerSkill("xiaoqi")
    {
        events << CardUsed << CardResponded << CardFinished << CardAsked;
        view_as_skill = new XiaoqiVS;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if (player) {
            if (triggerEvent == CardFinished) {
                const Card *card = data.value<CardUseStruct>().card;
                if (card && card->objectName() == "duel" && card->getSkillName() == objectName()) {
                    room->setPlayerMark(player, "xiaoqi-slash", 0);
                    room->setPlayerFlag(player, "-xiaoqi_slash");
                    room->setPlayerFlag(player, "-xiaoqi_duel");
                }
            } else if (triggerEvent == CardResponded) {
                const Card *card = data.value<CardResponseStruct>().m_card;
                if (card->isKindOf("Slash") && card->getSkillName() == objectName()) {
                    room->addPlayerMark(player, "xiaoqi-slash");
                }
            } else if (triggerEvent == CardAsked) {
                if (!player->hasFlag("xiaoqi_duel")) {
                    return;
                }
                QStringList data_list = data.toStringList();
                if (data_list.length() != 2) return;
                QString asked = data_list.first();
                if (asked == "slash") {
                    room->setPlayerFlag(player, "-xiaoqi_slash");
                    int i = 0;
                    foreach (ServerPlayer *p, room->getAlivePlayers()) {
                        if (p->hasShownGeneral1() && !p->getGeneralName().contains("sujiang")) {
                            foreach (const Skill *skill, p->getActualGeneral1()->getVisibleSkillList()) {
                                if (skill->objectName().startsWith("mashu")) {
                                    i++;
                                }
                            }
                        }
                        if (p->getGeneral2() && p->hasShownGeneral2() && !p->getGeneral2Name().contains("sujiang")) {
                            foreach (const Skill *skill, p->getActualGeneral2()->getVisibleSkillList()) {
                                if (skill->objectName().startsWith("mashu")) {
                                    i++;
                                }
                            }
                        }
                    }
                    if (player->getMark("xiaoqi-slash") < i) {
                        room->setPlayerFlag(player, "xiaoqi_slash");
                    }
                }
            }
        }
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (triggerEvent != CardUsed)
            return QStringList();
        CardUseStruct use = data.value<CardUseStruct>();
        if (TriggerSkill::triggerable(player) && use.card != NULL && use.card->isKindOf("Slash")) {
            return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this, data)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        Duel *duel = new Duel(use.card->getSuit(), use.card->getNumber());
        duel->copyFrom(use.card);
        duel->setSkillName(objectName());
        use.card = duel;
        data = QVariant::fromValue(use);
        room->setPlayerFlag(player, "xiaoqi_duel");
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


class Qizhi : public TriggerSkill
{
public:
    Qizhi() : TriggerSkill("qizhi")
    {
        events << CardUsed << EventPhaseStart;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == EventPhaseStart && player->getPhase() == Player::NotActive) {
            QList<ServerPlayer *> allplayers = room->getAlivePlayers();
            foreach (ServerPlayer *p, allplayers) {
                room->setPlayerMark(p, "#qizhi", 0);
            }
        }
    }


    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (triggerEvent != CardUsed || !TriggerSkill::triggerable(player)) return QStringList();
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card
                && use.card->getTypeId() != Card::TypeSkill
                && use.card->getTypeId() != Card::TypeEquip
                && player->getMark("#qizhi") < 4
                ) {
            foreach (ServerPlayer *p, room->getAlivePlayers()) {
                if (!use.to.contains(p) && use.from->canDiscard(p, "he")) {
                    return QStringList(objectName());
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        QList<ServerPlayer *> players;
        CardUseStruct use = data.value<CardUseStruct>();
        foreach (ServerPlayer *p, room->getAlivePlayers()) {
            if (!use.to.contains(p) && use.from->canDiscard(p, "he")) {
                players << p;
            }
        }
        ServerPlayer *target = room->askForPlayerChosen(player, players, objectName(), "qizhi-invoke", true, true);
        if (target) {
            room->broadcastSkillInvoke(objectName(), player);
            QStringList target_list = player->tag["qizhi_target"].toStringList();
            target_list.append(target->objectName());
            player->tag["qingshi_target"] = target_list;
            room->addPlayerMark(player, "#qizhi");
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QStringList target_list = player->tag["qizhi_target"].toStringList();
        QString target_name = target_list.last();
        target_list.removeLast();
        player->tag["qizhi_target"] = target_list;

        ServerPlayer *to = NULL;
        foreach (ServerPlayer *p, room->getPlayers()) {
            if (p->objectName() == target_name) {
                to = p;
                break;
            }
        }
        if (to) {
            int card_id = room->askForCardChosen(player, to, "he", objectName(), false, Card::MethodDiscard);
            room->throwCard(card_id, to, player, objectName());
            room->drawCards(to, 1, objectName());
        }
        return false;
    }
};

class Jinqu : public PhaseChangeSkill
{
public:
    Jinqu() : PhaseChangeSkill("jinqu")
    {
        frequency = Frequent;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (!PhaseChangeSkill::triggerable(player)) return QStringList();
        if (player->getPhase() == Player::Finish) return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this)) {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const
    {
        Room *room = player->getRoom();
        room->drawCards(player, 2, objectName());
        int x = player->getHandcardNum() - 4;
        if (x > 0) {
            room->askForDiscard(player, objectName(), x, x);
        }
        return false;
    }
};

class Juzhan : public TriggerSkill
{
public:
    Juzhan() : TriggerSkill("juzhan")
    {
        events << TargetChosen << TargetConfirmed << EventPhaseStart;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == EventPhaseStart && player->getPhase() ==  Player::NotActive) {
            foreach (ServerPlayer *p, room->getAlivePlayers()) {
                room->removePlayerDisableShow(p, objectName());
            }
        }
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (triggerEvent == EventPhaseStart || !TriggerSkill::triggerable(player)) return QStringList();
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card && use.card->isKindOf("Slash")) {
            if (triggerEvent == TargetChosen && use.index == 0 && player->getMark("#juzhan") & 1) {
                foreach (ServerPlayer *p, use.to) {
                    if (p != player && !p->isNude())
                        return QStringList(objectName());
                }
            } else if (triggerEvent == TargetConfirmed && use.from && use.from != player && !(player->getMark("#juzhan") & 1)) {
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (triggerEvent == TargetConfirmed) {
            if (player->askForSkillInvoke(this)) {
                room->broadcastSkillInvoke(objectName(), player);
                return true;
            }
        } else {
            CardUseStruct use = data.value<CardUseStruct>();
            QList<ServerPlayer *> plist;
            foreach (ServerPlayer *p, use.to) {
                if (p != player && !p->isNude())
                    plist << p;
            }
            ServerPlayer *target = room->askForPlayerChosen(player, plist, objectName(), "juzhan-invoke", true, true);
            if (target) {
                room->broadcastSkillInvoke(objectName(), player);
                QStringList target_list = player->tag["juzhan_target"].toStringList();
                target_list.append(target->objectName());
                player->tag["juzhan_target"] = target_list;
                return true;
            }
        }
        return false;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        int x = qMax(1, player->getLostHp());
        if (triggerEvent == TargetConfirmed) {
            CardUseStruct use = data.value<CardUseStruct>();
            QList<ServerPlayer *> plist;
            plist << use.from << player;
            room->sortByActionOrder(plist);
            room->drawCards(plist, x, objectName());
            doJuzhan(player, use.from);
        } else {
            QStringList target_list = player->tag["juzhan_target"].toStringList();
            QString target_name = target_list.last();
            target_list.removeLast();
            player->tag["juzhan_target"] = target_list;

            ServerPlayer *to = NULL;
            foreach (ServerPlayer *p, room->getPlayers()) {
                if (p->objectName() == target_name) {
                    to = p;
                    break;
                }
            }
            if (to) {
                QList<int> toGet = room->askForCardsChosen(player, to, "he", objectName(), x, x, false, Card::MethodGet);
                if (!toGet.isEmpty()) {
                    DummyCard dummy(toGet);
                    CardMoveReason reason(CardMoveReason::S_REASON_EXTRACTION, player->objectName(), to->objectName(), objectName(), QString());
                    room->obtainCard(player, &dummy, reason, false);
                }
                doJuzhan(to, player);
            }
        }
        room->addPlayerMark(player, "#juzhan");
        return false;
    }

private:
    static void doJuzhan(ServerPlayer *from, ServerPlayer *to)
    {
        if (from->isDead() || to->isDead()) return;
        Room *room = from->getRoom();
        QStringList generals, allchoices;
        allchoices << "head" << "deputy" << "cancel";
        if (!to->getActualGeneral1Name().contains("sujiang") && !to->isLord())
            generals << "head";

        if (to->getGeneral2() && !to->getGeneral2Name().contains("sujiang"))
            generals << "deputy";

        if (generals.isEmpty()) return;
        generals << "cancel";

        QString choice = room->askForChoice(from, "juzhan", generals.join("+"), QVariant(),
                                            "@juzhan-hide::" + to->objectName(), allchoices.join("+"));
        if (choice == "cancel") return;
        bool head = (choice == "head");
        to->hideGeneral(head);
        room->setPlayerDisableShow(to, head ? "h":"d", "juzhan");
    }
};

class Danshou : public TriggerSkill
{
public:
    Danshou() : TriggerSkill("danshou")
    {
        events << EventPhaseStart;
    }

    virtual void record(TriggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (player->getPhase() == Player::RoundStart) {
            room->setPlayerMark(player, "danshouUsed", 0);
        } else if (player->getPhase() == Player::NotActive) {
            foreach (ServerPlayer *p, room->getPlayers()) {
                room->setPlayerMark(p, "danshou_discarded", 0);
                room->setPlayerMark(p, "#danshou:exdraw", 0);
            }
        }
    }

    virtual TriggerList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        TriggerList skill_list;
        if (player == NULL) return skill_list;
        switch (player->getPhase()) {
            case Player::PhaseNone:
                Q_ASSERT(false);
            case Player::RoundStart:
            case Player::Finish:
            case Player::NotActive:
                break;
            case Player::Start:
                foreach (ServerPlayer *p, room->findPlayersBySkillName(objectName())) {
                    if (TriggerSkill::triggerable(p) && !p->isAllNude() && p->getMark("danshouUsed") < 1) {
                        skill_list.insert(p, QStringList(objectName()));
                    }
                }
                break;
            case Player::Judge:
            case Player::Draw:
            case Player::Play:
            case Player::Discard:
                foreach (ServerPlayer *p, room->findPlayersBySkillName(objectName())) {
                    int x = p->getMark("danshou_discarded");
                    if (x > 0 && p->getHandcardNum() <= x) {
                        skill_list.insert(p, QStringList(objectName()));
                    }
                }
                break;
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
    {
        if (player->getPhase() == Player::Start) {
            if (ask_who->askForSkillInvoke(this, data)) {
                room->broadcastSkillInvoke(objectName(), ask_who);
                room->addPlayerMark(ask_who, "danshouUsed");
                return true;
            }
            return false;
        }
        return true;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        if (player->getPhase() == Player::Start) {
            QList<const Card *> tricks = ask_who->getJudgingArea();
            int x = tricks.length() + ask_who->getHandcardNum() + ask_who->getEquips().length();
            ask_who->throwAllHandCardsAndEquips();
            foreach (const Card *trick, tricks) {
                CardMoveReason reason(CardMoveReason::S_REASON_NATURAL_ENTER, ask_who->objectName());
                room->throwCard(trick, reason, NULL);
            }
            room->addPlayerMark(ask_who, "danshou_discarded", x);
        } else {
            int x = ask_who->getMark("#danshou:exdraw") + 1;
            if (room->askForChoice(ask_who, objectName(), "draw+exdraw", QVariant(), "#danshou-choose:::" + QString::number(x), "draw+exdraw") == "exdraw") {
                room->addPlayerMark(ask_who, "#danshou:exdraw");
            } else {
                room->setPlayerMark(ask_who, "#danshou:exdraw", 0);
                room->drawCards(ask_who, x, objectName());
                if (x == 4 && room->askForChoice(ask_who, objectName(), "yes+no", QVariant(), "#danshou-damage::" + player->objectName()) == "yes") {
                    room->damage(DamageStruct(objectName(), ask_who, player));
                }
            }
        }
        return false;
    }
};


class Yechou : public TriggerSkill
{
public:
    Yechou() : TriggerSkill("yechou")
    {
        events << Death;
        frequency = Compulsory;
    }


    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (player == NULL || !player->hasSkill(objectName())) return QStringList();
        DeathStruct death = data.value<DeathStruct>();
        if (death.who != player)
            return QStringList();

        if (death.damage && death.damage->from) {
            ServerPlayer *target = death.damage->from;
            if (target->isAlive())
                return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->broadcastSkillInvoke(objectName(), player);
        room->sendCompulsoryTriggerLog(player, objectName());
        return true;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        DeathStruct death = data.value<DeathStruct>();
        ServerPlayer *target = death.damage->from;
        if (target->isAlive()) {
            Slash *slash = new Slash(Card::NoSuit, 0);
            slash->setFlags("Global_NoDistanceChecking");
            slash->setFlags("yechou_1");
            slash->setSkillName("_yechou");
            CardUseStruct use = CardUseStruct(slash, player, target);
            use.disresponsive_list << "_ALL_PLAYERS";
            room->useCard(use, false);
        }
        if (target->isAlive()) {
            Slash *slash = new Slash(Card::NoSuit, 0);
            slash->setFlags("Global_NoDistanceChecking");
            slash->setFlags("yechou_2");
            slash->setSkillName("_yechou");
            CardUseStruct use = CardUseStruct(slash, player, target);
            room->useCard(use, false);
        }
        if (target->isAlive()) {
            Slash *slash = new Slash(Card::NoSuit, 0);
            slash->setFlags("Global_NoDistanceChecking");
            slash->setFlags("yechou_3");
            slash->setSkillName("_yechou");
            CardUseStruct use = CardUseStruct(slash, player, target);
            room->useCard(use, false);
        }
        return false;
    }
};

class YechouEffect : public TriggerSkill
{
public:
    YechouEffect() : TriggerSkill("#yechou-effect")
    {
        events << TargetChosen << DamageCaused << AskForPeaches;
        frequency = Compulsory;
    }


    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (triggerEvent == TargetChosen) {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card && use.card->isKindOf("Slash") && use.card->getSkillName() == "yechou" && use.card->hasFlag("yechou_2")) {
                ServerPlayer *target = use.to.at(use.index);
                if (target)
                    return QStringList(objectName() + "->" + target->objectName());
            }
        } else if (triggerEvent == DamageCaused) {
            DamageStruct damage = data.value<DamageStruct>();
            if (damage.card && damage.card->isKindOf("Slash") && damage.card->getSkillName() == "yechou" && damage.card->hasFlag("yechou_3")) {
                return QStringList(objectName());
            }
        } else {
            DyingStruct dying = data.value<DyingStruct>();
            ServerPlayer *who = dying.who;
            if (dying.damage) {
                const Card *card = dying.damage->card;
                if (card && card->isKindOf("Slash") && card->getSkillName() == "yechou"
                        && who && who != player && who->isFriendWith(player)) {
                    return QStringList(objectName());
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
    {
        return true;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (triggerEvent == TargetChosen) {
            CardUseStruct use = data.value<CardUseStruct>();
            player->addQinggangTag(use.card);
        } else if (triggerEvent == DamageCaused) {
            DamageStruct damage = data.value<DamageStruct>();
            damage.damage++;
            data.setValue(damage);
        } else {
            room->setPlayerFlag(player, "CannotHelp");
        }
        return false;
    }
};

MOLPackage::MOLPackage()
    : Package("MOL")
{
//    General *duyu = new General(this, "duyu", "qun");
//    duyu->addSkill(new Wuku);
//    duyu->addSkill(new Miewu);

    General *lifeng = new General(this, "lifeng", "shu", 3);
    lifeng->addSkill(new Tunchu);
    lifeng->addSkill(new TunchuEffect);
    lifeng->addSkill(new DetachEffectSkill("tunchu", "food"));
    insertRelatedSkills("tunchu", 2, "#tunchu-effect", "#tunchu-clear");
    lifeng->addSkill(new Shuliang);

    General *lingcao = new General(this, "lingcao", "wu");
    lingcao->addSkill(new Dujin);
    lingcao->addSkill(new DujinCompulsory);
    related_skills.insertMulti("dujin", "#dujin-compulsory");

    General *wangji = new General(this, "wangji", "wei", 3);
    wangji->addSkill(new Qizhi);
    wangji->addSkill(new Jinqu);

    General *zhuran = new General(this, "zhuran", "wu");
    zhuran->addSkill(new Danshou);

    addMetaObject<MiewuCard>();
}

OverseasPackage::OverseasPackage()
    : Package("overseas")
{
    General *caozhen = new General(this, "caozhen", "wei");
    caozhen->addCompanion("caopi");
    caozhen->addSkill(new Sidi);
    caozhen->addSkill(new SidiInvalidity);
    caozhen->addSkill(new DetachEffectSkill("sidi", "drive"));
    insertRelatedSkills("sidi", 2, "#sidi-invalidity", "#sidi-clear");

    General *liaohua = new General(this, "liaohua", "shu");
    liaohua->addSkill(new Dangxian);
    liaohua->addCompanion("guanyu");

    General *zhugejin = new General(this, "zhugejin", "wu", 3);
    zhugejin->addSkill(new Huanshi);
    zhugejin->addSkill(new Hongyuan);
    zhugejin->addSkill(new Mingzhe);
    zhugejin->addCompanion("sunquan");

    General *beimihu = new General(this, "beimihu", "qun", 3, false);
    beimihu->addSkill(new Guishu);
    beimihu->addSkill(new Yuanyu);

    General *tianyu = new General(this, "tianyu", "wei");
    tianyu->setDeputyMaxHpAdjustedValue();
    tianyu->addSkill(new Zhenxi);
    tianyu->addSkill(new ZhenxiProhibit);
    tianyu->addSkill(new ZhenxiTargetMod);
    insertRelatedSkills("zhenxi", 2, "#zhenxi-prohibit", "#zhenxi-target");
    tianyu->addSkill(new Jiansu);

    General *maxiumatie = new General(this, "maxiumatie", "qun");
    maxiumatie->addSkill(new Mashu("maxiumatie"));
    maxiumatie->addSkill(new Xiaoqi);
    related_skills.insertMulti("kenshang", "#kenshang-effect");

    General *xiahoushang = new General(this, "xiahoushang", "wei");
    xiahoushang->addCompanion("caopi");
    xiahoushang->addSkill(new Tanfeng);

    General *liyan = new General(this, "liyan", "shu");
    liyan->addCompanion("chendao");
    liyan->setHeadMaxHpAdjustedValue();
    liyan->addSkill(new Jinwu);
    liyan->addSkill(new Zhuke);
    liyan->addSkill(new Quanjia);
    liyan->addSkill(new QuanjiaCompulsory);
    related_skills.insertMulti("quanjia", "#quanjia-compulsory");

    General *huaxiong = new General(this, "huaxiong", "qun");
    huaxiong->addSkill(new Yaowu);
    huaxiong->addSkill(new YaowuDeath);
    huaxiong->addSkill(new Shiyong);
    related_skills.insertMulti("yaowu", "#yaowu-death");

    General *liufuren = new General(this, "liufuren", "qun", 3, false);
    liufuren->addCompanion("yuanshao");
    liufuren->addSkill(new Zhuidu);
    liufuren->addSkill(new Shigong);

    General *yangxiu = new General(this, "yangxiu", "wei", 3);
    yangxiu->addSkill(new Danlao);
    yangxiu->addSkill(new Jilei);

    General *chendao = new General(this, "chendao", "shu");
    chendao->addCompanion("zhaoyun");
    chendao->addSkill(new Wanglie);
    chendao->addSkill(new WanglieTarget);
    related_skills.insertMulti("wanglie", "#wanglie-target");

    General *zumao = new General(this, "zumao", "wu");
    zumao->addCompanion("sunjian");
    zumao->addSkill(new YinbingX);
    zumao->addSkill(new YinbingXCompulsory);
    zumao->addSkill(new DetachEffectSkill("yinbingx", "kerchief"));
    insertRelatedSkills("yinbingx", 2, "#yinbingx-compulsory", "#yinbingx-clear");
    zumao->addSkill(new Juedi);

    General *fuwan = new General(this, "fuwan", "qun");
    fuwan->addSkill(new Moukui);
    fuwan->addSkill(new MoukuiEffect);
    related_skills.insertMulti("moukui", "#moukui-effect");

    addMetaObject<GuishuCard>();
    addMetaObject<HongyuanCard>();
    addMetaObject<JiansuCard>();

    addMetaObject<ZhaofuCard>();
    addMetaObject<ZhaofuVSCard>();

    skills << new ZhenxiTrick << new Qinzhong << new Zhaofu;
}

