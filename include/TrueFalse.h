#ifndef TRUEORFALSE_H
#define TRUEORFALSE_H
#include <string>
#include <bits/stdc++.h>
#include <iostream>
#include"Question.h"
using namespace std;
class TrueFalse:public Question
{
    public:
        void print ();
        void readQuestionFromFile(ifstream& file);
        TrueFalse();
        TrueFalse (string q,string ans);
        TrueFalse (const TrueFalse& tf);
        void AddQuestion();
        void DeleteQuestion(int &BREAK);
        string question;
        string answer;
};

#endif // TRUEORFALSE_H
