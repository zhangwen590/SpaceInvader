#pragma once
#include "icomponent.h"




class CEntity :
	public IComponent
{
public:
	CEntity(void);
	virtual ~CEntity(void);

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
	int                      GetPositionX() const;
	int                      GetPositionY() const;
	int                      GetRadius() const;
	void                     SetPositionX(int);
	void                     SetPositionY(int);
	void                     SetRadius(int);

private:
	int                      mPosX;
	int                      mPosY;
	int                      mRadius;
	bool                     mRight;
};

