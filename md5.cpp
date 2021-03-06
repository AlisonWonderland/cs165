// #include"md5lib.h"
// #include <iostream>
// #include <sstream>
// #include <iomanip> 
// #include <string>

// g++ md5.cpp md5lib.cpp -o md5_sample && ./md5_sample

// using namespace std;

// int main() {
//     // unsigned char result[MD5_DIGEST_LENGTH];
//     // const unsigned char* blah = reinterpret_cast<const unsigned char *>("h");
//     // unsigned char* test;
//     // cout << "hello" << endl;
//     // test = MD5(blah, 1, result);
//     // cout << result[1];

//     // std::string str("abcdef");
//     // unsigned char result[MD5_DIGEST_LENGTH];
//     // MD5((unsigned char*)str.c_str(), str.size(), result);

//     // cout << result << endl;
//     // std::ostringstream sout;
//     // sout<<std::hex<<std::setfill ('0');
//     // for(long long c: result)
//     // {
//     //     sout<<std::setw(2)<<(long long)c;
//     // }
//     // cout << sout.str() << endl;
//     // return 0;
// }
#include <iostream>
#include "md5lib.h"
#include <omp.h>
#include <sstream>
#include <bitset>
#include <string.h>
 
using namespace std;

string convertTo16Bytes(string Alt_sum) {
    cout << "16 byte version" << endl;
}

string md5Part1(string password, string salt){
    string Alt_sum = md5(password + salt + password);
    string Alt_sum_16_bytes = convertTo16Bytes(Alt_sum);
    string intermediate = md5(password + "$1$" + salt + Alt_sum.substr(0, 5) + password[0] + "\0\0"); // last two concats are the bits(3 in total)
    for(int i = 0; i < 1000; ++i){
        string tempString = "";
        if(i%2 == 0){tempString = tempString + intermediate; }      //if i is even
        if(i%2 == 1){tempString = tempString + password;}           //if i is odd
        if(i%3 != 0){tempString = tempString + salt;}               //if i is not divisible by 3
        if(i%7 != 0){tempString = tempString + password;}           //if i is not divisible by 7
        if(i%2 == 0){tempString = tempString + password;}           //if i is even
        if(i%2 == 1){tempString = tempString + intermediate;}       //if i is odd

        intermediate = md5(tempString); 
    }
    return intermediate;
}

string getHash(string finalIntermediate) {
    string rearranged = finalIntermediate.substr(22, 2) + finalIntermediate.substr(8, 2) + finalIntermediate.substr(20, 2) +
                        finalIntermediate.substr(10, 2) + finalIntermediate.substr(6, 2) + finalIntermediate.substr(18, 2) + 
                        finalIntermediate.substr(30, 2) + finalIntermediate.substr(4, 2) + finalIntermediate.substr(16, 2) +
                        finalIntermediate.substr(28, 2) + finalIntermediate.substr(2, 2) + finalIntermediate.substr(14, 2) +  
                        finalIntermediate.substr(26, 2) + finalIntermediate.substr(0, 2) + finalIntermediate.substr(12, 2) + 
                        finalIntermediate.substr(24, 2);

    for(int i = 0; i < rearranged.size(); ++i) {
        if(isalpha(rearranged.at(i))) {
            rearranged.at(i) = toupper(rearranged.at(i));
        }
    }


    cout << "Rearranged: " << rearranged << endl; 
    cout << "Last char: " << rearranged.at(rearranged.size() - 1) << endl; 

    // string test = "6B31928914E69F20E3E50B1FC2B8FED6";
    // cout << rearranged << endl;
    // string s = "0x6B31928914E69F20E3E50B1FC2B8FED6";
    // stringstream ss;
    // ss << hex << s;

    // unsigned long long int n;
    // ss >> n;
    // cout << "n: " << n << endl;
    // bitset<128> b(n);
    // // outputs "00000000000000000000000000001010"
    // cout << b.to_string() << endl;
    string binaryNum = "";
    for(int i = 0; i < 32; ++i){
        switch(rearranged[i]){
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

            case 'A':
                binaryNum = binaryNum + "1010";
                break;

            case 'B':
                binaryNum = binaryNum + "1011";
                break;

            case 'C':
                binaryNum = binaryNum + "1100";
                break;

            case 'D':
                binaryNum = binaryNum + "1101";
                break;

            case 'E':
                binaryNum = binaryNum + "1110";
                break;

            case 'F':
                binaryNum = binaryNum + "1111";
                break;
        }
    }

    cout << "the binary num is " << binaryNum << endl;

    return rearranged;
}

