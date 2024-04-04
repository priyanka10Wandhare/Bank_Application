//*Problem Statement:

//Bank of Success Pvt LTD is in the process of establishing a new bank and requires the development of a banking system module to manage account operations. The initial module will focus on the setup of two types of accounts: Savings and Current. The following requirements outline the necessary functionalities:

//Level 1:
//1. Account Information:
 //  a. Auto-generated Account Number (beginning from 1000)
 //  b. Account Holder's Name
 //  c. PinNumber (for account access security)
 //  d. Balance
 //  e. Privilege Level (PREMIUM, GOLD, SILVER - Enum)
 //  f. Account Status (IsActive)
  // g. Activation Date
   //h. Closure Date
//2. Additional Information for Account Types:
//   i. Savings Account:
 //     - Date of Birth
 //     - Gender
 //     - Phone Number
//   j. Current Account:
  //    - Company Name
    //  - Website
 //     - Registration Number

//Level 2:
//1. Account Operations:
//   a. Opening an Account:
 //     - For Savings:
 //        - Verify age is greater than 18
 //        - Set IsActive status to true
  //    - For Current:
 //        - Ensure Registration Number is not null
  //       - Set IsActive status to true
 //     - Throw exceptions with detailed reasons if opening requirements are not met.
   //b. Closing an Account
  // c. Withdrawal from an Account
  // d. Deposit into an Account

//the  banking system module should facilitate the management of account operations, including opening, closing, withdrawing, and depositing funds, with distinct rules and validations for different account types. It should ensure data integrity, security, and user-friendly error handling to provide a seamless banking experience for customers. * //



#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <exception>
using namespace std;

// Critical focus areas and best practices while coding
// Quality conscious software engineers is what TGL focusses on
// End to end programming is another attribute everyone should carry

// Getting the requirements
// Getting your test cases right
// Unit Testable Code - Every line of your code should be of high quality. Well tested
// Breaking down the code into smaller units of code - This is a practice that has to be initiated from now
// Testing your code becomes very easy - Your quality score will increase when you break into smaller units of code
// SRP - Single Responsibility Principle: One goal, One task, One functionality, One Responsibility
// To test the ONE is easier....To debug the ONE is easier

// Class that represents an account of an account holder in the bank
// Common information across accounts is defined in the class

// Privilege to indicate the type of the customer
enum Privilege
{
    SILVER,
    GOLD,
    PLATINUM
};

class Account
{

    // Properties - Data Members
private:
    long id;
    long accountNumber;
    string name;
    bool isActive;
    int pinNumber;
    double balance;
    // Privilege privilege;
    // Date activatedDate;
    // Date closedDate;

    // Getters and Setters
public:
    long getAccountNumber()
    {
        return accountNumber;
    }

    string getName()
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setAccountNumber(long accountNumber)
    {
        // Write the logic of auto generation of account number
        this->accountNumber = accountNumber;
    }
    bool isActiveStatus()
    {
        return true; // temporary set to true
    }
    int getPinNumber()
    {
        // return pin number
        return 1234;
    }
    int getBalance()
    {
        // return pin number
        return 10000;
    }

    void setBalance(long balance)
    {
        // Write the logic of auto generation of account number
        this->balance = balance;
    }
    // Other getters and setters of all the Properties
};

// Class that represents a type of account which is for individuals of an account holder in the bank
// Specific information for a Savings account holder is defined in the class

class Savings : public Account
{
private:
    // Date dateOfBirth;
    string gender;
    string phoneNumber;
    // Getters and Setters
};
// Class that represents a type of account which is for companies
// Specific information for a Current account holder is defined in the class
class Current : public Account
{
private:
    string registrationNo;
    string companyName;
    string websiteURL;
    // Getters and Setters
};

// Account Controller class is the one which interacts with the user. Is given to collect infomation and
// submit to the manager and other classed to further process the account
// This is a boundary class which user interacts with
// Custom exception for Insufficient Balance in account
class InsufficientBalanceAmountException : public std::exception
{
public:
    InsufficientBalanceAmountException(const char *message) : m_message(message) {}

    const char *what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};
// Custom exception for inactive account
class AccountNotActiveException : public exception
{
public:
    AccountNotActiveException(const char *message) : m_message(message) {}

    const char *what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

// Custom exception for incorrect Pin Number
class IncorrectPinNumberException : public exception
{
public:
    IncorrectPinNumberException(const char *message) : m_message(message) {}

    const char *what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

class TransferLimitExceededException : public exception
{
public:
    TransferLimitExceededException(const char *message) : m_message(message) {}
    const char *what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    string m_message;
};

class AccountManager
{
    // Method to open the account
public:
    bool open()
    {
        return false;
    }
    bool withdraw(Account account, double amountToWithdraw, int pinNumber)
    {
        // Declaration
        bool isWithdrawn = false;
        // check if the account is active
        if (account.isActiveStatus())
        {
            // check for pin Number
            if (account.getPinNumber() == pinNumber)
            {
                // check if there is sufficient balance
                if (account.getBalance() >= amountToWithdraw)
                {
                    // deduce amount from acc
                    account.setBalance(account.getBalance() - amountToWithdraw);
                    isWithdrawn = true;
                }
                else
                {
                    throw InsufficientBalanceAmountException("INSUFFICIENT BALANCE IN ACCOUNT TO WITHDRAW!");
                }
            }
            else
            {
                throw IncorrectPinNumberException("PIN NUMBER IS INCORRECT, PLEASE TRY AGAIN !");
            }
        }
        else
        {
            throw AccountNotActiveException("Account is inactive!!");
        }
        return isWithdrawn;
    }

