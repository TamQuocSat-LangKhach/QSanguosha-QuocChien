#include "game.h"
#include "skill.h"
#include "standard-basics.h"
#include "standard-tricks.h"
#include "engine.h"
#include "client.h"

//general classes and functions

Key::Key(Card::Suit suit, int number)
    : DelayedTrick(suit, number)
{
    setObjectName("keyCard");
}

bool Key::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *) const
{
    // please use this to check validity when put key
    int num = 0;
    foreach (const Card *card, to_select->getJudgingArea())
    {
        if (card->objectName() == objectName())
        {
            num++;
        }
    }
    return targets.isEmpty() && (num == 0 || (to_select->hasShownSkill("huanyuan") && num < 3));
}

void Key::takeEffect(ServerPlayer *target) const
{
    target->clearHistory();
#ifndef QT_NO_DEBUG
    if (!target->getAI() && target->askForSkillInvoke("userdefine:cancelkeyCard")) return;
#endif
}

void Key::onEffect(const CardEffectStruct &effect) const
{
    ServerPlayer *player = effect.to;
    if (player == NULL || !player->isAlive() || !player->isWounded())
        return;

    Room *room = player->getRoom();

    LogMessage log;
    log.from = player;
    log.arg = effect.card->objectName();
    log.type = "$KeyRecover";
    room->sendLog(log);

    RecoverStruct recover;
    recover.recover = 1;
    recover.card = effect.card;
    room->recover(player, recover, true);
}

//for managing anything needed to be done with key
class keyCardGlobalManagement : public CardTriggerSkill
{
public:
    keyCardGlobalManagement() : CardTriggerSkill("keyCard-global")
    {
        events << CardsMoveOneTime << Damaged;
        global = true;
    }

    virtual TriggerList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (event == CardsMoveOneTime)
        {
            CardsMoveOneTimeStruct move = data.value<CardsMoveOneTimeStruct>();
            for (int i = 0; i < move.card_ids.length(); i++)
            {
                if (!VariantList2IntList(room->getTag("keyList").toList()).contains(move.card_ids[i]))
                    continue;
                if (move.from != NULL && move.from->isAlive() && move.from_places[i] != NULL && move.from_places[i] == Player::PlaceDelayedTrick)
                {
                    ServerPlayer *from = NULL;
                    foreach(auto p, room->getAlivePlayers())
                    {
                        if (p->objectName() == move.from->objectName())
                        {
                            from = p;
                            break;
                        }
                    }

                    if (from != NULL && from->isAlive() && from->isWounded())
                    {
                        skill_list.insert(from, QStringList(objectName()));
                    }
                    else if (move.to_place != Player::PlaceDelayedTrick)
                    {
                        QList<QVariant> ql = room->getTag("keyList").toList();
                        ql.removeOne(QVariant::fromValue(move.card_ids[i]));
                        room->setTag("keyList", ql);
                    }
                }
            }
        }
        else if (event == Damaged)
        {
            auto damage = data.value<DamageStruct>();
            if (damage.damage > 0 && damage.to != NULL && damage.to->isAlive() && damage.to->containsTrick("keyCard") && damage.to == player)
            {
                skill_list.insert(damage.to, QStringList(objectName()));
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *, QVariant &, ServerPlayer *ask_who) const
    {
        if (event == CardsMoveOneTime)
        {
            return true;
        }
        else if (event == Damaged)
        {
            const Card *key;
            foreach (const Card *card, ask_who->getJudgingArea())
            {
                if (card->isKindOf("Key"))
                {
                    key = card;
                }
            }

            LogMessage log;
            log.from = ask_who;
            log.type = "#DelayedTrick";
            log.arg = key->objectName();
            room->sendLog(log);

            JudgeStruct judge;
            judge.pattern = ".|diamond|.";
            judge.good = true;
            judge.reason = "keyCard";
            judge.who = ask_who;

            room->judge(judge);

            if (judge.isGood())
            {
                return true;
            }

        }
        return false;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *ask_who) const
    {
        if (event == Damaged)
        {
            const Card *key;
            foreach (const Card *card, ask_who->getJudgingArea())
            {
                if (card->isKindOf("Key"))
                {
                    key = card;
                }
            }

            CardMoveReason reason(CardMoveReason::S_REASON_PUT, ask_who->objectName());
            room->moveCardTo(key, ask_who, NULL, Player::DiscardPile, reason, true);
        }
        else if (event == CardsMoveOneTime)
        {
            CardsMoveOneTimeStruct move = data.value<CardsMoveOneTimeStruct>();
            for (int i = 0; i < move.card_ids.length(); i++)
            {
                if (!VariantList2IntList(room->getTag("keyList").toList()).contains(move.card_ids[i]))
                    continue;

                const Card *card = Sanguosha->getCard(move.card_ids[i]);
                Key* key = new Key(card->getSuit(), card->getNumber());
                key->addSubcard(card);
                Card *trick = Sanguosha->cloneCard(key);
                Q_ASSERT(trick != NULL);
                WrappedCard *wrapped = Sanguosha->getWrappedCard(move.card_ids[i]);
                wrapped->takeOver(trick);
                room->broadcastUpdateCard(room->getPlayers(), wrapped->getId(), wrapped);
                room->cardEffect(wrapped, ask_who, ask_who);

                if (move.to_place != Player::PlaceDelayedTrick)
                {
                    QList<QVariant> ql = room->getTag("keyList").toList();
                    ql.removeOne(QVariant::fromValue(move.card_ids[i]));
                    room->setTag("keyList", ql);
                }
            }
        }
        return false;
    }

    virtual int getPriority() const
    {
        return 2;
    }
};

//Put an card as key for Key Skills
void putKeyFromId(Room *room, int id, ServerPlayer *from, ServerPlayer *to, QString skill_name)
{
    const Card *card = Sanguosha->getCard(id);
    Key* key = new Key(card->getSuit(), card->getNumber());
    key->addSubcard(card);
    key->setSkillName(skill_name);

    Card *trick = Sanguosha->cloneCard(key);
    Q_ASSERT(trick != NULL);
    WrappedCard *wrapped = Sanguosha->getWrappedCard(id);
    wrapped->takeOver(trick);
    room->broadcastUpdateCard(room->getPlayers(), wrapped->getId(), wrapped);
    wrapped->setShowSkill(card->showSkill());

    CardMoveReason reason(CardMoveReason::S_REASON_PUT, from->objectName(), to->objectName(), skill_name, "putkey");
    room->moveCardTo(wrapped, from, to, Player::PlaceDelayedTrick, reason, true);

    //addkey
    if (room->getTag("keyList") == NULL)
    {
        QList<int> newList;
        room->setTag("keyList", QVariant::fromValue(newList));
    }
    QList<QVariant> ql = room->getTag("keyList").toList();
    ql.append(QVariant::fromValue(key->getEffectiveId()));
    room->setTag("keyList", ql);
}

//haixing & taozui by SE
HaixingCard::HaixingCard()
{
    will_throw = false;
    handling_method = Card::MethodNone;
}

bool HaixingCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    if (!targets.isEmpty())
        return false;

    return to_select != Self;
}

void HaixingCard::use(Room *room, ServerPlayer *source, QList<ServerPlayer *> &targets) const
{
    ServerPlayer *target = targets.first();

    CardMoveReason reason(CardMoveReason::S_REASON_GIVE, source->objectName(), target->objectName(), "haixing", QString());
    room->obtainCard(target, this, reason, false);

    if (!target->hasFlag("haixing_used"))
        target->setFlags("haixing_used");
}

class HaixingViewAsSkill : public ViewAsSkill
{
public:
    HaixingViewAsSkill() : ViewAsSkill("haixing")
    {
        response_pattern = "@@haixing";
    }

    virtual bool viewFilter(const QList<const Card *> &, const Card *to_select) const
    {
        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (cards.isEmpty())
            return NULL;

        HaixingCard *card = new HaixingCard;
        card->addSubcards(cards);
        card->setShowSkill(objectName());
        return card;
    }
};

