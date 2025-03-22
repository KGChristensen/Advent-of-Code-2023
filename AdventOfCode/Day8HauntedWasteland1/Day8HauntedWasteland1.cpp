// Day8HauntedWasteland1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <tuple>
#include <unordered_map>
#include <memory>

class BinaryGraphNode {
public:
    std::string value;
    std::shared_ptr<BinaryGraphNode> left = nullptr;
    std::shared_ptr<BinaryGraphNode> right = nullptr;

    BinaryGraphNode(const std::string& val) : value(val), left(nullptr), right(nullptr) {}
};

class BinaryGraph {
public:
    std::unordered_map<std::string, std::shared_ptr<BinaryGraphNode>> nodeMap;

    void addNode(const std::string& parent, const std::string& leftChild, const std::string& rightChild) {
        if (nodeMap.find(parent) == nodeMap.end()) {
            nodeMap[parent] = std::make_shared<BinaryGraphNode>(parent);
            nodeMap[parent]->left = nullptr;
            nodeMap[parent]->right = nullptr;
        }
        if (nodeMap.find(leftChild) == nodeMap.end()) {
            nodeMap[leftChild] = std::make_shared<BinaryGraphNode>(leftChild);
            nodeMap[leftChild]->left = nullptr;
            nodeMap[leftChild]->right = nullptr;
        }
        if (nodeMap.find(rightChild) == nodeMap.end()) {
            nodeMap[rightChild] = std::make_shared<BinaryGraphNode>(rightChild);
            nodeMap[rightChild]->left = nullptr;
            nodeMap[rightChild]->right = nullptr;
        }

        nodeMap[parent]->left = nodeMap[leftChild];
        nodeMap[parent]->right = nodeMap[rightChild];
    }

    void traverseWithRepeatedInstructions(const std::string& startNode, const std::string& instructions, const std::string& targetValue) {
        if (nodeMap.find(startNode) == nodeMap.end()) {
            std::cout << "Start node not found!" << std::endl;
            return;
        }

        auto current = nodeMap[startNode];
        int steps = 0;

        //std::cout << "Following instructions: " << instructions << std::endl;

        while (current != nullptr && current->value != targetValue) {
            for (char dir : instructions) {
                if (!current) {
                    std::cout << "Reached a null node. Path ended!" << std::endl;
                    return;
                }

                steps++;
                //std::cout << "Step " << steps << ": Move " << (dir == 'L' ? "Left" : "Right") << " -> ";

                current = (dir == 'L' || dir == 'l') ? current->left : current->right;

                if (current) {
                    //std::cout << "Current node value: " << current->value << std::endl;
                    if (current->value == targetValue) {
                        std::cout << "Target node " << targetValue << " reached in " << steps << " steps!" << std::endl;

                        for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
							it->second->left = nullptr;
							it->second->right = nullptr;
                        }

                        return;
                    }
                }
                else {
                    std::cout << "Reached a null node. Path ended!" << std::endl;
                    return;
                }
            }
        }
    }
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long results = 0;
	std::string instructions;
	//std::set<BinaryGraphNode*> nodes;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::getline(inputfile, instructions);

	std::getline(inputfile, line);

    BinaryGraph graph;

	while (std::getline(inputfile, line)) {

		std::string parent = line.substr(0, 3);

		std::string leftChild = line.substr(7, 3);
		std::string rightChild = line.substr(12,3);

		//std::cout << "Node: >" << node << "< Left: >" << leftEdge << "< Right: >" << rightEdge << "<\n";
        graph.addNode(parent, leftChild, rightChild);

	}

    graph.traverseWithRepeatedInstructions("AAA", instructions, "ZZZ");

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
