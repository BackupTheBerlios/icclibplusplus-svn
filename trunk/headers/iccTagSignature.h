#ifndef _H_iccTagSignature_H_#define _H_iccTagSignature_H_#include "iccTag.h"#include "iccDefines.h"ICC_LIB_NAMESPACE_STARTclass iccTagSignature:	public iccTag{public:        									iccTagSignature(void)        									:m_signature(0)        									{}        									iccTagSignature(const iccTagSignature& inTag)        									{        										*this = inTag;        									}    virtual									~iccTagSignature(void)        									{}			iccTagSignature&				operator=(const iccTagSignature& inTag);	virtual	iccNumberUInt32					GetSpecifiedTypeSignature(void) const											{            									return iccSignatureType;            								}protected:	virtual	iccError						LoadSelf(std::istream& inStream,unsigned long inSize);	virtual	iccError						SaveSelf(std::ostream& outStream,unsigned long& outSize) const;	virtual	unsigned long					GetSizeSelf(void) const;	virtual	void							InspectSelf(std::vector<iccTagInspector>& outErrorList) const											{}	virtual	void							AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList)											{} private:			iccFourByteType					m_signature;};ICC_LIB_NAMESPACE_END#endif//_H_iccTagSignature_H_