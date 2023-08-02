#include "removed.h"
#include "standard-basics.h"
#include "standard-tricks.h"
#include "client.h"
#include "engine.h"
#include "structs.h"
#include "gamerule.h"
#include "settings.h"
#include "roomthread.h"
#include "json.h"

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
                int x = qMin(from->getHandcardNum() - chengyu->getHandcardNum(),5);
                room->askForDiscard(from, "benyu_discard", x, x);
            }
        }
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
                        player->setChained(false);
                        room->setEmotion(player, "chain");
                        room->broadcastProperty(player, "chained");
                        room->getThread()->trigger(ChainStateChanged, room, player);
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

RemovedPackage::RemovedPackage()
    : Package("removed")
{
    General *quancong = new General(this, "quancong", "wu");
    quancong->addSkill(new Qinzhong);
    quancong->addSkill(new Zhaofu);

    General *guohuai = new General(this, "guohuai", "wei");
    guohuai->addSkill(new Jingce);
    guohuai->addCompanion("zhanghe");

    General *maliang = new General(this, "maliang", "shu", 3);
    maliang->addSkill(new Mumeng);
    maliang->addSkill(new Naman);
    maliang->addCompanion("zhugeliang");

    General *zhangchunhua = new General(this, "zhangchunhua", "wei", 3, false);
    zhangchunhua->addSkill(new Guojue);
    zhangchunhua->addSkill(new GuojueDamage);
    zhangchunhua->addSkill(new Shangshi);
    related_skills.insertMulti("guojue", "#guojue-damage");
    zhangchunhua->addCompanion("simayi");

    General *yijibo = new General(this, "yijibo", "shu", 3);
    yijibo->addSkill(new Dingke);
    yijibo->addSkill(new Jiyuan);

    General *zhangyi = new General(this, "zhangyi", "shu");
    zhangyi->addCompanion("liaohua");
    zhangyi->addSkill(new Kangrui);
    zhangyi->addSkill(new KangruiProhibit);
    insertRelatedSkills("kangrui", "#kangrui-prohibit");

    General *chengpu = new General(this, "chengpu", "wu");
    chengpu->addCompanion("zhouyu");
    chengpu->addSkill(new Huxun);
    chengpu->addSkill(new Yuancong);

    General *chengyu = new General(this, "chengyu", "wei", 3);
    chengyu->addCompanion("caopi");
    chengyu->addSkill(new Shefu);
    chengyu->addSkill(new ShefuCompulsory);
    chengyu->addSkill(new DetachEffectSkill("shefu", "ambush"));
    insertRelatedSkills("shefu", 2, "#shefu-compulsory", "#shefu-clear");
    chengyu->addSkill(new Benyu);

    General *guyong = new General(this, "guyong", "wu", 3);
    guyong->addSkill(new Lifu);
    guyong->addSkill(new Yanzhong);

    addMetaObject<ZhaofuCard>();
    addMetaObject<ZhaofuVSCard>();
    addMetaObject<ShangshiCard>();
    addMetaObject<HuxunMoveCard>();
    addMetaObject<ShefuCard>();
    addMetaObject<LifuCard>();
    addMetaObject<MumengCard>();

    skills << new HuxunMove << new YuancongUseCard;
}

