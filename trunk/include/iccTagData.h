#ifndef _H_iccTagData_H_
#define _H_iccTagData_H_

#include "iccTag.h"
#include "iccDefines.h"

ICC_LIB_NAMESPACE_START

class iccTagData:	public iccTag
{
public:
	enum
	{
		ICC_TAG_DATA_TYPE_ASCII	= 0L,
		ICC_TAG_DATA_TYPE_BINARY
	};
        									iccTagData(void)
        									:m_dataFlag(0),m_string(),m_count(0)
        									{}
        									iccTagData(const iccTagData& inTag)
        									{
        										*this = inTag;
        									}
    virtual									~iccTagData(void)
        									{}

			iccTagData&						operator=(const iccTagData& inTag);

	virtual	iccNumberUInt32					GetSpecifiedTypeSignature(void) const
											{
            									return iccDataType;
            								}
			iccNumberUInt32					GetDataFlag(void) const
	       									{
        										return m_dataFlag;
        									}
    const	std::string&					GetString(void) const
        									{
        										return m_string;
        									}
	virtual void							SetDataFlag(iccNumberUInt32 inFlag)
        									{
        										m_dataFlag = inFlag;
        									};
	virtual void							SetDataFlag(std::string& inString)
        									{
        										m_string = inString;
        									};

protected:
	virtual	iccError						LoadSelf(std::istream& inStream,unsigned long inSize);
	virtual	iccError						SaveSelf(std::ostream& outStream,unsigned long& outSize) const;
	virtual	unsigned long					GetSizeSelf(void) const;
	virtual	void							InspectSelf(std::vector<iccTagInspector>& outErrorList) const;
	virtual	void							AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList);
 
private:
			iccNumberUInt32					m_dataFlag;
			std::string						m_string;
			unsigned long					m_count; ///< String size: not stored in tag
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccTagData_H_
