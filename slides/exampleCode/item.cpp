#include "item.h"
#include "player.h"

#include <iostream>


Item::Item(std::string theName) : name(theName) { }

Item::~Item() {
    std::cout << "base item is being deleted" << std::endl;
    // ...
}

float InvokableItem::getWeight() {
    return 20;
}

void Item::setPlayer(Player* p) {
    player = p;
}

const std::string Item::getName() const {
    return name;
};

void Item::destroyItem() {
    std::cout << "item is being removed from the game" << std::endl;
    player->removeFromInventory(this);
}

/// *****

InvokableItem::InvokableItem(std::string name, bool isDestroyedOnInvocation)
    : Item(name)
    , destroyedOnInvocation(isDestroyedOnInvocation) { }

bool InvokableItem::invoke() {
    std::cout << "base item was invoked" << std::endl;
    if ( destroyedOnInvocation ) {
        destroyItem();
        return true;
    }
    return false;
}

/// *****

HealingPotion::HealingPotion()
    : InvokableItem("Potion of Healing", true) { }

bool HealingPotion::invoke() {
    player->heal(20);
    return InvokableItem::invoke();
}

/// *****

SpeedPotion::SpeedPotion()
    : InvokableItem("Potion of Speed", true) { }

bool SpeedPotion::invoke() {
    player->speedUp(50);
    return InvokableItem::invoke();
}
