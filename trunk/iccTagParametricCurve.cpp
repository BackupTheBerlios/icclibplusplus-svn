#include "iccTagParametricCurve.h"

using namespace std;
USING_ICC_LIB_NAMESPACE

const unsigned short	kNbParameters[] = {1, 3, 4, 5, 7};

//--------------------------------------------------------------------
iccTagParametricCurve& iccTagParametricCurve::operator=(const iccTagParametricCurve& inTag)
{
	if(this != &inTag)
	{
		*(iccTag*)this = *(iccTag*)&inTag;

		m_functionType	= inTag.GetFunctionType();
		m_reserved2		= inTag.GetReserved2();
		m_parameters	= inTag.GetParameters();
	}
	return *this;
}

//--------------------------------------------------------------------
unsigned long iccTagParametricCurve::GetSizeSelf(void) const
{
	unsigned long outSize	= 0;
	
	outSize =	sizeof m_functionType
				+ sizeof m_reserved2;
	if(!m_parameters.empty())
		outSize += m_parameters.size() * m_parameters[0].GetSize();
	
	return outSize;
}

//--------------------------------------------------------------------
iccError iccTagParametricCurve::LoadSelf(istream& inStream,unsigned long inSize)
{
	iccNumberS15Fixed16	tmpFixed;
	long				insize	= inSize;
	unsigned short		i		= 0;

	inStream >> m_functionType;
	insize -= sizeof m_functionType;
	if(insize <= 0)
		return iccErrorRead;

	inStream >> m_reserved2;
	insize -= sizeof m_reserved2;
	if(insize <= 0)
		return iccErrorRead;

	m_parameters.clear();
	for(i=0; i<kNbParameters[m_functionType] && 0<=insize; i++)
	{
    	inStream >> tmpFixed;
		m_parameters.push_back(tmpFixed);
    	insize -= tmpFixed.GetSize();
	}

	if(insize != 0)
		return iccErrorRead;;
	
	return iccErrorNone;
}

//--------------------------------------------------------------------
iccError iccTagParametricCurve::SaveSelf(ostream& outStream,unsigned long& outSize) const
{
	unsigned short	i	= 0;

	outStream << m_functionType;
	outSize += sizeof m_functionType;

	outStream << m_reserved2;
	outSize += sizeof m_reserved2;

	for(i=0; i<kNbParameters[m_functionType]; i++)
	{
		outStream << m_parameters[i];
    	outSize += m_parameters[i].GetSize();
	}

	return iccErrorNone;
}

//--------------------------------------------------------------------
void iccTagParametricCurve::InspectSelf(std::vector<iccTagInspector>& outErrorList) const
{
	if(FCT_TYPE_MAX <= m_functionType)
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MAJOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_ERROR_PARAMETRIC_CURVE_BAD_FUNCTION_TYPE
								) );
	else
	if(m_parameters.size() != kNbParameters[m_functionType])
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_ELEMENT_COUNT_MISMATCH,
									iccTagInspector::ICC_TAG_ERROR_PARAMETRIC_CURVE_NB_PARAMETERS_MISMATCH
								) );

	if(m_reserved2 != 0)
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_ERROR_PARAMETRIC_CURVE_BAD_RESERVED_VALUE
								) );
}

//--------------------------------------------------------------------
void iccTagParametricCurve::AutoCorrectSelf(const vector<iccTagInspector>& inErrorList)
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
				case iccTagInspector::ICC_TAG_ERROR_PARAMETRIC_CURVE_BAD_FUNCTION_TYPE:
					m_functionType = 0;
					m_parameters.clear();
					m_parameters.push_back(iccNumberS15Fixed16(0F));
					break;
				case iccTagInspector::ICC_TAG_ERROR_PARAMETRIC_CURVE_BAD_RESERVED_VALUE:
					m_reserved2 = 0;
					break;
				case iccTagInspector::ICC_TAG_ERROR_PARAMETRIC_CURVE_NB_PARAMETERS_MISMATCH:
					unsigned long	i		= 0,
									imax	= 0;
					m_parameters.erase(m_parameters.begin()+kNbParameters[m_functionType], m_parameters.end());
					for(i=m_parameters.size(); i<kNbParameters[m_functionType]; i++)
						m_parameters.push_back(iccNumberS15Fixed16(0F));
					break;
				default:
					break;
			}
	}
}
