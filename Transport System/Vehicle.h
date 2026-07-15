#pragma once
#include <string>

class Vehicle
{
protected:
    std::string vehicleId;
    int    capacity;
    int    seatsBooked;

public:
    Vehicle(std::string id, int cap);
    virtual ~Vehicle();

    std::string getVehicleId() const;
    int    getAvailableSeats() const;
    void   setVehicleId(std::string id);
    void   setCapacity(int cap);
    bool   bookSeat();

    virtual void displayTypeDetails() const = 0;
};

class Bus : public Vehicle
{
public:
    Bus(std::string id);
    Bus(std::string id, int customCap);
    void displayTypeDetails() const override;
};

class Van : public Vehicle
{
public:
    Van(std::string id);
    Van(std::string id, int customCap);
    void displayTypeDetails() const override;
};