    // Method to transfer from one account to another

    // From Account, To Account, amountToTransfer, pinNumber

    // In a day you can transfer only 1 Lac - Thats your max limit

    bool transfer(Account sender, Account receiver, double amountToTransfer, int pinNumber)
    {
        // Declaration
        bool isTransferred = false;

        // 1. Is from account active
        // 2. Is to account active
        if (sender.isActiveStatus() && receiver.isActiveStatus())
        {
            // 3. Check if pin number is valid
            if (sender.getPinNumber() == pinNumber)
            {
                // 4. Check if sufficient funds are available in from account
                if (sender.getBalance() >= amountToTransfer)
                {
                    // 5. Check if the transfer limit is exceeded
                    TransferLog transferLog;
                    double totalTransfer = transferLog.getTransferAmountFromLog(sender.getAccountNumber());
                    if ((totalTransfer + amountToTransfer) < transferLimit)
                    {
                        // 6. Deduct amount from sender
                        sender.setBalance(sender.getBalance() - amountToTransfer);
                        // 7. Add amount to receiver
                        receiver.setBalance(receiver.getBalance() + amountToTransfer);

                        // 8. Add into Log the transfer made
                        transferLog.addToLog(sender.getAccountNumber(), amountToTransfer);

                        // 9. Update the status of transfer
                        isTransferred = true;
                    }
                    else
                    {
                        throw TransferLimitExceededException("TRANSFER LIMIT EXCEEDED!");
                    }
                }
                else
                {
                    throw InsufficientBalanceAmountException("INSUFFICIENT BALANCE IN ACCOUNT TO WITHDRAW!");
                }
            }
            else
            {
                throw IncorrectPinNumberException("PIN NUMBER IS INCORRECT, PLEASE TRY AGAIN !");
            }
        }
        else
        {
            if (!sender.isActiveStatus())
            {
                // Throw error that sender's acc is inactive
                throw AccountNotActiveException("ACCOUNT IS INACTIVE !");
            }
            else
            {
                // Throw error that receiver's acc is inactive
                throw AccountNotActiveException("ACCOUNT IS INACTIVE !");
            }
        }

        // 10. Return the status

        return isTransferred;
    }

    // Instance of TransferLog

    class TransferLog
    {

        // Here i will have a property to store the transfers done for an account

        // Collection - Map - Key Value (Account, Amount)

        // Method to Log the transfer
    private:
        unordered_map<long, double> transferLogMap;

    public:
        void addToLog(long accountNumber, double transferAmount)
        {
            auto it = transferLogMap.find(accountNumber);
            if (it != transferLogMap.end())
            {
                transferLogMap[accountNumber] += transferAmount;
            }
            else
            {
                transferLogMap[accountNumber] = transferAmount;
            }
        }

        // Method to get the transfers done

        double getTransferAmountFromLog(long accountNumber) const
        {
            auto it = transferLogMap.find(accountNumber);
            if (it != transferLogMap.end())
            {
                // Account found in transfer log, return the transfer amount
                return it->second;
            }
            else
            {
                // Account not found in transfer log, return 0
                return 0.0;
            }
            // Pass the account and get to know how much transfer is done already
        }
    };

private:
    const double transferLimit = 100000.0; // transfer limit
    TransferLog transferLog;
};

class AccountController
{

    // AccountController HAS-A AccountManager. Has-A Relationship
    // Scope of this object is class level
    AccountManager manager;

    // Method to open the account
    // SRP - Call - Delegate to other methods and get the job done
public:
    void open()
    {
        // Construction of a solution...
        // 1. Check the type of account user wants to created
        string accountType = acceptUserChoice();
        // This is to get the object filled based on the type of account needed
        Account account = getAccountInformation(accountType);
        // Submit the form once filled to manager
        bool status = manager.open();

        // 5. Display message to the user
        displayAccountStatus(status);
    }

    // Method to get account oject filled with user information based on the type needed
protected:
    Account getAccountInformation(string accountType)
    {
        Account account;
        // Create the object based on the type of account to be created
        account = createAccount(accountType);
        // Get Common Account information
        getCommonAccountInformation(account);
        // Get specific information related to savings or current
        getAccountTypeInformation(account);
        return account;
    }

