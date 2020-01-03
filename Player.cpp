/*******************************************************
File:Player.cpp
Author : <Jeni Robbie>
Description: Function definitions for player class to store players name information, calculate scores and
read and print score table.

Assumptions:
1.How long are user initials?
Must be 3 charcter max and min to format table appropriatly.
2. Does the user have to answer question in specific format? e.g Answer begins with captial letter
No the user can enter answer case insensitive
3. Can the user if playing again overwrite previos score?
No the score with same initials will be appended to file
4. How is the score table formatted?
We have to know how the score table is formatted in file to choose appropriate method of reading -see decisions
New score is added to a new line.
5. When is the score calculated?
Score is calculated once all questions are asked and answers are given not after each answer.

Decisions
1. Opened and closed score table file for reading and writing within the seperate functions as they are only used within those functions
2. Formatted the score table to store each player initials and score on same line
New score is added to a new line.
3. Stored all answers in lowercase and converted user answers to lowercase to score answers case insensitively

Dates created:08/11/19
Last modified: 21/11/19
*******************************************************/
#pragma once
#include "Player.h"
#include <iostream>
#include <algorithm>

// Constructor: sets all object scoreCalculator object score counter to 0 as default	
Player::Player()
{
	cout << "#Create instance of player objecton with constructor values" << endl;		//Trace to screen
	playerInitials = "unknown";
	playerScore = 0;
}

//Get score Value method
int Player::getPlayerScore()
{
	return playerScore;
}
//Get initials Value method
string Player::getPlayerInitials()
{
	return playerInitials;
}
//Set initials value method
void Player::setPlayerInitials(string name)
{
	cout << "#entering function setPlayerInitials()" << endl;
	playerInitials = name;
}
//Set score value method
void Player::setPlayerScore(int score)
{
	cout << "#entering function setPlayerScore()" << endl;
	playerScore = score;
}
/* Compares User answers and QAStore object answer  and increases score by 1 if user answer is the same
Checks all user input to object answers  at once by looping through array */
void Player::compare2answers(string userA[], QAStore questionA[], int numQ) 
{
	cout << "#entering function compare2answers()" << endl;		//Tracing
	for (int x = 0; x < numQ; x++)
	{

		cout << "#Comparing userAnswer to QAStore answer in same array position as QAStore object array " << endl;
		if (userA[x] == questionA[x].getAnswer())			//compares user answer to QAStore object answer
		{
			cout << "#Correct answer so 1 is added to score" << endl; //Trace to screen
			playerScore += 1;		//Adds 1 to score if answers match
		}
	}
	cout << "#Leaving function compare2answers()" << endl;		//Tracing
}

/*Asks for user to input 3 characters for initials
checks length is valid using the constraint constant 
and returns initials when length is valid */
string Player::askForUserInitials()
{
	bool valid = false;
	string initials;
	cout << "#entering askForuserinitials()" << endl;		//tracing to screen
	while (valid == false)
	{
		cout << "Please enter your initials to add to the highscore table. (Initials must include 3 characters)" << endl;
		cin >> initials;
		if (initials.length() != maxConstraint)					//compare the length of the input to the value constraint
		{
			cout << "#doing length validation test" << endl;		//tracing to screen
			cout << "Input invalid." << endl;
			valid=false;

		}
		else
			valid= true;
		
	}
	return initials;
}
/*Asks player to input answer and return it
All user answers are converted to lowercase so that the addition or
absence of a capital at start of user answer has not impact on score */
string Player::getPlayerAns()
{
	cout << "#entering getplayerAns()" << endl;
	cout << "Please enter answer:" << endl;
	string playerAnswer;
	cin >> playerAnswer;
	//Converts user answer to all lowercase
	cout << "#converting player answer to begin with lowercase letter" << endl;
	transform(playerAnswer.begin(), playerAnswer.end(), playerAnswer.begin(), ::tolower);
	return playerAnswer;
}

/*Takes in player object as parameter
and wappends player instance attributes- score and initials- to text file */
void Player::writeToScore(Player& user)
{
	cout << "#entering function writeToScoreTable()" << endl;		//Tracing
	ofstream writeFile;
	writeFile.open("HighScoreTable.txt", ios::app);		//Open highscore file and allow the file to be appended
	
	//Check if file has opened correctly- if not display error
	if (!writeFile.is_open())
		cout << "Error. Could not open file." << endl;
	else
	{
		cout << "#Writing initials and score to text file" << endl;			//Trace to screen
		writeFile << user.getPlayerInitials() << "                " << user.getPlayerScore() << endl;	//Write player object initials and score to file in specific format
		
	}
	writeFile.close();
	cout << "#Closing ofstream /nLeaving writeScoreTable()" << endl;	//Tracing
}

/*Reads the score table file 
Assumptions made is that we know how the file is formatted therefore not looking for intials and score seperately- read together by reading the whole line.
Stores each line in scoreResult
Prints players scores and initials together to console */
void Player::readScoreTable()
{
	cout << "#Entering readScoreTable()" << endl;	//Tracing
	string scoreResult;			//Stores string of each line from text file read
	ifstream scoreTable;
	cout << "Create scoreTable ifstream" << endl;	//Trace to screen
	scoreTable.open("HighScoreTable.txt");

	cout << "opened HighScoreTable text file and checked if opened correctly" << endl;		//Trace to Screen
	//Check if file has opened correctly- if not display error
	if (!scoreTable.is_open())
		cout << "Error. Could not open file." << endl;
	else
	{
		cout << "Name		Score" << endl;	//Print table title
		while (!scoreTable.eof())					//Reads until end of file
		{
			getline(scoreTable, scoreResult);	//Reads scores line by line and strores as string scoreResult
			cout << "#Reading line from text file \n" << scoreResult << endl;
		}
		scoreTable.close();
		cout << "#Leaving readScoreTable()" << endl;	//Tracing
	}
}