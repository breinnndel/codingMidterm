#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

class Item {
private:
    int id;            
    string name;       
    int quantity;      
    double price;      
    string category;  

public:
    static int nextID;  

   
    Item(string n, int q, double p, string c) {
        id = nextID++;      
        name = n;           
        quantity = q;       
        price = p;          
        category = c;       
    }

    
    int getID() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }

    
    void setQuantity(int q) { quantity = q; }
    void setPrice(double p) { price = p; }
    void setCategory(string c) { category = c; }

    void display() const {
        cout << setw(4) << id
             << setw(20) << name
             << setw(23) << quantity
             << setw(27) << fixed << setprecision(2) << price
             << setw(15) << category
             << endl;
    }
};

// Static initialization ng nextID pagkuha ng sunod na ID
int Item::nextID = 1;

vector<Item*> inventory;  

// Bubble sort function na naka base sa pagpili (quantity o price)
void bubbleSort(int choice, bool isDescending) {
    int n = inventory.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            bool shouldSwap = false;

            if (choice == 1) {  // Pagsort base sa quantity
                if ((isDescending && inventory[j]->getQuantity() < inventory[j + 1]->getQuantity()) ||
                    (!isDescending && inventory[j]->getQuantity() > inventory[j + 1]->getQuantity())) {
                    shouldSwap = true;
                }
            } else if (choice == 2) {  // Pagsort base sa price
                if ((isDescending && inventory[j]->getPrice() < inventory[j + 1]->getPrice()) ||
                    (!isDescending && inventory[j]->getPrice() > inventory[j + 1]->getPrice())) {
                    shouldSwap = true;
                }
            }

            
            if (shouldSwap) {
                swap(inventory[j], inventory[j + 1]);
            }
        }
    }
}


void addItem() {
    string name, category;
    int quantity;
    double price;
    cout << "enter name: "; cin >> name;
    cout << "enter category: "; cin >> category;
    cout << "enter quantity: "; cin >> quantity;
    cout << "enter price: "; cin >> price;

    
    inventory.push_back(new Item(name, quantity, price, category));
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
                 << setw(26) << "Price"
                 << setw(15) << "Category" << endl;
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
         << setw(26) << "Price"
         << setw(15) << "Category" << endl;

    
    for (const auto& item : inventory) {
        item->display();
    }
}

// para magdisplay ng low stock items na less than 5 or equal sa 5
void displayLowStock() {
    cout << "low stock items (Quantity <= 5):" << endl;
    bool found = false;

    for (const auto& item : inventory) {
        if (item->getQuantity() <= 5) {
            if (!found) {
                cout << setw(5) << "ID"
                     << setw(20) << "Name"
                     << setw(23) << "Quantity"
                     << setw(26) << "Price"
                     << setw(15) << "Category" << endl;
            }
            item->display();
            found = true;
        }
    }

    if (!found) {
        cout << "no low stock items." << endl;
    }
}

// Function para mag-sort ng items base sa quantity o price at descending o ascending
void sortItems() {
    int sortChoice;
    char orderChoice;
    cout << "Sort items by (1) Quantity or (2) Price? "; cin >> sortChoice;

    
    cout << "Sort in ascending (A) or descending (D) order? ";
    cin >> orderChoice;

    bool isDescending = (orderChoice == 'D' || orderChoice == 'd');
    bubbleSort(sortChoice, isDescending); 
    cout << "Items sorted successfully!" << endl;
}

// Menu function kung saan pipili ng options
void menu() {
    int choice;
    do {
        cout << "Menu" << endl;
        cout << "1 - add item" << endl;
        cout << "2 - update item" << endl;
        cout << "3 - remove item" << endl;
        cout << "4 - display all items" << endl;
        cout << "5 - search item" << endl;
        cout << "6 - sort items" << endl;
        cout << "7 - display low stock items" << endl;
        cout << "8 - exit" << endl;
        cout << "enter choice: "; cin >> choice;

        if (choice < 1 || choice > 8) {
            cout << "Invalid choice! Exiting program..." << endl;
            break;
        }

        switch (choice) {
            case 1: addItem(); break;
            case 2: updateItem(); break;
            case 3: removeItem(); break;
            case 4: displayAllItems(); break;
            case 5: searchItem(); break;
            case 6: sortItems(); break;
            case 7: displayLowStock(); break;
            case 8: cout << "exiting program..." << endl; break;
            default: cout << "invalid! try again." << endl;
        }
    } while (choice >= 1 && choice <= 8); 
}


int main() {
    menu(); // pag tinawag maglloop yung buong program

    
    for (auto& item : inventory) {
        delete item;
    }

    return 0;
}
