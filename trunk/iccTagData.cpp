#include "iccTagData.h"

using namespace std;
USING_ICC_LIB_NAMESPACE

//--------------------------------------------------------------------
iccTagData& iccTagData::operator=(const iccTagData& inTag)
{
	if(this != &inTag)
	{
		*(iccTag*)this = *(iccTag*)&inTag;

		m_dataFlag = inTag.GetDataFlag();
		m_string.clear();
		m_string = inTag.GetString();
	}
	return *this;
}

//--------------------------------------------------------------------
unsigned long iccTagData::GetSizeSelf(void) const
{
	return	sizeof m_dataFlag
			+ m_string.size();
}

//--------------------------------------------------------------------
iccError iccTagData::LoadSelf(istream& inStream,unsigned long inSize)
{
	iccNumberUInt32		tmpUInt32	= 0,
						i			= 0;
	long				insize		= inSize;
	char				readChar	= 0;
	
	inStream >> m_dataFlag;
	insize -= sizeof m_dataFlag;

	m_string.clear();
	m_count = 0;
	while(0 < insize)
	{
    	inStream.get(readChar);
    	m_string.push_back(readChar);
    	insize--;
    	m_count++;
	}
   	m_string.push_back(0);

	return iccErrorNone;
}

//--------------------------------------------------------------------
iccError iccTagData::SaveSelf(ostream& outStream,unsigned long& outSize) const
{
	outStream << m_dataFlag;
	outSize += sizeof m_dataFlag;

	if(!m_string.empty())
		outStream << m_string;
	outSize += m_string.size();

	return iccErrorNone;
}

//--------------------------------------------------------------------
void iccTagData::InspectSelf(std::vector<iccTagInspector>& outErrorList) const
{
	if(
		m_dataFlag == ICC_TAG_DATA_TYPE_ASCII
		&& m_string[m_count - 1] != 0
	)
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_STRING,
									iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_STRING
								) );
}

//--------------------------------------------------------------------
void iccTagData::AutoCorrectSelf(const vector<iccTagInspector>& inErrorList)
{
	vector<iccTagInspector>::const_iterator	itError,
											itErrorEnd;

	for(itError=inErrorList.begin(),itErrorEnd=inErrorList.end(); itError!=itErrorEnd; itError++)
	{
		if(
			itError->GetTagSignature() == GetSignature()
			&& itError->GetTagTypeSignature() == GetTypeSignature()
			&& itError->IsAutoCorrective()
		)
			switch(itError->GetSpecificError())
			{
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_STRING:
					m_string[m_count - 1] = 0;
					break;
				default:
					break;
			}
	}
}
