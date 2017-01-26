#pragma once

namespace StudentScoring
{
	// Non-Virtual Interface pattern for score (interface)
	class ScorableNonMutable
	{

	protected:

		ScoreValue score;

		/* CTOR only available to derived class (Non Virtual Interface pattern - NVI) */
		ScorableNonMutable(ScoreValue score) : score(score) {};

		/* Prevent the use of default constructor */
		ScorableNonMutable() = delete;

	public:

		/* NVI prohibits use of copy CTOR */
		ScorableNonMutable(const ScorableNonMutable& scorableNonMutable) = delete;

		/* NVI prohibits use of assignment */
		ScorableNonMutable& operator=(const ScorableNonMutable& scorableNonMutable) = delete;

		/* Force implementation of accessors */
		virtual ScoreValue GetScore() = 0;
	};
}

