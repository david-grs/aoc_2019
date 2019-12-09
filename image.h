#pragma once

#include <iostream>
#include <vector>

class Image
{
public:
	using Layer = std::vector<int>;

	Image(int width, int height, const std::vector<Layer>& layers) :
	  mWidth{width},
	  mHeight{height},
	  mLayers{layers}
	{}

	static Image FromStdin(int width, int height)
	{
		std::vector<Layer> layers;
		int pos = 0;
		for (char digit; std::cin >> digit; ++pos)
		{
			if (pos % (width * height) == 0)
				layers.emplace_back();
			layers.back().push_back(digit - '0');
		}
		if ((int)layers.back().size() != width * height) throw std::runtime_error("unexpected layer size");
		return Image{width, height, layers};
	}

	std::size_t LayersCount() const { return mLayers.size(); }

	template <class Visitor>
	void Visit(Visitor visit) const
	{
		for (std::size_t l = 0; l < mLayers.size(); ++l)
			for (int x : mLayers[l])
				visit(l, x);
	}

private:
	int mWidth;
	int mHeight;
	std::vector<Layer> mLayers;
};
