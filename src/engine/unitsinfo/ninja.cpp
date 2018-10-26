
#include <engine/unit.h>
#include <engine/effects/lastescape.h>

#include "unitsinfo/ninja.h"
#include "skills/teleport.h"
#include "skills/onofflastescape.h"

using namespace unitsinfo;

Ninja *Ninja::_info = nullptr;

Ninja::Ninja() {

    addSkill(skill::Teleport::getSkill(), QPixmap(":/wing_boot_blue.png").scaled(50, 50));
    addSkill(skill::OnOffLastEscape::getSkill(), QPixmap(":/onofflastescape_icon.png").scaled(50, 50));
}

