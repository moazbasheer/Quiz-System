#include "Player.h"
#include "Quiz.h"
#include "Database.h"
Player::Player()
{
    MenuLowerBound=1;
    MenuUpperBound=7;
}
Player::Player(const User &copy)  ///copy constructor that assigns the values of the object to the member of the class.
{
    LogedIn=1;
    MenuLowerBound=1;
    MenuUpperBound=7;
    FirstName=copy.FirstName;
    LastName=copy.LastName;
    Username=copy.Username;
    Password=copy.Password;
    Role=copy.Role;
}
int Player::MainMenu()
{
    cout<<"Hello player"<<FirstName<<" "<<LastName<<". \n";
    cout<<"1-switch accounts. \n2-update your name. \n3-Start new quiz. \n4-Display your score statistics. \n5-display all your scores. \n";
    cout<<"6-Display details of your last 2 quizzes. \n7-Exit Program. \n";
    cout<<"My choice: \n";

    int choice=GetChoice(MenuLowerBound,MenuUpperBound); ///call GetChoice function to get a valid choice.
    return choice;
}
void Player::StartNewQuiz()
{
    int TotalQuestions=6;

    if(Database::CompleteStorage.size()+Database::TFStorage.size()+Database::MCQStorage.size()<TotalQuestions) ///check if the available number of questions is less than the TotalQuestions.
    {
        cout<<"There is no enough questions. \n";
        return ;
    }
    Quiz quiz=Quiz();  ///If there is enough questions then will create an object of type Quize and call the empty constructor to call the random function and print function.
    quizes.push_back(new Quiz(quiz));  ///then push these questions in the quizes vector.
}

void Player::ViewStatistics()
{
    cout<<"Your score statistics per quiz: \n";
    cout<<"- Number of Quizzes taken: "<<quizes.size()<<"\n";
    if(quizes.size()<=0)  ///Check for the number of quizzes.
    {
        cout<<"There is no quizzes. \n";
        return ;
    }
    int minimum=1e9, maximum=-1;
    int CorrectAnswer=0;       ///Initialize the questions & the correct answers.
    int CorrectMCQ=0,CorrectTF=0,CorrectComplete=0;
    int TotalQuizSum=0;
    int MCQQuestions=0,TFQuestions=0,CompleteQuestions=0;
    cout<<quizes.size()<<"\n";   ///Display the size of the quizzes that available.
    map<string ,string > mp;
    mp["t"]="true"; mp["T"]="true";
    mp["f"]="false"; mp["F"]="false";
    for(int i=0;i<quizes.size();i++)  ///Until the size of the available quizzes end.
    {
        CorrectAnswer=0;
        for(int j=0;j<quizes[i]->MCQquestions.size();j++)  ///Until the end of the MCQ Questions in the quizes vector.
        {
            string temp=quizes[i]->MCQquestions[j]->ans.answer;  ///Assign the answer of the user to a variable temp.
            if(temp.size()==1 && quizes[i]->MCQquestions[j]->choice[temp[0]-'a']==quizes[i]->MCQquestions[j]->answer)  ///checks if the user answer is the right answer.
                CorrectAnswer++,CorrectMCQ++; ///If user's answer is true then increment the correct answers & the correct answers of MCQ questions.
        }
        MCQQuestions+=quizes[i]->MCQquestions.size();  ///Increment the number of MCQ questions.
        for(int j=0;j<quizes[i]->TFquestions.size();j++) ///Until the end of the True False questions.
            if(mp[quizes[i]->TFquestions[j]->ans.answer]==quizes[i]->TFquestions[j]->answer)  ///check if user's answer is the right answer.
                CorrectAnswer+=2,CorrectTF++; ///Increment the Correct answer if the user's answer is right.
        TFQuestions+=quizes[i]->TFquestions.size();  ///Then increment the True False questions.

        for(int j=0;j<quizes[i]->Completequestions.size();j++)  ///Until the end of the Complete Questions in the quizes vector.
            if(quizes[i]->Completequestions[j]->ans.answer==quizes[i]->Completequestions[j]->answer)   ///checks if the user answer is the right answer.
                CorrectAnswer+=2,CorrectComplete++;   ///Increment the Correct answer if the user's answer is right
        CompleteQuestions+=quizes[i]->Completequestions.size();  ///Then increment the Complete questions.
        int QuizScore=quizes[i]->TFGrade*CorrectTF+quizes[i]->CompleteGrade*CorrectComplete+quizes[i]->MCQGrade*CorrectMCQ; ///Calculate the total grade in the quizzes.
        TotalQuizSum+=QuizScore;
        maximum=max(maximum,QuizScore); ///Get the maximum score.
        minimum=min(minimum,QuizScore);   ///Get the minimum score.
    }
                    ///Then display the score statistics.
    cout<<"- Highest quiz score: "<<maximum<<"/10\n";
    cout<<"- Lowest quiz score: "<<minimum<<"/10\n";
    cout<<"- Average quiz score: "<<TotalQuizSum/10.0<<"/10\n";
    cout<<"Your score statistics per question type: \n";
    cout<<"- Number of MC questions: "<<MCQQuestions<<"\n";
    cout<<"- Number of Complete questions: "<<CompleteQuestions<<"\n";
    cout<<"- Number of T/F Questions: "<<TFQuestions<<"\n";
    cout<<"- Average grade for MC questions: "<<quizes[0]->MCQGrade*CorrectMCQ/MCQQuestions<<"/2\n";
    cout<<"- Average grade for Complete questions: "<<quizes[0]->CompleteGrade*CorrectComplete/CompleteQuestions<<"/2\n";
    cout<<"- Average grade for T/F questions: "<<quizes[0]->TFGrade*CorrectTF/TFQuestions<<"/1\n";
    cout<<"Press any key if you want to go back to the main menu or [e] to exit. \n";
    cout<<"My choice: \n";
    string c;
    cin>>c;
    if(c=="e") exit(0); ///Check if the user want to exist or not.
}

