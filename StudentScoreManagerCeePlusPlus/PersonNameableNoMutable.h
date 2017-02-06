#pragma once

#include <string>

namespace StudentScoring
{
	// Non-Virtual Interface pattern for Persons Name (interface)
	class PersonNameableNonMutable
	{

	protected:

		std::string firstName;
		std::string lastName;

		/* CTOR only available to derived class (Non Virtual Interface pattern - NVI) */
		PersonNameableNonMutable(const std::string& studentDetails) : firstName(""), lastName("") {};

		/* CTOR only available to derived class (Non Virtual Interface pattern - NVI) */
		PersonNameableNonMutable(const std::string& firstName, const std::string& lastName) : firstName(firstName), lastName(lastName) {};

		/* Prevent the use of default constructor */
		PersonNameableNonMutable() = delete;

	public:

		/* NVI prohibits use of copy CTOR */
		PersonNameableNonMutable(const PersonNameableNonMutable& personNameableNonMutable) = delete;

		/* NVI prohibits use of assignment */
		PersonNameableNonMutable& operator=(const PersonNameableNonMutable& personNameableNonMutable) = delete;

		/* Force implementation of accessors */
		virtual std::string GetFirstName() = 0;
		virtual std::string GetLastName() = 0;
	};
}