#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <vector>
#include "word.h"

using namespace std;

/*
Dictionary class handles the functionality of storing and managing Word objects
*/
class Dictionary
{
    protected:
        vector<Word> dict;
        string savePath;
        int findPos(string);
    public:
        Dictionary();
        Dictionary(string);
        int loadDictionaryFile(string dictPath);
        int size();
        void clearDictionary();
        Word findWord(string word);
        int addWord(Word word);// check seperately
        int addWord(Word word, string newSavePath);// check seperately
        vector<string> zzzWords();
};

class ExtendedDictionary : public Dictionary
{
    private:
        int fourthWordHighScore;
    public:
        ExtendedDictionary();
        ExtendedDictionary(string);
        vector<Word> findPalindromes();
        vector<Word> findRhymes(string);
        void guessfourthWord();
        void searchdleCheat();
};

#endif