#include "stdafx.h"

#include <algorithm>
#include <string>
#include "StudentScoreManager.h"

namespace StudentScoring
{
	// Simple method for creating the container of Students using a CSV file
	void StudentScoreManager::CreateStudents(std::string& sourceFile)
	{
		// Create our Student container based upon the contents of the input-file
		students = studentCSVFileManager.ReadStudents(sourceFile);

		// Sort the St&udent(s) according to our sort criteria
		students.sort(Compare);
	}

	/* Method to allow the sorted student container to be written
	* to an output CSV file */
	void StudentScoreManager::PersistStudents(Students& students)
	{
		/* Output-file is inferred from input file so we only provide the
		* students */
		studentCSVFileManager.WriteStudents(students);
	}

	/*	This is our Student type sort method which determines how to sort the
		respective container of Student objects */
	bool Compare(std::shared_ptr<Student>& x, std::shared_ptr<Student>& y)
	{
		// Indicate equality of Student objects
		if (x == y)
		{
			return 0;
		}

		auto xFirstName = x->GetFirstName();
		auto xLastName = x->GetLastName();
		auto yFirstName = y->GetFirstName();
		auto yLastName = y->GetLastName();

		/* Work in lowercase for names */
		std::transform(xFirstName.begin(), xFirstName.end(), xFirstName.begin(), ::tolower);
		std::transform(xLastName.begin(), xLastName.end(), xLastName.begin(), ::tolower);
		std::transform(yFirstName.begin(), yFirstName.end(), yFirstName.begin(), ::tolower);
		std::transform(yLastName.begin(), yLastName.end(), yLastName.begin(), ::tolower);

		/* Score is the first discriminator but if equal revert
		* to comparing last-name and if equality for that then
		* compare using first-name */
		if (x->GetScore() == y->GetScore())
		{
			if (xLastName == yLastName)
			{
				return xFirstName.compare(yFirstName) == -1 ? true : false;
			}
			else
			{
				return xLastName.compare(yLastName) == -1 ? true : false;;
			}
		}
		else if (x->GetScore() > y->GetScore())
		{
			/* Score ordering is descending as
			* apposed to the default ordering of
			* the 'CompareTo' method */
			return true;
		}
		else
		{
			return false;
		}
	}
}