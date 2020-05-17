#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace Belonogov
{
	class Input
	{
	public:
		Input( ) {}
		~Input( ) {}

		bool IsSpriteClicked(Sprite object, Mouse::Button button, RenderWindow& window);

		Vector2i GetMousePosition(RenderWindow& window);
	};
}