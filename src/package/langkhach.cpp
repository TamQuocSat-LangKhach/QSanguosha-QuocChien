#include "langkhach.h"
#include "skill.h"
#include "engine.h"
#include "general.h"

class Bianhua : public TriggerSkill
{
public:
    Bianhua() : TriggerSkill("bianhua")
    {
        events << GeneralShown << Dying;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (TriggerSkill::triggerable(player)) {
            if (triggerEvent == GeneralShown) {
                if ((data.toBool() && player->getMark("HaventShowGeneral") > 0)
                        || (!data.toBool() && player->getMark("HaventShowGeneral2") > 0))
                return QStringList(objectName());
            } else if (triggerEvent == Dying) {
                DyingStruct dying = data.value<DyingStruct>();
                if (dying.who == player)
                    return QStringList(objectName());
            }
        }

        return QStringList();
    }

    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
    {
        if (!ask_who->hasShownSkill(this)){
            if (triggerEvent == GeneralShown) return false;
            DyingStruct dying = data.value<DyingStruct>();
            if (dying.who == player)
                return player->askForSkillInvoke(this, data);
        }
        room->sendCompulsoryTriggerLog(player, "bianhua");
        room->broadcastSkillInvoke("bianhua");
        return true;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (triggerEvent == Dying) return false;
        if (player->cheakSkillLocation(objectName(), true)) {
            if (data.toBool()) {
                QList<ServerPlayer *> targets;

                foreach (ServerPlayer *p, room->getAlivePlayers()) {
                    if (p == player) continue;
                    if (p->hasShownGeneral1() && !p->getActualGeneral1Name().contains("sujiang")) {
                        targets << p;
                        continue;
                    }
                    if (p->hasShownGeneral2() && !p->getActualGeneral2Name().contains("sujiang")) {
                        targets << p;
                        continue;
                    }
                }
                if (targets.isEmpty()) return false;
                ServerPlayer *to = room->askForPlayerChosen(player, targets, objectName(), "bianhua-invoke", false, true);
                if (to != NULL) {
                    QStringList choicelist;
                    if (to->hasShownGeneral1() && !to->getActualGeneral1Name().contains("sujiang")) {
                        choicelist << to->getActualGeneral1Name();
                    }
                    if (to->hasShownGeneral2() && !to->getActualGeneral2Name().contains("sujiang")) {
                        choicelist << to->getActualGeneral2Name();
                    }
                    QString choice = room->askForChoice(player, objectName(), choicelist.join("+"), QVariant::fromValue(to), "@bianhua-choose::"+to->objectName());
                    const General *general = Sanguosha->getGeneral(choice);
                    QList<const Skill *> skills = general->getVisibleSkillList();
        //                pg->setGender(general->getGender());
        //                pg->addCompanion(general->getCompanions());
                    foreach (const Skill *skill, skills) {
        //                    player->getActualGeneral1()->addSkill(skill);
                        if (skill->isLordSkill() || skill->isAttachedLordSkill()) continue;
                        if (skill->relateToPlace(false)) continue;
                        room->acquireSkill(player, skill, true, true);
                        if (!skill->getLimitMark().isEmpty()) {
                            room->setPlayerMark(player, skill->getLimitMark(), 1);
                        }
                    }
                    player->setGender(general->getGender());
                    if (player->hasShownGeneral2() && player->getActualGeneral2()->isCompanionWith(choice)) {
                        room->addPlayerMark(player, "@companion");
                    } else {
                        room->setTag("bianhua-choice", choice);
                    }
                }
            } else {
                if (!room->getTag("bianhua-choice").isNull() && player->getActualGeneral2()->isCompanionWith(room->getTag("bianhua-choice").toString())) {
                    room->addPlayerMark(player, "@companion");
                    room->removeTag("bianhua-choice");
                }
            }
        } else {
            LogMessage log;
            log.type = "#CheatingDeputyCareerist";
            log.from = player;
            log.to << room->getAllPlayers();
            room->sendLog(log);
        }

        return false;
    }
};

MilitaryOrder::MilitaryOrder(Suit suit, int number)
    : SingleTargetTrick(suit, number)
{
    setObjectName("military_order");
    target_fixed = true;
    transferable = true;
}

bool MilitaryOrder::targetRated(const Player *to_select, const Player *Self) const
{
    return to_select == Self;
}

void MilitaryOrder::onUse(Room *room, const CardUseStruct &card_use) const
{
    CardUseStruct use = card_use;
    if (use.to.isEmpty())
        use.to << use.from;
    SingleTargetTrick::onUse(room, use);
}

bool MilitaryOrder::isAvailable(const Player *player) const
{
    return !player->isProhibited(player, this) && TrickCard::isAvailable(player);
}

