#include "ConcreteDecorators.h"
#include <iostream>

InsuranceDecorator::InsuranceDecorator(ShipmentComponent* wrappee, double insuranceCost)
    : ShipmentDecorator(wrappee), insuranceCost(insuranceCost) {}

double InsuranceDecorator::getCost() const {
    return wrappee->getCost() + insuranceCost;
}

void InsuranceDecorator::display(int indent) const {
    wrappee->display(indent);
    std::cout << std::string(indent + 2, ' ') << "[Insured, +R" << insuranceCost << "]\n";
}

PriorityShipmentDecorator::PriorityShipmentDecorator(ShipmentComponent* wrappee, double handlingFee)
    : ShipmentDecorator(wrappee), handlingFee(handlingFee) {}

double PriorityShipmentDecorator::getCost() const {
    return wrappee->getCost() + handlingFee;
}

bool PriorityShipmentDecorator::isUrgent() const {
    return true;
}

void PriorityShipmentDecorator::display(int indent) const {
    wrappee->display(indent);
    std::cout << std::string(indent + 2, ' ') << "[Priority handling, +R" << handlingFee << "]\n";
}