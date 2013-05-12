#include "CRocket.h"
#include "CObjectManager.h"
#include "ComponentEnums.h"


CRocket::CRocket(void)
{
}


CRocket::~CRocket(void)
{
}


void CRocket::RegisterComponentType()
{
	CObjectManager::getInstance()->RegisterComponentType(CID_ROCKET, CreateMe, DestroyMe);
}


IComponent* CRocket::CreateMe()
{
	return new CRocket;
}


bool CRocket::DestroyMe(IComponent *p)
{
	delete p;
	return true;
}


bool CRocket::Init(CObjectId oid, CParameterNode &paramNode)
{
	this->SetObjectId(oid);

	return true;
}


void CRocket::Deinit()
{

}


EComponentTypeId CRocket::GetComponentTypeId()
{
	return CID_ROCKET;
}


void CRocket::HandleMessage(CObjectId oid, MessageTypeId msg)
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
				   CObjectManager::getInstance()->AddToRemoveList(this->GetObjectId());
			   break;
		   }
	   case M_ALIEN_DEALTH:
		   {
			   break;
		   }
	   case M_UPDATE:
		   {
			   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_MOVE_UP);
	           CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
	           CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_ALIEN);
			   break;
		   }
	   default:
		   break;
	}
}
	

void CRocket::Update(IDiceInvaders* system)
{
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_MOVE_UP);
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_ALIEN);
}