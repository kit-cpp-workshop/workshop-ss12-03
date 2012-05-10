/// Du kannst dieses Programm kompilieren mit
/// g++ -o main player.cpp item.cpp main.cpp -g

#include "player.h"
#include "item.h"

int main() {
    Player* p = new Player();
    Item* myPotion = new HealingPotion();
    p->addItemToInventory(myPotion);
    p->invokeItem(myPotion);
};