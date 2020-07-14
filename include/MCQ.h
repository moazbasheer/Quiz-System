#ifndef MCQ_H
#define MCQ_H
#include <string>
#include <bits/stdc++.h>
#include <iostream>
#include"Question.h"
using namespace std;
class MCQ:public Question{
    public:
        void print();
        void AddQuestion();
        void readQuestionFromFile(ifstream& file);
        void DeleteQuestion (int & BREAK);
        friend bool operator<(MCQ mcq1,MCQ mcq2);
        MCQ();
        MCQ (string q,string c1,string c2,string c3,string c4,string ans);
        MCQ(const MCQ& mcq);
        string questions;
        string choice[4];
        string answer;

};

#endif // MCQ_H
