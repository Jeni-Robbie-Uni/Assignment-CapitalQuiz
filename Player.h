/*******************************************************
File:Player.h
Author : <Jeni Robbie>
Description: objects of this class store players initials and scores.
The class functions calculates the players quiz score by taking in user answer, comparing the answer to the QAStore answer
and if correct incrementing score until all questions are marked.
A function writes the score and initials to a high score table file
then another reads the file and prints all the previous players scores and initials as well as the current players
score.

Dates created:08/11/19
Last modified: 08/11/19
*******************************************************/

#pragma once
#include "QAStore.h"
#include <string>
using namespace std;
class Player
{
private:
	string playerInitials;	//Variable to assign players name
	int playerScore=0;	//Variable to hold players game score
	const int maxConstraint = 3;		//Max number of characters user can enter for initials
public:

	//Declare Functions
	//Constructors
	Player();

	// Get score value method
	int getPlayerScore();

	// Get initials value method
	string getPlayerInitials();

	//Set initials value method
	void setPlayerInitials(string);

	//Set score value method
	void setPlayerScore(int);

	//Ask the user for initials and validate length
	string askForUserInitials();
	
	// Compares User answers and QAStore object answer  and increases score by 1 if user answer is the same
	void compare2answers(string[], QAStore [], int);

	//asks quiz questions and gets user answers
	string getPlayerAns();
	
	//Writes players initials and scores to a high score table
	void writeToScore(Player&);
	
	//reads highscore file and prints highscore table
	void readScoreTable();
	
};



