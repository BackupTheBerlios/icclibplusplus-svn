//----------------------------------------------------------------------------------------
//	iccHeader.h
//	ICCLib++
//
//	Creation: 09/10/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------
// $HEADER$
//----------------------------------------------------------------------------------------
#ifndef _ICCHEADER_H
#define _ICCHEADER_H

/**
 *	Structur that holds the profile header.
 */
typedef struct _iccHeader
{
    iccUInt32Number		m_size;				///< Profile size
    iccUInt32Number		m_CMMType;			///< Prefered CMM
    iccUInt32Number		m_version;			///< Profile version
    iccUInt32Number		m_deviceClass;		///< Profile device class
    iccUInt32Number		m_dataColorSpace;	///< Data color space
    iccUInt32Number		m_PCSColorSpace;	///< PCS color space
    iccDateTimeNumber	m_date;				///< Creation date
    iccUInt32Number		m_profileSignature;	///< Profile signature ('acsp')
    iccUInt32Number		m_platform;			///< Profile primary platform
    iccUInt32Number		m_flags;			///< CMM options
    iccUInt32Number		m_manufacturer;		///< Device manufacturer
    iccUInt32Number		m_model;			///< Device model
    iccUInt32Number		m_attributes;		///< Device attributes
    iccUInt32Number		m_renderingIntent;	///< Rendering intent
    iccUInt32Number		m_creator;			///< Profile creator
    unsigned char[16]	m_ID;				///< Profile ID
    unsigned char[28]	m_reserved;			///< Reserved for future expansion.
} iccHeader;

#endif	// _ICCHEADER_H
