/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC patter, and is responsibe for all 
user interaction. For game logic, see FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Unreal syntax
using FText = std::string;
using int32 = int;

// method forward declarations
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // declare a new game

// the entry for our application
int main() 
{
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } 
    while (bPlayAgain);
    return 0; // exit the application
}

void PrintIntro()
{
    std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

// plays a single round of the game
void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    // loop asking for guesses while the game
    // is NOT won and there are still tries remaining
    constexpr int32 NUMBER_OF_TURNS = 5;
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        FText Guess = GetValidGuess();

        // submit valid guess to the game, and receive counts
        FBullCowCount BullCowCount =  BCGame.SubmitValidGuess(Guess);
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }

    PrintGameSummary();
    return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {
        // get a guess from the player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ": Enter your guess: ";
        std::getline(std::cin, Guess);

        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters.\n\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter all lowercase letters.\n\n";
            break;
        default:
            // assume guess is valid
            break;
        }
    } while (Status != EGuessStatus::OK); // keep looping until we get no errors
    return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word (y/n)? ";
    FText Response = "";
    std::getline(std::cin, Response);
    return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n";
    }
    else
    {
        std::cout << "Better luck next time!\n";
    }
}
