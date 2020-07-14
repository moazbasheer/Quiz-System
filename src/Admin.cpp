#include "Admin.h"
#include"Database.h"
#include "MCQ.h"
#include"Complete.h"
#include"TrueFalse.h"
Admin::Admin()
{
    MenuLowerBound=1;
    MenuUpperBound=8;
}

Admin::Admin(const User & copy)  ///Copy constructor to assign the values of the object to the members of the class.
{
    MenuLowerBound=1;
    MenuUpperBound=8;
    FirstName=copy.FirstName;
    LastName=copy.LastName;
    Username=copy.Username;
    Password=copy.Password;
    Role=copy.Role;
}

int Admin::MainMenu(){
    cout<<"come "<<FirstName<<" "<<LastName <<"(ADMIN), please choose from the following options:\n";
    cout<<"1-switch accounts. \n2-update your name. \n3-View all users. \n4-Add new user.\n5-view all questions. \n6-add new question. \n7-Load question from file. \n";
    cout<<"8-Exit Program. \n";
    cout<<"My choice: \n";

    int choice=GetChoice(MenuLowerBound,MenuUpperBound); ///Function to handle choice errors.
    return choice;
}
string Tolower(string temp){         ///Function that takes a string and return it in lowercase.
    for(int i=0;i<temp.size();i++){
        temp[i]=tolower(temp[i]);
    }
    return temp;
}

void Admin::AddNewUser()
{
    User newuser;
    newuser.LogedIn=1;      ///Initialize login users to 1.
    cout<<"Enter 'w' if want to return to main menu\n";
    string temp;
    getline(cin,temp);
    if(temp=="w") return ;
    cout<<"Enter First name: \n";     ///Take the members of the new users.
    getline(cin,newuser.FirstName);
    cout<<"Enter Last name: \n";
    getline(cin,newuser.LastName);
    cout<<"Enter Username: \n";
    getline(cin,newuser.Username);
    cout<<"Enter Password: \n";
    getline(cin,newuser.Password);
    cout<<"Enter Role (admin/player): \n";
    getline(cin,newuser.Role);

    newuser.Role=Tolower(newuser.Role); ///Make the newuser role in lowercase.

    while(IsUserFound(newuser)){ ///If the user is already found in the UserStorage vector then an error message will appear.
        cout<<"Enter a valid username, or enter -1 to return to main menu. \n";
        getline(cin,newuser.Username);       ///Take the new choice of the user either to return to the main menu or to enter another username.
        if(newuser.Username=="-1") return ; ///If the choice equal -1 then will return to the main menu.
    }
    while(newuser.Role!="admin" && newuser.Role!="player"){   ///Checks if the role of the newuser was not an (admin / player).
        cout<<"Enter valid Role (admin/player) or enter -1 to return to main menu. \n";
        getline(cin,newuser.Role);
        if(newuser.Role=="-1") return ;
    }

    Database::UserStorage.push_back(new Admin(newuser)); /* Push back the values of the newuser to the vector UserStorage
                                                            by calling the copy constructor of class Admin. */

    cout<<"Enter 't' to switch account or any to continue \n";
    string tmp;
    cin>>tmp;
    cin.ignore();
    if(tmp=="t") LogedIn=0;

}

bool Admin::IsUserFound(User newUser){       ///Checks if the user is already found in the UserStorage vector.
    for(int i=0;i<Database::UserStorage.size();i++){
        if(*Database::UserStorage[i]==newUser)
            return true;          ///Return true if found else return false.
    }
    return false;
}

