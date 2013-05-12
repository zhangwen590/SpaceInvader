#include "CHealth.h"
#include "CObjectManager.h"
#include "ComponentEnums.h"


CHealth::CHealth(void): mHealth(1)
{
}


CHealth::~CHealth(void)
{
}


void CHealth::RegisterComponentType()
{
	CObjectManager::getInstance()->RegisterComponentType(CID_HEALTH, CreateMe, DestroyMe);
}


IComponent* CHealth::CreateMe()
{
	return new CHealth;
}


bool CHealth::DestroyMe(IComponent *p)
{
	delete p;
	return true;
}


bool CHealth::Init(CObjectId oid, CParameterNode &paramNode)
{
	this->SetObjectId(oid);

	return true;
}


void CHealth::Deinit()
{

}


EComponentTypeId CHealth::GetComponentTypeId()
{
	return CID_HEALTH;
}


void CHealth::HandleMessage(CObjectId oid, MessageTypeId msg)
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
			   if( this->mHealth <= 0 )
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_DEALTH);
			   else
			   {
				   this->mHealth--;
			   }	
			   break;
		   }
	   case M_DEALTH:
		   {
			   break;
		   }
	   case M_ALIEN_DEALTH:
		   {    
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


void CHealth::Update(IDiceInvaders* system)
{

}


int CHealth::GetHealth() const
{
	return this->mHealth;
}


void CHealth::SetHealth(int h)
{
	this->mHealth = h;
}