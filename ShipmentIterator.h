#ifndef SHIPMENTITERATOR_H
#define SHIPMENTITERATOR_H

class ShipmentComponent;

class ShipmentIterator {
public:
    virtual ~ShipmentIterator();
    virtual bool hasNext() = 0;
    virtual ShipmentComponent* next() = 0;
};

#endif