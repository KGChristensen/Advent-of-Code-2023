// Day06WaitForIt2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if defined(__GNUC__) ||defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wc++98-compat-pedantic"
#endif

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <algorithm>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long long results = 1;
	std::vector<long long> races;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	bool continueRead = false;

	while (std::getline(inputfile, line)) {
		std::string strNumber = "";
		for (size_t chId = 0; chId <= line.size(); chId++) {
			char ch = line[chId];
			if ((ch >= '0' && ch <= '9') || continueRead) {
				if (ch!=' ')
					strNumber += ch;
				continueRead = true;
				if (ch == '\0')
					continueRead = false;
			}
			//else {

			//	if (strNumber.size() > 0) {
			//		races.emplace_back(std::stoi(strNumber));
			//	}

			//	strNumber.clear();
			//}

		}
		races.emplace_back(std::stoll(strNumber));
	}

	size_t racesSize = (races.size() / 2);

	for (size_t rId = 0; rId < racesSize; rId++) {

		long long ways = 0;

		long long time = races[rId];
		long long distance = races[rId + racesSize];

		for (long long holdButton = 1; holdButton <= time; holdButton++) {
			long long traveled = (time - holdButton) * holdButton;
			//std::cout << "Time: " << time << ", Hold: " << holdButton << ", Traveled: " << traveled << "\n";

			ways = traveled > distance ? ways + 1 : ways;

		}

		results *= ways;

	}

	inputfile.close();

	std::cout << "Results: " << results << "\n";

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

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
