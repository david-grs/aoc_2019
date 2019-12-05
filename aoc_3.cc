#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <optional>
#include <chrono>

struct point { int x = 0; int y = 0; };
using segment = std::pair<point, point>;
using segments = std::vector<std::pair<point, point>>;

bool between(int x, int l, int r) { return std::min(l, r) < x && x < std::max(l, r); }
int distance(point p1, point p2) { return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y); }

std::optional<point> intersects(segment s1, segment s2)
{
	if (between(s1.first.x, s2.first.x, s2.second.x) && between(s2.first.y, s1.first.y, s1.second.y))
		return point{s1.first.x, s2.second.y};
	else if (between(s2.first.x, s1.first.x, s1.second.x) && between(s1.first.y, s2.first.y, s2.second.y))
		return point{s2.first.x, s1.second.y};
	return {};
}

class circuit
{
public:
	static constexpr point central_port{0, 0};

	std::pair<int, int> solve()
	{
		segments wires1, wires2;
		read_input(wires1);
		read_input(wires2);

		std::vector<std::pair<point, int>> intersections;
		int steps1 = 0;
		for (auto w1 : wires1)
		{
			int steps2 = 0;
			for (auto w2 : wires2)
			{
				if (auto p = intersects(w1, w2))
					intersections.emplace_back(*p, steps1 + steps2 + distance(*p, w1.first) + distance(*p, w2.first));
				steps2 += distance(w2.first, w2.second);
			}
			steps1 += distance(w1.first, w1.second);
		}

		auto it1 = std::min_element(intersections.cbegin(), intersections.cend(),
						[](auto p1, auto p2) { return distance(central_port, p1.first) < distance(central_port, p2.first); });
		auto it2 = std::min_element(intersections.cbegin(), intersections.cend(),
						[](auto p1, auto p2) { return p1.second < p2.second; });
		return {distance(central_port, it1->first), it2->second};
	}

private:
	void read_input(segments& s)
	{
		point p = central_port;
		point prev = p;
		for	(char direction; std::cin >> direction; )
		{
			int n;
			std::cin >> n;
			if (std::cin.peek() == ',') std::cin.ignore();
			switch (direction)
			{
			case 'L': p.x -= n; break;
			case 'R': p.x += n; break;
			case 'U': p.y += n; break;
			case 'D': p.y -= n; break;
			}
			s.emplace_back(prev, p);
			prev = p;
			if (std::cin.peek() == '\n') break;
		}
	}
};

int main()
{
	const auto startTs = std::chrono::steady_clock::now();

	circuit c;
	auto [min1, min2 ] = c.solve();

	const auto endTs = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs).count() << "us" << std::endl;
	std::cout << min1 << " " << min2 << std::endl;
	return 0;
}

