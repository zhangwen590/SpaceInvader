/*
this class manages all components in the game.It provides interfaces for component creation, destruction, query and interfaces for communications among components.In addition, it can 
access collision database to check collisions among components and component data base.
*/
#pragma once
#include "ParameterNode.h"
#include "IComponent.h"
#include "CObjectId.h"
#include "ComponentEnums.h"
#include "ObjectManagerDB.h"
#include "CollisionDB.h"
#include "CEntity.h"
#include "DiceInvaders.h"


class CObjectManager
{
public:
	CObjectManager(void);
	~CObjectManager(void);
	static CObjectManager* getInstance() { return &mObjectManager; }

	void Init();
	void Deinit();

	//load data from files to initialize the game 
	bool LoadObjectsFromFile(const char* filename);
	bool LoadObjects(CParameterNode *);

	//IComponent* CreateComponent(CObjectId, CParameterNode *);

	//remove a component
	void RemoveComponent(CObjectId);

	//query the creation method by component type
	ComponentCreationMethod QueryComponentCreationMethod(EComponentTypeId);

	//query the destruction method by component type
	ComponentDestructionMethod QueryComponentDestructionMethod(EComponentTypeId);

	//create a new collsion based on component type and entity pointer
	CollisionTypeInfo CreateCollision(EComponentTypeId, CEntity*);

	//add new component to component database
	void AddComponentToDB(CObjectId, IComponent *);

	//add to temporary database, after one frame is over, add to component database
	void AddToTemporaryDB(CObjectId, IComponent *);

	//add to remove list
	void AddToRemoveList(CObjectId);

	//add new collison to collsion database
	void AddCollsionToDB(CollisionTypeInfo&);

	//destroy all the components in the component database
	void DestroyAllComponents();

	//destroy all the collisions in the collision database
	void DestroyAllCollisions();

	//register a component type into component database
	void RegisterComponentType(EComponentTypeId, ComponentCreationMethod, ComponentDestructionMethod);

	//query the component by objectId and component type
	IComponent* QueryComponent(CObjectId, EComponentTypeId);

	//query collisions with component cored new components
	bool IsCollideWithPlayerCoreComponent(CObjectId);

	bool IsCollideWithAlienCoreComponent(CObjectId);

	bool IsCollideWithBombCoreComponent(CObjectId);

	bool IsCollideWithRocketCoreComponent(CObjectId);

	//Post messages within a component
	void PostMessage(CObjectId, MessageTypeId);

	//Post messages to all components
	void PostMessageToComponents(CObjectId, MessageTypeId);

	//get a entity by id
	CEntity* GetEntity(CObjectId);

	//Update all components
	void Update(IDiceInvaders *);

private:
	void RegisterAllComponentTypes();

	static CObjectManager              mObjectManager;
	ObjectManagerDB*                   mObjectManagerDB;
	CollisionDB*                       mCollisionDB;
	vector<map<CObjectId,IComponent*>> mTemporaryDB;
	vector<CObjectId>                  mTemporaryRemoveList;
};

