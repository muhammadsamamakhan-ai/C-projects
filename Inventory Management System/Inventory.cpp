#include "Inventory.h"
#include "Helpers.h"

// ============================================================
// INVENTORY SECTION
// ============================================================
InventorySection::InventorySection(int aisle, int cap) : fileName("inventory_data.txt")
{
    setAisleNumber(aisle);
    if (cap > 100) cap = 100;
    setCapacity(cap);
    productCount = 0;
}

InventorySection::~InventorySection()
{
    for (int i = 0; i < productCount; i++)
        delete products[i];
}

void InventorySection::setAisleNumber(int a)
{
    while (a <= 0) { cout << "Aisle must be positive: "; a = inputInteger(); }
    aisleNumber = a;
}

void InventorySection::setCapacity(int c)
{
    while (c <= 0) { cout << "Capacity must be positive: "; c = inputInteger(); }
    capacity = c;
}

int InventorySection::getAisleNumber() { return aisleNumber;  }
int InventorySection::getCapacity()    { return capacity;     }
int InventorySection::totalProducts()  { return productCount; }

void InventorySection::addStock(Product* p)
{
    if (productCount >= capacity)
    {
        cout << "Section is full! Cannot add more products." << endl;
        delete p;
        return;
    }
    products[productCount] = p;
    productCount++;
    saveInventoryToFile();
}

void InventorySection::saveInventoryToFile()
{
    ofstream outFile(fileName.c_str(), ios::out);
    if (!outFile)
    {
        cout << "Error: Could not open file for writing stock data!\n";
        return;
    }
    for (int i = 0; i < productCount; i++)
        products[i]->saveToFile(outFile);
    outFile.close();
}

void InventorySection::loadInventoryFromFile()
{
    ifstream inFile(fileName.c_str(), ios::in);
    if (!inFile) return;

    string type;
    while (getline(inFile, type))
    {
        if (type.empty()) continue;

        int id, qty;
        double price;
        string name;

        inFile >> id;
        inFile.ignore();
        getline(inFile, name);
        inFile >> price >> qty;
        inFile.ignore();

        // Load supplier
        int supID;
        string supName, supTerms;
        inFile >> supID; inFile.ignore();
        getline(inFile, supName);
        getline(inFile, supTerms);
        Supplier sup(supID, supName, supTerms);

        if (type == "EP")
        {
            int voltage, warranty;
            string brandStr;
            inFile >> voltage >> warranty; inFile.ignore();
            getline(inFile, brandStr);
            products[productCount++] = new ElectronicProduct(id, name, price, qty, voltage, warranty, brandStr.c_str(), sup);
        }
        else if (type == "FE")
        {
            int voltage, warranty, rating;
            string brandStr, packaging;
            inFile >> voltage >> warranty; inFile.ignore();
            getline(inFile, brandStr);
            inFile >> rating; inFile.ignore();
            getline(inFile, packaging);
            products[productCount++] = new FragileElectronics(id, name, price, qty, voltage, warranty, brandStr.c_str(), rating, packaging, sup);
        }
        else if (type == "PG")
        {
            int calories, temp;
            bool halal;
            string expiry;
            inFile >> calories >> halal; inFile.ignore();
            getline(inFile, expiry);
            inFile >> temp; inFile.ignore();
            products[productCount++] = new PerishableGrocery(id, name, price, qty, calories, halal, expiry, temp, sup);
        }
        else if (type == "NP")
        {
            int calories, shelfLife;
            bool halal;
            string preservative;
            inFile >> calories >> halal >> shelfLife; inFile.ignore();
            getline(inFile, preservative);
            products[productCount++] = new NonPerishable(id, name, price, qty, calories, halal, shelfLife, preservative, sup);
        }
        else if (type == "CP")
        {
            string sz, fabric, gender;
            getline(inFile, sz);
            getline(inFile, fabric);
            getline(inFile, gender);
            products[productCount++] = new ClothingProduct(id, name, price, qty, sz, fabric, gender, sup);
        }
    }
    inFile.close();
}

void InventorySection::displayAll()
{
    cout << "\nAisle " << aisleNumber << " | Capacity: " << capacity << " | Stored: " << productCount << endl;
    cout << string(44, '-') << endl;
    for (int i = 0; i < productCount; i++)
    {
        products[i]->displayStatus();
        cout << string(44, '-') << endl;
    }
}

void InventorySection::sortByID()
{
    for (int i = 0; i < productCount - 1; i++)
        for (int j = 0; j < productCount - i - 1; j++)
            if (products[j]->getProductID() > products[j+1]->getProductID())
            {
                Product* temp  = products[j];
                products[j]    = products[j+1];
                products[j+1]  = temp;
            }
    cout << "Products sorted by ID." << endl;
    saveInventoryToFile();
}

Product* InventorySection::findByID(int id)
{
    for (int i = 0; i < productCount; i++)
        if (products[i]->getProductID() == id)
            return products[i];
    return nullptr;
}

void InventorySection::listIDs()
{
    cout << "\nAvailable Products:" << endl;
    for (int i = 0; i < productCount; i++)
        cout << "  ID: " << products[i]->getProductID()
             << "  |  Name: " << products[i]->getProductName() << endl;
}

Product* InventorySection::operator[](int index)
{
    if (index >= 0 && index < productCount)
        return products[index];
    return nullptr;
}


// ============================================================
// WAREHOUSE
// ============================================================
Warehouse::Warehouse(int id, double footage)
{
    setLocationID(id);
    setTotalSquareFootage(footage);
    sectionCount = 0;
}

void Warehouse::setLocationID(int id)
{
    while (id <= 0) { cout << "Location ID must be positive: "; id = inputInteger(); }
    locationID = id;
}

void Warehouse::setTotalSquareFootage(double f)
{
    while (f < 0) { cout << "Footage cannot be negative: "; f = inputDouble(); }
    totalSquareFootage = f;
}

int    Warehouse::getLocationID()         { return locationID;         }
double Warehouse::getTotalSquareFootage() { return totalSquareFootage; }

void Warehouse::addSection(InventorySection* section)
{
    if (sectionCount < 50)
    {
        sections[sectionCount] = section;
        sectionCount++;
    }
}

double Warehouse::getGlobalValue()
{
    double total = 0;
    for (int i = 0; i < sectionCount; i++)
        for (int j = 0; j < sections[i]->totalProducts(); j++)
            total += (*sections[i])[j]->calculateValue();
    return total;
}

void Warehouse::findShortages(int threshold)
{
    cout << "\n===== LOW STOCK REPORT =====" << endl;
    bool found = false;
    for (int i = 0; i < sectionCount; i++)
        for (int j = 0; j < sections[i]->totalProducts(); j++)
            if ((*sections[i])[j]->getQuantity() <= threshold)
            {
                cout << "LOW STOCK: " << (*sections[i])[j]->getProductName()
                     << " | Qty: "   << (*sections[i])[j]->getQuantity() << endl;
                found = true;
            }
    if (!found) cout << "No shortages found." << endl;
    cout << "=============================" << endl;
}
