#ifndef WORD_H
#define WORD_H

#include <string>

using namespace std;


/*
Makes all input lowercase, seperate because both word and dictionary need
this method. Put here for convienience.
*/
string makeLowerCase(string wordtoConvert);

/*
Word holds 3 properties for the word itslef, its type and its definition
Written by Jack Briggs on 04/03/23
Modified to be OO, integrated makeLowerCase
Modified by Jack Briggs on 30-04-23 
*/
class Word
{
    private:
        string name;
        string type;
        string definition;
        string decodeType(string type);
    public:
        Word();
        Word(string name, string type, string definition);
        void printDefinition();
        void setWord(string);
        bool setType(string);
        void setDefinition(string);
        string getWord();
        string getType();
        string getDefinition();
};

#endif