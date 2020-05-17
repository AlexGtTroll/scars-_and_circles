#include "Game.hpp"
#include "Splash.hpp"

using namespace std;
using namespace sf;

namespace Belonogov
{
	Game::Game(int width, int height, string title)   /// окно игры
	{
		_data->window.create(VideoMode(width, height),
			title, Style::Close | Style::Titlebar);
		_data->machine.AddState(StateRef(new Splash(this->_data)));

		this->Run();
	}

	void Game::Run()   /// время, время кадра и промежутки между ними (интерполяция, короче)
	{							/// Если бы мне сказали, что будут такие штуки - выбрал бы чего полегче
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->_data->window.isOpen())  //пока окно открыто - перманентно происходит луп
		{
			this->_data->machine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();   /// получили время новой игры
			frameTime = newTime - currentTime;   /// Для чего? Уравниваем фпс со временем кадра (Стабильная плавность игры, в теории)

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}
			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_data->machine.GetActiveState()->HandleInput();
				this->_data->machine.GetActiveState()->Update(dt);

				accumulator -= dt;
			}
			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);  /// готовый Game Loop
		}
	}
}