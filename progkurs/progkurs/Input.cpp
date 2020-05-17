#include "Input.hpp"

using namespace std;
using namespace sf;

namespace Belonogov
{
	bool Input::IsSpriteClicked(Sprite object, Mouse::Button button, RenderWindow& window)
	{
		if (Mouse::isButtonPressed(button))
		{
			IntRect PlayButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width,
				object.getGlobalBounds().height);

			if (PlayButtonRect.contains(Mouse::getPosition(window)))
			{
				return true;
			}
		}
		return false;
	}

	Vector2i Input::GetMousePosition(RenderWindow& window)
	{
		return Mouse::getPosition(window);
	}

}