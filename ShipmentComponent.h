#ifndef SHIPMENTCOMPONENT_H
#define SHIPMENTCOMPONENT_H

#include <string>
class ShipmentIterator;

class ShipmentComponent {
protected:
    std::string id;
    double weight;
    std::string destination;

public:
    ShipmentComponent(std::string id, double weight, std::string destination);
    virtual ~ShipmentComponent();

    std::string getId() const;
    std::string getDestination() const;

    virtual double getWeight() const = 0;
    virtual double getCost() const = 0;
    virtual void display(int indent) const = 0;
    virtual bool isUrgent() const = 0;

    virtual void add(ShipmentComponent* component);
    virtual void remove(ShipmentComponent* component);

    virtual ShipmentIterator* createFullIterator() = 0;
    virtual ShipmentIterator* createPriorityIterator() = 0;
};

#endif