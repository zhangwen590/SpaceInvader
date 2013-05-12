/*
it is desinged for distributing a unique number for different components
*/
#pragma once
#include "CObjectId.h"

class CObjectIdGenerator
{
public:
	CObjectIdGenerator(void);
	~CObjectIdGenerator(void);
	static CObjectIdGenerator* getInstance() { return &mIdGenerator; }
	CObjectId GetAnObjectId();

private:
	static CObjectIdGenerator mIdGenerator;
	CObjectId                 mId;
};

