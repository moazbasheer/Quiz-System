#ifndef PLAYER_H
#define PLAYER_H

#include"User.h"
#include"Quiz.h"
#include<vector>
using namespace std;
class Player:public User
{
    public:
        vector<Quiz*> quizes;
        Player();
        void ViewStatistics();
        Player(const User &copy);
        void StartNewQuiz();
        int MainMenu();
        void DisplayAllScores();
        void DisplayLast2Quizes();
        void ViewAllScores();
        void ExecuteChoice(int choice);
    protected:

    private:
};

#endif // PLAYER_H
