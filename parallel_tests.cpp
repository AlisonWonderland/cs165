#include <iostream>
#include <omp.h>
#include <string.h>

using namespace std;

// **************** TO COMPILE *********************
// g++ parallel_tests.cpp -fopenmp -o parallel_tests && ./parallel_tests


// Here the password would be recieved and then be sent to be hashed and compared.
// For now just seeing if a certain password is generated with the first if statement.
void testPassword(string password) {
    if(password == "a") {
        cout << "DONE!! Generated: " << password << endl;
    }

    // ourHashedPassword is the hashed password for the team
    // if(ourHashedPassword == md5Part2(password)) {
        // exit(0); Could close the program when the hash is done 
    // }
    return;
}


// Parallelized version.
// !!!! SLOWER THAN SERIAL !!!!!

// ************* PREFIX EXPLANATION *****************
// prefix is basically the previous string of characters and will have more
// characters added to it until there are no characters left to add.
void generatePasswordsInParallel(char alphabet[], string prefix, 
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
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < alphabet_size; i++) 
            { 
                string newPrefix; 
                
                // Next character of input added 
                newPrefix = prefix + alphabet[i]; 
                
                // charsLeft is decreased, because  
                // we have added a new character 
                generatePasswordsInParallel(alphabet, newPrefix, alphabet_size, charsLeft - 1); 
        } 
    }

} 


// Same logic as the parallel one only serial
void generatePasswordsInSerial(char alphabet[], string prefix, 
                                    int n, int k) 
{ 
      
    // Base case: k is 0, 
    // print prefix 
    if (k == 0) 
    { 
        // cout << (prefix) << endl; 
        testPassword(prefix);
        return; 
    } 
  
    // One by one add all characters  
    // from alphabet and recursively  
    // call for k equals to k-1 
    
    for (int i = 0; i < n; i++) 
        { 
            string newPrefix; 
            
            // Next character of input added 
            newPrefix = prefix + alphabet[i]; 
            
            // k is decreased, because  
            // we have added a new character 
            generatePasswordsInSerial(alphabet, newPrefix, n, k - 1); 
    } 

} 

// TESTS for time duration
void generatePasswords(char alphabet[], int k,int n) 
{ 
    // **** OUR CODE WOULD LOOK LIKE THIS IN THIS FUNCTION ****
    // generatePasswordsInSerial(alphabet, "", n, 1);
    // generatePasswordsInSerial(alphabet, "", n, 2);
    // generatePasswordsInSerial(alphabet, "", n, 3);
    // generatePasswordsInSerial(alphabet, "", n, 4);
    // generatePasswordsInSerial(alphabet, "", n, 5);
    // generatePasswordsInSerial(alphabet, "", n, 6);

    // **** TESTS WITH TIME ****

    double start = omp_get_wtime();
    double end = 0.0;

    generatePasswordsInParallel(alphabet, "", n, 1);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 1 character strings(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    generatePasswordsInSerial(alphabet, "", n, 1);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 1 character strings(Serial): " << end << " seconds" << endl;


    generatePasswordsInParallel(alphabet, "", n, 2);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 2 character strings(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    generatePasswordsInSerial(alphabet, "", n, 2);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 2 character strings(Serial): " << end << " seconds" << endl;

    start = omp_get_wtime();
    generatePasswordsInParallel(alphabet, "", n, 3);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 3 character strings(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    generatePasswordsInSerial(alphabet, "", n, 3);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 3 character strings(Serial): " << end << " seconds" << endl;

    start = omp_get_wtime();
    generatePasswordsInParallel(alphabet, "", n, 4);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 4 character strings(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    generatePasswordsInSerial(alphabet, "", n, 4);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 4 character strings(Serial): " << end << " seconds" << endl;

    start = omp_get_wtime();
    generatePasswordsInParallel(alphabet, "", n, 5);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 5 character strings(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    generatePasswordsInSerial(alphabet, "", n, 5);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 5 character strings(Serial): " << end << " seconds" << endl;

    start = omp_get_wtime();
    generatePasswordsInParallel(alphabet, "", n, 6);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 6 character strings(Parallel): " << end << " seconds" << endl;

    start = omp_get_wtime();
    generatePasswordsInSerial(alphabet, "", n, 6);
    end = omp_get_wtime() - start;
    cout << "Time it took to print out all possible 6 character strings(Serial): " << end << " seconds" << endl;
} 

void testParallel() {
    double start = 0.0;
    double end = 0.0;
    int x = 0;

    omp_set_num_threads(2);
    start = omp_get_wtime();
    #pragma omp parallel for
    for(int i = 0; i < 1000000000; ++i) {
        x += 1;
        if(x == 10000) {
            x = 0;
        }
    }
    end = omp_get_wtime() - start;
    cout << "Time for parallel calculation: " << end << " seconds" << endl;

} 

void testSerial() {
    int x = 0;

    for(int i = 0; i < 1000000000; ++i) {
        x += 1;
        if(x == 10000) {
            x = 0;
        }
    }
} 

int main()
{
    // **** PARALLEL AND SERIAL CALCULATION COMPARISONS *****
    double start = 0.0;
    double end = 0.0;

    testParallel();


    start = omp_get_wtime();
    testSerial();
    end = omp_get_wtime() - start;
    cout << "Time for serial calculation: " << end << " seconds" << endl;

    // **** STRING TESTS ****

    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    // Generate strings here
    generatePasswords(alphabet, 3, 26);

    return 0;
}