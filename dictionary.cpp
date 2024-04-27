
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <chrono>
#include "dictionary.h"
#include "word.h"


using namespace std;

Dictionary::Dictionary()
{
    this->dict = vector<Word>{};
    this->savePath = "";
}

Dictionary::Dictionary(string loadPath)
{
    this->dict = vector<Word>{};
    loadDictionaryFile(loadPath);
    this->savePath = loadPath;
}

/*
    Uses a liniar search and points system to determine the closest fitting word
    If word is not found will return the closest word to it, can be used for word insertion.
    Takes a search word and a reference to a vector with Word objects, returns the words
    position in the vector as an int.
    Written by Jack Briggs on 19/03/23
*/
int Dictionary::findPos(string wordIn)
{
    int bestWordMatchPos{0};
    int bestWordMatch{1};
   
    for(int i = 0; i < this->dict.size(); i++)
    {
        int wordMatchPoints{0};

        for(int j = 0; j < wordIn.size() && j < this->dict[i].getWord().size(); j++)
        {
            if(wordIn[j] == this->dict[i].getWord()[j])
            {
                wordMatchPoints++;
            }
            else
            {
                break;
            }
        }

        if(wordMatchPoints > bestWordMatch)
        {
            bestWordMatch = wordMatchPoints;
            bestWordMatchPos = i;
        }
    }

    return bestWordMatchPos;
}


/*TASK 1: Loads in the dictionary file and reads line by line, if "<word>" is read,
    Reads the next 3 lines, will skip any remaining lines untill "</word>" is read
    Takes a file path string and a reference to the vector<Word> dictionary.
    Returns the number of words found as an integer
    Written by Jack Briggs on 15/03/23*/
int Dictionary::loadDictionaryFile(string dictPath)
{
    this->savePath = dictPath;

    ifstream dictFile(this->savePath);
    string lineBuffer;
    int wordsFound = 0;
    
    // Clears dictionary, for when loading a new dictionary into the program
    this->dict.clear();

    if(dictFile.is_open())
    {
        while (!dictFile.eof())
        {     
            getline(dictFile, lineBuffer);

            // if line starts with "<word>" create a new word object and read following values
            if (lineBuffer.substr(0,6) == "<word>")
            {
                Word newWord{};

                // Because now OO, needs intermediate values
                string name{};
                string definition{};
                string type{};

                getline(dictFile,name);
                getline(dictFile,definition);
                getline(dictFile,type);

                newWord.setWord(name);
                newWord.setDefinition(definition);
                newWord.setType(type);

                // ignore each line after untill "</word>" is read
                while(lineBuffer.substr(0,7) != "</word>")
                {
                    getline(dictFile, lineBuffer);

                    // Just in case end of file is reached
                    if(dictFile.eof())
                    {
                        break;
                    }
                }
                // when detected, add to dictionary
                this->dict.push_back(newWord);

                wordsFound++;
            }
        }
        dictFile.close();
    }

    return wordsFound;
}

int Dictionary::size()
{
    return dict.size();
}


void Dictionary::clearDictionary()
{
    this->dict.clear();
    this->savePath.clear();
}


/*TASK 2: finds a word (searchWord) in a Word vector (called dictionary). 
    Uses findPos, to find the position of the Word object in the dictionary vector.
    Takes a string with the search word and a reference to a Word vector (dictionary) to search in.
    returns the words position as an int, if no word is faound, returns -1.
    Written by Jack Briggs on 19/03/23 
    Modified for OO by Jack Briggs on 30-04-23
    */
Word Dictionary::findWord(string searchWord)
{
    searchWord = makeLowerCase(searchWord);

    int searchWordPos = findPos(searchWord);

    if(0 == this->dict[searchWordPos].getWord().compare(searchWord))
    {
        return this->dict[searchWordPos];
    }
    else
    {
        return Word{};
    }
}


/*
TASK 3: Finds words in a Word vector object (dictionary) with more than 3 z's
Takes a reference to a Word vector, returns a Word vector of words it found.
Written by Jack Briggs on 19/03/23
*/
vector<string> Dictionary::zzzWords()
{
    vector<string> zzzWords{};

    for(Word word : this->dict)
    {
        int zzzCounter{};
        for(char a : word.getWord())
        {
            if(a == 'z')
            {
                zzzCounter++;
            }
        }

        if(zzzCounter > 3)
        {
            zzzWords.push_back(word.getWord());
        }
    }

    return zzzWords;
}


/*TASK 4: Adds a word to a pre-existing Word vector (dictionary) and saves it to a new file
Takes a Word object, reference to a Word vector and the potential files name.
returns the number of words written to the file as an int.
Written by Jack Briggs on 21/03/23 */
int Dictionary::addWord(Word word, string savePath)
{
    // For finding where the word would be if it was in the dictionary (Keeps it organised)
    int wordPos = findPos(word.getWord()) + 1;

    this->savePath = savePath;

    this->dict.insert(this->dict.begin() + wordPos, word);

    // Put that in a new file, babee
    ofstream dictFile(this->savePath);
    int wordCount{};

    for(int i = 0; i < this->dict.size(); i++)
    {
        dictFile << "<word>" << endl;
        dictFile << this->dict[i].getWord() << endl;
        dictFile << this->dict[i].getDefinition() << endl;
        dictFile << this->dict[i].getType() << endl;
        dictFile << "</word>" << endl;
        wordCount++;
    }

    dictFile.close();

    return wordCount;
}