class Haixing : public TriggerSkill
{
public:
    Haixing() : TriggerSkill("haixing")
    {
        events << EventPhaseStart;
        frequency = NotFrequent;
        view_as_skill = new HaixingViewAsSkill;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer * &) const
    {
        if (triggerEvent == EventPhaseStart && player->getPhase() == Player::Start)
        {
            if (TriggerSkill::triggerable(player) && (player->getHandcardNum() > 0))
            {
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (room->askForUseCard(player, "@@haixing", "@haixing-card"))
        {
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *fuuko, QVariant &, ServerPlayer *) const
    {
        ServerPlayer *nil = NULL;
        QVariant null_data = QVariant::fromValue(NULL);
        while (!fuuko->isKongcheng() && cost(EventPhaseStart, room, fuuko, null_data, nil))
        {
            continue;
        }

        QVariant data = QVariant::fromValue(fuuko);
        room->setPlayerMark(fuuko, "haixing", 0);
        foreach (ServerPlayer *p, room->getAlivePlayers())
        {
            if (p->hasFlag("haixing_used"))
            {
                auto card = room->askForCard(p, ".", "@haixing-back", data, Card::MethodNone, fuuko, false, "haixing");
                if (card != NULL)
                {
                    room->obtainCard(fuuko, card, CardMoveReason::S_REASON_GIVE);
                    room->setPlayerMark(fuuko, "haixing", fuuko->getMark("haixing") + 1);
                }
                p->setFlags("-haixing_used");
            }
        }
        if (fuuko->getMark("haixing") > 1)
        {
            room->setPlayerMark(fuuko, "haixing", 0);
            QList<ServerPlayer *> candidates;
            foreach (auto p, room->getAlivePlayers())
            {
                if (p->isWounded())
                    candidates << p;
            }

            if (!candidates.isEmpty())
            {
                ServerPlayer *t = room->askForPlayerChosen(fuuko, candidates, "haixing_recover");
                RecoverStruct recover;
                recover.who = t;
                room->recover(t, recover);
            }
        }
        return false;
    }
};

TaozuiCard::TaozuiCard()
{
    mute = true;
}

bool TaozuiCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    return targets.isEmpty() && Self->canDiscard(to_select, "j");
}

void TaozuiCard::use(Room *, ServerPlayer *source, QList<ServerPlayer *> &targets) const
{
    foreach (ServerPlayer *target, targets)
    {
        if (!source->canDiscard(target, "j"))
            targets.removeOne(target);
    }

    if (targets.length() > 0)
    {

        QVariantList target_list;
        foreach (ServerPlayer *target, targets)
        {
            target_list << QVariant::fromValue(target);
        }

        source->tag["taozui_invoke"] = target_list;
        source->setFlags("taozui");
    }
}

class TaozuiViewAsSkill : public ViewAsSkill
{
public:
    TaozuiViewAsSkill() : ViewAsSkill("taozui")
    {
    }

    virtual bool isEnabledAtPlay(const Player *) const
    {
        return false;
    }

    virtual bool isEnabledAtResponse(const Player *, const QString &pattern) const
    {
        return pattern.startsWith("@@taozui");
    }

    virtual bool viewFilter(const QList<const Card *> &, const Card *) const
    {
        return false;
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (cards.isEmpty())
        {
            TaozuiCard *taozui = new TaozuiCard;
            return taozui;
        }
        return NULL;
    }
};

class Taozui : public TriggerSkill
{
public:
    Taozui() : TriggerSkill("taozui")
    {
        events << EventPhaseChanging;
        frequency = NotFrequent;
        view_as_skill = new TaozuiViewAsSkill;
    }

    virtual QStringList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (!TriggerSkill::triggerable(player))
            return QStringList();
        PhaseChangeStruct change = data.value<PhaseChangeStruct>();
        if (change.to == Player::Judge && !player->isSkipped(Player::Judge) && !player->isSkipped(Player::Draw))
        {
            bool invoke = false;
            foreach (ServerPlayer *p, room->getAlivePlayers())
            {
                if (player->canDiscard(p, "j"))
                {
                    invoke = true;
                    break;
                }
            }
            if (invoke)
            {
                player->tag.remove("taozui_invoke");
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (room->askForUseCard(player, "@@taozui", "@taozui"))
        {
            if (player->hasFlag("taozui") && player->tag.contains("taozui_invoke"))
            {
                player->skip(Player::Judge);
                player->skip(Player::Draw);
                return true;
            }
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *fuuko, QVariant &, ServerPlayer *) const
    {
        QVariantList target_list;
        target_list = fuuko->tag["taozui_invoke"].toList();
        fuuko->tag.remove("taozui_invoke");
        QList<ServerPlayer *> targets;

        foreach (QVariant x, target_list)
        {
            targets << x.value<ServerPlayer *>();
        }
        if (targets.length() == 0)
            return false;
        foreach (ServerPlayer *p, targets)
        {
            int id = room->askForCardChosen(fuuko, p, "j", objectName(), false, Card::MethodNone);
            if (id != -1)
            {
                auto card = Sanguosha->getCard(id);
                CardMoveReason reason(CardMoveReason::S_REASON_PUT, fuuko->objectName());
                room->throwCard(card, reason, NULL, fuuko);

                Key *key = new Key(Card::NoSuit, 0);
                key->deleteLater();
                const QList<const Player *> empty;
                if (key->targetFilter(empty, p, fuuko))
                {
                    int id = room->drawCard();
                    room->showCard(fuuko, id);
                    putKeyFromId(room, id, fuuko, p, objectName());
                }
            }
        }
        return false;
    }
};

//yuanqi by SE
class Yuanqi : public TriggerSkill
{
public:
    Yuanqi() : TriggerSkill("yuanqi")
    {
        events << EventPhaseStart << EventPhaseChanging;
        frequency = NotFrequent;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (triggerEvent == EventPhaseStart)
        {
            if (TriggerSkill::triggerable(player) && player->getPhase() == Player::Start)
            {
                foreach (ServerPlayer *p, room->getOtherPlayers(player))
                {
                    if (!p->getJudgingArea().isEmpty())
                    {
                        foreach (const Card *c, p->getJudgingArea())
                        {
                            if (player->getJudgingArea().isEmpty())
                                return QStringList(objectName());
                            bool good = true;
                            foreach (const Card *pc, player->getJudgingArea())
                            {
                                if (pc->getClassName() == c->getClassName())
                                    good = false;
                            }
                            if (good)
                                return QStringList(objectName());
                        }
                    }
                }
            }
        }
        else if (triggerEvent == EventPhaseChanging)
        {
            if (data.value<PhaseChangeStruct>().to == Player::Judge && player->hasFlag("yuanqi_used"))
            {
                player->setFlags("-yuanqi_used");
                player->skip(Player::Judge);
                player->insertPhase(Player::Play);
                PhaseChangeStruct change = data.value<PhaseChangeStruct>();
                change.to = Player::Play;
                data.setValue(change);
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (triggerEvent == EventPhaseStart)
        {
            if (player->askForSkillInvoke(objectName()))
            {
                room->broadcastSkillInvoke(objectName());
                return true;
            }
        }
        return false;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *haruka, QVariant &, ServerPlayer *) const
    {
        if (triggerEvent == EventPhaseStart)
        {
            QList<ServerPlayer *> targets;
            foreach (ServerPlayer *p, room->getOtherPlayers(haruka))
            {
                if (!p->getJudgingArea().isEmpty())
                {
                    foreach (const Card *c, p->getJudgingArea())
                    {
                        if (haruka->getJudgingArea().isEmpty())
                            targets.append(p);
                        else
                        {
                            bool good = true;
                            foreach (const Card *pc, haruka->getJudgingArea())
                            {
                                if (pc->getClassName() == c->getClassName())
                                    good = false;
                            }
                            if (good)
                                if (!targets.contains(p))
                                    targets.append(p);
                        }
                    }
                }
            }
            if (targets.isEmpty())
                return false;
            ServerPlayer *target = room->askForPlayerChosen(haruka, targets, objectName());
            QList<int> cardids;
            foreach (const Card *c, target->getJudgingArea())
            {
                if (haruka->getJudgingArea().isEmpty())
                    cardids.append(c->getEffectiveId());
                else
                {
                    bool good = true;
                    foreach (const Card *pc, haruka->getJudgingArea())
                    {
                        if (pc->getClassName() == c->getClassName())
                            good = false;
                    }
                    if (good)
                        cardids.append(c->getEffectiveId());
                }
            }
            room->fillAG(cardids, haruka);
            int cardid = room->askForAG(haruka, cardids, false, objectName());
            room->clearAG(haruka);
            if (cardid < 0)
                return false;
            room->moveCardTo(Sanguosha->getCard(cardid), target, haruka, room->getCardPlace(cardid),
                CardMoveReason(CardMoveReason::S_REASON_TRANSFER,
                    haruka->objectName(), objectName(), QString()));//not working good
            haruka->setFlags("yuanqi_used");
        }
        return false;
    }
};

//daihei by SE
class Daihei : public TriggerSkill
{
public:
    Daihei() : TriggerSkill("daihei")
    {
        events << EventPhaseStart;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer * &) const
    {
        if (triggerEvent == EventPhaseStart)
        {
            if (TriggerSkill::triggerable(player) && player->getPhase() == Player::Finish && player->faceUp())
            {
                int length = player->getHandcardNum() + player->getEquips().length() + player->getJudgingArea().length();
                foreach (ServerPlayer *p, room->getOtherPlayers(player))
                {
                    if (p->getHandcardNum() + p->getEquips().length() + p->getJudgingArea().length() > length)
                        return QStringList();
                }
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        bool invoke = player->hasShownSkill(this) ? true : room->askForSkillInvoke(player, objectName());
        if (invoke)
        {
            room->broadcastSkillInvoke(objectName());
            return true;
        }

        return false;
    }

    virtual bool effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *haruka, QVariant &, ServerPlayer *) const
    {
        if (triggerEvent == EventPhaseStart)
        {
            room->drawCards(haruka, 3); // Maybe drawing 2 is enough
            haruka->turnOver();
        }
        return false;
    }
};

//xiaying by SE

class Xiaying : public TriggerSkill
{
public:
    Xiaying() : TriggerSkill("xiaying")
    {
        events << EventPhaseStart;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player) || player->getPhase() != Player::Start)
            return QStringList();

        foreach (ServerPlayer *p, room->getOtherPlayers(player))
        {
            if (player->isFriendWith(p))
            {
                return QStringList(objectName());
            }
        }

        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->hasShownSkill(this) || room->askForSkillInvoke(player, objectName()))
        {
            room->broadcastSkillInvoke(objectName());
            return true;
        }

        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *misuzu, QVariant &, ServerPlayer *) const
    {
        int shouldGiveNum = 0;
        int giveNum = 0;
        foreach (ServerPlayer * p, room->getOtherPlayers(misuzu))
        {
            if (p->isFriendWith(misuzu))
            {
                shouldGiveNum++;
                auto exchange = room->askForExchange(p, objectName(), 999, 0, "@xiaying_give:" + misuzu->objectName(), "", ".|.|.|hand");
                if (!exchange.isEmpty())
                {
                    DummyCard dummy(exchange);
                    room->obtainCard(misuzu, &dummy, false);
                    giveNum += exchange.length();
                }
            }
        }
        if (giveNum <= shouldGiveNum) // must be more than
        {
            LogMessage log;
            log.type = "#XiayingLoseHp";
            log.from = misuzu;
            log.arg = giveNum;
            log.arg2 = shouldGiveNum;
            room->loseHp(misuzu, 1);
            if (misuzu->isAlive())
            {
                Key *key = new Key(Card::NoSuit, 0);
                key->deleteLater();
                const QList<const Player *> empty;
                if (key->targetFilter(empty, misuzu, misuzu))
                {
                    int id = room->drawCard();
                    room->showCard(misuzu, id);
                    putKeyFromId(room, id, misuzu, misuzu, objectName());
                }
            }
        }
        return false;
    }
};

//yumeng by SE
class Yumeng : public TriggerSkill
{
public:
    Yumeng() : TriggerSkill("yumeng")
    {
        frequency = Compulsory;
        events << DrawNCards;
    }

    virtual TriggerList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &) const
    {
        TriggerList skill_list;
        if (player != NULL && player->isAlive())
        {
            QList<ServerPlayer *> misuzus = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *misuzu, misuzus)
                if ((misuzu->isFriendWith(player) || misuzu->willBeFriendWith(player)) && misuzu->getLostHp() > 0)
                    skill_list.insert(misuzu, QStringList(objectName()));
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *ask_who) const
    {
        if (ask_who->hasShownSkill(this) || room->askForSkillInvoke(ask_who, objectName()))
        {
            room->broadcastSkillInvoke(objectName(), ask_who);
            return true;
        }

        return false;
    }

    virtual bool effect(TriggerEvent, Room *, ServerPlayer *, QVariant &data, ServerPlayer *ask_who) const
    {
        data = data.toInt() + qMin(2, ask_who->getLostHp());
        return false;
    }
};

//pasheng by SE
class Pasheng : public TriggerSkill
{
public:
    Pasheng() : TriggerSkill("pasheng")
    {
        events << TargetConfirming;
        frequency = NotFrequent;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player)) return QStringList();
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.to.length() > 1 || use.from == player || (use.from && use.from->getJudgingArea().isEmpty()))
            return QStringList();
        if (!use.to.contains(player))
            return QStringList();
        if (use.card != NULL && use.card->getTypeId() != Card::TypeSkill && !use.card->isKindOf("SkillCard") && !use.card->isKindOf("TransferCard"))
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        bool invoke = room->askForSkillInvoke(player, objectName());
        if (invoke)
        {
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
        return false;
    }
};

//jiuzhu by SE
class Jiuzhu : public TriggerSkill
{
public:
    Jiuzhu() : TriggerSkill("jiuzhu")
    {
        events << QuitDying << PreHpLost << CardsMoveOneTime;
    }

    virtual TriggerList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (event == QuitDying)
        {
            DyingStruct dying = data.value<DyingStruct>();
            if (player->isAlive() && player->getHp() > 0 ) {
                QList<ServerPlayer *> rins = room->findPlayersBySkillName(objectName());
                foreach (ServerPlayer *rin, rins)
                {
                    Key *key = new Key(Card::NoSuit, 0);
                    const QList<const Player *> empty;
                    if (key->targetFilter(empty, dying.who, rin) && !dying.who->containsTrick("keyCard"))
                    {
                        delete key;
                        skill_list.insert(rin, QStringList(objectName()));
                    }
                }
            }
        }
        else if (event == PreHpLost)
        {
            if (!player->containsTrick("keyCard")) return skill_list;
            QList<ServerPlayer *> rins = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *rin, rins)
            {
                if (rin != NULL)
                    skill_list.insert(rin, QStringList(objectName()));
            }
        }
        else if (event == CardsMoveOneTime)
        {
            CardsMoveOneTimeStruct move = data.value<CardsMoveOneTimeStruct>();
            for (int i = 0; i < move.card_ids.length(); i++)
            {
                if (!VariantList2IntList(room->getTag("keyList").toList()).contains(move.card_ids[i]))
                    continue;

                if (move.from != NULL && move.from_places[i] != NULL && move.origin_from_places[i] == Player::PlaceDelayedTrick && move.to_place == Player::DiscardPile)
                {
                    ServerPlayer *from = NULL;
                    foreach(auto p, room->getAlivePlayers())
                    {
                        if (p->objectName() == move.from->objectName())
                        {
                            from = p;
                            break;
                        }
                    }

                    if (from != NULL && from == player)
                    {
                        foreach(auto rin, room->findPlayersBySkillName(objectName()))
                        {
                            skill_list.insert(rin, QStringList(objectName()));
                        }
                    }
                }
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        if (event == QuitDying)
        {
            if (room->askForSkillInvoke(ask_who, objectName(), qVariantFromValue(player)))
            {
                room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, ask_who->objectName(), player->objectName());
                room->broadcastSkillInvoke(objectName(), ask_who);
                return true;
            }
        }
        else if (event == PreHpLost)
        {
            if (room->askForSkillInvoke(ask_who, objectName(), qVariantFromValue(player)))
            {
                room->broadcastSkillInvoke(objectName(), ask_who);
                return true;
            }
        }
        else if (event == CardsMoveOneTime)
        {
            if (ask_who->hasShownSkill(this) || room->askForSkillInvoke(ask_who, objectName()))
            {
                room->broadcastSkillInvoke(objectName(), ask_who);
                return true;
            }
        }
        return false;
    }
    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
    {
        if (event == QuitDying)
        {
            DyingStruct dying = data.value<DyingStruct>();
            putKeyFromId(room, room->drawCard(), ask_who, dying.who, objectName());
            return false;
        }
        else if (event == PreHpLost)
        {
            if (!player->containsTrick("keyCard"))
            {
                return false;
            }
            foreach (const Card *card, player->getJudgingArea())
            {
                if (card->isKindOf("Key"))
                {
                    CardMoveReason reason(CardMoveReason::S_REASON_PUT, ask_who->objectName(), player->objectName(), objectName(), QString());
                    room->moveCardTo(card, player, NULL, Player::DiscardPile, reason, true);
                    break;
                }
            }
            return false;
        }
        else if (event == CardsMoveOneTime)
        {
            LogMessage log;
            log.type = "#JiuzhuDraw";
            log.from = ask_who;
            log.arg = objectName();
            room->sendLog(log);
            ask_who->drawCards(1, objectName());
        }
        return false;
    }
};

//luoxuan by SE
LuoxuanCard::LuoxuanCard()
{
}

bool LuoxuanCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *) const
{
    return targets.isEmpty() && to_select->isWounded();
}

void LuoxuanCard::onEffect(const CardEffectStruct &effect) const
{
    RecoverStruct recover;
    recover.card = this;
    recover.who = effect.from;
    effect.to->getRoom()->recover(effect.to, recover);
    if (effect.to->getEquips().length() > 0)
    {
        QString choice = effect.to->getRoom()->askForChoice(effect.from, "luoxuan", "luoxuan_get+luoxuan_give_up");
        if (choice == "luoxuan_get")
        {
            int c = effect.to->getRoom()->askForCardChosen(effect.from, effect.to, "e", objectName());
            effect.from->obtainCard(Sanguosha->getCard(c));
        }
    }
}

class Luoxuan : public OneCardViewAsSkill
{
public:
    Luoxuan() : OneCardViewAsSkill("luoxuan")
    {
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return player->canDiscard(player, "h");
    }

    virtual bool viewFilter(const QList<const Card *> &selected, const Card *to_select) const
    {
        return selected.isEmpty() && !to_select->isEquipped() && (to_select->isKindOf("EquipCard") || to_select->isKindOf("Peach"))
            && !Self->isJilei(to_select);
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        LuoxuanCard *luoxuan = new LuoxuanCard;
        luoxuan->addSubcard(originalCard->getId());
        luoxuan->setShowSkill(objectName());
        return luoxuan;
    }
};

//sidai
class Sidai : public TriggerSkill
{
public:
    Sidai() : TriggerSkill("sidai")
    {
        events << Death;
        frequency = NotFrequent;
    }

    virtual QStringList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (player == NULL || !player->hasSkill(objectName())) return QStringList();
        DeathStruct death = data.value<DeathStruct>();
        if (death.who != player)
            return QStringList();

