#include <iostream>
#include <string.h>
#include <cstdlib>
#include "md5lib.h"
using namespace std;

// **************** TO COMPILE *********************
// g++ lab1.cpp md5lib.cpp -o lab1 && ./lab1

string md5Part1(string password, string salt){
    string Alt_sum = md5(password + salt + password);
    //cout << "The Alt_sum is " << Alt_sum << endl;
    string Alt_sum_string;
    for(int i = 0; i < password.length()*2; i = i +2){
        unsigned char temp;
        string keeper = "0x";
        keeper +=  Alt_sum[i];
        keeper += Alt_sum[i+1];

        // cout << "the keeper is " << keeper << endl;

        temp = stoul(keeper, nullptr, 16);

        // int test1 = temp;

        // cout << "the char is " << temp << endl;

        // cout << "the number is " << test1 << endl;

        Alt_sum_string += temp;
        

    }
    char Nullcharacter = 0;

   
    string add_on = "";
    int i = password.length();
    while(i != 0){
        if(i%2 == 0){
            add_on += password[0];
        }
        else{
            add_on += '\0';
        }
        i = i/2;
    }

    // cout << "the string of add on is " << add_on << "and the length is " << add_on.length()<< endl;

    //cout <<  " and the length is " << Alt_sum_string.length() << endl;

    // string test2 = password + "$1$" + salt + Alt_sum.substr(0, 6) + Alt_sum_string + password[0] + '\0' + '\0';
    // cout <<  "and the length is " << test2.length() << endl;

    string intermediate = md5(password + "$1$" + salt + Alt_sum_string + add_on);

    // cout << "length of inter0 is : " << intermediate.length() << endl;

    // cout << "This is intermediate before loop " << intermediate << endl;        //This is working above this line with the value ed7a5307588e49ed3a2777d926d62f96
    for(int i = 0; i < 1000; i++){

        string intermediate_16 ="";
        for(int z = 0; z < 32; z = z +2){
            unsigned char temp;
            string keeper = "0x";
            keeper +=  intermediate[z];
            keeper += intermediate[z+1];

            //cout << "the keeper is " << keeper << endl;

            temp = stoul(keeper, nullptr, 16);

        // int test1 = temp;

        // cout << "the char is " << temp << endl;

        // cout << "the number is " << test1 << endl;

            intermediate_16 += temp;
        

        }


        

        string tempString = "";
        if(i%2 == 0){tempString = tempString + intermediate_16; }      //if i is even
        if(i%2 == 1){tempString = tempString + password;}           //if i is odd
        if(i%3 != 0){tempString = tempString + salt;}               //if i is not divisible by 3
        if(i%7 != 0){tempString = tempString + password;}           //if i is not divisible by 7
        if(i%2 == 0){tempString = tempString + password;}           //if i is even
        if(i%2 == 1){tempString = tempString + intermediate_16;}       //if i is odd


        intermediate = md5(tempString); 
        // if(i == 0){
        //     //cout << "The string in the first loop is " << tempString << endl;
        //     //cout << "the first intermediate is " << intermediate_16 << endl;
        // }
        // if(i == 999){
        //     cout << "The 1000 inter should be :" << md5(tempString) << endl;
        // }
    }
    // cout << "This is intermediate after loop " << intermediate << endl;         //the output is ff202f2e9b6ac6e495570536fc89fd2a
    return intermediate;
}

