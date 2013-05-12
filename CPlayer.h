#pragma once
#include "icomponent.h"

class CPlayer :
	public IComponent
{
public:
	CPlayer(void);
	virtual ~CPlayer(void);

	//static methods
	static void              RegisterComponentType();
	static IComponent*       CreateMe();
	static bool              DestroyMe(IComponent*);

	//virtual IComponent methods
	virtual bool             Init(CObjectId, CParameterNode &);
	virtual void             Deinit();
	virtual EComponentTypeId GetComponentTypeId();
    virtual void             HandleMessage(CObjectId, MessageTypeId );
	virtual void             Update(IDiceInvaders*);

};

