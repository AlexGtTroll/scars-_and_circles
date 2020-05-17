#include <sstream>
#include "defs.hpp"
#include "Splash.hpp"
#include <iostream>
#include "mainMenu.hpp"

using namespace std;

namespace Belonogov
{
	Splash::Splash(GameDataRef data) : _data(data)
	{

	}

	void Splash::Init()
	{
		this->_data->assets.LoadTexture("Splash background", splash_background_path);

		_background.setTexture(this->_data->assets.GetTexture("Splash background"));
	}

	void Splash::HandleInput()
	{
		Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}
	}
	void Splash::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > splash_state_time)
		{
			//Ћетим в меню
			this->_data->machine.AddState(StateRef(new mainMenu(_data)), true);
		}
	}

		void Splash::Draw(float dt)
		{
			this->_data->window.clear(Color::Black);
			this->_data->window.draw(this->_background);
			this->_data->window.display();
		}
}
