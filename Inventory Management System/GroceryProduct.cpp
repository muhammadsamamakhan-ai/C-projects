#include "GroceryProduct.h"
#include "Helpers.h"

// ============================================================
// GROCERY PRODUCT
// ============================================================
GroceryProduct::GroceryProduct(int id, string name, double p,
                               int q, int c, bool halal, Supplier s)
    : Product(id, name, p, q, s)
{
    setCalories(c);
    setHalalStatus(halal);
}

int  GroceryProduct::getCalories()    { return calories; }
bool GroceryProduct::getHalalStatus() { return isHalal;  }

void GroceryProduct::setCalories(int c)
{
    while (c < 0) { cout << "Calories cannot be negative: "; c = inputInteger(); }
    calories = c;
}

void GroceryProduct::setHalalStatus(bool h) { isHalal = h; }

string GroceryProduct::getTypeID() { return "GP"; }

void GroceryProduct::saveToFile(ofstream& out)
{
    Product::saveToFile(out);
    out << calories << "\n" << isHalal << "\n";
}

void GroceryProduct::displayStatus()
{
    cout << "\n[Grocery Product]" << endl;
    cout << *this;
    cout << "  Calories      : " << calories                    << endl;
    cout << "  Halal         : " << (isHalal ? "Yes" : "No") << endl;
}


// ============================================================
// PERISHABLE GROCERY
// ============================================================
PerishableGrocery::PerishableGrocery(int id, string name, double p, int q,
                                     int c, bool halal, string exp, int temp, Supplier s)
    : GroceryProduct(id, name, p, q, c, halal, s)
{
    setExpiryDate(exp);
    setStorageTemp(temp);
}

string PerishableGrocery::getExpiryDate()  { return expiryDate;  }
int    PerishableGrocery::getStorageTemp() { return storageTemp; }

void PerishableGrocery::setExpiryDate(string exp)
{
    if (exp.empty()) exp = "Unknown";
    expiryDate = exp;
}

void PerishableGrocery::setStorageTemp(int t)
{
    while (t < -50 || t > 100)
    {
        cout << "Temperature must be -50 to 100 C: ";
        t = inputInteger();
    }
    storageTemp = t;
}

string PerishableGrocery::getTypeID() { return "PG"; }

void PerishableGrocery::saveToFile(ofstream& out)
{
    GroceryProduct::saveToFile(out);
    out << expiryDate << "\n" << storageTemp << "\n";
}

void PerishableGrocery::displayStatus()
{
    cout << "\n[Perishable Grocery]" << endl;
    GroceryProduct::displayStatus();
    cout << "  Expiry Date  : " << expiryDate  << endl;
    cout << "  Storage Temp : " << storageTemp << " C" << endl;
}

void PerishableGrocery::calculateRisk()
{
    cout << "Perishable risk: check expiry date " << expiryDate << endl;
}

double PerishableGrocery::calculateValue() { return price * quantity * 0.9; }


// ============================================================
// NON PERISHABLE
// ============================================================
NonPerishable::NonPerishable(int id, string name, double p, int q,
                             int c, bool halal, int shelfLife, string preservative, Supplier s)
    : GroceryProduct(id, name, p, q, c, halal, s)
{
    setShelfLifeYears(shelfLife);
    setPreservativeLevel(preservative);
}

int    NonPerishable::getShelfLifeYears()    { return shelfLifeYears;    }
string NonPerishable::getPreservativeLevel() { return preservativeLevel; }

void NonPerishable::setShelfLifeYears(int y)
{
    while (y <= 0) { cout << "Shelf life must be positive: "; y = inputInteger(); }
    shelfLifeYears = y;
}

void NonPerishable::setPreservativeLevel(string lv)
{
    bool valid;
    do
    {
        valid = !lv.empty();
        for (int i = 0; i < (int)lv.length(); i++)
            if (!isalpha(lv[i]) && lv[i] != ' ') { valid = false; break; }
        if (!valid) { cout << "Letters only: "; getline(cin >> ws, lv); }
    } while (!valid);
    preservativeLevel = lv;
}

string NonPerishable::getTypeID() { return "NP"; }

void NonPerishable::saveToFile(ofstream& out)
{
    GroceryProduct::saveToFile(out);
    out << shelfLifeYears << "\n" << preservativeLevel << "\n";
}

void NonPerishable::displayStatus()
{
    cout << "\n[Non-Perishable Grocery]" << endl;
    GroceryProduct::displayStatus();
    cout << "  Shelf Life   : " << shelfLifeYears   << " years" << endl;
    cout << "  Preservative : " << preservativeLevel            << endl;
}

void NonPerishable::calculateRisk()
{
    cout << "Non-perishable risk: minimal - stable for " << shelfLifeYears << " years." << endl;
}

double NonPerishable::calculateValue() { return price * quantity * 1.05; }
