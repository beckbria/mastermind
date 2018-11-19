#ifndef MASTERMINDRESULT_H
#define MASTERMINDRESULT_H

#include <string>
#include <unordered_map>

/**
 MastermindResult represents the outcome of a guess in the game mastermind.
 Given the result of a guess, it can determine if that outcome was consistent
 with a theoretical answer.  This can be used to solve Mastermind puzzles:
 https://puzzlephil.com/puzzles/mastermind/en/
 */
class MastermindResult {
public:
	class Builder {
	public:
		MastermindResult build();
		Builder& setGuess(std::string&& guess);
		Builder& setCorrectlyPlaced(unsigned int placed);
		Builder& setMisplaced(unsigned int misplaced);

	private:
		std::string m_guess = "";
		unsigned int m_placed = 0;
		unsigned int m_misplaced = 0;
	};
	static Builder builder() { return Builder(); }

	bool matches(const std::string& answer) const;
	size_t size() const { return m_guess.size(); }

private:
	MastermindResult(const std::string& guess, unsigned int placed, unsigned int misplaced)
		: m_guess(guess),
			m_guessCounts(countCharacters(m_guess)),
			m_correctlyPlaced(placed),
			m_misplaced(misplaced) {}

	static std::unordered_map<std::string::value_type, unsigned int> countCharacters(const std::string& str);

	const std::string m_guess;
	const std::unordered_map<std::string::value_type, unsigned int> m_guessCounts;
	unsigned int m_digitCount[10] = {};
	const unsigned int m_correctlyPlaced;
	const unsigned int m_misplaced;
};

#endif