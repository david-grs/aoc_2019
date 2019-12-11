#pragma once

#include <iostream>
#include <vector>
#include <optional>

class Image
{
public:
	using Layer = std::vector<int>;

	Image(std::size_t width, std::size_t height, const std::vector<Layer>& layers) :
	  mWidth{width},
	  mHeight{height},
	  mLayers{layers}
	{
		if (mLayers.empty() || mLayers.back().size() != mWidth * mHeight)
			throw std::runtime_error("unexpected layer count or size");
	}

	static Image FromStdin(std::size_t width, std::size_t height)
	{
		std::vector<Layer> layers;
		int pos = 0;
		for (char digit; std::cin >> digit; ++pos)
		{
			if (pos % (width * height) == 0)
				layers.emplace_back();
			layers.back().push_back(digit - '0');
		}
		return Image{width, height, layers};
	}

	std::size_t LayersCount() const { return mLayers.size(); }

	template <class Visitor>
	void VisitLayers(Visitor visit) const
	{
		for (std::size_t l = 0; l < mLayers.size(); ++l)
			for (int x : mLayers[l])
				visit(l, x);
	}

	enum Color { Black = 0, White = 1, Transparent = 2 };

	template <class Visitor>
	void VisitFlatten(Visitor visit) const
	{
		for (std::size_t i = 0; i < mWidth * mHeight; ++i)
		{
			std::optional<int> color;
			for (const Layer& layer : mLayers)
			{
				if (!color && layer[i] != Transparent)
					color = layer[i];
			}
			visit(i, color.value_or(Transparent));
		}
	}

	std::size_t Width() const { return mWidth; }
	std::size_t Height() const { return mHeight; }

private:
	std::size_t mWidth;
	std::size_t mHeight;
	std::vector<Layer> mLayers;
};
