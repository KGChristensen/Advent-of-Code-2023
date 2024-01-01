// Day05IfYouGiveASeedAFertilizer2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Big thanks to HappyCerberus / aoc - 2023 - cpp - solutions :-)
// 
// https://github.com/HappyCerberus/aoc-2023-cpp-solutions/tree/main/aoc2023/day05
//

#if defined(__GNUC__) ||defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wc++98-compat-pedantic"
#endif

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <chrono>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <numeric>
#include <ranges>
#include <span>
#include <spanstream>

struct Range {
	unsigned long int input_offset;
	unsigned long int output_offset;
	unsigned long int size;
	bool operator<(const Range& other) const {
		return input_offset < other.input_offset;
	}
	friend std::istream& operator>>(std::istream& s, Range& rng) {
		return s >> rng.output_offset >> rng.input_offset >> rng.size;
	}
};

struct SeedRange {
	unsigned long int start;
	unsigned long int size;
	bool operator<(const SeedRange& other) const { return start < other.start; }
	friend std::istream& operator>>(std::istream& s, SeedRange& rng) {
		return s >> rng.start >> rng.size;
	}
};

struct Mapper {
	std::vector<SeedRange> seeds;
	std::vector<Range> seed_to_soil;
	std::vector<Range> soil_to_fertilizer;
	std::vector<Range> fertilizer_to_water;
	std::vector<Range> water_to_light;
	std::vector<Range> light_to_temperature;
	std::vector<Range> temperature_to_humidity;
	std::vector<Range> humidity_to_location;

	static std::vector<SeedRange> convert(const std::vector<SeedRange>& input,
		const std::vector<Range>& map) {
		std::vector<SeedRange> output;

		// Get the first relevant map
		auto it = std::ranges::upper_bound(map, Range{ input[0].start, 0, 0 },
			std::less<>{});
		if (it != map.begin())
			it = std::prev(it);

		// For each seed range in the input (the ranges are already sorted)
		for (auto [start, size] : input) {
			while (size > 0) {
				if (it == map.end()) {
					// No conversion, no more mappings
					output.push_back({ start, size });
					size = 0;
				}
				else if (start < it->input_offset) {
					// No conversion (initial part of the range not covered by a mapping)
					unsigned long int actual = std::min(size, it->input_offset - start);
					output.push_back({ start, actual });
					start += actual;
					size -= actual;
				}
				else if (start - it->input_offset >= it->size) {
					// The current mapping is no longer relevant
					++it;
				}
				else {
					// Actual conversion
					unsigned long int actual =
						std::min((it->input_offset + it->size) - start, size);
					output.push_back(
						{ start - it->input_offset + it->output_offset, actual });
					start += actual;
					size -= actual;
				}
			}
		}
		std::ranges::sort(output, std::less<>{});
		return output;
	}

	std::vector<SeedRange> all_seed_locations() const {
		auto soil = convert(seeds, seed_to_soil);
		auto fertilizer = convert(soil, soil_to_fertilizer);
		auto water = convert(fertilizer, fertilizer_to_water);
		auto light = convert(water, water_to_light);
		auto temperature = convert(light, light_to_temperature);
		auto humidity = convert(temperature, temperature_to_humidity);
		return convert(humidity, humidity_to_location);
	}

	friend std::istream& operator>>(std::istream& s, Mapper& mapper) {
		std::string dump;
		s >> dump;

		auto drop_text = [&] {
			while (not std::isdigit(s.peek()))
				s.ignore();
			};

		// Parse the seeds
		std::ranges::copy(std::views::istream<SeedRange>(s),
			std::back_inserter(mapper.seeds));
		s.clear();
		drop_text();
		// Parse the seed-to-soil map
		std::ranges::copy(std::views::istream<Range>(s),
			std::back_inserter(mapper.seed_to_soil));
		s.clear();
		drop_text();
		// Parse the soil-to-fertilizer map
		std::ranges::copy(std::views::istream<Range>(s),
			std::back_inserter(mapper.soil_to_fertilizer));
		s.clear();
		drop_text();
		// Parse the fertilizer-to-water map
		std::ranges::copy(std::views::istream<Range>(s),
			std::back_inserter(mapper.fertilizer_to_water));
		s.clear();
		drop_text();
		// Parse the water-to-light map
		std::ranges::copy(std::views::istream<Range>(s),
			std::back_inserter(mapper.water_to_light));
		s.clear();
		drop_text();
		// Parse the light_to_temperature map
		std::ranges::copy(std::views::istream<Range>(s),
			std::back_inserter(mapper.light_to_temperature));
		s.clear();
		drop_text();
		// Parse the temperature-to-humidity map
		std::ranges::copy(std::views::istream<Range>(s),
			std::back_inserter(mapper.temperature_to_humidity));
		s.clear();
		drop_text();
		// Parse the humidity-to-location map
		std::ranges::copy(std::views::istream<Range>(s),
			std::back_inserter(mapper.humidity_to_location));
		s.clear();

		// Sort all the maps
		std::ranges::sort(mapper.seeds, std::less<>{});
		std::ranges::sort(mapper.seed_to_soil, std::less<>{});
		std::ranges::sort(mapper.soil_to_fertilizer, std::less<>{});
		std::ranges::sort(mapper.fertilizer_to_water, std::less<>{});
		std::ranges::sort(mapper.water_to_light, std::less<>{});
		std::ranges::sort(mapper.light_to_temperature, std::less<>{});
		std::ranges::sort(mapper.temperature_to_humidity, std::less<>{});
		std::ranges::sort(mapper.humidity_to_location, std::less<>{});
		return s;
	}
};

static unsigned long int closest_range_location(std::ifstream &s) {
	Mapper map;
	
	if (not(s >> map))
		throw std::runtime_error("Failed to parse");
	return map.all_seed_locations()[0].start;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::cout << "Lowest location number: " << closest_range_location(inputfile) << "\n";

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
