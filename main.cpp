#include <iostream>
#include <vector>
#include "MastermindResult.h"

int main() {
	std::vector<MastermindResult> results = {
		MastermindResult::builder().setGuess(1356).build(),
		MastermindResult::builder().setGuess(2586).setMisplaced(2).build(),
		MastermindResult::builder().setGuess(8307).setMisplaced(1).build(),
		MastermindResult::builder().setGuess(8916).setMisplaced(1).setCorrectlyPlaced(1).build(),
	};

	for (unsigned int i = 0; i < 10000; ++i) {
		bool matched = true;
		for (auto &r : results) {
			matched = r.matches(i);
			if (!matched) break;
		}

		if (matched) std::cout << i << std::endl;
	}

	std::cout << "\nDone" << std::endl << std::endl;
	char c;
	std::cin >> c;

	return 0;
}