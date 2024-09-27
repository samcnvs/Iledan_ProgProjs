/* CC 212/211L PROJECT # 1 – Application of ADT LIST Operations – THE ATM SIMULATION
Submitted by:
ILEDAN, SAMANTHA
TIAMSON, DANNAH JANELLE
BSIS 2A
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <ctime>
#include <chrono> //for exit countdown
#include <thread> //for exit countdown
#include <conio.h>
#define MAX 50

using namespace std;

typedef struct Account {
    int acc_no;
    string name;
    string birthday;
    string contact_no;
    double balance;
    int pin_code;
} DETAILS;

typedef struct Account_List {
    DETAILS ad[MAX];
} LIST;

class MyATM {
private:
public:
    void registration(LIST& accounts); // creation of account
    bool findCard(LIST& accounts, const string& filename);
    void save(LIST& accounts, const string& filename);
    double getBalance(LIST& accounts, int acc_no);
    bool logIn(const LIST& accounts, int& acc_no, int& pin_code);
    bool withdraw(LIST& accounts, int acc_no, double amount);
    void deposit(LIST& accounts,int acc_no, double deposit_amount);
    void transferFunds(LIST& accounts, int acc_no, int receiver, double transfer_amount);
    bool changePin_code(LIST& accounts, int acc_no, double newPin_code);
    void displayAccount_info(LIST& accounts, int acc_no);

    int get_randomnum(unsigned int seed){
        random_device num;
        mt19937 gen(seed);
        uniform_int_distribution<int> dst(10000, 99999);
        return dst(gen);
    }

    void welcomeDisplay(){
    system("cls");
    std::cout << "\n\n\n\n\n\t\t\t\t|\033[47m                                                                                                                  \033[0m|" << std::endl;
    std::cout << "\t\t\t\t|\033[46m                                                                                                                  \033[0m|\n" << std::endl;
    std::cout << "\t\t\t      ##     ## ##### ##    ###### ####### ###  ### #####    ###### #######     \033[36m######       ######    ###### ###### ##     ## \033[0m" << std::endl;
    std::cout << "\t\t\t      ##  #  ## ##    ##    ##     ##    # ## ##  # ##         ##   ##    #     \033[36m##   ##      ##        ##  ##   ##   ###   ### \033[0m" << std::endl;
    std::cout << "\t\t\t      ## # # ## ##### ##    ##     ##    # ## ##  # #####      ##   ##    #     \033[36m##   ## \033[37m####\033[33m \033[36m######    ######   ##   ######### \033[0m" << std::endl;
    std::cout << "\t\t\t      ###   ### ##    ##    ##     ##    # ## ##  # ##         ##   ##    #     \033[36m##   ## \033[37m####\033[33m     \033[36m##    ##  ##   ##   ##  #  ## \033[0m" << std::endl;
    std::cout << "\t\t\t      ##     ## ##### ##### ###### ####### ## ##  # #####      ##   #######     \033[36m######       ######    ##  ##   ##   ##  #  ## \033[0m" << std::endl;
    std::cout << "\n\t\t\t\t|\033[46m                                                                                                                  \033[0m|" << std::endl;
    std::cout << "\t\t\t\t|\033[47m                                                                                                                  \033[0m|\n" << std::endl;
    std::cout << "\n\t\t\t\t.\033[47m==================================================================================================================\033[0m." << std::endl;
    std::cout << "\t\t\t\t.\033[47;30m                                         EXPERIENCE EXCELLENCE WITH D&S ATM.                                      \033[0m." << std::endl;
    std::cout << "\t\t\t\t.\033[47;30m                             DEPENDABILITY IN EVERY TRANSACTION, SECURITY AT EVERY TURN.                          \033[0m." << std::endl;
    std::cout << "\t\t\t\t.\033[47m==================================================================================================================\033[0m\033[0m." << std::endl;
    std::cout << " \n\n\t\t\t\t\t\t\t\t\t ";
    displayLoadingScreen("    ", 2);
}

    void transactionDisplay(){
    system("cls");
    std::cout << "\n\n\n\n\n\t\t\t\t|\033[47m                                                                                                                  \033[0m|" << std::endl;
    std::cout << "\t\t\t\t|\033[46m                                                                                                                  \033[0m|\n" << std::endl;
    std::cout << "\t\t\t\t\t\t ######## #####   ######  ##   ## ###### ###### ###### ######## ## ###### ##   ##" << std::endl;
    std::cout << "\t\t\t\t\t\t    ##    ##   #  ##   #  ###  ## ##     ##   # ##        ##    ## ##   # ###  ## " << std::endl;
    std::cout << "\t\t\t\t\t\t    ##    #####   ######  ####### ###### ###### ##        ##    ## ##   # #######" << std::endl;
    std::cout << "\t\t\t\t\t\t    ##    ##  ##  ##   #  ##  ###     ## ##   # ##        ##    ## ##   # ##  ###" << std::endl;
    std::cout << "\t\t\t\t\t\t    ##    ##  ##  ##   #  ##   ## #####  ##   # ######    ##    ## ###### ##   ##" << std::endl;
    std::cout << "\n\t\t\t\t|\033[47m                                                                                                                  \033[0m|" << std::endl;
    std::cout << "\t\t\t\t|\033[46m                                                                                                                  \033[0m|\n" << std::endl;
    displayLoadingScreen("    ", 2);
}


    void displayLoadingScreen(const string& message, int durationSeconds) {
    cout << message << endl;
    string animation = "/- \\|";
    int animationIndex = 0;

    auto start = chrono::steady_clock::now();
    while (true) {
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();
        if (elapsed >= durationSeconds) {
        break;
        }

        cout << "\r" << "\t\t\t\t\t\t\t\t\t\t\t  " << animation[animationIndex] << flush;
        this_thread::sleep_for(chrono::milliseconds(250));  // Delay to control animation speed
        animationIndex = (animationIndex + 1) % animation.size();
    }
}

    int exitDisplay(){
                std::cout << "\n\n\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m ######  ##    ##  ## ######## ##  ##    ##   ######        \033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m ##       ##  ##   ##    ##    ##  ###   ##  ##             \033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m ####       ##     ##    ##    ##  ##### ##  ##  ###        \033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m ##       ##  ##   ##    ##    ##  ## #####  ##   ##        \033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m ######  ##    ##  ##    ##    ##  ##   ###  ######  ## ##  \033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";

                while(true){
                    int countdown;
                    countdown = 5; //initial countdown before exit

                     while(countdown >0){
                        std::cout << "\n\t\t\t\t\t\t\t\t   Exiting Transaction in \033[31m" << countdown << " \033[0mseconds..." << std::endl;

                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        countdown--;
                     }
                    std::cout << "\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";
                    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                ATM Transaction has ended.                  \033[47m   \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m       Thank you for using D&S ATM. Have a great day!       \033[47m   \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";
                    return 0;
                }
    }
};


bool MyATM::findCard(LIST& accounts, const string& filename) {
    ifstream file(filename);

    if (!file) {
        return false;
    }

    int count = 0;
    while (count < MAX) {
        DETAILS& ad = accounts.ad[count];
        if (file >> ad.acc_no) {
            file.ignore();
            getline(file, ad.name);

            if (file >> ad.birthday >> ad.contact_no >> ad.balance >> ad.pin_code) {
                count++;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    file.close();
    return true;
}

void MyATM::registration(LIST& accounts) {
    DETAILS newAccount;

    system("cls");
    welcomeDisplay();
    system("cls");
    cout << "\n\n" << endl;
    std::cout << "\n\n\n\n\t\t\t\t|\033[47m                                                                                                                  \033[0m|" << std::endl;
    std::cout << "\t\t\t\t|\033[46m                                                                                                                  \033[0m|\n" << std::endl;
    std::cout << "\t\t\t\t\t     ######  #######  ######   ## ####### ######## ######  ####### ######## ## ####### ##    ##" << std::endl;
    std::cout << "\t\t\t\t\t     ##    # ##      ##        ## ##         ##    ##    # ##    #    ##    ## ##    # ###   ##" << std::endl;
    std::cout << "\t\t\t\t\t     ######  #####   ##   ###  ## #######    ##    ######  #######    ##    ## ##    # ########" << std::endl;
    std::cout << "\t\t\t\t\t     ## ##   ##      ##     #  ##      ##    ##    ## ##   ##    #    ##    ## ##    # ##  ####" << std::endl;
    std::cout << "\t\t\t\t\t     ##  ##  ####### #######   ## #######    ##    ##  ##  ##    #    ##    ## ####### ##    ##" << std::endl;
    std::cout << "\n\t\t\t\t|\033[47m                                                                                                                  \033[0m|" << std::endl;
    std::cout << "\t\t\t\t|\033[46m                                                                                                                  \033[0m|\n" << std::endl;

    std::cout << "\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                      > REGISTRATION <                      \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;

    std::cout << "\n\t\t\t\t.\033[47m==================================================================================================================\033[0m." << std::endl;
    std::cout << "\t\t\t\t.\033[47;30m                                     MAKE SURE YOUR CARD IS INSERTED.                                             \033[0m." << std::endl;
    std::cout << "\t\t\t\t.\033[47m==================================================================================================================\033[0m\033[0m." << std::endl;

    time_t now = time(NULL);
    newAccount.acc_no = get_randomnum(now);

    std::cout << "\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\t\t\t\t\t\t\t\033[36m                Your Account Number:   \033[0m" << newAccount.acc_no << endl;

    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\t\t\t\t\t\t\t                Enter Account Details: \n  ";

    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\t\t\t\t\t\t\t                Name:  ";
    cin.ignore();
    getline(cin, newAccount.name);

    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\t\t\t\t\t\t\t                Birthday (DD-MM-YYYY):  ";
    cin >> newAccount.birthday;

    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\t\t\t\t\t\t\t                Contact Number:  ";

    cin >> newAccount.contact_no;
    newAccount.balance = 5000;

    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\t\t\t\t\t\t\t                PIN Code:  ";

    while(!(cin >> newAccount.pin_code)||newAccount.pin_code<1000||newAccount.pin_code>9999){

        std::cout << "\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                        INVALID INPUT.                      \033[0m\033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m        LEADING ZEROS NOT ALLOWED. ENTER 4 DIGITS ONLY.     \033[0m\033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
        std::cout << "\n\t\t\t\t\t\t\t\t\t ENTER PIN CODE AGAIN:  ";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

}

    for (int i = 0; i < MAX; i++) {
        if (accounts.ad[i].acc_no == 0) {
            accounts.ad[i] = newAccount;
            std::cout << "\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[32m               ACCOUNT CREATED SUCCESSFULLY.                \033[0m\033[47m   \033[0m" << std::endl;
            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
            std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
            std::cout << "\n\t\t\t\t\t\t\t\t\t> ";
            system("pause");
            return;
        }
    }

    std::cout << "\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                   ACCOUNT LIST IS FULL.                    \033[0m\033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\n\t\t\t\t\t\t\t\t\t<  ";
    system("pause");
    return;
}

void MyATM::save(LIST& accounts, const string& filename) {
    ofstream file(filename, ios::out);

    if (!file) {
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                             ERROR:                         \033[0m\033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                    UNABLE TO OPEN FILE.                    \033[0m\033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
        std::cout << "\n\t\t\t\t\t\t\t\t\t> ";
        system("pause");
        return;
    }

    for (int i = 0; i < MAX; i++) {
        const DETAILS& ad = accounts.ad[i];
        if (ad.acc_no == 0) {
            break;
        }
        file << ad.acc_no << "\n";
        file << ad.name << "\n";
        file << ad.birthday << " " << ad.contact_no << " " << ad.balance << " " << ad.pin_code << "\n";
        file << "\n";
    }
    file.close();
    std::cout << "\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[32m               CHANGES SAVED SUCCESSFULLY.                  \033[0m\033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
    std::cout << "\n\t\t\t\t\t\t\t\t\t> ";
    system("pause");
}

bool MyATM::logIn(const LIST& accounts, int& acc_no, int& pin_code){
    std::cout << "\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                     Enter Account Number:                  \033[47m   \033[0m";
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t    ";

    cin >> acc_no;
    std::cout << "\n\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";

    std::cout << "\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                        Enter PIN Code:                     \033[47m   \033[0m";
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t    ";

    char c;
    string inputPin;
    while(true){
        c = _getch();
        if (c == 13)
            break;
        if (c == 8) {
            if (inputPin.length() > 0) {
                inputPin.pop_back();
                cout << "\b \b";
            }
        } else if (isdigit(c) && inputPin.length() < 4) {
            inputPin += c;
            cout << "*";
        }
    }

    pin_code = stoi(inputPin);

    std::cout << "\n\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";
    for (int i = 0; i < MAX; i++) {
        const DETAILS& ad = accounts.ad[i];
        if (ad.acc_no == acc_no && ad.pin_code == pin_code) {
            return true;
        }
    }
    return false;
}


double MyATM::getBalance(LIST& accounts, int acc_no) {
    for (int i = 0; i < MAX; i++) {
            DETAILS& ad = accounts.ad[i];
            if (ad.acc_no == acc_no) {
                return ad.balance;
            }}
            }

void MyATM:: displayAccount_info(LIST& accounts, int acc_no){
for (int i = 0; i < MAX; i++) {
        DETAILS& ad = accounts.ad[i];
        if (ad.acc_no == acc_no) {
            std::cout << "\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
            std::cout << "\t\t\t\t\t\t\t                Your Account Number:   " << ad.acc_no << endl;

            std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
            std::cout << "\t\t\t\t\t\t\t                Name:  " << ad.name << endl;

            std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
            std::cout << "\t\t\t\t\t\t\t                Birthday:  " << ad.birthday << endl;

            std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
            std::cout << "\t\t\t\t\t\t\t                Contact Number:  " << ad.contact_no << endl;

            std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
            std::cout << "\t\t\t\t\t\t\t                Balance:  " << ad.balance << endl;

            std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
            std::cout << "\t\t\t\t\t\t\t                PIN Code:  ";
            for (size_t j = 0; j < to_string(ad.pin_code).length(); j++) {
                cout << "*";
            }
            std::cout << "\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
            cout << endl;

}}}


bool MyATM::withdraw(LIST& accounts, int acc_no, double amount){
        for (int i = 0; i < MAX; i++){
        DETAILS& ad = accounts.ad[i];
            if (ad.acc_no == acc_no) {
                if(ad.balance >= amount){
                ad.balance -= amount;
                return true;
            }else{
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                   WITHDRAWAL UNSUCCESSFUL.                 \033[0m\033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                     INSUFFICIENT FUNDS.                    \033[0m\033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                std::cout << "\n\t\t\t\t\t\t\t\t\t> ";
                system("pause");
                return false;
            }
            }
        }
    }

void MyATM::deposit(LIST& accounts,int acc_no, double deposit_amount){
        for(int i = 0; i < MAX; i++){
                DETAILS& ad = accounts.ad[i];
            if(ad.acc_no == acc_no){
                ad.balance += deposit_amount;
                return;
            }
        }
    }

void MyATM::transferFunds(LIST& accounts, int acc_no, int receiver, double transfer_amount){
    DETAILS* sender = nullptr;
    DETAILS* recipient = nullptr;

    for(int i = 0; i < MAX; i++){
            if(accounts.ad[i].acc_no==acc_no){
                sender= &accounts.ad[i];
            }
            if(accounts.ad[i].acc_no==receiver){
                recipient= &accounts.ad[i];
            }}
    if(sender && recipient){
        if(sender->balance >= transfer_amount){
            sender->balance -= transfer_amount;
            recipient->balance += transfer_amount;
            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[32m                     TRANSFER SUCCESSFUL.                   \033[0m\033[47m   \033[0m" << std::endl;
            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
            std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m ";
            return;

        } else{
            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m            INSUFFICIENT BALANCE FOR THE TRANSFER.          \033[0m\033[47m   \033[0m" << std::endl;
            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
            std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m ";
            return;

        }
    } else {
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                         RECIPIENT NOT FOUND.               \033[0m\033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m ";
        return;
    }

}

bool MyATM::changePin_code(LIST& accounts, int acc_no, double newPin_code){
    if(newPin_code >= 1000 && newPin_code <= 9999){
        for (int i = 0; i < MAX; i++) {
                if(accounts.ad[i].acc_no==acc_no){
                    accounts.ad[i].pin_code = newPin_code;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[32m                PIN CODE CHANGED SUCCESSFULLY.              \033[0m\033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m ";
        return true;
                }
        }
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                      ACCOUNT NOT FOUND.                    \033[0m\033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m ";

        }else{
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                        INVALID INPUT.                      \033[0m\033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m        LEADING ZEROS NOT ALLOWED. ENTER 4 DIGITS ONLY.     \033[0m\033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
        }
        return false;
}

int main() {
    LIST accounts;
    MyATM pm;
    const string filename = "D:/MyATM/pin_code.txt";

    if (pm.findCard(accounts, filename)) {
            pm.welcomeDisplay();
            std::cout << "\n\t\t\t\t\t\t                  "<<"\033[32m          CARD SCANNED SUCCESSFULLY.               \033[0m"<< "\n";
            std::cout << "\t\t\t\t\t\t\t     \033[47m                                                          \033[0m ";
            std::cout << "\n\t\t\t\t\t\t\t\t\t> ";
            system("pause");

    } else {
        std::cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t                                                               " << std::endl;
        std::cout << "\t\t\t\t\t\t                        PLEASE INSERT CARD.                       " << std::endl;
        std::cout << "\t\t\t\t\t\t                        ACCOUNT NOT FOUND.                                 " << std::endl;
        std::cout << "\t\t\t\t\t\t                                                                      " << std::endl;
        std::cout << "\n\t\t\t\t\t\t\t\t> ";
        system("pause");
        int y_n;

        system("cls");
        std::cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\033[47m                                                 \033[0m \n" ;
        std::cout << "\t\t\t\t\t\t\t\033[47m    \033[0m                                         \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\033[47m    \033[0m   WOULD YOU LIKE TO CREATE AN ACCOUNT?  \033[47m    \033[0m"<< std::endl;
        std::cout << "\t\t\t\t\t\t\t\033[47m    \033[0m                                         \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\033[47m                                                 \033[0m\n\n\t\t\t\t\t\t\t\t\t\t\t" ;
        std::cout << "\n\t\t\t\t\t\t\t\t\033[47m                               \033[0m \n" ;
        std::cout << "\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\033[47m    \033[0m\033[32m   > (1) YES           \033[0m\033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\033[47m    \033[0m\033[31m   > (2) NO            \033[0m\033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\033[47m                               \033[0m \n" ;
        std::cout << "\n\t\t\t\t\t\t\t\t ";
        cin >> y_n;

            switch (y_n) {
            case 1:
                pm.registration(accounts);
                pm.save(accounts, filename);
                break;

            case 2:
                return true;
                break;

            default:

                std::cout << "\n\t\t\t\t\t\t\t\t\t  \033[47m                               \033[0m \n";
                std::cout << "\t\t\t\t\t\t\t\t\t  \033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t\t\t\t  \033[47m    \033[0m\033[31m     Invalid Choice.   \033[0m\033[47m    \033[0m"<< std::endl;
                std::cout << "\t\t\t\t\t\t\t\t\t  \033[47m    \033[0m\033[31m    Please try again.  \033[0m\033[47m    \033[0m"<< std::endl;
                std::cout << "\t\t\t\t\t\t\t\t\t  \033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t\t\t\t  \033[47m                               \033[0m" << std::endl;
                std::cout << "\n\t\t\t\t\t\t\t\t\t   > ";
                system("pause");
        }
    }

int choice;
while (true) {
        pm.welcomeDisplay();system("cls");
        std::cout << "\n\n\n\n\n\t\t\t\t|\033[47m                                                                                                                  \033[0m|" << std::endl;
        std::cout << "\t\t\t\t|\033[46m                                                                                                                  \033[0m|\n" << std::endl;
        std::cout << "\t\t\t\t\t\t\t ######  ########  ###   ###       ###   ###  ######  ##    ##  ##   ##" << std::endl;
        std::cout << "\t\t\t\t\t\t\t ##  ##     ##     ## # # ##       ## # # ##  ##      ###   ##  ##   ##" << std::endl;
        std::cout << "\t\t\t\t\t\t\t ######     ##     ## # # ## ##### ## # # ##  #####   ##### ##  ##   ##" << std::endl;
        std::cout << "\t\t\t\t\t\t\t ##  ##     ##     ##  #  ##       ##  #  ##  ##      ########  ##   ##" << std::endl;
        std::cout << "\t\t\t\t\t\t\t ##  ##     ##     ##  #  ##       ##  #  ##  ######  ##   ###   #####" << std::endl;
        std::cout << "\n\t\t\t\t|\033[47m                                                                                                                  \033[0m|" << std::endl;
        std::cout << "\t\t\t\t|\033[46m                                                                                                                  \033[0m|\n" << std::endl;

        std::cout << "\n\t\t\t\t\t\t\t\t\t\033[47m                               \033[0m \n" ;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   > (1) Registration  \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   > (2) Transaction   \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   > (3) Exit/Cancel   \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m                               \033[0m \n" ;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   Input your choice:  \033[47m    \033[0m"<< std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
        std::cout << "\t\t\t\t\t\t\t\t\t\033[47m                               \033[0m\n\n\t\t\t\t\t\t\t\t\t\t\t" ;

        cin >> choice;

        switch (choice) {
            case 1:
                pm.registration(accounts);
                pm.save(accounts, filename);
                pm.displayLoadingScreen("    ", 3);
                break;

            case 2:
                system("cls");
                int acc_no, pin_code;
                pm.transactionDisplay();

                if (pm.logIn(accounts, acc_no, pin_code)) {
                    std::cout << "\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";
                    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[32m                     LOG IN SUCCESSFUL.                     \033[0m\033[47m   \033[0m";
                    std::cout << "\n\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";
                    std::cout << " \n\n\t\t\t\t\t\t\t\t\t> ";
                    system("pause");


                    int t_menu;

                    while(true){
                    system("cls");
                    pm.transactionDisplay();
                    std::cout << "\n\t\t\t\t\t\t\t\t\t\033[47m                                    \033[0m \n" ;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   > (1) Balance Inquiry    \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   > (2) Withdraw           \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   > (3) Deposit            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   > (4) Fund Transfer      \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   > (5) Change PIN Code    \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   > (6) Show Account Info  \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m   > (7) Back to Main Menu  \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m                                    \033[0m \n" ;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m      Input your choice:    \033[47m    \033[0m"<< std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                            \033[47m    \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t\t\t\t\033[47m                                    \033[0m\n\n\t\t\t\t\t\t\t\t\t\t\t " ;
                        cin >> t_menu;
                        switch(t_menu){

                    //BALANCE INQUIRY
                    case 1:
                        system("cls");
                        pm.transactionDisplay();
                        std::cout << "\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                     > BALANCE INQUIRY <                    \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                       CURRENT BALANCE:                     \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[32m                            " << pm.getBalance(accounts, acc_no) << "\t                    \033[0m\033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m ";
                        std::cout << "\n\n\t\t\t\t\t\t\t\t\t>   ";
                        system("pause");
                        break;

                    //WITHDRAW
                    case 2:
                        double amount;
                        bool success;
                        system("cls");
                        pm.transactionDisplay();
                        std::cout << "\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                        > WITHDRAW <                        \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;

                        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                   Input Withdrawal Amount:                 \033[47m   \033[0m";
                        std::cout << "\n\t\t\t\t\t\t\t\t\t\t   ";
                        cin >> amount;

                        success = pm.withdraw(accounts, acc_no, amount);
                        if(success){
                            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[32m                     WITHDRAWAL SUCCESSFUL.                 \033[0m\033[47m   \033[0m" << std::endl;
                            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                            std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m ";
                            pm.save(accounts, filename);std::cout << "\n\t\t\t\t\t\t\t\t\t> ";

                        }else{
                            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                   WITHDRAWAL UNSUCCESSFUL.                 \033[0m\033[47m   \033[0m" << std::endl;
                            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                     INSUFFICIENT FUNDS.                    \033[0m\033[47m   \033[0m" << std::endl;
                            std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                            std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                            std::cout << "\n\t\t\t\t\t\t\t\t\t> ";
                            }
                        break;

                    //DEPOSIT
                    case 3:
                        double deposit_amount;
                        system("cls");
                        pm.transactionDisplay();
                        std::cout << "\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                        > DEPOSIT <                         \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;

                        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                   Input Deposit Amount:                    \033[47m   \033[0m";
                        std::cout << "\n\t\t\t\t\t\t\t\t\t\t   ";
                        std::cin >> deposit_amount;
                        pm.deposit(accounts, acc_no, deposit_amount);

                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[32m                      DEPOSIT SUCCESSFUL.                   \033[0m\033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        pm.save(accounts, filename); std::cout << "\n\t\t\t\t\t\t\t\t\t> ";
                        break;

                    //TRANSFER FUND
                    case 4:
                        int receiver;
                        double transfer_amount;
                        system("cls");
                        pm.transactionDisplay();
                        std::cout << "\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                    > TRANSFER FUND <                       \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;

                        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m              Input Receiver Account Number:                \033[47m   \033[0m";
                        std::cout << "\n\t\t\t\t\t\t\t\t\t\t   ";
                        std::cin >> receiver;

                        std::cout << "\n\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m \n";
                        std::cout << "\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                  Input Transfer Amount:                    \033[47m   \033[0m";
                        std::cout << "\n\t\t\t\t\t\t\t\t\t\t   ";
                        std::cin >> transfer_amount;

                        pm.transferFunds(accounts, acc_no, receiver, transfer_amount);
                        pm.save(accounts, filename);std::cout << "\n\n\t\t\t\t\t\t\t\t\t>   ";
                        break;

                    //NEW PIN CODE
                    case 5:
                        int newPin_code;
                        system("cls");
                        pm.transactionDisplay();
                        std::cout << "\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                   > CHANGE PIN CODE <                      \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;

                        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                    Input New PIN Code:                     \033[47m   \033[0m";
                        std::cout << "\n\t\t\t\t\t\t\t\t\t\t   ";
                        cin >> newPin_code;

                        pm.changePin_code(accounts, acc_no, newPin_code);
                        pm.save(accounts, filename);std::cout << "\n\n\t\t\t\t\t\t\t\t\t>   ";
                        break;

                    //VIEW ACCOUNT INFORMATION
                    case 6:
                        system("cls");
                        pm.transactionDisplay();
                        std::cout << "\n\n\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                 > ACCOUNT INFORMATION <                    \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                        pm.displayAccount_info(accounts, acc_no);
                        std::cout << "\n\n\t\t\t\t\t\t\t\t\t>   ";
                        system("pause");
                        break;

                    //GO BACK TO MAIN MENU
                    case 7:
                        break;

                    default:
                        std::cout << "\n\t\t\t\t\t\t\t\t\t  \033[47m                               \033[0m \n";
                        std::cout << "\t\t\t\t\t\t\t\t\t  \033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t\t\t\t  \033[47m    \033[0m\033[31m     Invalid Choice.   \033[0m\033[47m    \033[0m"<< std::endl;
                        std::cout << "\t\t\t\t\t\t\t\t\t  \033[47m    \033[0m\033[31m    Please try again.  \033[0m\033[47m    \033[0m"<< std::endl;
                        std::cout << "\t\t\t\t\t\t\t\t\t  \033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
                        std::cout << "\t\t\t\t\t\t\t\t\t  \033[47m                               \033[0m" << std::endl;
                        std::cout << "\n\t\t\t\t\t\t\t\t\t   > ";
                        system("pause");
                    }
                        if (t_menu == 7) {
                        break; // Break from the t_menu loop to go back to the main menu
                    }
                    }




                } else {

                    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m                        LOG-IN FAILED.                      \033[0m\033[47m   \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m\033[31m               INVALID ACCOUNT NUMBER / PIN CODE            \033[0m\033[47m   \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m   \033[0m                                                            \033[47m   \033[0m" << std::endl;
                    std::cout << "\t\t\t\t\t\t     \033[47m                                                                  \033[0m " << std::endl;
                    std::cout << "\n\t\t\t\t\t\t\t\t\t> ";
                    system("pause");
                }
                break;

            case 3:
                system("cls");
                pm.exitDisplay();
                return 0;
                break;

            default:
                std::cout << "\n\t\t\t\t\t\t\t\t\t\033[47m                               \033[0m \n";
                std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m\033[31m     Invalid Choice.   \033[0m\033[47m    \033[0m"<< std::endl;
                std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m\033[31m    Please try again.  \033[0m\033[47m    \033[0m"<< std::endl;
                std::cout << "\t\t\t\t\t\t\t\t\t\033[47m    \033[0m                       \033[47m    \033[0m" << std::endl;
                std::cout << "\t\t\t\t\t\t\t\t\t\033[47m                               \033[0m" << std::endl;
                std::cout << "\n\t\t\t\t\t\t\t\t\t   > ";
                system("pause");
        }
    }
    return 0;
}
