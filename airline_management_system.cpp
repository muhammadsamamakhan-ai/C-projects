#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

struct Passenger {
    int id;   
    string name;
    int age;
    string flightId;
    bool isBooked;
};

struct Flight {
    int flightID;
    string city;
    string destination;
    string date;
    string time;
    int seats;
    int baseFare;
};

struct Admin {
    string username;
    string password;
};

Admin admin = {"SAMAMA", "12345"};

//humny declare kia
Passenger passengers[100];
int passengerCount = 0;
Flight flights[10];
int flightCount = 0;
int userID[100];
string password[100];
string name[100];
int credCount = 0;

void loadAdminFromFile() {
    ifstream file("admin.txt");
    if (!file) {
        return;
    }

    string u, p;
    if (file >> u >> p) {
        admin.username = u;
        admin.password = p;
    }
    file.close();
}

void saveAdminToFile() {
    ofstream file("admin.txt");
    if (!file) {
        cout << "Error saving admin credentials"<<endl;
        return;
    }
    file << admin.username << " " << admin.password;
    file.close();
}

bool adminLogin() {
    string username, password;
    cout << " ADMIN LOGIN"<<endl;
    cout << "enter Username ";
    cin >> username;
    cout << "enter Password "<<endl;
    cin >> password;

    if (username == admin.username && password == admin.password) {
        cout << "Login successful"<<endl;
        return true;
    } else {
        cout << "Invalid credentials. Access denied"<<endl;
        return false;
    }
}

void changePassword() {
    string oldPass, newPass;
    cout << "Enter your old password  "<<endl;
    cin >> oldPass;
    if (oldPass == admin.password) {
        cout << "Enter your new password "<<endl;
        cin >> newPass;
        admin.password = newPass;

        saveAdminToFile();

        cout << "Your Password is changed successfully"<<endl;
    } else {
        cout << "You enter an  Incorrect old password"<<endl;
    }
}

void viewData() {
    cout << "Registered Passengers:\n";
    for (int i = 0; i < passengerCount; i++) {
        string pass="";
        for (int j = 0; j < credCount; j++) {
            if (userID[j] == passengers[i].id) {
                pass = password[j];
                break;
            }
        }
        cout << "ID  " << passengers[i].id
             << "  Name  " << passengers[i].name
             << "  Age  " << passengers[i].age
             << "  Password " << pass
             <<endl;
    }
      cout<<endl;
    cout << "REGITER FLIGHT"<<endl;
    for (int i = 0; i < flightCount; i++) {
        cout << "Flight ID: " << flights[i].flightID
             << "  City: " << flights[i].city
             << "  Destination: " << flights[i].destination
             << "  Date: " << flights[i].date
             << "  Time " << flights[i].time
             << "  Seats  " << flights[i].seats
             << "  Base Fare  " << flights[i].baseFare
             <<endl;
    }
}

void loadPassengerCredentials() {
    ifstream file("passengercredentials.txt");

    if (!file) {
        credCount = 0;
        return;
    }
     
    credCount = 0;

    while (credCount < 100 &&
           file >> userID[credCount] &&
           file.ignore() &&                     
           getline(file, password[credCount], '\t') &&
           getline(file, name[credCount])) {

        credCount++;
    }

    file.close();
}

void savePassengerCredentials() {
    ofstream file("passengercredentials.txt", ios::out);
    if (!file) {
        cout << "Error saving passenger credentials"<<endl;
        return;
    }
    for (int i = 0; i < credCount; i++) {
        file << userID[i] << "\t" << password[i] << "\t" << name[i] << endl;
    }
    file.close();
}

void addPassenger() {
    if (passengerCount >= 100) {
        cout << "Max passengers reached!\n";
        return;
    }

    int maxID = 0;
    for (int i = 0; i < credCount; i++) {
        if (userID[i] > maxID) maxID = userID[i];
    }
    int newID = maxID + 1;

    string newPassword = "pass";
    int temp = newID;
    if (temp == 0) {
        newPassword += "0";
    } else {
        string s;
        while (temp > 0) {
            s = char('0' + temp % 10) + s;
            temp /= 10;
        }
        newPassword += s;
    }

    string passengerName;
    int passengerAge;
    cout << "Enter Name  ";
    getline(cin, passengerName);
    cout << "Enter Age  ";
    cin >> passengerAge;
    cin.ignore();

    userID[credCount] = newID;
    password[credCount] = newPassword;
    name[credCount] = passengerName;
    credCount++;

    passengers[passengerCount].id = newID;
    passengers[passengerCount].name = passengerName;
    passengers[passengerCount].age = passengerAge;
    passengers[passengerCount].flightId = "";
    passengers[passengerCount].isBooked = false;

    passengerCount++;
    cout << "Passenger added successfully  ID " << newID << ", Password: " << newPassword << endl;
}

