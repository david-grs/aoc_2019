#include "intcode.h"

#include <iostream>
#include <chrono>
#include <utility>
#include <vector>
#include <algorithm>

struct day7
{
	int solve1()
	{
		IntCode acs = IntCode::FromStdin();
		std::array<int, 5> phases{0, 1, 2, 3, 4};
		std::array<IntCode, 5> amps{acs, acs, acs, acs, acs};
		int maxThurster = 0;

		do
		{
			int output = 0;

			for (int i = 0; i < 5; ++i)
				amps[i].Reset(acs);

			for (int i = 0; i < 5; ++i)
			{
				int read = 0;
				amps[i].Execute([&]() { return read++ == 0 ? phases[i] : output; },
								[&](int x) { output = x; });
			}

			maxThurster = std::max(maxThurster, output);
		} while (std::next_permutation(phases.begin(), phases.end()));
		return maxThurster;
	}

	int solve2()
	{
		IntCode acs = IntCode::FromStdin();
		std::array<IntCode, 5> amps{acs, acs, acs, acs, acs};
		std::array<int, 5> phases{5, 6, 7, 8, 9};
		int maxThurster = 0;

		do
		{
			for (int i = 0; i < 5; ++i)
				amps[i].Reset(acs);

			std::array<int, 5> reads{0, 0, 0, 0, 0};
			std::array<int, 5> writes{0, 0, 0, 0, 0};
			std::array<bool, 5> running{true, true, true, true, true};
			int output = 0;

			for (int run = 0; std::any_of(running.cbegin(), running.cend(), [](bool b) { return b; }); ++run)
			{
				for (int i = 0; i < 5; ++i)
				{
					while (running[i] && writes[i] == run)
					{
						running[i] &= amps[i].ExecuteInstruction(
									[&]() { return reads[i]++ == 0 ? phases[i] : output; },
									[&](int x) { ++writes[i]; output = x; });
					}
				}
			}

			maxThurster = std::max(maxThurster, output);
		} while (std::next_permutation(phases.begin(), phases.end()));
		return maxThurster;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie();

	auto startTs = std::chrono::steady_clock::now();

	day7 d;
	//const int s = d.solve1();
	const int s = d.solve2();

	const auto endTs = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs).count() << "us" << std::endl;
	std::cout << s << std::endl;
	return 0;
}

