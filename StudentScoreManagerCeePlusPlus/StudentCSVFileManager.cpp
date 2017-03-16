#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <Windows.h>

#include "StudentCSVFileManager.h"
#include "StudentCsvFileException.h"

namespace StudentScoring
{
	StudentCsvFileManager::StudentCsvFileManager()
		: inputFileNameAndPathWithoutExtension("")
	{
	}

	// CSV Reader method which is abstracted away from the notion of Student types
	LinesUniquePtr StudentCsvFileManager::ReadCsv(const std::string& sourceFile)
	{
		// Input-filename kept as intrinsic to the creation of the output-CSV-file
		inputFileNameAndPathWithoutExtension = sourceFile.substr(0, sourceFile.find_last_of("."));

		/* Note that the returned container uses move NOT copy semantics */
		return std::move(ReadFile(sourceFile));
	}

	// CSV Writer method
	void StudentCsvFileManager::WriteCsv(const Lines& content)
	{
		// We cannot generate an output file if no input-file(name) provided
		if (inputFileNameAndPathWithoutExtension.length() == 0)
		{
			throw StudentCsvFileException("No respective CSV input-file provided. Output incorporates use of input-file name");
		}

		// We must have a valid input-file so proceed to create an output file
		WriteFile(inputFileNameAndPathWithoutExtension + outputFilePostfix, content);
	}

	// A method to return CSV data from input-file as a container of Student objects
	Students StudentCsvFileManager::ReadStudents(const std::string& sourceFile)
	{
		LinesUniquePtr csvContent = std::move(ReadCsv(sourceFile));		
		Students students;

		// Remove all blank lines from container
		std::remove_if(csvContent->begin(), csvContent->end(), [&](const auto& line) { return line.length() == 0; });

		// Initialise Student objects using the CSV string
		std::for_each(csvContent->begin(), csvContent->end(),
			[&](const auto& line) mutable -> Students
		{
			if (std::count_if(begin(line), end(line), [](auto i) {return i == ','; }) == 2)
			{
				auto student = std::make_shared<Student>(line);
				students.push_back(student);
			}

			return students;
		});

		return students;
	}

	// A method to serialise (loosely speaking) a container of Student objects as CSV to a text file
	void StudentCsvFileManager::WriteStudents(const Students& students)
	{
		Lines lines;

		try
		{
			/*	Write each student as a serliased line of CSV representing the ordered 
				data member contents */
			std::for_each(begin(students), end(students),
				[&lines](const std::shared_ptr<Student>& student) mutable -> Lines
			{
				/* In the absence of any C++ provided reflection of types we set the data-member output order (to CSV) here */
				lines.push_back(student->GetLastName() + "," + student->GetFirstName() + "," + student->GetScoreString() + "\n");

				return lines;
			});

			/* Now write the output as CSV lines */
			WriteCsv(lines);
		}
		catch (StudentCsvFileException& exception)
		{
			std::string compositeMessage = "Attempt to write the output CSV file generated message: " + std::string(exception.what());
			OutputDebugStringA(compositeMessage.c_str());			

			/* Re-throw so dependant methods
			* can also catch the exception */
			throw;
		}
	}
}