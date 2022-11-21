#include<iostream>
#include "Stock.h"
#include <vector>

using namespace std;

class Supply {
protected:
    string dateOfArrival;
    string status = "PENDING";
    Stock *item;
    int amount;
public:
    Supply(char itemType, bool isImported);

    void approve(){
        status="APPROVED";
    }

    Stock *getItem() const {
        return item;
    }
    string getStatus() const {
        return status;
    }

    virtual void printDetails() const = 0;
};

class Local : public Supply {
private:
    string vehicleType;
    string registrationNum;
    string nameOfOrigin;
    string dateDeparture;
public:
    Local(char itemType);

    void printDetails() const;

};

class Imported : public Supply {
private:
    string shipNum;
    string countryOfOrigin;
    string dateToHarbour;
public:
    Imported(char itemType);

    void printDetails() const;

};

Supply::Supply(char itemType, bool isImported) {
    switch (itemType) {
        case '0':
            item = new Produce(isImported);
            break;
        case '1':
            item = new MeatnSeafood(isImported);
            break;
        case '2':
            item = new Grains(isImported);
            break;
        case '3':
            item = new Bakery(isImported);
            break;
        case '4':
            item = new Frozen(isImported);
            break;
        case '5':
            item = new DairyProducts(isImported);
            break;
        case '6':
            item = new SnacksSweets(isImported);
            break;
        case '7':
            item = new Beverages(isImported);
            break;
        case '8':
            item = new HealthBeauty(isImported);
            break;
        case '9':
            item = new CondimentsSpices(isImported);
            break;
    }
    amount=item->getAmount();

    cout.setf(ios::left);

    cout.width(32);
    cout << "Date of Arrival";
    cout << " : ";
    dateOfArrival = get_input();

    cout.unsetf(ios::left);
}

Local::Local(char itemType) : Supply(itemType, false) {
    cout.setf(ios::left);

    cout.width(32);
    cout << "Vehicle type";
    cout << " : ";
    cout << "1 - Van   2 - Small Truck   3 - Large Truck";
    char selection = getch();
    while (selection != '1' && selection != '2' && selection != '3') {
        selection = getch();
    }
    vehicleType = ((selection == '1') ? "Van" : (selection == '2') ? "Small Truck" : "Large Truck");
    cout << " <" << vehicleType << ">" << endl;

    cout.width(32);
    cout << "Vehicle Registration Number";
    cout << " : ";
    registrationNum = get_input();

    cout.width(32);
    cout << "Origin Place";
    cout << " : ";
    nameOfOrigin = get_input();


    cout.width(32);
    cout << "Date of departure";
    cout << " : ";
    dateDeparture = get_input();

    cout.unsetf(ios::left);

    cout << "\n***********************************************************************************" << endl;
    system("Pause");
    system("cls");
}

Imported::Imported(char itemType) : Supply(itemType, true) {
    cout.setf(ios::left);

    cout.width(32);
    cout << "Ship Number";
    cout << " : ";
    shipNum = get_input();

    cout.width(32);
    cout << "Country of origin";
    cout << " : ";
    countryOfOrigin = get_input();

    cout.width(32);
    cout << "Date to harbour";
    cout << " : ";
    dateToHarbour = get_input();

    cout.unsetf(ios::left);

    cout << "\n***********************************************************************************" << endl;
    system("Pause");
    system("cls");

}

void Local::printDetails() const {
    cout.setf(ios::left);
    cout.width(20);
    cout << item->getName();
    cout.width(15);
    cout << amount;
    cout.width(12);
    cout << status;
    cout.width(22);
    cout << dateOfArrival;

    cout.width(20);
    cout << registrationNum;
    cout.width(15);
    cout << vehicleType;
    cout.width(25);
    cout << nameOfOrigin;
    cout.width(22);
    cout << dateDeparture;

    cout.width(15);
    cout << "N/A";
    cout.width(25);
    cout << "N/A";
    cout.width(22);
    cout << "N/A" << endl;

    cout.unsetf(ios::left);
}

void Imported::printDetails() const {
    cout.setf(ios::left);
    cout.width(20);
    cout << item->getName();
    cout.width(15);
    cout << amount;
    cout.width(12);
    cout << status;
    cout.width(22);
    cout << dateOfArrival;

    cout.width(20);
    cout << "N/A";
    cout.width(15);
    cout << "N/A";
    cout.width(25);
    cout << "N/A";
    cout.width(22);
    cout << "N/A";

    cout.width(15);
    cout << shipNum;
    cout.width(25);
    cout << countryOfOrigin;
    cout.width(22);
    cout << dateToHarbour << endl;

    cout.unsetf(ios::left);
}
