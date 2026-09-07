#ifndef SHIPMENTGROUP_H
#define SHIPMENTGROUP_H

#include "ShipmentComponent.h"
#include <vector>

class ShipmentGroup : public ShipmentComponent {
private:
    std::string name;
    std::vector<ShipmentComponent*> children;

    friend class DeliveryIterator; // only iterator internals may see raw children

public:
    ShipmentGroup(std::string id, std::string name, std::string destination);
    ~ShipmentGroup() override;

    void add(ShipmentComponent* component) override;
    void remove(ShipmentComponent* component) override;

    double getWeight() const override;
    double getCost() const override;
    void display(int indent) const override;
    bool isUrgent() const override;

    ShipmentIterator* createFullIterator() override;
    ShipmentIterator* createPriorityIterator() override;

    // internal-only accessor used by DeliveryIterator during traversal construction
    const std::vector<ShipmentComponent*>& getChildrenInternal() const;
};

#endif