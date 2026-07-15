#include "Domain.h"
#include <iostream>
#include <sstream>

using namespace std;

// === Route Class Implementation ===
Route::Route() : startPoint(""), endPoint(""), distance(0.0) {}
Route::Route(string start, string end, double dist)
    : startPoint(start), endPoint(end), distance(dist) {}

void Route::displayRoute() const
{
    cout << "  Transit Path   : " << startPoint << " <---> " << endPoint      << "\n"
         << "  Total Distance : " << distance   << " KM"                       << "\n"
         << "  Est. Commute   : ~" << int(distance * 2) << " minutes (Traffic Dependent)\n"
         << "  Service Window : Morning/Evening Shifts"                         << "\n"
         << "  Frequency      : Every 20-30 mins during peak hours"             << "\n";
}

string Route::getDetailsCSV() const
{
    stringstream ss;
    ss << distance;
    return startPoint + "," + endPoint + "," + ss.str();
}

// === Bill Class Implementation ===
Bill::Bill() : baseFee(0.0), lateFine(0.0), isPaid(false) {}
Bill::Bill(double fee) : baseFee(fee), lateFine(0.0), isPaid(false) {}

void   Bill::applyFine(double fine)  { lateFine += fine; }
double Bill::getTotal()        const { return baseFee + lateFine; }
bool   Bill::getPaidStatus()   const { return isPaid; }
void   Bill::pay()                   { isPaid = true; }

void Bill::displayBill() const
{
    cout << "  Base Fee : Rs. " << baseFee
         << "  | Late Fine: Rs. " << lateFine
         << "  | Total: Rs. "     << getTotal()
         << "  | Status: "        << (isPaid ? "Paid" : "Unpaid") << "\n";
}

// === TransportPass Class Implementation ===
TransportPass::TransportPass() : passId(""), invoice(0.0), isApproved(false), assignedRouteIndex(-1) {}
TransportPass::TransportPass(string id, double fee, int routeIdx)
    : passId(id), invoice(fee), isApproved(false), assignedRouteIndex(routeIdx) {}

void  TransportPass::approvePass()         { isApproved = true; }
bool  TransportPass::checkApproval() const { return isApproved; }
int   TransportPass::getRouteIndex() const { return assignedRouteIndex; }
Bill& TransportPass::getInvoice()          { return invoice; }

void TransportPass::displayPassDetails() const
{
    cout << "  Pass ID : " << passId
         << "  | Status: " << (isApproved ? "Approved" : "Pending Approval") << "\n";
    invoice.displayBill();
}