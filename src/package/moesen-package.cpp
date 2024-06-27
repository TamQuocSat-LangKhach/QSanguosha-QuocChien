#include "moesen-package.h"
#include "standard-basics.h"
#include "standard-tricks.h"
#include "client.h"
#include "engine.h"
#include "structs.h"
#include "exppattern.h"
#include "card.h"

MoesenPackage::MoesenPackage()
    : Package("moesen", GeneralPack, true)
{
    addAnimationGenerals();
    addComicGenerals();
    addGameGenerals();
    addNovelGenerals();
}

ADD_PACKAGE(Moesen)
