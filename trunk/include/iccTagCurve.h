#ifndef _H_iccTagCurve_H_
#define _H_iccTagCurve_H_

#include "iccTag.h"
#include "iccDefines.h"
#include <vector>

ICC_LIB_NAMESPACE_START

class iccTagCurve:	public iccTag
{
public:
        									iccTagCurve(void)
        									:m_count(0),m_values()
        									{};
        									iccTagCurve(const iccTagCurve& inTag)
        									{
        										*this = inTag;
        									};
        									iccTagCurve(const iccTagCurve* inTag)
            								{
            									if(inTag != NULL)
                									*this = *inTag;
            								}
    virtual									~iccTagCurve(void)
        									{};

			iccTagCurve&					operator=(const iccTagCurve& inTag);

	virtual	iccNumberUInt32					GetSpecifiedTypeSignature(void) const
											{
            									return iccCurveType;
            								}
			iccNumberUInt32					GetCount(void) const
        									{
        										return m_count;
        									};
    const	std::vector<iccNumberUInt16>&	GetValues(void) const
        									{
        										return m_values;
        									};
			void							SetValues(const std::vector<iccNumberUInt16>& inValues)
        									{
        										m_count = inValues.size();
        										m_values = inValues;
        									};

protected:
	virtual	iccError						LoadSelf(std::istream& inStream,unsigned long inSize);
	virtual	iccError						SaveSelf(std::ostream& outStream,unsigned long& outSize) const;
	virtual	unsigned long					GetSizeSelf(void) const;
	virtual	void							InspectSelf(std::vector<iccTagInspector>& outErrorList) const;
	virtual	void							AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList);

private:
			iccNumberUInt32					m_count;
       		std::vector<iccNumberUInt16>	m_values;
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccTagCurve_H_