void removePassenger() {
    int id;
    cout << "Enter Passenger ID to remove "<< endl;
    cin >> id;
    cin.ignore();

    
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].id == id) {
            for (int j = i; j < passengerCount - 1; j++) {
                passengers[j] = passengers[j + 1];
            }
            passengerCount--;
            cout << "Passenger removed successfully"<< endl;
            break;
        }
    }

    for (int i = 0; i < credCount; i++) {
        if (userID[i] == id) {
            for (int j = i; j < credCount - 1; j++) {
                userID[j] = userID[j + 1];
                password[j] = password[j + 1];
                name[j] = name[j + 1];
            }
            credCount--;
            break;
        }
    }
}

void updatePassenger() {
    int id;
    cout << "Enter Passenger ID to update: ";
    cin >> id;
    cin.ignore();

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].id == id) {
            cout << "Enter new Name  "<< endl;
            getline(cin, passengers[i].name);
            cout << "Enter new Age: "<< endl;
            cin >> passengers[i].age;
            cin.ignore();
            cout << "Update successful"<< endl;

           // to  update name
            for (int j = 0; j < credCount; j++) {
                if (userID[j] == id) {
                    name[j] = passengers[i].name;
                    break;
                }
            }
            return;
        }
    }
    cout << "Passenger not found.\n";
}

void addFlight() {
    if (flightCount >= 10) {
        cout << "Max flights reached\n";
        return;
    }
    Flight f;
    cout << "Enter Flight ID : ";
    cin >> f.flightID;
    cin.ignore();
    cout << "Enter City: ";
    getline(cin, f.city);
    cout << "Enter Destination: ";
    getline(cin, f.destination);
    cout << "Enter Date: ";
    getline(cin, f.date);
    cout << "Enter Time: ";
    getline(cin, f.time);
    cout << "Enter Seats: ";
    cin >> f.seats;
    cin.ignore();
    cout << "Enter Base Fare: ";
    cin >> f.baseFare;
    cin.ignore();

    flights[flightCount] = f;
    flightCount++;
    cout << "Flight added: " << f.flightID << " to " << f.destination << "\n";
}

void removeFlight() {
    int flightId;
    cout << "Enter Flight ID to remove: ";
    cin >> flightId;
    cin.ignore();

    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == flightId) {
            for (int j = i; j < flightCount - 1; j++) {
                flights[j] = flights[j + 1];
            }
            flightCount--;
            cout << "Flight removed: " << flightId << "\n";
            return;
        }
    }
    cout << "Flight not found."<< endl;
}

void generateReports() {
    ofstream reportFile("admin_reports.txt");
    if (!reportFile) {
        cout << "Error opening report file"<< endl;
        return;
    }

    int bookedCount = 0;
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].isBooked) bookedCount++;
    }

    reportFile << "Passenger Report:\n";
    for (int i = 0; i < passengerCount; i++) {
        reportFile << "ID: " << passengers[i].id
                   << ", Name: " << passengers[i].name
                   << ", Flight: " << passengers[i].flightId
                   << ", Booked: " << (passengers[i].isBooked ? "Yes" : "No")
                    << endl;
    }

    reportFile << "\nSummary:\n";
    reportFile << "Total Passengers: " << passengerCount << "\n";
    reportFile << "Total Booked: " << bookedCount << "\n";
    reportFile << "Total Not Booked: " << (passengerCount - bookedCount) << "\n";

    reportFile.close();
    cout << "Reports generated and saved to admin_reports.txt\n";
}

void loadPassengersFromFile() {
    ifstream file("passengerdata.txt");
    if (!file) {
        passengerCount = 0;
        return;
    }

    passengerCount = 0;
    while (file >> passengers[passengerCount].id >> passengers[passengerCount].age >> passengers[passengerCount].isBooked) {
        file.ignore();
        getline(file, passengers[passengerCount].name);
        getline(file, passengers[passengerCount].flightId);
        passengerCount++;
        if (passengerCount >= 100) break;
    }
    file.close();
    cout << "Passengers loaded from file"<< endl;
}
void savePassengersToFile() {
    ofstream file("passengerdata.txt");
    if (!file) {
        cout << "Error saving to file"<< endl;
        return;
    }

    for (int i = 0; i < passengerCount; i++) {
        file << passengers[i].id << " " << passengers[i].age << " " << passengers[i].isBooked
            << endl << passengers[i].name
             << endl << passengers[i].flightId << endl;
    }
    file.close();
    cout << "Passengers saved to file"<< endl;
}

