#include "TransportManager.h"
#include "Modules.h"
#include "Validation.h"
#include <iostream>

using namespace std;

int main()
{
    TransportManager manager;
    manager.loadDataState();

    User* activeSession    = nullptr;
    int   primarySelection = 0;

    while (true)
    {
        if (!activeSession)
        {
            system("cls");
            system("color 0B");

            cout << "\n";
            cout << "*****************************************************\n";
            cout << "* UNIVERSITY TRANSPORT MANAGEMENT & BILLING SYSTEM *\n";
            cout << "* v2026                                             *\n";
            cout << "*****************************************************\n";
            cout << "* 1. Admin Portal Login                             *\n";
            cout << "* 2. Student Portal Login                           *\n";
            cout << "* 3. Driver Portal Login                            *\n";
            cout << "* 4. Shutdown System                                *\n";
            cout << "*****************************************************\n";

            primarySelection = getValidatedInteger("\nEnter Choice (1-4): ", 1, 4);

            if (primarySelection >= 1 && primarySelection <= 3)
            {
                string u = getValidatedString("Username: ");
                string p = getValidatedString("Password: ");

                User* tempSession = manager.loginSystem(u, p);

                if (tempSession)
                {
                    bool roleMatch =
                        (primarySelection == 1 && tempSession->getRole() == "Admin")   ||
                        (primarySelection == 2 && tempSession->getRole() == "Student") ||
                        (primarySelection == 3 && tempSession->getRole() == "Driver");

                    if (roleMatch)
                    {
                        activeSession = tempSession;
                        cout << "\nAccess Granted. Welcome to the dashboard.\n";
                    }
                    else
                        cout << "\nAuthentication Refused: Role mismatch for selected portal.\n";
                }
                else
                    cout << "\nAuthentication Refused: Incorrect credentials.\n";

                system("pause");
            }
            else if (primarySelection == 4)
            {
                system("cls");
                system("color 0A");
                manager.saveDataState();
                cout << "\nSystem state saved. Goodbye!\n\n";
                break;
            }
        }
        else
        {
            string role = activeSession->getRole();
            if      (role == "Admin")   adminModule  (activeSession, manager, activeSession);
            else if (role == "Student") studentModule(activeSession, manager, activeSession);
            else if (role == "Driver")  driverModule (activeSession, manager, activeSession);

            system("pause");
        }
    }

    return 0;
}