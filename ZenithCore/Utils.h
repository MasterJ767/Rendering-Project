#pragma once
#include <string>

namespace Zenith {
	namespace Util {
		const std::string ASSETROOT(ASSETROOTLOCATION);
		const std::string SHADERDIR(ASSETROOT + "Shaders/");
		const std::string MODELDIR(ASSETROOT + "Models/");
		const std::string TEXTUREDIR(ASSETROOT + "Textures/");
		const std::string AUDIODIR(ASSETROOT + "Audio/");
		const std::string FONTDIR(ASSETROOT + "Fonts/");

		template <typename T, typename... Rest>
		void hashCombine(std::size_t& seed, const T& v, const Rest&... rest) {
			seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			(hashCombine(seed, rest), ...);
		};
	}
}