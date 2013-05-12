#include "CObjectManager.h"
#include "ObjectIdGenerator.h"
#include <fstream>
#include <string>

#include "CAlien.h"
#include "CBomb.h"
#include "CScore.h"
#include "CEntity.h"
#include "CHealth.h"
#include "CRocket.h"
#include "CPlayer.h"
#include "CRender.h"

using namespace std;


CObjectManager CObjectManager::mObjectManager;


CObjectManager::CObjectManager(void)
{
}


CObjectManager::~CObjectManager(void)
{
}



void CObjectManager::Init()
{
	if( this->mObjectManagerDB != NULL )
		delete this->mObjectManagerDB;

	this->mObjectManagerDB = new ObjectManagerDB();

	if( this->mCollisionDB != NULL )
		delete this->mCollisionDB;

	this->mCollisionDB = new CollisionDB();

	this->RegisterAllComponentTypes();
}


void CObjectManager::Deinit()
{
	if( this->mObjectManagerDB != NULL )
	{
		DestroyAllComponents();

		// Now get rid of the database
		delete this->mObjectManagerDB;
		this->mObjectManagerDB = NULL;
	}

	if( this->mCollisionDB != NULL )
	{
		DestroyAllCollisions();

		// Now get rid of the database
		delete this->mCollisionDB;
		this->mCollisionDB = NULL;
	}
}


bool CObjectManager::LoadObjectsFromFile(const char* filename)
{
	//create player Hardcoded here but is extendable
	CObjectId id = CObjectIdGenerator::getInstance()->GetAnObjectId();
	CParameterNode node;
	for( vector<ComponentTypeInfo>::iterator it = this->mObjectManagerDB->mComponentTypeInfo.begin(); it != this->mObjectManagerDB->mComponentTypeInfo.end(); it++ )
	{
		if( it->mTypeId == CID_PLAYER )
		{
			IComponent* player = it->mCreationMethod();
			if( player != NULL )
			{
				player->Init(id,node);
				this->AddComponentToDB(id,player);
			}
		}
		else if( it->mTypeId == CID_ENTITY )
		{
			IComponent* entity = it->mCreationMethod();
			if( entity != NULL )
			{
				entity->Init(id,node);
				CEntity* temp = static_cast<CEntity*>(entity);
				temp->SetPositionX(WINWIDTH/2);
				temp->SetPositionY(WINHEIGHT - RADIUS);
				temp->SetRadius(RADIUS/2);
				//add collsion
			    this->AddCollsionToDB(this->CreateCollision(CID_PLAYER,temp));

				this->AddComponentToDB(id,entity);
			}
		}
		else if( it->mTypeId == CID_HEALTH )
		{
			IComponent* health = it->mCreationMethod();
			if( health != NULL )
			{
				health->Init(id,node);
				CHealth* temp = static_cast<CHealth*>(health);
				temp->SetHealth(3);
				this->AddComponentToDB(id,health);
			}

		}
		else if( it->mTypeId == CID_RENDER )
		{
			IComponent* render = it->mCreationMethod();
			if( render != NULL )
			{
				render->Init(id,node);
				CRender* temp = static_cast<CRender*>(render);
				temp->GetRenderFile("data/player.bmp");
				IComponent* ren = temp;
				this->AddComponentToDB(id,ren);
			}
		}
		else if( it->mTypeId == CID_SCORE )
		{
			IComponent* score = it->mCreationMethod();
			if( score != NULL )
			{
				score->Init(id,node);
				this->AddComponentToDB(id,score);
			}
		}
		else
			;
	}
	//create a alien here
	CObjectId id2 = CObjectIdGenerator::getInstance()->GetAnObjectId();
	CParameterNode node2;
	for( vector<ComponentTypeInfo>::iterator it = this->mObjectManagerDB->mComponentTypeInfo.begin(); it != this->mObjectManagerDB->mComponentTypeInfo.end(); it++ )
	{
		if( it->mTypeId == CID_ALIEN )
		{
			IComponent* player = it->mCreationMethod();
			if( player != NULL )
			{
				player->Init(id2,node2);
				this->AddComponentToDB(id2,player);
			}
		}
		else if( it->mTypeId == CID_ENTITY )
		{
			IComponent* entity = it->mCreationMethod();
			if( entity != NULL )
			{
				entity->Init(id2,node2);
				CEntity* temp = static_cast<CEntity*>(entity);
				temp->SetPositionX(0);
				temp->SetPositionY(0);
				temp->SetRadius(RADIUS/2);
				//add collsion
			    this->AddCollsionToDB(this->CreateCollision(CID_ALIEN,temp));

				this->AddComponentToDB(id2,entity);
			}
		}
		else if( it->mTypeId == CID_HEALTH )
		{
			IComponent* health = it->mCreationMethod();
			if( health != NULL )
			{
				health->Init(id2,node2);
				this->AddComponentToDB(id2,health);
			}

		}
		else if( it->mTypeId == CID_RENDER )
		{
			IComponent* render = it->mCreationMethod();
			if( render != NULL )
			{
				render->Init(id2,node2);
				CRender* temp = static_cast<CRender*>(render);
				temp->GetRenderFile("data/enemy1.bmp");
				IComponent* ren = temp;
				this->AddComponentToDB(id2,ren);
			}
		}
		else
			;
	}
	return true;
}


