#include <sstream>
#include "PAUSE.hpp"
#include "defs.hpp"
#include "GAMING.hpp"
#include "mainMenu.hpp"
#include <iostream>

using namespace std;
using namespace sf;

namespace Belonogov
{
	PAUSE::PAUSE(GameDataRef data) : _data(data)
	{

	}

	void PAUSE::Init()
	{
		this->_data->assets.LoadTexture("Background", pause_background_path);
		this->_data->assets.LoadTexture("Resume", resume_button);
		this->_data->assets.LoadTexture("Home", home_button);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_resumeButton.setTexture(this->_data->assets.GetTexture("Resume"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home"));

		this->_resumeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_resumeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3) - (this->_resumeButton.getLocalBounds().height / 2));
		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3 * 2) - (this->_homeButton.getLocalBounds().height / 2));
	}

	void PAUSE::HandleInput()
	{
		Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_resumeButton, Mouse::Left, this->_data->window))
			{
				//Продолжить игру
				this->_data->machine.RemoveState();

			}

			if (this->_data->input.IsSpriteClicked(this->_homeButton, Mouse::Left, this->_data->window))
			{
				// Убрать паузу из State
				this->_data->machine.RemoveState();

				// Перейти в меню
				this->_data->machine.AddState(StateRef(new mainMenu(_data)), true);

			}
		}
	}

	void PAUSE::Update(float dt)
	{

	}

	void PAUSE::Draw(float dt)
	{
		this->_data->window.clear(Color::Black);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_resumeButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();
	}
}