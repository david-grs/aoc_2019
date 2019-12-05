#include <iostream>
#include <chrono>
#include <utility>
#include <array>

struct number
{
	explicit number(int n)
	{
		d[0] = n % 10;
		d[1] = (n / 10) % 10;
		d[2] = (n / 100) % 10;
		d[3] = (n / 1000) % 10;
		d[4] = (n / 10000) % 10;
		d[5] = (n / 100000) % 10;
	}

	constexpr int operator[](std::size_t n) { return d[n]; }

	void operator++()
	{
		for (int i = 0; i < 6; ++i)
		{
			d[i] += 1;
			if (d[i] == 10)
				d[i] = 0;
			else
				break;
		}
	}
	
	bool operator!=(const number& other) const 
	{
		return d != other.d;
	}

	std::array<int, 6> d;
};

struct day4
{
	std::pair<int, int> solve()
	{
		constexpr int start = 134792;
		constexpr int end = 675810;
		constexpr int iterations = end - start;

		std::pair<int, int> p{0, 0};
		number x{start};
		
		for (int i = 0; i < iterations; ++i, ++x)
		{
			auto [v1, v2] = is_valid(x);
			p.first += v1 ? 1 : 0;
			p.second += v2 ? 1 : 0;
		}
		return p;
	}

	std::pair<bool, bool> is_valid(number x)
	{
		const bool increasing = x[5] <= x[4] && x[4] <= x[3] && x[3] <= x[2] && x[2] <= x[1] && x[1] <= x[0];
		const bool two_adjacent = x[5] == x[4] || x[4] == x[3] || x[3] == x[2] || x[2] == x[1] || x[1] == x[0];
		const bool v0 = increasing && two_adjacent;

		if (!v0)
			return {false, false};

		if (x[5] == x[4] && x[4] == x[3])
			return {true, x[3] != x[2] && (x[2] == x[1] || x[1] == x[0])};
		else if (x[4] == x[3] && x[3] == x[2])
			return {true, x[2] != x[1] && x[1] == x[0]};
		else if (x[3] == x[2] && x[2] == x[1])
			return {true, x[3] != x[4] && x[4] == x[5]};
		else if (x[2] == x[1] && x[1] == x[0])
			return {true, x[2] != x[3] && (x[3] == x[4] || x[4] == x[5])};

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

