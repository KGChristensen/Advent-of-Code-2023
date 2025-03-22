// Day7CamelCards1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

size_t determineType(const std::string& hand) {
	std::map<char, int> mapHand;
	for (char c : hand) {
		mapHand[c]++;
	}

	size_t typeHand = mapHand.size() * 2;

	// Full house or four of a kind
	if (typeHand == 4 && std::any_of(mapHand.begin(), mapHand.end(), [](const auto& elm) { return elm.second == 4; })) {
		typeHand -= 1;
	}
	// Three of a kind or two pair
	if (typeHand == 6 && std::any_of(mapHand.begin(), mapHand.end(), [](const auto& elm) { return elm.second == 3; })) {
		typeHand -= 1;
	}

	return typeHand;
}

int translateStrength(char c) {
	if (c == 'A') return 1;
	if (c == 'K') return 2;
	if (c == 'Q') return 3;
	if (c == 'J') return 4;
	if (c == 'T') return 5;
	return 15 - (c - '0');
}

bool determinesStrength(const std::pair<size_t, std::pair<std::string, int>>& lhs,
	const std::pair<size_t, std::pair<std::string, int>>& rhs) {
	if (lhs.first == rhs.first) {
		for (size_t chId = 0; chId < lhs.second.first.size(); ++chId) {
			if (lhs.second.first[chId] != rhs.second.first[chId]) {
				return translateStrength(lhs.second.first[chId]) < translateStrength(rhs.second.first[chId]);
			}
		}
	}
	return lhs.first < rhs.first;
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long long results = 0;

	// int = type, string = cards, int = bids

	std::vector<std::pair<size_t,std::pair<std::string, int>>> hands;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {
		std::string cards = line.substr(0, 5);
		int bids = std::stoi(line.substr(6)); // Directly use fixed index for the bid
		hands.emplace_back(determineType(cards), std::make_pair(cards, bids));
	}

	// Use a lambda for sorting
	std::sort(hands.begin(), hands.end(), determinesStrength);

	size_t id = hands.size();
	for (const auto& hand : hands) {
		results += static_cast<long long>(hand.second.second) * id;
		--id;
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
