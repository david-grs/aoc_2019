#include <iostream>
#include <chrono>
#include <utility>
#include <string>
#include <numeric>
#include <vector>
#include <unordered_map>
#include <unordered_set>

struct day6
{
	std::pair<int, int> solve()
	{
		for (std::string line; std::cin >> line; )
		{
			const std::string parent = line.substr(0, 3);
			const std::string child = line.substr(4, 7);
			const bool inserted = m.emplace(child, std::make_pair(-1, parent)).second;
			if (!inserted) throw 42;
			nodes.emplace(child);
			nodes.emplace(parent);
		}
		m["COM"] = std::make_pair(0, "COM");

		const int s0 = std::accumulate(nodes.cbegin(), nodes.cend(), 0,
						[this](int n, const std::string& node) { return calc_orbits(node) + n; });
		return {s0, 0};
	}

	int calc_orbits(const std::string& planet)
	{
		auto it = m.find(planet);
		if (it == m.end()) throw 42;

		int& orbits = it->second.first;
		const std::string& parent = it->second.second;

		if (orbits == -1)
			orbits = calc_orbits(parent) + 1;
		return orbits;
	}

	std::unordered_map<std::string, std::pair<int, std::string>> m;
	std::unordered_set<std::string> nodes;
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie();

	auto startTs = std::chrono::steady_clock::now();

	day6 d;
	auto [s1, s2] = d.solve();

	const auto endTs = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs).count() << "us" << std::endl;
	std::cout << s1 << ", " << s2 << std::endl;
	return 0;
}

