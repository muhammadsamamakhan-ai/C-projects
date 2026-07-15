#define _CRT_SECURE_NO_WARNINGS
#include "ElectronicProduct.h"
#include "Helpers.h"

// ============================================================
// ELECTRONIC PRODUCT
// ============================================================
ElectronicProduct::ElectronicProduct(int id, string name, double p,
                                     int q, int v, int w,
                                     const char* brand, Supplier s)
    : Product(id, name, p, q, s)
{
    brandName = nullptr;
    setVoltage(v);
    setWarranty(w);
    setBrandName(brand);
}

ElectronicProduct::ElectronicProduct(const ElectronicProduct& src) : Product(src)
{
    voltage  = src.voltage;
    warranty = src.warranty;
    brandName = new char[strlen(src.brandName) + 1];
    strcpy(brandName, src.brandName);
}

ElectronicProduct& ElectronicProduct::operator=(const ElectronicProduct& src)
{
    if (this == &src) return *this;
    productID   = src.productID;
    productName = src.productName;
    price       = src.price;
    quantity    = src.quantity;
    voltage     = src.voltage;
    warranty    = src.warranty;
    delete[] brandName;
    brandName = new char[strlen(src.brandName) + 1];
    strcpy(brandName, src.brandName);
    return *this;
}

ElectronicProduct::~ElectronicProduct() { delete[] brandName; }

int   ElectronicProduct::getVoltage()  { return voltage;  }
int   ElectronicProduct::getWarranty() { return warranty; }
char* ElectronicProduct::getBrandName(){ return brandName;}

void ElectronicProduct::setVoltage(int v)
{
    while (v < 0) { cout << "Voltage cannot be negative: "; v = inputInteger(); }
    voltage = v;
}

void ElectronicProduct::setWarranty(int w)
{
    while (w < 0) { cout << "Warranty cannot be negative: "; w = inputInteger(); }
    warranty = w;
}

void ElectronicProduct::setBrandName(const char* brand)
{
    if (strlen(brand) == 0) brand = "Unknown";
    delete[] brandName;
    brandName = new char[strlen(brand) + 1];
    strcpy(brandName, brand);
}

string ElectronicProduct::getTypeID() { return "EP"; }

void ElectronicProduct::saveToFile(ofstream& out)
{
    Product::saveToFile(out);
    out << voltage << "\n" << warranty << "\n" << brandName << "\n";
}

void ElectronicProduct::displayStatus()
{
    cout << "\n[Electronic Product]" << endl;
    cout << *this;
    cout << "  Voltage      : " << voltage  << "V"   << endl;
    cout << "  Warranty     : " << warranty << " yr" << endl;
    cout << "  Brand        : " << brandName          << endl;
}

void ElectronicProduct::calculateRisk()
{
    cout << "Electronic risk: medium (check voltage compatibility)." << endl;
}

double ElectronicProduct::calculateValue() { return price * quantity * 1.1; }


// ============================================================
// FRAGILE ELECTRONICS
// ============================================================
FragileElectronics::FragileElectronics(int id, string name, double p, int q,
                                       int v, int w, const char* brand,
                                       int rating, string packaging, Supplier s)
    : ElectronicProduct(id, name, p, q, v, w, brand, s)
{
    setFragilityRating(rating);
    setPackagingType(packaging);
}

int    FragileElectronics::getFragilityRating() { return fragilityRating; }
string FragileElectronics::getPackagingType()   { return packagingType;   }

void FragileElectronics::setFragilityRating(int r)
{
    while (r < 1 || r > 10)
    {
        cout << "Fragility must be 1 to 10. Enter again: ";
        r = inputInteger();
    }
    fragilityRating = r;
}

void FragileElectronics::setPackagingType(string t)
{
    bool valid;
    do
    {
        valid = !t.empty();
        for (int i = 0; i < (int)t.length(); i++)
            if (!isalpha(t[i]) && t[i] != ' ') { valid = false; break; }
        if (!valid) { cout << "Letters only for packaging: "; getline(cin >> ws, t); }
    } while (!valid);
    packagingType = t;
}

string FragileElectronics::getTypeID() { return "FE"; }

void FragileElectronics::saveToFile(ofstream& out)
{
    ElectronicProduct::saveToFile(out);
    out << fragilityRating << "\n" << packagingType << "\n";
}

void FragileElectronics::displayStatus()
{
    cout << "\n[Fragile Electronics]" << endl;
    ElectronicProduct::displayStatus();
    cout << "  Fragility     : " << fragilityRating << "/10" << endl;
    cout << "  Packaging     : " << packagingType            << endl;
}

void FragileElectronics::calculateRisk()
{
    if      (fragilityRating >= 7) cout << "RISK: HIGH - special handling required!" << endl;
    else if (fragilityRating >= 4) cout << "RISK: MEDIUM - handle with care."        << endl;
    else                           cout << "RISK: LOW - standard handling OK."        << endl;
}

double FragileElectronics::calculateValue() { return price * quantity * 1.2; }
