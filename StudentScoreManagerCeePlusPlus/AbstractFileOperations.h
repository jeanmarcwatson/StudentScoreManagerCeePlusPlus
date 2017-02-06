#pragma once

#include "CustomTypes.h"

namespace StudentScoring
{
	/*	Abstract class to define required functionality for
		reading/writing a text file */
	class AbstractFileOperations
	{
	public:

		virtual void WriteFile(const std::string& fileName, const Lines& contents) = 0;
		virtual LinesUniquePtr ReadFile(const std::string& fileName) = 0;
	};
}