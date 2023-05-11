#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <string>
// #include <climits>
#include <limits>
#include <math.h>
// #include <algorithm>
#include <stdio.h>
#include <numeric>
#include <bits/stdc++.h>
#include <list>
#define MAX 100000
// #include <boost/multiprecision/cpp_int.hpp>

// using namespace boost::multiprecision;

using namespace std;

class publickKeyClass
{
public:
    int64_t e;
    int64_t n;
};

class privateKeyClass
{
public:
    int64_t d;
    int64_t n;
};

publickKeyClass publickKey;
privateKeyClass privateKey;

int64_t p = 58043;
int64_t q = 58237;

int64_t powermod(int64_t base, int64_t exponent, int64_t modulus)
{
    if (base < 1 || exponent < 0 || modulus < 1)
        return -1;

    int64_t result = 1;
    while (exponent > 0)
    {
        if ((exponent % 2) == 1)
        {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent = floor(exponent / 2);
    }
    return result;
    // int value = 1;
    // while (exponent > 0)
    // {
    //     value *= base;
    //     value %= modulus;
    //     exponent--;
    // }
    // return value;
}

// calculate phi
void CalculateTheValueOfPhi()
{

    if (p <= 2 & p == q | p == 0 | q == 0)
        return;

    int64_t n = p * q;

    publickKey.n = n;
    privateKey.n = n;

    int64_t phi = (p - 1) * (q - 1);

    for (int64_t index = 2; index < phi; index++)
    {
        if (gcd(index, n) == 1 && gcd(index, phi) == 1)
        {
            publickKey.e = index;
            break;
        }
    }

    double f3;
    double d = 0.1;

    int64_t k = 2;

    while (modf(d, &f3) != 0)
    {
        double step1 = 1 + (k * phi);
        double ass = step1 / publickKey.e;
        d = ass;
        k++;
    }
    privateKey.d = d;

    cout << "public key:{" + to_string(publickKey.e) + "," + to_string(publickKey.n) + "}\n";
    cout << "private key:{" + to_string(privateKey.d) + "," + to_string(privateKey.n) + "}\n";
}

std::vector<int> chars;
std::vector<int64_t> encryptedCharsList;
std::vector<int64_t> decryptedCharsList;

// creating a char code
void asciiConstructor(string str)
{
    cout << "\n <----- next step (finding ascii number) -----> \n";
    for (int i = 0; i < str.size(); ++i)
    {
        int ascii = str[i];
        cout << "ascii:" + to_string(ascii) + "\n";

        chars.push_back(ascii);
    }
}

void encryptingChars()
{
    cout << "\n <----- next step (encrytpting chars) -----> \n";

    cout << "starting encrypt \n please wait.. \n\n";
    for (auto ascii : chars)
    {

        double assciiChar = 1;
        for (double i = 0; i < publickKey.e; i++)
        {
            assciiChar *= ascii - 96;
            assciiChar = fmod(assciiChar, publickKey.n);
        }

        // int64_t asciiChar = powermod(ascii, publickKey.e, publickKey.n);

        encryptedCharsList.push_back(assciiChar);
    }
    cout << "list item:\n";
    for (auto encryptChar : encryptedCharsList)
    {
        cout << to_string(encryptChar) + "\n";
    }
    cout << "done \n";
}

void decryptingChars()
{
    cout << "\n <----- next step (decrypting chars) -----> \n";

    cout << "starting decrypt \n please wait.. \n";
    for (int64_t encryptChar : encryptedCharsList)
    {

        cout << "encryptChar item:" + to_string(encryptChar) + "\n";

        int64_t asciiChar = 1;

        for (int64_t i = 0; i < privateKey.d; i++)
        {

            asciiChar *= encryptChar;
            asciiChar = fmod(asciiChar, publickKey.n);
        }

        decryptedCharsList.push_back(asciiChar + 96);
    }
    cout << "done \n";

    cout << "forach in my decrypt list: \n";
    for (auto myChar : decryptedCharsList)
    {
        cout << to_string(myChar) + "\n";
    }
}

void convertingAsciiCodeToChar()
{
    cout << "\n <----- next step (converting ascii to the char) -----> \n";
    string text = "";
    for (auto myChar : decryptedCharsList)
    {
        text += char(myChar);
    }
    cout << "\n this is a your text after the decrypted:" + text + "\n";
}

std::vector<int64_t> breakEncryptedCharsList;

bool checkBreakPrimeNum(string p, string q, string orgText)
{

    int64_t intNum1 = (int64_t)stod(p);
    int64_t intNum2 = (int64_t)stod(q);

    int64_t n = intNum1 * intNum2;

    int64_t phi = (intNum1 - 1) * (intNum2 - 1);

    int64_t e = 1;
    int64_t itemIndex = 0;
    for (int64_t itemIndex = 0; itemIndex < phi; itemIndex++)
    {
        if (gcd(itemIndex, n) == 1 && gcd(itemIndex, phi) == 1 && itemIndex != 1)
        {
            e = itemIndex;
            break;
        }
    }

    double f3;
    double d = 0.1;

    int64_t k = 2;

    while (modf(d, &f3) != 0)
    {
        double step1 = 1 + (k * phi);
        double ass = step1 / e;
        d = ass;
        k++;
    }
    d = d;

    for (auto encryptChar : encryptedCharsList)
    {
        // int64_t asciiChar = powermod(encryptChar, d, n);
        int64_t asciiChar = 1;

        for (int64_t i = 0; i < d; i++)
        {

            asciiChar *= encryptChar;
            asciiChar = fmod(asciiChar, n);
        }

        breakEncryptedCharsList.push_back(asciiChar+96);

        string text = "";

        for (auto myChar : breakEncryptedCharsList)
        {
            text += char(myChar);
        }

        if (text == orgText)
        {
            cout << "key:{ \n private.d is:" + to_string((int)d) + "\n private.n is:" + to_string(n) + "\n}\n";
            return true;
        }
    }

    breakEncryptedCharsList.clear();
    return false;
}

void breakTheAlgorithm()
{

    string num1;
    string num2;
    ifstream primeNumbersFile1;
    ifstream primeNumLength4("primeNumLength4.txt");
    ifstream primeNumLength5("primeNumLength5.txt");
    ifstream primeNumLength6("primeNumLength6.txt");

    bool findKey = false;

    cout << "\n <----- next step (break the algorithm) -----> \n";

    string orgText = "";
    for (auto myChar : decryptedCharsList)
    {
        orgText += char(myChar);
    }
    cout << "\n this is a orgText:" + orgText + "\n";
    cout << "starting break \n please wait to finding a keys.. \n\n";

    // break length 4
    if (primeNumLength4.is_open())
    {
        while (getline(primeNumLength4, num1))
        {
            ifstream primeBaseLength4("primeBaseLength4.txt");
            while (getline(primeBaseLength4, num2))
            {
                if (checkBreakPrimeNum(num1, num2, orgText))
                {
                    return;
                    primeNumLength4.close();
                    primeBaseLength4.close();
                }
            }
        }
        primeNumLength4.close();
    }

    // break length 5
    if (primeNumLength5.is_open() && !findKey)
    {
        while (getline(primeNumLength5, num1))
        {
            ifstream primeBaseLength5("primeBaseLength5.txt");
            while (getline(primeBaseLength5, num2))
            {
                if (checkBreakPrimeNum(num1, num2, orgText))
                {
                    return;
                    primeNumLength5.close();
                    primeBaseLength5.close();
                }
            }
        }
        primeNumLength5.close();
    }

    // break length 6
    if (primeNumLength6.is_open() && !findKey)
    {
        while (getline(primeNumLength6, num1))
        {
            ifstream primeBaseLength6("primeBaseLength6.txt");
            while (getline(primeBaseLength6, num2))
            {
                if (checkBreakPrimeNum(num1, num2, orgText))
                {
                    return;
                    primeNumLength6.close();
                    primeBaseLength6.close();
                }
            }
        }
        primeNumLength6.close();
    }

    cout << "done \n";
}

int main()
{

    string myText;

    cout << "please write your text:";
    getline(cin, myText);

    cout << "please write your prime number value for p:";
    cin >> p;
    cout << "please write your prime number value for q:";
    cin >> q;

    if (p != 0 & q != 0)
    {
        CalculateTheValueOfPhi();
        asciiConstructor(myText);
        encryptingChars();
        decryptingChars();
        convertingAsciiCodeToChar();
        breakTheAlgorithm();
    }
}
