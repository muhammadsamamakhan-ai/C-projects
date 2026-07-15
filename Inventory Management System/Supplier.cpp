#include "Supplier.h"
#include "Helpers.h"
#include <cctype>

Supplier::Supplier(int id, string name, string terms)
{
    setSupplierID(id);
    setSupplierName(name);
    contractTerms = terms;
}

int    Supplier::getSupplierID()    { return supplierID;    }
string Supplier::getSupplierName()  { return supplierName;  }
string Supplier::getContractTerms() { return contractTerms; }

void Supplier::setSupplierID(int id)
{
    while (id < 0)
    {
        cout << "Supplier ID cannot be negative. Enter again: ";
        id = inputInteger();
    }
    supplierID = id;
}

void Supplier::setSupplierName(string name)
{
    bool valid;
    do
    {
        valid = !name.empty();
        for (int i = 0; i < (int)name.length(); i++)
            if (!isalpha(name[i]) && name[i] != ' ') { valid = false; break; }
        if (!valid)
        {
            cout << "Letters only for supplier name: ";
            getline(cin >> ws, name);
        }
    } while (!valid);
    supplierName = name;
}

void Supplier::setContractTerms(string terms) { contractTerms = terms; }

void Supplier::orderRestock()
{
    cout << "Restock order placed with: " << supplierName << endl;
}

void Supplier::generateInvoice()
{
    cout << "Invoice for Supplier #" << supplierID << " | Terms: " << contractTerms << endl;
}

ostream& operator<<(ostream& out, const Supplier& s)
{
    out << "  Supplier ID   : " << s.supplierID   << endl;
    out << "  Supplier Name : " << s.supplierName << endl;
    out << "  Contract      : " << s.contractTerms << endl;
    return out;
}
