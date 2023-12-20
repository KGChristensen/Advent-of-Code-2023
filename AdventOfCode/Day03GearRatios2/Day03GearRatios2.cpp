// Day03GearRatios2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

constexpr static void findAdjacentGear(std::map<std::string, std::vector<int>> &gears, const std::string chrline, std::string number, size_t idx_outer, size_t idx_inner) {

	idx_inner = idx_inner == -1ULL ? 0 : idx_inner;

	size_t idx = 0;
	for (auto chr : chrline) {
		if (chr == '*') {
			const std::string ind = std::to_string(idx_outer) + "-" + std::to_string(idx_inner + idx);

			if (gears.find(ind) == gears.end()) {
				gears.insert(std::pair<std::string, std::vector<int>>(ind, std::vector<int>{stoi(number)}));
			}
			else {
				gears[ind].push_back(stoi(number));
			}

		}
		idx++;
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;

	int sum_of_all_of_the_part_numbers = 0;
	std::vector<std::string> allengineschematic;
	std::map<std::string, std::vector<int>> allgears;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {

		allengineschematic.push_back(line + ".");

	}

	const size_t schematicrows = allengineschematic.size();
	const size_t schematiccols = allengineschematic[0].length();

	for (size_t idx_outer = 0; idx_outer < schematicrows; idx_outer++) {
		for (size_t idx_inner = 0; idx_inner < schematiccols; idx_inner++) {
			char chr = allengineschematic[idx_outer][idx_inner];

			if (chr < '0' || chr > '9') {
				continue;
			}

			std::string number = { chr };

			while (++idx_inner < schematiccols) {
				chr = allengineschematic[idx_outer][idx_inner];
				if (chr >= '0' && chr <= '9') {
					number += chr;
				}
				else {
					break;
				}

			}

			// Vertical (top to bottom)
			size_t startVerIdx = (idx_outer == 0 ? 0 : idx_outer - 1);
			size_t endVerIdx = (idx_outer == schematicrows - 1 ? idx_outer : idx_outer + 1);

			// Horizontal (left to right)
			size_t startHozIdx = (idx_inner - number.length()) == 0 ? 0 : (idx_inner - number.length() - 1); //std::max(0, idx_inner - number.length() - 1));
			size_t endHozIdx = (idx_inner + 1 == schematiccols) ? idx_inner : idx_inner + 1;

			//std::cout << number << "(row: " << idx_outer << ", cols: " << idx_inner << ")\n";

			std::string top = (idx_outer == startVerIdx) ? "" : allengineschematic[startVerIdx].substr(startHozIdx, endHozIdx - startHozIdx);
			std::string bottom = (idx_outer == endVerIdx) ? "" : allengineschematic[endVerIdx].substr(startHozIdx, endHozIdx - startHozIdx);
			std::string left = (idx_inner - number.length()) == 0 ? "" : allengineschematic[idx_outer].substr(startHozIdx, 1);
			std::string right = (idx_inner + 1 == allengineschematic[idx_outer].length()) ? "" : allengineschematic[idx_outer].substr(endHozIdx - 1, 1);

			findAdjacentGear(allgears, top, number, idx_outer - 1, idx_inner - number.length() - 1);
			findAdjacentGear(allgears, bottom, number, idx_outer + 1, idx_inner - number.length() - 1);
			findAdjacentGear(allgears, left, number, idx_outer, idx_inner - number.length() - 1);
			findAdjacentGear(allgears, right, number, idx_outer, idx_inner);


		}
	}

	std::for_each(allgears.begin(), allgears.end(), [&sum_of_all_of_the_part_numbers](std::pair<std::string, std::vector<int>> gear_pair) {
		sum_of_all_of_the_part_numbers += gear_pair.second.size() == 2 ? std::accumulate(gear_pair.second.begin(), gear_pair.second.end(), 1, std::multiplies<int>()) : 0;
		});

	std::cout << "Sum of all of the part numbers: " << sum_of_all_of_the_part_numbers << "\n";

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
