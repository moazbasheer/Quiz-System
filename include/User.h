#include <iostream>
#include <string>
#ifndef USER_H
#define USER_H
using namespace std;
class User{

    protected:
        int MenuLowerBound,MenuUpperBound;
    public:
        string FirstName,LastName,Role;
        string Username;
        string Password;
        static int LogedIn;
        User();
        User(const User& user);
        int LogIn(string username,string password);
        int GetChoice(int lowerbound,int upperbound);
        bool operator==(const User& user);
        void switchAccounts();
        void UpdateName();
        virtual void ExecuteChoice(int choice);
        virtual int MainMenu();
        void Start();

    protected:

    private:
};

#endif // USER_H
