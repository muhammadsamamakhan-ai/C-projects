#include "Modules.h"
#include "Validation.h"
#include <iostream>

using namespace std;

void adminModule(User* activeSession, TransportManager& manager, User*& sessionRef)
{
    system("cls");
    system("color 0E");
    activeSession->displayMenu();
    int choice = getValidatedInteger("Enter Choice (1-11): ", 1, 11);

    switch (choice)
    {
        case 1: {
            system("cls"); system("color 0B");
            int t = getValidatedInteger("Select Type (1. Bus / 2. Van): ", 1, 2);
            string id = getValidatedName("Enter Asset Tag/ID: ");
            if (t == 1) manager.addVehicle(new Bus(id));
            else        manager.addVehicle(new Van(id));
            cout << "\n[OK] Fleet registration processed successfully.\n";
            break;
        }
        case 2: {
            system("cls"); system("color 0B");
            manager.displayAllVehicles();
            
            cout << "\n----------------------------------------\n";
            char updateChoice = getValidatedChar("Do you want to update any vehicle details? (y/n): ", "yYnN");
            if (updateChoice == 'y' || updateChoice == 'Y')
            {
                string oldId = getValidatedString("Enter current Vehicle ID to change: ");
                string newId = getValidatedString("Enter new Vehicle ID: ");
                int typeChoice = getValidatedInteger("Select new class layout structure (1. Bus / 2. Van): ", 1, 2);
                
                int cap = 0;
                if (typeChoice == 1) {
                    cap = getValidatedInteger("Enter custom structural capacity allocation (1-100): ", 1, 100);
                } else {
                    cap = getValidatedInteger("Enter custom structural capacity allocation (1-30): ", 1, 30);
                }
                
                manager.updateVehicle(oldId, newId, typeChoice, cap);
            }
            break;
        }
        case 3: {
            system("cls"); system("color 0B");
            string s = getValidatedString("Start Location: ");
            string e = getValidatedString("End Destination: ");
            double d = getValidatedDouble("Total Distance (KM) [0.1-1000.0]: ", 0.1, 1000.0);
            manager.addRoute(Route(s, e, d));
            cout << "\n[OK] Route operationalized successfully.\n";
            break;
        }
        case 4:
            system("cls"); system("color 0B");
            manager.displayAllRoutes();
            break;
        case 5: {
            system("cls"); system("color 0B");
            cout << "\n--- REGISTER NEW USER ---\n"
                 << "1. Register Student\n"
                 << "2. Register Driver\n";
            int userType = getValidatedInteger("Choice (1-2): ", 1, 2);
            string uname = getValidatedName("Enter Username: ");
            string pass  = getValidatedName("Enter Password: ");
            string field;
            if (userType == 1)
            {
                field = getValidatedName("Enter Registration Number: ");
                manager.registerStudent(new Student(uname, pass, field));
                cout << "\n[OK] Student registration successful.\n";
            }
            else
            {
                field = getValidatedName("Enter Driving License ID: ");
                manager.registerDriver(new Driver(uname, pass, field));
                cout << "\n[OK] Driver registration successful.\n";
            }
            break;
        }
        case 6:
            system("cls"); system("color 0B");
            manager.processPassApplications();
            break;
        case 7:
            system("cls"); system("color 0B");
            manager.applyLateFees();
            break;
        case 8:
            system("cls"); system("color 0F");
            manager.generateFinancialReport();
            break;
        case 9:
            system("cls"); system("color 0B");
            manager.displayAllUsers();
            break;
        case 10:
            system("cls"); system("color 0A");
            manager.saveDataState();
            break;
        case 11:
            sessionRef = nullptr;
            cout << "\nLogged out successfully.\n";
            break;
    }
}

void studentModule(User* activeSession, TransportManager& manager, User*& sessionRef)
{
    system("cls");
    system("color 0A");
    activeSession->displayMenu();
    int choice = getValidatedInteger("Enter Choice (1-5): ", 1, 5);
    
    Student* s = manager.findStudentBySession(activeSession);

    if (!s) {
        cout << "Session Error: Structural student profile mapping failed.\n";
        sessionRef = nullptr;
        return;
    }

    switch (choice)
    {
        case 1:
            system("cls"); system("color 0A");
            manager.displayAllRoutes();
            break;
        case 2:
            system("cls"); system("color 0A");
            if (s->getPass())
                cout << "Policy Conflict: One active pass per profile permitted.\n";
            else if (manager.getRoutesCount() == 0)
                cout << "No active routes available. Contact Administration.\n";
            else
            {
                manager.displayAllRoutes();
                int idx = getValidatedInteger("Select Route Number: ", 1, manager.getRoutesCount());
                s->linkTransportPass(new TransportPass("PASS-" + s->getUsername(), 4500.00, idx - 1));
                cout << "\n[OK] Transport application submitted for approval.\n";
            }
            break;
        case 3:
            system("cls"); system("color 0A");
            if (s->getPass()) s->getPass()->displayPassDetails();
            else cout << "No pass associated with your profile.\n";
            break;
        case 4:
            system("cls"); system("color 0C");
            s->removePass();
            cout << "\n[OK] Registration cancelled successfully.\n";
            break;
        case 5:
            sessionRef = nullptr;
            cout << "\nLogged out successfully.\n";
            break;
    }
}

void driverModule(User* activeSession, TransportManager& manager, User*& sessionRef)
{
    system("cls");
    system("color 0D");
    activeSession->displayMenu();
    int choice = getValidatedInteger("Enter Choice (1-3): ", 1, 3);
    
    Driver* d = manager.findDriverBySession(activeSession);

    if (!d) {
        cout << "Session Error: Structural driver profile mapping failed.\n";
        sessionRef = nullptr;
        return;
    }

    switch (choice)
    {
        case 1:
            system("cls"); system("color 0D");
            cout << "\nAssigned Vehicle: " << d->getAssignedVehicle() << "\n";
            break;
        case 2:
            system("cls"); system("color 0D");
            manager.displayAllRoutes();
            break;
        case 3:
            sessionRef = nullptr;
            cout << "\nLogged out successfully.\n";
            break;
    }
}