#pragma once
#include <sstream>
#include "Gaming.hpp"
#include "mainMenu.hpp"
#include "defs.hpp"
#include <iostream>
#include "PAUSE.hpp"
#include "GameOver.hpp"

using namespace std;
using namespace sf;

namespace Belonogov
{
	Gaming::Gaming(GameDataRef data) : _data(data)
	{

	}

	void Gaming::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->_data->assets.LoadTexture("Pause Button", pause_button);
		this->_data->assets.LoadTexture("Grid Sprite", setka_sprite);
		this->_data->assets.LoadTexture("X Piece", X_Piece);
		this->_data->assets.LoadTexture("O Piece", O_Piece);
		this->_data->assets.LoadTexture("X Win", X_WIN);
		this->_data->assets.LoadTexture("O Win", O_WIN);

		_background.setTexture(this->_data->assets.GetTexture("Background"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_setkaSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		_setkaSprite.setPosition((s_WIDTH / 2) - (_setkaSprite.getGlobalBounds().width / 2), (s_HEIGHT / 2) - (_setkaSprite.getGlobalBounds().height / 2));

		InitSetkaPieces();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				setkaArr[x][y] = EMPTY_PIECE;
			}
		}
	}

	void Gaming::HandleInput()
	{
		Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_pauseButton, Mouse::Left, this->_data->window))
			{
				// Switch To Gaming
				this->_data->machine.AddState(StateRef(new PAUSE(_data)), false);
			}
			else if (this->_data->input.IsSpriteClicked(this->_setkaSprite, Mouse::Left, this->_data->window))
			{
				if (STATE_PLAYING == gameState)
				{
					this->CheckerPlacesPiece();
				}
			}
		}
	}

	void Gaming::Update(float dt)
	{

	}

	void Gaming::Draw(float dt)
	{
		this->_data->window.clear(Color::Black);

		this->_data->window.draw(this->_background);

		this->_data->window.draw(this->_pauseButton);

		this->_data->window.draw(this->_setkaSprite);

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				this->_data->window.draw(this->_setkaPieces[x][y]);
			}
		}

		this->_data->window.display();
	}

	void Gaming::InitSetkaPieces()
	{
		Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				_setkaPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				_setkaPieces[x][y].setPosition(_setkaSprite.getPosition().x + (tempSpriteSize.x * x) - 7, _setkaSprite.getPosition().y + (tempSpriteSize.y * y) - 7);
				_setkaPieces[x][y].setColor(Color(255, 255, 255, 0));
			}
		}
	}
	void Gaming::CheckerPlacesPiece()
	{
		Vector2i Point = this->_data->input.GetMousePosition(this->_data->window);
		FloatRect setkaSize = _setkaSprite.getGlobalBounds();
		Vector2f setkaSectSize = Vector2f(setkaSize.width / 3, setkaSize.height / 3); /// Делим сетку 3 на 3
		Vector2f gapOutsideOfSetka = Vector2f((s_WIDTH - setkaSize.width) / 2, (s_HEIGHT - setkaSize.height) / 2 );
		Vector2f setkaOnePiece = Vector2f(Point.x - gapOutsideOfSetka.x, Point.y - gapOutsideOfSetka.y);        ///////Нужно узнать положение клетки во всей игровой сетке
																												/// Таким образом мы сможем избежать бага, что даже если нажимаем
																												/// не на элемент сетки, то элемент все равно заполняется
		int col, row;     //// Будем проверять строку и столбец, на которые тыкнул игрок
		if (setkaOnePiece.x < setkaSectSize.x)
		{
			col = 1;
		}
		else if (setkaOnePiece.x < setkaSectSize.x * 2)
		{
			col = 2;
		}
		else if (setkaOnePiece.x < setkaSize.width)
		{
			col = 3;
		}
		if (setkaOnePiece.y < setkaSectSize.y)
		{
			row = 1;
		}
		else if (setkaOnePiece.y < setkaSectSize.y * 2)
		{
			row = 2;
		}
		else if (setkaOnePiece.y < setkaSize.height)
		{
			row = 3;
		}
		if (setkaArr[col - 1][row - 1] == EMPTY_PIECE)  ////тут ходы
		{
			setkaArr[col - 1][row - 1] = turn;
			if (KREST == turn)
			{
				_setkaPieces[col - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));
				this->WonChecker(turn); /// проверяем на победу, чтобы не дать играть даже после победы
				turn = ZERO; /// после хода крестиков - ход переходит к нуликам
			}
			else if (ZERO == turn)
			{
				_setkaPieces[col - 1][row - 1].setTexture(this->_data->assets.GetTexture("O Piece"));
				this->WonChecker(turn); /// проверяем на победу
				turn = KREST;  /// нулики сходили - ход крестиков
			}
			_setkaPieces[col - 1][row - 1].setColor(Color(255, 255, 255, 255));
		}
	}
	void Gaming::WonChecker(int player)
	{
		MatchChecker(0, 0, 1, 0, 2, 0, player);
		MatchChecker(0, 1, 1, 1, 2, 1, player);
		MatchChecker(0, 2, 1, 2, 2, 2, player);
		MatchChecker(0, 0, 0, 1, 0, 2, player);
		MatchChecker(1, 0, 1, 1, 1, 2, player);
		MatchChecker(2, 0, 2, 1, 2, 2, player);
		MatchChecker(0, 0, 1, 1, 2, 2, player);
		MatchChecker(0, 2, 1, 1, 2, 0, player);

		int empty = 9;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (EMPTY_PIECE != setkaArr[x][y])
				{
					empty--;       ///// С каждым ходом количество свободных ячеек в сетке уменьшается
				}
			}
		}
		if (0 == empty && (STATE_WON != gameState) && (STATE_LOSE != gameState))
		{
			gameState = STATE_DRAW; /// Если ничья - вывод 
		}
		if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState)
		{
			/// Конец игры
		}
		cout << gameState << endl;
	}
	void Gaming::MatchChecker(int x1, int y1, int x2, int y2, int x3, int y3, int pieceCheck)
	{
		if (pieceCheck == setkaArr[x1][y1] && pieceCheck == setkaArr[x2][y2] && pieceCheck == setkaArr[x3][y3])  
		{
			string winningPiece;      ///// Условие двумя строками выше - чтобы игра не продолжалась, после
													/// чьей-нибудь победы
			if (ZERO == pieceCheck)
			{
				winningPiece = "O Win";
			}
			else
			{
				winningPiece = "X Win";
			}

			_setkaPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPiece));
			_setkaPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPiece));
			_setkaPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPiece));


			if (PLAYER_PIECE == pieceCheck)
			{
				gameState = STATE_WON;
			}
			else
			{
				gameState = STATE_LOSE;
			}
		}
	}
}