#ifndef _REMOVED_H
#define _REMOVED_H

#include "package.h"
#include "card.h"
#include "wrappedcard.h"
#include "skill.h"
#include "standard.h"
#include "generaloverview.h"

class ZhaofuCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE ZhaofuCard();

    virtual void onEffect(const CardEffectStruct &effect) const;
};

class ZhaofuVSCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE ZhaofuVSCard();

    virtual bool targetFixed() const;
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual bool targetsFeasible(const QList<const Player *> &targets, const Player *Self) const;
    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
};

class ShangshiCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE ShangshiCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual bool targetsFeasible(const QList<const Player *> &targets, const Player *Self) const;
    virtual void extraCost(Room *room, const CardUseStruct &card_use) const;
};

class HuxunMoveCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE HuxunMoveCard();

    virtual bool targetsFeasible(const QList<const Player *> &targets, const Player *Self) const;
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onUse(Room *room, const CardUseStruct &use) const;
};

class ShefuCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE ShefuCard();

    virtual void extraCost(Room *room, const CardUseStruct &card_use) const;
};

class LifuCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE LifuCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class RemovedPackage : public Package
{
    Q_OBJECT

public:
    RemovedPackage();
};

ADD_PACKAGE(Removed)


#endif // _MOL_H

