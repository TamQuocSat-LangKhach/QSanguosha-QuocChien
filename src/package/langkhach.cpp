#include "langkhach.h"
#include "skill.h"
#include "engine.h"
#include "general.h"
#include "package.h"
#include "standard.h"
#include "standard-tricks.h"
#include "standard-shu-generals.h"
#include "json.h"

class Bianhua : public TriggerSkill
{
public:
    Bianhua() : TriggerSkill("bianhua")
    {
        events << GeneralShowed << EventPhaseEnd;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player) || !player->hasShownSkill(this))
            return QStringList();
        if (triggerEvent == GeneralShowed && player->cheakSkillLocation(objectName(), data) && player->getMark("bianhuaUsed") == 0)
            return QStringList(objectName());
        if (triggerEvent == EventPhaseEnd && player->getPhase() == Player::RoundStart && !player->getBianhuaGeneral())
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->sendCompulsoryTriggerLog(player, objectName());
        room->broadcastSkillInvoke(objectName());
        if (triggerEvent == GeneralShowed) {
            room->addPlayerMark(player, "bianhuaUsed");
        }
        return true;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (triggerEvent == EventPhaseEnd) {
            room->broadcastSkillInvoke("transform", player->getActualGeneral2()->isMale());
            room->transformDeputyGeneral(player);
            return false;
        }
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
        ServerPlayer *to = room->askForPlayerChosen(player, targets, objectName(), "@bianhua-invoke", true, true);
        if (to != NULL) {
            bool head = player->inHeadSkills(objectName());
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
            room->setPlayerProperty(player, "bianhua-choice", choice);
            QList<const TriggerSkill *> game_start;
            QVariant void_data;
            foreach (const Skill *skill, general->getVisibleSkillList(true, head)) {
                if (skill == this || skill->isLordSkill() || skill->isAttachedLordSkill()) continue;
                if (skill->inherits("TriggerSkill")) {
                    const TriggerSkill *tr = qobject_cast<const TriggerSkill *>(skill);
                    if (tr && tr->getTriggerEvents().contains(GameStart) && !tr->triggerable(GameStart, room, player, void_data, player).isEmpty()) {
                        game_start << tr;
                    }
                }
                player->addSkill(skill->objectName(), head);
                JsonArray args;
                args << QSanProtocol::S_GAME_EVENT_ADD_SKILL;
                args << objectName();
                args << skill->objectName();
                args << head;
                foreach(ServerPlayer *p, room->getOtherPlayers(player, true))
                    room->doNotify(p, QSanProtocol::S_COMMAND_LOG_EVENT, args);
                if (skill->getFrequency() == Skill::Limited && !skill->getLimitMark().isEmpty()) {
                    room->setPlayerMark(player, skill->getLimitMark(), 1);
                }
            }
            foreach (const TriggerSkill *skill, game_start) {
                if (skill->cost(GameStart, room, player, void_data, player))
                    skill->effect(GameStart, room, player, void_data, player);
            }
            if (head) {
                player->setGender(general->getGender());
            }
        } else {
            room->setPlayerProperty(player, "maxhp", player->getMaxHp() + 1);

            LogMessage log;
            log.type = "#GainMaxHp";
            log.from = player;
            log.arg = QString::number(1);
            room->sendLog(log);

            if (player->canRecover()) {
                RecoverStruct recover;
                recover.who = player;
                room->recover(player, recover);
            }
            room->addPlayerMark(player, "@careerist");
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
        foreach(const Skill *skill, effect.to->getSkillList(true, true)) {
            if (skill && skill->getDescription().contains("Giai đoạn ra bài chủ động ")) {
                const ViewAsSkill *vsSkill = Sanguosha->getViewAsSkill(skill->objectName());
                if (vsSkill) {
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

class MilitaryOrderSkill : public CardTriggerSkill
{
public:
    MilitaryOrderSkill() : CardTriggerSkill("military_order")
    {
        events << EventPhaseStart << Death;
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
        } else if (triggerEvent == EventPhaseStart) {
            if (player->getPhase() != Player::NotActive) return;
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

class BaixiangRange : public AttackRangeSkill
{
public:
    BaixiangRange() : AttackRangeSkill("#baixiang-range")
    {
    }

    virtual int getExtra(const Player *target, bool) const
    {
        if (target->hasShownSkill("baixiang") && !target->getOffensiveHorse() && !target->getDefensiveHorse() && !target->getSpecialHorse()) {
            return 1;
        }
        return 0;
    }
};

class Baixiang : public DistanceSkill
{
public:
    Baixiang() : DistanceSkill("baixiang")
    {
    }

    virtual int getCorrect(const Player *, const Player *to) const
    {
        if (to->hasShownSkill(objectName()) && !to->getOffensiveHorse() && !to->getDefensiveHorse() && !to->getSpecialHorse())
            return 1;
        else
            return 0;
    }
};


PowangCard::PowangCard()
{
    will_throw = false;
    handling_method = Card::MethodNone;
}

bool PowangCard::targetRated(const Player *to_select, const Player *self) const
{
    SavageAssault *sa = new SavageAssault(Card::NoSuit, 0);
    sa->deleteLater();
    return sa->isAvailable(self) && to_select != self && to_select->hasShownOneGeneral() && !self->isProhibited(to_select, sa);
}

void PowangCard::onUse(Room *room, const CardUseStruct &card_use) const
{
    ServerPlayer *from = card_use.from;
    QList<ServerPlayer *> targets;
    SavageAssault *sa = new SavageAssault(card_use.card->getSuit(), card_use.card->getNumber());
    sa->setSkillName("_powang");
    sa->addSubcards(subcards);
    sa->setShowSkill("powang");
    sa->setCanRecast(false);
    foreach (ServerPlayer *p, room->getOtherPlayers(from)) {
        if (p->isFriendWith(card_use.to.first()) &&  !from->isProhibited(p, sa)) {
            targets << p;
        }
    }
    room->addPlayerMark(from, "powangUse");
    room->useCard(CardUseStruct(sa, from, targets));
    room->setPlayerMark(from, "powangUse", 0);
}

class Powang : public OneCardViewAsSkill
{
public:
    Powang() : OneCardViewAsSkill("powang")
    {
        relate_to_place = "head";
        filter_pattern = ".|.|1,12,13|.";
        response_or_use = true;
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        SavageAssault *sa = new SavageAssault(Card::NoSuit, 0);
        sa->setSkillName("_powang");
        sa->deleteLater();
        return !player->hasUsed("PowangCard") && sa->isAvailable(player);
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        PowangCard *powang = new PowangCard();
        powang->setSkillName(objectName());
        powang->addSubcard(originalCard);
        return powang;
    }

    virtual int getEffectIndex(const ServerPlayer *, const Card *card) const
    {
        return (card->getTypeId() == Card::TypeSkill) ? -1 : 0;
    }
};

class PowangDiscard : public TriggerSkill
{
public:
    PowangDiscard() : TriggerSkill("#powang-discard")
    {
        events << DamageCaused;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (player != NULL && player->isAlive()) {
            DamageStruct damage = data.value<DamageStruct>();
            if (damage.card && damage.card->getSkillName() == "powang" && player->getMark("powangUse") > 0 && damage.to->hasEquip()) {
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        DamageStruct damage = data.value<DamageStruct>();
        if (room->askForChoice(player, "powang", "yes+no", data, "@powang-discard:" + damage.to->objectName()) == "yes") {
            QList<int> to_throw;
            foreach (const Card *c, damage.to->getEquips()) {
                to_throw << c->getEffectiveId();
            }
            LogMessage log;
            log.type = "#PowangDiscard";
            log.from = player;
            log.to << damage.to;
            room->sendLog(log);
            if (!to_throw.isEmpty()) {
                CardMoveReason reason(CardMoveReason::S_REASON_DISMANTLE, player->objectName(), damage.to->objectName(), QString(), QString());
                room->moveCardsAtomic(CardsMoveStruct(to_throw, NULL, Player::DiscardPile, reason), true);
            }
            return true;
        }
        return false;
    }
};

class Shengweijiang : public TriggerSkill
{
public:
    Shengweijiang() : TriggerSkill("shengweijiang")
    {
        events << AskForPeachesDone;
        frequency = Frequent;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (TriggerSkill::triggerable(player) && player->getPhase() == Player::NotActive && player->getHp() <= 0) {
            return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this, data)) {
            room->broadcastSkillInvoke(objectName(), player);
            room->doSuperLightbox("shengweijiang", objectName());
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        RecoverStruct recover;
        recover.recover = player->getMaxHp() - player->getHp();
        recover.who = player;
        room->recover(player, recover);
        player->fillHandCards(player->getMaxHp(), objectName());
        ServerPlayer *current = room->getCurrent();
        if (current && current->isAlive() && current->getPhase() == Player::Play) {
            room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, player->objectName(), current->objectName());
            room->setPlayerFlag(current, "Global_PlayPhaseTerminated");
            LogMessage log;
            log.type = "#shengweijiang-end";
            log.from = player;
            log.to << current;
            room->sendLog(log);
        }
        room->addPlayerMark(player, "##shengweijiang");
        room->addPlayerMark(player, "##siweishen");
        room->handleAcquireDetachSkills(player, "-shengweijiang|siweishen!");
        return false;
    }
};

class Siweishen : public TriggerSkill
{
public:
    Siweishen() : TriggerSkill("siweishen")
    {
        events << EventPhaseStart << DamageCaused;
        frequency = Frequent;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == EventPhaseStart && player->getPhase() == Player::NotActive && player->isAlive() && player->getMark("##siweishen") > 0) {
            LogMessage log;
            log.type = "#siweishen-death";
            log.from = player;
            room->sendLog(log);
            room->killPlayer(player);
        }
    }

    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        TriggerList skill_list;
        if (triggerEvent == DamageCaused) {
            QList<ServerPlayer *> zhaoshizhens = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *zhaoshizhen, zhaoshizhens) {
                if (zhaoshizhen && TriggerSkill::triggerable(zhaoshizhen) && zhaoshizhen->isFriendWith(player) && zhaoshizhen->getMark("##shengweijiang") > 0) {
                    skill_list.insert(zhaoshizhen, QStringList(objectName()));
                }
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *ask_who) const
    {
        if (ask_who->askForSkillInvoke(this, data)) {
            room->broadcastSkillInvoke(objectName(), ask_who);
            room->setPlayerMark(ask_who, "##shengweijiang", 0);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *, ServerPlayer *, QVariant &data, ServerPlayer *) const
    {
        DamageStruct damage = data.value<DamageStruct>();
        damage.damage++;
        data = QVariant::fromValue(damage);
        return false;
    }
};


ColdsnapCard::ColdsnapCard()
{

}

bool ColdsnapCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    return targets.isEmpty() && to_select != Self && to_select->getMark("##coldsnap") < 1;
}

void ColdsnapCard::onEffect(const CardEffectStruct &effect) const
{
    ServerPlayer *target = effect.to;
    Room *room = target->getRoom();
    room->addPlayerMark(target, "#coldsnap");
}

class Coldsnap : public OneCardViewAsSkill
{
public:
    Coldsnap() : OneCardViewAsSkill("coldsnap")
    {
        filter_pattern = ".|.|.|hand";
    }

    const Card *viewAs(const Card *originalCard) const
    {
        ColdsnapCard *skill_card = new ColdsnapCard;
        skill_card->addSubcard(originalCard);
        skill_card->setShowSkill(objectName());
        return skill_card;
    }

    bool isEnabledAtPlay(const Player *player) const
    {
        return !player->hasUsed("ColdsnapCard");
    }

    virtual int getEffectIndex(const ServerPlayer *, const Card *card) const
    {
        return (card->getTypeId() == Card::TypeSkill) ? -1 : 0;
    }
};

class ColdsnapEffect : public TriggerSkill
{
public:
    ColdsnapEffect() : TriggerSkill("#coldsnap-effect")
    {
        events << Damaged << EventPhaseStart;
        frequency = Compulsory;
        global = true;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == EventPhaseStart && player->getPhase() == Player::RoundStart) {
            room->setPlayerMark(player, "#coldsnap", 0);
        }
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (triggerEvent == Damaged) {
            if (player->getMark("#coldsnap") > 0) {
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
    {
        return true;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        int x = player->getMark("#coldsnap");
        if (room->askForDiscard(player, "coldsnap", x, x, true, true, "@coldsnap-effect:::" + x)) {
            room->addPlayerMark(player, "#coldsnap");
        } else {
            room->setPlayerMark(player, "#coldsnap", 0);
            player->turnOver();
        }
        return false;
    }
};

class Ghostwalk : public TriggerSkill
{
public:
    Ghostwalk() : TriggerSkill("ghostwalk")
    {
        events << EventPhaseStart << GeneralShown;
        frequency = Compulsory;
    }

    virtual bool canPreshow() const
    {
        return false;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if (triggerEvent == EventPhaseStart) {
            if (player != NULL && player->isAlive() && player->getPhase() == Player::RoundStart) {
                ServerPlayer *caohong = room->findPlayerBySkillName("heyi");
                if (caohong && caohong->isAlive() && caohong->hasShownSkill("heyi") && player->inFormationRalation(caohong)) {
                    room->doBattleArrayAnimate(caohong);
                    room->broadcastSkillInvoke(objectName(), caohong);
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

class Icewall : public BattleArraySkill
{
public:
    Icewall() : BattleArraySkill("icewall", HegemonyMode::Formation)
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
                ServerPlayer *caohong = room->findPlayerBySkillName("heyi");
                if (caohong && caohong->isAlive() && caohong->hasShownSkill("heyi") && player->inFormationRalation(caohong)) {
                    room->doBattleArrayAnimate(caohong);
                    room->broadcastSkillInvoke(objectName(), caohong);
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

class IcewallVH : public ViewHasSkill
{
public:
    IcewallVH() : ViewHasSkill("icewallVH")
    {
        global = true;
    }

    virtual bool ViewHas(const Player *player, const QString &skill_name, const QString &flag) const
    {
        if (flag != "skill" || skill_name != "feiying" && skill_name != "ganglie") return false;
        QList<const Player *> sib = player->getAliveSiblings();
        sib << player;
        if (sib.length() < 4) return false;

        QList<const Player *> teammates = player->getFormation();

        if (teammates.length() < 2) return false;

        foreach (const Player *caohong, teammates) {
            if (caohong->hasShownSkill("icewall"))
                return true;
        }

        return false;
    }
};


LangKhachPackage::LangKhachPackage()
    : Package("langkhach", GeneralPack, true)
{
    General *wuding = new General(this, "wuding", "careerist", 3);
    wuding->setGender(General::Neuter);
    wuding->addSkill(new Bianhua);

    General *zhaoshizhen = new General(this, "zhaoshizhen", "qun", 4, false);
    zhaoshizhen->addSkill(new SavageAssaultAvoid("baixiang"));
    zhaoshizhen->addSkill(new Baixiang);
    zhaoshizhen->addSkill(new BaixiangRange);
    zhaoshizhen->addSkill(new Powang);
    zhaoshizhen->addSkill(new PowangDiscard);
    zhaoshizhen->addSkill(new Shengweijiang);
    zhaoshizhen->addRelateSkill("siweishen");
    zhaoshizhen->setHeadMaxHpAdjustedValue();
    insertRelatedSkills("baixiang", 2, "#baixiang-range", "#sa_avoid_baixiang");
    insertRelatedSkills("powang", "#powang-discard");

    addMetaObject<PowangCard>();
    skills << new Siweishen;
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
