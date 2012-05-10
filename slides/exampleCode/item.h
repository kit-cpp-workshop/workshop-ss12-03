#ifndef ITEM_H
#define ITEM_H


#include <string>

class Player;


class Item {
public:
    Item(std::string theName);
    virtual ~Item();
    virtual float getWeight() = 0;
    const std::string getName() const;
    void setPlayer(Player* p);
protected:
    Player* player;
    virtual void destroyItem();
private:
    std::string name;
};

class InvokableItem : public Item {
public:
    InvokableItem(std::string name, bool isDestroyedOnInvocation);
    virtual bool invoke();
    virtual float getWeight();
protected:
    bool destroyedOnInvocation;
};

class HealingPotion : public InvokableItem {
public:
    HealingPotion();
    virtual bool invoke();
};

class SpeedPotion : public InvokableItem {
public:
    SpeedPotion();
    virtual bool invoke();
};


#endif