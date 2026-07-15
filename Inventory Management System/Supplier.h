#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <iostream>
#include <string>
using namespace std;

class Supplier
{
private:
    int    supplierID;
    string supplierName;
    string contractTerms;

public:
    Supplier(int id = 0, string name = "Unknown", string terms = "Standard");

    int    getSupplierID();
    string getSupplierName();
    string getContractTerms();

    void setSupplierID(int id);
    void setSupplierName(string name);
    void setContractTerms(string terms);

    void orderRestock();
    void generateInvoice();

    friend ostream& operator<<(ostream& out, const Supplier& s);
};

#endif
