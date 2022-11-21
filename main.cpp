#include <iostream>
#include "Staff.h"
#include <conio.h>
#include <vector>

vector<Staff *> staff;
vector<Supply *> supply;


Staff *loginScreen();

Staff *currentUser = NULL;
char currentSelection = 'x';

char menu(Staff *user);

void staffScreen(Staff *user);

void supplyScreen(Staff *user);

void stockScreen(Staff *user);

int main() {
    system("mode 650");
    staff.push_back(new Owner);
    while (true) {
        LOGIN_SCREEN:
        system("cls");
        currentUser = loginScreen();
        MAIN_MENU:
        system("Cls");
        currentSelection = menu(currentUser);
        switch (currentSelection) {
            case '1':
                stockScreen(currentUser);
                goto MAIN_MENU;
            case '2':
                supplyScreen(currentUser);
                goto MAIN_MENU;
            case '3':
                staffScreen(currentUser);
                goto MAIN_MENU;
            case '9':
                goto LOGIN_SCREEN;
            case '0':
                goto END;
        }
    }
    END:;
}

Staff *loginScreen() {
    while (true) {
        string data;
        int id = -1;
        cout << "Enter your Username : ";
        cin >> data;
        cin.ignore();
        for (int i = 0; i < staff.size(); i++) {
            if (data == staff[i]->get_username()) {
                id = i;
                break;
            }
        }
        if (id == -1) {
            cout << "Username not found try again..." << endl;
            system("PAUSE");
            system("CLS");
        } else {
            cout << "Enter your Password : ";
            cin >> data;
            cin.ignore();
            if (data == staff[id]->get_password()) {
                cout << "Login Successful. Logged in as " << staff[id]->get_username() << " ("
                     << staff[id]->get_position() << ")" << endl;
                system("pause");
                return staff[id];
            } else {
                cout << "Password is incorrect try again..." << endl;
                system("PAUSE");
                system("CLS");
            }
        }
    }
}

char menu(Staff *user) {
    cout << "Enter screen you want to enter : " << endl;
    cout << "\t1 - Stock" << endl;
    if (user->get_position() != "Cashier") {
        cout << "\t2 - Supply" << endl;
    }
    if (user->get_position() == "Manager" || user->get_position() == "Owner") {
        cout << "\t3 - Staff" << endl;
    }
    cout << "\t9 - Logout" << endl;
    cout << "\t0 - Exit" << endl;
    cout << "Enter the relevant number..." << endl;
    char selection;
    while (true) {
        selection = getch();
        if (selection == '1' || selection == '9' || selection == '0') {
            break;
        } else if ((selection == '2') && (user->get_position() != "Cashier")) {
            break;
        } else if ((selection == '3') && (user->get_position() == "Manager" || user->get_position() == "Owner")) {
            break;
        }
        cout << "Your input is not valid. Tray again...!!!" << endl;
    }
    system("Cls");
    return selection;
}

