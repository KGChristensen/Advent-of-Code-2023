// Day02CubeConundrum2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	int sum_of_the_power_of_sets = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {
		std::stringstream record(line);
		std::string split;
		std::string subset_of_cube;
		std::vector<int> rgb = { 0, 0, 0 };

		getline(record, split, ':');

		//int gameid = stoi(split.substr(5, split.length() - 5));

		getline(record, split, ':');

		std::stringstream subsets_of_cubes(split);

		while (getline(subsets_of_cubes, subset_of_cube, ';')) {

			std::string rgbs;
			std::stringstream cube(subset_of_cube);
			while (getline(cube, rgbs, ',')) {

				rgb[0] = rgbs.find("red") != std::string::npos ? std::max(rgb[0], stoi(rgbs.substr(0, rgbs.find("red") - 1))) : rgb[0];
				rgb[1] = rgbs.find("green") != std::string::npos ? std::max(rgb[1], stoi(rgbs.substr(0, rgbs.find("green") - 1))) : rgb[1];
				rgb[2] = rgbs.find("blue") != std::string::npos ? std::max(rgb[2], stoi(rgbs.substr(0, rgbs.find("blue") - 1))) : rgb[2];
			}
		}

		sum_of_the_power_of_sets += rgb[0]*rgb[1]*rgb[2];

	}

	std::cout << "Sum of IDS: " << sum_of_the_power_of_sets << "\n";

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
