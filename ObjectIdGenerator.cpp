#include "ObjectIdGenerator.h"


CObjectIdGenerator CObjectIdGenerator::mIdGenerator;


CObjectIdGenerator::CObjectIdGenerator(void)
{
	this->mId = 0;
}


CObjectIdGenerator::~CObjectIdGenerator(void)
{
}


CObjectId CObjectIdGenerator::GetAnObjectId()
{
	CObjectId id = this->mId;
	this->mId++;
	return id;
}