#include "langkhach.h"
#include "skill.h"
#include "engine.h"
#include "general.h"
#include "package.h"

class Bianhua : public TriggerSkill
{
public:
    Bianhua() : TriggerSkill("bianhua")
    {
        events << GeneralShown << GeneralShowed;
        frequency = Compulsory;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == GeneralShowed && player->hasShownAllGenerals()) {
            if (player->getMark("FakeCompanion") > 0 && !player->getMark("BianhuaCompanionChecked") > 0) {
                room->addPlayerMark(player, "@companion");
            }
            room->addPlayerMark(player, "BianhuaCompanionChecked");
            room->removePlayerMark(player, "FakeCompanion");
        }
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (triggerEvent == GeneralShown && TriggerSkill::triggerable(player)) {
            if (data.toBool() && player->getMark("HaventShowGeneral") > 0)
            return QStringList(objectName());
        }

        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        if (!ask_who->hasShownSkill(this)){
            return false;
        }
        if (!player->cheakSkillLocation(objectName(), true)) {
            return false;
        }
        room->sendCompulsoryTriggerLog(player, "bianhua");
        room->broadcastSkillInvoke("bianhua");
        return true;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
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
        ServerPlayer *to = room->askForPlayerChosen(player, targets, objectName(), "@bianhua-invoke", false, true);
        if (to != NULL) {
            QStringList choicelist;
            if (to->hasShownGeneral1() && !to->getActualGeneral1Name().contains("sujiang")) {
                choicelist << to->getActualGeneral1Name();
            }
            if (to->hasShownGeneral2() && !to->getActualGeneral2Name().contains("sujiang")) {
                choicelist << to->getActualGeneral2Name();
            }
            QString choice = room->askForChoice(player, objectName(), choicelist.join("+"), QVariant::fromValue(to), "@bianhua-choose");
            const General *general = Sanguosha->getGeneral(choice);
            LogMessage log;
            log.type = "#bianhua-choice";
            log.from = player;
            log.arg = choice;
            room->sendLog(log);
            room->addPlayerMark(player, "##" + choice);
            QList<const Skill *> skills = general->getVisibleSkillList();
            foreach (const Skill *skill, skills) {
                if (skill->isLordSkill() || skill->isAttachedLordSkill()) continue;
                if (skill->relateToPlace(false)) continue;
                room->acquireSkill(player, skill, true, true);
                if (!skill->getLimitMark().isEmpty()) {
                    room->setPlayerMark(player, skill->getLimitMark(), 1);
                }
            }
            player->setGender(general->getGender());
            if (player->getActualGeneral2()->isCompanionWith(choice))
                room->addPlayerMark(player, "FakeCompanion");
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
        QStringList choicelist;
        choicelist << "slash";
//        choicelist << "analeptic";
        foreach(const Skill *skill, effect.to->getSkillList(true, true)) {
//            static QSet<QString> skill_set;
//            if (skill_set.isEmpty()) {
//                skill_set.insert("qice");
//                skill_set.insert("zaoyun");
//                skill_set.insert("mingfa");
//            }
            if (skill->getDescription().contains("lần trong giai đoạn ra bài")) {
                if (skill->inherits("ViewAsSkill") ||
                        (skill->inherits("TriggerSkill") && qobject_cast<const TriggerSkill*>(skill)->getViewAsSkill() != NULL)) {
                    choicelist << skill->objectName();
                }
            }
        }
        QString choice = room->askForChoice(effect.to, "military_order", choicelist.join("+"), QVariant(), "military_order_choose", choicelist.join("+"));
        if (choice == "slash") {
            room->addPlayerMark(effect.to, "MilitaryOrder_Slash");
        } else if (choice == "analeptic") {
            room->addPlayerMark(effect.to, "MilitaryOrder_Analeptic");
        } else if (choice != NULL) {
            room->addPlayerHistory(effect.to, "ViewAsSkill_" + choice + "Card", -1);
            room->addPlayerHistory(effect.to, QString(choice.at(0).toUpper()) + choice.mid(1) + "Card", -1);
        }
        room->setPlayerMark(effect.to, "MilitaryOrder", 1);
    }
}

class MilitaryOrderTarget : public TargetModSkill
{
public:
    MilitaryOrderTarget() : TargetModSkill("#militaryorder-target")
    {
    }

