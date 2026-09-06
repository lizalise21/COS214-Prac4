#ifndef CONCRETEITERATORS_H
#define CONCRETEITERATORS_H

#include "ShipmentIterator.h"
#include <vector>

class DeliveryIterator : public ShipmentIterator {
private:
    std::vector<ShipmentComponent*> items;
    int position;
    void collect(ShipmentComponent* node);

public:
    explicit DeliveryIterator(ShipmentComponent* root);
    bool hasNext() override;
    ShipmentComponent* next() override;
};

class PriorityIterator : public ShipmentIterator {
private:
    DeliveryIterator* internalIterator;
    ShipmentComponent* nextUrgent;
    void advanceToNextUrgent();

public:
    explicit PriorityIterator(ShipmentComponent* root);
    ~PriorityIterator() override;
    bool hasNext() override;
    ShipmentComponent* next() override;
};

class ItemIterator : public ShipmentIterator {
private:
    ShipmentComponent* item;
    bool returned;
    bool includeIfUrgentOnly;

public:
    explicit ItemIterator(ShipmentComponent* item, bool includeIfUrgentOnly = false);
    bool hasNext() override;
    ShipmentComponent* next() override;
};

#endif