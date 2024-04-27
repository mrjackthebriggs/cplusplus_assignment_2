#include <iostream>
#include <stdexcept>
#include "word.h"

using namespace std;


/* for making all input lowercase.
   Takes a string pottentially in uppercase and returns a string completely in lower case.
   Written by Jack Briggs on 19/03/23 */
string makeLowerCase(string wordtoConvert)
{
    for(int i = 0; i < wordtoConvert.size(); i++)
    {
        if(wordtoConvert[i] >= 65 && wordtoConvert[i] <= 90)
        {
            wordtoConvert[i] += 32;
        }
    }

    return wordtoConvert;
}


/*
 Definitions for the Word object constructors.
*/
Word::Word()
{
    this->name = "";
    this->type = "";
    this->definition = "";
}

Word::Word(string name, string type, string definition)
{
    this->setWord(name);
    if(!this->setType(type))
        throw invalid_argument("Invalid word type");
    this->setDefinition(definition);
}


/* Made to decode the word type syntax and return the propper output for printing
   takes the string from the dictionary file and returns a string with the full name of what it is.

   The else at the bottom allows this method to have a second use, if an invalid word type is input durring the addWord()
   process, it will return an empty string, for determining if the input word type is valid or not

   Witten by Jack Briggs on 19/03/23 */
string Word::decodeType(string wordType)
{
    if(wordType == "n")
    {
        return (string)"noun";
    }
    else if(wordType == "v")
    {
        return (string)"verb";
    }
    else if(wordType == "adv")
    {
        return (string)"adverb";
    }
    else if(wordType == "adj")
    {
        return (string)"adjective";
    }
    else if(wordType == "prep")
    {
        return (string)"preposition";
    }
    else if(wordType == "misc")
    {
        return (string)"miscellaneous";
    }
    else if(wordType == "pn")
    {
        return (string)"proper noun";
    }
    else
    {
        return (string)"";
    }

}

/*
Prints output as it did in Assignment 1.
Needs no inputs, Outputs name, type and definition to terminal
Written by Jack Briggs on 30-04-23
*/
void Word::printDefinition()
{
    cout << this->name << endl;
    cout << "[" << decodeType(this->type) << "]"<< endl;    // For printing out the name of the full type instead of an abreviation
    cout << this->definition << endl;
}

/*
Setter method for the name variable
Takes a string in for setting the word. Returns nothing
Written by Jack Briggs on 30-04-23
*/
void Word::setWord(string wordIn)
{
    this->name = makeLowerCase(wordIn);
}

/*
Setter method for the type variable
Takes a string and checks if it follows the input rules in decodeType()
Returns a bool to confirm of set was successful
Written by Jack Briggs on 30-04-23
*/
bool Word::setType(string typeIn)
{
    if(decodeType(typeIn) != "")
    {
        this->type = typeIn;
        return true;
    }
    else
    {
        return false;
    }
}

/*
A setter method for the definition of the word
HAs a string input to assign to the definition, returns nothing
Written by Jack Briggs on 30-04-23
*/
void Word::setDefinition(string definitionIn)
{
    this->definition = definitionIn;
}

/*

*/
string Word::getWord()
{
    return this->name;
}

/*

*/
string Word::getType()
{
    return decodeType(this->type);
}

/*

*/
string Word::getDefinition()
{
    return this->definition;
}
