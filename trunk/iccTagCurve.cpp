#include "iccTagCurve.h"

using namespace std;
USING_ICC_LIB_NAMESPACE

//--------------------------------------------------------------------
iccTagCurve& iccTagCurve::operator=(const iccTagCurve& inTag)
{
	if(this != &inTag)
	{
		*(iccTag*)this = *(iccTag*)&inTag;

		m_count = inTag.m_count;
		m_values = inTag.m_values;
	}
	return *this;
}

//--------------------------------------------------------------------
unsigned long iccTagCurve::GetSizeSelf(void) const
{
	unsigned long	outSize	= 0;
	
	outSize = sizeof m_count;
	if(!m_values.empty())
		outSize += m_values.size() * sizeof m_values[0];
	
	return outSize;
}

//--------------------------------------------------------------------
iccError iccTagCurve::LoadSelf(istream& inStream,unsigned long inSize)
{
	iccNumberUInt16		tmp		= 0;
	long				insize	= inSize;
	
	inStream >> m_count;
	insize -= sizeof m_count;

	m_values.clear();
	while(0 < insize)
	{
    	m_values.push_back(tmp);
		insize -= sizeof tmp;
	}

	return iccErrorNone;
}

//--------------------------------------------------------------------
iccError iccTagCurve::SaveSelf(ostream& outStream,unsigned long& outSize) const
{
	outStream << m_count;
	outSize += sizeof m_count;

	if(!m_values.empty())
	{
		vector<iccNumberUInt16>::const_iterator	itUInt16;

    	for(itUInt16=m_values.begin();
			itUInt16<m_values.end();
			itUInt16++)
    	{
   	    	outStream << *itUInt16;
			outSize += sizeof *itUInt16;
    	}
	}

	return iccErrorNone;
}

//--------------------------------------------------------------------
void iccTagCurve::InspectSelf(std::vector<iccTagInspector>& outErrorList) const
{
	if(m_count != m_values.size())
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_COUNT_VALUE
								) );
}

//--------------------------------------------------------------------
void iccTagCurve::AutoCorrectSelf(const vector<iccTagInspector>& inErrorList)
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
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_COUNT_VALUE:
					m_count = m_values.size();
					break;
				default:
					break;
			}
	}
}
