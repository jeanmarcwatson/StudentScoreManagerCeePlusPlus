#pragma once

#include <exception>
#include <string>

namespace StudentScoring
{
	// A bespoke exception class for CSV file-exceptions 
	class StudentCsvFileException : public std::exception
	{
	public:
		StudentCsvFileException::StudentCsvFileException()
		{
		}

		StudentCsvFileException(const std::string& exceptionMessage)
			: std::exception(exceptionMessage.c_str())
		{
		}
	};
}
