#pragma once

#include "CustomTypes.h"
#include "PersonNameableNoMutable.h"
#include "ScorableNonMutable.h"

namespace StudentScoring
{
	/* Concrete implementations of respective NVI's to provide Student and Score */
	class Student : PersonNameableNonMutable, ScorableNonMutable
	{
	private:
		
		/* Prevent default CTOR */
		Student() = delete;

		/* Break down contiguous string into CSV representation */
		IndexedLines DecomposeCSV(const std::string& input);

	public:

		/* Implementation of accessors from NVI */
		std::string GetFirstName() override;
		std::string GetLastName() override;

		/* Implementation of accessor from NVI */
		ScoreValue GetScore() override;

		/* Helper method to convert unsigned int (value) to string */
		inline std::string GetScoreString() { return std::to_string(score); }

		/* Force explicit CTOR(s) */
		explicit Student(std::string& firstName, std::string& lastName, ScoreValue score);
		explicit Student(const std::string& studentDetails);
	};
}
