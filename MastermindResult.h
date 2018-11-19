#ifndef MASTERMINDRESULT_H
#define MASTERMINDRESULT_H

#include <vector>

/**
 MastermindResult represents the outcome of a guess in the game mastermind.
 Given the result of a guess, it can determine if that outcome was consistent
 with a theoretical answer.  This can be used to solve Mastermind puzzles:
 https://puzzlephil.com/puzzles/mastermind/en/
 */
class MastermindResult {
public:
	class MastermindResultBuilder {
	public:
		MastermindResult build();
		MastermindResultBuilder& setGuess(unsigned int guess);
		MastermindResultBuilder& setLength(unsigned int length);
		MastermindResultBuilder& setCorrectlyPlaced(unsigned int placed);
		MastermindResultBuilder& setMisplaced(unsigned int misplaced);

	private:
		bool m_hasGuess = false;
		unsigned int m_guess;
		unsigned int m_length = 4;
		unsigned int m_placed = 0;
		unsigned int m_misplaced = 0;
	};
	static MastermindResultBuilder builder() { return MastermindResultBuilder(); }

	bool matches(unsigned int answer);

private:
	MastermindResult(unsigned int guess, unsigned int length, unsigned int placed, unsigned int misplaced)
		: m_guessDigits(splitToDigits(guess, length)),
			m_guessDigitCount(countDigits(m_guessDigits)),
			m_correctlyPlaced(placed),
			m_misplaced(misplaced) {}

	static std::vector<unsigned int> splitToDigits(unsigned int n, unsigned int length);
	static std::vector<unsigned int> countDigits(const std::vector<unsigned int>& digits);

	const std::vector<unsigned int> m_guessDigits;
	const std::vector<unsigned int> m_guessDigitCount;
	unsigned int m_digitCount[10] = {};
	const unsigned int m_correctlyPlaced;
	const unsigned int m_misplaced;
};

#endif