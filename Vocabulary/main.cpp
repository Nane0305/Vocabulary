
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class FreqVocab
{
    map <string, int> countWords;
    void addWord(string word);
public:
    FreqVocab() = default;
    void readFile(const char* fname);
    map <string, int>::iterator mostComWord();
    void print();
    void writeFile(const char* fname);
};

void FreqVocab::addWord(string word)
{
    map <string, int>::iterator k = countWords.find(word);
    if (k != countWords.end())
        k->second++;
    else
        countWords[word] = 1;
}

void  FreqVocab::readFile(const char* fname)
{
    std::ifstream file(fname);
    string str;
    if (!file.is_open())
        throw "Can`t open the file";
    while (!file.eof())
    {
        std::getline(file, str);
        char* str_w = &str[0];
        char* pw = strtok(str_w, " ,-:.\";?!");
        while (pw)
        {
            string word(pw);
            char capitalLet = toupper(word[0]);
            word = capitalLet + word.substr(1);
            addWord(word);
            pw = strtok(0, " ,-:.\";?!");
        }
    }
    file.close();
}

map <string, int>::iterator FreqVocab::mostComWord()
{
    return std::max_element(countWords.begin(), countWords.end(), [](const std::pair<string, int>& p1, const std::pair<string, int>& p2)
        { return p1.second < p2.second; });
}

void FreqVocab::print()
{
    map<string, int>::iterator k = countWords.begin();
    cout << "******************************" << endl;
    for (int i = 0; k != countWords.end(); k++, i++)
        cout << k->first << " - " << k->second << endl;
    cout << "******************************" << endl;
    map <string, int>::iterator comW = mostComWord();
    cout << "The most common word is: " << comW->first << " - " << comW->second << endl;
}

void FreqVocab::writeFile(const char* fname)
{
    std::ofstream file(fname);
    if (!file.is_open())
        throw "Can`t open the file";
    map <string, int>::iterator k = countWords.begin();
    file << "******************************" << endl;
    for (int i = 0; k != countWords.end(); k++, i++)
        file << k->first << " - " << k->second << endl;
    file << "******************************" << endl;
    map <string, int>::iterator comW = mostComWord();
    file << "The most common word is: " << comW->first << " - " << comW->second << endl;
    file.close();
}

int main()
{
    FreqVocab v;
    try
    {
        v.readFile("Spring.txt");
        v.print();
        v.writeFile("Test.txt");
    }
    catch (const char* error)
    {
        cout << "Error! " << error;
    }
    return 0;
}