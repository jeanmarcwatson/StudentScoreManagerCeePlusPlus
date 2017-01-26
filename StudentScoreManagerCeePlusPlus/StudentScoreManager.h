#pragma once

#include "CustomTypes.h"
#include "StudentCSVFileManager.h"

namespace StudentScoring
{
	bool Compare(std::shared_ptr<Student>& x, std::shared_ptr<Student>& y);

	/* The top-level Student container management class */
	class StudentScoreManager
	{
	private:

		// All of our students
		Students students;

		// File-management type
		StudentCsvFileManager studentCSVFileManager;

	protected:


	public:

		// Provide read-only access the student container
		inline Students GetStudents()
		{
			return students;
		}

		/* We provide a default CTOR */
		StudentScoreManager() {}

		// Simple method for creating the container of Students using a CSV file
		void CreateStudents(std::string& sourceFile);

		/* Method to allow the sorted student container to be written
		* to an output CSV file */
		void PersistStudents(Students& students);
	};
}
