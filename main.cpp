#include <iostream>
#include <vector>
#include "MastermindSolver.h"

int main() {
	MastermindSolver solver("0123456789");

	std::vector<MastermindResult> results = {
		MastermindResult::builder().setGuess("1356").build(),
		MastermindResult::builder().setGuess("2586").setMisplaced(2).build(),
		MastermindResult::builder().setGuess("8307").setMisplaced(1).build(),
		MastermindResult::builder().setGuess("8916").setMisplaced(1).setCorrectlyPlaced(1).build(),
	};

	for (const auto& result : solver.solutions(results)) {
		std::cout << result << std::endl;
	}

	std::cout << "\nDone" << std::endl << std::endl;
	char c;
	std::cin >> c;

	return 0;
}