        QList<ServerPlayer *> dests = room->getOtherPlayers(player);
        Key *key = new Key(Card::NoSuit, 0);
        const QList<const Player *> empty;
        foreach (ServerPlayer *p, dests)
        {
            if (!key->targetFilter(empty, p, player))
                dests.removeOne(p);
        }
        delete key;
        if (dests.length() == 0)
        {
            return QStringList();
        }

        return QStringList(objectName());
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(objectName()))
        {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->notifySkillInvoked(player, objectName());

        int id = room->drawCard();
        room->showCard(player, id);
        QList<ServerPlayer *> dests = room->getOtherPlayers(player);
        Key *key = new Key(Card::NoSuit, 0);
        const QList<const Player *> empty;
        foreach (ServerPlayer *p, dests)
        {
            if (!key->targetFilter(empty, p, player))
                dests.removeOne(p);
        }
        delete key;
        if (dests.length() == 0)
        {
            return false;
        }

        ServerPlayer *dest = room->askForPlayerChosen(player, room->getOtherPlayers(player), objectName());
        if (!dest)
        {
            return false;
        }

        putKeyFromId(room, id, player, dest, objectName());

        auto card = Sanguosha->getEngineCard(id);
        if (card->isKindOf("BasicCard"))
        {
            dest->drawCards(2, objectName());
        }
        else if (card->isKindOf("TrickCard"))
        {
            if (dest->isWounded())
            {
                RecoverStruct recover;
                recover.recover = 1;
                recover.who = player;
                room->recover(dest, recover);
            }
        }
        else if (card->isKindOf("EquipCard"))
        {
            if (!dest->faceUp())
                dest->turnOver();

            if (dest->isChained())
                room->setPlayerProperty(dest, "chained", false);
        }

        return false;
    }
};

class Liepo : public TriggerSkill
{
public:
    Liepo() : TriggerSkill("liepo")
    {
        events << TargetChosen << DamageCaused;
    }

    virtual QStringList triggerable(TriggerEvent event, Room *, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player))
            return QStringList();

        if (event == TargetChosen)
        {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.from != NULL && use.from == player && use.card != NULL && use.card->isKindOf("Slash"))
            {
                ServerPlayer *target = use.to.at(use.index);
                if (target != NULL && !target->getJudgingArea().isEmpty())
                    return QStringList(objectName() + "->" + target->objectName());
            }
        }
        else if (event == DamageCaused)
        {
            DamageStruct damage = data.value<DamageStruct>();

            if (damage.from != NULL && damage.from == player && damage.to != NULL && damage.from->hasFlag("liepo_select_2") && damage.to->hasFlag("liepo_change_damage_type"))
            {
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *target, QVariant &, ServerPlayer *ask_who) const
    {
        if (event == TargetChosen)
        {
            if (ask_who->askForSkillInvoke(objectName(), QVariant::fromValue(target)))
            {
                room->broadcastSkillInvoke(objectName(), 1);
                return true;
            }
        }
        else if (event == DamageCaused)
        {
            room->broadcastSkillInvoke(objectName(), 2);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
    {
        if (event == TargetChosen)
        {
            CardUseStruct use = data.value<CardUseStruct>();
            ServerPlayer *nanoha = ask_who;

            QStringList choices;
            choices << "cant_use_jink";

            if (use.card->isKindOf("ThunderSlash") || use.card->isKindOf("FireSlash"))
                choices << "change_damage_type";

            QString choice = room->askForChoice(nanoha, objectName(), choices.join("+"));

            if (choice == "cant_use_jink")
            {
                QVariantList jink_list = nanoha->tag["Jink_" + use.card->toString()].toList();
                doLiepo(player, use, jink_list);
                nanoha->tag["Jink_" + use.card->toString()] = QVariant::fromValue(jink_list);
            }
            else if (choice == "change_damage_type")
            {
                nanoha->setFlags("liepo_select_2");
                player->setFlags("liepo_change_damage_type");
            }
        }
        else if (event == DamageCaused)
        {
            DamageStruct damage = data.value<DamageStruct>();
            LogMessage log;
            log.type = "#LiepoBuff";
            log.from = damage.from;
            log.to << damage.to;
            log.arg = QString::number(++damage.damage);
            room->sendLog(log);

            damage.from->setFlags("-liepo_select_2");
            damage.to->setFlags("-liepo_change_damage_type");

            damage.nature = DamageStruct::Normal;
            data = QVariant::fromValue(damage);
        }
        return false;
    }

private:
    static void doLiepo(ServerPlayer *target, CardUseStruct use, QVariantList &jink_list)
    {
        int index = use.to.indexOf(target);
        LogMessage log;
        log.type = "#NoJink";
        log.from = target;
        target->getRoom()->sendLog(log);
        jink_list[index] = 0;
    }
};

Lingdan::Lingdan(Card::Suit suit, int number)
    : DelayedTrick(suit, number)
{
    setObjectName("lingdanCard");

    judge.pattern = "BasicCard|.|2~9";
    judge.good = true;
    judge.reason = objectName();
}

bool Lingdan::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    return targets.isEmpty() && !to_select->containsTrick(objectName()) && to_select != Self;
}

void Lingdan::takeEffect(ServerPlayer *target) const
{
    target->clearHistory();

#ifndef QT_NO_DEBUG
    if (!target->getAI() && target->askForSkillInvoke("userdefine:cancellingdanCard")) return;
#endif

    if (target->canDiscard(target, "he"))
        target->getRoom()->askForDiscard(target, objectName(), 2, 2, false, true, "@Lingdan-discard");
}

ShenxingCard::ShenxingCard()
{
    will_throw = false;
}

bool ShenxingCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    return targets.isEmpty() && !to_select->containsTrick("lingdanCard") && to_select != Self;
}

void ShenxingCard::onEffect(const CardEffectStruct &effect) const
{
    Lingdan *ld = new Lingdan(effect.card->getSuit(), effect.card->getNumber());
    ld->addSubcard(effect.card);
    ld->setSkillName("shenxing");
    effect.from->getRoom()->useCard(CardUseStruct(ld, effect.from, effect.to));
}

class Shenxing : public OneCardViewAsSkill
{
public:
    Shenxing() : OneCardViewAsSkill("shenxing")
    {
        response_or_use = true;
        filter_pattern = "BasicCard";
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return !player->isKongcheng();
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        ShenxingCard *card = new ShenxingCard;
        card->addSubcard(originalCard);
        card->setShowSkill(objectName());
        return card;
    }
};

class LeiguangVS : public OneCardViewAsSkill
{
public:
    LeiguangVS() : OneCardViewAsSkill("leiguang")
    {
        response_or_use = true;
        filter_pattern = ".|black|.|hand";
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return Slash::IsAvailable(player) && player->getPhase() == Player::Play;
    }

    virtual bool isEnabledAtResponse(const Player *, const QString &) const
    {
        return false;
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        Card *acard = new ThunderSlash(originalCard->getSuit(), originalCard->getNumber());
        acard->addSubcard(originalCard->getId());
        acard->setSkillName("leiguang");
        acard->setShowSkill("leiguang");
        return acard;
    }
};

class Leiguang : public TriggerSkill
{
public:
    Leiguang() : TriggerSkill("leiguang")
    {
        events << CardFinished;
        view_as_skill = new LeiguangVS;
    }

    virtual bool canPreshow() const
    {
        return false;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (!TriggerSkill::triggerable(player))
            return QStringList();
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.card->getSkillName() == "leiguang" && use.card->isKindOf("Slash")
            && use.from == player && use.to.length() == 1 && use.to.first()->isAlive())
            return QStringList(objectName());
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        if (player->askForSkillInvoke(objectName(), QVariant::fromValue(use.to.first())))
        {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        CardUseStruct use = data.value<CardUseStruct>();
        if (use.to.first()->canDiscard(use.to.first(), "he")
            && room->askForDiscard(use.to.first(), objectName(), 1, 1, true, true, "@leiguang_effect"))
        {
            return false;
        }
        else if (use.m_addHistory)
        {
            room->addPlayerHistory(player, use.card->getClassName(), -1);
            LogMessage log;
            log.type = "#leiguang_more_slash";
            log.from = player;
            log.to << room->getAllPlayers(true);
            room->sendLog(log);
        }
        return false;
    }
};

class Kongwu : public DistanceSkill
{
public:
    Kongwu() : DistanceSkill("kongwu")
    {
    }

    virtual int getCorrect(const Player *from, const Player *to) const
    {
        if (from->hasShownSkill(objectName()) && from->hasShownOneGeneral() && !to->hasShownAllGenerals())
            return -1000;
        else
            return 0;
    }
};

class Chaidao : public TriggerSkill
{
public:
    Chaidao() : TriggerSkill("chaidao")
    {
        events << DamageCaused << DamageInflicted;
    }

