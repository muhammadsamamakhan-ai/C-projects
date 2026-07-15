#ifndef INVENTORY_H
#define INVENTORY_H

#include "Product.h"
#include "ElectronicProduct.h"
#include "GroceryProduct.h"
#include "ClothingProduct.h"
#include <fstream>

// ============================================================
// INVENTORY SECTION
// ============================================================
class InventorySection
{
private:
    Product*     products[100];
    int          productCount;
    int          aisleNumber;
    int          capacity;
    const string fileName;

public:
    InventorySection(int aisle = 1, int cap = 100);
    ~InventorySection();

    void setAisleNumber(int a);
    void setCapacity(int c);

    int getAisleNumber();
    int getCapacity();
    int totalProducts();

    void addStock(Product* p);
    void saveInventoryToFile();
    void loadInventoryFromFile();

    void     displayAll();
    void     sortByID();
    Product* findByID(int id);
    void     listIDs();

    Product* operator[](int index);
};


// ============================================================
// WAREHOUSE
// ============================================================
class Warehouse
{
private:
    int               locationID;
    double            totalSquareFootage;
    InventorySection* sections[50];
    int               sectionCount;

public:
    Warehouse(int id = 1, double footage = 0.0);

    void setLocationID(int id);
    void setTotalSquareFootage(double f);

    int    getLocationID();
    double getTotalSquareFootage();

    void   addSection(InventorySection* section);
    double getGlobalValue();
    void   findShortages(int threshold = 5);
};

#endif
