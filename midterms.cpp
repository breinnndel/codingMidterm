#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Item {
private:
    int id;
    string name;
    int quantity;
    double price;

public:
    static int nextID;

   
    Item(string n, int q, double p) {
        id = nextID++;
        name = n;
        quantity = q;
        price = p;
    }

   
    int getID() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    
    void setQuantity(int q) { quantity = q; }
    void setPrice(double p) { price = p; }

   
    void display() const {
        cout << setw(4) << id
             << setw(20) << name
             << setw(23) << quantity
             << setw(27) << fixed << setprecision(2) << price
             << endl;
    }
};

int Item::nextID = 1;

vector<Item*> inventory;

void addItem() {
    string name;
    int quantity;
    double price;
    cout << "enter name: "; cin >> name;
    cout << "enter quantity: "; cin >> quantity;
    cout << "enter price: "; cin >> price;
    inventory.push_back(new Item(name, quantity, price));
    cout << "item added successfully!" << endl;
}

bool removeItem() {
    int id;
    cout << "enter product ID: "; cin >> id;
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getID() == id) {
            delete *it;
            inventory.erase(it);
            cout << "item removed successfully!" << endl;
            return true;
        }
    }
    cout << "item not found!" << endl;
    return false;
}

void updateItem() {
    int id, newValue;
    char choice;
    cout << "enter product ID: "; cin >> id;
    for (auto& item : inventory) {
        if (item->getID() == id) {
            cout << "update quantity (Q) or price (P)?: "; cin >> choice;
            if (choice == 'Q' || choice == 'q') {
                cout << "enter new quantity: "; cin >> newValue;
                item->setQuantity(newValue);
            } else if (choice == 'P' || choice == 'p') {
                double newPrice;
                cout << "enter new price: "; cin >> newPrice;
                item->setPrice(newPrice);
            }
            cout << "item updated successfully!" << endl;
            return;
        }
    }
    cout << "item not found!" << endl;
}

void searchItem() {
    int id;
    cout << "enter product ID: "; cin >> id;
    for (const auto& item : inventory) {
        if (item->getID() == id) {
            cout << setw(5) << "ID"
                 << setw(20) << "Name"
                 << setw(23) << "Quantity"
                 << setw(26) << "Price" << endl;
            item->display();
            return;
        }
    }
    cout << "item cannot be found!" << endl;
}

void displayAllItems() {
    if (inventory.empty()) {
        cout << "no items found in inventory." << endl;
        return;
    }

    cout << setw(5) << "ID"
         << setw(20) << "Name"
         << setw(23) << "Quantity"
         << setw(26) << "Price" << endl;

    for (const auto& item : inventory) {
        item->display();
    }
}

void displayLowStock() {
    cout << "low stock items (Quantity <= 5):" << endl;
    bool found = false;
    for (const auto& item : inventory) {
        if (item->getQuantity() <= 5) {
            if (!found) {
                cout << setw(5) << "ID"
                     << setw(20) << "Name"
                     << setw(23) << "Quantity"
                     << setw(26) << "Price" << endl;
            }
            item->display();
            found = true;
        }
    }
    if (!found) {
        cout << "no low stock items." << endl;
    }
}

void menu() {
    int choice;
    do {
        cout << "Menu" << endl;
        cout << "1 - add item" << endl;
        cout << "2 - update item" << endl;
        cout << "3 - remove item" << endl;
        cout << "4 - display all items" << endl;
        cout << "5 - search item" << endl;
        cout << "6 - display low stock items" << endl;
        cout << "7 - exit" << endl;
        cout << "enter choice: "; cin >> choice;

        switch (choice) {
            case 1: addItem(); break;
            case 2: updateItem(); break;
            case 3: removeItem(); break;
            case 4: displayAllItems(); break;
            case 5: searchItem(); break;
            case 6: displayLowStock(); break;
            case 7: cout << "exiting program..." << endl; break;
            default: cout << "invalid! try again." << endl;
        }
    } while (choice != 7);
}

int main() {
    menu();
    // cleanup memory
    for (auto& item : inventory) {
        delete item;
    }
    return 0;
}
