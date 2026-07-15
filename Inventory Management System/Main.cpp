// ============================================================
//   INVENTORY MANAGEMENT SYSTEM WITH FILE HANDLING
//   CSC-103 Object Oriented Programming  |  UET Lahore KSK
// ============================================================

#include "Helpers.h"
#include "TransactionLog.h"
#include "Inventory.h"

// ============================================================
// FORWARD DECLARATIONS
// ============================================================
void addFragileElectronicsModule (InventorySection& sec, TransactionLog<string>& log);
void addPerishableGroceryModule  (InventorySection& sec, TransactionLog<string>& log);
void addNonPerishableModule      (InventorySection& sec, TransactionLog<string>& log);
void addClothingModule           (InventorySection& sec, TransactionLog<string>& log);
void displayAllModule            (InventorySection& sec);
void compareModule               (InventorySection& sec);
void applyDiscountModule         (InventorySection& sec, TransactionLog<string>& log);
void sortAndSearchModule         (InventorySection& sec);
void warehouseReportModule       (Warehouse& wh, TransactionLog<string>& log);


// ============================================================
// MAIN
// ============================================================
int main()
{
    InventorySection section1(1, 100);
    section1.loadInventoryFromFile();

    Warehouse warehouse(1, 5000.0);
    warehouse.addSection(&section1);

    TransactionLog<string> auditLog;
    int choice;

    do
    {
        system("cls");
        system("color 0B");

        cout << "\n";
        cout << "*****************************************************\n";
        cout << "* INVENTORY MANAGEMENT SYSTEM (FILE HANDLING LOADED)*\n";
        cout << "*****************************************************\n";
        cout << "* 1. Add Fragile Electronics                        *\n";
        cout << "* 2. Add Perishable Grocery                         *\n";
        cout << "* 3. Add Non-Perishable Grocery                     *\n";
        cout << "* 4. Add Clothing Product                           *\n";
        cout << "* 5. Display All Products                           *\n";
        cout << "* 6. Compare Two Products  (operator==)             *\n";
        cout << "* 7. Apply Discount                                 *\n";
        cout << "* 8. Sort & Search                                  *\n";
        cout << "* 9. Warehouse Report                               *\n";
        cout << "* 0. Exit                                           *\n";
        cout << "*****************************************************\n";
        cout << "\nEnter Choice: ";
        choice = inputInteger();

        switch (choice)
        {
        case 1: addFragileElectronicsModule (section1, auditLog); system("pause"); break;
        case 2: addPerishableGroceryModule  (section1, auditLog); system("pause"); break;
        case 3: addNonPerishableModule      (section1, auditLog); system("pause"); break;
        case 4: addClothingModule           (section1, auditLog); system("pause"); break;
        case 5: displayAllModule            (section1);           system("pause"); break;
        case 6: compareModule               (section1);           system("pause"); break;
        case 7: applyDiscountModule         (section1, auditLog); system("pause"); break;
        case 8: sortAndSearchModule         (section1);           system("pause"); break;
        case 9: warehouseReportModule       (warehouse, auditLog);system("pause"); break;
        case 0:
            system("cls");
            system("color 0A");
            cout << "\nThank you for using the Inventory System!\n\n";
            break;
        default:
            system("color 0C");
            cout << "\nInvalid choice. Try again.\n";
            system("pause");
        }

    } while (choice != 0);

    return 0;
}


// ============================================================
// MODULE DEFINITIONS
// ============================================================

void addFragileElectronicsModule(InventorySection& sec, TransactionLog<string>& log)
{
    system("cls");
    system("color 0C");
    cout << "\n--- ADD FRAGILE ELECTRONICS ---\n";

    int    id, qty, voltage, warranty, rating;
    double price;
    char   brand[50];
    string name, packaging;

    cout << "Product ID       : "; id       = inputInteger();
    cout << "Product Name     : "; name     = inputString();
    cout << "Price            : "; price    = inputDouble();
    cout << "Quantity         : "; qty      = inputInteger();
    cout << "Voltage          : "; voltage  = inputInteger();
    cout << "Warranty (years) : "; warranty = inputInteger();
    cout << "Brand Name       : "; inputBrandName(brand, 50);
    cout << "Fragility (1-10) : "; rating   = inputInteger();
    cout << "Packaging Type   : "; packaging = inputString();
    cout << "Supplier ID      : "; int supID = inputInteger();
    cout << "Supplier Name    : "; string supName = inputString();
    cout << "Contract Terms   : "; string supTerms = inputString();

    Supplier sup(supID, supName, supTerms);
    Product* p = new FragileElectronics(id, name, price, qty, voltage, warranty, brand, rating, packaging, sup);
    sec.addStock(p);
    log.recordAction("Added Fragile Electronics: " + name);

    cout << "\n[OK] Fragile Electronics added and saved!\n\n";
}

