#include "player.h"
#include "item.h"

#include <string>
#include <iostream>

Player::Player() { }

void Player::addItemToInventory(Item* item) {
    inventory.push_back(item);
    item->setPlayer(this);
}

void Player::removeFromInventory(Item* item) {
    inventory.remove(item);
}

void Player::invokeItem(Item* item) {
    InvokableItem* invokable = dynamic_cast<InvokableItem*>(item);
    if ( invokable ) {
        bool itemWasDestroyed = invokable->invoke();
        if ( itemWasDestroyed ) {
            delete item;
        }
    }
    else {
        std::cout << "This item cannot be invoked." << std::endl;
    }
}

void Player::speedUp(int duration) {
    std::cout << "sped up for " << duration << " turns" << std::endl;
    // ...
}

void Player::heal(int amount) {
    std::cout << "healed by " << amount << std::endl;
    // ...
}