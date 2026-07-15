#include "Vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle(string id, int cap) : vehicleId(id), capacity(cap), seatsBooked(0) {}
Vehicle::~Vehicle() {}

string Vehicle::getVehicleId()      const { return vehicleId; }
int    Vehicle::getAvailableSeats() const { return capacity - seatsBooked; }
void   Vehicle::setVehicleId(string id)   { vehicleId = id; }
void   Vehicle::setCapacity(int cap)      { capacity = cap; }

bool Vehicle::bookSeat()
{
    if (seatsBooked < capacity) { seatsBooked++; return true; }
    return false;
}

// === Bus Implementation ===
Bus::Bus(string id) : Vehicle(id, 50) {}
Bus::Bus(string id, int customCap) : Vehicle(id, customCap) {}
void Bus::displayTypeDetails() const
{
    cout << "  [Bus] ID: " << vehicleId
         << "  | Capacity: " << capacity
         << "  | Available Seats: " << getAvailableSeats() << "\n";
}

// === Van Implementation ===
Van::Van(string id) : Vehicle(id, 15) {}
Van::Van(string id, int customCap) : Vehicle(id, customCap) {}
void Van::displayTypeDetails() const
{
    cout << "  [Van] ID: " << vehicleId
         << "  | Capacity: " << capacity
         << "  | Available Seats: " << getAvailableSeats() << "\n";
}