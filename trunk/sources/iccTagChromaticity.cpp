#include "iccTagChromaticity.h"

#include <string.h>

#define	MINIMUM_NUMBER_OF_DEVICE_CHANNELS	3

using namespace std;
USING_ICC_LIB_NAMESPACE

const iccTagChromaticity::iccCieXyCoordinates	kZeroCieXyCoordinates[] = {0F};
const iccTagChromaticity::iccCieXyCoordinates	kITU_R_BT_709CieXyCoordinates[] =
{
	{iccNumberU16Fixed16(0.640), iccNumberU16Fixed16(0.330)},
	{iccNumberU16Fixed16(0.300), iccNumberU16Fixed16(0.600)},
	{iccNumberU16Fixed16(0.150), iccNumberU16Fixed16(0.060)}
};
const iccTagChromaticity::iccCieXyCoordinates	kSMPTE_RP145_1994CieXyCoordinates[] =
{
	{iccNumberU16Fixed16(0.630), iccNumberU16Fixed16(0.340)},
	{iccNumberU16Fixed16(0.310), iccNumberU16Fixed16(0.595)},
	{iccNumberU16Fixed16(0.155), iccNumberU16Fixed16(0.070)}
};
const iccTagChromaticity::iccCieXyCoordinates	kEBU_Tech_2113_ECieXyCoordinates[] =
{
	{iccNumberU16Fixed16(0.64), iccNumberU16Fixed16(0.330)},
	{iccNumberU16Fixed16(0.29), iccNumberU16Fixed16(0.600)},
	{iccNumberU16Fixed16(0.15), iccNumberU16Fixed16(0.060)}
};
const iccTagChromaticity::iccCieXyCoordinates	kP22CieXyCoordinates[] =
{
	{iccNumberU16Fixed16(0.625), iccNumberU16Fixed16(0.340)},
	{iccNumberU16Fixed16(0.280), iccNumberU16Fixed16(0.605)},
	{iccNumberU16Fixed16(0.155), iccNumberU16Fixed16(0.070)}
};
const iccTagChromaticity::iccCieXyCoordinates	*kCieXyCoordinates[] =
{
	kZeroCieXyCoordinates,
	kITU_R_BT_709CieXyCoordinates,
	kSMPTE_RP145_1994CieXyCoordinates,
	kEBU_Tech_2113_ECieXyCoordinates,
	kP22CieXyCoordinates
};

//--------------------------------------------------------------------
iccTagChromaticity::iccCieXyCoordinates&
iccTagChromaticity::iccCieXyCoordinates::operator=
(const iccCieXyCoordinates& inCoordinates)
{
	if(this != &inCoordinates)
	{
		x = inCoordinates.x;
		y = inCoordinates.y;
	}
	return *this;
}

