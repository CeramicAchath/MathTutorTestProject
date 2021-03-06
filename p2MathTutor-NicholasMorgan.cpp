﻿/*
@Project : p2mathtutorNicholasMorgan.cpp :
@Description : This program is supposed to generate problems for a user and check the answers the user inputs
@Version : 7/11/2018 First Build, created problem selection/menu,
@version 2 : 7/14/2018 broke math functions into int and decimal portions to allow scaling, added more customizeable parts
@known bugs : if EPSILON is changed the floating decimal place for floatgen doesnt change with it 
*/

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

//Global Constants
const int NUMBEROFPROBLEMS = 5;
const double EPSILON = 0.1;
const string CORRECT = "Correct!";
const string INCORRECT = "Incorrect.";
const int CORRECTSCORE = 1;
const int INCORRECTSCORE = 0;
const int MAXINTINTERVAL = 8;
const int MININTINTERVAL = 1;
const double MAXDOUBLEINTERVAL = 8.0;
const double MINDOUBLEINTERVAL = 1.0;

//Function Prototypes
int problemSelection(void);
void problemTree(int selection, int decimalOrInteger);
void additionTestInt(void);
void additionTestDouble(void);
void subtractionTestInt(void);
void subtractionTestDouble(void);
void multiplicationTestInt(void);
void multiplicationTestDouble(void);
void divisionTestInt(void);
void divisionTestDouble(void);
void remainderTestInt(void);
void remainderTestDouble(void);
int getUserIntOrDoubleSelection(void);
void userScore(int testScores);
int genInt(void);
float genFloat(void);
bool closeEnough(double userDouble, double answerDouble);
int answerCheckInt(int answerInt, int userAnswer);
int answerCheckDouble(double answerDouble, double userAnswer);

int main()
{
	//Local Variables
	int exitValue = 1;

	srand(time(0));

	while (exitValue != 0)
	{
		exitValue = problemSelection();

	}
	return 0;
}

int problemSelection(void)
{
	//local Variables
	int userInputSelection = 0;
	int exitValue = 0;
	int decimalOrInteger = 1;
	
	//Ask for decimal or integer tests
	decimalOrInteger = getUserIntOrDoubleSelection();

	//Present test types
	cout << "Which type of problems would you like to test yourself on?" << endl;
	cout << "Press 0 to quit" << endl;
	cout << "1. Addition" << endl;
	cout << "2. Subtraction" << endl;
	cout << "3. Multiplication" << endl;
	cout << "4. Division" << endl;
	cout << "5. Remainder" << endl;

	//Grab users input
	cin >> userInputSelection;

	//Pass selection to the decision tree

	problemTree(userInputSelection, decimalOrInteger);
	return userInputSelection;

}

void problemTree(int selection, int decimalOrInteger)
{
	enum problems_t { quit = 0, addition, subtraction, multiplication, division, remainder };
	if (selection == quit)
	{
		cout << "Have a good day." << endl;
		system("pause");

	}
	else if (selection == addition)
	{
		if (decimalOrInteger == 1)
		{
			additionTestInt();
		}
		else
		{
			additionTestDouble();
		}

	}
	else if (selection == subtraction)
	{
		if (decimalOrInteger == 1)
		{
			subtractionTestInt();
		}
		else
		{
			multiplicationTestDouble();
		}


	}
	else if (selection == multiplication)
	{
		if (decimalOrInteger == 1)
		{
			multiplicationTestInt();
		}
		else
		{
			multiplicationTestDouble();
		}

	}
	else if (selection == division)
	{
		if (decimalOrInteger == 1)
		{
			divisionTestInt();
		}
		else
		{
			divisionTestDouble();
		}

	}
	else if (selection == remainder)
	{
		if (decimalOrInteger == 1)
		{
			remainderTestInt();
		}
		else
		{
			remainderTestDouble();
		}

	}
	else
	{
		cout << "Sorry, please choose a valid selection." << endl;
		problemSelection();
	}
}

int getUserIntOrDoubleSelection(void)
{
	//Local Variables
	int userSelection = 0;

	cout << "Would you like to test decimals or integers? " << endl;
	cout << "1. Integers\n";
	cout << "2. Decimals\n";
	cin >> userSelection;

	return userSelection;
}