void loadFlightsFromFile() {
    ifstream file("flights.txt");
    if (!file) {
        cout << "No existing flight file found. Using defaults"<< endl;
        return;
    }

    flightCount = 0;
    while (file >> flights[flightCount].flightID >> flights[flightCount].city >> flights[flightCount].destination >> flights[flightCount].date >> flights[flightCount].time >> flights[flightCount].seats >> flights[flightCount].baseFare) {
        flightCount++;
        if (flightCount >= 10) break;
    }
    file.close();
    cout << "Flights loaded from file"<< endl;
}

void saveFlightsToFile() {
    ofstream file("flights.txt");
    if (!file) {
        cout << "Error saving flights to file.\n";
        return;
    }

    for (int i = 0; i < flightCount; i++) {
        file << flights[i].flightID << " " << flights[i].city << " " << flights[i].destination << " " << flights[i].date << " " << flights[i].time << " " << flights[i].seats << " " << flights[i].baseFare << "\n";
    }
    file.close();
    cout << "Flights saved to file"<< endl;
}

void mainMenu();
void passengerModule();   
void adminModule();       
void systemModule();      
bool login(int& loggedID) {
    int id;
    string pass;
    cout << "Enter User ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;

    for (int i = 0; i < credCount; i++) {
        if (userID[i] == id && password[i] == pass) {
            loggedID = id;
            cout << "Login Successful! Welcome " << name[i] << endl;
            return true;
        }
    }

    cout << "Invalid Login" << endl;
    return false;
}
void viewFlights() {
    ifstream file("flights.txt");
    if (!file) {
        cout << "Flights file not found" << endl;
        return;
    }

    Flight f;
    cout << "ID\tCity\tDestination\tDate\tTime\tSeats\tFare" << endl;

    while (file >> f.flightID >> f.city >> f.destination >> f.date >> f.time >> f.seats >> f.baseFare) {
        cout << f.flightID << "\t" << f.city << "\t" << f.destination
            << "\t" << f.date << "\t" << f.time
            << "\t" << f.seats << "\t" << f.baseFare << endl;
    }
    file.close();
}