void staffScreen(Staff *user) {
    STAFF_SCREEN:
    system("cls");
    char selection = 'x';
    cout << "********************************************************************************************\n\n";

    cout.setf(ios::left);
    cout.width(30);
    cout << "\tFull Name";
    cout.width(15);
    cout << "Position";
    cout.width(15);
    cout << "Joined Date\n" << endl;
    cout.unsetf(ios::left);

    for (int i = 0; i < staff.size(); i++) {
        cout << i + 1 << "\t";
        staff[i]->printDetails();
    }
    cout << "\n\n********************************************************************************************\n"
         << endl;
    if (user->get_position() == "Owner") {
        cout << "Take action," << endl;
        cout << "\t1 - View Transaction Details" << endl;
        cout << "\t2 - Add staff members" << endl;
        cout << "\t3 - Remove staff members" << endl;
        cout << "\t0 - Exit to main menu" << endl;
        selection = getch();
        while (selection != '0' && selection != '1' && selection != '2' && selection != '3') {
            cout << "Input is invalid. Try again..." << endl;
            selection = getch();
        }
        switch (selection) {
            case '0':
                goto EXIT;
            case '2':
                system("cls");
                cout << "Enter the position of the staff member you want to add" << endl;
                cout << "\t1 - Floor Worker" << endl;
                cout << "\t2 - Cashier" << endl;
                cout << "\t3 - Manager" << endl;
                cout << "\t0 - Exit" << endl;
                selection = getch();
                while (selection != '1' && selection != '2' && selection != '3' && selection != '0') {
                    cout << "Input is invalid. Try again..." << endl;
                    selection = getch();
                }
                switch (selection) {
                    case '1':
                        system("cls");
                        staff.push_back(new FloorWorker);
                        goto STAFF_SCREEN;
                    case '2':
                        system("cls");
                        staff.push_back(new Cashier);
                        goto STAFF_SCREEN;
                    case '3':
                        system("cls");
                        staff.push_back(new Manager);
                        goto STAFF_SCREEN;
                    case '0':
                        goto STAFF_SCREEN;
                }
            case '3':
                int employNum;
                cout << "Enter the index of the member you want to remove from above list (Enter 0 to exit)\nIndex : ";
                cin >> employNum;
                cin.ignore();
                while (employNum > staff.size() || employNum <= 1) {
                    if (employNum == 0) {
                        goto STAFF_SCREEN;
                    } else if (employNum == 1) {
                        cout << "You can't remove your self...You are the owner..." << endl;
                    } else {
                        cout << "The value you entered is invalid" << endl;
                    }
                    cout << "\nIndex : ";
                    cin >> employNum;
                    cin.ignore();
                }
                staff.erase(staff.begin() + (employNum - 1));
                goto STAFF_SCREEN;
            case '1':
                goto VIEW_TRANSACTIONS;
        }
    }else{
        cout << "Take action" << endl;
        cout << "\t1 - View Transaction Details" << endl;
        cout << "\t0 - Exit to main menu" << endl;
        selection = getch();
        while (selection != '0' && selection != '1') {
            cout << "Input is invalid. Try again..." << endl;
            selection = getch();
        }
        if(selection=='1'){
            VIEW_TRANSACTIONS:
            int employNum;
            cout << "Enter the index of the member you want to view transaction details from above list (Enter 0 to exit)\nIndex : ";
            cin >> employNum;
            cin.ignore();
            while (employNum > staff.size() || employNum < 1) {
                if (employNum == 0) {
                    goto STAFF_SCREEN;
                } else {
                    cout << "The value you entered is invalid" << endl;
                }
                cout << "\nIndex : ";
                cin >> employNum;
                cin.ignore();
            }
            system("cls");
            staff[employNum-1]->printTransactions();
            system("pause");
            goto STAFF_SCREEN;
        }

    }
    EXIT:
    system("pause");
    system("cls");
}

