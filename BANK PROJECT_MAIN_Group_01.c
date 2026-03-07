#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

//Function Prototypes//
void payment_bills(char select);
void display_history();
void record_payment(long int id, const char *bill, double amount, const char *card);
void acc_status();
void prompt();
void settings();
void print_header(const char *title);
void transaction();
void debit_to_credit();

//dps
void dps_menu();
void dps_set_years();
void dps_monthly_installment();
void dps_calculator();
void dps_maturity();
void dps_status();
void dps_interest_rate_check();
void dps_calculate_internals();
//dps

//fdr
void fdr_menu();
void fdr_deposit_amount();
void fdr_time_period();
void fdr_interest();
void fdr_maturity();
void fdr_status();
//fdr

//loan
void loan_menu();
void loan_apply();
void loan_repay();
void loan_status_module();
//loan

//mobile banking
void mobile_banking_menu();
void cash_in();
void cash_out();
void send_money();
//mobile banking
//Function Prototype//

//Global Variables//
double credited_amount = 0;
double credit_balance = 50000;
double debited_amount = 0;

int n = 0, current_user = 0;
int transaction_count = 0;
double dps_interest_rate = 6.5;
double fdr_interest_rate = 10.5;
double loan_interest_rate = 12.0;

struct bank {
    char password[20];
    long int id, card_num;
    int exp1, exp2, cvc;
    char name[40];
    double balance;
    double credit_balance;
    double mobile_balance; // Added for Mobile Banking

    //optional info//
    long int number;
    char e_mail[40];
    char address[50];
    //optional info//

    //dps
    int is_dps_active;
    double dps_monthly_amount;
    int dps_years;
    double dps_total_deposit;
    double dps_maturity_amount;
    //dps

    //fdr
    int is_fdr_active;
    double fdr_amount;
    int fdr_years;
    double fdr_maturity_amount;
    //fdr

    //loan
    int is_loan_active;
    double loan_principal;
    double loan_due_amount;
    //loan

} storage[100];

struct transaction_record {
    long int user_id;
    char bill_type[20];
    double amount;
    char card_type[10];
} history[100];
//Global Variables//

void print_header(const char *title)
{
    system("cls");
    printf("\n\t============================================\n");
    printf("\t           %s\n", title);
    printf("\t============================================\n\n");
}

//Mohi Protim Roy//
void bank_register() {
    print_header("ACCOUNT REGISTRATION");
    printf("\tEnter Name: ");
    scanf(" %39[^\n]", storage[n].name);
    prompt();
    printf("\tSet Password: ");
    scanf("%s", storage[n].password);

    storage[n].balance = 0.0;
    storage[n].credit_balance = 50000.0;
    storage[n].mobile_balance = 0.0;
    storage[n].id = 1000 + n;

    storage[n].is_dps_active = 0;
    storage[n].is_fdr_active = 0;
    storage[n].is_loan_active = 0;

    storage[n].dps_monthly_amount = 0;
    storage[n].fdr_amount = 0;
    storage[n].loan_principal = 0;
    storage[n].loan_due_amount = 0;

    printf("\n\tRegistration successful! \n\tID: %ld\n", storage[n].id);

    current_user = n;
    n++;
}

int password_checker()
{
    char temp_pass[20];
    int x;

    for (int count = 3; count > 0; count--)
    {
        printf("\n\tEnter your password: ");
        scanf("%s", temp_pass);

        x = strcmp(temp_pass, storage[current_user].password);

        if (x == 0)
        {
            return 1;
        }
        else
        {
            printf("\t[!] Wrong Password. Remaining Attempts: %d\n", count - 1);
        }
    }
    printf("\n\t[X] Your account is terminated.\n\n");
    return 0;
}

void prompt()
{
    printf("\tEnter Card Number: ");
    scanf("%ld", &storage[n].card_num);
    getchar();

    printf("\tExpiry Date (MM/YY): ");
    scanf("%d/%d", &storage[n].exp1, &storage[n].exp2);
    getchar();

    printf("\tEnter CVC: ");
    scanf("%d", &storage[n].cvc);
    getchar();
}
//Mohi Protim Roy//