int answerCheckDouble(double answerDouble, double userAnswerDouble)
{
	double correctAnswerDouble = answerDouble;
	double userDoubleInput = userAnswerDouble;
	bool correctAnswerBool = false;

	correctAnswerBool = closeEnough(userDoubleInput, correctAnswerDouble);

	if (correctAnswerBool == CORRECTSCORE)
	{
		cout << CORRECT << endl;
		return CORRECTSCORE;

	}
	else
	{
		cout << INCORRECT << endl;
		return INCORRECTSCORE;
	}

}
//Calculates and presents the users score for that excersice
void userScore(int score)
{
	//Local variables
	double totalScore;

	totalScore = (score / NUMBEROFPROBLEMS);

	cout << "Your score was " << setprecision(2) << totalScore << "% ( " << score << " / " << NUMBEROFPROBLEMS << " ) " << endl;


}
//generates a random int value between the max and min constnats
int genInt(void)
{
	//Local Variables
	int randomNumber = 0;

	randomNumber = (rand() % 10);
	if (randomNumber >= MININTINTERVAL || randomNumber >= MAXINTINTERVAL)
	{
		return randomNumber;
	}
	else 
	{
		genInt();
	}
	
}
//generates a random float value between the max and min constants
float genFloat(void)
{
	//Local Variables
	float randomFloat = 0;
	float truncatedFloat = 0;

	// generate a random floating point number between max double interval and min
	randomFloat = ( ( (rand() / (float)RAND_MAX) * (MAXDOUBLEINTERVAL - 1)) + MINDOUBLEINTERVAL); 
	
	//truncate the float to the first decimal
	truncatedFloat = roundf(randomFloat * 10) / 10;

	return truncatedFloat;
	
}
//checks answer vs user answer withing the epsilon value
bool closeEnough(double answerDouble, double userAnswerDouble)
{
	double closeEnoughCheck = 0;
	double errorMin = (0 - EPSILON);
	double errorMax = (EPSILON);

	closeEnoughCheck = answerDouble - userAnswerDouble;

	if (closeEnoughCheck >= 0 && closeEnoughCheck <= errorMax)
	{
		return CORRECTSCORE;
	}
	else if (closeEnoughCheck <= 0 && closeEnoughCheck >= errorMax)
	{
		return CORRECTSCORE;
	}
	else
	{
		return INCORRECTSCORE;
	}
}

//compates generated answer vs user's answer
int answerCheckInt(int answerInt, int userInputInt)
{
	if (answerInt == userInputInt)
	{
		cout << CORRECT << endl;
		cout << "Correct answer " << answerInt << endl;
		return CORRECTSCORE;
	}
	else
	{
		cout << INCORRECT << endl;
		cout << "Correct answer " << answerInt << endl;
		return INCORRECTSCORE;
	}
}

//Generates a integer addition problem and presents it 
void additionTestInt()
{
	int i = 0;
	int firstIntNumber = 0;
	int secondIntNumber = 0;
	int answer = 0;
	int userAnswer = 0;
	int currentScore = 0;

	for (int i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstIntNumber = genInt();
		secondIntNumber = genInt();
		answer = firstIntNumber + secondIntNumber;
		
		cout << "What is the sum of " << firstIntNumber << "+" << secondIntNumber << " ?" << endl;
		
		cin >> userAnswer;
		
		currentScore = currentScore + answerCheckInt(answer, userAnswer);
		
	}

	userScore(currentScore);
}

//Generates a decimal addition problem and presents it 
void additionTestDouble()
{
	int i = 0;
	float firstFloatNumber = 0;
	float secondFloatNumber = 0;
	float answer = 0;
	float userAnswer = 0;
	int currentScore = 0;

	for (i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstFloatNumber = genFloat();
		secondFloatNumber = genFloat();
	
		answer = (firstFloatNumber + secondFloatNumber);

		cout << "What is the sum of " << firstFloatNumber << "+" << secondFloatNumber << " ?" << endl;

		cin >> userAnswer;

		currentScore = currentScore + answerCheckDouble(answer, userAnswer);
	}

	userScore(currentScore);
}

//Generates a integer subtraction problem and presents it 
void subtractionTestInt()
{
	int i = 0;
	int firstIntNumber = 0;
	int secondIntNumber = 0;
	int answer = 0;
	int userAnswer = 0;
	int currentScore = 0;

	for (int i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstIntNumber = genInt();
		secondIntNumber = genInt();
		if (firstIntNumber >= secondIntNumber)
		{
			answer = firstIntNumber - secondIntNumber;

			cout << "What is " << firstIntNumber << "-" << secondIntNumber << " ?" << endl;

			cin >> userAnswer;

			currentScore = currentScore + answerCheckInt(answer, userAnswer);

		}
		else
		{
			answer = secondIntNumber - firstIntNumber;

			cout << "What is " << secondIntNumber << "-" << firstIntNumber << " ?" << endl;

			cin >> userAnswer;

			currentScore = currentScore + answerCheckInt(answer, userAnswer);
		}
	}

	userScore(currentScore);
}

