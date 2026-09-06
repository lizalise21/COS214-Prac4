#include "ShipmentDecorator.h"

ShipmentDecorator::ShipmentDecorator(ShipmentComponent* wrappee)
    : ShipmentComponent(wrappee->getId(), 0.0, wrappee->getDestination()), wrappee(wrappee) {}

ShipmentDecorator::~ShipmentDecorator() {
    delete wrappee;
}

double ShipmentDecorator::getWeight() const { return wrappee->getWeight(); }
double ShipmentDecorator::getCost() const { return wrappee->getCost(); }
void ShipmentDecorator::display(int indent) const { wrappee->display(indent); }
bool ShipmentDecorator::isUrgent() const { return wrappee->isUrgent(); }

ShipmentIterator* ShipmentDecorator::createFullIterator() { return wrappee->createFullIterator(); }
ShipmentIterator* ShipmentDecorator::createPriorityIterator() { return wrappee->createPriorityIterator(); }