string md5Part2(string intermediate){
    string newIntermediate ="";
    //11 4 10 5 3 9 15 2 8 14 1 7 13 0 6 12
    newIntermediate +=  intermediate.substr(22, 2) + intermediate.substr(8, 2) + intermediate.substr(20, 2) +
                        intermediate.substr(10, 2) + intermediate.substr(6, 2) + intermediate.substr(18, 2) + 
                        intermediate.substr(30, 2) + intermediate.substr(4, 2) + intermediate.substr(16, 2) +
                        intermediate.substr(28, 2) + intermediate.substr(2, 2) + intermediate.substr(14, 2) +  
                        intermediate.substr(26, 2) + intermediate.substr(0, 2) + intermediate.substr(12, 2) + 
                        intermediate.substr(24, 2);

    //12,6,0,13,7,1,14,8,2,15,9,3,5,10,4,11
    // newIntermediate +=  intermediate.substr(24, 2) + intermediate.substr(12, 2) + intermediate.substr(0, 2) +
    //                     intermediate.substr(26, 2) + intermediate.substr(14, 2) + intermediate.substr(2, 2) + 
    //                     intermediate.substr(28, 2) + intermediate.substr(16, 2) + intermediate.substr(4, 2) +
    //                     intermediate.substr(30, 2) + intermediate.substr(18, 2) + intermediate.substr(6, 2) +  
    //                     intermediate.substr(10, 2) + intermediate.substr(20, 2) + intermediate.substr(8, 2) + 
    //                     intermediate.substr(22, 2);
    
    // cout << "the old intermediate is " << intermediate << endl;
    // cout << "the new intermediate is " << newIntermediate << endl;
    
    string binaryNum = "";
    for(int i = 0; i < 32; ++i){
        switch(newIntermediate[i]){
            case '0':
                binaryNum = binaryNum + "0000";
                break;

            case '1':
                binaryNum = binaryNum + "0001";
                break;

            case '2':
                binaryNum = binaryNum + "0010";
                break;

            case '3':
                binaryNum = binaryNum + "0011";
                break;

            case '4':
                binaryNum = binaryNum + "0100";
                break;

            case '5':
                binaryNum = binaryNum + "0101";
                break;

            case '6':
                binaryNum = binaryNum + "0110";
                break;

            case '7':
                binaryNum = binaryNum + "0111";
                break;

            case '8':
                binaryNum = binaryNum + "1000";
                break;

            case '9':
                binaryNum = binaryNum + "1001";
                break;

            case 'a':
                binaryNum = binaryNum + "1010";
                break;

            case 'b':
                binaryNum = binaryNum + "1011";
                break;

            case 'c':
                binaryNum = binaryNum + "1100";
                break;

            case 'd':
                binaryNum = binaryNum + "1101";
                break;

            case 'e':
                binaryNum = binaryNum + "1110";
                break;

            case 'f':
                binaryNum = binaryNum + "1111";
                break;
        }
    }

    // cout << "the binary num is " << binaryNum << endl;

    


    string cryptBase64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int position = 122;              //init position
    string finalHashKey = "";
    while(position > 0){
        char tempKey =  cryptBase64[(binaryNum[position] == '1'?32:0) + (binaryNum[position+1] == '1'?16:0) + (binaryNum[position+2] == '1'?8:0) + (binaryNum[position+3] == '1'?4:0) + (binaryNum[position+4] == '1'?2:0) + (binaryNum[position+5] == '1'?1:0)] ;
        //cout << "the temp key is " << tempKey << endl;
        //cout << "the first position number is " << (binaryNum[position] == '1'?32:0) << endl;  
        finalHashKey += tempKey;
        position-=6;
    }

    finalHashKey += cryptBase64[(binaryNum[0] == '1'?2:0) + (binaryNum[position+5] == '1'?1:0)] ;
    //cout << "the final hash is: " << 0xff << endl;
    return finalHashKey;
}