    virtual int getResidueNum(const Player *from, const Card *card, const Player *) const
    {
        if (card->isKindOf("Slash")) {
            return from->getMark("MilitaryOrder_Slash");
        }
//        if (card->getName() == "analeptic") {
//            return from->getMark("MilitaryOrder_Analeptic");
//        }
        return 0;
    }
};

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

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if (triggerEvent == Death && player->getMark("MilitaryOrder") > 0) {
            DeathStruct death = data.value<DeathStruct>();
            if (death.who == player) {
                return;
            }
            ServerPlayer *from = death.damage->from;
            if (from == player) {
                LogMessage log;
                log.type = "#military_order_successed";
                log.from = player;
                room->sendLog(log);
                room->setPlayerMark(player, "MilitaryOrder", 0);
                if (player->getPhase() == Player::Play) {
                    room->setPlayerFlag(player, "Global_PlayPhaseTerminated");
                    room->setPlayerMark(player, "MilitaryOrderComplete", 1);
                }
            }
        } else if (triggerEvent == EventPhaseChanging) {
            PhaseChangeStruct change = data.value<PhaseChangeStruct>();
            if (change.to != Player::NotActive) return;
            if (player->getMark("MilitaryOrderComplete") > 0) {
                room->setPlayerMark(player, "MilitaryOrderComplete", 0);
            } else if (player->getMark("MilitaryOrder") > 0) {
                room->setPlayerMark(player, "MilitaryOrder", 0);
                if (player->isAlive()) {
                    LogMessage log;
                    log.type = "#military_order_failed";
                    log.from = player;
                    room->sendLog(log);
                    room->killPlayer(player);
                }
            }
            if (player->getMark("MilitaryOrder_Slash") > 0)
                room->setPlayerMark(player, "MilitaryOrder_Slash", 0);
            if (player->getMark("MilitaryOrder_Analeptic") > 0)
                room->setPlayerMark(player, "MilitaryOrder_Analeptic", 0);
        }
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

//class FemaleOutfitSkill : public ArmorSkill
//{
//public:
//    FemaleOutfitSkill() : ArmorSkill("FemaleOutfit")
//    {
//        events << CardsMoveOneTime;
//        frequency = Compulsory;
//    }

//    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
//    {
//        if (player->isMale()) {
//            CardsMoveOneTimeStruct move = data.value<CardsMoveOneTimeStruct>();
//            if (player->hasFlag("TianjituDiscard")) {
//                if (move.to == player && move.to_place == Player::PlaceEquip) {
//                    for (int i = 0; i < move.card_ids.size(); i++) {
//                        const Card *card = Sanguosha->getEngineCard(move.card_ids[i]);
//                        if (card->objectName() == objectName()) {
//                            player->setFlags("-TianjituDiscard");
//                            room->setEmotion(player, "treasure/tianjitu");

//                            bool discard = false;
//                            foreach (const Card *card, player->getCards("he")) {
//                                if (card->objectName() == objectName()) continue;
//                                int id = card->getEffectiveId();
//                                if (!player->canDiscard(player, id)) continue;
//                                discard = true;
//                            }
//                            if (discard)
//                                room->askForDiscard(player, objectName(), 1, 1, false, true, QString(), "^Tianjitu");
//                        }
//                    }
//                }
//            }
//        }
//        return QStringList();
//    }

//    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
//    {
//        if (triggerEvent == CardsMoveOneTime) return true;
//        return ArmorSkill::cost(room, player, data);
//    }

//    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
//    {
//        if (triggerEvent == DamageInflicted) {
//            DamageStruct damage = data.value<DamageStruct>();
//            room->setEmotion(player, "armor/silver_lion");
//            LogMessage log;
//            log.type = "#SilverLion";
//            log.from = player;
//            log.arg = QString::number(damage.damage);
//            log.arg2 = objectName();
//            room->sendLog(log);

//            damage.damage = 1;
//            data = QVariant::fromValue(damage);
//        } else {

//            room->notifySkillInvoked(player, objectName());

//            room->setEmotion(player, "armor/silver_lion");
//            RecoverStruct recover;
//            room->recover(player, recover);

//            return false;
//        }
//        return false;
//    }

