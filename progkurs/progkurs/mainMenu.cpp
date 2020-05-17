#include <sstream>
#include "mainMenu.hpp"
#include "defs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gaming.hpp"

using namespace std;
using namespace sf;

namespace Belonogov
{
	mainMenu::mainMenu(GameDataRef data) : _data(data)
	{

	}

	void mainMenu::Init()
	{
		this->_data->assets.LoadTexture("Background", mmenu_background_path);
		this->_data->assets.LoadTexture("Play Button", play_button);
		this->_data->assets.LoadTexture("Play Button Out", play_button_out);
		this->_data->assets.LoadTexture("Game Title", mmenu_title_path);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		this->_playButtonOut.setTexture(this->_data->assets.GetTexture("Play Button Out"));
		this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));

		this->_playButton.setPosition((s_WIDTH / 2) - (this->_playButton.getGlobalBounds().width / 2),
			(s_HEIGHT / 10) - (this->_playButton.getGlobalBounds().height / 100));  ///”станавливаем позицию дл€ play button
			this->_playButtonOut.setPosition((s_WIDTH / 2) - (this->_playButtonOut.getGlobalBounds().width / 2),
				(s_HEIGHT / 10 ) - (this->_playButtonOut.getGlobalBounds().height / 100 ));  ///”станавливаем позицию дл€ play button out
			this->_title.setPosition((s_WIDTH / 2) - (this->_title.getGlobalBounds().width / 2),
				this->_title.getGlobalBounds().height * 0.1);  ///”станавливаем позицию дл€ title
	}
	void mainMenu::HandleInput()
	{
		Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (Event::Closed == event.type)
			{
				this->_data->window.close();   /// если пользователь хочет закрыть окно - он его закрывает
			}
			if (this->_data->input.IsSpriteClicked(this->_playButton, Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new Gaming(_data)), true);
			}
		}
	}
	void mainMenu::Update(float dt)
	{

	}

	void mainMenu::Draw(float dt)
	{
		this->_data->window.clear(Color::Black);
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_playButtonOut);
		this->_data->window.draw(this->_title);

		this->_data->window.display();
	}
}