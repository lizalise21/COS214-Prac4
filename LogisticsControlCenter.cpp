#include "LogisticsControlCenter.h"
#include "ShipmentIterator.h"
#include <iostream>

LogisticsControlCenter::LogisticsControlCenter(ShipmentGroup* root) : root(root) {}

LogisticsControlCenter::~LogisticsControlCenter() {}

void LogisticsControlCenter::printFullManifest() {
    std::cout << "\n=== FULL MANIFEST ===\n";
    ShipmentIterator* it = root->createFullIterator();
    while (it->hasNext()) {
        ShipmentComponent* c = it->next();
        c->display(0);
    }
    delete it;
}

void LogisticsControlCenter::printUrgentManifest() {
    std::cout << "\n=== URGENT MANIFEST ===\n";
    ShipmentIterator* it = root->createPriorityIterator();
    while (it->hasNext()) {
        ShipmentComponent* c = it->next();
        c->display(0);
    }
    delete it;
}

void LogisticsControlCenter::relocateShipment(ShipmentComponent* item, ShipmentGroup* from, ShipmentGroup* to) {
    from->remove(item);
    to->add(item);
    std::cout << "Relocated " << item->getId() << " to group " << to->getId() << "\n";
}