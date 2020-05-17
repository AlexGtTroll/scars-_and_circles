#include <sstream>
#include "GameOver.hpp"
#include "defs.hpp"
#include "GAMING.hpp"
#include "mainMenu.hpp"
#include <iostream>

using namespace std;
using namespace sf;

namespace Belonogov
{
	GameOver::GameOver(GameDataRef data) : _data(data)
	{

	}

	void GameOver::Init()
	{
		this->_data->assets.LoadTexture("Retry", retry_button);
		this->_data->assets.LoadTexture("Home", home_button);

		this->_retryButton.setTexture(this->_data->assets.GetTexture("Retry"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home"));

		this->_retryButton.setPosition((this->_data->window.getSize().x / 2) - (this->_retryButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3) - (this->_retryButton.getLocalBounds().height / 2));
		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3 * 2) - (this->_homeButton.getLocalBounds().height / 2));
	}

	void GameOver::HandleInput()
	{
		Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_retryButton, Mouse::Left, this->_data->window))
			{
				//Продолжить игру
				this->_data->machine.AddState(StateRef(new Gaming(_data)), true);

			}

			if (this->_data->input.IsSpriteClicked(this->_homeButton, Mouse::Left, this->_data->window))
			{		
				// Перейти в меню
				this->_data->machine.AddState(StateRef(new mainMenu(_data)), true);

			}
		}
	}

	void GameOver::Update(float dt)
	{

	}

	void GameOver::Draw(float dt)
	{
		this->_data->window.clear(Color::Black);

		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();
	}
}