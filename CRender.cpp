#include "CRender.h"
#include "CObjectManager.h"
#include "ComponentEnums.h"
#include "CEntity.h"
#include "Gloabals.h"


CRender::CRender(void):mIsTextVisible(false),mIsScoreVisible(false)
{
	this->mRender = NULL;
}


CRender::~CRender(void)
{
}


void CRender::RegisterComponentType()
{
	CObjectManager::getInstance()->RegisterComponentType(CID_RENDER, CreateMe, DestroyMe);
}


IComponent* CRender::CreateMe()
{
	return new CRender;
}


bool CRender::DestroyMe(IComponent *p)
{
	delete p;
	return true;
}


bool CRender::Init(CObjectId oid, CParameterNode &paramNode)
{
	this->SetObjectId(oid);

	return true;
}


void CRender::Deinit()
{
	this->mRender->destroy();
}


EComponentTypeId CRender::GetComponentTypeId()
{
	return CID_RENDER;
}


void CRender::HandleMessage(CObjectId oid, MessageTypeId msg)
{
	if( oid != this->GetObjectId() )
		return;

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
			   if( CObjectManager::getInstance()->GetEntity(this->GetObjectId()) != NULL )
			   {
				   int x = CObjectManager::getInstance()->GetEntity(this->GetObjectId())->GetPositionX();
			       int y = CObjectManager::getInstance()->GetEntity(this->GetObjectId())->GetPositionY();
			       //this->mRender->draw(320,240);
			       this->display(x,y);
			   }
			   
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


void CRender::Update(IDiceInvaders* system)
{
	
}


void CRender::display(int x, int y)
{
	if( this->mRender )
		this->mRender->draw(x,y);
}


void CRender::GetRenderFile(const char* file)
{
	this->mRender = Globals::GetSpaceInvaderEngine().GetSystem()->createSprite(file);
}