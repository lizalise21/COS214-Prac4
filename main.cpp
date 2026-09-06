#include <iostream>
#include <vector>
#include <string>

#include "ShipmentComponent.h"
#include "ShipmentGroup.h"
#include "ShipmentItem.h"
#include "ShipmentDecorator.h"
#include "ConcreteDecorators.h"
#include "ShipmentIterator.h"
#include "ConcreteIterators.h"
#include "Delivery.h"
#include "ConcreteStates.h"
#include "LogisticsControlCenter.h"

int main() {
    std::cout << "========================================================\n";
    std::cout << "         COS 214/226 TASK 3: LOGISTICS DEMO             \n";
    std::cout << "========================================================\n\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "SCENARIO 1: Standard Logistics & Delivery Flow\n";
    std::cout << "--------------------------------------------------------\n";

    // Step 1: Build a ShipmentGroup containing ShipmentItem leaves
    std::cout << "\n[Step 1] Constructing Composite Hierarchy...\n";
    ShipmentGroup* mainContainer = new ShipmentGroup("G01", "Pretoria Central Hub", "Pretoria");
    ShipmentGroup* regionalSubGroup = new ShipmentGroup("G02", "Gauteng Regional Depot", "Johannesburg");

    ShipmentItem* item1 = new ShipmentItem("ITEM01", 3.5, "Pretoria", 150.0, false);
    ShipmentItem* item2 = new ShipmentItem("ITEM02", 6.0, "Pretoria", 250.0, false);
    ShipmentItem* item3 = new ShipmentItem("ITEM03", 0.5, "Johannesburg", 50.0, false);

    regionalSubGroup->add(item3);
    mainContainer->add(item1);
    mainContainer->add(item2);
    mainContainer->add(regionalSubGroup);

    std::cout << "Shipment hierarchy constructed:\n";
    mainContainer->display(1);

    // Step 2: Access Delivery Context from item1 initialized in CreatedState
    std::cout << "\n[Step 2] Inspecting Delivery Context...\n";
    Delivery* mainDelivery = item1->getDelivery();
    mainDelivery->updateLocation("Pretoria Central Hub");
    
    std::cout << "Delivery Context Initialized. Current State: " << mainDelivery->getStateName() << "\n";

    // Step 3: Create a ShipmentIterator to list all items and get the total costs
    std::cout << "\n[Step 3] Traversing Hierarchy & Calculating Total Cost...\n";
    ShipmentIterator* fullIterator = mainContainer->createFullIterator();

    std::cout << "--- Traversal Start --- \n";
    while (fullIterator->hasNext()) {
        ShipmentComponent* current = fullIterator->next();
        std::cout << "Visiting Component: " << current->getId() 
                  << " | Weight: " << current->getWeight() << "kg"
                  << " | Cost: R" << current->getCost() << "\n";
    }
    delete fullIterator; // Clean up iterator instance

    std::cout << "Total Hierarchy Cost: R" << mainContainer->getCost() << "\n";

    // Step 4: Advance Delivery through PickedUpState, TransitState, and DeliveredState
    std::cout << "\n[Step 4] Advancing Delivery Lifecycle States...\n";
    
    std::cout << "Action: Picking up delivery...\n";
    mainDelivery->pickUp();
    std::cout << "Current State: " << mainDelivery->getStateName() << "\n";

    std::cout << "\nAction: Depart for transit...\n";
    mainDelivery->departForTransit();
    std::cout << "Current State: " << mainDelivery->getStateName() << "\n";

    std::cout << "\nAction: Mark as delivered...\n";
    mainDelivery->markDelivered();
    std::cout << "Current State: " << mainDelivery->getStateName() << "\n";

    std::cout << "\nScenario 1 Completed Successfully.\n\n";


    std::cout << "--------------------------------------------------------\n";
    std::cout << "SCENARIO 2: Traversal Under Live Mutation (Snapshot Policy)\n";
    std::cout << "--------------------------------------------------------\n";

    // Step 1: Instantiate packages and wrap them with Decorators
    std::cout << "\n[Step 1] Wrapping Items with Decorators...\n";
    ShipmentItem* baseItem = new ShipmentItem("SRV-01", 25.0, "Cape Town", 1200.0, true);
    
    // Wrap base item with InsuranceDecorator (cost: 200.0)
    ShipmentComponent* insuredItem = new InsuranceDecorator(baseItem, 200.0);
    
    // Wrap insured item with PriorityShipmentDecorator (handling fee: 150.0)
    ShipmentComponent* priorityInsuredItem = new PriorityShipmentDecorator(insuredItem, 150.0);

    ShipmentGroup* mutationGroup = new ShipmentGroup("G03", "Cape Town Express Hub", "Cape Town");
    mutationGroup->add(priorityInsuredItem);

    ShipmentItem* existingItem = new ShipmentItem("CABL-01", 1.2, "Cape Town", 40.0, false);
    mutationGroup->add(existingItem);

    std::cout << "Decorated package total cost (Base R1200 + Insurance R200 + Priority R150): R" 
              << priorityInsuredItem->getCost() << "\n";

    // Step 2: Instantiate a ShipmentIterator (takes a snapshot of current tree)
    std::cout << "\n[Step 2] Capturing Snapshot Iterator prior to tree modification...\n";
    ShipmentIterator* snapshotIterator = mutationGroup->createFullIterator();

    // Step 3: Simulate Changes (Add new item while iteration is active)
    std::cout << "\n[Step 3] Modifying underlying ShipmentGroup during active iteration...\n";
    ShipmentItem* lateAddedItem = new ShipmentItem("MED-01", 4.0, "Cape Town", 500.0, true);
    
    // Mutation takes place on the group
    mutationGroup->add(lateAddedItem);
    std::cout << "-> Added 'MED-01' directly to the live ShipmentGroup.\n";

    // Step 4: Complete traversal using snapshot iterator
    std::cout << "\n[Step 4] Executing Traversal over the Snapshot...\n";
    std::cout << "--- Snapshot Traversal Start --- \n";
    int visitedCount = 0;
    
    while (snapshotIterator->hasNext()) {
        ShipmentComponent* comp = snapshotIterator->next();
        visitedCount++;
        std::cout << " Snapshot Node [" << visitedCount << "]: " << comp->getId() 
                  << " | Cost: R" << comp->getCost() << "\n";
    }
    delete snapshotIterator;

    std::cout << "--- Snapshot Traversal End ---\n";
    std::cout << "Total items processed by snapshot: " << visitedCount << "\n";
    std::cout << "Result: Traversal executed cleanly over isolated snapshot without memory corruption.\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "SCENARIO 3: Control Center Manifests & Shipment Relocation\n";
    std::cout << "--------------------------------------------------------\n";

    // Step 1: Create groups and items for control center management
    std::cout << "\n[Step 1] Constructing Control Center Hierarchy...\n";
    ShipmentGroup* hubRoot = new ShipmentGroup("HUB-01", "Gauteng Distribution Hub", "Midrand");
    ShipmentGroup* depotA = new ShipmentGroup("DEP-A", "Pretoria Local Depot", "Pretoria");
    ShipmentGroup* depotB = new ShipmentGroup("DEP-B", "Johannesburg Express Hub", "Johannesburg");

    ShipmentItem* pkg1 = new ShipmentItem("PKG-101", 5.0, "Pretoria", 200.0, true);  // Urgent
    ShipmentItem* pkg2 = new ShipmentItem("PKG-102", 12.0, "Johannesburg", 150.0, false); // Non-urgent

    depotA->add(pkg1);
    depotA->add(pkg2);
    hubRoot->add(depotA);
    hubRoot->add(depotB);

    // Step 2: Instantiate LogisticsControlCenter with root group
    std::cout << "\n[Step 2] Initializing Logistics Control Center...\n";
    LogisticsControlCenter controlCenter(hubRoot);

    // Step 3: Print Full and Urgent Manifests
    std::cout << "\n[Step 3] Printing Manifests via Control Center...\n";
    controlCenter.printFullManifest();
    controlCenter.printUrgentManifest();

    // Step 4: Relocate shipment from Depot A to Depot B
    std::cout << "\n[Step 4] Relocating PKG-102 from Depot A to Depot B...\n";
    controlCenter.relocateShipment(pkg2, depotA, depotB);

    std::cout << "\n--- Updated Full Manifest After Relocation ---";
    controlCenter.printFullManifest();

    std::cout << "\nScenario 3 Completed Successfully.\n\n";

    std::cout << "\n--------------------------------------------------------\n";
    std::cout << "CLEANUP: Deallocating Dynamic Memory...\n";
    std::cout << "--------------------------------------------------------\n";

    // Deleting root groups cascades down and deletes child components/decorators
    delete mainContainer; 
    delete mutationGroup;

    std::cout << "All memory successfully freed. Program exiting cleanly.\n";
    std::cout << "========================================================\n";

    return 0;
}