int Dictionary::addWord(Word word)
{
    if(savePath == "")
    {
        throw logic_error("No save path defined");
    }
    return addWord(word, this->savePath);
}

ExtendedDictionary::ExtendedDictionary():Dictionary()
{
    fourthWordHighScore = 0;
}

ExtendedDictionary::ExtendedDictionary(string loadPath):Dictionary(loadPath)
{
    fourthWordHighScore = 0;
}


/*
A function to find all the palindromes in the current dictionary
takes no input and returns a list of Word objects
Written by Jack Briggs on 04-05-23
*/
vector<Word> ExtendedDictionary::findPalindromes()
{
    vector<Word> dictCopy; 
    vector<Word> returnDict{};

    // Add words with the same letter as the first and last word, Stops from being quadratic time complexity
    for(Word a : dict)
    {
        if(a.getWord()[0] == a.getWord()[a.getWord().length()-1])
        {
            dictCopy.push_back(a);
        }
    }

    for(int i{}; 1 < dictCopy.size() ; i++)
    {
        for(int j{}; j < dictCopy.size();)
        {    
            string current = dictCopy[j].getWord();
            int wordLen = dictCopy[j].getWord().size();

            char a = dictCopy[j].getWord()[i];
            char b = dictCopy[j].getWord()[(wordLen-1)-i];

            if(dictCopy[j].getWord()[i] != dictCopy[j].getWord()[(wordLen-1)-i])
            {
                dictCopy.erase(dictCopy.begin() + j);
                continue;
            }

            if(wordLen < 3)
            {
                dictCopy.erase(dictCopy.begin() + j);
                continue;
            }

            if(i == floor(wordLen/2) && i >= 1)
            {
                returnDict.push_back(dictCopy[j]);
                dictCopy.erase(dictCopy.begin() + j);   
                continue;    
            }
            j++;   
        } 
    }
    
    return returnDict;
}


/*
finds words with the same last three letters as the input string
takes a string and returns a vector holding Word objects
Written by Jack Briggs on 07-05-23
*/
vector<Word> ExtendedDictionary::findRhymes(string wordIn)
{
    //return blank if 3 words or shorter
    if(wordIn.size() <= 3)
    {
        return vector<Word>{};
    }

    wordIn = makeLowerCase(wordIn);

    vector<Word> returnWords{};

    string lastThreeChars = wordIn.substr(wordIn.length()-3, wordIn.length()-1);
    
    for(Word a : dict)
    {
        if(a.getWord().length() > 3)
        {
            string wordEnd = a.getWord().substr(a.getWord().length()-3, a.getWord().length()-1);
            if(lastThreeChars.compare(wordEnd) == 0)
            {
                returnWords.push_back(a);
            }
        }
    }
    
    return returnWords;
}


/*
Starts a game where you guess the forth word for the definition of the word. 
does this by counting the spaces.
takes no input or output
Written by Jack Briggs on 08-05-23
*/
void ExtendedDictionary::guessfourthWord()
{
    cout << "Welcome to the game, Guess the four word!" << endl;
    cout << "In this game, you are required to guess the fourth word of the definition!" << endl;

    cout << "the current high score is " << fourthWordHighScore << endl;

    int points = 0;

    while(true)     //Main game loop
    {
        //gets random word by getting the count since epoch and modulo
        int key = chrono::system_clock::now().time_since_epoch().count() % dict.size();

        Word foundWord{dict[key]};
        
        int spaceCount{};
        string fourthWord{};
        string definition{};
        string secondDef{};
        char previousChar{};

        for(char a : foundWord.getDefinition()) //Finds fourth word and replaces it with unerscores(_)
        {
            if(spaceCount < 3)
            {
                definition.push_back(a);
            }
            else if(spaceCount == 3 && a != ' ' && ((a > 64 && a < 133) || (a > 96 && a < 123)))    // Make sure it doesn't print symbols
            {
                fourthWord.push_back(a);
                definition.push_back('_');
            }
            else if (spaceCount >= 4)
            {
                break;
            }

            if(a == ' ' && previousChar != ' ')
            {
                spaceCount ++;
            }
            previousChar = a;
        }

        if(fourthWord.length() < 2)
        {
            continue;
        }

        // make sure the fourth word is all lower to make easier
        fourthWord = makeLowerCase(fourthWord);

        // Add the rest of the definition
        definition.append(foundWord.getDefinition().substr(definition.length(), foundWord.getDefinition().length()));

        cout << "Your current points are " << points << endl; 
        cout << "\nWord: " << foundWord.getWord() << endl;
        cout << definition << endl;
        cout << "what is the fourth word?" << endl;

        string wordIn{};
        cin >> wordIn;

        if(wordIn.compare(fourthWord) == 0)
        {
            cout << "Congratulations, that was the correct word. You just got 10 points!" << endl;
            points += 10;
        }
        else
        {
            if(points > fourthWordHighScore) 
            {
                fourthWordHighScore = points;
                cout << "New high score!" << endl;
            }

            cout << "Sorry, that was incorrect, the correct word was " << fourthWord <<  endl;
            cout << "you finished with " << points << " points!" << endl;
            cout << "would you like to play again? (y/n)" << endl;

            points = 0;

            string response;

            cin >> response;

            response = makeLowerCase(response);

            if (response == "y")
            {
                continue;
            }
            cout << "Thanks for playing" << endl;
            return;
        }
        
    }
    // Make sure to clean buffer so getline() still works
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
}