//    bool triggerable(const ServerPlayer *target) const
//    {
//        return target != NULL && target->isAlive();
//    }

//    bool trigger(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
//    {
//        CardsMoveOneTimeStruct move = data.value<CardsMoveOneTimeStruct>();
//        if (player->hasFlag("TianjituDiscard")) {
//            if (move.to == player && move.to_place == Player::PlaceEquip) {
//                for (int i = 0; i < move.card_ids.size(); i++) {
//                    const Card *card = Sanguosha->getEngineCard(move.card_ids[i]);
//                    if (card->objectName() == objectName()) {
//                        player->setFlags("-TianjituDiscard");
//                        room->setEmotion(player, "treasure/tianjitu");

//                        bool discard = false;
//                        foreach (const Card *card, player->getCards("he")) {
//                            if (card->objectName() == objectName()) continue;
//                            int id = card->getEffectiveId();
//                            if (!player->canDiscard(player, id)) continue;
//                            discard = true;
//                        }
//                        if (discard)
//                            room->askForDiscard(player, objectName(), 1, 1, false, true, QString(), "^Tianjitu");
//                    }
//                }
//            }
//        }
//        if (player->hasFlag("TianjituDraw")) {
//            if (move.from != player || !move.from_places.contains(Player::PlaceEquip)) return false;
//            for (int i = 0; i < move.card_ids.size(); i++) {
//                if (move.from_places[i] != Player::PlaceEquip) continue;
//                const Card *card = Sanguosha->getEngineCard(move.card_ids[i]);
//                if (card->objectName() == objectName()) {
//                    player->setFlags("-TianjituDraw");
//                    room->setEmotion(player, "treasure/tianjitu");
//                    player->drawCards(5 - player->getHandcardNum(), objectName());
//                }
//            }
//        }
//        return false;
//    }
//};

//FemaleOutfit::FemaleOutfit(Suit suit, int number) :Armor(suit, number)
//{
//    setObjectName("FemaleOutfit");

//    target_fixed = false;
//}

//bool FemaleOutfit::targetFilter(const QList<const Player *> &targets, const Player *, const Player *) const
//{
//    return targets.isEmpty();
//}


//void FemaleOutfit::onInstall(ServerPlayer *player) const
//{
//    if (player->isAlive() && player->isMale() && player->hasArmorEffect(objectName())) {
//    Room *room = player->getRoom();
//    JudgeStruct judge;
//    judge.pattern = ".|heart";
//    judge.good = true;
//    judge.reason = objectName();
//    judge.who = player;

//    room->judge(judge);

//    if (judge.isBad())
//        room->askForDiscard(player, "FemaleOutfit_discard", 2, 2, false, true);
//    }
//    Armor::onInstall(player);
//}

//BrokenHalberd::BrokenHalberd(Suit suit, int number) : Weapon(suit, number, 0)
//{
//    setObjectName("BrokenHalberd");
//    target_fixed = false;
//}

//bool BrokenHalberd::targetFilter(const QList<const Player *> &targets, const Player *, const Player *) const
//{
//    return targets.isEmpty();
//}

LangKhachPackage::LangKhachPackage()
    : Package("langkhach")
{
    General *wuding = new General(this, "wuding", "careerist", 3);
    wuding->setGender(General::Neuter);
    wuding->addSkill(new Bianhua);

    diy = true;
}

ADD_PACKAGE(LangKhach)

LangKhachCardPackage::LangKhachCardPackage() : Package("langkhach_card", CardPack, true)
{
    QList<Card *> cards;

    cards
        << new MilitaryOrder(Card::Club, 3);

    foreach(Card *card, cards)
        card->setParent(this);
    skills << new MilitaryOrderSkill << new MilitaryOrderMaxCards << new MilitaryOrderTarget;
}

ADD_PACKAGE(LangKhachCard)

//ExodiaCardPackage::ExodiaCardPackage() : Package("gift_card", CardPack)
//{
//    QList<Card *> cards;

//    cards
//        << new BrokenHalberd(Card::Club, 3);
//    cards
//        << new FemaleOutfit(Card::Heart, 3);

//    foreach(Card *card, cards)
//        card->setParent(this);
//}

//ADD_PACKAGE(GiftCard)
