#include "LoginAppHeader.h"


void LoadFile(){
    string UserSentence, contentID;
    UserDataBase user;
    int count_User = CountNewLineFile();
    int j;
    RegisterFile.clear();
    RegisterFile.seekg(0);

    for(int i = 0; i < count_User; i++){
        getline(RegisterFile,UserSentence,'\n');

        for(j = 0; j < UserSentence.length(); j++){
            if(UserSentence[j] != ' ')
                contentID += UserSentence[j];
            else{
                break;
            }
        }
        for(j+=1; j < UserSentence.length(); j++){
            if(UserSentence[j] != ' ')
                user.Email += UserSentence[j];
            else
                break;
        }
        for(j+=1; j < UserSentence.length(); j++){
            if(UserSentence[j] != ' ')
                user.Password += UserSentence[j];
            else
                break;
        }
        for(j+=1; j < UserSentence.length(); j++){
            if(UserSentence[j] != ' ')
                user.UserName += UserSentence[j];
            else
                break;
        }
        for(j+=1; j < UserSentence.length(); j++){
            if(UserSentence[j] != ' ')
                user.PhoneNum += UserSentence[j];
            else
                break;
        }
        UserMap[contentID] = {user.Email,user.Password,user.UserName,user.PhoneNum};
        contentID = "";
        user.Email = "";
        user.Password = "";
        user.UserName = "";
        user.PhoneNum = "";

    }
}

void LoginID(){
    bool isFound = false;
    cout << "Enter Your ID: ";
    cin >> LogID;
    for(auto pair : UserMap){
        if(LogID == pair.first)
            isFound = true;
    }
    while(!isFound){
        cout << "\t *** No ID Match.. Try Again! ***\n";
        cout << "Enter Your ID: ";
        cin >> LogID;
        for(auto pair : UserMap){
            if(LogID == pair.first)
                isFound = true;
        }
    }

}

void LoginPassword(){
    string passwordStr;
    char password[100]; int i;
    cout << "Enter Your Password: ";
    for(i = 0; i < 100; i++){
        password[i] = getch();
        if(password[i] == ENTER || password[i] == SPACE)
            break;
        else if (password[i] == BACKSPACE){
            cout << "\b \b";
            if(passwordStr.empty())
                continue;
            else
                passwordStr.pop_back();
        }
        else{
            passwordStr += password[i];
            cout << "*";
        }
    }
    cout << "\n_________________________________________________" <<endl;

    LogPass = passwordStr;
}

void ChangePassword(){
    string passwordStr;
    char password[100]; int i;
    LoginID();
    regex ValidPass ("(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[#?!@$%^&*-]).{8,}");
    do{
        passwordStr = "";
        cout << "Enter Your OLD Password: ";
        for(i = 0; i < 100; i++){
            password[i] = getch();
            if(password[i] == ENTER || password[i] == SPACE)
                break;
            else if (password[i] == BACKSPACE){
                cout << "\b \b";
                if(passwordStr.size() == 0)
                    continue;
                else
                    passwordStr.pop_back();
            }
            else{
                passwordStr += password[i];
                cout << "*";
            }
        }
        if(UserMap[LogID].Password != EncryptionPass(passwordStr)){
            cout << "\t\n *** Password Doesn't Match...Try Again *** \n";
        }
    }while(UserMap[LogID].Password != EncryptionPass(passwordStr));
    passwordStr = RegisterPassword();

    UserMap[LogID].Password = EncryptionPass(passwordStr);
}


string RegisterUserName(){
    string userName; bool isValid; bool isFound = false;
    regex ValidUserName (R"(\w+[\.*\w*#*\w*]*)");
    do{
        cout << "\nNOTE!\n\t"<<
             " *** No Spaces Only Alphabet,Special Character,Number is Avaliable. *** \n";

        cout << "Enter UserName: ";
        getline(cin,userName);
        isValid = regex_match(userName,ValidUserName);
        if(isValid == false)
            cout << "Invalid UserName..Try again !!\n";
    }while(!isValid);

    for(auto pair:UserMap){
        if(userName == pair.second.UserName){
            isFound = true;
        }
    }

    if(isFound == true){
        do{
            cout << "\t *** UserName has Already been Taken *** \n" <<
                 "Pls Enter a New One. \n";
            isValid = false;
            while(!isValid){

                cout << "Enter UserName: ";
                getline(cin,userName);
                isValid = regex_match(userName,ValidUserName);
                if(isValid == false)
                    cout << "Invalid UserName..Try again !!\n";
            }
            for(auto pair:UserMap){
                if(userName == pair.second.UserName){
                    isFound = true;
                    break;
                }
                else
                    isFound = false;
            }
        }while(isFound == true);
    }
    cout << "_________________________________________________" <<endl;
    return userName;
}

string RegisterID(){
    string ID; bool isValid = true, isFound = false;
    regex ValidID ("([0-9]){8}");
    do{
        cout << "\nNOTE!\n\t"<<
             " *** No Spaces Only 8 Digits Number is Avaliable. *** \n";
        cout << "Enter ID: ";
        getline(cin,ID);
        isValid = regex_match(ID,ValidID);
        if(!isValid)
            cout << "Invalid ID..Try again !!\n";
    }while(!isValid);

    for(auto pair:UserMap){
        if(ID == pair.first)
            isFound = true;
    }
    if(isFound){
        do{
            cout << "\t *** ID has Already been Taken *** \n" <<
                 "Pls Enter a New One. \n";
            isValid = false;
            while(!isValid){
                cout << "Enter ID: ";
                getline(cin,ID);
                isValid = regex_match(ID,ValidID);
                if(!isValid)
                    cout << "Invalid ID..Try again !!\n";
            }
            for(auto pair:UserMap){
                if(ID == pair.first){
                    isFound = true;
                    break;
                }
                else
                    isFound = false;
            }
        }while(isFound);
    }
    cout << "_________________________________________________" <<endl;
    return ID;
}

