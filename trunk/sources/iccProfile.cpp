//----------------------------------------------------------------------------------------
//	iccProfile.cpp
//	ICCLib++
//	
//	Creation: 16/10/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------

#include "iccProfile.h"

#include "iccError.h"

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccProfile::iccProfile()
{
    memset(m_header,0,sizeof(iccHeader));
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
iccProfile::~iccProfile()
{
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
int iccProfile::ReadHeader()
{
	int	i	= 0;

    if(m_inputStream == NULL)
    	return iccErrorIOError;
    
    // Go to the begining of the stream
    m_inputStream.seekg(0);

    // Read header values
    m_stream >> m_header.m_size;
    m_stream >> m_header.m_CMMType;
    m_stream >> m_header.m_version;
    m_stream >> m_header.m_deviceClass;
    m_stream >> m_header.m_dataColorSpace;
    m_stream >> m_header.m_PCSColorSpace;
    
    m_stream >> m_header.m_date.year;
    m_stream >> m_header.m_date.month;
    m_stream >> m_header.m_date.day;
    m_stream >> m_header.m_date.hours;
    m_stream >> m_header.m_date.minutes;
    m_stream >> m_header.m_date.seconds;
    
    m_stream >> m_header.m_profileSignature;
    m_stream >> m_header.m_platform;
    m_stream >> m_header.m_flags;
    m_stream >> m_header.m_manufacturer;
    m_stream >> m_header.m_model;
    m_stream >> m_header.m_attributes;
    m_stream >> m_header.m_renderingIntent;
    m_stream >> m_header.m_creator;
   	
	for(i=0; i<16; i++)
    	inStream >> m_header.m_ID[i];
	for(i=0; i<28; i++)
    	inStream >> m_header.m_reserved[i];
}

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
int iccProfile::ReadTagTable()
{
	int					nbTags		= 0;
	iccTagTableEntry	tmpEntry	= {0};
	
    if(m_stream == NULL)
    	return iccErrorIOError;
    	
    // Check if stream is an input stream	
    if(dynamic_cast<istream>(m_stream) == NULL)
    	return iccErrorIOError;
    	
    // Go to the begining of the tag table in the stream
    m_stream.seekg(128);
    
	// Load the number of tags
	m_stream >> nbTags;
	
	// Read tag entries
	while(nbTags--)
	{
		m_stream >> tmpEntry.m_signature;
		m_stream >> tmpEntry.m_offset;
		m_stream >> tmpEntry.m_size;
		tmpEntry.m_tag = NULL;
		m_tagTable.AddTag(tmpEntry);
	}    
}     
