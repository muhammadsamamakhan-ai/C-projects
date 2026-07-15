#include "Product.h"
#include "Helpers.h"
#include <cctype>

Product::Product(int id, string name, double p, int q, Supplier s)
{
    setProductID(id);
    setProductName(name);
    setPrice(p);
    setQuantity(q);
    supplier = s;
}

int      Product::getProductID()   { return productID;   }
string   Product::getProductName() { return productName; }
double   Product::getPrice()       { return price;       }
int      Product::getQuantity()    { return quantity;    }
Supplier Product::getSupplier()    { return supplier;    }

void Product::setProductID(int id)
{
    while (id < 0)
    {
        cout << "Product ID cannot be negative. Enter again: ";
        id = inputInteger();
    }
    productID = id;
}

void Product::setProductName(string name)
{
    bool valid;
    do
    {
        valid = !name.empty();
        for (int i = 0; i < (int)name.length(); i++)
            if (!isalpha(name[i]) && name[i] != ' ') { valid = false; break; }
        if (!valid)
        {
            cout << "Letters only for product name: ";
            getline(cin >> ws, name);
        }
    } while (!valid);
    productName = name;
}

void Product::setPrice(double p)
{
    while (p < 0)
    {
        cout << "Price cannot be negative. Enter again: ";
        p = inputDouble();
    }
    price = p;
}

void Product::setQuantity(int q)
{
    while (q < 0)
    {
        cout << "Quantity cannot be negative. Enter again: ";
        q = inputInteger();
    }
    quantity = q;
}

void Product::setSupplier(Supplier s) { supplier = s; }

void Product::saveToFile(ofstream& out)
{
    out << getTypeID() << "\n" << productID << "\n" << productName << "\n"
        << price << "\n" << quantity << "\n";
    out << supplier.getSupplierID()    << "\n"
        << supplier.getSupplierName()  << "\n"
        << supplier.getContractTerms() << "\n";
}

void Product::calculateRisk()
{
    cout << "General product risk: low." << endl;
}

double Product::calculateValue()
{
    return price * quantity;
}

void Product::applyDiscount(double percent)
{
    price = price - (price * percent / 100.0);
    cout << "Discount applied. New price: Rs." << price << endl;
}

bool Product::operator==(const Product& other) const
{
    return productID == other.productID;
}

ostream& operator<<(ostream& out, const Product& p)
{
    out << "  Product ID   : " << p.productID   << endl;
    out << "  Name         : " << p.productName << endl;
    out << "  Price        : Rs." << p.price    << endl;
    out << "  Quantity     : " << p.quantity    << endl;
    return out;
}