string RegisterEmail(){
    string email; bool isValid = true, isFound = false;
    regex ValidEmail(R"([\w]+(.|_)?(\w*([.]?\w+))@(\w+)(.(\w+))+)");

    do{
        cout << "\nNOTE!\n\t"<<
             " *** PLS Follow Guidelines Syntax for Emails. *** \n";
        cout << "Enter Email: ";
        getline(cin,email);
        isValid = regex_match(email,ValidEmail);
        if(!isValid)
            cout << "Invalid Email..Try again !!\n";

    }while(!isValid);
    for(auto pair : UserMap){
        if(email == pair.second.Email)
            isFound = true;
    }
    if(isFound){
        do{
            cout << "\t *** Email has Already been Taken *** \n" <<
                 "Pls Enter a New One. \n";
            isValid = false;
            while(!isValid){

                cout << "Enter Email: ";
                getline(cin,email);
                isValid = regex_match(email,ValidEmail);
                if(!isValid)
                    cout << "Invalid Email..Try again !!\n";
            }
            for(auto pair:UserMap){
                if(email == pair.second.Email){
                    isFound = true;
                    break;
                }
                else
                    isFound = false;
            }
        }while(isFound);
    }
    cout << "_________________________________________________" <<endl;
    return email;

}

string RegisterPassword(){
    string passwordStr; bool isValid;
    string passwordStr2;
    char password[100]; int i,j;

    regex ValidPass ("(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[#?!@$%^&*-]).{8,}");
    do{
        passwordStr2 = ""; passwordStr = "";
        do{
            passwordStr = "";
            cout << "\nNOTE!\n\t"<<
                 " *** Password Must have Both Characters and Numbers. *** \n\t" <<
                 " *** At Least 6 character is Avaliable. *** \n";

            cout << "Enter Password: ";
            for(i = 0; i < 100; i++){
                password[i] = getch();
                if(password[i] == ENTER || password[i] == SPACE)
                    break;
                else if (password[i] == BACKSPACE){
                    cout << "\b \b";
                    if(passwordStr.size() == 0)
                        continue;
                    else
                        passwordStr.pop_back();
                }
                else{
                    passwordStr += password[i];
                    cout << "*";
                }
            }
            isValid = regex_match(passwordStr,ValidPass);
            if(!isValid){
                isValid = false;
                cout << "\nInvalid Password..Try again !!\n";
            }
        }while(!isValid);
        cout << "\nRepeat Password: ";
        for(i = 0; i < 100; i++){
            password[i] = getch();
            if(password[i] == ENTER || password[i] == SPACE)
                break;
            else if (password[i] == BACKSPACE){
                cout << "\b \b";
                if(passwordStr2.size() == 0)
                    continue;
                else
                    passwordStr2.pop_back();
            }
            else{
                passwordStr2 += password[i];
                cout << "*";
            }
        }
        if(passwordStr != passwordStr2){
            cout << "\n\t *** Password Doesn't Match with Reapeted one *** \n";
        }
    }while(passwordStr != passwordStr2);
    cout << "\n_________________________________________________" <<endl;
    return passwordStr;
}

string RegisterPhoneNum(){
    string phoneNum; bool isValid = true;
    regex ValidPhoneNum ("[01]{2,2}[0125]{1,1}[0-9]{8,8}");
    do{
        cout << "NOTE!\n\t"<<
             " *** Phone Number Must Start with (010),(011),(012) or(015). *** \n\t\t"<<
             " *** Number Must be 11 Digits ONLY. ***\n";
        cout << "Enter PhoneNumber: ";
        getline(cin,phoneNum);
        isValid = regex_match(phoneNum,ValidPhoneNum);
        if(!isValid)
            cout << "Invalid PhoneNumber..Try again !!\n";
    }while(!isValid);
    cout << "_________________________________________________" <<endl;
    return phoneNum;
}


//_______________________________________________

int CountNewLineFile(){

    int counter = 0; string line;

    while(RegisterFile.peek() != EOF){
        getline(RegisterFile,line,'\n');
        counter += 1;
    }
    return counter;

}

ostream& operator << (ostream& out, UserDataBase User){
    out << User.Email << endl;
    out << User.Password << endl;
    out << User.UserName << endl;
    out << User.PhoneNum << endl;
}

string EncryptionPass(string text){
    int row = 0, col = 0;
    string encText;
    char matrix[3][(text.length())];
    bool isDown = false;

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < text.length(); j++)
            matrix[i][j] = '*';

    for(int i = 0; i < text.length();i++){
        if(row == 0 || row == 2){
            isDown = !isDown;
        }
        matrix[row][col++] = text[i];
        isDown?row++:row--;
    }

    for (int i = 0; i < 3; i++){
        for(int j = 0; j < text.length();j++){
            if(matrix[i][j]!= '*'){
                encText.push_back(matrix[i][j]);
            }
        }
    }
    return encText;
}
//______________________________________________
