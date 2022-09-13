#ifndef _LANGKHACH_H
#define _LANGKHACH_H

#include "package.h"
#include "standard.h"

class LangKhachPackage : public Package
{
    Q_OBJECT

public:
    LangKhachPackage();
};

class MilitaryOrder : public SingleTargetTrick
{
    Q_OBJECT

public:
    Q_INVOKABLE MilitaryOrder(Card::Suit suit, int number);
    virtual bool targetRated(const Player *to_select, const Player *Self) const;
    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
    virtual bool isAvailable(const Player *player) const;
};

class Poison : public BasicCard
{
    Q_OBJECT

public:
    Q_INVOKABLE Poison(Card::Suit suit, int number, bool is_transferable = false);
    virtual QString getSubtype() const;
    virtual bool targetRated(const Player *to_select, const Player *Self) const;
    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
    virtual bool isAvailable(const Player *player) const;
};
#endif
