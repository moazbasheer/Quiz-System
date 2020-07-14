#include "Database.h"
#include"User.h"
#include"Question.h"
using namespace std;

Database::Database(){}

void Database::AddInitialData(){          ///Initialize the first two users.
    User InitialUser1,InitialUser2;         ///Two objects of class User.
    InitialUser1.FirstName="user";
    InitialUser1.LastName="user";
    InitialUser1.Username="AH1";
    InitialUser1.Password="123456";
    InitialUser1.Role="admin";
    Database::UserStorage.push_back(new User(InitialUser1));    /* Push back the values of the first user to the vector UserStorage
                                                                   by calling the copy constructor of class User. */
    InitialUser2.FirstName="Ahmed";
    InitialUser2.LastName="Ahmed";
    InitialUser2.Username="AH2";
    InitialUser2.Password="123456";
    InitialUser2.Role="player";
    Database::UserStorage.push_back(new User(InitialUser2));    /* Push back the values of the second user to the vector UserStorage
                                                                   by calling the copy constructor of class User. */
}

void Database::ViewAllUsers(){
    cout<<"Existing users in the system:\n";
    cout<<"First name\t Last name\t Username\t Role\n";

    for(int i=0;i<UserStorage.size();i++){             /* Until the end of the users stored in UserStorage vector.
                                                          This function will print the data for every user stored in the UserStorage. */
        cout<<Database::UserStorage[i]->FirstName<<"\t \t ";
        cout<<Database::UserStorage[i]->LastName<<"\t \t ";
        cout<<Database::UserStorage[i]->Username<<"\t \t ";
        cout<<Database::UserStorage[i]->Role<<"\t \t ";
        cout<<endl;
    }

}
Database::~Database()       ///A Database destructor to delete the values in the vectors to free the memory.
{
    for(int i=0;i<UserStorage.size();i++)
        delete UserStorage[i];              ///A loop to delete the data in UserStorage vector to free the memory.
    UserStorage.clear();                ///Clear function to ensure that the memory is clear.
    for(int i=0;i<MCQStorage.size();i++)
        delete MCQStorage[i];
    MCQStorage.clear();
    for(int i=0;i<TFStorage.size();i++)
        delete TFStorage[i];
    TFStorage.clear();
    for(int i=0;i<CompleteStorage.size();i++)
        delete CompleteStorage[i];
    CompleteStorage.clear();
}