void addPerishableGroceryModule(InventorySection& sec, TransactionLog<string>& log)
{
    system("cls");
    system("color 0A");
    cout << "\n--- ADD PERISHABLE GROCERY ---\n";

    int    id, qty, calories, temp, halalInput;
    double price;
    bool   halal;
    string name, expiry;

    cout << "Product ID           : "; id       = inputInteger();
    cout << "Product Name         : "; name     = inputString();
    cout << "Price                : "; price    = inputDouble();
    cout << "Quantity             : "; qty      = inputInteger();
    cout << "Calories             : "; calories = inputInteger();
    cout << "Halal? (1=Yes 0=No)  : "; halalInput = inputInteger();
    while (halalInput != 0 && halalInput != 1) { cout << "Enter 1 or 0: "; halalInput = inputInteger(); }
    halal = (bool)halalInput;
    cout << "Expiry (26-Jan-2026) : "; expiry = inputExpiryDate();
    cout << "Storage Temp (C)     : "; temp   = inputInteger();
    cout << "Supplier ID          : "; int supID = inputInteger();
    cout << "Supplier Name        : "; string supName = inputString();
    cout << "Contract Terms       : "; string supTerms = inputString();

    Supplier sup(supID, supName, supTerms);
    Product* p = new PerishableGrocery(id, name, price, qty, calories, halal, expiry, temp, sup);
    sec.addStock(p);
    log.recordAction("Added Perishable Grocery: " + name);

    cout << "\n[OK] Perishable Grocery added and saved!\n\n";
}

void addNonPerishableModule(InventorySection& sec, TransactionLog<string>& log)
{
    system("cls");
    system("color 0E");
    cout << "\n--- ADD NON-PERISHABLE GROCERY ---\n";

    int    id, qty, calories, shelfLife, halalInput;
    double price;
    bool   halal;
    string name, preservative;

    cout << "Product ID           : "; id         = inputInteger();
    cout << "Product Name         : "; name       = inputString();
    cout << "Price                : "; price      = inputDouble();
    cout << "Quantity             : "; qty        = inputInteger();
    cout << "Calories             : "; calories   = inputInteger();
    cout << "Halal? (1=Yes 0=No)  : "; halalInput = inputInteger();
    while (halalInput != 0 && halalInput != 1) { cout << "Enter 1 or 0: "; halalInput = inputInteger(); }
    halal = (bool)halalInput;
    cout << "Shelf Life (years)   : "; shelfLife   = inputInteger();
    cout << "Preservative Level   : "; preservative = inputString();
    cout << "Supplier ID          : "; int supID = inputInteger();
    cout << "Supplier Name        : "; string supName = inputString();
    cout << "Contract Terms       : "; string supTerms = inputString();

    Supplier sup(supID, supName, supTerms);
    Product* p = new NonPerishable(id, name, price, qty, calories, halal, shelfLife, preservative, sup);
    sec.addStock(p);
    log.recordAction("Added Non-Perishable: " + name);

    cout << "\n[OK] Non-Perishable Grocery added and saved!\n\n";
}

void addClothingModule(InventorySection& sec, TransactionLog<string>& log)
{
    system("cls");
    system("color 0D");
    cout << "\n--- ADD CLOTHING PRODUCT ---\n";

    int    id, qty;
    double price;
    string name, sz, fabric, gender;

    cout << "Product ID   : "; id     = inputInteger();
    cout << "Product Name : "; name   = inputString();
    cout << "Price        : "; price  = inputDouble();
    cout << "Quantity     : "; qty    = inputInteger();
    cout << "Size         : "; sz     = inputString();
    cout << "Fabric       : "; fabric = inputString();
    cout << "Gender (Male/Female/Unisex): "; gender = inputString();
    while (gender != "Male" && gender != "Female" && gender != "Unisex")
    { cout << "Enter Male, Female, or Unisex: "; gender = inputString(); }
    cout << "Supplier ID      : "; int supID = inputInteger();
    cout << "Supplier Name    : "; string supName = inputString();
    cout << "Contract Terms   : "; string supTerms = inputString();

    Supplier sup(supID, supName, supTerms);
    Product* p = new ClothingProduct(id, name, price, qty, sz, fabric, gender, sup);
    sec.addStock(p);
    log.recordAction("Added Clothing: " + name);

    cout << "\n[OK] Clothing Product added and saved!\n\n";
}

