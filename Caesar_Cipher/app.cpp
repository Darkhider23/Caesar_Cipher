// Extra_Credits.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include<cmath>
using namespace std;
void readFreq(float freq[26])
{
    /// <summary>
    /// this function reads the avearge frequency for all the letters of the alphabet
    /// </summary>
    /// <param name="freq">is an array in which it will be stored the avearage frequency of all letters</param>
    int i = 0;
    ifstream f;
    f.open("distribution.txt");
    while (f >> freq[i])
        i++;
}
void readText(string& text) {
    /// <summary>
    /// this function reads from a file the text we need to decypher
    /// </summary>
    /// <param name="text">is a string which will store the message we will need to decypher</param>
    ifstream f;
    f.open("text.txt");
    f >> text;
}
void ComputeFreqLetter(string text, float* Cfreq) {
    /// <summary>
    /// this function computes the frequency of each letter from the text
    /// </summary>
    /// <param name="text">a string which is the text we need to decypher</param>
    /// <param name="Cfreq">is the array which stores the frequency of each letter from the text</param>
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
            Cfreq[text[i] - 'a']++;
        if (text[i] >= 'A' && text[i] <= 'Z')
            Cfreq[text[i] - 'A']++;
    }
}
float ComputeChiSquare(float current, float expected) {
    /// <summary>
    /// this function computes the Chi-Squared Distance
    /// </summary>
    /// <param name="current">is a float that stores the current appearance of a letter</param>
    /// <param name="expected">is a float that stores the expected appearance of a letter</param>
    /// <returns></returns>
    return ((current - expected) * (current - expected)) / expected;
}
float ComputeSum(string text, float Efreq[26], float Cfreq[26]) {
    /// <summary>
    /// this function computes the sum of all letters with the Chi-Squared Distance
    /// </summary>
    /// <param name="text">a string which represents the message we need to decypher</param> 
    /// <param name="Efreq">is an array which contains the average frequency of all letters</param>
    /// <param name="Cfreq">is an array which contains the frequency of all letters from the message</param>
    /// <returns></returns>
    float sum = 0;
    float expected;
    for (int i = 0; i < 26; i++)
    {
        expected = text.size() * Efreq[i] / 100;
        sum += ComputeChiSquare(Cfreq[i], expected);
    }
    return sum;
}
void Perm_Text(string& text) {
    /// <summary>
    /// this function modifies the text by shifting each letter to the right in the alphabet 
    /// </summary>
    /// <param name="text"></param> is a string which stores the message 
    for (int i = 0; i < text.size(); i++)
        if (text[i] == 'z')
            text[i] = 'a';
        else if (text[i] == 'Z')
            text[i] = 'A';
        else
            text[i] += 1;

}
void Decryptation(string text)
{
    /// <summary>
    /// this functions is the brain in which I use all the functions defined above
    ///  to determine the text with which most probable to be the good one
    /// </summary>
    /// <param name="text">a string which stores the message that needs decyphered</param>
    float* Efreq = new float[26];
    float* Cfreq = new float[26]{ 0 };
    readFreq(Efreq);
    string decrypt_text;
    int minimum = 9999999;
    for (int i = 1; i < 26; i++) {
        float* Cfreq = new float[26]{ 0 };
        ComputeFreqLetter(text, Cfreq);
        //here I try to find the minimum sum (the lower the sum the closer the 2 distributions are)
        //when I find a new minimum sum I also memorize the text for it in the variable decrpy_text
        if (minimum > ComputeSum(text, Efreq, Cfreq)) {
            minimum = ComputeSum(text, Efreq, Cfreq);
            decrypt_text = text;
        }
        Perm_Text(text);
    }
    cout << decrypt_text;
}
int main()
{
    string text;
    readText(text);
    Decryptation(text);

}
