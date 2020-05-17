#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "Assets.hpp"
#include "Input.hpp"

using namespace std;
using namespace sf;


namespace Belonogov
{
	struct Data
	{
		StateMachine machine;
		RenderWindow window;
		Assets assets;
		Input input;
	};
	typedef shared_ptr<Data> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, string GameTitle);

	private:
		const float dt = 1.0f / 60.0f; /// גנולÿ ג טדנו, פנולנויע
		Clock _clock;

		GameDataRef _data = make_shared<Data>();

		void Run();
	};
}