#ifndef PLAYER_H
#define PLAYER_H


#include <list>

class Item; // "forward declaration"


class Player {
public:
    Player();
    void heal(int amount);
    void speedUp(int duration);
    void removeFromInventory(Item* item);
    void invokeItem(Item* item);
    void addItemToInventory(Item* item);
private:
    std::list<Item*> inventory;
};


#endif