#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "MastermindSolver.h"

void asciiTestCases();
void unicodeTestCases();

int main() {
	asciiTestCases();
	unicodeTestCases();

	std::cout << "\nDone" << std::endl << std::endl;
	char c;
	std::cin >> c;

	return 0;
}

template<typename T>
void confirmEqual(std::vector<T> expected, const std::vector<T>& actual)
{
	bool identical = true;
	if (expected.size() == actual.size()) {
		for (size_t i = 0; identical && i < expected.size(); ++i) {
			identical = (expected[i] == actual[i]);
		}
	}

	if (!identical) {
		throw "Test case failed";
	}
}

template<typename T>
void printVector(std::ostream& out, std::vector<T> vec) {
	out << '{';
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(out, ", "));
	out << '}';
}

void asciiTestCases()
{
	MastermindSolver numberSolver("0123456789");

	std::vector<MastermindResult> results = {
		MastermindResult::builder().setGuess("1356").build(),
		MastermindResult::builder().setGuess("2586").setMisplaced(2).build(),
		MastermindResult::builder().setGuess("8307").setMisplaced(1).build(),
		MastermindResult::builder().setGuess("8916").setMisplaced(1).setCorrectlyPlaced(1).build(),
	};

	confirmEqual(std::vector<std::string>{ "4928", "9928" }, numberSolver.solutions(results));
}

void unicodeTestCases()
{
	MastermindSolverW colorSolver(L"RYVGOPWC");

	std::vector<MastermindResultW> results = {
		MastermindResultW::builder().setGuess(L"POYGO").setMisplaced(1).setCorrectlyPlaced(1).build(),
		MastermindResultW::builder().setGuess(L"CRCPW").setMisplaced(3).build(),
		MastermindResultW::builder().setGuess(L"ORPRR").setMisplaced(3).build(),
		MastermindResultW::builder().setGuess(L"PPVWO").setMisplaced(3).build(),
		MastermindResultW::builder().setGuess(L"YRCOY").setMisplaced(3).build(),
	};

	confirmEqual(std::vector<std::wstring>{ L"VORCP" }, colorSolver.solutions(results));
}