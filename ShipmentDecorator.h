#ifndef SHIPMENTDECORATOR_H
#define SHIPMENTDECORATOR_H

#include "ShipmentComponent.h"

class ShipmentDecorator : public ShipmentComponent {
protected:
    ShipmentComponent* wrappee;

public:
    explicit ShipmentDecorator(ShipmentComponent* wrappee);
    ~ShipmentDecorator() override;

    double getWeight() const override;
    double getCost() const override;
    void display(int indent) const override;
    bool isUrgent() const override;

    ShipmentIterator* createFullIterator() override;
    ShipmentIterator* createPriorityIterator() override;
};

#endif