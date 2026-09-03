#include "ShipmentComponent.h"
#include <iostream>

ShipmentComponent::ShipmentComponent(std::string id, double weight, std::string destination)
    : id(id), weight(weight), destination(destination) {}

ShipmentComponent::~ShipmentComponent() {}

std::string ShipmentComponent::getId() const { return id; }
std::string ShipmentComponent::getDestination() const { return destination; }

void ShipmentComponent::add(ShipmentComponent* component) {
    std::cout << "Cannot add to this component.\n";
}

void ShipmentComponent::remove(ShipmentComponent* component) {
    std::cout << "Cannot remove from this component.\n";
}