void bookFlight(int passengerID) {
    int fid, seatNo;
    string travelDate;
    char travelClass;

    cout << "Enter Flight ID to book: ";
    cin >> fid;
    cout << "Enter Travel Date  ";
    cin >> travelDate;

    ifstream in("flights.txt");
    if (!in) {
        cout << "Flights file not found " << endl;
        return;
    }
    ofstream temp("temp.txt");

    Flight f;
    bool found = false;
    int finalFare = 0;
    int totalSeats = 0;

    while (in >> f.flightID >> f.city >> f.destination >> f.date
        >> f.time >> f.seats >> f.baseFare) {

        if (f.flightID == fid && f.date == travelDate) {
            found = true;
            totalSeats = f.seats;

            if (f.seats <= 0) {
                cout << "No seats available on this flight" << endl;
                temp << f.flightID << " " << f.city << " "
                    << f.destination << " " << f.date << " "
                    << f.time << " " << f.seats << " " << f.baseFare << endl;
                continue;
            }

            cout << "Available seats  " << endl;
            int availableSeats[100];
            int count = 0;

            for (int s = 1; s <= totalSeats; s++) {
                ifstream bookings("bookings.txt");
                int pid, bid, bookedSeat, fare;
                string date, status;
                bool bookedFlag = false;

                while (bookings >> pid >> bid >> bookedSeat >> date >> fare >> status) {
                    if (bid == fid && date == travelDate && bookedSeat == s) {
                        bookedFlag = true;
                        break;
                    }
                }
                bookings.close();

                if (!bookedFlag) {
                    availableSeats[count] = s;
                    count++;
                    cout << s << " ";
                }
            }
            cout << endl;

            if (count == 0) {
                cout << "No seats available on this date." << endl;
                temp << f.flightID << " " << f.city << " "
                    << f.destination << " " << f.date << " "
                    << f.time << " " << f.seats << " " << f.baseFare << endl;
                in.close();
                temp.close();
                remove("temp.txt");
                return;
            }

            bool valid = false;
            while (!valid) {
                cout << "Select Seat Number "<< endl;
                cin >> seatNo;
                for (int i = 0; i < count; i++) {
                    if (seatNo == availableSeats[i]) {
                        valid = true;
                        break;
                    }
                }
                if (!valid) cout << "Seat already booked or invalid, choose again." << endl;
            }

            cout << "Enter Travel Class (E = Economy, B = Business): "<< endl;
            cin >> travelClass;
            if (travelClass == 'B' || travelClass == 'b')
                finalFare = f.baseFare * 1.5;
            else
                finalFare = f.baseFare;

            f.seats--;
        }

        temp << f.flightID << " " << f.city << " " << f.destination << " "
            << f.date << " " << f.time << " " << f.seats << " " << f.baseFare << endl;
    }

    in.close();
    temp.close();

    if (!found) {
        cout << "Flight not found on this date" << endl;;
        remove("temp.txt");
        return;
    }

    remove("flights.txt");
    rename("temp.txt", "flights.txt");

    ofstream book("bookings.txt", ios::app);
    book << passengerID << " " << fid << " " << seatNo << " "
        << travelDate << " " << finalFare << " Booked" << endl;
    book.close();

	 for (int i = 0; i < passengerCount; i++){
	  if (passengers[i].id == passengerID) { 
	  passengers[i].isBooked = true;
	   passengers[i].flightId = to_string(fid);
	    break; 
			}
		}
	cout << "Flight booked successfully!\n";
	}
	void cancelBooking(int passengerID) {
	 int fid; string travelDate;
	  cout << "Enter Flight ID to cancel: " << endl;
	   cin >> fid;
	    cout << "Enter Travel Date (DD-MM-YYYY) " << endl;
		 cin >> travelDate;
		ifstream in("bookings.txt");
ofstream temp("temp.txt");
int pid, flightID, seat, fare;
string date, status;
bool found = false;
int refunded = 0;
while (in >> pid >> flightID >> seat >> date >> fare >> status) {
    if (pid == passengerID && flightID == fid && date == travelDate) {
        found = true;
        refunded = fare * 0.8;
    }
    else {
        temp << pid << " " << flightID << " " << seat << " "
            << date << " " << fare << " " << status << endl;
    }
}

in.close();
temp.close();

if (!found) {
    cout << "Booking not found on this date" << endl;
    remove("temp.txt");
    return;
}
remove("bookings.txt");
rename("temp.txt", "bookings.txt");

cout << "Booking cancelled. Refund: " << refunded << endl;

ifstream fin("flights.txt");
ofstream fout("temp2.txt");
Flight f;
while (fin >> f.flightID >> f.city >> f.destination >> f.date >> f.time >> f.seats >> f.baseFare) {
    if (f.flightID == fid && f.date == travelDate) f.seats++;
    fout << f.flightID << " " << f.city << " " << f.destination << " "
        << f.date << " " << f.time << " " << f.seats << " " << f.baseFare << endl;
}
fin.close();
fout.close();
remove("flights.txt");
rename("temp2.txt", "flights.txt");

for (int i = 0; i < passengerCount; i++) {
    if (passengers[i].id == passengerID) {
        passengers[i].isBooked = false;
        passengers[i].flightId = "";
        break;
    }
}
}
    void viewReport(int passengerID) {
     int fid = 0, seatNo = 0, fare = 0;
      string travelDate; 
      string status;
       bool found = false;	
       ifstream in("bookings.txt");
if (!in) {
    cout << "No bookings found.\n";
    return;
}

int pid, bid, bseat, bfare;
string bdate, bstatus;
while (in >> pid >> bid >> bseat >> bdate >> bfare >> bstatus) {
    if (pid == passengerID) {
    
        fid = bid;
        seatNo = bseat;
        travelDate = bdate;
        fare = bfare;
        status = bstatus;
        found = true;
    }
}
in.close();

if (!found) {
    cout << "No booking found for passenger ID " << passengerID << endl;
    return;
}

ofstream receipt("receipt.txt", ios::app);
if (!receipt) {
    cout << "Unable to open receipt file.\n";
    return; 
    
}

receipt << endl << "----- RECEIPT -----" << endl;
receipt << "Passenger ID: " << passengerID << endl;
receipt << "Flight ID: " << fid << endl;
receipt << "Seat No: " << seatNo << endl;
receipt << "Date: " << travelDate << endl;
receipt << "Fare: " << fare << endl;
receipt << "Status: " << status << endl;
receipt << "-------------------" << endl;
receipt.close();

cout << "Booking report generated. Receipt appended to receipt.txt\n";
}
int main() {
    system("color B0");
    loadAdminFromFile();
    loadPassengerCredentials();
    loadPassengersFromFile();
    loadFlightsFromFile();
    mainMenu();
    savePassengersToFile();
    saveFlightsToFile();
    savePassengerCredentials();
    return 0;
}

