// Day8HauntedWasteland2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Great thanks to https://www.youtube.com/watch?v=8ZJRJHEsXPQ&ab_channel=BradleySward


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
#include <tuple>
#include <unordered_map>
#include <memory>

class BinaryGraphNode {
public:
    //
    BinaryGraphNode(const std::string& _value = "", const std::string& _left = "",
        const std::string& _right = "");
    std::string value;
    std::string left;
    std::string right;
    
};

BinaryGraphNode::BinaryGraphNode(const std::string& _value, const std::string& _left,
    const std::string& _right)
    : value(_value), left(_left), right(_right) {
}

class BinaryGraph {
public:
    std::map<std::string, BinaryGraphNode> tree;
    std::string Order;

    BinaryGraph() {
    }

	void Instructions(std::string& instructions) {
		Order = instructions;
	}

    void Insert(std::string& parent, std::string& leftEdge, std::string& rightEdge) {
        tree.insert(std::pair<std::string, BinaryGraphNode>(parent, BinaryGraphNode(parent, leftEdge, rightEdge)));
    }

    long long Navigate() {
        std::vector<BinaryGraphNode> current;

        for (std::pair<std::string, BinaryGraphNode> p : tree)
            if (p.first[2] == 'A') current.push_back(p.second);

        std::vector<long long> answers;

        for (BinaryGraphNode& n : current) {
            std::string O = Order;
            int Moves = 0;

            while (true) {
                ++Moves;
                if (O[0] == 'L')
                    n = tree[n.left];
                else if (O[0] == 'R')
                    n = tree[n.right];
                if (n.value[2] == 'Z') {
                    answers.push_back(Moves);
                    break;
                }
                O = O.substr(1, O.size() - 1) + O[0];
            }
        }

        long long answer = answers[0];
        for (long long a : answers) answer = std::_Lcm(answer, a);
        return answer;
    }
};


int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto start = std::chrono::high_resolution_clock::now();

    std::string line;
    std::string instructions;

    std::ifstream inputfile("input.txt");

    if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

    std::getline(inputfile, instructions);

    std::getline(inputfile, line);

    BinaryGraph graph;

	graph.Instructions(instructions);

    while (std::getline(inputfile, line)) {

        std::string parent = line.substr(0, 3);

        std::string leftChild = line.substr(7, 3);
        std::string rightChild = line.substr(12, 3);

        graph.Insert(parent, leftChild, rightChild); 
    }

    std::cout << "Result: " << graph.Navigate() << "\n";

    inputfile.close();

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
