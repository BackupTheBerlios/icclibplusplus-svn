//----------------------------------------------------------------------------------------
//	iccTagTable.cpp
//	ICCLib++
//	
//	Creation: 16/10/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------

#include "iccTagTable.h"

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccTagTable::iccTagTable()
{
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccTagTable::~iccTagTable()
{
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
int iccTagTable::AddTag(iccTagTableEntry &inTagEntry)
{
	// Check if tag is not already in the list
	if(m_tagList.find(inTagEntry.m_signature) != m_tagList.end())
		return iccErrorBadParameter;
	
	// Put tag in list
	m_tagList[inTagEntry.m_signature] = inTagEntry;
	
	return iccErrorNone;
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
int iccTagTable::RemoveTag(iccTagSignature inTagSignature)
{
    map<iccTagSignature,iccTagTableEntry>::iterator	tmpIterator;
    
    // Look for tag in the list
	tmpIterator = m_tagList.find(inTagEntry.m_signature);
  	if(tmpIterator == m_tagList.end())
  		return iccErrorTagNotFound;
	
	// Remove tag from list
	m_tagList.erase(tmpIterator);
	
	return iccErrorNone;
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccTag *GetTag(iccTagSignature inTagSignature)
{
    map<iccTagSignature,iccTagTableEntry>::iterator	tmpIterator;
    
    // Look for tag in the list
	tmpIterator = m_tagList.find(inTagEntry.m_signature);
  	if(tmpIterator == m_tagList.end())
  		return NULL;

	if(tmpIterator->second.m_tag != NULL)
		return tmpIterator->second.m_tag;

	// Allocate Tag
	iccTagFactory tagFactory = iccTagFactory::GetInstance();
	if(iccTagFactory == NULL)
		return NULL;
	tmpIterator->second.m_tag = iccTagFactory->CreateTag();
}    