void Player::DisplayAllScores()
{
    cout<<"Your score statistics per quiz: \n";
    cout<<"- Number of Quizzes taken: "<<quizes.size()<<"\n";  ///Display the number of quizzes.
    int CorrectAnswer=0;
    int CorrectMCQ=0,CorrectTF=0,CorrectComplete=0;
    map<string ,string > mp;
    mp["t"]="true"; mp["T"]="true";  ///assign the values true & false to mp for checking the user's answer.
    mp["f"]="false"; mp["F"]="false";
    for(int i=0;i<quizes.size();i++)
    {
        cout<<"Quiz no."<<i+1<<"\n";
        CorrectAnswer=0;
        for(int j=0;j<quizes[i]->MCQquestions.size();j++)
        {
            string temp=quizes[i]->MCQquestions[j]->ans.answer;
            if(temp.size()!=1 || (temp[0]>'d' || temp[0]<'a')) continue; ///Check for not valid answers.
            if(quizes[i]->MCQquestions[j]->choice[temp[0]-'a']==quizes[i]->MCQquestions[j]->answer) ///If the answer is correct then increment the correct answers.
                CorrectAnswer++,CorrectMCQ++;
        }
        for(int j=0;j<quizes[i]->TFquestions.size();j++)
            if(mp[quizes[i]->TFquestions[j]->ans.answer]==quizes[i]->TFquestions[j]->answer)
                CorrectAnswer++,CorrectTF++;   ///If the answer is correct then increment the correct answers.

        for(int j=0;j<quizes[i]->Completequestions.size();j++)
            if(quizes[i]->Completequestions[j]->ans.answer==quizes[i]->Completequestions[j]->answer)
                CorrectAnswer++,CorrectComplete++;
        cout<<"Correct answer : "<<CorrectAnswer<<"\n";  ///Display the correct answer, the wrong answer and the grade for this quiz.
        cout<<"Wrong answer : "<<quizes[i]->TFquestions.size()+quizes[i]->MCQquestions.size()+quizes[i]->Completequestions.size()-CorrectAnswer<<"\n";
        cout<<"Total Quiz Score: "<<(CorrectComplete*quizes[i]->CompleteGrade+CorrectMCQ*quizes[i]->MCQGrade+CorrectTF*quizes[i]->TFGrade)<<"/10\n";
    }

}

