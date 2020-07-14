#include "Quiz.h"
#include "TrueFalse.h"
#include "Complete.h"
#include "MCQ.h"
#include "Database.h"
#include <stdlib.h>
#include <vector>
Quiz::Quiz() ///Empty constructor that initialize the number of questions and the grade of each kind of questions.
{
    NumTF=2,NumMCQ=2,NumComplete=2;
    TFGrade=1,MCQGrade=2,CompleteGrade=2;
    RandomQuestion();  ///Function that get a random questions.
    PrintQuestions(); ///Function that print the questions.
}
Quiz::Quiz(const Quiz& quiz)
{
    indexTF=quiz.indexTF;
    indexMCQ=quiz.indexMCQ;
    indexComplete=quiz.indexComplete;
    MCQquestions=quiz.MCQquestions;
    Completequestions=quiz.Completequestions;
    TFquestions=quiz.TFquestions;
    NumTF=quiz.NumTF;
    NumMCQ=quiz.NumMCQ;
    NumComplete=quiz.NumComplete;
    TFGrade=quiz.TFGrade;
    MCQGrade=quiz.MCQGrade;
    CompleteGrade=quiz.CompleteGrade;
}
Quiz::~Quiz(){}
void Quiz::PrintQuestions()  ///Function to print the questions.
{

    for(int i=0;i<NumTF;i++) ///Until the end of number of TrueFalse questions.
    {
        Database::TFStorage[indexTF[i]]->print(); ///print a TrueFalse question.
        cout<<"Write answer t,T for true or F,f for false. \nOtherwise it will be wrong. \n";
        string answer;
        getline(cin,answer); ///Get the answer from the user.
        TrueFalse tf(*Database::TFStorage[indexTF[i]]);
        tf.ans.answer=answer; ///Store the answer.
        TFquestions.push_back(new TrueFalse(tf));
    }
    for(int i=0;i<NumComplete;i++)  ///Until the end of number of Complete questions.
    {
        Database::CompleteStorage[indexComplete[i]]->print(); ///print a Complete question.
        cout<<"Write answer. \n";
        string answer;
        getline(cin,answer); ///Get the answer from the user.
        Complete complete(*Database::CompleteStorage[indexComplete[i]]);
        complete.ans.answer=answer;  ///store the answer.
        Completequestions.push_back(new Complete(complete));
    }
    for(int i=0;i<NumMCQ;i++)  ///Until the end of number of MCQ questions.
    {
        Database::MCQStorage[indexMCQ[i]]->print();  ///print a Complete question.
        cout<<"Write answer a,b,c,d otherwise it will be wrong. \n";
        string answer;
        getline(cin,answer);  ///Get the answer from the user.
        MCQ mcq(*Database::MCQStorage[indexMCQ[i]]);
        mcq.ans.answer=answer;  ///store the answer.
        MCQquestions.push_back(new MCQ(mcq));
    }
}
void Quiz::RandomQuestion()
{
    while (indexTF.size()<2) ///Utile the size of the vector indexTF equal 2.
    {
        for (int k=0;k<2;k++)
        {
            int g=rand()%Database::TFStorage.size();  ///Give g a random number from TFStorage indexes.

            indexTF.push_back(g);  ///store this number in indexTF.
        }
        sort(indexTF.begin(),indexTF.end());  ///Sorting indexTF vector.
        indexTF.resize(unique(indexTF.begin(),indexTF.end())-indexTF.begin()); ///resize the vector with a unique element every time.
    }

    while (indexComplete.size()<2)  ///Utile the size of the vector indexComplete equal 2.
    {
        for (int k=0;k<2;k++)
        {
            int g=rand()%Database::CompleteStorage.size();  ///Give g a random number from CompleteStorage indexes.

            indexComplete.push_back(g);  ///store this number in indexComplete.
        }
        sort(indexComplete.begin(),indexComplete.end());   ///Sorting indexComplete vector.
        indexComplete.resize(unique(indexComplete.begin(),indexComplete.end())-indexComplete.begin());  ///resize the vector with a unique element every time.
    }

    while (indexMCQ.size()<2)  ///Utile the size of the vector indexMCQ equal 2.
    {
        for (int k=0;k<2;k++)
        {
            int g=rand()%Database::MCQStorage.size();  ///Give g a random number from MCQStorage indexes.

            indexMCQ.push_back(g);
        }
        sort(indexMCQ.begin(),indexMCQ.end());  ///Sorting indexComplete vector.
        indexMCQ.resize(unique(indexMCQ.begin(),indexMCQ.end())-indexMCQ.begin());  ///resize the vector with a unique element every time.
    }
}

