
/************************************************************************************************************************************************************************
File: QuizGame.cpp
Author:Jeni Robbie
Dates created:08/11/19
modified last:20/11/19
Lines of code (not including blank lines or brackets) :197

Objective:
Program reads questions and answers from file,
Asks the player the question, gets user response, compares user answer and to question answer.
If useanswer is right (userA == quesA), add one to to score.
The score and player name will be save to score file and then full score table printed

Assumptions made are as followed :
1. How many times do they get to take the quiz?
As many times as they would like.
2. Does the user get to choose quiz?
No at this point in time only the capital quiz is available but this could be extended functionality
3. Do they overwrite their previous score?
No just like old arcade games there score will be saved additionally
4. How many Questions will be asked?
Set amount of 7
As of yet can not extend arrays therefore number of questions must be set constant
5. What format will the questions answer be in quiz text file?
Questions and answers are held in same file similar to key value database
6. Will the questions be asked in specific or random order?
Specific order from 1 to 7.
7. Can the user exit at anytime?
No they must complete the quiz or exit via closing the console window
8. Will scores be read/ written to file in specific order for example highest score first?
No all scores and initials will be appended to file added to previous score list

Decisions:
1. Could have asked user for initials first and then initialised object.
However I believed the function that you ask for input and validate should be encapsulated in player class
2. Made the highscore name entry 3 charcters for initials like old arcade games
Having a set character length meant I could format the highscore table the same way for each entry
3. how to store Q and A format
Questions and answers are on the same line.
The end of the question is signified by a '?' and the end of an answer signified by '.'
4. Class vs 2D array
Used class instead of 2D array to store questions and answes
Thought about using 2d array however as the value (answer) is specific to the question (key) need to store context indictive of column data
4. Functionality of extending array sizes would allow more flexible importing of quiz files that could involves
a function to get the number of questions asked- hency why it is a variable to be specified in all functions.
5. Included player initials length check in player class not as seperate function as this program is small but potentially be apart of a bigger string validation based class
6. Declared quiz read file stream outside of classed used to give future flexibility in changing the file
7. Kept read and write highscore streams to open and close in functions as they were only used in one function- greater degree of encapsulation
8. Calculated score all at once instead of recalculating  after every question and answer as seemed more efficient

*****************************************************************************************************************************************************************************/
#include "Player.h"
#include "QAStore.h"
#include <string>
#include <iostream>
using namespace std;

	//Print the quiz instructions 
	void printQuizInstructions(int);

	int main()
	{
		string userAnswer[7];			//Create string array to hold players answers
		string userInitials, answer, question;				//users initials, Stores questions and answers read from text file 
		ifstream readQuizFile;
		string fileName = "Quiz Questions.txt";				//Name of file to be opened
		
		const int numOfQuestions = 7;		//Number of questions needs to be constant to initialise QAStore object array
		char exitResponse = ' ';			// User response to exit or continue question

		//Create instance of player
		Player playerOne;

		//Create object array of questions and answers class
		cout << "#Create instance of QAStore" << endl;		//Trace to screen
		QAStore capitalQuiz[numOfQuestions];

		//Prints quiz instructions to console	
		printQuizInstructions(numOfQuestions);

		//Get and validate length of player initials
		userInitials = playerOne.askForUserInitials();

		//Set player instance initals
		playerOne.setPlayerInitials(userInitials);

		cout << "#Open file Quiz game .txt" << endl;			//Trace to screen
		readQuizFile.open(fileName);
		//Check if file has opened correctly- if not display error
		cout << "#Check if file has opened correctly" << endl;		//Trace to screen
		if (!readQuizFile.is_open())
			cout << "Error. Could not open file." << endl;
		else
		{
			//Loop for number of questions and answers in file
			for (int x = 0; x < numOfQuestions; x++)
			{
				//Reads the questions and answers from text file
				capitalQuiz[x].readQuestionAndAnswer(numOfQuestions, readQuizFile, answer, question);

				//set question to object array appropiate postion 
				capitalQuiz[x].setQuestion(question);

				//set the answer to object in same object as associated question
				capitalQuiz[x].setAnswer(answer);

				//Clears string of values so that new answer value may be added in next loop
				answer.clear();

				//Clears string of values so that new question value may be added in next loop
				question.clear();
			}
		}
		//close read file as no longer needed
		readQuizFile.close();


		do {
			//Resets score if player is taking quiz again
			playerOne.setPlayerScore(0);
			//Ask player the quiz questions and get answer 
			for (int x = 0; x < numOfQuestions; x++)
			{
				//Print the question number before question
				if (x == 0)
				{
					cout << "Question " << (x + 1) << endl;	//Only Need to include the endl for first question as the or question function adds new lines thereafter
				}
				else
					cout << "Question " << (x + 1);

				//Prints question from object instance at specific array position 
				capitalQuiz[x].printQuestion();

				//sets values of user answer arrays 
				userAnswer[x] = playerOne.getPlayerAns();
			}


			//Calculate players score by comparing user answer and correct answer
			playerOne.compare2answers(userAnswer, capitalQuiz, numOfQuestions);

			//Add current players score to score table file
			playerOne.writeToScore(playerOne);

			//print highscore table
			playerOne.readScoreTable();

			//Asks user if the would like to play again
			cout << "Would you like to play again? Press Y or yes or any other key to exit" << endl;
			cin >> exitResponse;

		} while (exitResponse == 'Y' || exitResponse == 'y');

	return 0;

}

//Prints quiz instructions with number of questions in quiz passed as parameter 
void printQuizInstructions(int numQ)
{
	cout << "Welcome to the quiz! /nYou will be asked to enter your initials which must be 3 characters in length." << endl;
	cout << "You will be asked a series of " << numQ << " questions about the captials of countries. \nAfter each question, please input your answer." << endl;
	cout << "At the end, your score and initials will be added to the score table and the score table will be printed to screen. Good Luck!" << endl;
}

