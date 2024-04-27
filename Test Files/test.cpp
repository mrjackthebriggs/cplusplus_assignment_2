#include <iostream>
#include "word.h"
#include "dictionary.h"
#include <stdexcept>

#define BOOST_TEST_MODULE asstest
#include "boost/test/included/unit_test.hpp"
using namespace std;

BOOST_AUTO_TEST_CASE(WordSets)
{
    Word word1 = Word("Name","n","Sucks dick");
    
    word1.setWord("New Name");
    BOOST_TEST(word1.getWord() == "new name");

    BOOST_TEST(!word1.setType("shithead"));
    BOOST_TEST(word1.getType() != "shithead");

    BOOST_TEST(word1.setType("pn"));
    BOOST_TEST(word1.getType() == "pn");

    word1.setDefinition("When you get a new name");
    BOOST_TEST(word1.getDefinition() == "When you get a new name");
}

BOOST_AUTO_TEST_CASE(WordGets)
{
    Word word("Name", "n", "A label for a thing");

    BOOST_TEST(word.getWord() == "name");
    BOOST_TEST(word.getType() == "n");
    BOOST_TEST(word.getDefinition() == "A label for a thing");
}

BOOST_AUTO_TEST_CASE(BlankWord)
{
    Word word{};

    BOOST_TEST(word.getWord() == "");
    BOOST_TEST(word.getType() == "");
    BOOST_TEST(word.getDefinition() == "");
}

void wordexceptiontest()
{
    Word word{"Name", "Whoops", "Definiton"};
}

void wordnoexceptiontest()
{
    Word word{"Name", "n", "Definiton"};
}

BOOST_AUTO_TEST_CASE(ThrowWordExcept)
{

    BOOST_CHECK_THROW(wordexceptiontest(), invalid_argument); 
    BOOST_CHECK_NO_THROW(wordnoexceptiontest()); 
}

/*
issues with writing and boost test
BOOST_AUTO_TEST_CASE(BlankDictionaryTest)
{
    Dictionary dict{};

    Word w {"Name","n","Definition"};

    BOOST_TEST(dict.addWord(w,"here.txt") == 1);
}
*/

BOOST_AUTO_TEST_CASE(LoadDictionary1)
{
    Dictionary dict{};

    BOOST_TEST(dict.loadDictionaryFile("dictionary_2023S1.txt") == 105160);
}

BOOST_AUTO_TEST_CASE(Cleardictionary)
{
    Dictionary dict{};

    BOOST_TEST(dict.loadDictionaryFile("dictionary_2023S1.txt") == 105160);
}

BOOST_AUTO_TEST_CASE(checknosavePath)
{
    Dictionary dict{};
    Word word{"Name", "n", "Definition"};
    BOOST_CHECK_THROW(dict.addWord(word), logic_error); 
}

BOOST_AUTO_TEST_CASE(checkdictionaryclear)
{
    Dictionary dict{};
    Word word{"Name", "n", "Definition"};
    BOOST_TEST(dict.loadDictionaryFile("dictionary_2023S1.txt") == 105160);

    dict.clearDictionary();

    BOOST_CHECK_THROW(dict.addWord(word), logic_error); 

    BOOST_TEST(dict.size() == 0);

    BOOST_TEST(dict.loadDictionaryFile("dictionary_2023S1.txt"));

    BOOST_TEST(dict.size() != 0);
}

BOOST_AUTO_TEST_CASE(dictionaryfind)
{
    Dictionary dict{"dictionary_2023S1.txt"};
    
    BOOST_TEST(dict.findWord("apple").getWord() == "apple");
}

BOOST_AUTO_TEST_CASE(dictionaryfailfind)
{
    Dictionary dict{"dictionary_2023S1.txt"};
    
    BOOST_TEST(dict.findWord("kasnozzle").getWord() != "kasnozzle");
}

BOOST_AUTO_TEST_CASE(zzzzwordfind)
{
    Dictionary dict{"dictionary_2023S1.txt"};

    BOOST_TEST(dict.zzzWords().size() < 2);
    BOOST_TEST(dict.zzzWords().size() > 0);
    BOOST_TEST(dict.zzzWords().size() == 1);
}

BOOST_AUTO_TEST_CASE(lowercaseTest)
{
    Word word("BeNiS","n","Benis :DDD");
    BOOST_TEST(word.getWord() == "benis");
}

BOOST_AUTO_TEST_CASE(lowercasedictionaryfind)
{
    Dictionary dict{"dictionary_2023S1.txt"};
    
    BOOST_TEST(dict.findWord("aPpLe").getWord() == "apple");
}

BOOST_AUTO_TEST_CASE(extendedpalindrome)
{
    ExtendedDictionary dict{"dictionary_2023S1.txt"};

    vector<Word> retwords = dict.findPalindromes();

    BOOST_TEST(retwords.size() == 83);   
}


BOOST_AUTO_TEST_CASE(Rhyme_Test)
{
    ExtendedDictionary dict{"dictionary_2023S1.txt"};
    vector<Word> ret = dict.findRhymes("Pigger");

    BOOST_TEST(ret.size() == 311);

    ret = dict.findRhymes("Time");

    BOOST_TEST(ret.size() == 80);
    BOOST_TEST(ret[ret.size()-1].getWord() == "xenotime");
}