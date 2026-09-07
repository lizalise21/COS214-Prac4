#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>
#include <vector>
class DeliveryState;

class Delivery {
private:
    DeliveryState* currentState;
    std::string location;
    std::vector<std::string> history;

public:
    Delivery();
    ~Delivery();

    void setState(DeliveryState* state);
    std::string getStateName() const;

    void pickUp();
    void departForTransit();
    void markDelivered();
    void updateLocation(const std::string& loc);
};

#endif