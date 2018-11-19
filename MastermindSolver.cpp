#include "MastermindSolver.h"

#include <unordered_set>
#include <utility>

MastermindSolver::MastermindSolver(std::string&& characterSet)
{
	m_characterSet = std::forward<std::string>(characterSet);
	if (m_characterSet.size() < 1) throw "Empty character set";

	// Ensure that each character in the input is unique
	std::unordered_set<std::string::value_type> seen;
	for (std::string::value_type c : m_characterSet) {
		auto result = seen.insert(c);
		if (!result.second) {
			throw "Duplicate characters in character set";
		}
	}	
}

std::vector<std::string> MastermindSolver::solutions(const std::vector<MastermindResult>& knownResults)
{
	std::vector<std::string> solutionsFound;
	if (knownResults.size() < 1) {
		return solutionsFound;
	}

	size_t length = knownResults[0].size();
	// Ensure that all rules are consistently sized
	for (auto& r : knownResults) {
		if (r.size() != length) throw "Inconsistent rule set";
	}

	std::string candidate(length, m_characterSet[0]);
	findSolutions(knownResults, length, 0, candidate, solutionsFound);
	return solutionsFound;
}

// Recursively fill in the candidate string to generate all possibilities and check them
void MastermindSolver::findSolutions(
	const std::vector<MastermindResult>& knownResults,
	size_t length,
	size_t position,
	std::string& candidate,
	std::vector<std::string>& solutions)
{
	for (auto c : m_characterSet) {
		candidate[position] = c;
		if (position == (length - 1)) {
			// Check the candidate against the rules
			bool matchesAll = true;
			for (const auto &result : knownResults) {
				matchesAll = result.matches(candidate);
				if (!matchesAll) break;
			}
			if (matchesAll) solutions.push_back(candidate);
		} else {
			// Continue filling in characters
			findSolutions(knownResults, length, position + 1, candidate, solutions);
		}
	}
}