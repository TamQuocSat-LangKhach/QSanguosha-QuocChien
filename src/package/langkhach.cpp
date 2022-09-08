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

    virtual bool cost(TriggerEvent , Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
    {
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

                    }
                }
            } else {
                if (player->hasShownGeneral2() && player->getActualGeneral2()->isCompanionWith(choice)) {
                    room->addPlayerMark(player, "@companion");
                }
            }
        }

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