//Mohi Protim Roy//
void bill_payment()
{
    char select;
    while(1)
    {
        print_header("BILL PAYMENT");
        printf("\t[1] Electricity Bill\n");
        printf("\t[2] Gas Bill\n");
        printf("\t[3] Water Bill\n");
        printf("\t[4] Internet Bill\n");
        printf("\t[5] Check Payment History\n");
        printf("\t[6] Return to Main Menu\n");
        printf("\n\tSelect Option: ");

        select = getch();

        if (select == '6')
            return;
        else
            payment_bills(select);
    }
}
//Mohi Protim Roy//

//Mohi Protim Roy//
int main()
{
    start:

    system("cls");
    printf("\n\n\n");
    printf("\t********************************************\n");
    printf("\t\n");
    printf("\t\t  WELCOME TO AMADER BANK            \n");
    printf("\t\n");
    printf("\t********************************************\n");
    printf("\n\t\tPress any key to start...");
    getch();

    bank_register();

    char select;

    do
    {
        print_header("MAIN DASHBOARD");

        printf("\t[?] Select Profile\n");
        printf("\t[0] New Account\n");
        printf("\t[1] DPS\n");
        printf("\t[2] FDR\n");
        printf("\t[3] Transaction\n");
        printf("\t[4] Fund Transfer\n");
        printf("\t[5] Loan\n");
        printf("\t[6] Bill Payment\n");
        printf("\t[7] Settings\n");
        printf("\t[8] Current Account Status\n");
        printf("\t[9] Mobile Banking\n");
        printf("\t[X] Exit\n");

        printf("\n\tSelect Option: ");

        select = getch();

        switch (select)
        {
            case '?':
                {
                long int temp_id;
                int temp_index;

                printf("\tWhich profile do you want to access?\n");
                printf("\tID: ");
                scanf("%ld", &temp_id);

                for(int i=0; 100>i; i++)
                {
                    if(temp_id==storage[i].id)
                       {
                        temp_index=i;
                        break;
                       }
                }
                int previous_index = current_user;


                    if((temp_id==storage[temp_index].id))
                    {
                        current_user = temp_index;
                        if(password_checker())
                            {
                                current_user = temp_index;
                                printf("\tWelcome, %s", storage[temp_index].name);
                            }

                        else
                            current_user = previous_index;
                    }
                    else
                    {
                        printf("\tProfile does not exist.");
                        getch();
                    }

                break;
                }

            case '0':
                printf("\tOpen New Account");
                goto start;

            case '1':
                dps_menu();
                break;

            case '2':
                fdr_menu();
                break;

            case '3':
                print_header("TRANSACTION");
                transaction();
                getch();
                break;

            case '4':
                print_header("Debit to Credit Transfer");
                debit_to_credit();
                getch();
                break;

            case '5':
                loan_menu();
                break;

            case '6':
                bill_payment();
                break;

            case '7':
                settings();
                break;

            case '8':
                acc_status();
                break;

            case '9':
                mobile_banking_menu();
                break;

            case 'x':
                system("cls");
                printf("\n\n\n\n\tThank you for banking with us.\n\n\n");
                return 0;
        }
    } while (select != 'x');

    return 0;
}
//Mohi Protim Roy//

//Mohi Protim Roy//
void payment_bills(char select)
{
    int id;
    float amount;
    char card;
    char billName[20];

    if(select == '1')
        strcpy(billName, "Electric Bill");
    else if(select == '2')
        strcpy(billName, "Gas Bill");
    else if(select == '3')
        strcpy(billName, "Water Bill");
    else if(select == '4')
        strcpy(billName, "Internet Bill");
    else if(select == '5')
    {
        display_history();
        printf("\n\tPress any key to return...");
        getch();
        return;
    }
    else
        return;

    print_header(billName);

    printf("\tCustomer ID: ");
    scanf("%d", &id);
    printf("\tEnter Amount: ");
    scanf("%f", &amount);
    getchar();

    printf("\n\tUser: %s\n", storage[current_user].name);
    printf("\t----------------------------\n");
    printf("\t[1] Credit Card\n");
    printf("\t[2] Debit Card\n");
    printf("\n\tSelect Card: ");
    scanf("%c", &card);

    if (password_checker())
    {
        if (card == '2')
        {
            storage[current_user].balance = storage[current_user].balance - amount;
            record_payment(storage[current_user].id, billName, amount, "Debit");
            printf("\n\t>> Payment Successful via Debit!\n");
        }

        else if (card == '1')
        {
            credit_balance = credit_balance - amount;
            record_payment(storage[current_user].id, billName, amount, "Credit");
            printf("\n\t>> Payment Successful via Credit!\n");
        }
        printf("\tPress any key...");
        getch();
    }
}
//Mohi Protim Roy//

