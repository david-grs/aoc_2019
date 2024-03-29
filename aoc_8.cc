#include "image.h"

#include <iostream>
#include <chrono>
#include <utility>
#include <algorithm>
#include <array>

struct day8
{
	static const int Width = 25;
	static const int Height = 6;

	int solve()
	{
		const Image img = Image::FromStdin(Width, Height);
		solve2(img);
		return solve1(img);
	}

	int solve1(const Image& img)
	{
		std::vector<std::array<int, 3>> colors(img.LayersCount());
		img.VisitLayers([&](std::size_t layer, int x) { colors.at(layer)[x] += 1; });
		const std::array<int, 3> layer = *std::min_element(colors.cbegin(), colors.cend(),
										[&](const auto& lhs, const auto& rhs) { return lhs[0] < rhs[0]; });
		return layer[1] * layer[2];
	}

	void solve2(const Image& img)
	{
		img.VisitFlatten([&](std::size_t pos, int x)
		{
			std::cout << (x == 1 ? 'X' : ' ');
			if ((pos + 1) % img.Width() == 0)
				std::cout << '\n';
		});
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie();

	auto startTs = std::chrono::steady_clock::now();

	day8 d;
	const int s = d.solve();

	const auto endTs = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs).count() << "us" << std::endl;
	std::cout << s << std::endl;
	return 0;
}

