//----------------------------------------------------------------------------------------
//	iccTagTable.h
//	ICCLib++
//	
//	Creation: 16/10/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//	iccTagTable.h
//	ICCLib++
//
//	Creation: 23/10/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------
// $HEADER$
//----------------------------------------------------------------------------------------
#ifndef _ICCTAGTABLE_H
#define _ICCTAGTABLE_H

#include <map>

#include "iccObject.h"
#include "iccTag.h"

typedef iccUInt32Number iccTagSignature;

typedef struct _iccTagTableEntry
{
    iccTagSignature	m_signature;
    iccUInt32Number	m_offset;
    iccUInt32Number	m_size;
    iccTag			*m_tag;
} iccTagTableEntry;

class iccTagTable	:	public iccObject
{
public:
    								iccTagTable(void);
virtual    							~iccTagTable(void);
   
virtual	int							AddTag(iccTagTableEntry &inTagEntry);
virtual	int							RemoveTag(iccTagSignature inTagSignature);

virtual	iccTag						*GetTag(iccTagSignature inTagSignature);

private:
    std::map<iccTagSignature,iccTagTableEntry>	m_tagList;
};

#endif	// _ICCTAGTABLE_H