//Mohi Protim Roy//
void display_history()
{
    int found_transactions = 0;

    print_header("PAYMENT HISTORY");
    printf("\tUser ID: %ld\n\n", storage[current_user].id);

    printf("\t /----------------------------------------------\\");
    printf("\n\t| %-20s | %-10s | %-10s |\n", "Bill Type", "Amount", "Card");
    printf("\t|----------------------|------------|------------|\n");

    for (int i = 0; i < transaction_count; i++)
    {
        if (history[i].user_id == storage[current_user].id)
        {
            printf("\t| %-20s | %-10.2f | %-10s |\n", history[i].bill_type, history[i].amount, history[i].card_type);
            found_transactions++;
        }
    }

    printf("\t \\----------------------------------------------/");
    printf("\n");

    if (found_transactions == 0)
    {
        printf("\n\tNo transactions recorded for this user.\n");
    }
}
//Mohi Protim Roy//

//Mohi Protim Roy//
void record_payment(long int id, const char *bill, double amount, const char *card)
{
    if (transaction_count < 100)
    {
        history[transaction_count].user_id = id;
        history[transaction_count].amount = amount;
        strcpy(history[transaction_count].bill_type, bill);
        strcpy(history[transaction_count].card_type, card);
        transaction_count++;
    }
}
//Mohi Protim Roy//

//Mohi Protim Roy//
void acc_status()
{
    print_header("ACCOUNT STATUS");
    printf("\t[1] Balance Check\n");
    printf("\t[2] Check Loan Remain\n");
    printf("\t[3] Account Holder Information\n");
    printf("\t[4] Account Type & Limit\n");
    printf("\n\tSelect Option: ");

    char x = getch();

    switch (x)
    {
        case '1':
            print_header("CURRENT BALANCE");
            printf("\tDebit Card Balance : %.2f\n", storage[current_user].balance);
            printf("\tMobile Wallet Bal  : %.2f\n", storage[current_user].mobile_balance);
            printf("\tCredit Card Balance: %.2f\n", credit_balance);
            break;

        case '2':
            print_header("LOAN STATUS");
            if(storage[current_user].is_loan_active) {
                printf("\tActive Loan Amount: %.2f\n", storage[current_user].loan_principal);
                printf("\tTotal Due Amount  : %.2f\n", storage[current_user].loan_due_amount);
            } else {
                printf("\tNo active loans.\n");
            }
            break;

        case '3':
            print_header("ACCOUNT INFO");
            printf("\tName               : %s\n", storage[current_user].name);
            printf("\tUser ID            : %ld\n", storage[current_user].id);
            printf("\t--------------------------------------------\n");
            printf("\tCard Num           : %ld\n", storage[current_user].card_num);
            printf("\tExpiry             : %02d/%02d\n", storage[current_user].exp1, storage[current_user].exp2);
            printf("\tDebit Card Balance : %.2f\n", storage[current_user].balance);
            printf("\tMobile Wallet Bal  : %.2f\n", storage[current_user].mobile_balance);
            break;

        case '4':
            print_header("TYPE & LIMIT");
            printf("\tType: Savings\n\tLimit: 500,000\n");
            break;
    }
    printf("\n\tPress any key to return...");
    getch();
}
//Mohi Protim Roy//

