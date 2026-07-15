#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>
#include <string>
#include "Supplier.h"
using namespace std;

class Product
{
protected:
    int      productID;
    string   productName;
    double   price;
    int      quantity;
    Supplier supplier;

public:
    Product(int id = 0, string name = "Unknown", double p = 0.0, int q = 0, Supplier s = Supplier());
    virtual ~Product() {}

    int      getProductID();
    string   getProductName();
    double   getPrice();
    int      getQuantity();
    Supplier getSupplier();

    void setProductID(int id);
    void setProductName(string name);
    void setPrice(double p);
    void setQuantity(int q);
    void setSupplier(Supplier s);

    virtual void   displayStatus()  = 0;
    virtual string getTypeID()      = 0;

    virtual void saveToFile(ofstream& out);
    virtual void calculateRisk();
    virtual double calculateValue();
    virtual void applyDiscount(double percent);

    bool operator==(const Product& other) const;
    friend ostream& operator<<(ostream& out, const Product& p);
};

#endif
