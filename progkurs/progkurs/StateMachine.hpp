#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

using namespace std;

namespace Belonogov
{
	typedef unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine() { }
		~StateMachine() { }

		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();
		// ����������� �� ������ ���� � Game.cpp
		void ProcessStateChanges();

		StateRef& GetActiveState();

	private:
		stack<StateRef> _states;
		StateRef _newState;

		bool _isRemoving;
		bool _isAdding;
		bool _isReplacing;
	};
}