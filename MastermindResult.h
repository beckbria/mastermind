#ifndef MASTERMINDRESULT_H
#define MASTERMINDRESULT_H

#include <algorithm>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>

/**
 MastermindResult represents the outcome of a guess in the game mastermind.
 Given the result of a guess, it can determine if that outcome was consistent
 with a theoretical answer.  This can be used to solve Mastermind puzzles:
 https://puzzlephil.com/puzzles/mastermind/en/
 */
template<typename T>
class MastermindResultBase {
public:
	class Builder {
	public:
		MastermindResultBase<T> build() {
			if (m_guess.size() < 1) {
				throw "Guess is required";
			}
			return MastermindResultBase(m_guess, m_placed, m_misplaced);
		}

		Builder& setGuess(std::basic_string<T>&& guess) {
			m_guess = std::forward<std::basic_string<T>>(guess);
			return *this;
		}

		Builder& setGuess(const std::basic_string<T>& guess) {
			m_guess = guess;
			return *this;
		}

		Builder& setCorrectlyPlaced(unsigned int placed) {
			m_placed = placed;
			return *this;
		}

		Builder& setMisplaced(unsigned int misplaced) {
			m_misplaced = misplaced;
			return *this;
		}

	private:
		std::basic_string<T> m_guess;
		unsigned int m_placed = 0;
		unsigned int m_misplaced = 0;
	};
	static Builder builder() { return Builder(); }

	bool matches(const std::basic_string<T>& answer) const {
		if (answer.size() != m_guess.size()) throw "Incompatible candidate length";

		auto answerCounts = countCharacters(answer);

		unsigned int exactMatches = 0;
		unsigned int misplacedMatches = 0;

		// Step 1: Count all partial matches
		for (const auto& answerChar : answerCounts) {
			auto it = m_guessCounts.find(answerChar.first);
			const unsigned int guessCount = (it == m_guessCounts.end()) ? 0 : it->second;
			const unsigned int matches = std::min(guessCount, answerChar.second);
			misplacedMatches += matches;
		}

		// Step 2: Count all exact matches and subtract them from partial matches
		for (size_t i = 0; i < m_guess.size(); ++i) {
			if (answer[i] == m_guess[i]) {
				++exactMatches;
				--misplacedMatches;
			}
		}

		return (m_misplaced == misplacedMatches) && (m_correctlyPlaced == exactMatches);
	}

	size_t size() const { return m_guess.size(); }

private:
	MastermindResultBase(const std::basic_string<T>& guess, unsigned int placed, unsigned int misplaced)
		: m_guess(guess),
			m_guessCounts(countCharacters(m_guess)),
			m_correctlyPlaced(placed),
			m_misplaced(misplaced) {}

	static std::unordered_map<T, unsigned int> countCharacters(const std::basic_string<T>& str) {
		std::unordered_map<T, unsigned int> seen;
		for (auto c : str) {
			auto it = seen.find(c);
			if (it == seen.end()) {
				seen[c] = 1;
			}
			else {
				it->second++;
			}
		}

		return seen;
	}

	const std::basic_string<T> m_guess;
	const std::unordered_map<T, unsigned int> m_guessCounts;
	const unsigned int m_correctlyPlaced;
	const unsigned int m_misplaced;
};

typedef MastermindResultBase<char> MastermindResult;
typedef MastermindResultBase<wchar_t> MastermindResultW;

#endif