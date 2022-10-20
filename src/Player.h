//
// Created by moosavi on 10/19/22.
//

#include "../include/Player.h"

void Player::reset() {
    this->health = 100;
    this->guns[Setting::get_start_gun()->get_type()] = Setting::get_start_gun();
}

bool Player::shut(int health) {
    if (!this->is_live())
        throw "Player is not live!";
    this->health -= health;
    if (this->health <= 0) {
        this->killed++;
        this->health = 0;
        this->guns.clear();
    }
    return !this->health;
}

void Player::bye_gun(Gun *gun) {
    this->can_bye(gun);
    this->money -= gun->get_price();
    this->guns[gun->get_type()] = gun;
}

void Player::can_bye(Gun *gun) const {
    if (this->guns.count(gun->get_type())) {
        throw "you have a" + (gun->get_type() == GlobalVariable::type_gun::heavy) ? "heavy" : "pistol";
    }

    if (gun->get_price() > this->money) {
        throw "no enough money";
    }
}

void Player::add_kill(GlobalVariable::type_gun type) {
    if (!this->has_gun(type))
        throw "you have no gun named" + type;
    this->kills++;
    this->add_money(this->guns[type]->get_money());
}

int Player::get_health() const { return this->health; }

int Player::get_money() const { return this->money; }

int Player::get_kills() const {
    return this->kills;
}

int Player::get_killed() const {
    return this->killed;
}

Time Player::get_time() const {
    return this->TIME;
}

void Player::won() {
    this->add_money(Setting::get_won_money());
}

void Player::lose() {
    this->add_money(Setting::get_lose_money());
}

void Player::add_money(int _money) {
    this->money += _money;
    if (this->money > Setting::get_max_money()) {
        this->money = Setting::get_max_money();
    }
}

bool Player::is_live() const {
    return this->health;
}

bool Player::has_gun(GlobalVariable::type_gun type) const {
    return this->guns.count(type);
}

Gun *Player::get_gun(GlobalVariable::type_gun type) const {
    if (this->has_gun(type))
        return const_cast<Gun *>(this->guns.at(type));
    else
        return nullptr;
}
