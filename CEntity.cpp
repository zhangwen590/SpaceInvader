#include "CEntity.h"
#include "CObjectManager.h"
#include "ComponentEnums.h"
#include "Gloabals.h"
#include "ObjectIdGenerator.h"
#include "CRender.h"


CEntity::CEntity(void)
{
	this->mPosX   = 0;
	this->mPosY   = 0;
	this->mRadius = 16;
	this->mRight  = true;
}


CEntity::~CEntity(void)
{
}


void CEntity::RegisterComponentType()
{
	CObjectManager::getInstance()->RegisterComponentType(CID_ENTITY, CreateMe, DestroyMe);
}


IComponent* CEntity::CreateMe()
{
	return new CEntity;
}


bool CEntity::DestroyMe(IComponent *p)
{
	delete p;
	return true;
}


bool CEntity::Init(CObjectId oid, CParameterNode &paramNode)
{
	this->SetObjectId(oid);
	//place for initialize from datafiles


	return true;
}


void CEntity::Deinit()
{

}


EComponentTypeId CEntity::GetComponentTypeId()
{
	return CID_ENTITY;
}


void CEntity::HandleMessage(CObjectId oid, MessageTypeId msg)
{
	if( oid != this->GetObjectId() )
		return;

	switch( msg ){

	   case M_MOVE_RIGHT:
		   {
			   //player click right
			   if( this->mPosX >= WINWIDTH )
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
			   else
			   {
				   this->mPosX += SPEED * 1 / Globals::GetSpaceInvaderEngine().GetFPS();
			       //CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
			   }
			   break;
		   }
	   case M_MOVE_LEFT:
		   {
			   //player click left
			   if( this->mPosX <= 0 )
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
			   else
			   {
				   this->mPosX -= SPEED * 1 / Globals::GetSpaceInvaderEngine().GetFPS();
			       //CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
			   }
			   break;
		   }
	   case M_MOVE_ALIEN:
		   {
			   //create a new alien ship 
			   if( (this->mPosX == RADIUS) && (this->mPosY == 0) )
			   {
				   CObjectId id = CObjectIdGenerator::getInstance()->GetAnObjectId();
			       IComponent* proto = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_ENTITY)();
			       proto->SetObjectId(id);
			       CEntity* alienentity = static_cast<CEntity*>(proto);
			       alienentity->SetPositionX(0);
			       alienentity->SetPositionY(0);
			       alienentity->SetRadius(this->mRadius);
			       //add collsion
			       CObjectManager::getInstance()->AddCollsionToDB(CObjectManager::getInstance()->CreateCollision(CID_ALIEN,alienentity));
			
			       IComponent* en = alienentity;
			       CObjectManager::getInstance()->AddToTemporaryDB(id,en);

			       //add a render
			       IComponent* proto2 = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_RENDER)();
			       proto2->SetObjectId(id);
			       CRender* alienrender = static_cast<CRender*>(proto2);
			       alienrender->GetRenderFile("data/enemy2.bmp");
			       IComponent* ren = alienrender;
			       CObjectManager::getInstance()->AddToTemporaryDB(id,ren);

			       //add a health
			       IComponent* proto3 = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_HEALTH)();
			       proto3->SetObjectId(id);
			       CObjectManager::getInstance()->AddToTemporaryDB(id,proto3);

			       //add a rocket
			       IComponent* proto4 = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_ALIEN)();
			       proto4->SetObjectId(id);
			       CObjectManager::getInstance()->AddToTemporaryDB(id,proto4);
			   }

			   //alien ship move
			   if( this->mPosY >= WINHEIGHT )
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_TAKE_DAMAGE);
			   else if( this->mPosX >= WINWIDTH )
			   {
				   this->mPosX -= this->mRadius * 2;
				   this->mPosY += this->mRadius * 2;
				   this->mRight = !this->mRight;
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
			   }
			   else if( this->mPosX < 0 )
			   {
				   this->mPosX += this->mRadius * 2;
				   this->mPosY += this->mRadius * 2;
				   this->mRight = !this->mRight;
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
			   }
			   else
			   {
				   if( this->mRight )
				   {
					   this->mPosX += SPEED * 1 / Globals::GetSpaceInvaderEngine().GetFPS();
				       CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
				   }
				   else
				   {
					   this->mPosX -= SPEED * 1 / Globals::GetSpaceInvaderEngine().GetFPS();
				       CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_RENDER);
				   }
			   }
			   break;
		   }
	   case M_MOVE_UP:
		   {
			   //rocket move up
			   if( this->mPosY < 0 )
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_TAKE_DAMAGE);
			   else
			   {
				   this->mPosY -= SPEED * 1 / Globals::GetSpaceInvaderEngine().GetFPS();
			   }
			   break;
		   }
	   case M_MOVE_DOWN:
		   {
			   //bomb drop down
			   if( this->mPosY > WINHEIGHT )
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_TAKE_DAMAGE);
			   else
			   {
				   this->mPosY += SPEED * 1 / Globals::GetSpaceInvaderEngine().GetFPS();
			   }
			   break;
		   }
	   case M_FIRE_ROCKET:
		   {
			   //fire a rocket and a rocket component is created here
			   //a rocket contains a render, entity, rocket, health here is hardcoded but can be read from script
			   CObjectId id = CObjectIdGenerator::getInstance()->GetAnObjectId();
			   IComponent* proto = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_ENTITY)();
			   proto->SetObjectId(id);
			   CEntity* rocketentity = static_cast<CEntity*>(proto);
			   rocketentity->SetPositionX(this->mPosX);
			   rocketentity->SetPositionY(this->mPosY);
			   rocketentity->SetRadius(this->mRadius);
			   //add collsion
			    CObjectManager::getInstance()->AddCollsionToDB(CObjectManager::getInstance()->CreateCollision(CID_ROCKET,rocketentity));
			
			   IComponent* en = rocketentity;
			   CObjectManager::getInstance()->AddToTemporaryDB(id,en);

			   //add a render
			   IComponent* proto2 = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_RENDER)();
			   proto2->SetObjectId(id);
			   CRender* rocketrender = static_cast<CRender*>(proto2);
			   rocketrender->GetRenderFile("data/rocket.bmp");
			   IComponent* ren = rocketrender;
			   CObjectManager::getInstance()->AddToTemporaryDB(id,ren);

			   //add a health
			   IComponent* proto3 = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_HEALTH)();
			   proto3->SetObjectId(id);
			   CObjectManager::getInstance()->AddToTemporaryDB(id,proto3);

			   //add a rocket
			   IComponent* proto4 = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_ROCKET)();
			   proto4->SetObjectId(id);
			   CObjectManager::getInstance()->AddToTemporaryDB(id,proto4);
			   
			   break;
		   }
	   case M_FIRE_BOMB:
		   {
			   //fire a bomb and a bomb component is created here
			   //a bomb contains a render, entity, bomb, health here is hardcoded but can be read from script
			   CObjectId id = CObjectIdGenerator::getInstance()->GetAnObjectId();
			   IComponent* proto = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_ENTITY)();
			   proto->SetObjectId(id);
			   CEntity* rocketentity = static_cast<CEntity*>(proto);
			   rocketentity->SetPositionX(this->mPosX);
			   rocketentity->SetPositionY(this->mPosY);
			   rocketentity->SetRadius(this->mRadius);
			   //add collsion
			   CObjectManager::getInstance()->AddCollsionToDB(CObjectManager::getInstance()->CreateCollision(CID_BOMB,rocketentity));
			   IComponent* en = rocketentity;
			   CObjectManager::getInstance()->AddToTemporaryDB(id,en);

			   //add a render
			   IComponent* proto2 = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_RENDER)();
			   proto2->SetObjectId(id);
			   CRender* rocketrender = static_cast<CRender*>(proto2);
			   rocketrender->GetRenderFile("data/bomb.bmp");
			   IComponent* ren = rocketrender;
			   CObjectManager::getInstance()->AddToTemporaryDB(id,ren);

			   //add a health
			   IComponent* proto3 = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_HEALTH)();
			   proto3->SetObjectId(id);
			   CObjectManager::getInstance()->AddToTemporaryDB(id,proto3);

			   //add a bomb
			   IComponent* proto4 = CObjectManager::getInstance()->QueryComponentCreationMethod(CID_BOMB)();
			   proto4->SetObjectId(id);
			   CObjectManager::getInstance()->AddToTemporaryDB(id,proto4);
			   
			   break;

		   }
	   case M_CHECK_COLLISION_WITH_PLAYER:
		   {
			   //check if collide with player
			   if( CObjectManager::getInstance()->IsCollideWithPlayerCoreComponent(this->GetObjectId()) )
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_TAKE_DAMAGE);
			   break;
		   }
	   case M_CHECK_COLLISION_WITH_ALIEN:
		   {
			   //check if collide with alien
			   if( CObjectManager::getInstance()->IsCollideWithAlienCoreComponent(this->GetObjectId()) )
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_TAKE_DAMAGE);
			   break;
		   }
	   case M_CHECK_COLLISION_WITH_BOMB:
		   {
			   //check if collide with bomb
			   if( CObjectManager::getInstance()->IsCollideWithBombCoreComponent(this->GetObjectId()) )
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_TAKE_DAMAGE);
			   break;
		   }
	   case M_CHECK_COLLISION_WITH_ROCKET:
		   {
			   //check if collide with rocket
			   if( CObjectManager::getInstance()->IsCollideWithRocketCoreComponent(this->GetObjectId()) )
				   CObjectManager::getInstance()->PostMessage(this->GetObjectId(),M_TAKE_DAMAGE);
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


void CEntity::Update(IDiceInvaders* system)
{
	
}


int CEntity::GetPositionX() const
{
	return this->mPosX;
}


int CEntity::GetPositionY() const
{
	return this->mPosY;
}


int CEntity::GetRadius() const
{
	return this->mRadius;
}


void CEntity::SetPositionX(int px)
{
	this->mPosX = px;
}


void CEntity::SetPositionY(int py)
{
	this->mPosY = py;
}


void CEntity::SetRadius(int r)
{
	this->mRadius = r;
}