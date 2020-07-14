#include "User.h"
#include"DataBase.h"
#include"Admin.h"
#include"Player.h"
using namespace std;
User::User(){}

User::User(const User& user)    ///copy constructor that assigns the values of the object to the member of the class.
{
    MenuLowerBound=user.MenuLowerBound;
    MenuUpperBound=user.MenuUpperBound;
    FirstName=user.FirstName;
    LastName=user.LastName;
    Role=user.Role;
    Username=user.Username;
    Password=user.Password;
}
void User::Start()
{
while(true)
    {
        int UserNumber=MainMenu();      ///If the user exist the the value of UserNumber will be positive else will be -1.
        while(UserNumber==-1)       ///check if the user not exist.
        {
            cout<<"Not Found try again please. \n";
            cout<<"Enter 'e' to exit, or any key to continue. \n";

            string ch;      ///Declare a string to take the choice of the user.
            cin>>ch;
            cin.ignore();

            if(ch=="e") exit(0);    ///Check if the choice is 'e' will Exit else will return to the main menu.
            UserNumber=MainMenu();
        }
        LogedIn=1;
        cout<<"You Logged in successfully. \n";

        if(Database::UserStorage[UserNumber]->Role=="admin")    ///Check for the role of the user, after login successfully.
            Database::UserStorage[UserNumber]=new Admin(*Database::UserStorage[UserNumber]);    ///assign the vector UserStorage to class admin if the role was admin
        else
            Database::UserStorage[UserNumber]=new Player(*Database::UserStorage[UserNumber]);   ///assign the vector UserStorage to class player if the role was player
        Database::UserStorage[UserNumber]->LogedIn=1;
        while(true)
        {
            int choice=Database::UserStorage[UserNumber]->MainMenu();
            cin.ignore();
            if(LogedIn==0) break;
            Database::UserStorage[UserNumber]->ExecuteChoice(choice);

            if(LogedIn==0) break;
        }
    }
}

void User::UpdateName()
{
    cout<<"Enter First name\n";
    getline(cin,FirstName);
    cout<<"Enter Last name\n";
    getline(cin,LastName);
}

bool User::operator==(const User& user)  //Operator oveloading that enable me to check the equality.
{
    return Username==user.Username;
}

int User::MainMenu()
{
    cout<<"*******************************************************************\n";
    cout<<"Welcome to the Quiz game program V2.0!\n";
    cout<<"*******************************************************************\n";
    cout<<"Enter Username :\n";
    string username; getline(cin,username);  ///Take Username
    cout<<"Enter Password :\n";
    string password; getline(cin,password);     ///Take Password
    return LogIn(username,password);        ///Return Positive number if the user exist & Return -1 if the user not exist
}

int User::LogIn(string username,string password)
{

    for(int i=0;i<Database::UserStorage.size();i++)  ///Until the data in the UserStorage vector end.
    {
        if(username==Database::UserStorage[i]->Username && password==Database::UserStorage[i]->Password)
        {
            return i;                                       ///Check if the username & password are the same of any user in UserStorage.
        }                                               ///Return positive number if true & -1 if false.
    }
    return -1;
}

int User::GetChoice(int lowerbound,int upperbound)  ///Function for handling invalid choices.
{
        int choice; cin>>choice;
        while(choice>upperbound || choice<lowerbound)
        {
            cout<<"Please enter a valid number, or enter '-1' to switch accounts. \n";
            cin>>choice;
            if(choice==-1)
            {
                LogedIn=0;
                break;
            }
        }
    return choice;
}

void User::switchAccounts()
{
    LogedIn=0;
}

void User::ExecuteChoice(int choice){}
