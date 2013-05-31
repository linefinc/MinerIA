#pragma once

template <class T> class State
{
public:
	virtual void Enter(T* pEntity) = 0;

	virtual void Execute(T* pEntity) = 0;

	virtual void Exit(T* pEntity) = 0;
};