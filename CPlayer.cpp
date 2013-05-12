#include "CPlayer.h"
#include "CObjectManager.h"
#include "ComponentEnums.h"
#include "Gloabals.h"


CPlayer::CPlayer(void)
{
}


CPlayer::~CPlayer(void)
{
}


void CPlayer::RegisterComponentType()
{
	CObjectManager::getInstance()->RegisterComponentType(CID_PLAYER, CreateMe, DestroyMe);
}


IComponent* CPlayer::CreateMe()
{
	return new CPlayer;
}


bool CPlayer::DestroyMe(IComponent *p)
{
	delete p;
	return true;
}


bool CPlayer::Init(CObjectId oid, CParameterNode &paramNode)
{
	this->SetObjectId(oid);
	return true;
}


void CPlayer::Deinit()
{

}


EComponentTypeId CPlayer::GetComponentTypeId()
{
	return CID_PLAYER;
}


void CPlayer::HandleMessage(CObjectId oid, MessageTypeId msg)
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
			   if( oid == this->GetObjectId() )
			   {
				   //CObjectManager::getInstance()->AddToRemoveList(this->GetObjectId());
			       Globals::GetSpaceInvaderEngine().EndGame();
			   }
			  
			   break;
		   }
	   case M_ALIEN_DEALTH:
		   {
			   break;
		   }
	   case M_UPDATE:
		   {
			   //respond to the user input,if there is no user input,then stay
	           IDiceInvaders::KeyStatus keys;
			   Globals::GetSpaceInvaderEngine().GetSystem()->getKeyStatus(keys);
	           if( keys.right )
	           {
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_MOVE_RIGHT);
	           }
	           else if( keys.left )
	           {
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_MOVE_LEFT);
	           }
	           else if( keys.fire )
           	   {
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_FIRE_ROCKET);
	           }
	           else
		         ;
	  
	           CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
	           CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_ALIEN);
	           CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_BOMB);
			   break;
		   }
	   default:
		   break;
	}
}


void CPlayer::Update(IDiceInvaders *system)
{
	//respond to the user input,if there is no user input,then stay
	IDiceInvaders::KeyStatus keys;
	Globals::GetSpaceInvaderEngine().GetSystem()->getKeyStatus(keys);
	if( keys.right )
	{
		CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_MOVE_RIGHT);
	}
	else if( keys.left )
	{
		CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_MOVE_LEFT);
	}
	else if( keys.fire )
    {
		CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_FIRE_ROCKET);
	}
	else
		;
	  
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_ALIEN);
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_BOMB);
	
}