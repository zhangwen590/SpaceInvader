#include "CAlien.h"
#include "CObjectManager.h"
#include "ComponentEnums.h"
#include <cstdlib>


CAlien::CAlien(void)
{
}


CAlien::~CAlien(void)
{
}


void CAlien::RegisterComponentType()
{
	CObjectManager::getInstance()->RegisterComponentType(CID_ALIEN, CreateMe, DestroyMe);
}


IComponent* CAlien::CreateMe()
{
	return new CAlien;
}


bool CAlien::DestroyMe(IComponent *p)
{
	delete p;
	return true;
}


bool CAlien::Init(CObjectId oid, CParameterNode &paramNode)
{
	this->SetObjectId(oid);

	return true;
}


void CAlien::Deinit()
{

}


EComponentTypeId CAlien::GetComponentTypeId()
{
	return CID_ALIEN;
}


void CAlien::HandleMessage(CObjectId oid, MessageTypeId msg)
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
				   CObjectManager::getInstance()->PostMessageToComponents(this->GetObjectId(),M_ALIEN_DEALTH);
			       CObjectManager::getInstance()->AddToRemoveList(this->GetObjectId());
			   }
			   break;
		   }
	   case M_ALIEN_DEALTH:
		   {
			   break;
		   }
	   case M_UPDATE:
		   {
			   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_MOVE_ALIEN);
	           CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_ROCKET);
	           CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_PLAYER);
			   break;
		   }
	   default:
		   break;
	}
}


void CAlien::Update(IDiceInvaders* system)
{
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_MOVE_ALIEN);
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_ROCKET);
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_PLAYER);

	int fire = rand() % 100;
	int fire2 = rand() % 100;
	int fire3 = rand() % 100;
	int fire4 = rand() % 100;
	if( (fire < 1) && (fire2 == 28) && (fire3 < 30) ) 
		CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_FIRE_BOMB);

}