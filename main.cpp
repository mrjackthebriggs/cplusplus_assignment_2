
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "dictionary.h"
#include "word.h"
#include <limits>

/*
main.cpp is used for the main loop and display of the app, this will handle user inputs and what is printed to console
*/

using namespace std;

const string DEFAULT_DICTIONARY = "dictionary_2023S1.txt"; 

int main()
{
    int inputChoice;
    ExtendedDictionary dictionary{};
      
    //Displays a menu of 4 tasks
    cout << "|             Welcome to Dictionary Manager Xtreme            |" << endl;

    //Loops menu while inputChoice has a value between 1-4
    do
    {
        cout << "\nPlease pick a task by inputing its coresponding number:" << endl;
        cout << "1) Load a custom or default dictionary" << endl;
        cout << "2) Find a word in the loaded dictionary" << endl;
        cout << "3) Find words with more than 3 z's in the loaded dictionary" << endl;
        cout << "4) Add a word to the loaded dictionary" << endl;
        cout << "5) Find palindromes in the current dictionary" << endl;
        cout << "6) Find Rhymes in current dictionary" << endl;
        cout << "7) Guess the foruth word, Game where you guess the fourth word" << endl;
        cout << "8) Searchle cheat, a tool for cheating at searchle" << endl;
        cout << "0) to exit\n" << endl; 

        cin >> inputChoice;

        // stole this from : https://stackoverflow.com/a/10553849
        // removes the newline from the buffer of the previous cin, allows the use of getline()
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

        
        if(inputChoice == 0)
        {
            cout << "0 : Exit Program" << endl;
            cout << "Thank you for using:\n" << endl;
            cout << "|      Dictionary Manager Xtreme      |\n\n" << endl;
        }


        else if(inputChoice == 1)
        {
            cout << "1 : Load Dictionary Selected" << endl;
            cout << "Please input a dictionary file path (with file type at the end), put in \"default\" to select the default dictionary file" << endl;
            
            std::string dictSel;
            unsigned int wordsFound;

            getline(cin,dictSel);

            if(dictSel == "default")
            {
                dictSel = DEFAULT_DICTIONARY;
            }
            
            wordsFound = dictionary.loadDictionaryFile(dictSel);
            cout << wordsFound << " Words loaded into the dictionary" << endl;
        }


        else if(inputChoice == 2)
        { 
            cout << "2 : Word Search Selected" << endl;
            // Check if dictionary is loaded
            if(dictionary.size() != 0)
            {
                string searchWord; 
                cout << "please input a word to search for: " << endl;
                getline(cin, searchWord);

                // finds position of searched for word using findWord in source.cpp
                Word returnedWord = dictionary.findWord(searchWord);

                if (returnedWord.getWord() == "")
                {
                    cout << "\nWord not found!\n";
                }
                else
                {
                    cout << endl;
                    cout <<"Word Found! " << endl;
                    cout << returnedWord.getWord() << endl;
                    cout << "[" << returnedWord.getType() << "]"<< endl;
                    cout << returnedWord.getDefinition() << endl;
                } 
            }
            else
            {
                cout << "No dictionary loaded, please load a dictionary with option 1" << endl;
            }

            
        }


        else if(inputChoice == 3)
        {    
            cout << "3 : >ZZZ Word Search Selected" << endl;
            // Check if dictionary is loaded
            if(dictionary.size() != 0)
            {
                vector<string> zzzWords = dictionary.zzzWords();

                if(zzzWords.size() != 0)
                {
                    cout << zzzWords.size() <<" >ZZZ words found: " << endl;
                    for(string zzzWord : zzzWords)
                    {
                        cout << "\t> " << zzzWord << endl;
                    }
                }

                
            }
            else
            {
                cout << "No dictionary loaded, please load a dictionary with option 1" << endl;
            }
        }


        else if(inputChoice == 4)
        {
            cout << "4 : Add Word to Dictionary Selected" << endl;
            // Check if dictionary is loaded
            if(dictionary.size() != 0)
            {
                string newName{};
                bool overWrite{};
                Word newWord{};

                cout << "Please input the word you would like to add: " << endl;
                getline(cin, newName);
                newWord.setWord(newName);

                // Check if new word already exists, else returns to top of loop
                Word ifFound = dictionary.findWord(newName);

                if(ifFound.getWord() != "")
                {
                    cout << "error: word exists, elevated privileges required to edit existing words" << endl; 
                    continue;                
                }
               
               cout << ":" << ifFound.getWord() << ":";

                // checking if input word type is valid, if a blank string is returned then it is an invalid type
                string typeInp{};
                cout << "\nWhat type of word is it? Input: " << endl;
                cout << "\"n\" for a noun" << endl;
                cout << "\"v\" for a verb" << endl;
                cout << "\"adv\" for an adverb" << endl;
                cout << "\"adj\" for an adjective" << endl;
                cout << "\"prep\" for a preposition" << endl;
                cout << "\"misc\" for miscellaneous" << endl;
                cout << "\"pn\" for a proper noun" << endl;
                
                getline(cin, typeInp);

                if(!newWord.setType(typeInp))
                {
                    cout << "\ninvalid word type, please try again" << endl;
                    continue;
                }

                // All checks are done, get definition of the word and where the new dictionary file is to be saved
                string defInp{};
                cout << "\nWhat is the definition of this word?:" << endl;
                getline(cin,defInp);
                newWord.setDefinition(defInp);

                // Make if blank only uses the other overload
                // Now we have all our info, make the word object using a constructor and give it to addWord()
                string savePath{};
                cout << "\nWhat would you like to name the new dictionary file (with file type at the end)?(Leave blank if you would like to use the last one used):" << endl;
                getline(cin,savePath);

                if(savePath == "")
                {
                    int wordCount = dictionary.addWord(newWord);
                    cout << wordCount << " words successfully written." << endl;
                }
                else
                {
                    int wordCount = dictionary.addWord(newWord,savePath);
                    cout << wordCount << " words successfully written to " << savePath << endl;
                }
                
            }
            else
            {
                cout << "No dictionary file not loaded, please load a dictionary file with option 1" << endl;
            }
        }

        else if(inputChoice == 5)
        {
            // Check if dictionary is loaded
            if(dictionary.size() != 0)
            {
                vector<Word> palindromes = dictionary.findPalindromes();

                cout << "Palindromes in the dictionary are:"<< endl;
                for(int i{}; i < palindromes.size(); i++)
                {
                    cout << palindromes[i].getWord() << endl;
                }
            }
            else
            {
                cout << "No dictionary file not loaded, please load a dictionary file with option 1" << endl;
            }
        }

        else if(inputChoice == 6)
        {
            // Check if dictionary is loaded
            if(dictionary.size() != 0)
            {
                cout << "Input the word you want rhyming words for:" << endl;
                string rhymeWord{};
                getline(cin, rhymeWord);

                Word retWord = dictionary.findWord(rhymeWord);

                if(retWord.getWord() == "")
                {
                    cout << "word not found, please try again" << endl;
                    continue;
                }

                vector<Word> rhymes = dictionary.findRhymes(rhymeWord);
                
                cout << "Words that rhyme with " << rhymeWord << ":" << endl;
                
                for(int i{}; i < rhymes.size(); i++)
                {
                    cout << rhymes[i].getWord() << endl;
                }
            }
            else
            {
                cout << "No dictionary file not loaded, please load a dictionary file with option 1" << endl;
            }
        }

        else if(inputChoice == 7)
        {
            // Check if dictionary is loaded
            if(dictionary.size() != 0)
            {

            }
            else
            {
                cout << "No dictionary file not loaded, please load a dictionary file with option 1" << endl;
            }
        }

        else if(inputChoice == 8)
        {
            // Check if dictionary is loaded
            if(dictionary.size() != 0)
            {

            }
            else
            {
                cout << "No dictionary file not loaded, please load a dictionary file with option 1" << endl;
            }
        }
        else if(inputChoice > 8 || inputChoice < 0)
            cout << "Please input a value between 0 - 8\n" << endl;
            continue;                
    }
    while(inputChoice != 0);

    return 0;
}