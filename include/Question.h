#ifndef QUESTION_H
#define QUESTION_H

#include<iostream>
#include<vector>
#include"PlayerAnswer.h"
using namespace std;
class Question
{
    public:
        int id;
        PlayerAnswer ans;
        Question();
        /// overriding
        virtual void AddQuestion();
        virtual void print();
        virtual void readQuestionFromFile(ifstream& file);
        virtual void DeleteQuestion(int &BREAK);
    protected:

    private:
};

#endif // QUESTION_H
