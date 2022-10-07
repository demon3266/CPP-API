#include <iostream>
#include <cstring>
#include<bits/stdc++.h>
using namespace std;
string macA;
int main ()
{

    string cmd = "ifconfig | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}' "; 
    //const char *cmd = str2.c_str();
   
     string filename = "macaddress.txt";

  system((cmd + ">" + filename).c_str());
  
  ifstream myfile ("macaddress.txt");

  if(myfile.is_open()){
  string line;
    getline(myfile,line);
      //cout<<line<<endl;
      macA=line;
    
    myfile.close();
  }
  else{
  cout<<"Unable to open the file";}
    int result = remove("macaddress.txt");
   
    cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<macA<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    return 0; 
}