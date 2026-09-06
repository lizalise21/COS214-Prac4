#include "ShipmentItem.h"
#include "Delivery.h"
#include "ConcreteIterators.h"
#include <iostream>

ShipmentItem::ShipmentItem(std::string id, double weight, std::string destination,
                            double baseCost, bool priorityFlag)
    : ShipmentComponent(id, weight, destination),
      priorityFlag(priorityFlag), baseCost(baseCost), delivery(new Delivery()) {}

ShipmentItem::~ShipmentItem() {
    delete delivery;
}

double ShipmentItem::getWeight() const { return weight; }
double ShipmentItem::getCost() const { return baseCost; }

void ShipmentItem::display(int indent) const {
    std::cout << std::string(indent, ' ') << "- Item " << id
              << " (" << destination << ", " << weight << "kg, R" << baseCost
              << ", state=" << delivery->getStateName()
              << (priorityFlag ? ", URGENT" : "") << ")\n";
}

bool ShipmentItem::isUrgent() const { return priorityFlag; }

ShipmentIterator* ShipmentItem::createFullIterator() {
    return new ItemIterator(this, false);
}

ShipmentIterator* ShipmentItem::createPriorityIterator() {
    return new ItemIterator(this, true);
}

Delivery* ShipmentItem::getDelivery() { return delivery; }