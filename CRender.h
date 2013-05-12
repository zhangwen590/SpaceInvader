#pragma once
#include "icomponent.h"
#include "DiceInvaders.h"

class CRender :
	public IComponent
{
public:
	CRender(void);
	virtual ~CRender(void);

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

	//render methods
	void                     GetRenderFile(const char*);

private:
	ISprite*                 mRender;
	bool                     mIsTextVisible;
	bool                     mIsScoreVisible;
	void                     display(int,int);
};

