#pragma once

#include "CustomTypes.h"
#include "AbstractFileOperations.h"

namespace StudentScoring
{
	// This class serves as the file reader/writer and cannot be extended any further
	class FileIO : AbstractFileOperations
	{

	public:

		/* Concrete and non-extendable implementation for file-writing */
		void WriteFile(const std::string& fileName, const Lines& contents) final;

		/* Concrete and non-extendable implementation for file-reading */
		LinesUniquePtr ReadFile(const std::string& fileName) final;
	};
}
