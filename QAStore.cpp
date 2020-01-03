/*******************************************************
File: QAsStore.cpp
Author : <Jeni Robbie>
Description: Contains function definitions for Q and A class that store question and its corresponding answer in each object.
Contains function to read questions and answers from text file  to set QAStore object variables.

Assumptions made:
1. How is questions and stored stored?
We need to know this preemptively to read in appropriate manner
2. How are questions and answers distinguishable?
Seperated by special characters.

Decisions
1. Kept a lot of readAnswer variables within the functions as they are only used there.

Date created: 08/11/19
Date modified: 20/11/19
*******************************************************/


#pragma once
#include "QAStore.h"
#include <iostream>

// Constructor: sets all object instances of QuestionAnd Answer to "unknown" as default	
QAStore::QAStore()
{
		question = "unknown";			
		answer = "unknown";
}

// Get the answer value	
string QAStore::getAnswer()
{
	return answer;
}

// Get question value
string QAStore::getQuestion()
{
	return question;
}

// Set question value by question value to input variable
void QAStore::setQuestion(string input)
{
	question = input;
}
// Set question value by answer value to input variable
void QAStore::setAnswer(string input)
{
	answer = input;
}

// Print questions to console
void QAStore::printQuestion()
{
	cout << question << endl;
}



/*ReadQuestionAndAnswer()
PARAMETERS : Number of questions to read, the ifstream and strings to store question and answer values
VALUE RETURNED : none
DESCRIPTION : reads each character from text file and if the character is not "?" or "." is converted to a string and concatenated to question or answer variable.
Loops until all characters read.
Seperates question and answer in text by using "?" to signal end of question and "." signalling the end of a answer.
and stores values in QuestionAndAnswer object array to get all questions and answers
*/
void QAStore::readQuestionAndAnswer( int numQ, ifstream& fileBeingRead, string &a, string &q)
{
	const char questionEnd = '?', answerEnd = '.';				//character signifying end of question ? seperating questions and answers and chracter signifying end of answer

	char input;						//current character read
	string inputConvert[1];			//String to store input character
	bool isQuestion = false;

	cout << "#entering function readQuestionAndAnswer()" << endl;		//Trace to screen
			//Read through every character (including spaces)
			while (fileBeingRead.get(input))
			{
				//Check to see if the current character read is question or answer end symbol
				if (input == questionEnd)			//if true = end of question
				{
					isQuestion = true;
					fileBeingRead >> input; //Move onto next character to not store seperator symbols
				}
				else if (input == answerEnd)		//if true = end of answer
				{
					isQuestion = false;
					break;
				}
				if (isQuestion == false)
				{
					inputConvert[0] = input; //convert cuurently read character to string
					q +=inputConvert[0];	//concatenate current question string and character to be added to form full questions
				}
				else
				{
					inputConvert[0] = input;		//convert cuurently read character to string
					a += inputConvert[0];			//concatenate current answer string and character to be added to form full answer
				}
			}
			cout << "#leaving function readQuestionAndAnswer()" << endl;		//Trace to screen
}




