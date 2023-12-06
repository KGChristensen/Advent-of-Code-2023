// Day01Trebuchet1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	long long sum = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {

		std::string calibration_value = "";
		for (const char ch : line) {
			if (ch > '0' && ch <= '9') {
				calibration_value += ch;
			}
		}

		/*if (calibration_value.length() > 0) {
			auto chr_start = calibration_value[0];
			auto chr_end = calibration_value[calibration_value.length() - 1];

			int int_start = (chr_start-'0');
			int int_end = (chr_end-'0');

			sum += (int_start * 10) + int_end;

		}*/
		//std::cout << calibration_value << "\n";
		//sum += calibration_value;
		sum += (calibration_value.length() > 0 ? ((calibration_value[0]-'0')*10)+(calibration_value[calibration_value.length() - 1]-'0') : 0);
	}

	std::cout << "Sum: " << sum << "\n";

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