bool CObjectManager::LoadObjects(CParameterNode *)
{
	return true;
}


void CObjectManager::RemoveComponent(CObjectId oid)
{
	for( vector<map<CObjectId, IComponent*>>::iterator it = this->mObjectManagerDB->mComponentObjects.begin(); it != this->mObjectManagerDB->mComponentObjects.end(); it++ )
	{
		if( !it->empty() )
		{
			if( (*it->begin()).first == oid )
		    {
				IComponent* temp = it->begin()->second;
			    temp->Deinit();
			    this->QueryComponentDestructionMethod(temp->GetComponentTypeId())(temp);

			    it->clear();
			    it = this->mObjectManagerDB->mComponentObjects.erase(it);
		    }
		}
		
	}

	//remove from the collision DB also
	for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
	{
		if( it->mEntity->GetObjectId() == oid )
		{
			it->mEntity = NULL;
			it = this->mCollisionDB->mCollsionObjects.erase(it);
			return;
		}
	}

}


ComponentCreationMethod CObjectManager::QueryComponentCreationMethod(EComponentTypeId ctype)
{
	for( vector<ComponentTypeInfo>::iterator it = this->mObjectManagerDB->mComponentTypeInfo.begin(); it != this->mObjectManagerDB->mComponentTypeInfo.end(); it++ )
	{
		if( it->mTypeId == ctype )
			return it->mCreationMethod;
	}
    return NULL;
}


ComponentDestructionMethod CObjectManager::QueryComponentDestructionMethod(EComponentTypeId ctype)
{
	for( vector<ComponentTypeInfo>::iterator it = this->mObjectManagerDB->mComponentTypeInfo.begin(); it != this->mObjectManagerDB->mComponentTypeInfo.end(); it++ )
	{
		if( it->mTypeId == ctype )
			return it->mDestuctionMehod;
	}
    return NULL;
}


CollisionTypeInfo CObjectManager::CreateCollision(EComponentTypeId oid, CEntity *entity)
{
	CollisionTypeInfo col;
	col.mCollisionType = oid;
	col.mEntity        = entity;
	return col;
}


void CObjectManager::AddComponentToDB(CObjectId oid, IComponent *comp)
{
	std::map<CObjectId,IComponent*> tmap;
	tmap.insert(std::pair<CObjectId,IComponent*>(oid,comp));
	this->mObjectManagerDB->mComponentObjects.push_back(tmap);
}


void CObjectManager::AddToTemporaryDB(CObjectId oid, IComponent *comp)
{
	std::map<CObjectId,IComponent*> tmap;
	tmap.insert(std::pair<CObjectId,IComponent*>(oid,comp));
	this->mTemporaryDB.push_back(tmap);
}


void CObjectManager::AddToRemoveList(CObjectId oid)
{
	this->mTemporaryRemoveList.push_back(oid);
}


void CObjectManager::AddCollsionToDB(CollisionTypeInfo &col)
{
	this->mCollisionDB->mCollsionObjects.push_back(col);
}


