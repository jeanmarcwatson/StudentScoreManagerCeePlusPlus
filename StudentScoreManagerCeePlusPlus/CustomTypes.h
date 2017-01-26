#pragma once

#include <list>
#include <string>
#include <memory>
#include <vector>

namespace StudentScoring
{
	/*	Forward declare student as cannot include header
		as it creates a cyclic dependency */
	class Student;

	/* Unsigned integer for score */
	using ScoreValue = unsigned int;

	/* Ensure container of students is not unmanaged */
	using Students = std::list<std::shared_ptr<Student>>;

	/* Semantically more intuutive definition for container of strings */
	using Lines = std::list<std::string>;

	/* Allows items in the container to be indexed */
	using IndexedLines = std::vector<std::string>;

	/* Unique instance of Lines - requires move NOT copy semantics */
	using LinesUniquePtr = std::unique_ptr<Lines>;

	/* Companion type for LinesUniquePtr */
	using StudentsUniquePtr = std::unique_ptr<Students>;
}
