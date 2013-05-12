/*
parent class of all basic components in the system
*/
#pragma once

#include "CObjectId.h"
#include "ComponentEnums.h"
#include "ParameterNode.h"
#include "DiceInvaders.h"

class IComponent
{
public:
	IComponent(){}
	virtual ~IComponent(){}
	virtual bool              Init(CObjectId, CParameterNode &) = 0;
	virtual void              Deinit() = 0;
	CObjectId                 GetObjectId() const { return mObjectId; }
	virtual EComponentTypeId  GetComponentTypeId() = 0;
	virtual void              HandleMessage(CObjectId, MessageTypeId ) = 0;
	virtual void              Update(IDiceInvaders*) = 0;
	void                      SetObjectId(CObjectId oId) { mObjectId = oId; }
protected:
	CObjectId                 mObjectId;

};