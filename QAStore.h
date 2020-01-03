/*******************************************************
File: QAStore.h
Author : <Jeni>
An object of QAStore stores questions and correct corresponding answers.
The class includes functions to read the question and answers from a text file and  store them in the question and answer variables.
The class instance can have its stored question printed to console.

Date created: 08/11/19
Last modified: 20/11/19
*******************************************************/
#pragma once
#include <string>
#include <fstream>
using namespace std;

class QAStore
{
private:
	string question, answer;

public:
	//Constructor
	QAStore();

	//Get value methods for answer and question
	string getAnswer();
	string getQuestion();

	//Set value methods for answer and question
	void setQuestion(string);
	void setAnswer(string);

	//Display questions to screen
	void printQuestion();


	/*ReadQuestionAndAnswer(): reads each characters from text file and if the character is not "?" or "." is converted to a string and concatenated to question or answer variable.
	Seperates question and answer seperately in text by using "?" to signal end of question and "." signalling the end of a answer. */
	void readQuestionAndAnswer( int, ifstream&,  string &a,string &q);
};
