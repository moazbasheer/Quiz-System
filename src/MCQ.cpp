#include "MCQ.h"
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "MCQ.h"
#include "Database.h"
using namespace std;
MCQ::MCQ(){}
MCQ::MCQ(const MCQ& mcq){
    questions=mcq.questions;
    choice[0]=mcq.choice[0];
    choice[1]=mcq.choice[1];
    choice[2]=mcq.choice[2];
    choice[3]=mcq.choice[3];
    answer=mcq.answer;
    id=mcq.id;
    ans=mcq.ans;
}

bool operator<(MCQ mcq1,MCQ mcq2){
    return mcq1.questions<mcq2.questions;
}


void MCQ::readQuestionFromFile(ifstream& file)      ///Function overriding to load MCQquestions from file.
{
    getline(file,questions);    ///Get the question.
    for(int i=0;i<4;i++)    ///Get the 4 choices.
    {
        getline(file,choice[i]);
    }
    answer=choice[0];   ///Set the correct answer.
    id=Database::NumberEnteredQuestions++;  ///Give an id for the question.
}

void MCQ:: print ()         ///Overriding function that printing when asking the player to answer.
{
    cout<<"ID:"<<id<<":"<<questions<<endl;      ///print the question with the id.
    cout<<"[a] "<<choice[0]<<"   [b]"<<choice[1]<<"   [c]"<<choice[2]<<"   [d]"<<choice[3]<<endl;   ///print the choices.
}

void MCQ::AddQuestion ()    ///overriding function that add a MCQ question.
{
            cout<<"Enter the question. \n";
            cin>>questions;
            cout<<"Enter the four choices. \n";
            cout<<"Or enter 'b' to return to add question again. \n";
            cin>>choice[0];
            if(choice[0]=="b") return ;         ///If choice equal b then return to add question.
            cin>>choice[1]>>choice[2]>>choice[3];   ///Enter the choices.
            vector <string> answer1 ;
            answer1.push_back(choice[0]);
            answer1.push_back(choice[1]);  ///Store the choices in answer1 vector.
            answer1.push_back(choice[2]);
            answer1.push_back(choice[3]);
            sort(answer1.begin(),answer1.end());  ///sorting answer1 vector.
            answer1.resize(unique (answer1.begin(),answer1.end())-answer1.begin());
            while (answer1.size()!=4)
            {
                cout<<"You answers isn't unique please try again: "<<endl;
                cout<<"Enter the four choices again: "<<endl;
                cout<<"Or enter 'b' to return to add question again. \n";
                answer1.clear();
                cin>>choice[0];
                if(choice[0]=="b") continue;
                cin>>choice[1]>>choice[2]>>choice[3];
                answer1.push_back(choice[0]);
                answer1.push_back(choice[1]);
                answer1.push_back(choice[2]);
                answer1.push_back(choice[3]);
                sort(answer1.begin(),answer1.end());
                answer1.resize(unique (answer1.begin(),answer1.end())-answer1.begin());
            }
            cout<<" the correct choice [a] or [b] or [c] or [d] \n";
            string correct;     ///Take the correct answer.
            cin>>correct;
            while (correct.size() > 1 || correct > "d" || correct<"a")  ///Handling invalid input.
            {
                cout<<"Invalid please enter the correct answer: \n";
                cout<<"Or enter 'b' to return to add question again. \n";
                cin>>correct;
                if(correct=="b") continue;
            }
            answer=correct;
            Database::MCQStorage.push_back(new MCQ(*this));
}
void MCQ::DeleteQuestion (int & BREAK)  ///overriding function to delete a MCQ question.
{
    cout<<"You will delete MCQ question. "<<endl<<"Please enter the id of it: "<<endl;
     int id;
     cin>>id;   ///get the id from the user.
     int found=0;
     for (int i=0;i<Database::MCQStorage.size();i++)
     {
         if (Database::MCQStorage[i]->id==id) ///Searching for the question with the same id.
         {
            found=1;
            Database::MCQStorage.erase(Database::MCQStorage.begin()+i); ///Delete the question from the vector.
            break;
         }
     }
     if(found) ///Check if found not equal zero.
     {
        cout<<"DELETED SUCCESSFULLY!\n"; BREAK=1;
     }
     else
        cout<<"ID NOT FOUND\n";
}
MCQ::MCQ (string q,string c1,string c2,string c3,string c4,string ans)
{
    questions=q;
    choice[0]=c1;
    choice[1]=c2;
    choice[2]=c3;
    choice[3]=c4;
    answer=ans;
}

