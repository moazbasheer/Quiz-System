#include "Complete.h"
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include"Database.h"
using namespace std;
Complete::Complete(){}
void Complete::readQuestionFromFile(ifstream& file) ///Overriding function to load complete questions from file.
{
    getline(file,question);
    getline(file,answer);
    id=Database::NumberEnteredQuestions++;
}
void Complete:: print () ///Overriding function for printing when asking the player to answer
{
    cout<<"ID: "<<id<<" "<<question<<endl;
}
bool Complete::isValidQuestion(string s){
    int cnt=0;
    int n=(int)s.size();
    for(int i=0;i<n-1;i++){
        if(s[i]=='.' && s[i+1]=='.' ){
            cnt++;
            while(i<s.size() && s[i]=='.') i++;
        }
    }
    return cnt==1;
}
bool Complete::isValidAnswer(string s){
    int flag=0;
    for(int i=0;i<(int)s.size();i++){
        if(s[i]==' ') flag=1;
        else if(s[i]!=' ' && flag) return false;
    }
    return true;
}
void Complete::AddQuestion(int &BREAK) ///Overriding function to add Complete question.
{
    while(true){
        ///Take the question and the answer.
        cout<<"Enter the question: \n";
        getline(cin,question);
        while(!isValidQuestion(question)){
            cout<<"Invalid question try again or enter 'b' to go to add question\n";
            getline(cin,question);
            if(question=="b") {BREAK=1; break;}
        }
        cout<<"Enter the answer: \n";
        getline(cin,answer);
        while(!isValidAnswer(answer)){
            cout<<"Invalid answer try again or enter 'b' to go to add question \n";
            getline(cin,answer);
            if(answer=="b"){ BREAK=1; break;}
        }
        break;
    }
    Database::CompleteStorage.push_back(new Complete(*this)); ///Push pack the question and the answer to theCompleteStorage vector.
}
void Complete::DeleteQuestion (int &BREAK) ///overriding function to delete Complete question.
{
    cout<<"You will delete Complete question. "<<endl<<"Please enter the id of it: "<<endl;
     int id;
     cin>>id; ///Get the id of the question.
     int found=0;
     for (int i=0;i<Database::CompleteStorage.size();i++) ///Searching for the question with the same id.
     {
         if (Database::CompleteStorage[i]->id==id)
         {
            found=1;
            Database::CompleteStorage.erase(Database::CompleteStorage.begin()+i); ///Delete the id & the question from the vector.
            break;
         }
     }
     if(found) ///If found not equal to zero then the delete complete.
     {
        cout<<"DELETED SUCCESSFULLY!\n"; BREAK=1;
     }
     else
        cout<<"ID NOT FOUND\n";
}
Complete::Complete (string q,string ans)
{
    question=q;
    answer=ans;
}

Complete::Complete(const Complete& temp){
    question=temp.question;
    answer=temp.answer;
    id=temp.id;
    ans=temp.ans;
}
