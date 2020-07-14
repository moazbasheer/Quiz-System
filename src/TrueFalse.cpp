#include "TrueFalse.h"
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include"Database.h"
using namespace std;
TrueFalse::TrueFalse(){}
void TrueFalse::readQuestionFromFile(ifstream& file) ///overriding function to load TrueFalse questions from file.
{
    getline(file,question);
    getline(file,answer);
    id=Database::NumberEnteredQuestions;
    Database::NumberEnteredQuestions++;
}
void TrueFalse:: print ()   ///Overriding function for printing when asking the player to answer
{
    cout<<"ID: "<<id<<" "<<question<<endl;
    cout<<"[a]"<<"True"<<endl<<"[b]"<<"False"<<endl;

}

void TrueFalse::AddQuestion() ///Overriding function to add a TrueFalse question.
{
    cout<<"enter the question \n";
    cin>>question;       ///Take the question from the user.
    cout<<"the correct answer [1] true  [2] false \n";
    cin>>answer;   ///Take the answer.
    while ((answer !="true" && answer!="false")) ///Check for invalid answers.
    {
        cout<<"invalid answer ,(true or false) or b to return back "<<endl;
        if(answer=="b") return ;
        cin>>answer;
    }
    Database::TFStorage.push_back(new TrueFalse(*this)); ///Push back the question to TFStorage vector.
}
void TrueFalse:: DeleteQuestion(int &BREAK) ///Overriding function to delete a TrueFalse question.
{
    cout<<"You will delete True or False question. "<<endl<<"Please enter the id of it: "<<endl;
     int id;
     cin>>id; ///Get the id.
     int found=0;
     for (int i=0;i<Database::TFStorage.size();i++)  ///searching for the question with the same id.
     {
         if (Database::TFStorage[i]->id==id){
            found=1;
            Database::TFStorage.erase(Database::TFStorage.begin()+i); ///Delete the question with the same id.
            break;
         }
     }
     if(found) ///If found not equal 0 then the delete complete.
     {
        cout<<"DELETED SUCCESSFULLY!\n"; BREAK=1;
     }else cout<<"ID NOT FOUND\n";
}
TrueFalse:: TrueFalse (string q,string ans)
{
    question=q;
    answer=ans;
};
TrueFalse:: TrueFalse (const TrueFalse& tf)
{
    question=tf.question;
    answer=tf.answer;
    id=tf.id;
    ans=tf.ans;
};
