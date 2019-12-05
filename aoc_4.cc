#include <iostream>
#include <chrono>
#include <utility>

struct day4
{
	std::pair<int, int> solve()
	{
		std::pair<int, int> p{0, 0};
		for (int x = 134792; x < 675810; ++x)
		{
			auto [v1, v2] = is_valid(x);
			p.first += v1 ? 1 : 0;
			p.second += v2 ? 1 : 0;
		}
		return p;
	}

	std::pair<bool, bool> is_valid(int x)
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
		const bool two_adjacent = d6 == d5 || d5 == d4 || d4 == d3 || d3 == d2 || d2 == d1;
		const bool v1 = increasing && two_adjacent;

		if (!v1)
			return {false, false};

		if (d6 == d5 && d5 == d4)
			return {true, d4 != d3 && (d3 == d2 || d2 == d1)};
		else if (d5 == d4 && d4 == d3)
			return {true, d3 != d2 && d2 == d1};
		else if (d4 == d3 && d3 == d2)
			return {true, d4 != d5 && d5 == d6};
		else if (d3 == d2 && d2 == d1)
			return {true, d3 != d4 && (d4 == d5 || d5 == d6)};

		return {true, true};
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