    // Method to accept the user choice to open the type of account needed
protected:
    string acceptUserChoice()
    {
        cout << "Select the account type you want to open: " << endl;
        cout << "1. SAVINGS, 2. CURRENT " << endl;
        string accountType;
        cin >> accountType;
        return accountType;
    }
    // Method to accept the user choice to open the type of account needed
protected:
    void displayAccountStatus(bool status)
    {
        if (status)
        {
            cout << "Congratulations. Your account is opened successfully" << endl;
        }
        else
        {
            cout << "Sorry. Try again next time" << endl;
        }
    }

protected:
    Account createAccount(string accountType)
    {
        Account account;
        if (accountType == "SAVINGS")
        {
            // Parent class reference - Child Class Object: This is acceptable
            // However child class reference and parent object is not acceptable (Savings s = new Account())
        }
        else if (accountType == "CURRENT")
        {
            // current account
        }
        // Return the object created as an account parent reference
        return account;
    }
    // Method to get common account information frmo the user
protected:
    Account getCommonAccountInformation(Account account)
    {
        // Get Common Account information
        cout << "Enter Name: " << endl;
        string name;
        cin >> name; // Typcially you would accept the information from the user

        cout << "Enter Balance: " << endl;
        double balance;
        cin >> balance; // Typcially you would accept the information from the user

        cout << "Enter Privilege Type: " << endl;
        string privilege = "SILVER"; // Typcially you would accept the information from the user

        cout << "Enter Pin Number: " << endl;
        int pinNumber;
        cin >> pinNumber; // Typcially you would accept the information from the user
        // Store common account information in the object
        // Return the account object with data
        account.setName(name);
        account.setAccountNumber(12345);
        return account;
    }
    // Method to get common account information frmo the user
protected:
    void getAccountTypeInformation(Account account)
    {
        // Based on the type of account - Ask the user to give information

        // Store common account information in the object
    }
    // Method to close the account
public:
    void close()
    {

        // Creating the instance of manager. A new instance is created

        // In this case - AccountController USES AccountManager

        // AccountManager manager = new AccountManager();

        // manager.close();
        // manager.close();
    }

    void withdraw()
    {

        cout << "Enter Account Number: ";
        long accountNumber;
        cin >> accountNumber;
        // Create the account object for the given account number
        Account *account = new Savings();
        cout << "\nEnter amount to Withdraw: ";
        int amount;
        cin >> amount;
        cout << "\nEnter Pin Number: ";
        int pinNum;
        cin >> pinNum;
        bool isWithdrawn = manager.withdraw(*account, amount, pinNum);
        if (isWithdrawn)
        {
            cout << "Amount has been withdrawn successfully!";
        }
        else
        {
            cout << "Error! Please try again!";
        }
    }

    void transfer()
    {
        cout << "Enter Your Account Number: ";
        long senderAccountNumber;
        cin >> senderAccountNumber;
        // Create the account object for the given senders account number
        Account *sender = new Savings();

        cout << "Enter Receiver\'s Account Number: ";
        long receiverAccountNumber;
        cin >> receiverAccountNumber;
        // Create the account object for the given receiver's account number
        Account *receiver = new Savings();

        cout << "\nEnter amount to Transfer: ";
        int amount;
        cin >> amount;

        cout << "\nEnter PIN Number: ";
        int pinNum;
        cin >> pinNum;

        bool isTransfered = manager.transfer(*sender, *receiver, amount, pinNum);
        if (isTransfered)
        {
            cout << "\nAmount has been transfered successfully!";
        }
        else
        {
            cout << "Error! Please try again!";
        }
    }
};

class IAccountImpl {
public:
    virtual bool open(Account& account) = 0;
};

// SavingsImpl class implementing the interface
class SavingsImpl : public IAccountImpl {
public:
    bool open(Account& account) override {
        bool isOpened = false;
        // Assume Account class has a method to get the age of the holder
        // Assuming there is a method in Account class to get the date of birth
        // For simplicity, let's assume the method is getDOB() which returns a date
        // You'll need to adjust this according to your actual implementation
        int age = account->getAge();
        // Assuming Account class has a method to get the date of birth
        // Assuming there is a method in Account class to get the date of activation
        // For simplicity, let's assume the method is setActivationDate()
        // You'll need to adjust this according to your actual implementation
        Date dob = account.getDOB();

        if (age >= 18) {
            // Activate the account
            account.activate();
            // Set the current date as the activation date
            account.setActivationDate(Date()); // Current date, you need to implement Date class and its functionalities
            isOpened = true;
        }

        return isOpened;
    }
};

// AccountImplFactory class
class AccountImplFactory {
public:
    // Method to create the object of a given account type
    static IAccountImpl* create(const string& accountType) {
        IAccountImpl* accountImpl = nullptr;
        if (accountType == "Savings") {
            accountImpl = new SavingsImpl();
        } else {
            throw InvalidAccountTypeException(); // You need to define and implement this exception
        }
        return accountImpl;
    }
};

// Account class (You need to implement this)
class Account {
public:
    int getAge() const {
        // Implement this to get age of account holder
        return 0; // Placeholder
    }

    Date getDOB() const {
        // Implement this to get date of birth of account holder
        return Date(); // Placeholder
    }

    void activate() {
        // Implement this to activate the account
    }

    void setActivationDate(Date activationDate) {
        // Implement this to set activation date of the account
    }
};
// Class to manage the activities of the account.

int main()
{

    AccountController controller;
    // controller.open();
    // controller.withdraw();
    controller.transfer();
    return 0;
}
