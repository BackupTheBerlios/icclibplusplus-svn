#ifndef _H_iccTagColorantTable_H_
#define _H_iccTagColorantTable_H_

#include "iccTag.h"
#include "iccDefines.h"
#include <vector>
#include <string>
#include <ostream>
#include <istream>

ICC_LIB_NAMESPACE_START

class iccTagColorantTable:	public iccTag
{
public:

struct iccColorant{
									iccColorant(void)
									: name(),coordinates()
									{}
	std::string						name;
	std::vector<iccNumberUInt16>	coordinates;
	iccColorant&					operator=(const iccColorant& inColorant);
	friend	void					operator>>(std::istream& inStream,iccColorant& outRecord);
	friend	std::ostream&			operator<<(std::ostream& outStream,const iccColorant& inRecord);
	unsigned long					GetSize(void) const;
};

            								iccTagColorantTable(void)
            								:m_count(0),m_colorants(),m_requiredNbChannels(0)
            								{}
            								iccTagColorantTable(const iccTagColorantTable& inTag)
            								{
            									*this = inTag;
            								}
	virtual									~iccTagColorantTable()
											{};

			iccTagColorantTable&			operator=(const iccTagColorantTable& inTag);

			iccNumberUInt32					GetCountOfColorants(void) const
											{
												return m_colorants.size();
											}
	const	std::vector<iccColorant>&		GetColorants(void) const
											{
												return m_colorants;
											}
	virtual	iccNumberUInt32					GetSpecifiedTypeSignature(void) const
											{
            									return iccColorantTableType;
            								}
			void							SetColorants(const std::vector<iccColorant>& inColorants)
											{
												m_count = inColorants.size();
												m_colorants = inColorants;
											}
            void							SetRequiredNbChannels(iccNumberUInt32 inNbChannels)
								            {
								            	m_requiredNbChannels = inNbChannels;
								            }

protected:
	virtual	iccError						LoadSelf(std::istream& inStream,unsigned long inSize);
	virtual	iccError						SaveSelf(std::ostream& outStream,unsigned long& outSize) const;
	virtual	unsigned long					GetSizeSelf(void) const;
	virtual	void							InspectSelf(std::vector<iccTagInspector>& outErrorList) const = 0;
	virtual	void							AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList) = 0;

private:
			iccNumberUInt32					m_count;
			std::vector<iccColorant>		m_colorants;
			/**
			*	Number of channels corresponding to profile color space.
			*/
			iccNumberUInt32					m_requiredNbChannels;
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccBaseTag_H_
