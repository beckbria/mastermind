#include <algorithm>
#include <stack>
#include "MastermindResult.h"

bool MastermindResult::matches(unsigned int answer) {
	auto answerDigits = splitToDigits(answer, m_guessDigits.size());
	auto answerDigitCounts = countDigits(answerDigits);

	unsigned int exactMatches = 0;
	unsigned int misplacedMatches = 0;

	// Step 1: Count all partial matches
	for (size_t i = 0; i < m_guessDigitCount.size(); ++i) {
		unsigned int matches = std::min(m_guessDigitCount[i], answerDigitCounts[i]);
		misplacedMatches += matches;
	}

	// Step 2: Count all exact matches and subtract them from partial matches
	for (size_t i = 0; i < m_guessDigits.size(); ++i) {
		if (answerDigits[i] == m_guessDigits[i]) {
			++exactMatches;
			--misplacedMatches;
		}
	}

	return (m_misplaced == misplacedMatches) && (m_correctlyPlaced == exactMatches);
}

std::vector<unsigned int> MastermindResult::splitToDigits(unsigned int n, unsigned int length) {
	std::stack<unsigned int> digits;
	while (n > 0) {
		digits.push(n % 10);
		n /= 10;
	}
	if (digits.size() > length) {
		throw "Provided number larger than requested length";
	}
	while (digits.size() < length) {
		digits.push(0);
	}

	std::vector<unsigned int> orderedDigits;
	orderedDigits.resize(digits.size());
	auto it = orderedDigits.begin();
	while (!digits.empty()) {
		*it++ = digits.top();
		digits.pop();
	}
	return orderedDigits;
}

std::vector<unsigned int> MastermindResult::countDigits(const std::vector<unsigned int>& digits) {
	std::vector<unsigned int> count(10, 0);
	for (unsigned int i : digits) ++count[i];
	return count;
}

MastermindResult MastermindResult::MastermindResultBuilder::build() {
	if (!m_hasGuess) {
		throw "Guess is required";
	}
	return MastermindResult(m_guess, m_length, m_placed, m_misplaced);
}

MastermindResult::MastermindResultBuilder& MastermindResult::MastermindResultBuilder::setGuess(unsigned int guess) {
	m_guess = guess;
	m_hasGuess = true;
	return *this;
}

MastermindResult::MastermindResultBuilder& MastermindResult::MastermindResultBuilder::setLength(unsigned int length) {
	m_length = length;
	return *this;
}

MastermindResult::MastermindResultBuilder& MastermindResult::MastermindResultBuilder::setCorrectlyPlaced(unsigned int placed) {
	m_placed = placed;
	return *this;
}

MastermindResult::MastermindResultBuilder& MastermindResult::MastermindResultBuilder::setMisplaced(unsigned int misplaced) {
	m_misplaced = misplaced;
	return *this;
}