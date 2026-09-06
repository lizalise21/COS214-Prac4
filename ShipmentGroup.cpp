#include "ShipmentGroup.h"
#include "ConcreteIterators.h"
#include <iostream>

ShipmentGroup::ShipmentGroup(std::string id, std::string name, std::string destination)
    : ShipmentComponent(id, 0.0, destination), name(name) {}

ShipmentGroup::~ShipmentGroup() {
    for (ShipmentComponent* child : children) {
        delete child;
    }
}

void ShipmentGroup::add(ShipmentComponent* component) {
    children.push_back(component);
}

void ShipmentGroup::remove(ShipmentComponent* component) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if (*it == component) {
            children.erase(it);
            return;
        }
    }
    std::cout << "Component " << component->getId() << " not found in group " << id << "\n";
}

double ShipmentGroup::getWeight() const {
    double total = 0.0;
    for (ShipmentComponent* child : children) {
        total += child->getWeight();
    }
    return total;
}

double ShipmentGroup::getCost() const {
    double total = 0.0;
    for (ShipmentComponent* child : children) {
        total += child->getCost();
    }
    return total;
}

void ShipmentGroup::display(int indent) const {
    std::cout << std::string(indent, ' ') << "[Group] " << id << " (" << name << ") -> "
              << destination << " | weight=" << getWeight() << " cost=" << getCost() << "\n";
    for (ShipmentComponent* child : children) {
        child->display(indent + 2);
    }
}

bool ShipmentGroup::isUrgent() const {
    for (ShipmentComponent* child : children) {
        if (child->isUrgent()) {
            return true;
        }
    }
    return false;
}

ShipmentIterator* ShipmentGroup::createFullIterator() {
    return new