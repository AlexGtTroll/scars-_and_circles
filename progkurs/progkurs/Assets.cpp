#include "Assets.hpp"

using namespace std;
using namespace sf;

namespace Belonogov
{
	void Assets::LoadTexture(string name, string fileName)
	{
		Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_textures[name] = tex;
		}
	}
	Texture& Assets::GetTexture(string name)
	{
		return this->_textures.at(name);
	}


	void Assets::LoadFont(string name, string fileName)
	{
		Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}
	Font& Assets::GetFont(string name)
	{
		return this->_fonts.at(name);
	}
}