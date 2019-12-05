#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <optional>
#include <chrono>

struct day4
{
	std::pair<int, int> solve()
	{
		int count= 0;
		for (int i = 134792; i < 675810; ++i)
			count += is_valid(i);
		return {count, 0};
	}

	bool is_valid(int x)
	{
		const int w2 = x / 10;
		const int w3 = w2 / 10;
		const int w4 = w3 / 10;
		const int w5 = w4 / 10;
		const int d6 = w5 / 10;
		const int d1 = x - w2 * 10;
		const int d2 = w2 - w3 * 10;
		const int d3 = w3 - w4 * 10;
		const int d4 = w4 - w5 * 10;
		const int d5 = w5 - d6 * 10;
		const bool increasing = d6 <= d5 && d5 <= d4 && d4 <= d3 && d3 <= d2 && d2 <= d1;
		const bool adjacent = d6 == d5 || d5 == d4 || d4 == d3 || d3 == d2 || d2 == d1;
		return adjacent && increasing;
	}
};

int main()
{
	const auto startTs = std::chrono::steady_clock::now();

	day4 d;
	auto [s1, s2] = d.solve();

	const auto endTs = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs).count() << "us" << std::endl;
	std::cout << s1 << ", " << s2 << std::endl;
	return 0;
}

