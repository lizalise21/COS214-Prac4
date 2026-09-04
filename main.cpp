#include <iostream>
#include <vector>
#include <string>


int main() {
    std::cout << "=== LOGISTICS MANAGEMENT SYSTEM DEMO ===" << std::endl << std::endl;

    // ------------------------------------------------------------------------
    // SCENARIO 1: COMPOSITE PATTERN (Shipment Management)
    // ------------------------------------------------------------------------
    std::cout << "--- 1. Building Shipment Hierarchy (Composite) ---" << std::endl;
    // TODO: Instantiate root shipment group and sub-groups
    // ShipmentGroup* rootContainer = new ShipmentGroup("Gauteng Main Hub");
    // ShipmentGroup* localHub = new ShipmentGroup("Pretoria Central Depot");
    
    // TODO: Create individual shipment items (leaves)
    // ShipmentItem* item1 = new ShipmentItem("Electronics Package", 15.5);
    // ShipmentItem* item2 = new ShipmentItem("Document Bundle", 2.0);

    // TODO: Build tree hierarchy
    // localHub->add(item1);
    // localHub->add(item2);
    // rootContainer->add(localHub);
    
    // rootContainer->displayDetails();
    std::cout << "[Composite] Hierarchy created successfully.\n\n";


    // ------------------------------------------------------------------------
    // SCENARIO 2: DECORATOR PATTERN (Additional Services)
    // ------------------------------------------------------------------------
    std::cout << "--- 2. Applying Additional Services (Decorator) ---" << std::endl;
    // TODO: Wrap individual shipment items or groups with optional services
    // ShipmentComponent* insuredPackage = new InsuranceDecorator(item1, 50.0);
    // ShipmentComponent* priorityInsuredPackage = new PriorityDecorator(insuredPackage);

    // priorityInsuredPackage->displayDetails();
    std::cout << "[Decorator] Additional services wrapped.\n\n";


    // ------------------------------------------------------------------------
    // SCENARIO 3: ITERATOR PATTERN (Tracking & Traversal)
    // ------------------------------------------------------------------------
    std::cout << "--- 3. Traversing Shipment Structure (Iterator) ---" << std::endl;
    // TODO: Obtain iterator instance (Snapshot policy)
    // Iterator* it = rootContainer->createIterator();

    // for (it->first(); !it->isDone(); it->next()) {
    //     ShipmentComponent* current = it->currentItem();
    //     std::cout << " - Visiting: " << current->getName() << std::endl;
    // }
    // delete it;
    std::cout << "[Iterator] Traversal completed.\n\n";


    // ------------------------------------------------------------------------
    // SCENARIO 4: STATE PATTERN (Delivery Processing Lifecycle)
    // ------------------------------------------------------------------------
    std::cout << "--- 4. Processing Delivery Lifecycle (State) ---" << std::endl;
    // TODO: Create Delivery Context and cycle through state transitions
    // Delivery* shipmentDelivery = new Delivery("DEL-99201");

    // shipmentDelivery->displayState(); // CreatedState
    // shipmentDelivery->proceedToNext(); // Transitions to TransitState
    // shipmentDelivery->displayState();
    // shipmentDelivery->proceedToNext(); // Transitions to DeliveredState
    // shipmentDelivery->displayState();
    std::cout << "[State] Delivery state lifecycle transitions tested.\n\n";


    // ------------------------------------------------------------------------
    // CLEANUP
    // ------------------------------------------------------------------------
    std::cout << "--- 5. Memory Cleanup ---" << std::endl;
    // TODO: Free dynamically allocated memory for all Composite nodes and Decorators
    // delete rootContainer;
    // delete shipmentDelivery;

    std::cout << "=== DEMO COMPLETED CLEANLY ===" << std::endl;

    return 0;
}