void displayAllModule(InventorySection& sec)
{
    system("cls");
    system("color 0F");
    cout << "\n--- ALL PRODUCTS ---\n";
    if (sec.totalProducts() == 0)
        cout << "\nNo products yet. Add some first or check inventory_data.txt!\n";
    else
        sec.displayAll();
}

void compareModule(InventorySection& sec)
{
    system("cls");
    system("color 0E");
    cout << "\n--- COMPARE TWO PRODUCTS ---\n";

    if (sec.totalProducts() < 2) { cout << "\nYou need at least 2 products to compare.\n"; return; }

    sec.listIDs();
    int id1, id2;
    cout << "\nFirst Product ID  : "; id1 = inputInteger();
    cout << "Second Product ID : "; id2 = inputInteger();

    Product* p1 = sec.findByID(id1);
    Product* p2 = sec.findByID(id2);

    if (!p1) { cout << "Product ID " << id1 << " not found.\n"; return; }
    if (!p2) { cout << "Product ID " << id2 << " not found.\n"; return; }

    cout << "\n=== PRODUCT 1 ===" << endl;
    p1->displayStatus();
    p1->calculateRisk();

    cout << "\n=== PRODUCT 2 ===" << endl;
    p2->displayStatus();
    p2->calculateRisk();

    cout << "\n=== RESULT ===" << endl;
    if (*p1 == *p2)
        cout << "Both products have the SAME ID.\n";
    else
    {
        cout << "Products are DIFFERENT.\n";
        cout << "Value of " << p1->getProductName() << ": " << p1->calculateValue()
             << "  |  "    << p2->getProductName() << ": " << p2->calculateValue() << "\n";

        if      (p1->getPrice() > p2->getPrice()) cout << "Pricier: " << p1->getProductName() << "\n";
        else if (p2->getPrice() > p1->getPrice()) cout << "Pricier: " << p2->getProductName() << "\n";
        else                                       cout << "Both have equal price.\n";

        if      (p1->getQuantity() > p2->getQuantity()) cout << "More stock: " << p1->getProductName() << "\n";
        else if (p2->getQuantity() > p1->getQuantity()) cout << "More stock: " << p2->getProductName() << "\n";
        else                                             cout << "Equal stock.\n";
    }
    cout << "\n";
}

void applyDiscountModule(InventorySection& sec, TransactionLog<string>& log)
{
    system("cls");
    system("color 0A");
    cout << "\n--- APPLY DISCOUNT ---\n";

    if (sec.totalProducts() == 0) { cout << "No products available.\n"; return; }

    sec.listIDs();
    cout << "\nProduct ID   : "; int id = inputInteger();
    Product* p = sec.findByID(id);
    if (!p) { cout << "Product not found.\n"; return; }

    cout << "Discount (%) : "; double pct = inputDouble();
    p->applyDiscount(pct);
    sec.saveInventoryToFile();
    log.recordAction("Discount applied to product.");
    cout << "\n";
}

void sortAndSearchModule(InventorySection& sec)
{
    system("cls");
    system("color 0B");
    cout << "\n--- SORT & SEARCH ---\n";
    cout << "1. Sort all products by ID\n";
    cout << "2. Search product by ID\n";
    cout << "Choice: ";
    int ch = inputInteger();

    if (ch == 1)
    {
        sec.sortByID();
        sec.displayAll();
    }
    else if (ch == 2)
    {
        sec.listIDs();
        cout << "\nEnter Product ID: ";
        int id = inputInteger();
        Product* p = sec.findByID(id);
        if (p) p->displayStatus();
        else   cout << "Product not found.\n";
    }
    else
        cout << "Invalid choice.\n";
    cout << "\n";
}

void warehouseReportModule(Warehouse& wh, TransactionLog<string>& log)
{
    system("cls");
    system("color 0F");
    cout << "\n--- WAREHOUSE REPORT ---\n";
    cout << "Warehouse ID      : " << wh.getLocationID()         << "\n";
    cout << "Square Footage    : " << wh.getTotalSquareFootage() << " sq ft\n";
    cout << "Total Stock Value : Rs." << wh.getGlobalValue()     << "\n";
    wh.findShortages(5);
    log.printAuditTrail();
    cout << "\n";
}