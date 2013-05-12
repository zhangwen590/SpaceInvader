#include "CBomb.h"
#include "CObjectManager.h"
#include "ComponentEnums.h"


CBomb::CBomb(void)
{
}


CBomb::~CBomb(void)
{
}


void CBomb::RegisterComponentType()
{
	CObjectManager::getInstance()->RegisterComponentType(CID_BOMB, CreateMe, DestroyMe);
}


IComponent* CBomb::CreateMe()
{
	return new CBomb;
}


bool CBomb::DestroyMe(IComponent *p)
{
	delete p;
	return true;
}


bool CBomb::Init(CObjectId oid, CParameterNode &paramNode)
{
	this->SetObjectId(oid);

	return true;
}


void CBomb::Deinit()
{

}


EComponentTypeId CBomb::GetComponentTypeId()
{
	return CID_BOMB;
}


void CBomb::HandleMessage(CObjectId oid, MessageTypeId msg)
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
			   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_MOVE_DOWN);
	           CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
	           CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_PLAYER);
			   break;
		   }
	   default:
		   break;
	}

}


void CBomb::Update(IDiceInvaders* system)
{
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_MOVE_DOWN);
    CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
	CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_CHECK_COLLISION_WITH_PLAYER);
}