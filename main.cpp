/*
Team members:

Ibrahim Samir Esmail 20180003 G13
Moaz Mahmoud Saad 20180286  G13 
Moaz Basheer Anwar 20180285  G14
Nader Fekry Salah 20180304  G13
*/
#include <iostream>
#include"User.h"
#include"Question.h"
#include"DataBase.h"
#include"Admin.h"
using namespace std;
vector<User*> Database::UserStorage;
vector<TrueFalse*> Database::TFStorage;
vector<MCQ*> Database::MCQStorage;
vector<Complete*> Database::CompleteStorage;
int Database::NumberEnteredQuestions=1;
int User::LogedIn=0;
int main()
{
    Database::AddInitialData(); ///Call AddIntitialData form calss Database to initialize users.
    User myUser;
    myUser.Start(); ///Call function start from class User to start the program.
    return 0;
}
