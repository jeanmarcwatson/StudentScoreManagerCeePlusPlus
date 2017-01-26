// StudentScoreManagerCeePlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "StudentScoreManager.h"

using namespace StudentScoring;

int main()
{
	/* Read an input CSV file, sort the contents and write the resulting output file */
	StudentScoreManager studentScoreManager;
	std::string inputFile{ "G:\\Development\\Visual C++\\StudentScoreManagerCeePlusPlus\\StudentScoreManagerCeePlusPlus\\Data\\students.txt" };

	studentScoreManager.CreateStudents(inputFile);
	studentScoreManager.PersistStudents(studentScoreManager.GetStudents());
}

