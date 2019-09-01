
#include "utility/imagecolorchange.h"

#include "gameinfo/skills.h"

#include "engine/skillfactories/genericskillfactory.h"
#include "engine/skills/basicattack.h"
#include "engine/skills/evade.h"
#include "engine/skills/explosion.h"
#include "engine/skills/fireball.h"
#include "engine/skills/knightblock.h"
#include "engine/skills/mageonoffmagicshield.h"
#include "engine/skills/magicmissile.h"
#include "engine/skills/onofflastescape.h"
#include "engine/skills/plantareaattack.h"
#include "engine/skills/rage.h"
#include "engine/skills/shoot.h"
#include "engine/skills/teleport.h"
#include "engine/skills/thrust.h"
#include "engine/skills/walk.h"

using namespace gameinfo;

std::map<std::string, Skills::GetSkillFunctionType> Skills::_skills;

std::optional<Skills::Info> Skills::get(const std::string& name) {

    if(_skills.empty()) _init();

    auto func_it = _skills.find(name);

    if(func_it == _skills.end()) return std::nullopt;

    return (func_it->second)();
}

static Skills::Info _get_basic_attack() {

    static skillfactory::GenericSkillFactory<skill::BasicAttack> factory;

    return Skills::Info(&factory, QPixmap(":/sword_image.png"));
}

static Skills::Info _get_evade() {

    static skillfactory::GenericSkillFactory<skill::Evade> factory;

    return Skills::Info(&factory, QPixmap(":/wing_boot_blue.png"));
}

static Skills::Info _get_explosion() {

    static skillfactory::GenericSkillFactory<skill::Explosion> factory;

    return Skills::Info(&factory, QPixmap(":/explosion_icon.png"));
}

static Skills::Info _get_fireball() {

    static skillfactory::GenericSkillFactory<skill::Fireball> factory;

    return Skills::Info(&factory, QPixmap(":/fireball_image.png"));
}

static Skills::Info _get_knight_block() {

    static skillfactory::GenericSkillFactory<skill::KnightBlock> factory;

    utility::ImageColorChange icch;

    icch.addChInterval({0, 120}, {200, 256}, {200, 256}, QColor("#c0c0c0"));
    icch.addChInterval({0, 30}, {0, 30}, {220, 256}, QColor("#808080"));

    QImage im(":/magic_shield.png");

    icch.changeImage(im);

    return Skills::Info(&factory, QPixmap::fromImage(im));
}

static Skills::Info _get_on_off_magic_shield() {

    static skillfactory::GenericSkillFactory<skill::MageOnOffMagicShield> factory;

    return Skills::Info(&factory, QPixmap(":/magic_shield.png"));
}

static Skills::Info _get_magic_missile() {

    static skillfactory::GenericSkillFactory<skill::MagicMissile> factory;

    return Skills::Info(&factory, QPixmap(":/magic_missile_3.png").scaled(50, 50));
}

static Skills::Info _get_on_off_last_escape() {

    static skillfactory::GenericSkillFactory<skill::OnOffLastEscape> factory;

    return Skills::Info(&factory, QPixmap(":/onofflastescape_icon.png"));
}

static Skills::Info _get_plant_area_attack() {

    static skillfactory::GenericSkillFactory<skill::PlantAreaAttack> factory;

    return Skills::Info(&factory);
}

static Skills::Info _get_rage() {

    static skillfactory::GenericSkillFactory<skill::Rage> factory;

    return Skills::Info(&factory, QPixmap(":/rage_img.png"));
}

static Skills::Info _get_shoot_arrow() {

    static skillfactory::GenericSkillFactory<skill::Shoot, true> factory(sutils::VariantDataInfo{{"projectile", "arrow"}});

    return Skills::Info(&factory, QPixmap(":/arrow_projectile_image.png"));
}

static Skills::Info _get_throw_shuriken() {

    static skillfactory::GenericSkillFactory<skill::Shoot, true> factory(sutils::VariantDataInfo{{"projectile", "shuriken"}});

    return Skills::Info(&factory, QPixmap(":/shuriken_image.png"));
}

static Skills::Info _get_teleport() {

    static skillfactory::GenericSkillFactory<skill::Teleport> factory;

    return Skills::Info(&factory, QPixmap(":/teleport_mage_icon.png"));
}

static Skills::Info _get_thrust() {

    static skillfactory::GenericSkillFactory<skill::Thrust> factory;

    return Skills::Info(&factory, QPixmap(":/x_simbol.png"));
}

static Skills::Info _get_walk() {

    static skillfactory::GenericSkillFactory<skill::Walk> factory;

    return Skills::Info(&factory, QPixmap(":/wing_boot.png"));
}

void Skills::_init() {

    _skills["basic attack"] = _get_basic_attack;
    _skills["evade"] = _get_evade;
    _skills["explosion"] = _get_explosion;
    _skills["fireball"] = _get_fireball;
    _skills["knight block"] = _get_knight_block;
    _skills["ON/OFF magic shield"] = _get_on_off_magic_shield;
    _skills["magic missile"] = _get_magic_missile;
    _skills["ON/OFF last escape"] = _get_on_off_last_escape;
    _skills["plant area attack"] = _get_plant_area_attack;
    _skills["rage"] = _get_rage;
    _skills["shoot arrow"] = _get_shoot_arrow;
    _skills["throw shuriken"] = _get_throw_shuriken;
    _skills["teleport"] = _get_teleport;
    _skills["thrust"] = _get_thrust;
    _skills["walk"] = _get_walk;
}
