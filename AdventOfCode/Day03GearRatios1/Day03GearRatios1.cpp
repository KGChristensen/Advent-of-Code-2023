// Day03GearRatios1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;

	int sum_of_all_of_the_part_numbers = 0;
	std::vector<std::string> allengineschematic;


	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {


		allengineschematic.push_back(line + ".");


		//int line_len = line.length();
		//std::string number = "";
		//int idx_inner = 0;
		//for (auto chr : line) {
		//	
		//	if (chr >= '0' && chr <= '9') {
		//		number += chr;
		//	}
		//	else if (chr != '.') {
		//		//std::cout << chr << "\n";
		//	} else {
		//		// reset number

		//		std::cout << number << "\n";



		//		number = "";
		//		
		//	}
		//	idx_inner++;
		//}


	}

	for (size_t idx_outer = 0; idx_outer < allengineschematic.size(); idx_outer++) {
		//std::cout << allengineschematic[idx_outer] << "\n";

		std::string number = "";
		size_t idx_inner = 0;
		for (auto chr : allengineschematic[idx_outer]) {
			//std::cout << idx_inner << "=" << allengineschematic[idx_outer].length() << " - " << number << "\n";
			if (chr >= '0' && chr <= '9') {
				number += chr;

			}

			if (number.length() > 0 && ((chr < '0' || chr > '9') || (idx_inner == allengineschematic[idx_outer].length() - 1))) {
				// reset number

				//std::cout << number; // << "\n";

				// Check boundaries

				// Vertical (top to bottom)
				size_t startVerIdx = (idx_outer == 0 ? 0 : idx_outer - 1);
				size_t endVerIdx = (idx_outer == allengineschematic.size() - 1 ? idx_outer : idx_outer + 1);

				// Horizontal (left to right)
				size_t startHozIdx = (idx_inner - number.length()) == 0 ? 0 : (idx_inner - number.length() - 1); //std::max(0, idx_inner - number.length() - 1));
				size_t endHozIdx = (idx_inner == allengineschematic[idx_outer].length()) ? idx_inner : idx_inner + 1;


				bool adjacent_to_a_symbol = false;
				for (size_t vIdx = startVerIdx; vIdx <= endVerIdx; vIdx++) {
					std::string l = allengineschematic[vIdx];
					for (size_t hIdx = startHozIdx; hIdx < endHozIdx; hIdx++) {
						if (l[hIdx] != '.' && (l[hIdx] < '0' || l[hIdx] > '9')) {
							if (number.size() > 0) {
								//								std::cout << "|" << number << "|";
								//								std::cout << "\n";

								adjacent_to_a_symbol = true;

							}
						}
					}
				}

				if (adjacent_to_a_symbol) {
					sum_of_all_of_the_part_numbers += stoi(number);
				}

				number = "";
			}

			//std::cout << idx_inner << "=" << allengineschematic[idx_outer].length() << "\n";
			idx_inner++;
		}

	}

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
