#ifndef _H_iccTagChromaticity_H_
#define _H_iccTagChromaticity_H_

#include "iccTag.h"
#include "iccDefines.h"
#include "iccBasicNumericTypes.h"
#include <vector>

ICC_LIB_NAMESPACE_START

class iccTagChromaticity:	public iccTag
{
public:
	// Possible colorant values
	enum
	{
		unknownColorant	= 0,
		ITU_R_BT_709,
		SMPTE_RP145_1994,
		EBU_Tech_2113_E,
		P22,
		lastColorantValue,
		firstColorantValue = unknownColorant + 1
	};

	struct iccCieXyCoordinates
	{
		iccNumberU16Fixed16		x;
		iccNumberU16Fixed16		y;
		iccCieXyCoordinates&	operator=(const iccCieXyCoordinates& inCoordinates);
		bool					operator==(const iccCieXyCoordinates& inCoordinates) const;
		bool					operator!=(const iccCieXyCoordinates& inCoordinates) const;
		friend	void			operator>>(std::istream& inStream,iccCieXyCoordinates& outCoordinates);
		friend	std::ostream&	operator<<(std::ostream& outStream,const iccCieXyCoordinates& inCoordinates);
		unsigned long			GetSize(void) const;
	};

                    							iccTagChromaticity(void)
                    							:	m_nbChannels(0),
													m_encodedValue(0),
													m_coordinates()
                    							{}
                    							iccTagChromaticity(const iccTagChromaticity& inTag)
                    							{
                    								*this = inTag;
                    							}
	virtual										~iccTagChromaticity()
												{};

			iccTagChromaticity&					operator=(const iccTagChromaticity& inTag);

	virtual	iccNumberUInt32						GetSpecifiedTypeSignature(void) const
												{
            										return iccChromaticityType;
            									}
			iccNumberUInt16						GetNbChannels(void) const
            									{
            										return m_nbChannels;
            									}
			iccNumberUInt16						GetEncodedValue(void) const
            									{
            										return m_encodedValue;
            									}
	const	std::vector<iccCieXyCoordinates>&	GetCoordinates(void) const
												{
													return m_coordinates;
												}
			void								SetEncodedValue(iccNumberUInt16 inValue);
			void								SetCoordinates(std::vector<iccCieXyCoordinates>	inCoordinates);

protected:
	virtual	iccError							LoadSelf(std::istream& inStream,unsigned long inSize);
	virtual	iccError							SaveSelf(std::ostream& outStream,unsigned long& outSize) const;
	virtual	unsigned long						GetSizeSelf(void) const;
	virtual	void								InspectSelf(std::vector<iccTagInspector>& outErrorList) const = 0;
	virtual	void								AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList) = 0;

private:

			bool								AreCoordinatesMatching(iccNumberUInt16 inEncoding) const;
			
			iccNumberUInt16						m_nbChannels;
			iccNumberUInt16						m_encodedValue;
			std::vector<iccCieXyCoordinates>	m_coordinates;
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccTagChromaticity_H_
