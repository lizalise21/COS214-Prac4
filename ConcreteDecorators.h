#ifndef CONCRETEDECORATORS_H
#define CONCRETEDECORATORS_H

#include "ShipmentDecorator.h"

class InsuranceDecorator : public ShipmentDecorator {
private:
    double insuranceCost;

public:
    InsuranceDecorator(ShipmentComponent* wrappee, double insuranceCost);
    double getCost() const override;
    void display(int indent) const override;
};

class PriorityShipmentDecorator : public ShipmentDecorator {
private:
    double handlingFee;

public:
    PriorityShipmentDecorator(ShipmentComponent* wrappee, double handlingFee);
    double getCost() const override;
    bool isUrgent() const override;
    void display(int indent) const override;
};

#endif