#ifndef SHIPMENTITEM_H
#define SHIPMENTITEM_H

#include "ShipmentComponent.h"
class Delivery;

class ShipmentItem : public ShipmentComponent {
private:
    bool priorityFlag;
    double baseCost;
    Delivery* delivery;

public:
    ShipmentItem(std::string id, double weight, std::string destination,
                 double baseCost, bool priorityFlag);
    ~ShipmentItem() override;

    double getWeight() const override;
    double getCost() const override;
    void display(int indent) const override;
    bool isUrgent() const override;

    ShipmentIterator* createFullIterator() override;
    ShipmentIterator* createPriorityIterator() override;

    Delivery* getDelivery();
};

#endif