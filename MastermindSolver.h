#ifndef MASTERMINDSOLVER_H
#define MASTERMINDSOLVER_H

#include <string>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>
#include "MastermindResult.h"

template<class T>
class MastermindSolverBase {
public:
	// Takes the list of all characters potentially in the solution
	MastermindSolverBase(std::basic_string<T>&& characterSet) {
		m_characterSet = std::forward<std::basic_string<T>>(characterSet);
		if (m_characterSet.size() < 1) throw "Empty character set";

		// Ensure that each character in the input is unique
		std::unordered_set<T> seen;
		for (auto c : m_characterSet) {
			auto result = seen.insert(c);
			if (!result.second) {
				throw "Duplicate characters in character set";
			}
		}
	}

	// Given a set of known results, provides all possible solutions that match those constraints
	std::vector<std::basic_string<T>> solutions(const std::vector<MastermindResultBase<T>>& knownResults) {
		std::vector<std::basic_string<T>> solutionsFound;
		if (knownResults.size() < 1) {
			return solutionsFound;
		}

		size_t length = knownResults[0].size();
		// Ensure that all rules are consistently sized
		for (auto& r : knownResults) {
			if (r.size() != length) throw "Inconsistent rule set";
		}

		std::basic_string<T> candidate(length, m_characterSet[0]);
		findSolutions(knownResults, length, 0, candidate, solutionsFound);
		return solutionsFound;
	}

private:
	void findSolutions(
		const std::vector<MastermindResultBase<T>>& knownResults,
		size_t length,
		size_t position,
		std::basic_string<T>& candidate,
		std::vector<std::basic_string<T>>& solutions) {
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
			}
			else {
				// Continue filling in characters
				findSolutions(knownResults, length, position + 1, candidate, solutions);
			}
		}
	}

	std::basic_string<T> m_characterSet;
};

typedef MastermindSolverBase<char> MastermindSolver;
typedef MastermindSolverBase<wchar_t> MastermindSolverW;

#endif
