#ifndef _H_iccTagParametricCurve_H_
#define _H_iccTagParametricCurve_H_

#include "iccTag.h"
#include "iccBasicNumericTypes.h"
#include "iccDefines.h"
#include <istream>
#include <ostream>
#include <vector>

ICC_LIB_NAMESPACE_START

class iccTagParametricCurve:	public iccTag
{
public:
enum
{
	FCT_TYPE_GAMMA	= 0L,
	FCT_TYPE_CIE_122_1966,
	FCT_TYPE_IEC_61966_3,
	FCT_TYPE_IEC_61966_2_1,
	FCT_TYPE_5,
	FCT_TYPE_MAX
};
            									iccTagParametricCurve(void)
                								: m_functionType(FCT_TYPE_GAMMA),m_reserved2(0),m_parameters()
                								{}
                								iccTagParametricCurve(const iccTagParametricCurve& inTag)
                								{
                									*this = inTag;
                								}
                								iccTagParametricCurve(const iccTagParametricCurve* inTag)
                								{
                									if(inTag != NULL)
	                									*this = *inTag;
                								}
	virtual										~iccTagParametricCurve()
												{};

			iccTagParametricCurve&				operator=(const iccTagParametricCurve& inTag);

	virtual	iccNumberUInt32						GetSpecifiedTypeSignature(void) const
        										{
        											return iccParametricCurveType;
        										};
			iccNumberUInt16						GetFunctionType(void) const
            									{
            										return m_functionType;
            									}
			iccNumberUInt16						GetReserved2(void) const
            									{
            										return m_reserved2;
            									}
	const	std::vector<iccNumberS15Fixed16>&	GetParameters(void) const
            									{
            										return m_parameters;
            									}
			void								SetFunctionType(iccNumberUInt16 inType)
            									{
            										m_functionType = inType;
            									}
			void								SetParameters(const	std::vector<iccNumberS15Fixed16>& inParameters)
            									{
            										m_parameters = inParameters;
            									}

protected:
	virtual	iccError							LoadSelf(std::istream& inStream,unsigned long inSize);
	virtual	iccError							SaveSelf(std::ostream& outStream,unsigned long& outSize) const;
	virtual	unsigned long						GetSizeSelf(void) const;
	virtual	void								InspectSelf(std::vector<iccTagInspector>& outErrorList) const;
	virtual	void								AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList);

private:
			iccNumberUInt16						m_functionType;
			iccNumberUInt16						m_reserved2;
			std::vector<iccNumberS15Fixed16>	m_parameters;
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccTagParametricCurve_H_

