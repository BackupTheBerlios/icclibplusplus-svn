#include "iccTagColorantTable.h"

#include <iostream>

#define ICC_COLORANT_NAME_LENGTH	32
#define ICC_COLORANT_NB_COORDINATES	3

using namespace std;
USING_ICC_LIB_NAMESPACE

//--------------------------------------------------------------------
iccTagColorantTable::iccColorant&
iccTagColorantTable::iccColorant::operator=
(const iccColorant& inColorant)
{
	if(this != &inColorant)
	{
		name = inColorant.name;
		coordinates = inColorant.coordinates;
	}

	return *this;
}

//--------------------------------------------------------------------
void
operator>>
(istream& inStream,iccTagColorantTable::iccColorant& outColorant)
{
	unsigned long	i	= 0;
	
	outColorant.name.clear();
	for(i=0; i<ICC_COLORANT_NAME_LENGTH; i++)
    	inStream >> outColorant.name[i];

	outColorant.coordinates.clear();
	for(i=0; i<ICC_COLORANT_NB_COORDINATES; i++)
	   	inStream >> outColorant.coordinates[i];
}

//--------------------------------------------------------------------
ostream&
operator<<
(ostream& outStream,const iccTagColorantTable::iccColorant& inColorant)
{
	unsigned long	i		= 0,
					imax	= 0;
	
	for(i=0,imax=inColorant.name.size(); i<imax; i++)
    	outStream << inColorant.name[i];
	for(; i<ICC_COLORANT_NAME_LENGTH; i++)
    	outStream << 0;
	
	for(i=0,imax=inColorant.coordinates.size(); i<imax; i++)
    	outStream << inColorant.coordinates[i];
	for(; i<ICC_COLORANT_NB_COORDINATES; i++)
    	outStream << 0;

	return outStream;
}

//--------------------------------------------------------------------
unsigned long
iccTagColorantTable::iccColorant::GetSize
(void)
const
{
	return ICC_COLORANT_NAME_LENGTH + 3*sizeof(iccNumberUInt16);
}

//--------------------------------------------------------------------
iccTagColorantTable& iccTagColorantTable::operator=(const iccTagColorantTable& inTag)
{
	if(this != &inTag)
	{
		*(iccTag*)this = *(iccTag*)&inTag;

		m_count = inTag.m_count;
		m_colorants = inTag.m_colorants;
		m_requiredNbChannels = inTag.m_requiredNbChannels;
	}
	return *this;
}

//--------------------------------------------------------------------
unsigned long iccTagColorantTable::GetSizeSelf(void) const
{
	unsigned long	outSize	= 0;
	
	outSize = sizeof m_count;
	if(!m_colorants.empty())
		outSize += m_colorants.size() * m_colorants[0].GetSize();

	return outSize;
}

//--------------------------------------------------------------------
iccError iccTagColorantTable::LoadSelf(istream& inStream,unsigned long inSize)
{
	iccColorant		tmpColorant;
	long			insize	= inSize;
	
	inStream >> m_count;
	insize -= sizeof m_count;
	
	m_colorants.clear();
	while(0 < insize)
	{
    	inStream >> tmpColorant;
		m_colorants.push_back(tmpColorant);
		insize -= tmpColorant.GetSize();
 	}
	
	return iccErrorNone;
}

//--------------------------------------------------------------------
iccError iccTagColorantTable::SaveSelf(ostream& outStream,unsigned long& outSize) const
{
	outStream << m_count;
	outSize += sizeof m_count;

	if(!m_colorants.empty())
	{
		vector<iccColorant>::const_iterator	itColorant,
											itColorantEnd;

    	for(itColorant=m_colorants.begin(),
				itColorantEnd=m_colorants.end();
			itColorant<itColorantEnd;
			itColorant++)
    	{
	    	outStream << *itColorant;
	    	outSize += itColorant->GetSize();
  		}
	}

	return iccErrorNone;
}

//--------------------------------------------------------------------
void iccTagColorantTable::InspectSelf(std::vector<iccTagInspector>& outErrorList) const
{
	vector<iccColorant>::const_iterator	itColorant,
										itColorantEnd;

	if(m_requiredNbChannels == 0)
		cerr	<< "Error detected in file " << __FILE__
				<< ", line " << __LINE__
				<< ": The number of channels corresponding to profile color space hasn't been set."
				<< endl;

	// Check that number of colorants matches number of channels corresponding to profile color space
	if(m_colorants.size() != m_requiredNbChannels)
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_COLORANT_COUNT_IN_TABLE
								) );
	else
	if(m_count != m_colorants.size())
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_SPECIFIC_ERROR_COLORANT_COUNT_IN_TABLE_MISMATCH
								) );

	for(itColorant=m_colorants.begin(),
			itColorantEnd=m_colorants.end();
		itColorant<itColorantEnd;
		itColorant++)
	{
		if(ICC_COLORANT_NAME_LENGTH < itColorant->name.size())
		{
			outErrorList.push_back(	iccTagInspector(
										GetSignature(),
										GetTypeSignature(),
										iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
										true,
										iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_STRING,
										iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_COLORANT_NAME
									) );
			break;
		}
	}

	for(itColorant=m_colorants.begin(),
			itColorantEnd=m_colorants.end();
		itColorant<itColorantEnd;
		itColorant++)
	{
		if(itColorant->coordinates.size() != ICC_COLORANT_NB_COORDINATES)
		{
			outErrorList.push_back(	iccTagInspector(
										GetSignature(),
										GetTypeSignature(),
										iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
										true,
										iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_STRING,
										iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_COLORANT_COORDINATES
									) );
			break;
		}
	}
}

//--------------------------------------------------------------------
void iccTagColorantTable::AutoCorrectSelf(const vector<iccTagInspector>& inErrorList)
{
	vector<iccTagInspector>::const_iterator	itError,
											itErrorEnd;
	vector<iccColorant>::iterator			itColorant,
											itColorantEnd;
	unsigned long							i	= 0;

	for(itError=inErrorList.begin(),itErrorEnd=inErrorList.end(); itError!=itErrorEnd; itError++)
	{
		if(
			itError->GetTagSignature() == GetSignature()
			&& itError->GetTagTypeSignature() == GetTypeSignature()
			&& itError->IsAutoCorrective()
		)
			switch(itError->GetSpecificError())
			{
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_COLORANT_COUNT_IN_TABLE:
					for(itColorant=m_colorants.begin(),
							itColorantEnd=m_colorants.end();
						itColorant<itColorantEnd;
						itColorant++)
					{
						// Remove supernumerary coordinates
						itColorant->coordinates.erase(
										itColorant->coordinates.begin() + m_requiredNbChannels,
										itColorant->coordinates.end()
									);
						// Add missing coordinates
						for(i=itColorant->coordinates.size(); i<m_requiredNbChannels; i++)
							itColorant->coordinates.push_back((iccNumberUInt16)0);
					}
					// no break
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_COLORANT_COUNT_IN_TABLE_MISMATCH:
					m_count = m_colorants.size();
					break;
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_COLORANT_NAME:
					for(itColorant=m_colorants.begin(),
							itColorantEnd=m_colorants.end();
						itColorant<itColorantEnd;
						itColorant++)
					{
						if(ICC_COLORANT_NAME_LENGTH <= itColorant->name.size())
							itColorant->name.erase(ICC_COLORANT_NAME_LENGTH-1, string::npos);
						itColorant->name[ICC_COLORANT_NAME_LENGTH-1] = 0;
					}
					break;
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_COLORANT_COORDINATES:
					// What can it be ?
					break;
				default:
					break;
			}
	}
}
