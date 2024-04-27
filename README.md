# C++ Dictionary (Assignment 2)
This was submitted as the second assignment for a university unit: Object-oriented C++. This assignment scored a 29/30. 

This assignment used BOOST test to unit test methods and classses
    Boost 1.82.0 was used, and needs to be in the main dir for tests to work

This project was redone in rust, which is another one of my public repos

The brief for this assignment was:
An extension of Assignment 1. First, you will re-factor your program to be more object-oriented, then you will implement some additional functionality.

1. Convert you Word struct from Assignment 1 into a Word class. Encapsulate the appropriate functionality of a Word into the Word class, including getters, setters, constructor and the printDefinition function that prints that words name, type and definition according to the output requirements that were given in Assignment 1.
    a. The Word class should be defined and implemented in its own file (eg. Word.h) – for this assignment there is no requirement for a separate Word.cpp file, and you may include your implementation of Word in the header (.h) file.
2. Create a class called Dictionary. Use the Dictionary class to encapsulate the data and functionality related to the dictionary.
    a. The Dictionary class should be defined in a file called Dictionary.h and implemented in a file called Dictionary.cpp
    b. The Dictionary class should hold and maintain the STL Vector of Word objects.
    c. The Dictionary class should be responsible for loading the dictionary file using an appropriately named method.
    d. The functions from Assignment 1 should be encapsulated as member functions (aka methods) into the Dictionary class.
3. Once the Assignment 1 functionality is working in the new Assignment 2 program architecture, create a new class ExtendedDictionary, using inheritance from the Dictionary class. 
    a. ExtendedDictionary should use the functions from its parent class to load and manage the Vector of Words, and perform Assignment 1 functionality (ie. do not re-implement these in ExtendedDictionary)

4. Add new functionality to the ExtendedDictionary class, allowing the following tasks to be selected from the program main menu:

## Basic Tasks:
### Task 05
Palindromes - List all words in the dictionary that are palindromes. e.g .”civic”

### Task 06
Rhyming words – prompt the user to enter a word and print all words from the dictionary that end in the same sequence of three letters as the entered word.

## Intermediate tasks 
### Task 07
Guess the fourth word – Your program should choose a random word from the dictionary, one that has more than 4 words in its definition. The program should initially welcome the player and print the current high score. Then the program should print the word and the definition, with the fourth word of the definition replaced by underscores. The player then has to guess the missing word. If the player succeeds, the program should print ‘congratulations’ and continue by presenting another word and definition. If the player guesses incorrectly, the program should print a message informing the player of the correct word and the players score, the game then finishes. The player should receive 10 points for each correctly guessed word and the program should keep a record (which should be preserved if they exit the game and attempt other tasks) of the highest score, with the player informed when they have beaten it.

## Advanced task
### Task 08
Cheat at Searchdle (see: https://wtfseo.com/searchdle/). Design, implement and test functionality that will allow the user to search for all words in the Dictionary that meet a set of parameters:
    a. Have the same number of letters as the ‘mystery’ word.
    b. Do not contain any of the letters in a user-specified set (i.e., the grey letters),
    c. Contain the entire set of letters in a second, user-specified, set, anywhere in the word) (i.e., the yellow/orange letters),
    d. Contain the entire set of letters in a third user-specified set at positions specified for each of the letters (i.e., the green letters).
    e. The task should be implemented as a new method in the ExtendedDictionary class, however Word objects should be responsible for determining what letters they have, don’t have, and how long they are.
    f. For this task it is up to you to design a means of interaction with the program and how the results are displayed, aim for an interface that is easy to use by someone proficient with a console interface or menu style interface. Assume the user has never heard of the game before running your program (ie. give some instructions). 