#include "User.h"
#include <iostream>

using namespace std;

// === User Base Class Implementation ===
User::User(string uname, string pass, string role) : username(uname), password(pass), roleType(role) {}
User::~User() {}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
bool   User::authenticate(string pass) const { return password == pass; }
string User::getRole()     const { return roleType; }

// === Student Class Implementation ===
Student::Student(string uname, string pass, string regNo)
    : User(uname, pass, "Student"), studentRegNo(regNo), transportPass(nullptr) {}

// Fixed bug preventing complete system memory clearing on deletions
Student::~Student() { delete transportPass; }

void Student::linkTransportPass(TransportPass* pass) { delete transportPass; transportPass = pass; }
TransportPass* Student::getPass() { return transportPass; }
string Student::getRegNo() const { return studentRegNo; }
void Student::removePass()        { delete transportPass; transportPass = nullptr; }

void Student::displayMenu() const
{
    cout << "\n";
    cout << "*****************************************************\n";
    cout << "* STUDENT PORTAL MENU                               *\n";
    cout << "*****************************************************\n";
    cout << "* 1. View Active Routes                             *\n";
    cout << "* 2. Apply for Transport Pass                       *\n";
    cout << "* 3. View My Registration Status                    *\n";
    cout << "* 4. Cancel Transport Registration                  *\n";
    cout << "* 5. Logout                                         *\n";
    cout << "*****************************************************\n";
}

void Student::displayInfo() const
{
    cout << "  [Student] Username: " << username
         << "  | Reg No: "          << studentRegNo;
    if (transportPass)
        cout << "  | Pass: " << (transportPass->checkApproval() ? "Approved" : "Pending");
    else
        cout << "  | Pass: No Pass Linked";
    cout << "\n";
}

// === Driver Class Implementation ===
Driver::Driver(string uname, string pass, string license)
    : User(uname, pass, "Driver"), licenseId(license), assignedVehicleId("Not Assigned") {}

void   Driver::assignVehicle(string vehicleId) { assignedVehicleId = vehicleId; }
string Driver::getAssignedVehicle() const      { return assignedVehicleId; }
string Driver::getLicenseId() const { return licenseId; }

void Driver::displayMenu() const
{
    cout << "\n";
    cout << "*****************************************************\n";
    cout << "* DRIVER PORTAL MENU                                *\n";
    cout << "*****************************************************\n";
    cout << "* 1. View My Vehicle Shift Assignment               *\n";
    cout << "* 2. View Active Routes                             *\n";
    cout << "* 3. Logout                                         *\n";
    cout << "*****************************************************\n";
}

void Driver::displayInfo() const
{
    cout << "  [Driver] Username: " << username
         << "  | License: "        << licenseId
         << "  | Vehicle: "        << assignedVehicleId << "\n";
}

// === Admin Class Implementation ===
Admin::Admin(string uname, string pass) : User(uname, pass, "Admin") {}

void Admin::displayMenu() const
{
    cout << "\n";
    cout << "*****************************************************\n";
    cout << "* ADMIN SYSTEM CONTROL PANEL                        *\n";
    cout << "*****************************************************\n";
    cout << "* 1.  Add Vehicle (Bus/Van)                         *\n";
    cout << "* 2.  View & Update Operational Vehicles            *\n";
    cout << "* 3.  Operationalize Route                          *\n";
    cout << "* 4.  View Active Routes                            *\n";
    cout << "* 5.  Add Student or Driver                         *\n";
    cout << "* 6.  Process Pass Approvals                        *\n";
    cout << "* 7.  Apply Late Payment Penalties                  *\n";
    cout << "* 8.  Generate Financial Report                     *\n";
    cout << "* 9.  View Registered Users                         *\n";
    cout << "* 10. Save System State                             *\n";
    cout << "* 11. Logout                                        *\n";
    cout << "*****************************************************\n";
}

void Admin::displayInfo() const
{
    cout << "  [Admin] Username: " << username << "\n";
}