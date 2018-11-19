#ifndef MASTERMINDSOLVER_H
#define MASTERMINDSOLVER_H

#include <string>
#include <type_traits>
#include <vector>
#include "MastermindResult.h"

class MastermindSolver {
public:
	// Takes the list of all characters potentially in the solution
	MastermindSolver(std::string&& characterSet);

	// Given a set of known results, provides all possible solutions that match those constraints
	std::vector<std::string> solutions(const std::vector<MastermindResult>& knownResults);

private:
	void findSolutions(const std::vector<MastermindResult>& knownResults, size_t length, size_t position, std::string& candidate, std::vector<std::string>& solutions);

	std::string m_characterSet;
};

#endif