//Mohi Protim Roy//
void settings()
{
    char temp_password[20];
    char confirm_pass[20];
    int otp;

    print_header("SETTINGS");
    printf("\t[1] Change Password\n");
    printf("\t[2] Change Number\n");
    printf("\t[3] Change E-mail\n");
    printf("\t[4] Update Address\n");
    printf("\t[5] Deactivate\n");
    printf("\n\tSelect Option: ");

    char select = getch();

    switch(select){

    case '1':
        print_header("CHANGE PASSWORD");

        label_1:
        printf("\tCurrent Password: ");
        scanf("%s", temp_password);
        getchar();

        if (strcmp(temp_password, storage[current_user].password) == 0)
        {
            label_2:
            printf("\n\tNew Password: ");
            scanf("%s", temp_password);
            printf("\tConfirm Password: ");
            scanf("%s", confirm_pass);

            if (strcmp(temp_password, confirm_pass) == 0)
            {
                printf("\n\t[OTP] Sent to your email.\n");
                printf("\tEnter OTP: ");
                scanf("%d", &otp);
                strcpy(storage[current_user].password, temp_password);
                printf("\n\t>> Password updated successfully!\n");
            }
            else {
                printf("\n\t[!] Passwords do not match. Try again.\n");
                goto label_2;
            }
        }
        else
        {
            printf("\n\t[!] Incorrect Password.\n");
            printf("\tForgot Password? (Y/N): ");
            char option = getchar();
            getchar();

            if (option == 'Y' || option == 'y')
            {
                printf("\n\tNew Password: ");
                scanf("%s", temp_password);
                printf("\tConfirm: ");
                scanf("%s", confirm_pass);

                if (strcmp(temp_password, confirm_pass) == 0)
                {
                    printf("\tEnter OTP: ");
                    scanf("%d", &otp);
                    getchar();
                    strcpy(storage[current_user].password, temp_password);
                    printf("\n\t>> Password Reset Successfully<<\n");
                }
            }
            else if (option == 'N' || option == 'n') {
                goto label_1;
            }
        }
        break;

    case '2':
        printf("\n\tEnter Number: ");
        scanf("%ld", &storage[current_user].number);
        getchar();
        printf("\n\tYour number is +880%ld", storage[current_user].number);
        break;

    case '3':
        printf("\n\tEnter e-mail: ");
        scanf(" %39[^\n]", storage[current_user].e_mail);
        getchar();
        printf("\n\tYour e-mail is %s", storage[current_user].e_mail);
        break;

    case '4':
        printf("\n\tEnter Address: ");
        scanf(" %49[^\n]", storage[current_user].address);
        getchar();
        printf("\n\tYour address is %s", storage[current_user].address);
        break;

    case '5':
        printf("\n\tEnter password to deactivate.");
        if(password_checker())
            printf("\n\n\tDear Customer, your account has been deactivated.");
        getch();
        break;

    default:
        printf("\n\tInvalid Input!");
    }

    printf("\n\n\tPress any key to continue.");
    getch();
}
//Mohi Protim Roy//

void transaction()
{
    int choice;
    float amount;

    print_header("\n\tTRANSACTION MENU\n");
    printf("\t[1] Cash Deposit\n");
    printf("\t[2] Cash Withdraw\n");
    printf("\t[3] Fund Transfer\n");
    printf("\n\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {

        case 1: printf("\tEnter deposit amount: ");
                scanf("%f", &amount);

                if (amount <= 0)
                {
                    printf("\tInvalid amount!\n");
                }
                else if(((storage[current_user].balance>=amount) || (storage[current_user].balance<=amount)) && (password_checker()))
                {

                    storage[current_user].balance = storage[current_user].balance + amount;
                    printf("\tDeposit successful!\n");
                    printf("\tCurrent Balance: %.2f\n", storage[current_user].balance);
                }
                break;


        case 2: printf("\tEnter withdraw amount: ");
                scanf("%f", &amount);

                if (amount <= 0)
                {
                    printf("\tInvalid amount!\n");
                }
                else if (amount > storage[current_user].balance)
                {
                    printf("\tInsufficient balance!\n");
                }
                else if((storage[current_user].balance>=amount) && (password_checker()))
                {
                    storage[current_user].balance = storage[current_user].balance - amount;
                    printf("\tWithdrawal successful!\n");
                    printf("\tCurrent Balance: %.2f\n", storage[current_user].balance);
                }
                break;


        case 3:
            {
                long long receiver_acc;

                printf("\tEnter receiver account number: ");
                scanf("%lld", &receiver_acc);
                printf("\tEnter transfer amount: ");
                scanf("%f", &amount);

                if (amount <= 0)
                {
                    printf("\tInvalid amount!\n");
                }
                else if (amount > storage[current_user].balance)
                {
                    printf("\tInsufficient balance!\n");
                }
                else if((storage[current_user].balance>=amount) && (password_checker()))
                {
                    storage[current_user].balance = storage[current_user].balance - amount;

                    printf("\n\tFund Transfer Successful!\n");
                    printf("\tTransferred %.2f to Account No: %lld\n", amount, receiver_acc);
                    printf("\tCurrent Balance: %.2f\n", storage[current_user].balance);
                }
                break;

           }

        default: printf("\tInvalid choice!\n");

    }
}