//Generates a decimal subtraction problem and presents it 
void subtractionTestDouble()
{
	int i = 0;
	float firstFloatNumber = 0;
	float secondFloatNumber = 0;
	float answer = 0;
	float userAnswer = 0;
	int currentScore = 0;

	for (i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstFloatNumber = genFloat();
		secondFloatNumber = genFloat();

		if (firstFloatNumber >= secondFloatNumber)
		{
			answer = (firstFloatNumber - secondFloatNumber);
			cout << "What is  " << firstFloatNumber << "-" << secondFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
		else
		{
			answer = (secondFloatNumber - firstFloatNumber);
			cout << "What is " << secondFloatNumber << "-" << firstFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
	}
	userScore(currentScore);
}

//Generates a integer multiplication problem and presents it 
void multiplicationTestInt()
{
	int i = 0;
	int firstIntNumber = 0;
	int secondIntNumber = 0;
	int answer = 0;
	int userAnswer = 0;
	int currentScore = 0;

	for (int i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstIntNumber = genInt();
		secondIntNumber = genInt();

		answer = firstIntNumber * secondIntNumber;
		
		cout << "What is " << firstIntNumber << "*" << secondIntNumber << " ?" << endl;
		
		cin >> userAnswer;
		
		currentScore = currentScore + answerCheckInt(answer, userAnswer);
	}

	userScore(currentScore);
}

//Generates a decimal multiplication problem and presents it 
void multiplicationTestDouble()
{
	int i = 0;
	float firstFloatNumber = 0;
	float secondFloatNumber = 0;
	float answer = 0;
	float userAnswer = 0;
	int currentScore = 0;

	for (i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstFloatNumber = genFloat();
		secondFloatNumber = genFloat();

			answer = (firstFloatNumber * secondFloatNumber);

			cout << "What is " << firstFloatNumber << "*" << secondFloatNumber << " to one decimal place?" << endl;
	
			cin >> userAnswer;
	
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
	}
	userScore(currentScore);
}
//Generates a integer division problem and presents it 
void divisionTestInt()
{
	int i = 0;
	int firstIntNumber = 0;
	int secondIntNumber = 0;
	int answer = 0;
	int userAnswer = 0;
	int currentScore = 0;

	for (int i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstIntNumber = genInt();
		secondIntNumber = genInt();
		if (firstIntNumber >= secondIntNumber)
		{
			answer = firstIntNumber / secondIntNumber;
			cout << "What is " << firstIntNumber << "/" << secondIntNumber << " in integers?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckInt(answer, userAnswer);

		}
		else
		{
			answer = secondIntNumber / firstIntNumber;
			cout << "What is " << secondIntNumber << "/" << firstIntNumber << " in integers?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckInt(answer, userAnswer);
		}
	}

	userScore(currentScore);
}
//Generates a decimal division problem and presents it 
void divisionTestDouble()
{
	int i = 0;
	float firstFloatNumber = 0;
	float secondFloatNumber = 0;
	float answer = 0;
	float userAnswer = 0;
	int currentScore = 0;

	for (i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstFloatNumber = genFloat();
		secondFloatNumber = genFloat();
		if (firstFloatNumber >= secondFloatNumber)
		{
			answer = (firstFloatNumber / secondFloatNumber);
			cout << "What is " << firstFloatNumber << "/" << secondFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
		else
		{
			answer = (secondFloatNumber / firstFloatNumber);
			cout << "What is " << secondFloatNumber << "/" << firstFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
	}
	userScore(currentScore);
}
//Generates a integer remainder problem and presents it 
void remainderTestInt()
{
	int i = 0;
	int firstIntNumber = 0;
	int secondIntNumber = 0;
	int answer = 0;
	int userAnswer = 0;
	int currentScore = 0;

	for (int i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstIntNumber = genInt();
		secondIntNumber = genInt();
		if (firstIntNumber >= secondIntNumber)
		{
			answer = firstIntNumber % secondIntNumber;
			cout << "What is the integer remainder of " << firstIntNumber << "/" << secondIntNumber << " ?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckInt(answer, userAnswer);

		}
		else
		{
			answer = secondIntNumber % firstIntNumber;
			cout << "What is the integer remainder of " << secondIntNumber << "/" << firstIntNumber << " ?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckInt(answer, userAnswer);
		}
	}

	userScore(currentScore);
}

//Generates a decimal remainder problem and presents it 
void remainderTestDouble()
{
	int i = 0;
	float firstFloatNumber = 0;
	float secondFloatNumber = 0;
	float answer = 0;
	float userAnswer = 0;
	int currentScore = 0;

	for (i = 1; i <= NUMBEROFPROBLEMS; i++)
	{
		firstFloatNumber = genFloat();
		secondFloatNumber = genFloat();
		if (firstFloatNumber >= secondFloatNumber)
		{
			answer = fmod(firstFloatNumber, secondFloatNumber);
			cout << "What is the remainder of " << firstFloatNumber << "/" << secondFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
		else
		{
			answer = fmod(secondFloatNumber, firstFloatNumber);
			cout << "What is the remainder of " << secondFloatNumber << "/" << firstFloatNumber << " to one decimal place?" << endl;
			cin >> userAnswer;
			currentScore = currentScore + answerCheckDouble(answer, userAnswer);
		}
	}
	userScore(currentScore);
}
