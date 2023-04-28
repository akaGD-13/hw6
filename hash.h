#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctype.h>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5];
        int size = k.size();
        unsigned long long s[28];
        for (int i=0; i < 28 - size; i++){
            s[i] = 0;
        }
        for (size_t i=0; i < size; i++){
            s[28 - size + i] = letterDigitToNumber(k[i]);
        }
        
        w[0] = ((s[0]*36 + s[1])*36 + s[2])*36 + s[3];
        w[1] = ((((s[4]*36 + s[5])*36 + s[6])*36 + s[7])*36 + s[8])* 36 + s[9];
        w[2] = ((((s[10]*36 + s[11])*36 + s[12])*36 + s[13])*36 + s[14])* 36 + s[15];
        w[3] = ((((s[16]*36 + s[17])*36 + s[18])*36 + s[19])*36 + s[20])* 36 + s[21];
        w[4] = ((((s[22]*36 + s[23])*36 + s[24])*36 + s[25])*36 + s[26])* 36 + s[27];

        unsigned long long h;
        h = rValues[0]*w[0]+rValues[1]*w[1]+rValues[2]*w[2]+rValues[3]*w[3]+rValues[4]*w[4];
        
        return h;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = tolower(letter);
        std::string x = "abcdefghijklmnopqrstuvwxyz0123456789";
        HASH_INDEX_T value = 0;
        for (auto i: x){
            if (i == letter){
                return value;
            }
            else{
                value++;
            }
        }
        return -1;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
