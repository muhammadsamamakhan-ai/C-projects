#pragma once
#include "User.h"
#include "Vehicle.h"
#include "Domain.h"

class TransportManager
{
private:
    User* users[200];
    Student* students[200];
    Driver* drivers[100];
    Admin* admins[10];
    Vehicle* vehicles[100];
    Route    routes[100];
    
    int userCount;
    int studentCount;
    int driverCount;
    int adminCount;
    int vehicleCount;
    int routeCount;

public:
    TransportManager();
    ~TransportManager();

    int  getRoutesCount()  const;
    int  getVehicleCount() const;

    void registerUser(User* u);
    void registerStudent(Student* s);
    void registerDriver(Driver* d);
    void registerAdmin(Admin* a);
    
    void addVehicle(Vehicle* v);
    void addRoute(Route r);

    Student* findStudentBySession(User* activeUser);
    Driver* findDriverBySession(User* activeUser);
    User* loginSystem(std::string username, std::string password);

    void displayAllRoutes() const;
    void displayAllVehicles() const;
    void displayAllUsers() const;

    void processPassApplications();
    bool updateVehicle(std::string oldId, std::string newId, int typeChoice, int newCapacity);
    void applyLateFees();
    void generateFinancialReport() const;

    void loadDataState();
    void saveDataState();
};