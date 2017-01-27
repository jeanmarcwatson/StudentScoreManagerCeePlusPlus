#pragma once

#include "CustomTypes.h"
#include "AbstractFileOperations.h"

namespace StudentScoring
{
	// Abstract class defines required CSV functionality
	class AbstractCSVOperations
	{
	public:

		virtual void WriteCsv(Lines& content) = 0;
		virtual LinesUniquePtr ReadCsv(std::string& sourceFile) = 0;
	};
}