void mainMenu() {
    int choice;

    while (true) {
        system("cls");
        system("color B0");

        cout << endl<< endl;
        cout << "*************************************************\n";
        cout << "*                                               *\n";
        cout << "*      AIRLINE RESERVATION MANAGEMENT SYSTEM    *\n";
        cout << "*                                               *\n";
        cout << "*************************************************\n";
        cout << "*                                               *\n";
        cout << "*   1. Passenger Menu                           *\n";
        cout << "*   2. Admin Menu                               *\n";
        cout << "*   3. System Information                       *\n";
        cout << "*   4. Exit                                     *\n";
        cout << "*                                               *\n";
        cout << "*************************************************\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            passengerModule();
            break;

        case 2:
            adminModule();
            break;

        case 3:
            systemModule();
            break;

        case 4:
            system("cls");
            system("color 0A");
            cout << "\nThank you for using the system!\n";
            return;

        default:
            cout << "\nInvalid choice! Try again.\n";
            system("pause");
        }
    }
}


void passengerModule() {
    system("cls");
    system("color 1E");

    cout << "\n---------------------------------------------\n";
    cout << "            PASSENGER MODULE\n";
    cout << "---------------------------------------------\n";

    int userID, choice = 0;
    cout << "PASSENGER AIRLINE SYSTEM" << endl;
    if (login(userID)) {
        while (choice != 5) {
            cout << "1.View Flights\n2.Book Flight\n3.Cancel Booking\n4.View Report\n5.Logout\nEnter Choice: ";
            cin >> choice;
            if (choice == 1) viewFlights();
            else if (choice == 2) bookFlight(userID);
            else if (choice == 3) cancelBooking(userID);
            else if (choice == 4) viewReport(userID);
            else if (choice == 5) cout << "Logged out." << endl;
            else cout << "Invalid choice." << endl;
        }
    }

    cout << "\nPress Enter to return to Main Menu...";
    cin.ignore();
    cin.get();
}


void adminModule() {
    system("cls");
    system("color 4F");

    cout << "\n---------------------------------------------\n";
    cout << "               ADMIN MODULE\n";
    cout << "---------------------------------------------\n";

    if (!adminLogin()) {
        cout << "\nPress Enter to return to Main Menu...";
        cin.ignore();
        cin.get();
        return;
    }

    int choice;
    while (true) {
        cout << "\nAdmin Menu:\n";
        cout << "1. Change Password\n";
        cout << "2. View Data\n";
        cout << "3. Add Passenger\n";
        cout << "4. Remove Passenger\n";
        cout << "5. Update Passenger\n";
        cout << "6. Add Flight\n";
        cout << "7. Remove Flight\n";
        cout << "8. Generate Reports\n";
        cout << "9. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: changePassword(); break;
            case 2: viewData(); break;
            case 3: addPassenger(); break;
            case 4: removePassenger(); break;
            case 5: updatePassenger(); break;
            case 6: addFlight(); break;
            case 7: removeFlight(); break;
            case 8: generateReports(); break;
            case 9:
                cout << "Logging out...\n";
                cout << "\nPress Enter to return to Main Menu...";
                cin.ignore();
                cin.get();
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

 void systemModule() { system("cls"); system("color 2F"); 
    cout << "\n---------------------------------------------\n";
cout << "           SYSTEM INFORMATION\n";
cout << "---------------------------------------------\n";
cout << "System: Airline Reservation Management System\n";
cout << "Version: 2.0\n";
cout << "Developed By : HASSAN RAZA,MALIK AHMED FRAZ\n\t\tZAEEM BUKHARI,M SAMAMA KHAN \n";
cout << "Features: Passenger booking, Admin management, Flight management\n";

cout << "\nPress Enter to return to Main Menu...";
cin.ignore();
cin.get();
}