void CObjectManager::DestroyAllComponents()
{
	for( vector<map<CObjectId, IComponent*>>::iterator it = this->mObjectManagerDB->mComponentObjects.begin(); it != this->mObjectManagerDB->mComponentObjects.end(); it++ )
	{
		if( !it->empty() )
		{
			IComponent* temp = it->begin()->second;
		    temp->Deinit();
		    this->QueryComponentDestructionMethod(temp->GetComponentTypeId())(temp);

		    it->clear();
		}
		//it = this->mObjectManagerDB->mComponentObjects.erase(it);
	}

	this->mObjectManagerDB->mComponentObjects.clear();
}


void CObjectManager::DestroyAllCollisions()
{
	for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
	{
		it->mEntity = NULL;
		//this->mCollisionDB->mCollsionObjects.erase(it);
	}
	this->mCollisionDB->mCollsionObjects.clear();
}


void CObjectManager::RegisterComponentType(EComponentTypeId typeId, ComponentCreationMethod creationM, ComponentDestructionMethod destructionM)
{
	ComponentTypeInfo typeinfo;
	typeinfo.mCreationMethod  = creationM;
	typeinfo.mDestuctionMehod = destructionM;
	typeinfo.mTypeId          = typeId;
	this->mObjectManagerDB->mComponentTypeInfo.push_back(typeinfo);
}


IComponent* CObjectManager::QueryComponent(CObjectId oid, EComponentTypeId ctype)
{
	for( vector<map<CObjectId, IComponent*>>::iterator it = this->mObjectManagerDB->mComponentObjects.begin(); it != this->mObjectManagerDB->mComponentObjects.end(); it++ )
	{
		if( !it->empty() )
		{
			if( (it->begin()->first == oid) && (it->begin()->second->GetComponentTypeId() == ctype) )
			{
				IComponent* temp = it->begin()->second;
			    return temp;
			}
		}
	}
	return NULL;
}


bool CObjectManager::IsCollideWithPlayerCoreComponent(CObjectId oid)
{
	CEntity* entity = NULL;
	for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
	{
		if( it->mEntity->GetObjectId() == oid )
		{
			entity = it->mEntity;
			break;
		}
	}

	if( entity != NULL )
	{
		for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
		{
			if( it->mCollisionType == CID_PLAYER )
			{
				int distance = (entity->GetPositionX() - it->mEntity->GetPositionX()) * (entity->GetPositionX() - it->mEntity->GetPositionX()) + (entity->GetPositionY() - it->mEntity->GetPositionY()) * (entity->GetPositionY() - it->mEntity->GetPositionY());
				int radiusdis = (entity->GetRadius() + it->mEntity->GetRadius()) * (entity->GetRadius() + it->mEntity->GetRadius());
				if( distance < radiusdis )
				{
					return true;
				}
			}
		}
	}
	return false;
}


bool CObjectManager::IsCollideWithAlienCoreComponent(CObjectId oid)
{
	CEntity* entity = NULL;
	for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
	{
		if( it->mEntity->GetObjectId() == oid )
		{
			entity = it->mEntity;
			break;
		}
	}

	if( entity != NULL )
	{
		for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
		{
			if( it->mCollisionType == CID_ALIEN )
			{
				int distance = (entity->GetPositionX() - it->mEntity->GetPositionX()) * (entity->GetPositionX() - it->mEntity->GetPositionX()) + (entity->GetPositionY() - it->mEntity->GetPositionY()) * (entity->GetPositionY() - it->mEntity->GetPositionY());
				int radiusdis = (entity->GetRadius() + it->mEntity->GetRadius()) * (entity->GetRadius() + it->mEntity->GetRadius());
				if( distance < radiusdis )
				{
					return true;
				}
			}
		}
	}
	return false;
}


