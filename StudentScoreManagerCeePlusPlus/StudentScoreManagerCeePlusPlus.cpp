// StudentScoreManagerCeePlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include "StudentScoreManager.h"

using namespace StudentScoring;

void main(int argc, char *argv[], char *envp[])
{
	/* Check we have valid command-line arguments */
	if (argc > 1)
	{
		/* Output to console regardless of whether running debug/release as we don't want
		the application to fail silently when no parameters/bad parameters are provided for
		input file */		
		OutputDebugStringA("You provided more than one argument for the input file-name/path.");
		return;
	}
	else if (argc == 0)
	{
		/* Same principle as above, for writing to console */
		OutputDebugStringA("You did not provide any argument for the input file-name/path.");
		return;
	}

	/* Read an input CSV file, sort the contents and write the resulting output file */
	StudentScoreManager studentScoreManager;
	std::string inputFile{ "students.txt" };

	studentScoreManager.CreateStudents(inputFile);
	studentScoreManager.PersistStudents(studentScoreManager.GetStudents());
}