/*
A tool for cheating in searchle, finds words with the same length and green in the same place.
then removes words without the yellows and with the black letters.
Takes no inputs or outputs (except for terminal inputs/outputs)
Written by Jack Briggs on 08-05-23
*/
void ExtendedDictionary::searchdleCheat()
{
    cout << "Welcome to searchle cheat!" <<  endl;
    cout << "This program is for cheating at searchle!\n" << endl;
    cout << "this program works in three parts" << endl;
    cout << "First: place the blank letters with underscores ('_') and place the letters in their GREEN positions. e.g: '_ell_'" << endl;
    cout << "Second: type out the yellow words as one word. e.g: 'wy'" << endl;
    cout << "Third: type out the black words as one word. e.g: 'xg'\n" << endl;
    cout << "Words matching the conditions will be shown" << endl;
    cout << "Input 'exit' at any point to exit" << endl;
    cout << "Input 'reset' at any point to reset the word database\n\n" << endl;

    

    while(true)
    {
        // Make it so it searches for words of the same length and adds them to the dict
        vector<Word> wordPointers{};
        
        // Find words matching length and green letters and add them to vector
        cout << "Input underlines and green letters:" << endl;

        string greenAndUnders;
        getline(cin,greenAndUnders);

        if(greenAndUnders == "exit")
            break;

        for(Word a : dict)
        {
            // Check Lengths, if not the same lenghth, delewtes and skips the word.
            if (a.getWord().length() != greenAndUnders.length())
            {
                continue;
            }

            bool ignoreElement = false;
            for(int j {0}; j < greenAndUnders.length(); j++)
            {
                // checks if is an underscore, if so, skips letter
                if(greenAndUnders[j] == '_')
                {
                    continue;
                }

                if(a.getWord()[j] != greenAndUnders[j])
                {
                    ignoreElement = true;
                    break;
                }
            }  
            
            if(ignoreElement)           //checkpoint for if element should be ignored
                continue;

            wordPointers.push_back(a);  // If made this far, passsed all tests, add to list
        }


        // Now filter out any words without yellow letters
        cout << "Input yellow letters:" << endl;
        
        string yellows;
        getline(cin,yellows);

        if(yellows == "exit")
            break;
        else if(yellows == "reset")
        {
            wordPointers = dict;
            cout << "word database reset\n" << endl;
            continue;
        }

        for(int i{0}; i < wordPointers.size();)
        {
            bool noYellowDeleted = false;

            for(char a : yellows)
            {
                bool inWord = false;

                for(char b : wordPointers[i].getWord())
                {
                    if(a == b)
                    {
                        inWord = true;
                    }
                }

                if(!inWord)
                {
                    wordPointers.erase(wordPointers.begin()+i);
                    noYellowDeleted = true;
                }
            }

            if(noYellowDeleted)     //checkpoint for if a element was deleted
                continue;

            i++;                    // got this far, iterate
        }


        // Filter out words with black words now
        cout << "Input black letters:" << endl;

        string blackLetters;
        getline(cin,blackLetters);

        if(blackLetters == "exit")
            break;
        else if(blackLetters == "reset")
        {
            wordPointers = dict;
            cout << "word database reset\n" << endl;
            continue;
        }

        for(int i{0}; i < wordPointers.size();)
        {  
            bool blackDeleted = false;

            for(char a : blackLetters)
            {
                bool inWord = false;

                for(char b : wordPointers[i].getWord())
                {
                    if(a == b)
                    {
                        inWord = true;
                    }
                }

                if(inWord)
                {
                    wordPointers.erase(wordPointers.begin()+i);
                    blackDeleted = true;
                }
            }

            if(blackDeleted)    //checkpoint for if a element was deleted
                continue;

            i++;                // Got this far, iterate
        }

        cout << "\n\n";
        for(Word a : wordPointers)
        {
            cout << a.getWord() << endl;
        }
        cout << "\n";
    }

    // exit message, prints when breaks out of loop
    cout << "\nReturning to main menu\n" << endl;
}