void debit_to_credit()
{
    double amount;
    long long credit_acc_no;

    printf("\tYour (Debit) Balance : %.2lf\n", storage[current_user].balance);
    printf("\tEnter credit account number: ");
    scanf("%lld", &credit_acc_no);
    printf("\tEnter transfer amount: ");
    scanf("%lf", &amount);

    if (amount <= 0)
    {
        printf("\t>>Invalid amount!\n");
    }
    else if (amount > storage[current_user].balance)
    {
        printf("\t>>Insufficient balance!\n");
    }
    else
    {
        storage[current_user].balance = storage[current_user].balance - amount;

        printf("\n\tDebit to Credit Successful!\n");
        printf("\tTransferred %.2lf to Account No: %lld\n", amount, credit_acc_no);
        printf("\tYour New Balance: %.2lf\n", storage[current_user].balance);
    }
}

void dps_calculate_internals() {
    if (storage[current_user].dps_years > 0 && storage[current_user].dps_monthly_amount > 0) {
        int total_months = storage[current_user].dps_years * 12;
        storage[current_user].dps_total_deposit = storage[current_user].dps_monthly_amount * total_months;
        double interest = (storage[current_user].dps_total_deposit * dps_interest_rate) / 100;
        storage[current_user].dps_maturity_amount = storage[current_user].dps_total_deposit + interest;
    }
}

void dps_menu()
{
    int choice;
    do
    {
        print_header("DPS MENU");
        printf("\t1. Set DPS Years\n");
        printf("\t2. Set Monthly Installment\n");
        printf("\t3. Check Maturity Details\n");
        printf("\t4. DPS Status\n");
        printf("\t5. Exit DPS\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: dps_set_years(); break;
            case 2: dps_monthly_installment(); break;
            case 3: dps_maturity(); break;
            case 4: dps_status(); break;
            case 5: printf("\tExiting DPS Module...\n"); break;
            default: printf("\n\tInvalid Choice!\n");
        }
        if(choice != 5) getch();

    } while (choice != 5);
}

void dps_set_years()
{
    printf("\tEnter DPS duration in years: ");
    scanf("%d", &storage[current_user].dps_years);

    if (storage[current_user].dps_years <= 0)
    {
        printf("\tInvalid years!\n");
        storage[current_user].dps_years = 0;
    }
    else
    {
        printf("\tDPS duration set to %d years\n", storage[current_user].dps_years);
        if(storage[current_user].dps_monthly_amount > 0) storage[current_user].is_dps_active = 1;
        dps_calculate_internals();
    }
}

void dps_monthly_installment()
{
    printf("\tEnter monthly installment amount: ");
    scanf("%lf", &storage[current_user].dps_monthly_amount);

    if (storage[current_user].dps_monthly_amount <= 0)
    {
        printf("\tInvalid amount!\n");
        storage[current_user].dps_monthly_amount = 0;
    }
    else
    {
        printf("\tMonthly installment set to %.2lf\n", storage[current_user].dps_monthly_amount);
        if(storage[current_user].dps_years > 0) storage[current_user].is_dps_active = 1;
        dps_calculate_internals();
    }
}

void dps_calculator() { }

void dps_maturity()
{
    if (storage[current_user].is_dps_active == 0)
    {
        printf("\tPlease set both Years and Installment amount first!\n");
        return;
    }
    dps_calculate_internals();
    printf("\tTotal DPS Deposit: %.2lf\n", storage[current_user].dps_total_deposit);
    printf("\tDPS Maturity Amount: %.2lf\n", storage[current_user].dps_maturity_amount);
}

void dps_status()
{
    if (storage[current_user].is_dps_active == 1)
    {
        dps_calculate_internals();
        print_header("DPS STATUS");
        printf("\tYears: %d\n", storage[current_user].dps_years);
        printf("\tMonthly Amount: %.2lf\n", storage[current_user].dps_monthly_amount);
        printf("\tTotal Deposit: %.2lf\n", storage[current_user].dps_total_deposit);
        printf("\tInterest Rate: %.2lf %%\n", dps_interest_rate);
        printf("\tMaturity Amount: %.2lf\n", storage[current_user].dps_maturity_amount);
        printf("\tStatus: ACTIVE\n");
    }
    else
    {
        printf("\tNo DPS Account Found!\n");
    }
}

