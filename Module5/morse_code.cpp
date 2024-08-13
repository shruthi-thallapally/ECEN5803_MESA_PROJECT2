/* THIS FILE CONTAINS THE MORSE CODE ENCODER AND DECORDER APPLICATION
*Author- Aysvarya Gopinath, Shruthi Thallapally, Taruni Gelli
*PROJECT 2 MODULE 5
*/


#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// declaration of encode and decode functions
string encode(char c); 
string decode(string morse);

string alphabets = "abcdefghijklmnopqrstuvwxyz";
//morse codes of alphabets
    string const morsecode[] = {".-", "-...", "-.-.", "-..", ".", "..-.","--.", "....", "..", ".---", "-.-", 
    ".-..", "--","-.", "---", ".--.", "--.-",".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    
    
// function to decode the given morse code to its equivalent message 
string decode(string morse)
{
    string output = ""; // holds the decoded data
    string cur_val = "";
    istringstream ss(morse); // parsing the given string into a stream of characters(tokenizing)
    size_t const characters = 26; // total number of alphabets and equivalent morse code

    while(ss >> cur_val) // extracts the current morse code token from the morse string
    {
        size_t index = 0; // traverse through each code from the array
        while(cur_val != morsecode[index] && index < characters) // finding the index of the current morse token 
        {
            ++index;     //if not , incremnent the index and check with next value
        }
          //appending the output with the correct alphabet
        output += 'A' + index; // starting from A and incrementing to the character corresponding to the index
    }
    return output;
}

// function to encode the given message to its equivalent morse code
string encode(char c) 
{    // encoding each character being passed
		  int index = alphabets.find(c); // find the index of each character'c' by comparing it with the "alphabets" string
	    if(index!=-1) // index is obtained 
            return morsecode[index]; // morse code  corresponding to the same index is taken
         else
            return " ";
}

// main function
int main()
{    
  string mess_ip,input = "";
  cout << "Please enter message to be encoded :";
  getline(cin,mess_ip);
  string morse_op="";
  for(int i=0; i<mess_ip.length(); i++) //traversing through each alphabet
       {
         morse_op += encode(mess_ip[i]);   // encoding each character
       }
 cout<<morse_op; // encoded message 
    cout<<"\n";
    cout << "Please enter morse code to be decoded :";
    getline(cin, input);            // gets the morse code 
  cout << decode(input) ;
return 0;
}


