#ifndef _H_iccTag_H_
#define _H_iccTag_H_

#include "iccObject.h"
#include "iccError.h"
#include "iccBasicNumericTypes.h"
#include "iccTagInspector.h"

#include <istream>
#include <ostream>
#include <vector>

ICC_LIB_NAMESPACE_START

class iccTag:	public iccObject
{
public:
    							iccTag(void)
    							: m_signature(0),m_typeSignature(0),m_reserved(0)
    							{}
    							iccTag(const iccTag& inTag)
    							{
    								*this = inTag;
    							}
	virtual						~iccTag()
								{}

			iccError			Load(std::istream& inStream,unsigned long inSize);
			iccError			Save(std::ostream& outStream,unsigned long& outSize) const;
			void				Inspect(std::vector<iccTagInspector>& outErrorList) const;
			void				AutoCorrect(const std::vector<iccTagInspector>& inErrorList);
	
			iccTag&				operator=(const iccTag& inTag);

	virtual	unsigned long		GetSize(void) const;
			iccNumberUInt32		GetSignature(void) const
    							{
    								return m_signature;
    							}
			iccNumberUInt32		GetTypeSignature(void) const
    							{
    								return m_typeSignature;
    							}
	virtual	iccNumberUInt32		GetSpecifiedTypeSignature(void) const = 0;
	virtual iccNumberUInt32		GetReserved(void) const
								{
									return m_reserved;
								}

			void				SetSignature(iccNumberUInt32 inSignature)
    							{
    								m_signature = inSignature;
    							}
			void				SetReserved(iccNumberUInt32 inReserved)
    							{
    								m_reserved = inReserved;
    							}

protected:
	virtual	iccError			LoadSelf(std::istream& inStream,unsigned long inSize) = 0;
	virtual	iccError			SaveSelf(std::ostream& outStream,unsigned long& outSize) const = 0;
	virtual	unsigned long		GetSizeSelf(void) const = 0;
	virtual	void				InspectSelf(std::vector<iccTagInspector>& outErrorList) const = 0;
	virtual	void				AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList) = 0;

private:
			iccNumberUInt32		m_signature;
			iccNumberUInt32		m_typeSignature;
			iccNumberUInt32		m_reserved;
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccTag_H_