void dps_interest_rate_check()
{
    printf("\n\tDPS Fixed Interest Rate: %.2lf %%\n", dps_interest_rate);
}

void fdr_menu()
{
    int choice;
    do
    {
        print_header("FDR MENU");
        printf("\t1. Create New FDR (Deposit)\n");
        printf("\t2. Check Maturity Details\n");
        printf("\t3. FDR Status\n");
        printf("\t4. Exit FDR\n");

        printf("\tEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: fdr_deposit_amount(); break;
            case 2: fdr_maturity(); break;
            case 3: fdr_status(); break;
            case 4: printf("\tExiting FDR Menu...\n"); break;
            default: printf("\tInvalid Entry!\n");
        }
        if(choice != 4) getch();

    } while (choice != 4);
}

void fdr_deposit_amount()
{
    if(storage[current_user].is_fdr_active == 1) {
        printf("\n\t[!] You already have an active FDR.\n");
        return;
    }

    double temp_amount;
    int temp_years;

    printf("\n\tEnter FDR Deposit Amount: ");
    scanf("%lf", &temp_amount);

    if (temp_amount > storage[current_user].balance) {
        printf("\n\t[!] Insufficient Balance in Main Account!");
        return;
    }
    if (temp_amount <= 0) {
        printf("\tInvalid amount!\n");
        return;
    }

    printf("\tEnter Duration (Years): ");
    scanf("%d", &temp_years);

    if(temp_years <= 0) {
        printf("\tInvalid duration!\n");
        return;
    }

    if(password_checker()) {
        storage[current_user].balance -= temp_amount;
        storage[current_user].fdr_amount = temp_amount;
        storage[current_user].fdr_years = temp_years;
        storage[current_user].is_fdr_active = 1;

        double interest = (storage[current_user].fdr_amount * fdr_interest_rate * storage[current_user].fdr_years) / 100;
        storage[current_user].fdr_maturity_amount = storage[current_user].fdr_amount + interest;

        printf("\n\t>> FDR Created Successfully!\n");
    }
}

void fdr_time_period() { }

void fdr_interest()
{
    printf("\n\tFixed Interest Rate: %.2lf %%\n", fdr_interest_rate);
}

void fdr_maturity()
{
    if (storage[current_user].is_fdr_active == 0) {
        printf("\n\tPlease create an FDR account first!\n");
    }
    else {
        printf("\n\tFDR Maturity Amount: %.2lf\n", storage[current_user].fdr_maturity_amount);
    }
}

void fdr_status()
{
    print_header("FDR STATUS");
    if (storage[current_user].is_fdr_active == 1)
    {
        printf("\tFDR Status: Active\n");
        printf("\tDeposit Amount: %.2lf\n", storage[current_user].fdr_amount);
        printf("\tYears: %d\n", storage[current_user].fdr_years);
        printf("\tInterest Rate: %.2lf %%\n", fdr_interest_rate);
        printf("\tMaturity Amount: %.2lf\n", storage[current_user].fdr_maturity_amount);
    }
    else
    {
        printf("\tNo FDR Account Created\n");
    }
}

void loan_menu()
{
    int choice;
    do
    {
        print_header("LOAN SECTION");
        printf("\t[1] Apply for Loan\n");
        printf("\t[2] Repay Loan\n");
        printf("\t[3] Check Loan Status\n");
        printf("\t[4] Return to Main Menu\n");
        printf("\n\tSelect Option: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: loan_apply(); break;
            case 2: loan_repay(); break;
            case 3: loan_status_module(); break;
            case 4: return;
            default: printf("\tInvalid Option!\n");
        }
        if(choice != 4) getch();
    } while(choice != 4);
}

void loan_apply()
{
    if(storage[current_user].is_loan_active)
    {
        printf("\n\t[!] You already have an active loan. Please repay it first.\n");
        return;
    }

    double request_amount;
    double max_limit = 50000.0;

    printf("\n\tMaximum Loan Limit: %.2f\n", max_limit);
    printf("\tEnter Loan Amount: ");
    scanf("%lf", &request_amount);

    if(request_amount <= 0 || request_amount > max_limit)
    {
        printf("\t[!] Invalid amount or exceeds limit.\n");
        return;
    }

    printf("\n\tLoan Interest Rate: %.2f %%\n", loan_interest_rate);
    double interest = (request_amount * loan_interest_rate) / 100;
    double total_repay = request_amount + interest;

    printf("\tTotal Payable Amount: %.2f\n", total_repay);
    printf("\n\tConfirm Loan? (Press 'Y' for Yes): ");
    char confirm = getch();

    if(confirm == 'y' || confirm == 'Y')
    {
        if(password_checker())
        {
            storage[current_user].is_loan_active = 1;
            storage[current_user].loan_principal = request_amount;
            storage[current_user].loan_due_amount = total_repay;
            storage[current_user].balance += request_amount;
            printf("\n\t>> Loan Approved! Amount credited to balance.\n");
        }
    }
    else
    {
        printf("\n\t>> Loan Cancelled.\n");
    }
}

