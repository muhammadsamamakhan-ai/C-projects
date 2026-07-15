#ifndef CLOTHINGPRODUCT_H
#define CLOTHINGPRODUCT_H

#include "Product.h"

class ClothingProduct : public Product
{
private:
    string size;
    string fabric;
    string gender;

public:
    ClothingProduct(int id, string name, double p, int q,
                    string sz, string fb, string gd, Supplier sup = Supplier());

    string getSize();
    string getFabric();
    string getGender();

    void setSize(string s);
    void setFabric(string f);
    void setGender(string g);

    virtual string getTypeID();
    virtual void saveToFile(ofstream& out);
    virtual void displayStatus();
};

#endif