void Player::DisplayLast2Quizes()
{
    int num=(quizes.size()); ///Assign the total number of questions to a num variable.
    for(int i=num-2;i<num;i++) ///For the last 2 available quizzes.
    {
        while(i<0)
            i++;
        int CorrectAnswer=0;
        int CorrectMCQ=0,CorrectTF=0,CorrectComplete=0;
        cout<<"Quiz no."<<i+1<<"\n";
        CorrectAnswer=0;
        for(int j=0;j<quizes[i]->MCQquestions.size();j++)
        {
            cout<<"["<<j+1<<"] ";
            quizes[i]->MCQquestions[j]->print();  ///Display a MCQ question through calling the print function.
            cout<<"Player answer is "<<quizes[i]->MCQquestions[j]->ans.answer<<"\n";
            cout<<"Correct answer is "<<quizes[i]->MCQquestions[j]->answer<<"\n";
            string temp=quizes[i]->MCQquestions[j]->ans.answer;
            if(temp.size()==1 && quizes[i]->MCQquestions[j]->choice[temp[0]-'a']==quizes[i]->MCQquestions[j]->answer) ///checking the right answer.
            {
                cout<<"Right answer : grade:"<<quizes[i]->MCQGrade<<"\n"; ///give the grade of the right answer.
                CorrectAnswer++,CorrectMCQ++;
            }
            else {
                cout<<"Wrong answer : grade:"<<0<<"\n";  ///Else give the grade of the wrong answer.
            }
        }
        for(int j=0;j<quizes[i]->TFquestions.size();j++)
        {
            cout<<"["<<j+1<<"] ";
            quizes[i]->TFquestions[j]->print();
            map<string ,string > mp;
            mp["t"]="true"; mp["T"]="true";
            mp["f"]="false"; mp["F"]="false";
            cout<<"Player answer is "<<quizes[i]->TFquestions[j]->ans.answer<<"\n";
            cout<<"Correct answer is "<<quizes[i]->TFquestions[j]->answer<<"\n";
            if(mp[quizes[i]->TFquestions[j]->ans.answer]==quizes[i]->TFquestions[j]->answer){
                cout<<"Right answer : grade:"<<quizes[i]->TFGrade<<"\n";
                CorrectAnswer++,CorrectTF++;
            }
            else {
                cout<<"Wrong answer : grade:"<<0<<"\n";
            }
        }
        for(int j=0;j<quizes[i]->Completequestions.size();j++)
        {
            cout<<"["<<j+1<<"] ";
            quizes[i]->Completequestions[j]->print(); ///Display a Complete question using the print function.
            cout<<"Player answer is "<<quizes[i]->Completequestions[j]->ans.answer<<"\n";
            cout<<"Correct answer is "<<quizes[i]->Completequestions[j]->answer<<"\n";
            if(quizes[i]->Completequestions[j]->ans.answer==quizes[i]->Completequestions[j]->answer)  ///Checking th right answer.
            {
                cout<<"Right answer : grade:"<<quizes[i]->CompleteGrade<<"\n";  ///give the grade of the right answer.
                CorrectAnswer++,CorrectComplete++;
            }
            else {
                cout<<"Wrong answer : grade:"<<0<<"\n";  ///Else give the grade of the wrong answer.
            }
        }
        cout<<"Correct answer : "<<CorrectAnswer<<"\n";  ///Display the correct & wrong answers.
        cout<<"Wrong answer : "<<quizes[i]->TFquestions.size()+quizes[i]->MCQquestions.size()+quizes[i]->Completequestions.size()-CorrectAnswer<<"\n";
        cout<<"Total Quiz Score: "<<(CorrectComplete*quizes[i]->CompleteGrade+CorrectMCQ*quizes[i]->MCQGrade+CorrectTF*quizes[i]->TFGrade)<<"/10\n";
    }
}

void Player::ExecuteChoice(int choice) ///Execute function that take the choice and execute it.
{
    if(choice==1)
        switchAccounts(); ///call the Switch function for switching accounts.
    else if(choice==2)
    {
        UpdateName(); ///Call Update name function to update the name.
    }
    else if(choice==3)
    {
        StartNewQuiz();  ///Call the Start new quiz function to take a quiz.
    }
    else if(choice==4)
    {
        ViewStatistics();  ///Call view statistics function to know the score.
    }
    else if(choice==5)
    {
        DisplayAllScores();  ///Call DisplayAllScores function to know the quiz score.
    }
    else if(choice==6)
    {
        DisplayLast2Quizes(); ///Call DisplayLast2Quizes function to know the last 2 quizzes score.
    }
    else if(choice==7) exit(0); ///Else choose 7 to exit.
}
