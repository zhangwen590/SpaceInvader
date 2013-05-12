#pragma once
#include "icomponent.h"
class CHealth :
	public IComponent
{
public:
	CHealth(void);
	virtual ~CHealth(void);

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

	//cplayer methods
	int                      GetHealth() const;
	void                     SetHealth(int);

private:
	int                      mHealth;
};

