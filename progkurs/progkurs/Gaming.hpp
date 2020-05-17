#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;

namespace Belonogov
{
	class Gaming : public State
	{
	public:
		Gaming(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		void InitSetkaPieces();
		void CheckerPlacesPiece();   
		void WonChecker(int turn);  ///// Проверка на то, кто победил
		void MatchChecker(int x1, int y1, int x2, int y2, int x3, int y3, int pieceCheck);  /// В общем-то, проверка на победу
		GameDataRef _data;
		Sprite _background;
		Sprite _pauseButton;
		Sprite _setkaSprite;

		Sprite _setkaPieces[3][3];
		char setkaArr[3][3];

		int turn;
		int gameState;
	};
}