void loan_repay()
{
    if(!storage[current_user].is_loan_active)
    {
        printf("\n\t[!] No active loan to repay.\n");
        return;
    }

    double repay_amount;
    printf("\n\tTotal Due: %.2f\n", storage[current_user].loan_due_amount);
    printf("\tEnter Repayment Amount: ");
    scanf("%lf", &repay_amount);

    if(repay_amount <= 0 || repay_amount > storage[current_user].balance)
    {
        printf("\t[!] Invalid amount or Insufficient balance.\n");
        return;
    }

    if(password_checker())
    {
        storage[current_user].balance -= repay_amount;
        storage[current_user].loan_due_amount -= repay_amount;
        printf("\n\t>> Repayment Successful!\n");

        if(storage[current_user].loan_due_amount <= 0)
        {
            storage[current_user].is_loan_active = 0;
            printf("\t>> Loan fully paid.\n");
        }
    }
}

void loan_status_module()
{
    print_header("LOAN STATUS");
    if(storage[current_user].is_loan_active)
    {
        printf("\tStatus         : ACTIVE\n");
        printf("\tPrincipal      : %.2f\n", storage[current_user].loan_principal);
        printf("\tOutstanding Due: %.2f\n", storage[current_user].loan_due_amount);
    }
    else
    {
        printf("\tNo active loans found.\n");
    }
}

void mobile_banking_menu()
{
    int choice;
    do
    {
        print_header("MOBILE BANKING");
        printf("\tMobile Balance: %.2f\n\n", storage[current_user].mobile_balance);
        printf("\t[1] Cash In (From Main Bank)\n");
        printf("\t[2] Cash Out (To Main Bank)\n");
        printf("\t[3] Send Money (To other Mobile Wallet)\n");
        printf("\t[4] Return to Main Menu\n");
        printf("\n\tSelect Option: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: cash_in(); break;
            case 2: cash_out(); break;
            case 3: send_money(); break;
            case 4: return;
            default: printf("\tInvalid Option!\n");
        }
        if(choice != 4) getch();
    } while(choice != 4);
}

void cash_in()
{
    double amount;
    printf("\n\tEnter amount to Cash In from Bank Account: ");
    scanf("%lf", &amount);

    if(amount > storage[current_user].balance || amount <= 0)
    {
        printf("\t[!] Insufficient bank balance or invalid amount.\n");
        return;
    }

    if(password_checker())
    {
        storage[current_user].balance -= amount;
        storage[current_user].mobile_balance += amount;
        printf("\n\t>> Success! %.2f moved to Mobile Wallet.\n", amount);
    }
}

void cash_out()
{
    double amount;
    printf("\n\tEnter amount to Cash Out to Bank Account: ");
    scanf("%lf", &amount);

    if(amount > storage[current_user].mobile_balance || amount <= 0)
    {
        printf("\t[!] Insufficient mobile balance.\n");
        return;
    }

    if(password_checker())
    {
        storage[current_user].mobile_balance -= amount;
        storage[current_user].balance += amount;
        printf("\n\t>> Success! %.2f moved to Bank Account.\n", amount);
    }
}

void send_money()
{
    char receiver_phone[15];
    double amount;

    printf("\n\tEnter Receiver Phone Number: ");
    scanf("%s", receiver_phone);
    printf("\tEnter Amount: ");
    scanf("%lf", &amount);

    if(amount > storage[current_user].mobile_balance || amount <= 0)
    {
        printf("\t[!] Insufficient mobile balance.\n");
        return;
    }

    if(password_checker())
    {
        storage[current_user].mobile_balance -= amount;
        printf("\n\t>> Success! %.2f sent to %s.\n", amount, receiver_phone);
    }
}
