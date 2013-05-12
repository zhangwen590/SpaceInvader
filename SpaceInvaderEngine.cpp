#include "SpaceInvaderEngine.h"
#include "CObjectManager.h"
#include "ComponentEnums.h"


SpaceInvaderEngine::SpaceInvaderEngine(void):mFPS(25) 
{
	this->mGameOver  = false;
	this->mSkipTick  = 1 / this->mFPS;
}


SpaceInvaderEngine::SpaceInvaderEngine(IDiceInvaders *system):mFPS(25)
{
	this->mSystem      = system;
	this->mGameOver    = false;
	this->mSkipTick  = 1 / this->mFPS;
}


SpaceInvaderEngine::~SpaceInvaderEngine(void)
{
}


void SpaceInvaderEngine::Init()
{
	//initialize the window
	this->mSystem->init(WINWIDTH,WINHEIGHT);

	//init the object manager
	CObjectManager::getInstance()->Init();
	CObjectManager::getInstance()->LoadObjectsFromFile("xx");
}


void SpaceInvaderEngine::Deinit()
{
	CObjectManager::getInstance()->Deinit();
	
	this->mSystem->destroy();
}


void SpaceInvaderEngine::RunGame()
{
	float nextSkipTick = this->mSkipTick + this->mSystem->getElapsedTime();
	while ( this->mSystem->update() )
	{
		if( nextSkipTick <= this->mSystem->getElapsedTime() )
		{
			//CObjectManager::getInstance()->PostMessageToComponents(0,M_UPDATE);
			if( this->mGameOver )
			{
				if( this->mSystem->getElapsedTime() - nextSkipTick > 10 )
					break;
				this->mSystem->drawText(WINWIDTH/2,WINHEIGHT/2,"Game Over");
			}
			else
			{
				CObjectManager::getInstance()->Update(this->mSystem);
			    nextSkipTick += this->mSkipTick;
			}
		    
		}
		
	}
}


void SpaceInvaderEngine::EndGame()
{
	this->mGameOver = true;
}


void SpaceInvaderEngine::SetSystem(IDiceInvaders *system)
{
	this->mSystem = system;
}


IDiceInvaders* SpaceInvaderEngine::GetSystem() const
{
	return this->mSystem;
}


const int SpaceInvaderEngine::GetFPS() const
{
	return this->mFPS;
}