bool CObjectManager::IsCollideWithBombCoreComponent(CObjectId oid)
{
	CEntity* entity = NULL;
	for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
	{
		if( it->mEntity->GetObjectId() == oid )
		{
			entity = it->mEntity;
			break;
		}
	}

	if( entity != NULL )
	{
		for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
		{
			if( it->mCollisionType == CID_BOMB )
			{
				int distance = (entity->GetPositionX() - it->mEntity->GetPositionX()) * (entity->GetPositionX() - it->mEntity->GetPositionX()) + (entity->GetPositionY() - it->mEntity->GetPositionY()) * (entity->GetPositionY() - it->mEntity->GetPositionY());
				int radiusdis = (entity->GetRadius() + it->mEntity->GetRadius()) * (entity->GetRadius() + it->mEntity->GetRadius());
				if( distance < radiusdis )
				{
					return true;
				}
			}
		}
	}
	return false;

}


bool CObjectManager::IsCollideWithRocketCoreComponent(CObjectId oid)
{
	CEntity* entity = NULL;
	for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
	{
		if( it->mEntity->GetObjectId() == oid )
		{
			entity = it->mEntity;
			break;
		}
	}

	if( entity != NULL )
	{
		for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
		{
			if( it->mCollisionType == CID_ROCKET )
			{
				int distance = (entity->GetPositionX() - it->mEntity->GetPositionX()) * (entity->GetPositionX() - it->mEntity->GetPositionX()) + (entity->GetPositionY() - it->mEntity->GetPositionY()) * (entity->GetPositionY() - it->mEntity->GetPositionY());
				int radiusdis = (entity->GetRadius() + it->mEntity->GetRadius()) * (entity->GetRadius() + it->mEntity->GetRadius());
				if( distance < radiusdis )
				{
					return true;
				}
			}
		}
	}
	return false;
}


void CObjectManager::PostMessage(CObjectId oid, MessageTypeId msg)
{
	for( vector<map<CObjectId, IComponent*>>::iterator it = this->mObjectManagerDB->mComponentObjects.begin(); it != this->mObjectManagerDB->mComponentObjects.end(); it++ )
	{
		if( !it->empty() ) 
		{
			if( it->begin()->first == oid )
				it->begin()->second->HandleMessage(oid,msg);
		}
	}
}


void CObjectManager::PostMessageToComponents(CObjectId oid, MessageTypeId msg)
{
	for( vector<map<CObjectId, IComponent*>>::iterator it = this->mObjectManagerDB->mComponentObjects.begin(); it != this->mObjectManagerDB->mComponentObjects.end(); it++ )
	{
		if( !it->empty() )
			it->begin()->second->HandleMessage(oid,msg);
	}
}


void CObjectManager::Update(IDiceInvaders *system)
{
	for( vector<map<CObjectId, IComponent*>>::iterator it = this->mObjectManagerDB->mComponentObjects.begin(); it != this->mObjectManagerDB->mComponentObjects.end(); it++ )
	{
		if( !it->empty() )
			it->begin()->second->Update(system);
	}

	//after one frame is finished, add new components to component database
	for( vector<map<CObjectId, IComponent*>>::iterator it = this->mTemporaryDB.begin(); it != this->mTemporaryDB.end(); it++ )
	{
		this->mObjectManagerDB->mComponentObjects.push_back((*it));
	}
	//empty the temporary db ready for next frame
	this->mTemporaryDB.clear();

	//remove components in the remove list
	for( vector<CObjectId>::iterator it = this->mTemporaryRemoveList.begin(); it != this->mTemporaryRemoveList.end(); it++ )
	{
		this->RemoveComponent((*it));
	}
	//empty remove list 
	this->mTemporaryRemoveList.clear();
}


CEntity* CObjectManager::GetEntity(CObjectId oid)
{
	CEntity* entity;
	for( vector<CollisionTypeInfo>::iterator it = this->mCollisionDB->mCollsionObjects.begin(); it != this->mCollisionDB->mCollsionObjects.end(); it++ )
	{
		if( it->mEntity->GetObjectId() == oid )
		{
			entity = it->mEntity;
			return entity;
		}
	}
	return NULL;
}


void CObjectManager::RegisterAllComponentTypes()
{
	CPlayer::RegisterComponentType();
	CAlien::RegisterComponentType();
	CBomb::RegisterComponentType();
	CScore::RegisterComponentType();
	CEntity::RegisterComponentType();
	CHealth::RegisterComponentType();
	CRender::RegisterComponentType();
	CRocket::RegisterComponentType();
}