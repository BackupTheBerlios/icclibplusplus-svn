//----------------------------------------------------------------------------------------
//	iccUnknownTag.cpp
//	ICCLib++
//
//	Creation: 20/11/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------
// $HEADER$
//----------------------------------------------------------------------------------------

#include "iccUnknownTag.h"

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccUnknownTag::iccUnknownTag()
{
    m_data	= NULL;
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccUnknownTag::~iccUnknownTag()
{
	FreeData();
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccUnknownTag::FreeData()
{
	if(m_data != NULL)
	{
		free(m_data);
		m_data = NULL;
	}
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
void iccUnknownTag::SetSize(unsigned long inSize)
{
	if(m_data == NULL)
		iccTag::SetSize(inSize);
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccError iccUnknownTag::Load(std::istream& inInputStream)
{
	iccUInt32Number		tmpUInt32	= 0;
	iccUInt32Number		i			= 0;

	// Read tag type
	inInputStream >> tmpUInt32;
	SetTypeSignature(tmpUInt32);
	
	// Size must have been previously set
	if(m_size == 0)
		return iccErrorBadParameter;

	// Allocate a new data buffer
	FreeData();
	m_data = (char *) calloc(GetSize(),1);
	if(m_data = NULL)
		return iccErrorNotEnoughMemory;

	// Load tag data
	for(i=0;i<GetSize()i++)
		inInputStream >> m_data[i];

	return iccErrorNone;
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccError iccUnknownTag::Save(std::ostream& inOutputStream)
{
	iccUInt32Number	i	= 0;

	// Save tag type
	inOutputStream << GetTypeSignature();

	// Check if data buffer  is present
	if(m_data == NULL)
		return iccErrorNoData;

	// Save data buffer
	for(i=0;i<GetSize()i++)
		inOutputStream << m_data[i];
}
