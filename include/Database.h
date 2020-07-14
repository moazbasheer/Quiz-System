#ifndef DATABASE_H
#define DATABASE_H
#include"User.h"
#include"Question.h"
#include<vector>
#include"Question.h"
#include"TrueFalse.h"
#include"Complete.h"
#include"MCQ.h"
using namespace std;
class Database
{
    public:
        Database();
        static int NumberEnteredQuestions;
        static vector<User*> UserStorage;
        static vector<TrueFalse*> TFStorage;
        static vector<MCQ*> MCQStorage;
        static vector<Complete*> CompleteStorage;
        static void AddInitialData();
        static void ViewAllUsers();
        ~Database();
    protected:

    private:
};

#endif // DATABASE_H
