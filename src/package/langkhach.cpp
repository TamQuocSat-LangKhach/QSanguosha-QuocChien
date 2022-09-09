#include "langkhach.h"
#include "skill.h"
#include "engine.h"
#include "general.h"

class Bianhua : public TriggerSkill
{
public:
    Bianhua() : TriggerSkill("bianhua")
    {
        events << GeneralShown;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (triggerEvent == GeneralShown) {
            if (TriggerSkill::triggerable(player)) {
                if ((data.toBool() && player->getMark("HaventShowGeneral") > 0)
                        || (!data.toBool() && player->getMark("HaventShowGeneral2") > 0))
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        if (!ask_who->hasShownSkill(this)) return false;
        room->sendCompulsoryTriggerLog(player, "bianhua");
        room->broadcastSkillInvoke("bianhua");
        return true;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
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
    if (effect.from->getPhase() == Player::Play)
        effect.from->setFlags("Global_PlayPhaseTerminated");
    effect.to->setMark("MilitaryOrderExtraTurn", 1);
}

class MilitaryOrderSkill : public TriggerSkill
{
public:
    MilitaryOrderSkill() : TriggerSkill("threaten_emperor")
    {
        events << EventPhaseEnd << DeathFinished;
        global = true;
    }

    virtual int getPriority() const
    {
        return 1;
    }

    virtual void record(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (triggerEvent == EventPhaseStart && player->getPhase() == Player::NotActive) {
            foreach (ServerPlayer *p, room->getAllPlayers()) {
                room->setPlayerMark(p, "MilitaryOrderExtraTurn", 0);
            }
        }
    }

    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        TriggerList list;
        if (triggerEvent != EventPhaseEnd || player->getPhase() != Player::Discard) return list;
        foreach(ServerPlayer *p, room->getAllPlayers())
            if (p->getMark("MilitaryOrderExtraTurn") > 0)
                list.insert(p, QStringList(objectName()));

        return list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *ask_who) const
    {
        return room->askForCard(ask_who, ".", "@threaten_emperor", data);
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *ask_who) const
    {
        LogMessage l;
        l.type = "#Fangquan";
        l.to << ask_who;
        room->sendLog(l);

        ask_who->gainAnExtraTurn();
        return false;
    }
};

ImperialOrder::ImperialOrder(Suit suit, int number)
    : GlobalEffect(suit, number)
{
    setObjectName("imperial_order");
}

bool ImperialOrder::targetRated(const Player *to_select, const Player *) const
{
    return !to_select->hasShownOneGeneral();
}

bool ImperialOrder::isAvailable(const Player *player) const
{
    bool invoke = !player->hasShownOneGeneral();
    if (!invoke) {
        foreach (const Player *p, player->getAliveSiblings()) {
            if (targetRated(p, player) && !player->isProhibited(p, this)) {
                invoke = true;
                break;
            }
        }
    }
    return invoke && TrickCard::isAvailable(player);
}

void ImperialOrder::onUse(Room *room, const CardUseStruct &card_use) const
{
    ServerPlayer *source = card_use.from;
    QList<ServerPlayer *> targets;
    if (card_use.to.isEmpty()) {
        foreach (ServerPlayer *p, room->getAllPlayers()) {
            if (p->hasShownOneGeneral())
                continue;
            const Skill *skill = room->isProhibited(source, p, this);
            if (skill) {
                if (skill && skill->isVisible()) {
                    LogMessage log;
                    log.type = "#SkillAvoid";
                    log.from = p;
                    log.arg = skill->objectName();
                    log.arg2 = objectName();
                    room->sendLog(log);

                    room->broadcastSkillInvoke(skill->objectName());
                }
                continue;
            }
            targets << p;
        }
    } else
        targets = card_use.to;

    CardUseStruct use = card_use;
    use.to = targets;
    Q_ASSERT(!use.to.isEmpty());
    TrickCard::onUse(room, use);
}

void ImperialOrder::onEffect(const CardEffectStruct &effect) const
{
    Room *room = effect.to->getRoom();
   // if (room->askForCard(effect.to, "EquipCard", "@imperial_order-equip"))
   //     return;
    QStringList choices;

    if (!effect.to->hasShownGeneral1() && effect.to->disableShow(true).isEmpty())
        choices << "show_head";
    if (effect.to->getGeneral2() && !effect.to->hasShownGeneral2() && effect.to->disableShow(false).isEmpty())
        choices << "show_deputy";

    QList<int> to_discard = effect.to->forceToDiscard(1, "EquipCard", QString(), true);
    if (!to_discard.isEmpty())
        choices << "dis_equip";

    choices << "losehp";

    QString all_choices = "show_head+show_deputy+dis_equip+losehp";

    QString choice = room->askForChoice(effect.to, objectName(), choices.join("+"), QVariant(), "@imperial_order-choose", all_choices);
    if (choice.contains("show")) {
        effect.to->showGeneral(choice == "show_head");
        effect.to->drawCards(1, objectName());
    } else if (choice == "dis_equip"){
        if (!room->askForCard(effect.to, "EquipCard!", "@imperial_order-equip")) {
            const Card *card = Sanguosha->getCard(to_discard.first());
            CardMoveReason reason(CardMoveReason::S_REASON_THROW, effect.to->objectName());
            room->moveCardTo(card, effect.to, NULL, Player::DiscardPile, reason, true);
        }
    } else if (choice == "losehp"){
        room->loseHp(effect.to);
    }
}

LangKhachPackage::LangKhachPackage()
    : Package("langkhach")
{
    General *wuding = new General(this, "wuding", "careerist", 3);
    wuding->addSkill(new Bianhua);
}

ADD_PACKAGE(LangKhach)