//--------------------------------------------------------------------
bool
iccTagChromaticity::iccCieXyCoordinates::operator==
(const iccCieXyCoordinates& inCoordinates)
const
{
	if(x==inCoordinates.x && y==inCoordinates.y)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------
bool
iccTagChromaticity::iccCieXyCoordinates::operator!=
(const iccCieXyCoordinates& inCoordinates)
const
{
	return ! operator==(inCoordinates);
}


//--------------------------------------------------------------------
void
operator>>
(istream& inStream,iccTagChromaticity::iccCieXyCoordinates& outCoordinates)
{
	inStream >> outCoordinates.x;
	inStream >> outCoordinates.y;
}

//--------------------------------------------------------------------
ostream&
operator<<
(ostream& outStream,const iccTagChromaticity::iccCieXyCoordinates& inCoordinates)
{
	outStream << inCoordinates.x;
	outStream << inCoordinates.y;
	
	return outStream;
}

//--------------------------------------------------------------------
unsigned long
iccTagChromaticity::iccCieXyCoordinates::GetSize
(void)
const
{
	return	x.GetSize()
			+ y.GetSize();
}

//--------------------------------------------------------------------
void iccTagChromaticity::SetEncodedValue(iccNumberUInt16 inValue)
{
	m_encodedValue = inValue;
#pragma message("TO DO: set coordinate values")
	switch(m_encodedValue)
	{
		case unknownColorant:
			break;
		case ITU_R_BT_709:
			break;
		case SMPTE_RP145_1994:
			break;
		case EBU_Tech_2113_E:
			break;
		case P22:
			break;
		default:
			break;
	}
}

//--------------------------------------------------------------------
void iccTagChromaticity::SetCoordinates(std::vector<iccCieXyCoordinates> inCoordinates)
{
#pragma message("TO DO: set coordinate values")
}

//--------------------------------------------------------------------
iccTagChromaticity&	iccTagChromaticity::operator=(const iccTagChromaticity& inTag)
{
	if(this != &inTag)
	{
		*(iccTag*)this = *(iccTag*)&inTag;

		m_nbChannels = inTag.GetNbChannels();
		m_encodedValue = inTag.GetEncodedValue();
		m_coordinates = inTag.m_coordinates;
	}
	return *this;
}

//--------------------------------------------------------------------
unsigned long iccTagChromaticity::GetSizeSelf(void) const
{
	unsigned long	outSize	= 0;
	
	outSize = 	sizeof m_nbChannels
				+ sizeof m_encodedValue;
	if(!m_coordinates.empty())
		outSize += m_coordinates.size() * m_coordinates[0].GetSize();

	return outSize;
}

//--------------------------------------------------------------------
iccError iccTagChromaticity::LoadSelf(istream& inStream,unsigned long inSize)
{
	iccCieXyCoordinates	tmpCoordinate;
	iccNumberUInt16		tmpUInt16	= 0,
						i			= 0;
	long				insize		= inSize;

	inStream >> m_nbChannels;
	insize -= sizeof m_nbChannels;

	inStream >> m_encodedValue;
	insize -= sizeof m_encodedValue;

	m_coordinates.clear();
	while(0 < insize)
	{
		inStream >> tmpCoordinate;
		m_coordinates.push_back(tmpCoordinate);
		insize -= tmpCoordinate.GetSize();
	}
	
	return iccErrorNone;
}

//--------------------------------------------------------------------
iccError iccTagChromaticity::SaveSelf(ostream& outStream,unsigned long& outSize) const
{
	outStream << m_nbChannels;
	outSize += sizeof m_nbChannels;
	
	outStream << m_encodedValue;
	outSize += sizeof m_encodedValue;

	if(!m_coordinates.empty())
	{
		vector<iccCieXyCoordinates>::const_iterator	itCoordinate,
													itCoordinateEnd;

		for(
			itCoordinate=GetCoordinates().begin(),
				itCoordinateEnd=GetCoordinates().end();
			itCoordinate<itCoordinateEnd;
			itCoordinate++
		)
		{
			outStream << *itCoordinate;
			outSize += itCoordinate->GetSize();
		}
	}

	return iccErrorNone;
}

//--------------------------------------------------------------------
void iccTagChromaticity::InspectSelf(std::vector<iccTagInspector>& outErrorList) const
{
	if(
		m_nbChannels < MINIMUM_NUMBER_OF_DEVICE_CHANNELS
		|| m_nbChannels != m_coordinates.size()
	)
	{
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_CRITICAL,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_NB_CHANNELS
								) );
	}

	// Check validity of colorant value
	if(lastColorantValue <= m_encodedValue)
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_COLORANT_TYPE
								) );
	
	// Check that coordinates match colorant value
	if(
		(m_encodedValue==unknownColorant && AreCoordinatesMatching((iccNumberUInt16)unknownColorant))
		|| !AreCoordinatesMatching(m_encodedValue)
	)
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_CHANNELS_VALUES
								) );
}

//--------------------------------------------------------------------
void iccTagChromaticity::AutoCorrectSelf(const vector<iccTagInspector>& inErrorList)
{
	vector<iccTagInspector>::const_iterator	itError,
											itErrorEnd;
	unsigned long							i		= 0,
											imax	= 0;

	for(itError=inErrorList.begin(),itErrorEnd=inErrorList.end(); itError!=itErrorEnd; itError++)
	{
		if(
			itError->GetTagSignature() == GetSignature()
			&& itError->GetTagTypeSignature() == GetTypeSignature()
			&& itError->IsAutoCorrective()
		)
			switch(itError->GetSpecificError())
			{
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_NB_CHANNELS:
					m_nbChannels = m_coordinates.size();
					break;
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_COLORANT_TYPE:
					for(i=firstColorantValue; i<lastColorantValue; i++)
						if(AreCoordinatesMatching(i))
						{
							m_encodedValue = i;
							break;
						}
					break;
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_CHANNELS_VALUES:
					m_coordinates.clear();
					imax = sizeof kCieXyCoordinates[m_encodedValue] / sizeof kCieXyCoordinates[m_encodedValue][0];
					for(i=0; i<imax; i++)
						m_coordinates.push_back(kCieXyCoordinates[m_encodedValue][i]);
					break;
				default:
					break;
			}
	}
}

//--------------------------------------------------------------------
bool iccTagChromaticity::AreCoordinatesMatching(iccNumberUInt16 inEncoding)
const
{
	unsigned long	i		= 0,
					imax	= 0;
					
	imax = sizeof kCieXyCoordinates[inEncoding] / sizeof kCieXyCoordinates[inEncoding][0];
	imax = (imax < m_coordinates.size()) ? imax : m_coordinates.size();
	
	for(i=0; i<imax; i++)
		if(m_coordinates[i] != kCieXyCoordinates[inEncoding][i])
			return false;

	return true;
}
