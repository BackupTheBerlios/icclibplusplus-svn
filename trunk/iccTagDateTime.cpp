#include "iccTagDateTime.h"

using namespace std;
USING_ICC_LIB_NAMESPACE

//--------------------------------------------------------------------
iccTagDateTime& iccTagDateTime::operator=(const iccTagDateTime& inTag)
{
	if(this != &inTag)
	{
		*(iccTag*)this = *(iccTag*)&inTag;

		m_dateTime = inTag.GetDateTime();
	}
	return *this;
}

//--------------------------------------------------------------------
unsigned long iccTagDateTime::GetSizeSelf(void) const
{
	return	m_dateTime.GetSize();
}

//--------------------------------------------------------------------
iccError iccTagDateTime::LoadSelf(istream& inStream,unsigned long inSize)
{
	inStream >> m_dateTime;
	inSize -= m_dateTime.GetSize();

	return iccErrorNone;
}

//--------------------------------------------------------------------
iccError iccTagDateTime::SaveSelf(ostream& outStream,unsigned long& outSize) const
{
	outStream << m_dateTime;
	outSize += m_dateTime.GetSize();

	return iccErrorNone;
}

//--------------------------------------------------------------------
void iccTagDateTime::InspectSelf(std::vector<iccTagInspector>& outErrorList) const
{
	if(!m_dateTime.IsValid())
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_DATE
								) );
}

//--------------------------------------------------------------------
void iccTagDateTime::AutoCorrectSelf(const vector<iccTagInspector>& inErrorList)
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
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_DATE:
					m_dateTime.AutoCorrect();
					break;
				default:
					break;
			}
	}
}