void Admin::PrintQuestions()
{
    cout<<"Number of questions available: ";
    cout<<Database::TFStorage.size()+Database::MCQStorage.size()+Database::CompleteStorage.size()<<"\n"; ///Print the number of all questions available from all kinds.
    cout<<"================================================================\n";
    cout<<"MCQ List (Number of questions:"<<Database::MCQStorage.size()<<").\n";  ///Print the number of MCQ questions.
    for(int i=0;i<Database::MCQStorage.size();i++)   ///Until the end of MCQ questions.
    {
        cout<<"["<<i+1<<"] ";
        cout<<"ID:"<<Database::MCQStorage[i]->id<<":"<<Database::MCQStorage[i]->questions<<endl;  ///Print the question.
        cout<<"[a] "<<Database::MCQStorage[i]->choice[0]<<"   [b]"; ///print the 4 choices.
        cout<<Database::MCQStorage[i]->choice[1]<<"   [c]";
        cout<<Database::MCQStorage[i]->choice[2]<<"   [d]";
        cout<<Database::MCQStorage[i]->choice[3]<<endl;
        cout<<"Correct answer: "<<Database::MCQStorage[i]->choice[0]<<endl;  ///Print  the correct answer.
    }
    cout<<"================================================================\n";
    cout<<"True or False List (Number of questions:"<<Database::TFStorage.size()<<").\n"; ///Print the number of True False questions.
    for(int i=0;i<Database::TFStorage.size();i++)    ///Utile the end of True False questions.
    {
        cout<<"["<<i+1<<"] ";
        cout<<"(ID:"<<Database::TFStorage[i]->id<<"):"<<Database::TFStorage[i]->question<<endl;   ///Print the question.
        cout<<"Correct answer : "<<Database::TFStorage[i]->answer<<endl;    ///Print the correct answer.
    }
    cout<<"================================================================\n";
    cout<<"Complete List (Number of questions:"<<Database::CompleteStorage.size()<<").\n";   ///Print the number of Complete questions.
    for(int i=0;i<Database::CompleteStorage.size();i++)     ///Until the end of complete questions.
    {
        cout<<"["<<i+1<<"] ";
        cout<<"(ID:"<<Database::CompleteStorage[i]->id<<"):"<<Database::CompleteStorage[i]->question<<endl;  ///Print the question.
        cout<<"Correct answer : "<<Database::CompleteStorage[i]->answer<<endl;  ///Print the correct answer.
    }
    cout<<"Enter 'd' to delete some questions, or any key to go to main menu. \n";
    string ch;
    cin>>ch;   ///Get the choice from the user.
    if(ch=="d") DeleteQuestion();  ///If the choice equal d then will call the DeleteQuestion function to delete a question.
}

void Admin::AddQuestion()
{
int num;
string question,choice1,choice2,choice3,choice4,answer,correct,tfans;
string type="a";
while (type != "w" )
{
    cout<<"Enter the type of question: \n";
    cout<<"[1] MCQ. \n"<<"[2] COMPLETE. \n"<<"[3] TRUE OR FALSE. \n or Enter 'w' to go back to main menu. ";
    cin>>type;              ///Get the choice from the user.
    cin.ignore();
    if(type=="w") break;      ///If the choice equal w then go back to main menu.
    if(type>"3" || type<"1")    ///If choice greater than 3 or less than 1 then an error message will appear.
    {
         cout<<"Invalid type, try again\n";
         continue;
    }
    if (type=="1")  ///If choice equal 1 then the user will add a MCQ question.
    {
        cout<<"Enter number of questions. \n";
        cout<<"Or Enter '-1' to return to add question again. \n";
        cin>>num;      ///Get the choice from the user.
        if(num==-1) continue;
        while(num<0)    ///Handle invalid choice.
        {
            cout<<"Enter valid number. \n";
            cout<<"Or enter '-1' to return to add question again. \n";
            cin>>num;
            if(num==-1) break;
        }

        if(num==-1) continue; ///If the choice equal -1 then will return to add question.

        while (num>0) ///If the choice is greater than 0 then the user will add the question.
        {
            MCQ mcq;    ///Declare an object of class MCQ;
            mcq.AddQuestion();   ///Call AddQuestion function from MCQ class to add a question.
            num--;   ///Decrement the the number of questions.
        }
    }
    else if (type =="2")   ///If the choice equal 2 then the user will add a Complete question.
    {
        cout<<"Enter number of questions. \n";
        cout<<"Or enter '-1' to return to add question again. \n";
        cin>>num;
        cin.ignore();
        if(num==-1) continue;
        while(num<0)    ///Handle invalid choice.
        {
            cout<<"Enter valid number. \n";
            cout<<"Or enter '-1' to return to add question again. \n";
            cin>>num;
            if(num==-1) break;
        }
        int BREAK=0;

        if(num==-1) continue; ///If the choice equal -1 then will return to add question.

        while (num>0)   ///If the choice is greater than 0 then the user will add a question.
        {
            Complete complete;  ///Declare an object from class Complete.
            complete.AddQuestion(BREAK);   ///Call AddQuestion function from Complete class to add a question.
            if(BREAK) break;
            num--;   ///Decrement the number of question.
        }

    }
    else if (type=="3")   ///If the choice equal 3 then the user will add a TrueFalse question.
    {
        cout<<"enter number of questions \n";
        cout<<"Or enter '-1' to return to add question again\n";
        cin>>num;
        cin.ignore();
        if(num==-1) continue;
        while(num<0)    ///Handle invalid choice.
        {
            cout<<"Enter valid number. \n";
            cout<<"Or enter '-1' to return to add question again. \n";
            cin>>num;
            if(num==-1) break;
        }

        if(num==-1) continue; ///If the choice equal -1 then will return to add question.

        while (num>0)    ///If the choice is greater than 0 then the user will add a question.
        {
            TrueFalse tf;   ///Declare an object of class TrueFalse.
            tf.AddQuestion();    ///Call AddQuestion function from TrueFalse class to add a question.
            num--;     ///Decrement the number of question.
        }
    }

}
}

