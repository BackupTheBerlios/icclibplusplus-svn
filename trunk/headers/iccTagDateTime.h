#ifndef _H_iccTagDateTime_H_
#define _H_iccTagDateTime_H_

#include "iccTag.h"
#include "iccNumberDateTime.h"
#include "iccDefines.h"

ICC_LIB_NAMESPACE_START

class iccTagDateTime:	public iccTag
{
public:
	       									iccTagDateTime(void)
        									:m_dateTime()
        									{};
        									iccTagDateTime(const iccTagDateTime& inTag)
        									{
        										*this = inTag;
        									};
    virtual									~iccTagDateTime(void)
        									{};
	
			iccTagDateTime&					operator=(const iccTagDateTime& inTag);

	virtual	iccNumberUInt32					GetSpecifiedTypeSignature(void)
        									{
        										return iccDateTimeType;
        									};
    const	iccNumberDateTime&				GetDateTime(void) const
        									{
        										return m_dateTime;
        									};
			void							SetDateTime(const iccNumberDateTime& inDateTime)
        									{
 												m_dateTime = inDateTime;
       										};

protected:
	virtual	iccError						LoadSelf(std::istream& inStream,unsigned long inSize );
	virtual	iccError						SaveSelf(std::ostream& outStream,unsigned long& outSize) const;
	virtual	unsigned long					GetSizeSelf(void) const;
	virtual	void							InspectSelf(std::vector<iccTagInspector>& outErrorList) const;
	virtual	void							AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList);

private:
			iccNumberDateTime				m_dateTime;
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccTagDateTime_H_

