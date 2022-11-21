#include<iostream>
#include<string.h>
#include <conio.h>

using namespace std;

string get_input() {
    string userInput;
    getline(cin, userInput);
    return userInput;
}


class Stock {
private:
    float ret_price;
    float disc;
    float finalPrice;
    void setStockData();

protected:
    string name;
    int amount;
    string brand="N/A";
    string localOrImport;

public:
    Stock () {
        setStockData();
        finalPrice=ret_price*(1.f-(disc/100.f));
    }

    string getName()const{return name;}
    string getBrand()const{return brand;}
    int getAmount()const{return amount;}
    float getFinalPrice()const{return finalPrice;}

    virtual void red_amount (int a)=0;
    virtual void inc_amount(int a)=0;

    void printDetails()const;
};

class Produce : public Stock {
public:
    Produce (bool a) {}

    void red_amount (int a) {
        amount -= a;
    }

    void inc_amount (int a) {
        amount += a;
    }
};

class MeatnSeafood : public Stock {
public:
    MeatnSeafood (bool a) {}

    void red_amount (int a) {
        amount -= a;
    }

    void inc_amount (int a) {
        amount += a;
    }
};

class Grains : public Stock {
public:
    Grains (bool a){
        cout.setf(ios::left);

        cout.width(32);
        cout << "Brand Name";
        cout << " : ";
        brand = get_input();

        cout.unsetf(ios::left);

        if(a==true){
            localOrImport = "Imported";
        }else{
            localOrImport = "Local";
        }
    }
    void red_amount (int a) {
        amount -= a;
    }

    void inc_amount (int a) {
        amount += a;
    }
};

class Bakery : public Stock {
public:
    Bakery (bool a){

        cout.setf(ios::left);

        cout.width(32);
        cout << "Brand Name";
        cout << " : ";
        brand = get_input();

        cout.unsetf(ios::left);

        if(a==true){
            localOrImport = "Imported";
        }else{
            localOrImport = "Local";
        }
    }

    void red_amount (int a) {
        amount -= a;
    }

    void inc_amount (int a) {
        amount += a;
    }
};

class Frozen : public Stock {
public:
    Frozen (bool a){
        cout.setf(ios::left);

        cout.width(32);
        cout << "Brand Name";
        cout << " : ";
        brand = get_input();

        cout.unsetf(ios::left);
        if(a==true){
            localOrImport = "Imported";
        }else{
            localOrImport = "Local";
        }
    }

    void red_amount (int a) {
        amount -= a;
    }

    void inc_amount (int a) {
        amount += a;
    }
};

class DairyProducts : public Stock {
public:
    DairyProducts (bool a){
        cout.setf(ios::left);

        cout.width(32);
        cout << "Brand Name";
        cout << " : ";
        brand = get_input();

        cout.unsetf(ios::left);
        if(a==true){
            localOrImport = "Imported";
        }else{
            localOrImport = "Local";
        }
    }

    void red_amount (int a) {
        amount -= a;
    }

    void inc_amount (int a) {
        amount += a;
    }
};

class SnacksSweets : public Stock {
public:
    SnacksSweets (bool a){
        cout.setf(ios::left);

        cout.width(32);
        cout << "Brand Name";
        cout << " : ";
        brand = get_input();

        cout.unsetf(ios::left);
        if(a==true){
            localOrImport = "Imported";
        }else{
            localOrImport = "Local";
        }
    }
    void red_amount (int a) {
        amount -= a;
    }
    void inc_amount (int a) {
        amount += a;
    }
};

class Beverages : public Stock {
public:
    Beverages (bool a){
        cout.setf(ios::left);

        cout.width(32);
        cout << "Brand Name";
        cout << " : ";
        brand = get_input();

        cout.unsetf(ios::left);
        if(a==true){
            localOrImport = "Imported";
        }else{
            localOrImport = "Local";
        }
    }

    void red_amount (int a) {
        amount -= a;
    }

    void inc_amount (int a) {
        amount += a;
    }
};

class HealthBeauty : public Stock {
public:
    HealthBeauty (bool a){
        cout.setf(ios::left);

        cout.width(32);
        cout << "Brand Name";
        cout << " : ";
        brand = get_input();

        cout.unsetf(ios::left);
        if(a==true){
            localOrImport = "Imported";
        }else{
            localOrImport = "Local";
        }
    }

    void red_amount (int a) {
        amount -= a;
    }
    void inc_amount (int a) {
        amount += a;
    }
};

class CondimentsSpices : public Stock {
public:
    CondimentsSpices (bool a){
        cout.setf(ios::left);

        cout.width(32);
        cout << "Brand Name";
        cout << " : ";
        brand = get_input();

        cout.unsetf(ios::left);
        if(a==true){
            localOrImport = "Imported";
        }else{
            localOrImport = "Local";
        }

    }

    void red_amount (int a) {
        amount -= a;
    }

    void inc_amount (int a) {
        amount += a;
    }
};

void Stock::setStockData(){
    cout<<"***********************************************************************************\n"<<endl;

    cout.setf(ios::left);

    cout.width(32);
    cout << "Product Name";
    cout << " : ";
    name = get_input();

    cout.width(32);
    cout << "Retail Price";
    cout << " : ";
    cin>>ret_price;
    cin.ignore();

    cout.width(32);
    cout << "Discount";
    cout << " : ";
    cin>>disc;
    cin.ignore();

    cout.width(32);
    cout << "Amount";
    cout << " : ";
    cin>>amount;
    cin.ignore();

    cout.unsetf(ios::left);

}

void Stock::printDetails() const {
    cout.setf(ios::left);

    cout.width(20);
    cout<<name;
    cout.width(20);
    cout<<brand;
    cout.width(15);
    cout<<amount;
    cout.width(15);
    cout<<ret_price;
    cout.width(15);
    cout<<disc;
    cout.width(15);
    cout<<finalPrice<<endl;

    cout.unsetf(ios::left);
}
