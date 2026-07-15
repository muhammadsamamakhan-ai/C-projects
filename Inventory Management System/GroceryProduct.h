#ifndef GROCERYPRODUCT_H
#define GROCERYPRODUCT_H

#include "Product.h"

// ============================================================
// GROCERY PRODUCT
// ============================================================
class GroceryProduct : public Product
{
protected:
    int  calories;
    bool isHalal;

public:
    GroceryProduct(int id = 0, string name = "Unknown", double p = 0.0,
                   int q = 0, int c = 0, bool halal = true, Supplier s = Supplier());

    int  getCalories();
    bool getHalalStatus();

    void setCalories(int c);
    void setHalalStatus(bool h);

    virtual string getTypeID();
    virtual void saveToFile(ofstream& out);
    virtual void displayStatus();
};


// ============================================================
// PERISHABLE GROCERY
// ============================================================
class PerishableGrocery : public GroceryProduct
{
private:
    string expiryDate;
    int    storageTemp;

public:
    PerishableGrocery(int id, string name, double p, int q,
                      int c, bool halal, string exp, int temp, Supplier s = Supplier());

    string getExpiryDate();
    int    getStorageTemp();

    void setExpiryDate(string exp);
    void setStorageTemp(int t);

    virtual string getTypeID();
    virtual void saveToFile(ofstream& out);
    virtual void displayStatus();
    virtual void calculateRisk();
    virtual double calculateValue();
};


// ============================================================
// NON PERISHABLE
// ============================================================
class NonPerishable : public GroceryProduct
{
private:
    int    shelfLifeYears;
    string preservativeLevel;

public:
    NonPerishable(int id, string name, double p, int q,
                  int c, bool halal, int shelfLife, string preservative, Supplier s = Supplier());

    int    getShelfLifeYears();
    string getPreservativeLevel();

    void setShelfLifeYears(int y);
    void setPreservativeLevel(string lv);

    virtual string getTypeID();
    virtual void saveToFile(ofstream& out);
    virtual void displayStatus();
    virtual void calculateRisk();
    virtual double calculateValue();
};

#endif
