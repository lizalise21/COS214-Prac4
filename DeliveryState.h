#ifndef DELIVERYSTATE_H
#define DELIVERYSTATE_H

#include <string>
class Delivery;

class DeliveryState {
public:
    virtual ~DeliveryState();

    virtual void pickUp(Delivery* context);
    virtual void departForTransit(Delivery* context);
    virtual void markDelivered(Delivery* context);
    virtual std::string getName() const = 0;
};

#endif