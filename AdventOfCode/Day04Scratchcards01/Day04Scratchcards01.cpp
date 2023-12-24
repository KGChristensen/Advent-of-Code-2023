// Day04Scratchcards01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if defined(__GNUC__) ||defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wc++98-compat-pedantic"
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <queue>
#include <map>
#include <numeric>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	int pointsWorthInTotal = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {
		int points = 0;

		size_t start_idx = line.find_first_of(':') + 2;
		size_t middle_idx = line.find_first_of('|') - 1;

		std::stringstream winningNumbers(line.substr(start_idx, middle_idx - start_idx));
		std::string winingNumber;

		//std::cout << "|" << line.substr(start_idx, middle_idx - start_idx) << "|\n";

		std::stringstream numbersIHave(line.substr(middle_idx + 3, line.length() - middle_idx));
		std::string numberIHave;

		//std::cout << "|" << line.substr(middle_idx + 3, line.length() - middle_idx) << "|\n";


		std::vector<int> iNumbersIHave = {};

		while (numbersIHave >> numberIHave) {
			iNumbersIHave.push_back(stoi(numberIHave));
		}

		//std::vector<int> iWinningNumbers = {};

		//while (winningNumbers >> winingNumber) {
		//	iWinningNumbers.push_back(stoi(winingNumber));
		//}

		//for (auto iNumberIHave : iNumbersIHave)
		//{
		//	if (std::find(iWinningNumbers.begin(), iWinningNumbers.end(), iNumberIHave) != iWinningNumbers.end()) {
		//		points = (points == 0) ? 1 : points * 2;
		//		std::cout << "Hit: " << iNumberIHave << "\n";
		//	}
		//}

		while (winningNumbers >> winingNumber) {
			int number = stoi(winingNumber);

			if (std::find(iNumbersIHave.begin(), iNumbersIHave.end(), number) != iNumbersIHave.end()) {
				points = (points == 0) ? 1 : points * 2;
				//std::cout << "Hit: " << number << "\n";
			}
		}

		pointsWorthInTotal += points;


	}



	std::cout << "Points worth in total: " << pointsWorthInTotal << "\n";

	inputfile.close();

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Time taken by function: "
		<< duration.count() << " microseconds\n";

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
