#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;

namespace Belonogov
{
	class GameOver : public State
	{
	public:
		GameOver(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		Sprite _retryButton;
		Sprite _homeButton;
	};
}