// Day05IfYouGiveASeedAFertilizer1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	std::vector<unsigned long int> allSeeds;
	std::vector<std::vector<unsigned long int>> maps;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::getline(inputfile, line);

	std::stringstream seeds(line.substr(7, line.length() - 7));
	std::string seed;

	while (seeds >> seed) {
		allSeeds.push_back(std::strtoul(seed.c_str(), nullptr, 0));
	}

	std::getline(inputfile, line);

	while (std::getline(inputfile, line)) {

		if (line[0] > 'a' && line[0] < 'z') {

			maps.push_back(std::vector<unsigned long int>());
			while (std::getline(inputfile, line) && (line[0] >= '0' && line[0] <= '9')) {

				std::stringstream values(line);
				std::string value;
				while (values >> value) {
					maps[maps.size() - 1].push_back(std::strtoul(value.c_str(), nullptr, 0));
				}
			}
			// Finished parsing map

			for (size_t seedIdx = 0; seedIdx < allSeeds.size(); seedIdx++) {
				
				unsigned long int curSeed = allSeeds[seedIdx];

				size_t curMapSize = maps[maps.size() - 1].size();
				bool changed = false;
				for (size_t idx = 0; (idx < curMapSize) && !changed; idx += 3) {
					unsigned long int endRange = maps[maps.size() - 1][idx];
					unsigned long int startRange = maps[maps.size() - 1][idx + 1];
					unsigned long int range = maps[maps.size() - 1][idx + 2];

					if (curSeed >= startRange && curSeed <= (startRange + range)) {

						allSeeds[seedIdx] = endRange - startRange + curSeed;
						changed = true;
					}

				}

			}

		}

	}

	std::cout << "Lowest location number: " << *std::min_element(allSeeds.begin(), allSeeds.end()) << "\n";

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
