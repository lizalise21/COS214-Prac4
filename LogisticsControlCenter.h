#ifndef LOGISTICSCONTROLCENTER_H
#define LOGISTICSCONTROLCENTER_H

#include "ShipmentGroup.h"

class LogisticsControlCenter {
private:
    ShipmentGroup* root;

public:
    explicit LogisticsControlCenter(ShipmentGroup* root);
    ~LogisticsControlCenter(); // does not delete root; root ownership is main's

    void printFullManifest();
    void printUrgentManifest();
    void relocateShipment(ShipmentComponent* item, ShipmentGroup* from, ShipmentGroup* to);
};

#endif