#ifndef ELECTRONICPRODUCT_H
#define ELECTRONICPRODUCT_H

#include "Product.h"
#include <cstring>

// ============================================================
// ELECTRONIC PRODUCT
// ============================================================
class ElectronicProduct : public Product
{
protected:
    int   voltage;
    int   warranty;
    char* brandName;

public:
    ElectronicProduct(int id = 0, string name = "Unknown", double p = 0.0,
                      int q = 0, int v = 0, int w = 0,
                      const char* brand = "None", Supplier s = Supplier());

    ElectronicProduct(const ElectronicProduct& src);
    ElectronicProduct& operator=(const ElectronicProduct& src);
    ~ElectronicProduct();

    int   getVoltage();
    int   getWarranty();
    char* getBrandName();

    void setVoltage(int v);
    void setWarranty(int w);
    void setBrandName(const char* brand);

    virtual string getTypeID();
    virtual void saveToFile(ofstream& out);
    virtual void displayStatus();
    virtual void calculateRisk();
    virtual double calculateValue();
};


// ============================================================
// FRAGILE ELECTRONICS
// ============================================================
class FragileElectronics : public ElectronicProduct
{
private:
    int    fragilityRating;
    string packagingType;

public:
    FragileElectronics(int id, string name, double p, int q,
                       int v, int w, const char* brand,
                       int rating, string packaging, Supplier s = Supplier());

    int    getFragilityRating();
    string getPackagingType();

    void setFragilityRating(int r);
    void setPackagingType(string t);

    virtual string getTypeID();
    virtual void saveToFile(ofstream& out);
    virtual void displayStatus();
    virtual void calculateRisk();
    virtual double calculateValue();
};

#endif
