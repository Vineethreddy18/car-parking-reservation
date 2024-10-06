#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class ParkingLot {
    vector<int> slots;  // Parking slots
    unordered_set<int> reservedSlots;  // Set to store reserved slots
    int parkingFee;      // Parking fee per car
    int totalRevenue;    // Total revenue from parked cars

public:
    ParkingLot(int size, int fee) {
        slots.resize(size, 0);  // Initialize all slots as empty (0)
        parkingFee = fee;
        totalRevenue = 0;
    }

    // Function to park a car in the nearest available slot
    void parkCar(int carNumber) {
        if (isCarParked(carNumber)) {
            cout << "Car " << carNumber << " is already parked!\n";
            return;
        }

        for (int i = 0; i < slots.size(); i++) {
            if (slots[i] == 0 && reservedSlots.find(i + 1) == reservedSlots.end()) {
                slots[i] = carNumber;
                totalRevenue += parkingFee;
                cout << "Car " << carNumber << " parked in slot " << i + 1 << " (nearest available)" << endl;
                return;
            }
        }
        cout << "Parking full or all empty slots are reserved!\n";
    }

    // Function to reserve a specific slot
    void reserveSlot(int slotNumber) {
        if (slotNumber < 1 || slotNumber > slots.size()) {
            cout << "Invalid slot number!\n";
            return;
        }
        if (slots[slotNumber - 1] != 0) {
            cout << "Slot " << slotNumber << " is already occupied!\n";
            return;
        }
        if (reservedSlots.find(slotNumber) != reservedSlots.end()) {
            cout << "Slot " << slotNumber << " is already reserved!\n";
            return;
        }
        reservedSlots.insert(slotNumber);
        cout << "Slot " << slotNumber << " has been reserved.\n";
    }

    // Function to release a reserved slot
    void releaseReservedSlot(int slotNumber) {
        if (reservedSlots.erase(slotNumber)) {
            cout << "Slot " << slotNumber << " reservation released.\n";
        } else {
            cout << "Slot " << slotNumber << " is not reserved!\n";
        }
    }

    // Function to display reserved slots
    void displayReservedSlots() {
        cout << "\nReserved Slots:\n";
        if (reservedSlots.empty()) {
            cout << "No reserved slots.\n";
        } else {
            for (const int& slot : reservedSlots) {
                cout << "Slot " << slot << endl;
            }
        }
    }

    // Function to remove a car
    void removeCar(int carNumber) {
        for (int i = 0; i < slots.size(); i++) {
            if (slots[i] == carNumber) {
                slots[i] = 0;
                cout << "Car " << carNumber << " removed from slot " << i + 1 << endl;
                return;
            }
        }
        cout << "Car not found in the parking lot!\n";
    }

    // Function to display the status of the parking lot
    void displayStatus() {
        cout << "\nParking Lot Status:\n";
        for (int i = 0; i < slots.size(); i++) {
            if (slots[i] == 0) {
                if (reservedSlots.find(i + 1) != reservedSlots.end()) {
                    cout << "Slot " << i + 1 << ": Reserved\n";
                } else {
                    cout << "Slot " << i + 1 << ": Empty\n";
                }
            } else {
                cout << "Slot " << i + 1 << ": Car " << slots[i] << endl;
            }
        }
    }

    // Function to check if the parking lot is full
    bool isFull() {
        for (int i = 0; i < slots.size(); i++) {
            if (slots[i] == 0 && reservedSlots.find(i + 1) == reservedSlots.end()) {
                return false;
            }
        }
        return true;
    }

    // Function to count available slots
    int availableSlots() {
        int count = 0;
        for (int i = 0; i < slots.size(); i++) {
            if (slots[i] == 0 && reservedSlots.find(i + 1) == reservedSlots.end()) {
                count++;
            }
        }
        return count;
    }

    // Function to search for a car's parking slot
    void searchCar(int carNumber) {
        for (int i = 0; i < slots.size(); i++) {
            if (slots[i] == carNumber) {
                cout << "Car " << carNumber << " is parked in slot " << i + 1 << endl;
                return;
            }
        }
        cout << "Car " << carNumber << " is not in the parking lot.\n";
    }

    // Function to check if a car is already parked
    bool isCarParked(int carNumber) {
        for (int i = 0; i < slots.size(); i++) {
            if (slots[i] == carNumber) {
                return true;
            }
        }
        return false;
    }

    // Function to display total revenue
    void displayRevenue() {
        cout << "Total revenue collected: $" << totalRevenue << endl;
    }

    // Function to set or change parking fee
    void setParkingFee(int fee) {
        parkingFee = fee;
        cout << "Parking fee set to $" << fee << " per car.\n";
    }
};

int main() {
    int size, choice, carNumber, slotNumber, fee;

    cout << "Enter the size of the parking lot: ";
    cin >> size;
    cout << "Set parking fee: ";
    cin >> fee;

    ParkingLot lot(size, fee);

    while (true) {
        cout << "\n1. Park Car\n2. Remove Car\n3. Display Parking Lot Status\n4. Search Car\n5. Reserve Slot\n6. Release Reserved Slot\n7. Display Reserved Slots\n8. Check Available Slots\n9. Check if Parking is Full\n10. Display Revenue\n11. Set Parking Fee\n12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter car number: ";
                cin >> carNumber;
                lot.parkCar(carNumber);
                break;
            case 2:
                cout << "Enter car number: ";
                cin >> carNumber;
                lot.removeCar(carNumber);
                break;
            case 3:
                lot.displayStatus();
                break;
            case 4:
                cout << "Enter car number to search: ";
                cin >> carNumber;
                lot.searchCar(carNumber);
                break;
            case 5:
                cout << "Enter slot number to reserve: ";
                cin >> slotNumber;
                lot.reserveSlot(slotNumber);
                break;
            case 6:
                cout << "Enter slot number to release reservation: ";
                cin >> slotNumber;
                lot.releaseReservedSlot(slotNumber);
                break;
            case 7:
                lot.displayReservedSlots();
                break;
            case 8:
                cout << "Available slots: " << lot.availableSlots() << endl;
                break;
            case 9:
                if (lot.isFull()) {
                    cout << "Parking lot is full.\n";
                } else {
                    cout << "Parking lot is not full.\n";
                }
                break;
            case 10:
                lot.displayRevenue();
                break;
            case 11:
                cout << "Enter new parking fee: ";
                cin >> fee;
                lot.setParkingFee(fee);
                break;
            case 12:
                char confirmExit;
                cout << "Are you sure you want to exit? (y/n): ";
                cin >> confirmExit;
                if (confirmExit == 'y' || confirmExit == 'Y') {
                    return 0;
                }
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
    return 0;
}
