//----------------------------------------------------------------------------------------
//	iccTagFactory.cpp
//	ICCLib++
//
//	Creation: 23/10/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------

#include "iccTagFactory.h"
#include "iccUnknownTag.h"

iccTagFactory	*iccTagFactory::s_instance	= NULL;

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccTagFactory::iccTagFactory()
{
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccTagFactory::~iccTagFactory()
{
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
void iccTagFactory::Initialize()
{
	if(s_instance == NULL)
		s_instance = new iccTagFactory;
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
void iccTagFactory::Terminate()
{
	if(s_instance != NULL)
		delete s_instance;

	s_instance = NULL;
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
void iccTagFactory::PushHandler(iccTagHandler *inHandler)
{
 	if(inHandler != NULL)
 		m_dynamicHandlers.push_back(inHandler);
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccTagHandler *iccTagFactory::PopHandler()
{
	iccTagHandler	*outHandler	= NULL;
	int				i			= 0;

	i = m_dynamicHandlers.size() - 1;
	if(i >= 0)
	{
		outHandler = m_dynamicHandlerList[i];
		m_dynamicHandlers.pop_back();
	}

	return outHandler;
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccTag *iccTagFactory::CreateTag(iccTagType inTagType)
{
	int		i		= 0;
    iccTag	*outTag	= NULL;

	// First try dynamic handlers
	i = m_dynamicHandlers.size() - 1;
	while(i-- >= 0)
	{
  		outTag = m_dynamicHandlerList[i]->CreateTag(inTagType);
    	if(outTag != NULL)
    		return outTag;
	}

	// Try to allocate tag as a standard tag
	CreateStandardTag(inTagType);
	
	return outTag;
}

iccTag *iccTagFactory::CreateStandardTag(iccTagType inTagType)
{
    iccTag	*outTag	= NULL;

	switch(inTagType)
	{
	default:
		outTag = new iccUnknownTag();
		break;
	}

	return outTag;
}
