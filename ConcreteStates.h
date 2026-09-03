#ifndef CONCRETESTATES_H
#define CONCRETESTATES_H

#include "DeliveryState.h"

class CreatedState : public DeliveryState {
public:
    void pickUp(Delivery* context) override;
    std::string getName() const override;
};

class PickedUpState : public DeliveryState {
public:
    void departForTransit(Delivery* context) override;
    std::string getName() const override;
};

class TransitState : public DeliveryState {
public:
    void markDelivered(Delivery* context) override;
    std::string getName() const override;
};

class DeliveredState : public DeliveryState {
public:
    std::string getName() const override;
};

#endif