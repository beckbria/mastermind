#include <algorithm>
#include <stack>
#include <utility>
#include "MastermindResult.h"

bool MastermindResult::matches(const std::string& answer) const {
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

std::unordered_map<std::string::value_type, unsigned int> MastermindResult::countCharacters(const std::string& str) {
	std::unordered_map<std::string::value_type, unsigned int> seen;
	for (auto c : str) {
		auto it = seen.find(c);
		if (it == seen.end()) {
			seen[c] = 1;
		} else {
			it->second++;
		}
	}

	return seen;
}

MastermindResult MastermindResult::Builder::build() {
	if (m_guess.size() < 1) {
		throw "Guess is required";
	}
	return MastermindResult(m_guess, m_placed, m_misplaced);
}

MastermindResult::Builder& MastermindResult::Builder::setGuess(std::string&& guess) {
	m_guess = std::forward<std::string>(guess);
	return *this;
}

MastermindResult::Builder& MastermindResult::Builder::setCorrectlyPlaced(unsigned int placed) {
	m_placed = placed;
	return *this;
}

MastermindResult::Builder& MastermindResult::Builder::setMisplaced(unsigned int misplaced) {
	m_misplaced = misplaced;
	return *this;
}