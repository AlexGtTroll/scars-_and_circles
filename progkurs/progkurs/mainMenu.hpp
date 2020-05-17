#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;

namespace Belonogov
{
	class mainMenu : public State
	{
	public:
		mainMenu(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		Sprite _background;
		Sprite _playButton;
		Sprite _playButtonOut;
		Sprite _title;
	};
}