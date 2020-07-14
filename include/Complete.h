#ifndef COMPLETE_H
#define COMPLETE_H
#include"Question.h"
#include <string>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;
class Complete:public Question
{
    public:
        bool isValidQuestion(string s);
        bool isValidAnswer(string s);
        void print();
        void readQuestionFromFile(ifstream& file);
        Complete();
        Complete (string q,string ans);
        Complete(const Complete& temp);
        void AddQuestion(int& BREAK);
        void DeleteQuestion (int &BREAK);
        string question;
        string answer;

};

#endif // COMPLETE_H
