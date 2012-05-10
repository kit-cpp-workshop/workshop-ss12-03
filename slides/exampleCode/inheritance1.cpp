#include <string>
#include <iostream>
#include <list>

class Player {
public:
    Player();
    void heal(int amount) { };
    void speedUp(int duration) { };
    void removeFromInventory(Item* item) {
        inventory.remove(item);
    };
    void invokeItem(Item* item) {
        InvokableItem* invokable = dynamic_cast<InvokableItem*>(item);
        if ( invokable ) {
            bool itemWasDestroyed = invokable->invoke();
            if ( itemWasDestroyed ) {
                delete item;
            }
        }
        else {
            std::cout << "This item cannot be invoked.";
        }
    };
private:
    std::list<Item*> inventory;
};

class Item {
public:
    // Constructor
    Item(std::string theName) : name(theName) { };
    // Destructor
    virtual ~Item() {
        std::cout << "base item is being deleted";
        // ...
    };
    // a purely virtual method
    virtual float getWeight() = 0;
    // a non-virtual method
    std::string getName() const {
        return name;
    };

// protected attributes can only be accessed by the class itself, and by all its children.
protected:
    Player* player;
    virtual void destroyItem() {
        std::cout << "item is being removed from the game";
        player->removeFromInventory(this);
    };

// private attibutes can only be read and written by the class itself.
private:
    std::string name;
};

class InvokableItem : public Item {
public:
    // Constructor
    InvokableItem(std::string name, bool isDestroyedOnInvocation)
      : Item(name)
      , destroyedOnInvocation(isDestroyedOnInvocation)
    { };
    // another virtual method
    virtual bool invoke() {
        std::cout << "item is being invoked";
        if ( destroyedOnInvocation ) {
            destroyItem();
            return true;
        }
        return false;
    };
    virtual float getWeight() {
        return 20;
    };
protected:
    bool destroyedOnInvocation;
};

class HealingPotion : public InvokableItem {
public:
    // Constructor
    HealingPotion() : InvokableItem("Potion of Healing", true) { };
    // overrides "invoke" from InvokableItem
    virtual bool invoke() {
        // do some stuff
        player->heal(20);
        // call the method which was overridden
        return InvokableItem::invoke();
    };
};

class SpeedPotion : public InvokableItem {
public:
    // Constructor
    SpeedPotion() : InvokableItem("Potion of Speed", true) { };
    // overrides "invoke" from InvokableItem
    virtual bool invoke() {
        player->speedUp(50);
        return InvokableItem::invoke();
    };
};
