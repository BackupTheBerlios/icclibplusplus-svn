//----------------------------------------------------------------------------------------
//	iccTagFactory.h
//	ICCLib++
//
//	Creation: 23/10/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------
// $HEADER$
//----------------------------------------------------------------------------------------
#ifndef _ICCTAGFACTORY_H
#define _ICCTAGFACTORY_H

#include "iccTagHandler.h"

typedef iccUInt32Number iccTagType;

class iccTagFactory	:	public iccTagHandler
{
public:

static	void							Initialize(void);
static	void							Terminate(void);

static	iccTagFactory					*GetInstance(void) {return s_instance;}

virtual	iccTag							*CreateTag(iccTagType inTagType);

virtual	void							PushHandler(iccTagHandler *inHandler);
virtual	iccTagHandler					*PopHandler(void);

//----------------------------------------------------------------------------------------
protected:
										iccTagFactory(void);
										~iccTagFactory(void);

virtual	iccTag							*CreateStandardTag(iccTagType inTagType);

//----------------------------------------------------------------------------------------
private:

static	iccTagFactory					*s_instance;
		std::vector<iccTagHandler *>	m_dynamicHandlerList;
};

#endif	// _ICCTAGFACTORY_H
