#include "ClothingProduct.h"
#include "Helpers.h"

ClothingProduct::ClothingProduct(int id, string name, double p, int q,
                                 string sz, string fb, string gd, Supplier sup)
    : Product(id, name, p, q, sup)
{
    setSize(sz);
    setFabric(fb);
    setGender(gd);
}

string ClothingProduct::getSize()   { return size;   }
string ClothingProduct::getFabric() { return fabric; }
string ClothingProduct::getGender() { return gender; }

void ClothingProduct::setSize(string s)
{
    bool valid;
    do
    {
        valid = !s.empty();
        for (int i = 0; i < (int)s.length(); i++)
            if (!isalpha(s[i]) && s[i] != ' ') { valid = false; break; }
        if (!valid) { cout << "Letters only for size: "; getline(cin >> ws, s); }
    } while (!valid);
    size = s;
}

void ClothingProduct::setFabric(string f)
{
    bool valid;
    do
    {
        valid = !f.empty();
        for (int i = 0; i < (int)f.length(); i++)
            if (!isalpha(f[i]) && f[i] != ' ') { valid = false; break; }
        if (!valid) { cout << "Letters only for fabric: "; getline(cin >> ws, f); }
    } while (!valid);
    fabric = f;
}

void ClothingProduct::setGender(string g)
{
    while (g != "Male" && g != "Female" && g != "Unisex")
    {
        cout << "Enter Male, Female, or Unisex: ";
        getline(cin >> ws, g);
    }
    gender = g;
}

string ClothingProduct::getTypeID() { return "CP"; }

void ClothingProduct::saveToFile(ofstream& out)
{
    Product::saveToFile(out);
    out << size << "\n" << fabric << "\n" << gender << "\n";
}

void ClothingProduct::displayStatus()
{
    cout << "\n[Clothing Product]" << endl;
    cout << *this;
    cout << "  Size           : " << size   << endl;
    cout << "  Fabric         : " << fabric << endl;
    cout << "  Gender         : " << gender << endl;
}
