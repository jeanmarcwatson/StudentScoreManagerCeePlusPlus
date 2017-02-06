#pragma once

#include "CustomTypes.h"
#include "FileIO.h"
#include "AbstractCSVOperations.h"
#include "Student.h"

namespace StudentScoring
{
	// The main management entity for reading/writing of CSV files
	class StudentCsvFileManager : FileIO, AbstractCSVOperations
	{
	private:
		std::string outputFilePostfix{ "-graded.txt" };
		std::string inputFileNameAndPathWithoutExtension;

	public:

		StudentCsvFileManager();

		// CSV Reader method which is abstracted away from the notion of Student types
		LinesUniquePtr ReadCsv(const std::string& sourceFile) override;

		// CSV Writer method
		void WriteCsv(const Lines& content) override;

		// A method to return CSV data from input-file as a container of Student objects
		Students ReadStudents(const std::string& sourceFile);

		// A method to serialise (loosely speaking) a container of Student objects as CSV to a text file
		void WriteStudents(const Students& students);
	};
}