    virtual QStringList triggerable(TriggerEvent event, Room *, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (!TriggerSkill::triggerable(player) || !player->getWeapon())
            return QStringList();

        DamageStruct damage = data.value<DamageStruct>();
        if (event == DamageCaused && player->canDiscard(player, player->getWeapon()->getEffectiveId()) && damage.card->isKindOf("Slash"))
        {
            return QStringList(objectName());
        }
        else if (event == DamageInflicted && damage.from != player)
        {
            Collateral *collateral = new Collateral(Card::SuitToBeDecided, 0);
            QList<const Player *> targets;
            collateral->deleteLater();
            if (collateral->targetFilter(targets, player, damage.from) && !damage.from->isProhibited(player, collateral, targets))
            {
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (event == DamageCaused && room->askForCard(player, "Weapon|.|.|equipped", "@chaidao_add_damage", data, Card::MethodDiscard, NULL, false))
        {
            room->broadcastSkillInvoke(objectName(), 1);
            return true;
        }
        if (event == DamageInflicted && room->askForSkillInvoke(player, objectName(), data))
        {
            room->broadcastSkillInvoke(objectName(), 2);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        DamageStruct damage = data.value<DamageStruct>();
        if (event == DamageCaused)
        {
            LogMessage log;
            log.type = "#ChaidaoBuff";
            log.from = damage.from;
            log.to << damage.to;
            log.arg = QString::number(++damage.damage);
            room->sendLog(log);

            data = QVariant::fromValue(damage);
        }
        else if (event == DamageInflicted)
        {
            Collateral *collateral = new Collateral(Card::SuitToBeDecided, 0);
            collateral->setSkillName(objectName());
            QList<const Player *> empty_targets;
            QList<ServerPlayer *> can_slash_targets;
            QList<ServerPlayer *> targets;
            Slash *slash = new Slash(Card::SuitToBeDecided, 0);
            slash->deleteLater();

            targets << player;

            foreach (ServerPlayer *p, room->getOtherPlayers(player))
                if ((slash->targetFilter(empty_targets, p, player)) && (!player->isProhibited(p, slash, empty_targets)))
                    can_slash_targets << p;

            ServerPlayer *victim = room->askForPlayerChosen(damage.from, can_slash_targets, objectName(), "@chaidao_choose", false, true);
            if (victim != NULL)
                targets << victim;

            if (targets.length() != 2)
            {
                delete collateral;
                return false;
            }

            if (room->useCard(CardUseStruct(collateral, damage.from, targets)))
            {
                LogMessage log;
                log.type = "#Breastplate";
                log.from = player;
                if (damage.from)
                    log.to << damage.from;
                log.arg = QString::number(damage.damage);
                if (damage.nature == DamageStruct::Normal)
                    log.arg2 = "normal_nature";
                else if (damage.nature == DamageStruct::Fire)
                    log.arg2 = "fire_nature";
                else if (damage.nature == DamageStruct::Thunder)
                    log.arg2 = "thunder_nature";
                room->sendLog(log);
                return true;
            }
            else
                delete collateral;
        }
        return false;
    }
};

class Canshi : public TriggerSkill
{
public:
    Canshi() : TriggerSkill("canshi")
    {
        events << Damaged << FinishJudge;
    }

    virtual TriggerList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (player == NULL) return skill_list;
        if (triggerEvent == Damaged)
        {
            DamageStruct damage = data.value<DamageStruct>();
            if (damage.card == NULL || !damage.card->isKindOf("Slash") || damage.to->isDead())
                return skill_list;

            QList<ServerPlayer *> rins = room->findPlayersBySkillName(objectName());
            foreach (ServerPlayer *rin, rins)
                if (rin->canDiscard(rin, "he"))
                    skill_list.insert(rin, QStringList(objectName()));
            return skill_list;
        }
        else if (triggerEvent == FinishJudge)
        {
            JudgeStruct *judge = data.value<JudgeStruct *>();

            if (judge->reason == objectName())
            {
                judge->pattern = QString::number(int(judge->card->getSuit()));
                if (room->getCardPlace(judge->card->getEffectiveId()) == Player::PlaceJudge && TriggerSkill::triggerable(player))
                {
                    QList<Card::Suit> suits;
                    foreach (auto id, player->getPile("gem"))
                    {
                        if (id != -1)
                        {
                            if (Sanguosha->getEngineCard(id) != NULL)
                            {
                                suits << Sanguosha->getEngineCard(id)->getSuit();
                            }
                        }
                    }
                    if (!suits.contains(judge->card->getSuit()))
                    {
                        skill_list.insert(player, QStringList(objectName()));
                    }
                }
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *, QVariant &data, ServerPlayer *ask_who) const
    {
        ServerPlayer *rin = ask_who;

        if (rin != NULL)
        {
            if (event == Damaged)
            {
                rin->tag["canshi_data"] = data;
                bool invoke = room->askForDiscard(rin, objectName(), 1, 1, true, true, "@canshi", true);
                rin->tag.remove("canshi_data");

                if (invoke)
                {
                    room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, rin->objectName(), data.value<DamageStruct>().to->objectName());
                    room->broadcastSkillInvoke(objectName(), rin);
                    return true;
                }
            }
            else if (event == FinishJudge)
            {
                return rin->hasShownSkill(this) || rin->askForSkillInvoke(this);
            }
        }
        return false;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
    {
        ServerPlayer *rin = ask_who;
        if (rin == NULL)
            return false;

        if (event == Damaged)
        {
            DamageStruct damage = data.value<DamageStruct>();

            JudgeStruct judge;
            judge.good = true;
            judge.play_animation = false;
            judge.who = rin;
            judge.reason = objectName();

            room->judge(judge);

            Card::Suit suit = (Card::Suit)(judge.pattern.toInt());
            switch (suit)
            {
                case Card::Heart:
                {
                    RecoverStruct recover;
                    recover.who = rin;
                    room->recover(player, recover);

                    break;
                }
                case Card::Diamond:
                {
                    player->drawCards(2);
                    break;
                }
                case Card::Club:
                {
                    if (damage.from && damage.from->isAlive())
                        room->askForDiscard(damage.from, "canshi_discard", 2, 2, false, true, "canshi_discard");

                    break;
                }
                case Card::Spade:
                {
                    if (damage.from && damage.from->isAlive())
                        damage.from->turnOver();

                    break;
                }
                default:
                    break;
            }
        }
        else if (event == FinishJudge)
        {
            JudgeStruct *judge = data.value<JudgeStruct *>();
            player->addToPile("gem", judge->card);
        }

        return false;
    }
};

ModanVoidCard::ModanVoidCard()
{
    will_throw = false;
    target_fixed = true;
}

class ModanVS : public ViewAsSkill
{
public:
    ModanVS() : ViewAsSkill("modan")
    {
        expand_pile = "gem";
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return !player->getPile("gem").isEmpty();
    }

    virtual bool isEnabledAtResponse(const Player *, const QString &pattern) const
    {
        return pattern == "@@modan";
    }

    virtual bool viewFilter(const QList<const Card *> &selected, const Card *to_select) const
    {
        ExpPattern pattern(".|.|.|gem");
        if (!pattern.match(Self, to_select))
            return false;

        if (Sanguosha->currentRoomState()->getCurrentCardUsePattern() == "@@modan")
            return selected.isEmpty();

        foreach (const Card *gem, selected)
            if (to_select->getSuit() == gem->getSuit())
                return false;

        if (selected.length() >= 4)
            return false;
        return true;
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (Sanguosha->currentRoomState()->getCurrentCardUsePattern() == "@@modan" && cards.length() == 1)
        {
            ModanVoidCard *retrialCard = new ModanVoidCard;
            retrialCard->addSubcards(cards);
            retrialCard->setSkillName("modan");
            retrialCard->setShowSkill("modan");
            return retrialCard;
        }

        if (cards.length() == 4)
        {
            ArcheryAttack *aa = new ArcheryAttack(Card::SuitToBeDecided, 0);
            aa->addSubcards(cards);
            aa->setSkillName("modan");
            aa->setShowSkill("modan");
            return aa;
        }
        else
            return NULL;
    }
};

class Modan : public TriggerSkill
{
public:
    Modan() : TriggerSkill("modan")
    {
        events << AskForRetrial;
        view_as_skill = new ModanVS;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *target, QVariant &, ServerPlayer * &) const
    {
        if (!TriggerSkill::triggerable(target))
            return QStringList();

        if (!target->getPile("gem").isEmpty())
        {
            return QStringList(objectName());
        }

        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        JudgeStruct *judge = data.value<JudgeStruct *>();

        QStringList prompt_list;
        prompt_list << "@modan-retrial" << judge->who->objectName()
            << objectName() << judge->reason << QString::number(judge->card->getEffectiveId());
        QString prompt = prompt_list.join(":");

        auto card = room->askForUseCard(player, "@@modan", prompt, -1, Card::MethodResponse, false);

        if (card != NULL)
        {
            room->broadcastSkillInvoke(objectName(), player);

            const Card *oldJudge = judge->card;
            judge->card = Sanguosha->getCard(card->getEffectiveId());

            CardsMoveStruct move1(QList<int>(), judge->who, Player::PlaceJudge,
                CardMoveReason(CardMoveReason::S_REASON_RETRIAL, player->objectName(), objectName(), QString()));

            move1.card_ids.append(card->getEffectiveId());
            int reasonType = CardMoveReason::S_REASON_OVERRIDE;

            CardMoveReason reason(reasonType, player->objectName(), objectName(), QString());
            CardsMoveStruct move2(QList<int>(), judge->who, player, Player::PlaceUnknown, Player::PlaceSpecial, reason);

            QList<int> toAdd;
            toAdd << oldJudge->getEffectiveId();
            player->pileAdd("gem", toAdd);
            move2.card_ids.append(oldJudge->getEffectiveId());

            LogMessage log;
            log.type = "$ChangedJudge";
            log.arg = objectName();
            log.from = player;
            log.to << judge->who;
            log.card_str = QString::number(card->getEffectiveId());
            room->sendLog(log);

            QList<CardsMoveStruct> moves;
            moves.append(move1);
            moves.append(move2);
            room->moveCardsAtomic(moves, true);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *, ServerPlayer *, QVariant &data, ServerPlayer *) const
    {
        JudgeStruct *judge = data.value<JudgeStruct *>();
        judge->updateResult();
        return false;
    }
};

//huanyuan
class Huanyuan : public TriggerSkill
{
public:
    Huanyuan() : TriggerSkill("huanyuan")
    {
        events << EventPhaseStart;
        frequency = NotFrequent;
    }

    virtual bool canPreshow() const
    {
        return false;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer * &) const
    {
        if (TriggerSkill::triggerable(player) && player->getPhase() == Player::Start)
        {
            Key *key = new Key(Card::NoSuit, 0);
            key->deleteLater();
            const QList<const Player *> empty;
            if (key->targetFilter(empty, player, player))
                return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this))
        {
            const Card *c = room->askForCard(player, ".|heart", "@huanyuan_discard", NULL, objectName());
            if (!c)
            {
                room->loseHp(player);
            }
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *ayu, QVariant &, ServerPlayer *) const
    {
        if (!ayu->isAlive()) return false;
        int id = room->drawCard();
        room->showCard(ayu, id);
        putKeyFromId(room, id, ayu, ayu, objectName());

        return false;
    }
};

//Mengxian
class Mengxian : public TriggerSkill
{
public:
    Mengxian() : TriggerSkill("mengxian")
    {
        events << AskForPeaches;
        frequency = NotFrequent;
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *target, QVariant &data, ServerPlayer * &) const
    {
        if (TriggerSkill::triggerable(target))
        {
            DyingStruct dying_data = data.value<DyingStruct>();

            if (target->getHp() > 0)
                return QStringList();

            if (dying_data.who != target)
                return QStringList();

            int num = 0;
            foreach (const Card *card, target->getJudgingArea())
            {
                if (card->isKindOf("Key"))
                {
                    num++;
                }
            }
            if (num < 2)
                return QStringList();
            return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *ayu, QVariant &, ServerPlayer *) const
    {
        QList<int> keys;
        foreach (const Card *card, ayu->getJudgingArea())
        {
            if (card->isKindOf("Key"))
            {
                keys.append(card->getEffectiveId());
            }
        }
        room->fillAG(keys, ayu);
        int id = room->askForAG(ayu, keys, true, objectName());
        room->clearAG(ayu);
        if (id == -1)
        {
            return false;
        }
        ayu->tag["mengxian_id"] = id;
        CardMoveReason reason(CardMoveReason::S_REASON_PUT, ayu->objectName());
        room->throwCard(Sanguosha->getEngineCard(id), reason, NULL, ayu);
        room->broadcastSkillInvoke(objectName(), ayu);
        //room->doSuperLightbox("mengxian", objectName());
        return true;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *ayu, QVariant &, ServerPlayer *) const
    {
        int num = 0;
        foreach (const Card *card, ayu->getJudgingArea())
        {
            if (card->isKindOf("Key"))
            {
                num++;
            }
        }

        ServerPlayer *y1 = room->askForPlayerChosen(ayu, room->getOtherPlayers(ayu), objectName());

        if (y1 == NULL)
        {
            return false;
        }

        QList<ServerPlayer *> drawers;
        drawers << ayu << y1;

        room->drawCards(drawers, num, objectName());
        return false;
    }
};

class FengwangFilter : public FilterSkill
{
public:
    FengwangFilter() : FilterSkill("#fengwang-filter")
    {
    }

    virtual bool viewFilter(const Card *to_select, ServerPlayer *player) const
    {
        Room *room = Sanguosha->currentRoom();
        return player->hasShownSkill("fengwang") && player->getMark("@excalibur") > 0 && to_select->isKindOf("Weapon") 
            && room->getCardPlace(to_select->getEffectiveId()) == Player::PlaceHand;
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        Slash *slash = new Slash(originalCard->getSuit(), originalCard->getNumber());
        slash->setSkillName(objectName());
        WrappedCard *card = Sanguosha->getWrappedCard(originalCard->getId());
        card->takeOver(slash);
        return card;
    }

    virtual int getEffectIndex(const ServerPlayer *, const Card *) const
    {
        return -2;
    }
};

FengwangCard::FengwangCard()
{
    will_throw = false;
    target_fixed = true;
    handling_method = Card::MethodNone;
}

void FengwangCard::onUse(Room *, const CardUseStruct &card_use) const
{
    // it's a weird problem that setShowSkill() can't make general shown, so I put it into onUse().
    QString skill_name = card_use.card->showSkill();
    if (!skill_name.isNull() && card_use.from->ownSkill(skill_name) && !card_use.from->hasShownSkill(skill_name))
        card_use.from->showGeneral(card_use.from->inHeadSkills(skill_name));
    ServerPlayer *source = card_use.from;
    if (source != NULL && subcards.length() > 0)
    {
        bool toPile = true;
        foreach (int id, subcards)
        {
            if (source->getPile("jian").contains(Sanguosha->getEngineCard(id)->getEffectiveId()))
            {
                toPile = false;
                break;
            }
        }

        if (toPile)
        {
            source->addToPile("jian", subcards, false);
        }
        else
        {
            DummyCard dummy(subcards);
            source->obtainCard(&dummy, false);
        }
    }
}

class FengwangVS : public OneCardViewAsSkill
{
public:
    FengwangVS() : OneCardViewAsSkill("fengwang")
    {
        filter_pattern = ".|.|.|jian,hand";
        expand_pile = "jian";
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return !player->getPile("jian").isEmpty() || player->getHandcardNum() > 0;
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        if ((Self->getPile("jian").length() > 0 && Self->getPile("jian").contains(originalCard->getEffectiveId()))
            || Self->getPile("jian").length() == 0)
        {
            FengwangCard *fw = new FengwangCard;
            fw->addSubcard(originalCard);
            fw->setSkillName(objectName());
            fw->setShowSkill(objectName());
            return fw;
        }
        return NULL;
    }
};

class FengwangTMS : public TargetModSkill
{
public:
    FengwangTMS() : TargetModSkill("#fengwang-target")
    {
        pattern = "Slash";
    }

    virtual int getDistanceLimit(const Player *from, const Card *) const
    {
        if (from->hasSkill("fengwang") && from->getPile("jian").length() > 0)
            return 1000;
        else
            return 0;
    }

    virtual int getExtraTargetNum(const Player *from, const Card *card) const
    {
        if (card->isKindOf("Slash") && !from->getPile("jian").isEmpty())
            return 1;
        else
            return 0;
    }
};

#include "json.h"
#include <QRegularExpression>
using namespace QSanProtocol;

class Fengwang : public TriggerSkill
{
public:
    Fengwang() : TriggerSkill("fengwang")
    {
        events << TargetChosen << FinishRetrial << SlashEffected << EventPhaseStart << SlashMissed << CardFinished;
        view_as_skill = new FengwangVS;
        frequency = Compulsory;
    }

    virtual QStringList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (event == TargetChosen)
        {
            CardUseStruct use = data.value<CardUseStruct>();
            if (TriggerSkill::triggerable(player) && use.card != NULL && use.card->isKindOf("Slash") && !use.to.isEmpty() && !player->getPile("jian").isEmpty())
            {
                if (use.index == 0)
                    foreach(ServerPlayer *p, use.to)
                        p->addQinggangTag(use.card);
                ServerPlayer *target = use.to.at(use.index);
                if (target != NULL)
                    return QStringList(objectName() + "->" + target->objectName());
            }
        }
        else if (event == FinishRetrial)
        {
            JudgeStruct *judge = data.value<JudgeStruct *>();
            if (TriggerSkill::triggerable(player) && !player->hasShownSkill(this) && player->getMark("@excalibur") > 0
                && judge->who == player && judge->card->isKindOf("Weapon"))
                return QStringList(objectName());
        }
        else if (event == SlashEffected)
        {
            SlashEffectStruct effect = data.value<SlashEffectStruct>();
            if (effect.slash->hasFlag("fengwang_nullified"))
                return QStringList(objectName());
        }
        else if (event == EventPhaseStart)
        {
            if (TriggerSkill::triggerable(player) && player->getPhase() == Player::Start && player->getWeapon() != NULL)
                return QStringList(objectName());
        }
        else if (event == SlashMissed)
        {
            if (TriggerSkill::triggerable(player))
            {
                auto effect = data.value<SlashEffectStruct>();
                if (effect.slash == NULL)
                    return QStringList();

                if (effect.to->hasFlag("fengwang_doubt_failed"))
                {
                    if (player->getPile("jian").isEmpty())
                        return QStringList();
                    int id = player->getPile("jian").first();
                    if (id != -1)
                    {
                        return QStringList(objectName());
                    }
                }
            }
        }
        else if (event == CardFinished)
        {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card != NULL && use.card->isKindOf("Slash"))
            {
                QRegularExpression re("fengwang.*");
                foreach (auto p, room->getAlivePlayers())
                {
                    foreach (auto flag, p->getFlagList())
                    {
                        if (re.match(flag).hasMatch())
                        {
                            p->setFlags("-" + flag);
                        }
                    }
                }
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
    {
        if (event == TargetChosen)
        {
            ask_who->tag["WushuangTarget"] = QVariant::fromValue(player); // for AI
            if (!ask_who->getPile("jian").isEmpty() && player->askForSkillInvoke(this, data))
            {
                room->broadcastSkillInvoke(objectName(), (qrand() % 2) + 1);
                return true;
            }
        }
        else if (event == SlashEffected)
        {
            room->broadcastSkillInvoke(objectName(), (qrand() % 2) + 2);
            return true;
        }
        else if (event == FinishRetrial)
        {
            return player->hasShownSkill(this) || player->askForSkillInvoke(this, data);
        }
        else if (event == EventPhaseStart)
        {
            return player->hasShownSkill(this) || player->askForSkillInvoke(this, data);
        }
        else if (event == SlashMissed)
        {
            room->broadcastSkillInvoke(objectName(), 4);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
    {
        if (event == TargetChosen)
        {
            CardUseStruct use = data.value<CardUseStruct>();
            if (ask_who->getPile("jian").isEmpty())
                return false;
            int id = ask_who->getPile("jian").first();
            room->notifyMoveFocus(player);
            JsonArray show_arg;
            show_arg << player->objectName();
            show_arg << id;

            WrappedCard *card = Sanguosha->getWrappedCard(id);
            bool modified = card->isModified();
            QList<ServerPlayer *>players;
            players << ask_who << player;
            if (modified)
                room->notifyUpdateCard(player, id, card);
            else
                room->notifyResetCard(player, id);
            room->doBroadcastNotify(players, S_COMMAND_SHOW_CARD, show_arg);

            const Card *jian = Sanguosha->getEngineCard(id);

            if (jian != NULL && jian->isKindOf("Weapon")
                && qobject_cast<const Weapon *>(jian->getRealCard())->getRange() >= ask_who->distanceTo(player))
            {
                LogMessage failLog;
                failLog.type = "#FengwangDoubtFailed";
                failLog.from = ask_who;
                failLog.to << player;
                failLog.arg = objectName();
                room->sendLog(failLog);

                player->setFlags("fengwang_doubt_failed");
                if (player->canDiscard(player, "he"))
                {
                    room->askForDiscard(player, objectName(), 1, 1, false, true, "@fengwang-doubt-discard", true);
                }
                int x = use.to.indexOf(player);
                QVariantList jink_list = ask_who->tag["Jink_" + use.card->toString()].toList();
                if (jink_list.at(x).toInt() == 1)
                    jink_list[x] = 2;
                ask_who->tag["Jink_" + use.card->toString()] = jink_list;
            }
            else
            {
                LogMessage successLog;
                successLog.type = "#FengwangDoubtSucceed";
                successLog.from = ask_who;
                successLog.to << player;
                successLog.arg = objectName();
                room->sendLog(successLog);
                use.card->setFlags("fengwang_nullified");

                ask_who->getPile("jian").removeOne(id);
                CardMoveReason reason(CardMoveReason::S_REASON_REMOVE_FROM_PILE, QString(), objectName(), QString());
                room->throwCard(jian, reason, NULL, player, objectName());
            }
        }
        else if (event == SlashEffected)
        {
            SlashEffectStruct effect = data.value<SlashEffectStruct>();
            LogMessage log;
            log.type = "#HalberdNullified";
            log.from = effect.from;
            log.to << effect.to;
            log.arg = objectName();
            log.arg2 = effect.slash->objectName();
            room->sendLog(log);
            return true;
        }
        else if (event == FinishRetrial)
        {
            JudgeStruct *judge = data.value<JudgeStruct *>();
            QList<const Card *> cards;
            cards << judge->card;
            room->filterCards(player, cards, true);
            judge->updateResult();
        }
        else if (event == EventPhaseStart)
        {
            WrappedCard *weapon = player->getWeapon();
            if (weapon != NULL)
            {
                CardMoveReason reason(CardMoveReason::S_REASON_THROW, player->objectName());
                room->moveCardTo(weapon, player, NULL, Player::PlaceTable, reason, true);
                QList<int> table_cardids = room->getCardIdsOnTable(weapon);
                if (!table_cardids.isEmpty())
                {
                    DummyCard dummy(table_cardids);
                    room->moveCardTo(&dummy, player, NULL, Player::DiscardPile, reason, true);
                }
            }
        }
        else if (event == SlashMissed)
        {
            if (player->getPile("jian").isEmpty())
                return false;

            int id = player->getPile("jian").first();
            if (id != -1)
            {
                SlashEffectStruct effect = data.value<SlashEffectStruct>();
                if (effect.slash != NULL)
                    effect.slash->setFlags("fengwang_nullified");

                player->getPile("jian").removeOne(id);
                CardMoveReason reason(CardMoveReason::S_REASON_REMOVE_FROM_PILE, QString(), objectName(), QString());
                room->throwCard(Sanguosha->getEngineCard(id), reason, NULL, player, objectName());
            }
        }

        return false;
    }
};

class Duangang : public TriggerSkill
{
public:
    Duangang() : TriggerSkill("duangang")
    {
        events << EventPhaseStart << Death << DamageCaused << Damage;
        frequency = Limited;
        limit_mark = "@excalibur";
    }

    virtual QStringList triggerable(TriggerEvent event, Room *, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (event == EventPhaseStart)
        {
            if (TriggerSkill::triggerable(player) && player->getPhase() == Player::Play && player->getMark("@excalibur") > 0)
            {
                player->tag["excalibur_count"] = 0;
                return QStringList(objectName());
            }
        }
        else if (event == DamageCaused)
        {
            if (player != NULL && player->hasFlag("excalibur") && player->isAlive())
                return QStringList(objectName());
        }
        else if (event == Death)
        {
            DeathStruct death = data.value<DeathStruct>();
            if (player != NULL && player->hasFlag("excalibur") && death.who != player)
            {
                player->tag["excalibur_count"] = 0;
                player->setFlags("-excalibur");
            }
        }
        else if (event == Damage && player != NULL)
        {
            DamageStruct damage = data.value<DamageStruct>();
            if (damage.from != NULL && damage.from->hasFlag("excalibur") && damage.from->getPhase() == Player::Play)
                damage.from->tag["excalibur_count"] = damage.from->tag["excalibur_count"].toInt() + damage.damage;
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (event == EventPhaseStart)
        {
            if (player->askForSkillInvoke(this, data))
            {
                room->broadcastSkillInvoke(objectName(), (qrand() % 3) + 1);
                room->removePlayerMark(player, "@excalibur");
                room->doSuperLightbox("altria", "Excalibur");
                return true;
            }
        }
        else if (event == DamageCaused)
        {
            room->broadcastSkillInvoke(objectName(), (qrand() % 2) + 4);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (event == EventPhaseStart)
        {
            room->setPlayerFlag(player, "excalibur");
        }
        else if (event == DamageCaused)
        {
            DamageStruct damage = data.value<DamageStruct>();
            LogMessage log;
            log.type = "#DuangangBuff";
            log.from = player;
            log.to << damage.to;
            log.arg = QString::number(damage.damage);
            damage.damage += player->tag["excalibur_count"].toInt();
            if (damage.damage == log.arg.toInt())
                return false;
            log.arg2 = QString::number(damage.damage);
            room->sendLog(log);

            data = QVariant::fromValue(damage);
        }
        return false;
    }
};

YonglanCard::YonglanCard()
{
    will_throw = false;
}

bool YonglanCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *) const
{
    Indulgence *indu = new Indulgence(Card::NoSuit, 0);
    indu->deleteLater();
    if (Self->isProhibited(to_select, indu))
        return false;
    return targets.isEmpty() && !to_select->containsTrick("indulgence") && Self->isFriendWith(to_select);
}

void YonglanCard::onEffect(const CardEffectStruct &effect) const
{
    if (subcards.length() == 1)
    {
        Indulgence *indu = new Indulgence(Card::SuitToBeDecided, -1);
        indu->addSubcards(subcards);
        indu->setSkillName("yonglan");
        Room *room = effect.from->getRoom();
        if (room->useCard(CardUseStruct(indu, effect.from, effect.to, true), true))
        {
            room->askForUseCard(effect.from, "@@yonglan", "@yonglan");
        }
    }
}

#include "roomthread.h"

YonglanPindianCard::YonglanPindianCard()
{
}

bool YonglanPindianCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *) const
{
    return targets.length() < 2 && !to_select->isKongcheng();
}

bool YonglanPindianCard::targetsFeasible(const QList<const Player *> &targets, const Player *) const
{
    return targets.length() == 2;
}

void YonglanPindianCard::onUse(Room *room, const CardUseStruct &card_use) const
{
    ServerPlayer *miki = card_use.from;

    LogMessage log;
    log.from = miki;
    log.to << card_use.to;
    log.type = "#UseCard";
    log.card_str = toString();
    room->sendLog(log);

    QVariant data = QVariant::fromValue(card_use);
    RoomThread *thread = room->getThread();

    thread->trigger(PreCardUsed, room, miki, data);
    room->broadcastSkillInvoke("yonglan", miki);

    CardMoveReason reason(CardMoveReason::S_REASON_THROW, miki->objectName(), QString(), "yonglan", QString());
    room->moveCardTo(this, miki, NULL, Player::PlaceTable, reason, true);

    if (miki->ownSkill("yonglan") && !miki->hasShownSkill("yonglan"))
        miki->showGeneral(miki->inHeadSkills("yonglan"));

    QList<int> table_ids = room->getCardIdsOnTable(this);
    if (!table_ids.isEmpty())
    {
        DummyCard dummy(table_ids);
        room->moveCardTo(&dummy, miki, NULL, Player::DiscardPile, reason, true);
    }

    thread->trigger(CardUsed, room, miki, data);
    thread->trigger(CardFinished, room, miki, data);
}

void YonglanPindianCard::use(Room *room, ServerPlayer *, QList<ServerPlayer *> &targets) const
{
    ServerPlayer *user = targets.at(0);
    ServerPlayer *victim = targets.at(1);
    ServerPlayer *winner = NULL;
    ServerPlayer *loser = NULL;

    PindianStruct *pd = user->pindianStruct(victim, "yonglan");
    if (pd != NULL)
    {
        if (pd->from_number > pd->to_number)
        {
            winner = pd->from;
            loser = pd->to;
        }
        else if (pd->to_number > pd->from_number)
        {
            winner = pd->to;
            loser = pd->from;
        }
        pd = NULL;
        if (winner != NULL && loser != NULL)
        {
            Duel *duel = new Duel(Card::NoSuit, 0);
            duel->setSkillName(QString("_%1").arg(getSkillName()));
            if (!winner->isCardLimited(duel, Card::MethodUse) && !winner->isProhibited(loser, duel))
                room->useCard(CardUseStruct(duel, winner, loser));
            else
            {
                LogMessage log;
                log.type = "#YonglanNullified";
                log.from = winner;
                log.arg = winner->objectName();
                delete duel;
            }
        }
    }
}

class Yonglan : public ViewAsSkill
{
public:
    Yonglan() : ViewAsSkill("yonglan")
    {
    }

    virtual bool viewFilter(const QList<const Card *> &selected, const Card *to_select) const
    {
        return !to_select->isEquipped() && Sanguosha->currentRoomState()->getCurrentCardUsePattern() == "@@yonglan" ? false : selected.length() == 0;
    }

    virtual bool isEnabledAtResponse(const Player *, const QString &pattern) const
    {
        return pattern == "@@yonglan";
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return player->getHandcardNum() + player->getPile("wooden_ox").length() > 0;
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (Sanguosha->currentRoomState()->getCurrentCardUsePattern() == "@@yonglan" && cards.length() == 0)
        {
            YonglanPindianCard *pd = new YonglanPindianCard;
            pd->setShowSkill(objectName());
            return pd;
        }
        else if (cards.length() == 1)
        {
            YonglanCard *yl = new YonglanCard;
            yl->addSubcards(cards);
            yl->setShowSkill(objectName());
            return yl;
        }
        return NULL;
    }
};

class ZhiyanMiki : public TriggerSkill
{
public:
    ZhiyanMiki() : TriggerSkill("zhiyanmiki")
    {
        events << EventPhaseSkipping << EventPhaseStart;
        frequency = Compulsory;
    }

    virtual void record(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &) const
    {
        if (event == EventPhaseSkipping)
        {
            if (player != NULL && player->isAlive())
            {
                room->setPlayerFlag(player, "zhiyanmiki_skip");
            }
        }
    }

    virtual QStringList triggerable(TriggerEvent event, Room *, ServerPlayer *player, QVariant &, ServerPlayer* &) const
    {
        if (event == EventPhaseStart)
        {
            if (TriggerSkill::triggerable(player) && player->hasFlag("zhiyanmiki_skip") && player->getPhase() == Player::Finish)
            {
                return QStringList(objectName());
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->hasShownSkill(this) || player->askForSkillInvoke(this))
        {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        LogMessage log;
        QString choice = "draw";
        QList<ServerPlayer *> targets;
        foreach (ServerPlayer *p, room->getAlivePlayers())
            if (player->canDiscard(p, "hej"))
                targets << p;
        if (!targets.isEmpty())
            choice += "+discard";
        if (room->askForChoice(player, objectName(), choice) == "draw")
        {
            log.type = "#ZhiyanMikiDraw";
            log.from = player;
            log.arg = objectName();
            player->drawCards(1, objectName());
        }
        else
        {
            ServerPlayer *target = room->askForPlayerChosen(player, targets, objectName());
            if (target != NULL)
            {
                room->throwCard(room->askForCardChosen(player, target, "hej", objectName(), false, Card::MethodDiscard), target, player, objectName());
                log.type = "#ZhiyanMikiDiscard";
                log.from = player;
                log.to << target;
                log.arg = objectName();
            }
        }
        room->sendLog(log);
        return false;
    }
};

class Yetian : public TriggerSkill
{
public:
    Yetian() : TriggerSkill("yetian")
    {
        events << CardUsed << CardsMoveOneTime << EventPhaseStart;
        frequency = Compulsory;
    }

    virtual void record(TriggerEvent event, Room *room, ServerPlayer *, QVariant &data) const
    {
        if (event == CardUsed)
        {
            CardUseStruct use = data.value<CardUseStruct>();
            const Card *card = room->getTag("NullifyingCard").value<const Card *>();
            auto yetian = room->getTag("yetian").value<QPair<const Card *, ServerPlayer *>>();
            if (use.from != NULL && use.card->isKindOf("Nullification") && card != NULL && card->isNDTrick() && yetian.first != card && card->subcardsLength() == 1)
            {
                yetian = qMakePair(card, use.from);
                room->setTag("yetian", QVariant::fromValue(yetian));
            }
        }
    }

    virtual QStringList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer* &) const
    {
        if (!TriggerSkill::triggerable(player))
            return QStringList();

        if (event == CardsMoveOneTime)
        {
            CardsMoveOneTimeStruct move = data.value<CardsMoveOneTimeStruct>();
            if (move.from != NULL && move.to_place == Player::DiscardPile && move.card_ids.length() > 0
                && ((move.reason.m_reason & CardMoveReason::S_MASK_BASIC_REASON) == CardMoveReason::S_REASON_USE)
                && move.from_places.contains(Player::PlaceTable))
            {
                auto yetian = room->getTag("yetian").value<QPair<const Card *, ServerPlayer *>>();
                if (yetian.second != player)
                    return QStringList();
                auto yetians = yetian.first->getSubcards();
                if (move.card_ids.contains(yetians.first()))
                {
                    room->removeTag("yetian");
                    player->tag["yetian_ids"] = QVariant::fromValue(yetians);
                    return QStringList(objectName());
                }
            }
        }
        else if (event == EventPhaseStart)
        {
            if (player->getPhase() == Player::Start && (player->getHandcardNum() == 0 || player->getPile("book").length() > 0))
                return QStringList(objectName());
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (event == CardsMoveOneTime)
        {
            QList<int> ids = player->tag["yetian_ids"].value<QList<int>>();
            if (player->askForSkillInvoke(this))
            {
                player->tag["yetian_current_id"] = ids.first();
                ids.removeFirst();
                player->tag["yetian_ids"] = QVariant::fromValue(ids);
                room->broadcastSkillInvoke(objectName());
                return true;
            }
            player->tag["yetian_ids"].clear();
        }
        else if (player->hasShownSkill(this) || player->askForSkillInvoke(this))
        {
            room->broadcastSkillInvoke(objectName());
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (event == CardsMoveOneTime)
        {
            bool canConvert = false;
            int id = player->tag["yetian_current_id"].toInt(&canConvert);
            if (canConvert && id != -1)
            {
                player->addToPile("book", id, true);
            }

            player->tag["yetian_current_id"] = NULL;
        }
        else
        {
            if (player->getHandcardNum() == 0)
                room->loseHp(player, 1);

            auto books = player->getPile("book");
            if (books.length() > 0)
            {
                DummyCard dummy(books);
                player->obtainCard(&dummy, true);
            }
        }
        return false;
    }
};

TianjianCard::TianjianCard()
{
    will_throw = false;
}

bool TianjianCard::targetFixed() const
{
    Card *mutable_card = Sanguosha->cloneCard(getUserString());
    if (mutable_card)
    {
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }
    return mutable_card && mutable_card->targetFixed();
}

bool TianjianCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->tag["tianjian"].toString());
    if (mutable_card)
    {
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }

    return mutable_card && mutable_card->targetFilter(targets, to_select, Self) && !Self->isProhibited(to_select, mutable_card, targets);
}

bool TianjianCard::targetsFeasible(const QList<const Player *> &targets, const Player *Self) const
{
    Card *mutable_card = Sanguosha->cloneCard(Self->tag["tianjian"].toString());
    if (mutable_card)
    {
        mutable_card->setCanRecast(false);
        mutable_card->deleteLater();
    }

    return mutable_card && mutable_card->targetsFeasible(targets, Self);
}

const Card *TianjianCard::validate(CardUseStruct &card_use) const
{
    Card *use_card = Sanguosha->cloneCard(toString().split(":").last(), Card::NoSuit, 0);
    auto source = card_use.from;
    auto room = source->getRoom();

    if (use_card == NULL)
        return NULL;

    use_card->addSubcards(subcards);
    if (subcardsLength() == 0)
        use_card->setSkillName("tianjianturn");
    else
        use_card->setSkillName("tianjian");
    use_card->setShowSkill("tianjian");
    use_card->setCanRecast(false);
    bool available = true;

    QList<ServerPlayer *> targets;
    if (use_card->isKindOf("AwaitExhausted"))
    {
        foreach(ServerPlayer *p, room->getAlivePlayers())
            if (!source->isProhibited(p, use_card) && source->isFriendWith(p))
                targets << p;
    }
    else if (use_card->getSubtype() == "global_effect" && !use_card->isKindOf("FightTogether"))
    {
        foreach(ServerPlayer *p, room->getAlivePlayers())
            if (!source->isProhibited(p, use_card))
                targets << p;
    }
    else if (use_card->isKindOf("FightTogether"))
    {
        QStringList big_kingdoms = source->getBigKingdoms("tianjian", MaxCardsType::Normal);
        QList<ServerPlayer *> bigs, smalls;
        foreach(ServerPlayer *p, room->getAllPlayers())
        {
            if (source->isProhibited(p, use_card)) continue;
            QString kingdom = p->objectName();
            if (big_kingdoms.length() == 1 && big_kingdoms.first().startsWith("sgs"))
            { // for JadeSeal
                if (big_kingdoms.contains(kingdom))
                    bigs << p;
                else
                    smalls << p;
            }
            else
            {
                if (!p->hasShownOneGeneral())
                {
                    smalls << p;
                    continue;
                }
                if (p->getRole() == "careerist")
                    kingdom = "careerist";
                else
                    kingdom = p->getKingdom();
                if (big_kingdoms.contains(kingdom))
                    bigs << p;
                else
                    smalls << p;
            }
        }
        if ((smalls.length() > 0 && smalls.length() < bigs.length() && bigs.length() > 0) || (smalls.length() > 0 && bigs.length() == 0))
            targets = smalls;
        else if ((smalls.length() > 0 && smalls.length() > bigs.length() && bigs.length() > 0) || (smalls.length() == 0 && bigs.length() > 0))
            targets = bigs;
        else if (smalls.length() == bigs.length())
            targets = smalls;
    }
    else if (use_card->getSubtype() == "aoe" && !use_card->isKindOf("BurningCamps"))
    {
        foreach(ServerPlayer *p, room->getOtherPlayers(source))
            if (!source->isProhibited(p, use_card))
                targets << p;
    }
    else if (use_card->isKindOf("BurningCamps"))
    {
        QList<const Player *> players = source->getNextAlive()->getFormation();
        foreach(const Player *p, players)
            if (!source->isProhibited(p, use_card))
                targets << room->findPlayerbyobjectName(p->objectName());
    }

    foreach(ServerPlayer *to, card_use.to)
    {
        if (source->isProhibited(to, use_card))
        {
            available = false;
            break;
        }
    }

    available = available && use_card->isAvailable(source);

    if (!available)
        return NULL;

    room->setPlayerFlag(source, "tianjian_used");

    return use_card;
}

class TianjianVS : public ViewAsSkill
{
public:
    TianjianVS() : ViewAsSkill("tianjian")
    {
        response_pattern = "nullification";
        response_or_use = true;
    }

    virtual bool viewFilter(const QList<const Card *> &, const Card *to_select) const
    {
        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (cards.length() >= qMax(Self->getHandcardNum(), 1) || (Self->faceUp() && cards.length() == 0))
        {
            QString userstring = Self->tag["tianjian"].toString();
            QString skillName = objectName();
            if (Sanguosha->currentRoomState()->getCurrentCardUsePattern() == "nullification")
            {
                Nullification *nulli = new Nullification(Card::NoSuit, 0);
                if (cards.length() > 0)
                    nulli->addSubcards(cards);
                else
                    skillName += "turn";
                nulli->setSkillName(skillName);
                nulli->setShowSkill(objectName());
                return nulli;
            }
            else if (!userstring.isNull() && !userstring.isEmpty())
            {
                TianjianCard *tcard = new TianjianCard;
                if (cards.length() > 0)
                    tcard->addSubcards(cards);
                tcard->setUserString(userstring);
                tcard->setSkillName(skillName);
                tcard->setShowSkill(objectName());
                return tcard;
            }
        }
        return NULL;
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return !player->hasFlag("tianjian_used") && !player->isRemoved() && (player->faceUp() || !player->isKongcheng());
    }

    virtual bool isEnabledAtNullification(const ServerPlayer *player) const
    {
        return !player->hasFlag("tianjian_used") && !player->isRemoved() && (player->faceUp() || !player->isKongcheng());
    }
};

class Tianjian : public TriggerSkill
{
public:
    Tianjian() : TriggerSkill("tianjian")
    {
        events << EventPhaseChanging << PreCardUsed;
        guhuo_type = "t";
        view_as_skill = new TianjianVS;
    }

    virtual void record(TriggerEvent event, Room *room, ServerPlayer *, QVariant &data) const
    {
        if (event == EventPhaseChanging)
        {
            auto change = data.value<PhaseChangeStruct>();
            if (change.to == Player::NotActive)
            {
                foreach (auto p, room->getAlivePlayers())
                {
                    if (p->hasFlag("tianjian_used"))
                    {
                        room->setPlayerFlag(p, "-tianjian_used");
                    }
                }
            }
        }
        else if (event == PreCardUsed)
        {
            auto use = data.value<CardUseStruct>();
            if (use.card != NULL && use.from != NULL && (use.card->getSkillName() == "tianjianturn" || use.card->getSkillName() == "tianjian"))
            {
                room->setPlayerFlag(use.from, "tianjian_used");
                if (use.card->getSkillName() == "tianjianturn")
                    use.from->turnOver();
            }
        }
    }

    virtual QStringList triggerable(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer* &) const
    {
        return QStringList();
    }
};

class GuiyuanFilter : public FilterSkill
{
public:
    GuiyuanFilter() : FilterSkill("#guiyuan-filter")
    {
    }

    virtual bool viewFilter(const Card *to_select, ServerPlayer *player) const
    {
        if (player == NULL || player->isDead() || to_select == NULL)
            return false;

        if (player->getMark("guiyuan_bool") == 1)
        {
            QString guiyuan_type1 = player->getRoom()->getTag("guiyuan_type1").value<QString>();
            QString guiyuan_type2 = player->getRoom()->getTag("guiyuan_type2").value<QString>();

            if (guiyuan_type1.isNull() || guiyuan_type1.isEmpty() || guiyuan_type2.isNull() || guiyuan_type2.isEmpty() || guiyuan_type1 == guiyuan_type2)
                return false;

            auto card = Sanguosha->getEngineCard(to_select->getEffectiveId());

            if (guiyuan_type1 == "slash")
                return card->isKindOf("Slash") || card->isKindOf(guiyuan_type2.toLatin1().constData());
            if (guiyuan_type2 == "slash")
                return card->isKindOf("Slash") || card->isKindOf(guiyuan_type1.toLatin1().constData());

            return card->isKindOf(guiyuan_type1.toLatin1()) || card->isKindOf(guiyuan_type2.toLatin1());
        }
        return false;
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        auto engineCard = Sanguosha->getEngineCard(originalCard->getEffectiveId());
        if (engineCard == NULL || engineCard->isVirtualCard() || originalCard->getSkillName() == "guiyuan")
            return originalCard;

        auto room = Sanguosha->currentRoom();
        QString guiyuan_type1 = room->getTag("guiyuan_type1").value<QString>();
        QString guiyuan_type2 = room->getTag("guiyuan_type2").value<QString>();

        QString guiyuan_type;
        if ((guiyuan_type1 == "slash" && engineCard->isKindOf("Slash")) || engineCard->isKindOf(guiyuan_type1.toLatin1().constData()))
            guiyuan_type = guiyuan_type2;
        if ((guiyuan_type2 == "slash" && engineCard->isKindOf("Slash")) || engineCard->isKindOf(guiyuan_type2.toLatin1().constData()))
            guiyuan_type = guiyuan_type1;

        if (guiyuan_type.isNull() || guiyuan_type.isEmpty())
            return originalCard;

        WrappedCard *new_card = Sanguosha->getWrappedCard(originalCard->getEffectiveId());
        Card *card = Sanguosha->cloneCard(guiyuan_type, originalCard->getSuit(), originalCard->getNumber());
        new_card->setSkillName("guiyuan");
        new_card->setModified(true);
        new_card->takeOver(card);
        return new_card;
    }

    virtual int getEffectIndex(const ServerPlayer *, const Card *) const
    {
        return -2;
    }
};

class Guiyuan : public TriggerSkill
{
public:
    Guiyuan() : TriggerSkill("guiyuan")
    {
        events << EventPhaseStart << EventPhaseChanging << CardsMoveOneTime;
    }

    virtual void record(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data) const
    {
        if (event == EventPhaseChanging)
        {
            if (data.value<PhaseChangeStruct>().to == Player::NotActive)
            {
                foreach(ServerPlayer *p, room->getAlivePlayers())
                {
                    if (p->getMark("guiyuan_bool") > 0)
                    {
                        room->filterCards(p, p->getHandcards(), true);
                        room->setPlayerMark(p, "guiyuan_bool", 0);
                    }
                }
            }
        }
        else if (event == CardsMoveOneTime)
        {
            if (player != NULL && !player->isKongcheng())
            {
                room->filterCards(player, player->getHandcards(), true);
            }
        }
    }

    virtual TriggerList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &) const
    {
        TriggerList skill_list;
        if (player == NULL)
            return skill_list;
        if (event == EventPhaseStart)
        {
            if (player->getPhase() == Player::Start)
            {
                QList<ServerPlayer *> rikas = room->findPlayersBySkillName(objectName());
                foreach (ServerPlayer *rika, rikas)
                    if (player != rika && !player->isChained() && !rika->isChained() && player->canBeChainedBy(rika) && rika->canBeChainedBy(rika))
                        skill_list.insert(rika, QStringList(objectName()));
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        if (ask_who->askForSkillInvoke(this))
        {
            room->setPlayerProperty(ask_who, "chained", true);
            room->setPlayerProperty(player, "chained", true);
            room->broadcastSkillInvoke(objectName(), 1);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        QString card1;
        QString card2;
        QList<const BasicCard*> basics = Sanguosha->findChildren<const BasicCard*>();
        QStringList basicName;
        foreach (const BasicCard *basic, basics)
        {
            if (!ServerInfo.Extensions.contains("!" + basic->getPackage()))
            {
                bool willAddThis = true;
                foreach(QString name, basicName)
                {
                    if (basic->isKindOf(name.toLatin1().constData()))
                    {
                        willAddThis = false;
                    }
                }

                if (willAddThis)
                {
                    basicName << basic->getClassName();
                }
            }
        }

        if (basicName.length() > 1)
        {
            card1 = room->askForChoice(ask_who, objectName(), basicName.join("+"));
            basicName.removeOne(card1);
            card2 = room->askForChoice(ask_who, objectName(), basicName.join("+"));

            if (card1.isNull() || card1.isEmpty() || card2.isNull() || card2.isEmpty())
                return false;

            room->setTag("guiyuan_type1", card1);
            room->setTag("guiyuan_type2", card2);
            room->setPlayerMark(player, "guiyuan_bool", 1);

            LogMessage log;
            log.type = "#GuiyuanSwapEffect";
            log.from = ask_who;
            log.to << player;
            log.arg = "guiyuan:" + card1;
            log.arg2 = "guiyuan:" + card2;

            // minagoroshi and matsubayashi
            QString choices;
            choices = "cancel";
            if (ask_who->getMark("minagoroshi") == 0)
                choices += "+minagoroshi";
            if (ask_who->getMark("matsubayashi") == 0)
                choices += "+matsubayashi";

            QString choice = room->askForChoice(ask_who, objectName(), choices);
            if (choice == "minagoroshi")
            {
                room->setPlayerMark(ask_who, choice, 1);
                foreach(ServerPlayer *p, room->getAlivePlayers())
                {
                    room->setPlayerMark(p, "guiyuan_bool", 1);
                    if (!log.to.contains(p))
                        log.to << p;
                }
            }
            else if (choice == "matsubayashi")
            {
                room->setPlayerMark(ask_who, choice, 1);
                foreach(ServerPlayer *p, room->getAlivePlayers())
                {
                    if (p->isChained())
                    {
                        room->setPlayerMark(p, "guiyuan_bool", 1);
                        if (!log.to.contains(p))
                            log.to << p;
                    }
                }
            }

            room->sendLog(log);
        }

        return false;
    }
};

class Zuimie : public TriggerSkill
{
public:
    Zuimie() : TriggerSkill("zuimie")
    {
        events << CardUsed << EventPhaseChanging;
    }

    virtual void record(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data) const
    {            
        if (player == NULL)
            return;
        if (event == EventPhaseChanging)
        {
            auto change = data.value<PhaseChangeStruct>();
            if (change.to == Player::NotActive && player->hasFlag("zuimie_turn"))
            {
                room->setPlayerMark(player, "Equips_Nullified_to_Yourself", qMax(0, player->getMark("Equips_Nullified_to_Yourself") - 1));
                player->setFlags("-zuimie_turn");
            }
        }
    }

    virtual TriggerList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (player == NULL || !player->isAlive())
            return skill_list;
        if (event == CardUsed)
        {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card != NULL && use.card->isKindOf("Slash"))
            {
                foreach (ServerPlayer *rika, room->findPlayersBySkillName(objectName()))
                {
                    if (rika->canBeChainedBy(rika) && rika->isChained())
                        skill_list.insert(rika, QStringList(objectName()));
                }
            }
        }
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        if (room->askForSkillInvoke(ask_who, objectName(), qVariantFromValue(player)))
        {
            room->setPlayerProperty(ask_who, "chained", false);
            room->broadcastSkillInvoke(objectName());
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        room->setPlayerMark(player, "Equips_Nullified_to_Yourself", player->getMark("Equips_Nullified_to_Yourself") + 1);
        player->setFlags("zuimie_turn");
        return false;
    }
};

class Gaoling : public MaxCardsSkill
{
public:
    Gaoling() : MaxCardsSkill("gaoling")
    {
    }

    virtual int getExtra(const ServerPlayer *target, MaxCardsType::MaxCardsCount) const
    {
        if (target->hasShownSkill(this))
            return 2 * target->getLostHp();
        return 0;
    }
};

class ChouchuVS : public OneCardViewAsSkill
{
public:
    ChouchuVS() : OneCardViewAsSkill("chouchu")
    {
        response_or_use = true;
    }

    virtual bool isEnabledAtPlay(const Player *) const
    {
        return false;
    }

    virtual bool isEnabledAtResponse(const Player *player, const QString &pattern) const
    {
        return player->getHandcardNum() && (player->getHandcardNum() % 2) == 1 && pattern == "jink";
    }

    virtual bool viewFilter(const Card *) const
    {
        return true;
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        Jink *jink = new Jink(originalCard->getSuit(), originalCard->getNumber());
        jink->addSubcard(originalCard->getId());
        jink->setSkillName(objectName());
        jink->setShowSkill(objectName());
        return jink;
    }

};

class Chouchu : public TriggerSkill
{
public:
    Chouchu() : TriggerSkill("chouchu")
    {
        events << Damaged;
        view_as_skill = new ChouchuVS;
    }

    virtual TriggerList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList skill_list;
        if (player == NULL) return skill_list;
        DamageStruct damage = data.value<DamageStruct>();
        if (damage.card == NULL || !damage.card->isKindOf("Slash") || damage.to == NULL || damage.to->isDead())
            return skill_list;
        QList<ServerPlayer *> setsunas = room->findPlayersBySkillName(objectName());
        foreach (ServerPlayer *setsuna, setsunas)
            if (setsuna->getHandcardNum() > 0 && setsuna->getHandcardNum() % 2 == 0 && setsuna->canDiscard(setsuna, "h"))
                skill_list.insert(setsuna, QStringList(objectName()));
        return skill_list;
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *ask_who) const
    {
        if (room->askForCard(ask_who, ".|red|.|hand", "@chouchu-discard", QVariant(), Card::MethodDiscard) != NULL)
        {
            room->broadcastSkillInvoke(objectName());
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        QStringList choices;
        if (player->getHandcardNum() < 3)
            choices << "supplementcards";
        if (player->isWounded())
            choices << "recover";

        if (choices.isEmpty())
            return false;

        QString choice = room->askForChoice(player, objectName(), choices.join("+"));

        if (choice.isNull() || choice.isEmpty())
            return false;

        if (choice == "supplementcards")
        {
            if (player->getHandcardNum() < 3)
                player->drawCards(3 - player->getHandcardNum());
        }
        else if (choice == "recover")
        {
            RecoverStruct recover;
            recover.who = ask_who;
            recover.recover = 1;
            room->recover(player, recover);
        }

        LogMessage log;
        log.type = "#Chouchu" + choice;
        log.from = ask_who;
        log.to << player;
        log.arg = objectName();
        room->sendLog(log);

        return false;
    }
};

class Bingshan : public DistanceSkill
{
public:
    Bingshan() : DistanceSkill("bingshan")
    {
    }

    virtual int getCorrect(const Player *, const Player *to) const
    {
        if (to->hasShownSkill(this))
            return to->getLostHp();
        return 0;
    }
};

ShenaiCard::ShenaiCard()
{
    will_throw = true;
}

bool ShenaiCard::targetFilter(const QList<const Player *> &, const Player *to_select, const Player *Self) const
{
    if (subcardsLength() == to_select->distanceTo(Self) / 2)
        return to_select != Self;
    return false;
}

void ShenaiCard::use(Room *, ServerPlayer *source, QList<ServerPlayer *> &targets) const
{
    ServerPlayer *target = targets.first();
    target->drawCards(qMin(5, target->distanceTo(source)), "shenai");
}

class Shenai : public ViewAsSkill
{
public:
    Shenai() : ViewAsSkill("shenai")
    {
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        return !player->hasUsed("ShenaiCard");
    }

    virtual bool viewFilter(const QList<const Card *> &, const Card *) const
    {
        return true;
    }

    virtual const Card *viewAs(const QList<const Card *> &cards) const
    {
        if (cards.length() > 0)
        {
            ShenaiCard *card = new ShenaiCard;
            card->setShowSkill(objectName());
            card->setSkillName(objectName());
            card->addSubcards(cards);
            return card;
        }
        return NULL;
    }
};

class Guangyu : public TriggerSkill
{
public:
    Guangyu() : TriggerSkill("guangyu")
    {
        events << CardsMoveOneTime << EventPhaseStart;
    }

    virtual TriggerList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data) const
    {
        TriggerList list;
        if (event == CardsMoveOneTime)
        {
            CardsMoveOneTimeStruct move = data.value<CardsMoveOneTimeStruct>();
            if (move.from != NULL && TriggerSkill::triggerable(player) && player == move.from
                && ((move.reason.m_reason & CardMoveReason::S_MASK_BASIC_REASON) == CardMoveReason::S_REASON_DISCARD)
                && move.to_place == Player::DiscardPile)
            {
                foreach (int id, move.card_ids)
                {
                    if (id != -1 && Sanguosha->getCard(id) && Sanguosha->getCard(id)->getSuit() == Card::Heart)
                    {
                        bool invoke = false;
                        Key *key = new Key(Card::Heart, Sanguosha->getCard(id)->getNumber());
                        QList<const Player *> empty;
                        foreach (ServerPlayer *p, room->getAlivePlayers())
                        {
                            if (key->targetFilter(empty, p, player))
                            {
                                invoke = true;
                                break;
                            }
                        }
                        if (invoke)
                        {
                            list.insert(player, QStringList(objectName()));
                        }
                    }
                }
            }
        }
        else if (event == EventPhaseStart)
        {
            if (player->getPhase() == Player::Judge)
            {
                QList<const Card *> judges = player->getJudgingArea();
                bool thereis = false;
                foreach (const Card *card, judges)
                {
                    if (card->isKindOf("Key"))
                    {
                        thereis = true;
                        break;
                    }
                }
                if (thereis)
                {
                    foreach (ServerPlayer *nagisa, room->findPlayersBySkillName(objectName()))
                        list.insert(nagisa, QStringList(objectName()));
                }
            }
        }
        return list;
    }

    virtual bool cost(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *ask_who) const
    {
        if (event == CardsMoveOneTime)
        {
            if (player->askForSkillInvoke(this))
            {
                room->broadcastSkillInvoke(objectName());
                return true;
            }
        }
        else if (event == EventPhaseStart)
        {
            if (ask_who->askForSkillInvoke(this, qVariantFromValue(player)))
            {
                DummyCard dummy(player->getJudgingAreaID());
                CardMoveReason reason(CardMoveReason::S_REASON_PUT, ask_who->objectName());
                room->throwCard(&dummy, reason, NULL, ask_who);
                room->broadcastSkillInvoke(objectName(), ask_who);
                return true;
            }
        }
        return false;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (event == CardsMoveOneTime)
        {
            CardsMoveOneTimeStruct move = data.value<CardsMoveOneTimeStruct>();
            foreach (int id, move.card_ids)
            {
                if (id != -1 && Sanguosha->getCard(id) && Sanguosha->getCard(id)->getSuit() == Card::Heart)
                {
                    Key *key = new Key(Card::Heart, Sanguosha->getCard(id)->getNumber());
                    QList<const Player *> empty;
                    QList<ServerPlayer *> can_put;
                    foreach (ServerPlayer *p, room->getAlivePlayers())
                    {
                        if (key->targetFilter(empty, p, player))
                            can_put << p;
                    }
                    if (can_put.length() == 0)
                        return false;
                    putKeyFromId(room, id, player, room->askForPlayerChosen(player, can_put, objectName(), "@guangyu-put"), objectName());
                }
            }
        }
        else if (event == EventPhaseStart)
        {
            return false;
        }
        return false;
    }
};

class Yunzhu : public TriggerSkill
{
public:
    Yunzhu() : TriggerSkill("yunzhu")
    {
        events << HpRecover;
    }

    virtual QStringList triggerable(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (TriggerSkill::triggerable(player))
        {
            QList<ServerPlayer *> friends;
            foreach (ServerPlayer *p, room->getOtherPlayers(player))
            {
                if (player->willBeFriendWith(p))
                    friends << p;
            }

            if (friends.isEmpty()) return QStringList();

            QStringList trigger_list;
            RecoverStruct recover = data.value<RecoverStruct>();
            for (int i = 1; i <= recover.recover; i++)
            {
                trigger_list << objectName();
            }

            return trigger_list;
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QList<ServerPlayer *> friends;
        foreach (ServerPlayer *p, room->getOtherPlayers(player))
        {
            if (player->willBeFriendWith(p))
                friends << p;
        }

        if (friends.isEmpty()) return false;
        ServerPlayer *target = room->askForPlayerChosen(player, friends, objectName(), "yunzhu-invoke", true, true);
        if (target != NULL)
        {
            room->broadcastSkillInvoke(objectName(), player);

            QStringList target_list = player->tag["yunzhu_target"].toStringList();
            target_list.append(target->objectName());
            player->tag["yunzhu_target"] = target_list;

            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        QStringList target_list = player->tag["yunzhu_target"].toStringList();
        QString target_name = target_list.last();
        target_list.removeLast();
        player->tag["yunzhu_target"] = target_list;

        ServerPlayer *to = NULL;

        foreach (ServerPlayer *p, player->getRoom()->getPlayers())
        {
            if (p->objectName() == target_name)
            {
                to = p;
                break;
            }
        }
        if (to != NULL)
            to->drawCards(1);
        return false;
    }
};

QiangqiCard::QiangqiCard()
{
}

bool QiangqiCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    Slash *slash = new Slash(Card::NoSuit, 0);
    slash->setSkillName("qiangqi");
    slash->deleteLater();
    return slash->targetFilter(targets, to_select, Self);
}

const Card *QiangqiCard::validate(CardUseStruct &use) const
{
    Room *room = use.from->getRoom();
    Card *card = Sanguosha->getCard(getSubcards().first());
    putKeyFromId(room, card->getEffectiveId(), use.from, use.from, "qiangqi");
    Slash *slash = new Slash(Card::NoSuit, 0);
    slash->setSkillName("qiangqi");
    slash->setShowSkill("qiangqi");
    return slash;
}

class QiangqiVS : public OneCardViewAsSkill
{
public:
    QiangqiVS() : OneCardViewAsSkill("qiangqi")
    {
        filter_pattern = "Slash|spade,club,diamond|.|hand";
    }

    virtual bool isEnabledAtPlay(const Player *player) const
    {
        Key *key = new Key(Card::NoSuit, 0);
        const QList<const Player *> empty;
        key->deleteLater();
        return key->targetFilter(empty, player, player);
    }

    virtual const Card *viewAs(const Card *originalCard) const
    {
        QiangqiCard *card = new QiangqiCard();
        card->addSubcard(originalCard);
        card->setShowSkill(objectName());
        return card;
    }
};

class Qiangqi : public TriggerSkill
{
public:
    Qiangqi() : TriggerSkill("qiangqi")
    {
        events << PreCardUsed;
        view_as_skill = new QiangqiVS;
    }

    virtual QStringList triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (triggerEvent == PreCardUsed)
        {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.card != NULL && use.card->getSkillName() == "qiangqi" && use.from != NULL)
            {
                room->addPlayerHistory(player, use.card->getClassName(), -1);
                use.m_addHistory = false;
                data = QVariant::fromValue(use);
            }
        }
        return QStringList();
    }

};

class Lianji : public TriggerSkill
{
public:
    Lianji() : TriggerSkill("lianji")
    {
        events << EventPhaseStart << Damage << TargetChosen << SlashMissed;
    }

    virtual QStringList triggerable(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &) const
    {
        if (!TriggerSkill::triggerable(player))
            return QStringList();
        if (event == TargetChosen)
        {
            CardUseStruct use = data.value<CardUseStruct>();
            if (use.from == NULL || use.from != player || use.index != 0)
                return QStringList();
            if (player->hasFlag("lianji_hengsao"))
            {
                if (use.card != NULL && use.card->isKindOf("Slash") && use.to.length() == 1)
                    use.card->setFlags("lianji_hengsao");
            }
        }
        else if (event == EventPhaseStart)
        {
            if (player->getPhase() == Player::Start)
                return QStringList(objectName());
        }
        else if (event == Damage)
        {
            DamageStruct damage = data.value<DamageStruct>();
            if (damage.from != NULL && damage.from == player && damage.card->isKindOf("Slash") && player->hasFlag("lianji_hengsao")
                && damage.card->hasFlag("lianji_hengsao") && !player->isAllNude() && !(damage.transfer || damage.chain || damage.prevented || damage.damage < 1))
            {
                bool pass = false;
                Slash *slash = new Slash(Card::NoSuit, 0);
                slash->setFlags("slashNoDistanceLimit");
                slash->deleteLater();
                QList<const Player*> empty;
                bool ok = false;
                if (slash->isAvailable(player))
                {
                    if (player->hasWeapon("Crossbow") || player->canSlashWithoutCrossbow(slash))
                        ok = true;

                    if (!ok)
                    {
                        QStringList assignee_list = player->property("extra_slash_specific_assignee").toString().split("+");
                        if (!assignee_list.isEmpty()) {
                            foreach(const Player *p, player->getAliveSiblings())
                            {
                                if (assignee_list.contains(p->objectName()) && player->canSlash(p, slash))
                                {
                                    ok = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (ok)
                {
                    foreach(ServerPlayer *p, room->getOtherPlayers(damage.to))
                    {
                        if (!player->isProhibited(p, slash, empty) && player->canSlash(p, false, 0, empty))
                        {
                            pass = true;
                            break;
                        }
                    }
                }
                return (ok && pass) ? QStringList(objectName()) : QStringList();
            }
        }
        else if (event == SlashMissed)
        {
            SlashEffectStruct effect = data.value<SlashEffectStruct>();
            if (effect.from && effect.from == player && player->hasFlag("lianji_lianti") && !player->isAllNude())
            {
                bool pass = false;
                Slash *slash = new Slash(Card::NoSuit, 0);
                slash->deleteLater();
                QList<const Player*> empty;
                if (!slash->isAvailable(player))
                    return QStringList();
                foreach (ServerPlayer *p, room->getOtherPlayers(effect.to))
                {
                    if (slash->targetFilter(empty, p, player) && player->canSlash(p, true, 0, empty))
                    {
                        pass = true;
                        break;
                    }
                }
                return pass ? QStringList(objectName()) : QStringList();
            }
        }
        return QStringList();
    }

    virtual bool cost(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
        if (player->askForSkillInvoke(this))
        {
            room->broadcastSkillInvoke(objectName(), player);
            return true;
        }
        return false;
    }

    virtual bool effect(TriggerEvent event, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *) const
    {
        if (event == EventPhaseStart)
        {
            QString choice = room->askForChoice(player, objectName(), "lianti+hengsao");
            if (choice == "lianti")
                player->setFlags("lianji_lianti");
            if (choice == "hengsao")
                player->setFlags("lianji_hengsao");

            LogMessage log;
            log.type = "#LianjiAnnounce";
            log.from = player;
            log.arg = choice + "effect";
            log.arg2 = choice;
            room->sendLog(log);
        }
        else if (event == SlashMissed)
        {
            QList<ServerPlayer *> targets;
            Slash *slash = new Slash(Card::NoSuit, 0);
            slash->deleteLater();
            QList<const Player*> empty;
            foreach (ServerPlayer *p, room->getOtherPlayers(data.value<SlashEffectStruct>().to))
            {
                if (slash->targetFilter(empty, p, player) && player->canSlash(p, true, 0, empty))
                {
                    targets << p;
                }
            }
            if (targets.length() == 0)
                return false;
            //@TODO: using weapon to lianti won't check target range
            int id = room->askForCardChosen(player, player, "hej", objectName(), true, Card::MethodNone);
            if (id == -1)
                return false;
            Slash *sl = new Slash(Card::SuitToBeDecided, 0);
            sl->addSubcard(id);
            sl->setSkillName("lianji");
            auto target = room->askForPlayerChosen(player, targets, objectName(), "@lianji-targetchoose");
            room->useCard(CardUseStruct(sl, player, target, true), false);
        }
        else if (event == Damage)
        {
            QList<ServerPlayer *> targets;
            Slash *slash = new Slash(Card::NoSuit, 0);
            slash->setFlags("slashNoDistanceLimit");
            slash->deleteLater();
            QList<const Player*> empty;
            foreach (ServerPlayer *p, room->getOtherPlayers(data.value<DamageStruct>().to))
            {
                if (slash->targetFilter(empty, p, player) && player->canSlash(p, false, 0, empty))
                {
                    targets << p;
                }
            }
            if (targets.length() == 0)
                return false;
            //@TODO: can't use crossbow to hengsao unless player can slash without crossbow
            int id = room->askForCardChosen(player, player, "hej", objectName(), true, Card::MethodNone);
            if (id == -1)
                return false;
            Slash *sl = new Slash(Card::SuitToBeDecided, 0);
            sl->addSubcard(id);
            sl->setSkillName("lianji");
            auto target = room->askForPlayerChosen(player, targets, objectName(), "@lianji-targetchoose");
            room->useCard(CardUseStruct(sl, player, target, true), true);
        }
        return false;
    }

};

void MoesenPackage::addGameGenerals()
{
    skills << new keyCardGlobalManagement;

    General *nanoha = new General(this, "nanoha", "wu", 4, false); // G001
    nanoha->addSkill(new Liepo);
    nanoha->addSkill(new Shenxing);

    General *fate = new General(this, "fate", "wu", 4, false); // G002
    fate->addSkill(new Leiguang);
    fate->addSkill(new Kongwu);

    General *hayate = new General(this, "hayate", "wu", 3, false); // G003
    hayate->addSkill(new Yetian);
    hayate->addSkill(new Tianjian);

    General *altria = new General(this, "altria", "wu", 4, false); // G004
    altria->addSkill(new Fengwang);
    altria->addSkill(new FengwangFilter);
    altria->addSkill(new FengwangTMS);
    altria->addSkill(new Duangang);
    insertRelatedSkills("fengwang", "#fengwang-target");
    insertRelatedSkills("fengwang", "#fengwang-filter");

    General *t_rin = new General(this, "t_rin", "wu", 3, false); // G005
    t_rin->addSkill(new Canshi);
    t_rin->addSkill(new Modan);

    General *rika = new General(this, "rika", "wu", 3, false); // G006
    rika->addSkill(new Guiyuan);
    rika->addSkill(new GuiyuanFilter);
    insertRelatedSkills("guiyuan", "#guiyuan-filter");
    rika->addSkill(new Zuimie);

    General *rena = new General(this, "rena", "wu", 4, false); // G007
    rena->addSkill(new Chaidao);

    General *haruka = new General(this, "haruka", "wu", 4, false); // G008
    haruka->addSkill(new Yuanqi);
    haruka->addSkill(new Daihei);

    General *miki = new General(this, "miki", "wu", 3, false); // G009
    miki->addSkill(new Yonglan);
    miki->addSkill(new ZhiyanMiki);

    General *setsuna = new General(this, "setsuna", "wu", 3, false); // G010
    setsuna->addSkill(new Chouchu);
    setsuna->addSkill(new Gaoling);

    General *kazusa = new General(this, "kazusa", "wu", 3, false); // G011
    kazusa->addSkill(new Bingshan);
    kazusa->addSkill(new Shenai);

    General *nagisa = new General(this, "nagisa", "wu", 3, false); // G012
    nagisa->addSkill(new Yunzhu);
    nagisa->addSkill(new Guangyu);
    nagisa->addRelateSkill("keyCard-global");

    General *tomoyo = new General(this, "tomoyo", "wu", 3, false); // G013
    tomoyo->addSkill(new Lianji);
    tomoyo->addSkill(new Qiangqi);
    tomoyo->addRelateSkill("keyCard-global");

    General *fuuko = new General(this, "fuuko", "wu", 3, false); // G014
    fuuko->addSkill(new Haixing);
    fuuko->addSkill(new Taozui);
    fuuko->addRelateSkill("keyCard-global");

    General *misuzu = new General(this, "misuzu", "wu", 3, false); // G015
    misuzu->addSkill(new Xiaying);
    misuzu->addSkill(new Yumeng);
    misuzu->addRelateSkill("keyCard-global");

    General *ayu = new General(this, "ayu", "wu", 3, false); // G016
    ayu->addSkill(new Huanyuan);
    ayu->addSkill(new Mengxian);
    ayu->addRelateSkill("keyCard-global");

    General *n_rin = new General(this, "n_rin", "wu", 3, false); // G017
    n_rin->addSkill(new Pasheng);
    n_rin->addSkill(new Jiuzhu);
    n_rin->addCompanion("komari");
    n_rin->addRelateSkill("keyCard-global");

    General *komari = new General(this, "komari", "wu", 3, false); // G018
    komari->addSkill(new Luoxuan);
    komari->addSkill(new Sidai);
    komari->addRelateSkill("keyCard-global");

    addMetaObject<HaixingCard>();
    addMetaObject<TaozuiCard>();
    addMetaObject<ShenxingCard>();
    addMetaObject<Key>();
    addMetaObject<Lingdan>();
    addMetaObject<LuoxuanCard>();
    addMetaObject<FengwangCard>();
    addMetaObject<YonglanCard>();
    addMetaObject<YonglanPindianCard>();
    addMetaObject<TianjianCard>();
    addMetaObject<ShenaiCard>();
    addMetaObject<QiangqiCard>();
    addMetaObject<ModanVoidCard>();
}
