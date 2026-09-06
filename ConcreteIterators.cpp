#include "ConcreteIterators.h"
#include "ShipmentComponent.h"
#include "ShipmentGroup.h"

// ---- DeliveryIterator (full traversal) ----
DeliveryIterator::DeliveryIterator(ShipmentComponent* root) : position(0) {
    collect(root);
}

void DeliveryIterator::collect(ShipmentComponent* node) {
    ShipmentGroup* group = dynamic_cast<ShipmentGroup*>(node);
    if (group != nullptr) {
        items.push_back(node);
        for (ShipmentComponent* child : group->getChildrenInternal()) {
            collect(child);
        }
    } else {
        items.push_back(node);
    }
}

bool DeliveryIterator::hasNext() {
    return position < (int)items.size();
}

ShipmentComponent* DeliveryIterator::next() {
    return items[position++];
}

// ---- PriorityIterator (urgent-only, wraps DeliveryIterator) ----
PriorityIterator::PriorityIterator(ShipmentComponent* root)
    : internalIterator(new DeliveryIterator(root)), nextUrgent(nullptr) {
    advanceToNextUrgent();
}

PriorityIterator::~PriorityIterator() {
    delete internalIterator;
}

void PriorityIterator::advanceToNextUrgent() {
    nextUrgent = nullptr;
    while (internalIterator->hasNext()) {
        ShipmentComponent* candidate = internalIterator->next();
        if (dynamic_cast<ShipmentGroup*>(candidate) == nullptr && candidate->isUrgent()) {
            nextUrgent = candidate;
            break;
        }
    }
}

bool PriorityIterator::hasNext() {
    return nextUrgent != nullptr;
}

ShipmentComponent* PriorityIterator::next() {
    ShipmentComponent* result = nextUrgent;
    advanceToNextUrgent();
    return result;
}

// ---- ItemIterator (leaf-level) ----
ItemIterator::ItemIterator(ShipmentComponent* item, bool includeIfUrgentOnly)
    : item(item), returned(false), includeIfUrgentOnly(includeIfUrgentOnly) {}

bool ItemIterator::hasNext() {
    if (returned) return false;
    if (includeIfUrgentOnly && !item->isUrgent()) return false;
    return true;
}

ShipmentComponent* ItemIterator::next() {
    returned = true;
    return item;
}