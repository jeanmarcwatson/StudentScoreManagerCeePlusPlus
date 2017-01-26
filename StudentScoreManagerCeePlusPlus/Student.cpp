#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <regex>
#include <vector>
#include <sstream>

#include "Student.h"

namespace StudentScoring
{
	Student::Student(std::string& firstName, std::string& lastName, ScoreValue score)
		: PersonNameableNonMutable(firstName, lastName), ScorableNonMutable(score)
	{
		/* Simply initialises our NVI classes (interfaces) */
	}

	Student::Student(const std::string& studentDetails)
		: PersonNameableNonMutable(studentDetails), ScorableNonMutable(0)
	{
		// De-compose the string into its constituent parts
		IndexedLines items = DecomposeCSV(studentDetails);

		/* Check length for semantic completeness of provided "Student"
		* NOTE:    Anything that does not conform to the expected input format is
		*          essentially rejected */
		if (items.size() == 3)
		{
			// If we have null strings for First and last name then default the name
			firstName = (items[0].size() == 0 ? "JOHN" : items[0]);
			lastName = (items[1].size() == 0 ? "DOE" : items[1]);

			/* Convert the string value to an unsigned int */
			std::stringstream scoreAsString;
			scoreAsString << items[2];
			scoreAsString >> score;
		}
	}

	/* Accessor for student first-name */
	std::string Student::GetFirstName()
	{
		return firstName;
	}

	/* Accessor for student last-name */
	std::string Student::GetLastName()
	{
		return lastName;
	}

	/* Accessor for student score */
	ScoreValue Student::GetScore()
	{
		return score;
	}

	/* Decompose a CSV line into an indexed container */
	IndexedLines Student::DecomposeCSV(const std::string& input)
	{
		IndexedLines lines;
		std::string outputStr{ "" };
		
		/*	Use a mutable and returnable lambda (closure) to iterate the string 
			build the container */
		std::for_each(input.begin(), input.end(),
			[&outputStr, &lines](const char& character) mutable -> IndexedLines
		{
			if (character != ',')
			{
				outputStr += character;
			}
			else
			{
				lines.push_back(outputStr);
				outputStr.erase();
			}

			return lines;
		});

		/*	Push the last field parsed from the line
			and ensure we have something in the container first */
		if (lines.size() > 0)
		{
			lines.push_back(outputStr);
		}

		return lines;
	}
}