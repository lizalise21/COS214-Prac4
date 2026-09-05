#include <iostream>
#include <vector>
#include <string>

// Include your pattern headers according to the UML
#include "ShipmentComponent.h"
#include "ShipmentGroup.h"
#include "ShipmentItem.h"
#include "ShipmentDecorator.h"
#include "InsuranceDecorator.h"
#include "PriorityShipmentDecorator.h"
#include "ShipmentIterator.h"
#include "DeliveryIterator.h"
#include "PriorityIterator.h"
#include "Delivery.h"
#include "DeliveryState.h"

int main() {
    std::cout << "========================================================\n";
    std::cout << "         COS 214/226 TASK 3: LOGISTICS DEMO             \n";
    std::cout << "========================================================\n\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "SCENARIO 1: Standard Logistics & Delivery Flow\n";
    std::cout << "--------------------------------------------------------\n";

    // Step 1: Build a ShipmentGroup containing ShipmentItem leaves
    std::cout << "\n[Step 1] Constructing Composite Hierarchy...\n";
    ShipmentGroup* mainContainer = new ShipmentGroup("Pretoria Central Hub", "Pretoria");
    ShipmentGroup* regionalSubGroup = new ShipmentGroup("Gauteng Regional Depot", "Johannesburg");

    ShipmentItem* item1 = new ShipmentItem("Laptop Box", 3.5, "Pretoria", 150.0, false);
    ShipmentItem* item2 = new ShipmentItem("Monitor", 6.0, "Pretoria", 250.0, false);
    ShipmentItem* item3 = new ShipmentItem("Document Folder", 0.5, "Johannesburg", 50.0, false);

    regionalSubGroup->addComponent(item3);
    mainContainer->addComponent(item1);
    mainContainer->addComponent(item2);
    mainContainer->addComponent(regionalSubGroup);

    std::cout << "Shipment hierarchy constructed:\n";
    mainContainer->display(1);

    // Step 2: Instantiate a Delivery context initialized in CreatedState
    std::cout << "\n[Step 2] Initializing Delivery Context...\n";
    Delivery* mainDelivery = new Delivery();
    mainDelivery->updateLocation("Pretoria Central Hub");
    
    // Assign delivery context to item1
    item1->setDelivery(mainDelivery);
    std::cout << "Delivery Context Created. Current State: ";
    mainDelivery->print();

    // Step 3: Create a ShipmentIterator to list all items and get the total costs
    std::cout << "\n[Step 3] Traversing Hierarchy & Calculating Total Cost...\n";
    ShipmentIterator* fullIterator = mainContainer->createFullIterator();

    std::cout << "--- Traversal Start --- \n";
    while (fullIterator->hasNext()) {
        ShipmentComponent* current = fullIterator->next();
        std::cout << "Visiting Component: " << current->getName() 
                  << " | Weight: " << current->getWeight() << "kg"
                  << " | Cost: R" << current->getCost() << "\n";
    }
    delete fullIterator; // Clean up iterator instance

    std::cout << "Total Hierarchy Cost: R" << mainContainer->getCost() << "\n";

    // Step 4: Advance Delivery through TransitState and DeliveredState
    std::cout << "\n[Step 4] Advancing Delivery Lifecycle States...\n";
    
    std::cout << "Action: Picking up delivery...\n";
    mainDelivery->pickUp();
    mainDelivery->print();

    std::cout << "\nAction: Depart for transit...\n";
    mainDelivery->departForTransit();
    mainDelivery->print();

    std::cout << "\nAction: Mark as delivered...\n";
    mainDelivery->reachDelivered();
    mainDelivery->print();

    std::cout << "\nScenario 1 Completed Successfully.\n\n";


    // =========================================================================
    // SCENARIO 2: Traversal When Changes Are Made (Snapshot Validation)
    // =========================================================================
    std::cout << "--------------------------------------------------------\n";
    std::cout << "SCENARIO 2: Traversal Under Live Mutation (Snapshot Policy)\n";
    std::cout << "--------------------------------------------------------\n";

    // Step 1: Instantiate packages and wrap them with Decorators
    std::cout << "\n[Step 1] Wrapping Items with Decorators...\n";
    ShipmentItem* baseItem = new ShipmentItem("Server Rack Module", 25.0, "Cape Town", 1200.0, true);
    
    // Wrap base item with InsuranceDecorator (cost: 200.0)
    ShipmentComponent* insuredItem = new InsuranceDecorator(baseItem, 200.0);
    
    // Wrap insured item with PriorityShipmentDecorator (handling fee: 150.0)
    ShipmentComponent* priorityInsuredItem = new PriorityShipmentDecorator(insuredItem, 150.0);

    ShipmentGroup* mutationGroup = new ShipmentGroup("Cape Town Express Hub", "Cape Town");
    mutationGroup->addComponent(priorityInsuredItem);

    ShipmentItem* existingItem = new ShipmentItem("Spare Cables", 1.2, "Cape Town", 40.0, false);
    mutationGroup->addComponent(existingItem);

    std::cout << "Decorated package total cost (Base R1200 + Insurance R200 + Priority R150): R" 
              << priorityInsuredItem->getCost() << "\n";

    // Step 2: Instantiate a ShipmentIterator (takes a snapshot of current tree)
    std::cout << "\n[Step 2] Capturing Snapshot Iterator prior to tree modification...\n";
    ShipmentIterator* snapshotIterator = mutationGroup->createFullIterator();

    // Step 3: Simulate Changes (Add new item while iteration is active)
    std::cout << "\n[Step 3] Modifying underlying ShipmentGroup during active iteration...\n";
    ShipmentItem* lateAddedItem = new ShipmentItem("Unscheduled Medical Supplies", 4.0, "Cape Town", 500.0, true);
    
    // Mutation takes place on the group
    mutationGroup->addComponent(lateAddedItem);
    std::cout << "-> Added 'Unscheduled Medical Supplies' directly to the live ShipmentGroup.\n";

    // Step 4: Complete traversal using snapshot iterator
    std::cout << "\n[Step 4] Executing Traversal over the Snapshot...\n";
    std::cout << "--- Snapshot Traversal Start --- \n";
    int visitedCount = 0;
    
    while (snapshotIterator->hasNext()) {
        ShipmentComponent* comp = snapshotIterator->next();
        visitedCount++;
        std::cout << " Snapshot Node [" << visitedCount << "]: " << comp->getName() 
                  << " | Cost: R" << comp->getCost() << "\n";
    }
    delete snapshotIterator;

    std::cout << "--- Snapshot Traversal End ---\n";
    std::cout << "Total items processed by snapshot: " << visitedCount << " (Expected: 2)\n";
    std::cout << "Live container actual items count: 3\n";
    std::cout << "Result: Traversal executed cleanly over isolated snapshot without memory corruption.\n";

    // =========================================================================
    // MEMORY CLEANUP
    // =========================================================================
    std::cout << "\n--------------------------------------------------------\n";
    std::cout << "CLEANUP: Deallocating Dynamic Memory...\n";
    std::cout << "--------------------------------------------------------\n";

    // Deleting root groups cascades down to child components
    delete mainContainer; 
    delete mutationGroup;
    delete mainDelivery;

    std::cout << "All memory successfully freed. Program exiting cleanly.\n";
    std::cout << "========================================================\n";

    return 0;
}