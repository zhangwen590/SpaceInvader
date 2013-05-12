/*
the data base contains all types of components info and all the components created during the run time
*/
#pragma once

#include "ComponentEnums.h"
#include "IComponent.h"
#include "CObjectId.h"
#include <vector>
#include <map>
using namespace std;


typedef IComponent* (*ComponentCreationMethod)(void);
typedef bool (*ComponentDestructionMethod)(IComponent *);


struct ComponentTypeInfo
{
	ComponentCreationMethod    mCreationMethod;
	ComponentDestructionMethod mDestuctionMehod;
	EComponentTypeId           mTypeId;
};


struct ObjectManagerDB
{
	//static component type data
	vector<ComponentTypeInfo>  mComponentTypeInfo;

	//all components in the game 
	vector<map<CObjectId, IComponent*>>  mComponentObjects;
};