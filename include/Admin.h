#ifndef ADMIN_H
#define ADMIN_H
#include"User.h"
#include"MCQ.h"
class Admin:public User{
    private:
        int MenuLowerBound,MenuUpperBound;
    public:
        Admin();

        void LoadFromFile();
        Admin(const User & copy);
        bool pre(MCQ*& mcq1,MCQ*& mcq2);
        void AddNewUser();
        void PrintQuestions();
        void AddQuestion();
        void DeleteQuestion();
        bool IsUserFound(User newUser);
        int MainMenu();
        void ExecuteChoice(int choice);

    protected:

    private:
};

#endif // ADMIN_H
