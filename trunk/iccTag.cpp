#include "iccTag.h"

using namespace std;
USING_ICC_LIB_NAMESPACE

//--------------------------------------------------------------------
iccTag& iccTag::operator=(const iccTag& inTag)
{
	if(this != &inTag)
	{
		m_typeSignature = inTag.m_typeSignature;
		m_reserved = inTag.m_reserved;
	}
	return *this;
}

//--------------------------------------------------------------------
iccError iccTag::Load(std::istream& inStream,unsigned long inSize)
{
	// Type signature
	inStream >> m_typeSignature;
	inSize -= sizeof m_typeSignature;
	
	// 4-bytes reserved
	inStream >> m_reserved;
	inSize -= sizeof m_reserved;
	
	// Load tag contents
	LoadSelf(inStream, inSize);

	return iccErrorNone;
}

//--------------------------------------------------------------------
iccError iccTag::Save(std::ostream& outStream,unsigned long& outSize) const
{
	outStream << m_typeSignature;
	outSize += sizeof m_typeSignature;

	outStream << m_reserved;
	outSize += sizeof m_reserved;

	SaveSelf(outStream, outSize);

	return iccErrorNone;
}

//--------------------------------------------------------------------
unsigned long iccTag::GetSize(void) const
{
	unsigned long	size	= 0;

	size =	sizeof m_typeSignature
			+ sizeof m_reserved;

	size += GetSizeSelf();

	return size;
}

//--------------------------------------------------------------------
void iccTag::Inspect(std::vector<iccTagInspector>& outErrorList) const
{
	if(m_typeSignature != GetSpecifiedTypeSignature())
	{
		outErrorList.push_back(	iccTagInspector(
									m_signature,
									m_typeSignature,
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_CRITICAL,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_TYPE_SIGNATURE
								) );
	}
	
	if(m_reserved != 0)
	{
		outErrorList.push_back(	iccTagInspector(
									m_signature,
									m_typeSignature,
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_RESERVED_VALUE
								) );
	}

	InspectSelf(outErrorList);
}

//--------------------------------------------------------------------
void iccTag::AutoCorrect(const vector<iccTagInspector>& inErrorList)
{
	vector<iccTagInspector>::const_iterator	itError,
											itErrorEnd;

	for(itError=inErrorList.begin(),itErrorEnd=inErrorList.end(); itError!=itErrorEnd; itError++)
	{
		if(
			itError->GetTagSignature() == m_signature
			&& itError->GetTagTypeSignature() == m_typeSignature
			&& itError->IsAutoCorrective()
		)
			switch(itError->GetSpecificError())
			{
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_TYPE_SIGNATURE:
					m_typeSignature = GetSpecifiedTypeSignature();
					break;
				case iccTagInspector::ICC_TAG_SPECIFIC_ERROR_BAD_RESERVED_VALUE:
					m_reserved = 0;
					break;
				default:
					break;
			}
	}
	
	AutoCorrectSelf(inErrorList);
}
