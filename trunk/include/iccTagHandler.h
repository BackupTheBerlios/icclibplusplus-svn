//----------------------------------------------------------------------------------------
//	iccTagHandler.h
//	ICCLib++
//
//	Creation: 23/10/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------
// $HEADER$
//----------------------------------------------------------------------------------------
#ifndef _ICCTAGHANDLER_H
#define _ICCTAGHANDLER_H

#include "iccObject.h"

class iccTagHandler	:	public iccObject
{
public:
					iccTagHandler(void);
     				~iccTagHandler(void);

virtual	iccTag		*CreateTag(iccTagType inTagType) = 0;
};

#endif	// _ICCTAGHANDLER_H
