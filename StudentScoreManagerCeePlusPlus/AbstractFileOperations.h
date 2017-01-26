#pragma once

#include "CustomTypes.h"

namespace StudentScoring
{
	/*	Abstract class to define required functionality for
		reading/writing a text file */
	class AbstractFileOperations
	{
	public:

		virtual void WriteFile(std::string& fileName, Lines& contents) = 0;
		virtual LinesUniquePtr ReadFile(std::string& fileName) = 0;
	};
}