#pragma once
#include <string>

class Route
{
private:
    std::string startPoint;
    std::string endPoint;
    double distance;

public:
    Route();
    Route(std::string start, std::string end, double dist);

    void displayRoute() const;
    std::string getDetailsCSV() const;
};

class Bill
{
private:
    double baseFee;
    double lateFine;
    bool   isPaid;

public:
    Bill();
    Bill(double fee);

    void   applyFine(double fine);
    double getTotal() const;
    bool   getPaidStatus() const;
    void   pay();
    void   displayBill() const;
};

class TransportPass
{
private:
    std::string passId;
    Bill   invoice;
    bool   isApproved;
    int    assignedRouteIndex;

public:
    TransportPass();
    TransportPass(std::string id, double fee, int routeIdx);

    void  approvePass();
    bool  checkApproval() const;
    int   getRouteIndex() const;
    Bill& getInvoice();
    void  displayPassDetails() const;
};