#pragma once
#include "DiceInvaders.h"

class SpaceInvaderEngine
{
public:
	SpaceInvaderEngine();
	SpaceInvaderEngine(IDiceInvaders*);
	~SpaceInvaderEngine(void);

	void Init();
	void Deinit();
	void RunGame();
	void EndGame();

	void SetSystem(IDiceInvaders*);
	IDiceInvaders* GetSystem() const;

	const int GetFPS() const;

private:
	IDiceInvaders*   mSystem;
	const int        mFPS;
	int              mSkipTick;
	bool             mGameOver;
};