void supplyScreen(Staff *user) {
    SUPPLY_SCREEN:
    system("cls");
    char selection = 'x';
    cout
            << "****************************************************************************************************************************************************************************************\n\n";

    cout.setf(ios::left);
    cout.width(20);
    cout << "\tItem Name";
    cout.width(15);
    cout << "Amount";
    cout.width(12);
    cout << "Status";
    cout.width(22);
    cout << "Date Arrival";

    cout.width(20);
    cout << "V.Reg no";
    cout.width(15);
    cout << "Vehicle Type";
    cout.width(25);
    cout << "Name Of Origin";
    cout.width(22);
    cout << "Date Dep.";

    cout.width(15);
    cout << "ShipNum";
    cout.width(25);
    cout << "countryOfOrigin";
    cout.width(22);
    cout << "Harbour@" << endl;


    for (int i = 0; i < supply.size(); i++) {
        cout << i + 1 << "\t";
        supply[i]->printDetails();
    }
    cout
            << "\n\n****************************************************************************************************************************************************************************************\n"
            << endl;
    cout << "Take action," << endl;
    cout << "\t1 - Approve Supplies" << endl;
    if (user->get_position() == "Owner") {
        cout << "\t2 - Order Supplies" << endl;
    }
    cout << "\t0 - Return to Main menu" << endl;
    selection = getch();
    while (selection != '0' && selection != '1' && (selection != '2' || user->get_position() != "Owner")) {
        cout << "Input is invalid. Try again..." << endl;
        selection = getch();
    }
    int point = -1;
    switch (selection) {
        case '0':
            goto END;
        case '1':
        ENTER_AGAIN:
            int supplyEntry;
            cout
                    << "Enter the entry of the supply detail you want to approve from above list (Enter 0 to exit)\nIndex : ";
            cin >> supplyEntry;
            cin.ignore();
            while (supplyEntry > supply.size() || supplyEntry < 1) {
                if (supplyEntry == 0) {
                    goto SUPPLY_SCREEN;
                } else {
                    cout << "The value you entered is invalid" << endl;
                }
                cout << "\nIndex : ";
                cin >> supplyEntry;
                cin.ignore();
            }
            if (supply[supplyEntry - 1]->getStatus() == "APPROVED") {
                cout << "The supply is already approved...Try another value..." << endl;
                goto ENTER_AGAIN;
            }
            point = -1;
            for (int i = 0; i < inventory.size(); i++) {
                if ((supply[supplyEntry - 1]->getItem()->getName() == inventory[i]->getName()) &&
                    (supply[supplyEntry - 1]->getItem()->getBrand() == inventory[i]->getBrand())) {
                    point = i;
                    break;
                }
            }
            if (point != -1) {
                supply[supplyEntry - 1]->approve();
                inventory[point]->inc_amount(supply[supplyEntry - 1]->getItem()->getAmount());
                cout << "Amount of item increased in inventory" << endl;
            } else {
                if (user->get_position() == "Floor Worker") {
                    cout
                            << "You cannot add new items to inventory ask a manager to login (or Owner)\nYOU CAN INCREASE THE INVENTORY OF EXISTING ITEMS ONLY"
                            << endl;
                } else {
                    supply[supplyEntry - 1]->approve();
                    inventory.push_back(supply[supplyEntry - 1]->getItem());
                    cout << "Item Added to inventory" << endl;
                }
            }
            system("pause");
            goto SUPPLY_SCREEN;
        case '2':
            system("cls");
            cout << "Are you want to get the supply from locals or import it," << endl;
            cout << "\t1 - Local" << endl;
            cout << "\t2 - Import" << endl;
            selection = getch();
            while (selection != '1' && selection != '2') {
                cout << "Input is invalid. Try again..." << endl;
                selection = getch();
            }
            system("cls");
            cout << "Select the type of the supply" << endl;
            switch (selection) {
                case '1':
                    cout << "\t0 - Produce" << endl;
                    cout << "\t1 - Meet and Seafood" << endl;
                    cout << "\t2 - Grains" << endl;
                    cout << "\t3 - Bakery" << endl;
                    cout << "\t4 - Frozen" << endl;
                    cout << "\t5 - Diary Products" << endl;
                    cout << "\t6 - Snacks and Sweets" << endl;
                    cout << "\t7 - Beverages" << endl;
                    cout << "\t8 - Health and Beauty" << endl;
                    cout << "\t9 - Condiments and Spices" << endl;
                    cout << "\tx - Back to supply screen" << endl;
                    selection = getch();
                    while (selection != '1' && selection != '2' && selection != '3' && selection != '4' &&
                           selection != '5' && selection != '6' && selection != '7' && selection != '8' &&
                           selection != '9' && selection != '0' && selection != 'x' && selection != 'X') {
                        cout << "Input is invalid. Try again..." << endl;
                        selection = getch();
                    }
                    if (!(selection == 'x' || selection == 'X')) {
                        system("cls");
                        supply.push_back(new Local(selection));
                    }
                    goto SUPPLY_SCREEN;
                case '2':
                    cout << "\t2 - Grains" << endl;
                    cout << "\t3 - Bakery" << endl;
                    cout << "\t4 - Frozen" << endl;
                    cout << "\t5 - Diary Products" << endl;
                    cout << "\t6 - Snacks and Sweets" << endl;
                    cout << "\t7 - Beverages" << endl;
                    cout << "\t8 - Health and Beauty" << endl;
                    cout << "\t9 - Condiments and Spices" << endl;
                    cout << "\tx - Back to supply screen" << endl;
                    selection = getch();
                    while (selection != '2' && selection != '3' && selection != '4' &&
                           selection != '5' && selection != '6' && selection != '7' && selection != '8' &&
                           selection != '9' && selection != 'x' && selection != 'X') {
                        cout << "Input is invalid. Try again..." << endl;
                        selection = getch();
                    }
                    if (!(selection == 'x' || selection == 'X')) {
                        system("cls");
                        supply.push_back(new Imported(selection));
                    }
                    goto SUPPLY_SCREEN;
            }
    }

    END:
    system("pause");
    system("cls");
}

void stockScreen(Staff *user) {
    STOCK_SCREEN:
    system("cls");
    char selection = 'x';
    cout << "********************************************************************************************\n\n";
    cout.setf(ios::left);

    cout.width(20);
    cout<<"\tName";
    cout.width(20);
    cout<<"Brand";
    cout.width(15);
    cout<<"Amount";
    cout.width(15);
    cout<<"Retail price";
    cout.width(15);
    cout<<"Discount";
    cout.width(15);
    cout<<"Final Price"<<endl;

    cout.unsetf(ios::left);
    for (int i = 0; i < inventory.size(); i++) {
        cout << i + 1 << "\t";
        inventory[i]->printDetails();
    }
    cout << "\n\n********************************************************************************************\n"
         << endl;
    if(user->get_position()=="Floor Worker"){
        goto END;
    }else{
        cout << "Take action," << endl;
        cout << "\t1 - Create a sale (Transaction)" << endl;
        cout << "\t0 - Back to main menu" << endl;
        selection = getch();
        while (selection != '1' && selection != '0') {
            cout << "Input is invalid. Try again..." << endl;
            selection = getch();
        }
        if(selection=='1'){
            if(inventory.size()>0){
                user->doTransaction();
            }else{
                cout<<"You can't make sales without any stock\nGoto supply and accept some"<<endl;
            }
            system("pause");
            goto STOCK_SCREEN;
        }
    }
    END:
    system("pause");
    system("cls");
}