void Admin::DeleteQuestion ()  ///Function for deleting questions.
{
   while(true)
    {
        string  choice;
        cout<<"Enter the type of question you need to delete. "<<endl;
        cout<<"[1] MCQ. "<<endl<<"[2] Complete. "<<endl<<"[3] True or False. "<<endl;
        cout<<"or enter 'b' to main menu "<<endl;
        cin>>choice;    ///Take the choice from the user.
        if(choice=="b") return ;    ///If the choice equal b then will return to main menu.

        while (choice.size() > 1 || choice > "3" || choice<"1" )    ///Handling invalid input.
        {
            cout<<"Invalid input, try again or enter 'b' to main menu. "<<endl;
            cin>>choice;
            if(choice=="b") return ;
        }
        int BREAK=0;
        if (choice =="1")   ///If the choice equal 1 then the user will delete a MCQ question.
        {
            MCQ mcq;    ///Declare an object of class MCQ.
            mcq.DeleteQuestion(BREAK); ///Call DeleteQuestion function from MCQ class to delete a question.
        }
        else if (choice =="2")      ///If the choice equal 2 then the user will delete a Complete question.
        {
            Complete complete;          ///Declare an object of class Complete.
            complete.DeleteQuestion(BREAK);     ///Call DeleteQuestion function from Complete class to delete a question.

        }
        else if(choice=="3")    ///If the choice equal 3 then the user will delete a TrueFalse question.
        {
            TrueFalse TF;            ///Declare an object of class TrueFalse.
            TF.DeleteQuestion(BREAK);       ///Call DeleteQuestion function from TrueFalse class to delete a question.
        }
        if(BREAK)
        {
            break;
        }
   }
}

void Admin::LoadFromFile()  ///Function for loading from file.
{

    cout<<"Enter file name :\n";
    string filename;

    getline(cin,filename);
    ifstream file;

    file.open(filename);
    if(!file.is_open())     ///Check if the file is exist or not.
    {
        cout<<"Sorry the file is not found\n";
        return ;
    }
    Database::MCQStorage.clear();
    Database::CompleteStorage.clear();
    Database::TFStorage.clear();
    while(!file.eof())      ///Utile the end of the file.
    {
        string type;
        getline(file,type);
        if(type=="MCQ")     ///If the type is MCQ then will read an MCQ question from the file.
        {
            MCQ mcq;
            mcq.readQuestionFromFile(file);     ///Call readQuestionFromFile from MCQ class.
            Database::MCQStorage.push_back(new MCQ(mcq));   ///Push back the lines from the file in the MCQStorage vector by calling copy constructor of class MCQ.
        }
        else if(type=="TF")     ///If the type is TF then will read an TrueFalse question from the file.
        {
            TrueFalse tf;
            tf.readQuestionFromFile(file);   ///Call readQuestionFromFile from TrueFalse class.
            Database::TFStorage.push_back(new TrueFalse(tf));   ///Push back the lines from the file in the TFStorage vector by calling copy constructor of class TrueFalse.
        }
        else if(type=="COMPLETE")   ///If the type is COMPLETE then will read an Complete question from the file.
        {
            Complete cp;
            cp.readQuestionFromFile(file);  ///Call readQuestionFromFile from Complete class.
            Database::CompleteStorage.push_back(new Complete(cp));  ///Push back the lines from the file in the CompleteStorage vector by calling copy constructor of class complete.
        }
    }
}

void Admin::ExecuteChoice(int choice)
{
    if(choice==1)
        switchAccounts();
    else if(choice==2)
    {
        UpdateName();
    }
    else if(choice==3)
    {
        Database::ViewAllUsers();
        cout<<"Press [n] if you want to add a new user or [b] to go back to the main menu.\n";
        char choose;
        cin>>choose;
        cin.ignore();
        if(choose=='n')
        {
            AddNewUser();
        }
    }
    else if(choice==4)
    {
        AddNewUser();
    }
    else if(choice==5)
    {
        PrintQuestions();
    }
    else if(choice==6)
    {
        AddQuestion();
    }
    else if(choice==7)
    {
        LoadFromFile();
    }
    else if(choice==8) exit(0);
}