void MilitaryOrder::onEffect(const CardEffectStruct &effect) const
{
    if (effect.to != effect.from) {
        return;
    }
    if (effect.card->getSkillName() != NULL) {
        return;
    }
    Room *room = effect.to->getRoom();
    room->setEmotion(effect.to, "military_order");
    if (effect.from->getPhase() == Player::Play) {
        int num = 0;
        foreach (ServerPlayer *p, room->getAlivePlayers()) {
            if (p->isFriendWith(effect.from)) continue;
            if (p->hasShownOneGeneral()) {
                int kingdomCount = p->getPlayerNumWithKingdom();
                if (kingdomCount > num)
                    num = kingdomCount;
            }
        }
        if (num > 0) effect.to->drawCards(num);
        foreach(const Skill *skill, effect.to->getSkillList()) {
            QString translation = skill->getDescription();
            if (translation.contains("Một lần trong giai đoạn hành động")) {

            }
        }

        effect.to->setMark("MilitaryOrder", 1);
    }
        //effect.from->setFlags("Global_PlayPhaseTerminated");
    //effect.to->setMark("MilitaryOrderExtraTurn", 1);
}

class MilitaryOrderSkill : public TriggerSkill
{
public:
    MilitaryOrderSkill() : TriggerSkill("military_order")
    {
        events << EventPhaseChanging << Death;
        global = true;
    }

    virtual int getPriority() const
    {
        return 1;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
//        if (triggerEvent == EventPhaseStart && player->getPhase() == Player::NotActive) {
//            foreach (ServerPlayer *p, room->getAllPlayers()) {
//                room->setPlayerMark(p, "MilitaryOrderExtraTurn", 0);
//            }
//        }
    }

    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
//        TriggerList list;
//        if (triggerEvent != EventPhaseEnd || player->getPhase() != Player::Discard) return list;
//        foreach(ServerPlayer *p, room->getAllPlayers())
//            if (p->getMark("MilitaryOrderExtraTurn") > 0)
//                list.insert(p, QStringList(objectName()));

//        return list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *ask_who) const
    {
        return true;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (triggerEvent == Death && player->getMark("MilitaryOrder") > 0) {
            DeathStruct death = data.value<DeathStruct>();
            ServerPlayer *from = death.damage->from;
            if (from == player) {
                player->setMark("MilitaryOrder", 0);
                if (player->getPhase() == Player::Play) {
                    player->setFlags("Global_PlayPhaseTerminated");
                    player->setMark("MilitaryOrderComplete", 1);
                }
            }
        } else if (triggerEvent == EventPhaseChanging) {
            PhaseChangeStruct change = data.value<PhaseChangeStruct>();
            if (change.to != Player::NotActive) return false;
            if (player->getMark("MilitaryOrderComplete") > 0) {
                player->setMark("MilitaryOrderComplete", 0);
            } else if (player->getMark("MilitaryOrder") > 0) {
                player->setMark("MilitaryOrder", 0);
                if (player->isAlive()) {
                    room->killPlayer(player);
                }
            }
        }
//        LogMessage l;
//        l.type = "#Fangquan";
//        l.to << ask_who;
//        room->sendLog(l);

//        ask_who->gainAnExtraTurn();
        return false;
    }
};

class MilitaryOrderMaxCards : public MaxCardsSkill
{
public:
    MilitaryOrderMaxCards() : MaxCardsSkill("#militaryorder-maxcards")
    {
    }

    virtual int getFixed(const Player *target) const
    {
        if (target->getMark("MilitaryOrderComplete") > 0)
            return target->getMaxHp();
        else
            return -1;
    }
};

Poison::Poison(Suit suit, int number, bool is_transferable) : BasicCard(suit, number)
{
    setObjectName("poison");
    target_fixed = true;
    transferable = is_transferable;
}

QString Poison::getSubtype() const
{
    return "poison_card";
}

bool Poison::targetRated(const Player *to_select, const Player *self) const
{
    return to_select == self;
}

void Poison::onUse(Room *room, const CardUseStruct &card_use) const
{
    CardUseStruct use = card_use;
    if (use.to.isEmpty())
        use.to << use.from;
    BasicCard::onUse(room, use);
}

void Poison::onEffect(const CardEffectStruct &) const
{
}

bool Poison::isAvailable(const Player *player) const
{
    return !player->isProhibited(player, this) && BasicCard::isAvailable(player);
}

class PoisonSkill : public TriggerSkill
{
public:
    PoisonSkill() : TriggerSkill("poison")
    {
        events << CardsMoveOneTime;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent , Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        QStringList trigger_skill;
        if (TriggerSkill::triggerable(player)) {

            QVariantList move_datas = data.toList();
            foreach (QVariant move_data, move_datas) {
                CardsMoveOneTimeStruct move = move_data.value<CardsMoveOneTimeStruct>();
                if (move.from == player && (move.from_places.contains(Player::PlaceHand))
                    && !(move.to == player && (move.to_place == Player::PlaceHand))
                        && move.open.at(0)) {
                    int i = 0;
                    foreach (int id, move.card_ids) {
                        bool open = move.open.at(i);
                        i++;
                        if (open && Sanguosha->getCard(id)->getName() == "poison")
                            trigger_skill << objectName();
                    }
                }
            }
        }
        return trigger_skill;
    }

    virtual bool cost(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
    {
        return true;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *player) const
    {
        room->loseHp(player);
        return false;
    }
};


LangKhachPackage::LangKhachPackage()
    : Package("langkhach")
{
    General *wuding = new General(this, "wuding", "careerist", 3);
    wuding->addSkill(new Bianhua);
}

ADD_PACKAGE(LangKhach)
