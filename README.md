# command.h
The command Processor library for c++
=================================================
This piece of code processes text in a command format using standard c++11.

>command arg1 arg2 arg3 -flag1 content1 -flag2 -flag3``

the order in which the args and flags appear doesnt matter as long as it doesnt cause ambiguity.

## methods:
>void process(string s) // processes the string and stores the data inside the object

>bool has_arg(string s) // returns true if the processed command includes the specified argument

>bool has_flag(string s) // returns true if the processed command includes the specified flag

>string get_flag(string s) // returns the content of the specified flag (-flag content) if the flag is a single "" is returned

>bool get_flag(string s, string& e) // searches for the flag s. If found, stores it inside e and returns true. If not, e wont be changed and the fucntion will return false

## fields:

>string command // the command which is essentially the first word in line.

>vector<string> args // a vector of all the captured args

>vector<FLAG_ELEM> flags // a vector of all the captured flags. The FLAG_ELEM class holds the flag and content fields.

## example
```
#include <iostream>
#include "command.h"

using namespace std;

int main(){
  string input;
  cin>>input;
  COMMAND_PROCESSOR cp;
  cp.process(input);
  cout<<cp.command<<endl<<endl;
  for(int i=0;i<cp.argc();i++) cout<<cp.args[i]<<endl;
  cout<<endl;
  for(int i=0;i<cp.flagc();i++) cout<<cp.flags[i].flag<<"\t"<<cp.flags[i].content<<endl;
  return 0;
}
```
 
input:
  
``mycommand arg1 -f fname -t -c 12 -l "C:\Users\A Name With Spaces\Desktop"``
  
output:
  
>mycommand
>  
> arg1
>  
> -f      fname
>  
> -t
>  
> -c      12
>  
> -l      C:\Users\A Name With Spaces\Desktop``
