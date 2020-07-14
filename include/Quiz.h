#ifndef QUIZ_H
#define QUIZ_H
#include"Complete.h"
#include"TrueFalse.h"
#include"MCQ.h"
#include<vector>
class Quiz
{
    public:
        vector <int> indexTF;
        vector <int> indexMCQ;
        vector <int> indexComplete;

        vector<MCQ*> MCQquestions;
        vector<Complete*> Completequestions;
        vector<TrueFalse*> TFquestions;

        int NumTF,NumMCQ,NumComplete;
        int TFGrade,MCQGrade,CompleteGrade;
        void RandomQuestion();
        void PrintQuestions();
        Quiz();
        Quiz(const Quiz& quiz);
        ~Quiz();
    protected:

    private:
};

#endif // QUIZ_H