void test(string prefix) {
    // cout << prefix << endl;
    if(prefix == "zhgnnd") {
        cout << "SOLVED!!! The solution: " << prefix << endl;
        // exit(0);
    }
    // else {
    //     while(1) {
    //         cout << prefix << endl;
    //     }
    // }
    return;
}

void printAllKLengthParallel(char set[], string prefix, 
                                    int n, int k) 
{ 
      
    // Base case: k is 0, 
    // print prefix 
    if (k == 0) 
    { 
        // cout << (prefix) << endl; 
        test(prefix);
        return; 
    } 
  
    // One by one add all characters  
    // from set and recursively  
    // call for k equals to k-1 
    // omp_set_num_threads(8);
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < n; i++) 
            { 
                string newPrefix; 
                
                // Next character of input added 
                newPrefix = prefix + set[i]; 
                
                // k is decreased, because  
                // we have added a new character 
                printAllKLengthParallel(set, newPrefix, n, k - 1); 
        } 
    }

} 

void printAllKLengthSerial(char set[], string prefix, 
                                    int n, int k) 
{ 
      
    // Base case: k is 0, 
    // print prefix 
    if (k == 0) 
    { 
        // cout << (prefix) << endl; 
        test(prefix);
        return; 
    } 
  
    // One by one add all characters  
    // from set and recursively  
    // call for k equals to k-1 
    
    for (int i = 0; i < n; i++) 
        { 
            string newPrefix; 
            
            // Next character of input added 
            newPrefix = prefix + set[i]; 
            
            // k is decreased, because  
            // we have added a new character 
            printAllKLengthSerial(set, newPrefix, n, k - 1); 
    } 

} 
  
void printAllKLength(char set[], int k,int n) 
{ 
    double start = omp_get_wtime();
    double end = 0.0;

    printAllKLengthParallel(set, "", n, 2);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible remaining 2 characters left(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    printAllKLengthSerial(set, "", n, 2);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible remaining 2 characters left(Serial): " << end << " seconds" << endl;

    start = omp_get_wtime();
    printAllKLengthParallel(set, "", n, 3);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible remaining 3 characters left(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    printAllKLengthSerial(set, "", n, 3);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible remaining 3 characters left(Serial): " << end << " seconds" << endl;

    start = omp_get_wtime();
    printAllKLengthParallel(set, "", n, 4);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible remaining 4 characters left(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    printAllKLengthSerial(set, "", n, 4);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible remaining 4 characters left(Serial): " << end << " seconds" << endl;

    start = omp_get_wtime();
    printAllKLengthParallel(set, "", n, 5);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible remaining 5 characters left(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    printAllKLengthSerial(set, "", n, 5);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible remaining 5 characters left(Serial): " << end << " seconds" << endl;

    start = omp_get_wtime();
    printAllKLengthParallel(set, "", n, 6);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible remaining 6 characters left(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    printAllKLengthSerial(set, "", n, 6);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible remaining 6 characters left(Serial): " << end << " seconds" << endl;

} 
 
int main()
{
    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    // Generate strings here
    printAllKLength(alphabet, 3, 26);

    // for(int i = 0; i < 6; ++i) {
    //     for(int j = 0; i < 26; ++i) {
    //         cout << alphabet[i] << endl;
    //     }
    // }

    // string password = "zhgnnd";
    // string salt = "hfT7jp2q";
    // string finalIntermediate = md5Part1(password, salt);
    // cout << "password: " << password << endl;
    // cout << "MD5 finalIntermediate: " << finalIntermediate << endl;
    // cout << "Actual hash: " << getHash(finalIntermediate) << endl;
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <openssl/md5.h>
 
// const char *string = "The quick brown fox jumped over the lazy dog's back";
 
// int main()
// {
//   int i;
//   unsigned char result[MD5_DIGEST_LENGTH];
 
//   MD5(reinterpret_cast<const unsigned char *>(string), strlen(string), result);
 
//   // output
//   for(i = 0; i < MD5_DIGEST_LENGTH; i++)
//     printf("%02x", result[i]);
//   printf("\n");
 
//   return EXIT_SUCCESS;
// }