#include<iostream>
#include<fstream>
#include<regex>
#include<map>
#include<set>
#include <conio.h>
using namespace std;
fstream RegisterFile ("loginData.txt",ios::in|ios::app);
const int ENTER = 13, SPACE = 32, BACKSPACE = 8;
string LogID; string LogPass;

struct UserDataBase{
    string Email;
    string Password;
    string UserName;
    string PhoneNum;
};

map < string,UserDataBase > UserMap = {};


void LoadFile();
void LoginID();
void LoginPassword();
void ChangePassword();

string RegisterUserName();
string RegisterID();
string RegisterEmail();
string RegisterPassword();
string RegisterPhoneNum();

int CountNewLineFile();
ostream& operator << (ostream& out, UserDataBase);
string EncryptionPass(string text);