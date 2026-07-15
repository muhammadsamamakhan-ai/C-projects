#include "TransportManager.h"
#include "Validation.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

TransportManager::TransportManager() : userCount(0), studentCount(0), driverCount(0), adminCount(0), vehicleCount(0), routeCount(0) {}

TransportManager::~TransportManager()
{
    for (int i = 0; i < userCount;    ++i) delete users[i];
    for (int i = 0; i < vehicleCount; ++i) delete vehicles[i];
}

int  TransportManager::getRoutesCount()  const  { return routeCount;  }
int  TransportManager::getVehicleCount() const  { return vehicleCount; }

void TransportManager::registerUser(User* u)
{
    if (userCount < 200) users[userCount++] = u;
}

void TransportManager::registerStudent(Student* s) 
{ 
    students[studentCount++] = s; 
    registerUser(s);
}

void TransportManager::registerDriver(Driver* d)   
{ 
    drivers[driverCount++] = d;  
    registerUser(d);
}

void TransportManager::registerAdmin(Admin* a)     
{ 
    admins[adminCount++] = a;    
    registerUser(a);
}

void TransportManager::addVehicle(Vehicle* v)      { if (vehicleCount < 100) vehicles[vehicleCount++] = v; }
void TransportManager::addRoute(Route r)           { if (routeCount < 100) routes[routeCount++] = r; }

Student* TransportManager::findStudentBySession(User* activeUser)
{
    for(int i = 0; i < studentCount; i++) {
        if(students[i]->getUsername() == activeUser->getUsername()) return students[i];
    }
    return nullptr;
}

Driver* TransportManager::findDriverBySession(User* activeUser)
{
    for(int i = 0; i < driverCount; i++) {
        if(drivers[i]->getUsername() == activeUser->getUsername()) return drivers[i];
    }
    return nullptr;
}

User* TransportManager::loginSystem(string username, string password)
{
    for (int i = 0; i < userCount; ++i)
        if (users[i]->getUsername() == username && users[i]->authenticate(password)) return users[i];
    return nullptr;
}

void TransportManager::displayAllRoutes() const
{
    if (routeCount == 0) { cout << "No current routes active in the system.\n"; return; }
    cout << "\n=========================================================\n";
    cout << "       CAMPUS TRANSPORT SERVICE - OPERATIONAL ROUTES     \n";
    cout << "=========================================================\n";
    for (int i = 0; i < routeCount; ++i)
    {
        cout << " [" << i + 1 << "]\n";
        routes[i].displayRoute();
        cout << "---------------------------------------------------------\n";
    }
}

void TransportManager::displayAllVehicles() const
{
    if (vehicleCount == 0) { cout << "No operational vehicles registered.\n"; return; }
    cout << "\n--- REGISTERED SYSTEM FLEET ---\n";
    for (int i = 0; i < vehicleCount; ++i)
        vehicles[i]->displayTypeDetails();
}

void TransportManager::displayAllUsers() const
{
    cout << "\n--- REGISTERED SYSTEM USERS ---\n";
    bool found = false;
    for (int i = 0; i < userCount; ++i)
    {
        if (users[i]->getRole() == "Student" || users[i]->getRole() == "Driver")
        {
            users[i]->displayInfo();
            found = true;
        }
    }
    if (!found) cout << "No active student or driver records located.\n";
}

void TransportManager::processPassApplications()
{
    bool found = false;
    for (int i = 0; i < studentCount; ++i)
    {
        Student* s = students[i];
        if (s->getPass() && !s->getPass()->checkApproval())
        {
            found = true;
            cout << "\nPending Application: " << s->getUsername() << "\n";
            s->getPass()->displayPassDetails();

            char choice = getValidatedChar("Approve registration? (y/n): ", "yYnN");
            if (choice == 'y' || choice == 'Y')
            {
                if (vehicleCount > 0 && vehicles[0]->bookSeat())
                {
                    s->getPass()->approvePass();
                    cout << "Pass approved and seat reserved successfully!\n";
                }
                else
                    cout << "Approval failed. No seats available.\n";
            }
            else
                cout << "Application left as pending.\n";
        }
    }
    if (!found) cout << "No pending transport registrations found.\n";
}

bool TransportManager::updateVehicle(string oldId, string newId, int typeChoice, int newCapacity)
{
    for (int i = 0; i < vehicleCount; ++i)
    {
        if (vehicles[i]->getVehicleId() == oldId)
        {
            delete vehicles[i]; 
            
            if (typeChoice == 1)
                vehicles[i] = new Bus(newId, newCapacity);
            else
                vehicles[i] = new Van(newId, newCapacity);

            for (int j = 0; j < driverCount; ++j)
            {
                if (drivers[j]->getAssignedVehicle() == oldId)
                    drivers[j]->assignVehicle(newId);
            }

            cout << "[OK] Vehicle updated successfully to ID '" << newId << "'.\n";
            return true;
        }
    }
    cout << "Error: Vehicle with ID '" << oldId << "' not found.\n";
    return false;
}

void TransportManager::applyLateFees()
{
    for (int i = 0; i < studentCount; ++i)
    {
        Student* s = students[i];
        if (s->getPass() && s->getPass()->checkApproval())
            s->getPass()->getInvoice().applyFine(500.00);
    }
    cout << "Late fee of Rs. 500 posted to all approved pass holders.\n";
}

