#ifndef _H_iccTagMultiLocalizedUnicode_H_
#define _H_iccTagMultiLocalizedUnicode_H_

#include "iccTag.h"
#include "iccDefines.h"
#include "iccError.h"
#include "iccBasicNumericTypes.h"

#include <istream>
#include <ostream>
#include <vector>
#include <map>

ICC_LIB_NAMESPACE_START

class iccTagMultiLocalizedUnicode:	public iccTag
{
public:
	       										iccTagMultiLocalizedUnicode(void)
        										:	m_nbNames(0),m_nameRecordSize(0),
													m_nameRecords(),m_names()
        										{}
        										iccTagMultiLocalizedUnicode(const iccTagMultiLocalizedUnicode& inTag)
        										{
        											*this = inTag;
        										}
    virtual										~iccTagMultiLocalizedUnicode(void)
        										{}
			iccTagMultiLocalizedUnicode&		operator=(const iccTagMultiLocalizedUnicode& inTag);

	virtual	iccNumberUInt32						GetSpecifiedTypeSignature(void) const
        										{
        											return iccParametricCurveType;
        										}

protected:
	virtual	iccError							LoadSelf(std::istream& inStream,unsigned long inSize );
	virtual	iccError							SaveSelf(std::ostream& outStream,unsigned long& outSize) const;
	virtual	unsigned long						GetSizeSelf(void) const;
	virtual	void								InspectSelf(std::vector<iccTagInspector>& outErrorList) const;
	virtual	void								AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList);

private:
	struct languageCode
	{
												languageCode(void)
												: m_languageCode(0),m_countryCode(0)
        										{}
		friend	void							operator>>(std::istream& inStream,languageCode& outLanguage)
												{
													inStream >> outLanguage.m_languageCode;
													inStream >> outLanguage.m_countryCode;
												}
		friend	std::ostream&					operator<<(std::ostream& outStream,const languageCode& inLanguage)
												{
													outStream << inLanguage.m_languageCode;
													outStream << inLanguage.m_countryCode;

													return outStream;
												}
  				languageCode&					operator=(const languageCode &languageCode)
                            					{
            										if(this != &languageCode)
            	                					{
            											m_languageCode	= languageCode.m_languageCode;
                                         				m_countryCode	= languageCode.m_countryCode;
            	                					}
                            						return *this;
                            					}
		static	unsigned long					Size(void)
           										{
           											return 2*sizeof(iccNumberUInt16);
           										}

				iccNumberUInt16					m_languageCode;
				iccNumberUInt16					m_countryCode;
	};
	struct nameRecord
	{
												nameRecord(void)
												: m_language(),m_nameLength(0),m_nameOffset(0)
        										{}

		friend	void							operator>>(std::istream& inStream,nameRecord& outRecord)
												{
													inStream >> outRecord.m_language;
													inStream >> outRecord.m_nameLength;
													inStream >> outRecord.m_nameOffset;
												}
		friend	std::ostream&					operator<<(std::ostream& outStream,const nameRecord& inRecord)
												{
													outStream << inRecord.m_language;
													outStream << inRecord.m_nameLength;
													outStream << inRecord.m_nameOffset;

													return outStream;
												}
   				nameRecord&						operator=(const nameRecord &inRecord)
                            					{
            										if(this != &inRecord)
            	                					{
            											m_language		= inRecord.m_language;
                                        				m_nameLength	= inRecord.m_nameLength;
            											m_nameOffset	= inRecord.m_nameOffset;
            	                					}
                            						return *this;
                            					}
		static	unsigned long					Size(void)
           										{
           											return	languageCode::Size()
															+ 2*sizeof(iccNumberUInt32);
           										}
				languageCode					m_language;
				iccNumberUInt32					m_nameLength;
				iccNumberUInt32					m_nameOffset;
	};

			iccNumberUInt32						m_nbNames;
			iccNumberUInt32						m_nameRecordSize;
			std::vector<nameRecord>				m_nameRecords;
			std::map<languageCode,std::string>	m_names;
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccTagMultiLocalizedUnicode_H_

