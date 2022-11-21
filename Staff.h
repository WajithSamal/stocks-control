#include <iostream>
#include <vector>
#include "Supply.h"

vector<Stock *> inventory;

using namespace std;

struct itemDetails {
    string itemName;
    int quantity;
    float total;

    itemDetails(Stock *item) {
        cout.setf(ios::left);
        itemName = item->getName();
        cout.width(30);
        cout << "Quantity selling";
        cout << " : ";
        cin >> quantity;
        cin.ignore();
        while (quantity < 1 || quantity > item->getAmount()) {
            cout << "<Quantity must be greater than 1 and less than or equal to available stock " << item->getAmount()
                 << ">" << endl;
            cout.width(30);
            cout << "Quantity selling";
            cout << " : ";
            cin >> quantity;
            cin.ignore();
        }

        item->red_amount(quantity);
        total = item->getFinalPrice() * quantity;
        cout.unsetf(ios::left);
    }
};

struct transaction {
    string customerName;
    vector<itemDetails *> items;
    float grandTotal;

    transaction() {
        cout.setf(ios::left);
        cout.width(30);
        cout << "Customer name";
        cout << " : ";
        customerName = get_input();

        ADD_TRANSACTION:
        int stockEntry;
        cout
                << "Enter the entry of the item detail you want to sell from above list (Enter 0 to end current transaction)"
                << endl;
        cout.width(30);
        cout << "Index";
        cout << " : ";
        cin >> stockEntry;
        cin.ignore();
        while (stockEntry > inventory.size() || stockEntry < 1) {
            if (stockEntry == 0) {
                if (items.size() == 0) {
                    cout << "Add at least add one item to sell" << endl;
                    goto ADD_TRANSACTION;
                }
                goto END;
            } else {
                cout << "The value you entered is invalid" << endl;
            }
            cout.width(30);
            cout << "Index";
            cout << " : ";
            cin >> stockEntry;
            cin.ignore();
        }
        cout.unsetf(ios::left);
        items.push_back(new itemDetails(inventory[stockEntry - 1]));
        if (inventory[stockEntry - 1]->getAmount() == 0) {
            inventory.erase(inventory.begin() + (stockEntry - 1));
        }
        goto ADD_TRANSACTION;
        END:
        grandTotal = 0;
        for (int i = 0; i < items.size(); i++) {
            grandTotal += items[i]->total;
        }
    }
};


class Staff {
private:
    string username;
    string password;
    string full_name;
    string joined_date;

    void set_data();


protected:
    string position;

public:
    Staff() {
        set_data();
    }

    string get_username() const;

    string get_password() const;

    string get_position() const;

    void printDetails() const;

    virtual void doTransaction() = 0;

    virtual void printTransactions() = 0;
};

string Staff::get_username() const {
    return username;
}

string Staff::get_password() const {
    return password;
}

string Staff::get_position() const {
    return position;
}

void Staff::printDetails() const {
    cout.setf(ios::left);
    cout.width(30);
    cout << full_name;
    cout.width(15);
    cout << position;
    cout.width(15);
    cout << joined_date << endl;
    cout.unsetf(ios::left);
}

void Staff::set_data() {
    cout << "***********************************************************************************" << endl;
    cout << "\t\tEnter the data of the staff member adding" << endl;
    cout << "***********************************************************************************\n" << endl;
    cout.setf(ios::left);

    cout.width(20);
    cout << "Enter Full Name";
    cout << " : ";
    full_name = get_input();

    cout.width(20);
    cout << "Enter Joined Date";
    cout << " : ";
    joined_date = get_input();

    cout.width(20);
    cout << "Enter Username";
    cout << " : ";
    username = get_input();

    cout.width(20);
    cout << "Enter password";
    cout << " : ";
    password = get_input();

    cout.unsetf(ios::left);

    cout << "\n\nNew staff member " << full_name << " added.\n" << endl;
    cout << "\n\n***********************************************************************************" << endl;

    system("pause");
    system("cls");

}

class FloorWorker : public Staff {
public:
    FloorWorker() {
        position = "Floor Worker";
    }

    void printTransactions() {
        cout << "No access" << endl;
    }

    void doTransaction() {
        cout << "No access" << endl;
    }
};


class Cashier : public Staff {
private:
    vector<transaction *> transactions;
public:
    Cashier() {
        position = "Cashier";
    }

    void doTransaction() {
        transactions.push_back(new transaction);
    }

    void printTransactions();
};


class Manager : public Staff {
private:
    vector<transaction *> transactions;
public:
    Manager() {
        position = "Manager";
    }

    void doTransaction() {
        transactions.push_back(new transaction);
    }

    void printTransactions();
};

class Owner : public Staff {
private:
    vector<transaction *> transactions;
public:
    Owner() {
        position = "Owner";
    }

    void doTransaction() {
        transactions.push_back(new transaction);
    }

    void printTransactions();
};

void Owner::printTransactions() {
    system("Cls");
    cout << "********************************************************************************************\n\n";

    cout.setf(ios::left);

    cout.width(30);
    cout << "\tCustomer name";
    cout.width(20);
    cout << "Items";
    cout.width(15);
    cout << "Quantity";
    cout.width(15);
    cout << "Sub-Total";
    cout.width(15);
    cout << "Total\n" << endl;

    for (int i = 0; i < transactions.size(); i++) {
        cout << i + 1 << "\t";
        for (int j = 0; j < transactions[i]->items.size(); j++) {
            if (j == 0 && j != transactions[i]->items.size() - 1) {
                cout.width(30);
                cout << transactions[i]->customerName;
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout << " " << endl;
            } else if (j == transactions[i]->items.size() - 1 && j != 0) {
                cout << "\t";
                cout.width(30);
                cout << " ";
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout << transactions[i]->grandTotal << endl;
            } else if (j == 0 && j == transactions[i]->items.size() - 1) {
                cout.width(30);
                cout << transactions[i]->customerName;
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout <<transactions[i]->grandTotal<< endl;
            } else {
                cout << "\t";
                cout.width(30);
                cout << " ";
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout << " " << endl;
            }
        }
    }

    cout.unsetf(ios::left);
}

void Manager::printTransactions() {
    system("Cls");
    cout << "********************************************************************************************\n\n";

    cout.setf(ios::left);

    cout.width(30);
    cout << "\tCustomer name";
    cout.width(20);
    cout << "Items";
    cout.width(15);
    cout << "Quantity";
    cout.width(15);
    cout << "Sub-Total";
    cout.width(15);
    cout << "Total\n" << endl;

    for (int i = 0; i < transactions.size(); i++) {
        cout << i + 1 << "\t";
        for (int j = 0; j < transactions[i]->items.size(); j++) {
            if (j == 0 && j != transactions[i]->items.size() - 1) {
                cout.width(30);
                cout << transactions[i]->customerName;
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout << " " << endl;
            } else if (j == transactions[i]->items.size() - 1 && j != 0) {
                cout << "\t";
                cout.width(30);
                cout << " ";
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout << transactions[i]->grandTotal << endl;
            } else if (j == 0 && j == transactions[i]->items.size() - 1) {
                cout.width(30);
                cout << transactions[i]->customerName;
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout <<transactions[i]->grandTotal<< endl;
            } else {
                cout << "\t";
                cout.width(30);
                cout << " ";
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout << " " << endl;
            }
        }
    }

    cout.unsetf(ios::left);
}

void Cashier::printTransactions() {
    system("Cls");
    cout << "********************************************************************************************\n\n";

    cout.setf(ios::left);

    cout.width(30);
    cout << "\tCustomer name";
    cout.width(20);
    cout << "Items";
    cout.width(15);
    cout << "Quantity";
    cout.width(15);
    cout << "Sub-Total";
    cout.width(15);
    cout << "Total\n" << endl;

    for (int i = 0; i < transactions.size(); i++) {
        cout << i + 1 << "\t";
        for (int j = 0; j < transactions[i]->items.size(); j++) {
            if (j == 0 && j != transactions[i]->items.size() - 1) {
                cout.width(30);
                cout << transactions[i]->customerName;
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout << " " << endl;
            } else if (j == transactions[i]->items.size() - 1 && j != 0) {
                cout << "\t";
                cout.width(30);
                cout << " ";
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout << transactions[i]->grandTotal << endl;
            } else if (j == 0 && j == transactions[i]->items.size() - 1) {
                cout.width(30);
                cout << transactions[i]->customerName;
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout <<transactions[i]->grandTotal<< endl;
            } else {
                cout << "\t";
                cout.width(30);
                cout << " ";
                cout.width(20);
                cout << transactions[i]->items[j]->itemName;
                cout.width(15);
                cout << transactions[i]->items[j]->quantity;
                cout.width(15);
                cout << transactions[i]->items[j]->total;
                cout.width(15);
                cout << " " << endl;
            }
        }
    }

    cout.unsetf(ios::left);
}