void TransportManager::generateFinancialReport() const
{
    double total = 0;
    cout << "\n----- ADMINISTRATIVE REVENUE REPORT -----\n";
    for (int i = 0; i < studentCount; ++i)
    {
        Student* s = students[i];
        if (s->getPass())
        {
            cout << "User: " << s->getUsername() << " |\n";
            s->getPass()->displayPassDetails();
            total += s->getPass()->getInvoice().getTotal();
        }
    }
    cout << "\nTotal Forecasted Revenue: Rs. " << total << "\n";
}

void TransportManager::loadDataState()
{
    ifstream routeFile("routes.txt");
    if (routeFile.is_open())
    {
        string start, end, distStr;
        double dist;
        while (getline(routeFile, start, ',') &&
               getline(routeFile, end,   ',') &&
               getline(routeFile, distStr))
        {
            if (!start.empty() && !end.empty() && !distStr.empty())
            {
                stringstream ss(distStr);
                ss >> dist;
                routes[routeCount++] = Route(start, end, dist);
            }
        }
        routeFile.close();
    }

    if (routeCount == 0)
    {
        routes[routeCount++] = Route("UET New Campus",  "Lahore Main Station",   18.5);
        routes[routeCount++] = Route("Johar Town",      "GT Road Gate 01",       26.2);
        routes[routeCount++] = Route("Anarkali Bazar",  "Kala Shah Kaku Campus", 31.0);
        routes[routeCount++] = Route("DHA Phase 6",     "UET Main Campus",       22.4);
    }

    registerAdmin(new Admin("samama", "samama123"));

    ifstream userFile("users.txt");
    if (userFile.is_open())
    {
        string line;
        while (getline(userFile, line))
        {
            if (line.empty()) continue;
            stringstream ss(line);
            string type, uname, pass, specificField;
            
            getline(ss, type, ',');
            getline(ss, uname, ',');
            getline(ss, pass, ',');
            getline(ss, specificField, ',');

            if (type == "Student")
            {
                string hasPassStr, routeIdxStr, approvedStr;
                getline(ss, hasPassStr, ',');
                getline(ss, routeIdxStr, ',');
                getline(ss, approvedStr, ',');

                Student* newStudent = new Student(uname, pass, specificField);
                
                if (hasPassStr == "1")
                {
                    int rIdx = stoi(routeIdxStr);
                    TransportPass* passObj = new TransportPass("PASS-" + uname, 4500.00, rIdx); 
                    if (approvedStr == "1") {
                        passObj->approvePass();
                    }
                    newStudent->linkTransportPass(passObj);
                }
                registerStudent(newStudent);
            }
            else if (type == "Driver")
            {
                string assignedVehicle;
                getline(ss, assignedVehicle);

                Driver* newDriver = new Driver(uname, pass, specificField);
                if (!assignedVehicle.empty()) {
                    newDriver->assignVehicle(assignedVehicle);
                }
                registerDriver(newDriver);
            }
        }
        userFile.close();
    }
    else
    {
        registerStudent(new Student("hira", "hira123", "2025-SE-428"));

        Student* studentPending = new Student("ali", "ali123", "2025-CS-110");
        studentPending->linkTransportPass(new TransportPass("PASS-ALI-99", 4500.00, 0));
        registerStudent(studentPending);

        Student* studentApproved = new Student("zain", "zain123", "2025-EE-05");
        TransportPass* approvedPass = new TransportPass("PASS-ZAIN-12", 5200.00, 1);
        approvedPass->approvePass();
        studentApproved->linkTransportPass(approvedPass);
        registerStudent(studentApproved);

        Driver* driverA = new Driver("hassan", "hassan123", "PK-LNC-7721");
        driverA->assignVehicle("BUS-LHR-7712");
        registerDriver(driverA);

        Driver* driverB = new Driver("bilal", "bilal123", "PK-KHI-1102");
        driverB->assignVehicle("VAN-LHR-1122");
        registerDriver(driverB);
    }

    if (vehicleCount == 0) {
        addVehicle(new Bus("BUS-LHR-7712"));
        addVehicle(new Van("VAN-LHR-1122"));
        addVehicle(new Bus("BUS-LHR-9000"));
        addVehicle(new Van("VAN-LHR-4432"));
    }
}

void TransportManager::saveDataState()
{
    ofstream routeFile("routes.txt");
    if (routeFile.is_open())
    {
        for (int i = 0; i < routeCount; ++i)
            routeFile << routes[i].getDetailsCSV() << "\n";
        routeFile.close();
    }

    ofstream userFile("users.txt");
    if (userFile.is_open())
    {
        for (int i = 0; i < studentCount; ++i)
        {
            Student* s = students[i];
            userFile << "Student," << s->getUsername() << "," << s->getPassword() << "," << s->getRegNo();
            
            if (s->getPass())
            {
                TransportPass* p = s->getPass();
                userFile << ",1," << p->getRouteIndex() << "," << (p->checkApproval() ? "1" : "0");
            }
            else
            {
                userFile << ",0,-1,0";
            }
            userFile << "\n";
        }

        for (int i = 0; i < driverCount; ++i)
        {
            Driver* d = drivers[i];
            userFile << "Driver," << d->getUsername() << "," << d->getPassword() << "," 
                     << d->getLicenseId() << "," << d->getAssignedVehicle() << "\n";
        }
        userFile.close();
        cout << "System data synchronized to external storage.\n";
    }
}