void testPassword(string generatedPassword) {
    // UNCOMMENT THIS CODE TO ACTUALLY CRACK PASSWORD. ADD our HASHED PASSWORD

    // string ourHashedPassword = "";
    // string salt = "4fTgjp6q";
    
    // if(ourHashedPassword == md5Part2(md5Part1(generatedPassword, salt))) {
    //     cout << "MATCH FOUND: " << generatedPassword << endl;
    //     exit(0); // no need to continue
    // }


    // *** TESTS. DELETED LATER ***

    // "a" hashed
    string testHashedPassword1 = "pZg4uQ9ur9356fohTDh9u/";
    // "ab" hased
    string testHashedPassword2 = "mJpiQ6c5/hc6giQA.QSq.1";
    // "abc" hased
    string testHashedPassword3 = "4EuZizSo6kunm/d3f7pJg1";
    // "abcd" hashed
    string testHashedPassword4 = "HtyOYVTSrJkX3GxpxXJY50";
    string salt = "hfT7jp2q"; // salt used for previous four

    string hashedGeneratedPassword = md5Part2(md5Part1(generatedPassword, salt));

    if(testHashedPassword1 == hashedGeneratedPassword) {
        cout << "MATCH FOUND FOR FIRST PASSWORD(a): " << generatedPassword << endl;
        cout << "---Hash for first password: " << testHashedPassword1 << " and hash for generated password: " 
            << hashedGeneratedPassword << " and plaintext generated password: " <<  generatedPassword << endl;
    }

    else if(testHashedPassword2 == hashedGeneratedPassword) {
        cout << "MATCH FOUND FOR SECOND PASSWORD(ab): " << generatedPassword << endl;
        cout << "---Hash for first password: " << testHashedPassword2 << " and hash for generated password: " 
            << hashedGeneratedPassword << " and plaintext generated password: " <<  generatedPassword << endl;
    }

    else if(testHashedPassword3 == hashedGeneratedPassword) {
        cout << "MATCH FOUND FOR THIRD PASSWORD(abc): " << generatedPassword << endl;
        cout << "---Hash for first password: " << testHashedPassword3 << " and hash for generated password: " 
            << hashedGeneratedPassword << " and plaintext generated password: " <<  generatedPassword << endl;

    }

    else if(testHashedPassword4 == hashedGeneratedPassword) {
        cout << "MATCH FOUND FOR FOURTH PASSWORD(abcd): " << generatedPassword << endl;
        cout << "---Hash for first password: " << testHashedPassword4 << " and hash for generated password: " 
            << hashedGeneratedPassword << " and plaintext generated password: " <<  generatedPassword << endl;

    }

    return;
}

// prefix is basically the previous string of characters and will have more
// characters added to it until there are no characters left to add.
// This function produces strings of only one length(the initial charsLeft value).
void generatePasswordsInSerial(char alphabet[], string prefix, 
                                    int alphabet_size, int charsLeft) 
{ 
      
    // Base case: charsLeft is 0, 
    // test password when no characters are left to add
    if (charsLeft == 0) 
    { 
        testPassword(prefix);
        return; 
    } 
  
    // One by one add all characters  
    // from alphabet and recursively  
    // call for charsLeft equals to charsLeft-1 
    for (int i = 0; i < alphabet_size; i++) 
        { 
            string newPrefix; 
            
            // Next character of input added 
            newPrefix = prefix + alphabet[i]; 
            
            // charsLeft is decreased, because  
            // we have added a new character 
            generatePasswordsInSerial(alphabet, newPrefix, alphabet_size, charsLeft - 1); 
    } 
}

// TESTS for time duration
void generatePasswords(char alphabet[], int alphabet_size) 
{ 
    // **** OUR CODE WOULD LOOK LIKE THIS IN THIS FUNCTION ****
    generatePasswordsInSerial(alphabet, "", alphabet_size, 1);
    generatePasswordsInSerial(alphabet, "", alphabet_size, 2);
    generatePasswordsInSerial(alphabet, "", alphabet_size, 3);
    generatePasswordsInSerial(alphabet, "", alphabet_size, 4);
    generatePasswordsInSerial(alphabet, "", alphabet_size, 5);
    generatePasswordsInSerial(alphabet, "", alphabet_size, 6);
} 

int main()
{

    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    // Generate strings here
    generatePasswords(alphabet, 26);

    return 0;
}