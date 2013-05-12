/*
collision data base is used to perform collision detection
*/
#include "CEntity.h"
#include "ComponentEnums.h"
#include <vector>
using namespace std;



struct CollisionTypeInfo
{
	CEntity*         mEntity;
	EComponentTypeId mCollisionType;
};


struct CollisionDB
{
	//storing all the objects entity , assume that all new components in the game need collision detections
	vector<CollisionTypeInfo> mCollsionObjects;
};