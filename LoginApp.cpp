// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: LoginSystem.cpp
// Last Modification Date: 30/4/2022
// Author1 and ID and Group: Karim Mohamed Hassib 20210298
// Author2 and ID and Group: Mohamed Essam Mahmoud 20210346
// Author3 and ID and Group: Hazem Mohamed Waheed 20210115


#include "Login_Library.cpp"


int main(){
    LoadFile();
    bool isLog = false; int countLog = 1;
    string option = "0";
    UserDataBase user;
    set <string> options = {"1","2","3","4"};
    while(stoi(option) != 4){
        cout << "Ahlan yaa user ya habibi.\n"<<
             "Would you like to login or register.\n"
             "1.Login\n"
             "2.Register\n"
             "3.Change Password\n"
             "4.Exit\n";
        cout << "Your Option -->  ";
        cin >> option;
        while(!options.count(option)){
            cout << "Ahlan yaa user ya habibi.\n"<<
                 "Would you like to login or register.\n"
                 "1.Login\n"
                 "2.Register\n"
                 "3.Change Password\n"
                 "4.Exit\n";
            cout << "Your Option -->  ";
            cin >> option;
        }
        switch(stoi(option)){
            case 1:
                countLog = 1;
                do{
                    cout << "\n" << countLog << "st Login.\n";
                    LoginID();
                    LoginPassword();
                    if(UserMap[LogID].Password == EncryptionPass(LogPass)){
                        isLog = true;
                        cout << "\t *** LOGIN Compelet *** \n";
                        cout << "Welcome: " << UserMap[LogID].UserName << "\n\n";
                    }
                    else{
                        isLog = false;
                        cout << "\t *** Login Failed...Try Again. *** \n";
                        countLog+=1;
                    }
                    if(countLog > 3){
                        cout << "\t *** You Have Denied from Access *** \n";
                        break;
                    }
                }while(!isLog);
                break;
            case 2:
                cout << "Ahlan" << endl;
                cin.clear();
                cin.sync();
                UserMap[RegisterID()] = {RegisterEmail(), EncryptionPass(RegisterPassword()), RegisterUserName(), RegisterPhoneNum()};
                cout << "\t\t **** Registration Complete ! **** " <<endl;
                break;
            case 3:
                ChangePassword();
                break;
            case 4:
                ofstream outFile("loginData.txt");
                for(auto pair : UserMap){
                    outFile << pair.first << " " << pair.second.Email << " " << pair.second.Password
                            << " " << pair.second.UserName << " " << pair.second.PhoneNum << endl;
                }
                return 0;
                break;
        }
    }

    return 0;
}


