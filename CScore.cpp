#include "CScore.h"
#include "CObjectManager.h"
#include "ComponentEnums.h"
#include "Gloabals.h"
#include <sstream>
#include <string>
using namespace std;


CScore::CScore(void)
{
	this->mScore = 0;
}


CScore::~CScore(void)
{
}


void CScore::RegisterComponentType()
{
	CObjectManager::getInstance()->RegisterComponentType(CID_SCORE, CreateMe, DestroyMe);
}


IComponent* CScore::CreateMe()
{
	return new CScore;
}


bool CScore::DestroyMe(IComponent *p)
{
	delete p;
	return true;
}


bool CScore::Init(CObjectId oid, CParameterNode &paramNode)
{
	this->SetObjectId(oid);


	return true;
}


void CScore::Deinit()
{

}


EComponentTypeId CScore::GetComponentTypeId()
{
	return CID_SCORE;
}


void CScore::HandleMessage(CObjectId oid, MessageTypeId msg)
{

	switch( msg ){

	   case M_MOVE_RIGHT:
		   {
			   break;
		   }
	   case M_MOVE_LEFT:
		   {
			   break;
		   }
	   case M_MOVE_ALIEN:
		   {
			   break;
		   }
	   case M_MOVE_UP:
		   {
			   break;
		   }
	   case M_MOVE_DOWN:
		   {
			   break;
		   }
	   case M_FIRE_ROCKET:
		   {
			   break;
		   }
	   case M_FIRE_BOMB:
		   {   
			   break;
		   }
	   case M_CHECK_COLLISION_WITH_PLAYER:
		   {
			   break;
		   }
	   case M_CHECK_COLLISION_WITH_ALIEN:
		   {
			   break;
		   }
	   case M_CHECK_COLLISION_WITH_BOMB:
		   {
			   break;
		   }
	   case M_CHECK_COLLISION_WITH_ROCKET:
		   {
			   break;
		   }
	   case M_RENDER:
		   {
			   break;
		   }
	   case M_TAKE_DAMAGE:
		   {
			   break;
		   }
	   case M_DEALTH:
		   {
			   break;
		   }
	   case M_ALIEN_DEALTH:
		   {
			   if( this->GetObjectId() != oid )
				   this->mScore++;
			   break;
		   }
	   case M_UPDATE:
		   {
			   break;
		   }
	   default:
		   break;
	}
}
	

void CScore::Update(IDiceInvaders* system)
{
	stringstream ss;
	ss << this->mScore;
	string text = "Score: " + ss.str();
	Globals::GetSpaceInvaderEngine().GetSystem()->drawText(0,WINHEIGHT - 32,text.c_str());

}


int CScore::GetScore() const
{
	return this->mScore;
}