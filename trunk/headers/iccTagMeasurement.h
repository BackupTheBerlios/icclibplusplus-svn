#ifndef _H_iccTagMeasurement_H_
#define _H_iccTagMeasurement_H_

#include "iccTag.h"
#include "iccDefines.h"
#include "iccError.h"
#include "iccBasicNumericTypes.h"
#include "iccNumberXYZ.h"
#include <istream>
#include <ostream>

ICC_LIB_NAMESPACE_START

class iccTagMeasurement:	public iccTag
{
public:
	enum
	{
		kStandardObserver_Unknown	= 0L,
		kStandardObserver_CIE1931,
		kStandardObserver_CIE1964,
		kStandardObserver_Max,
	};
	enum
	{
		kMeasurementGeometry_Unknown	= 0L,
		kMeasurementGeometry_0_45,
		kMeasurementGeometry_0_d,
		kMeasurementGeometry_Max
	};
	enum
	{
		kMeasurementFlare_0	= 0L,
		kMeasurementFlare_100,
		kMeasurementFlare_Max
	};

	       									iccTagMeasurement(void)
        									:	m_standardObserver(0),m_tristimulus(),
												m_measurementGeometry(0),m_measurementFlare(0),
												m_standardIlluminant(0)
        									{};
        									iccTagMeasurement(const iccTagMeasurement& inTag)
        									{
        										*this = inTag;
        									};
    virtual									~iccTagMeasurement(void)
        									{};
	
			iccTagMeasurement&				operator=(const iccTagMeasurement& inTag);

	virtual	iccNumberUInt32					GetSpecifiedTypeSignature(void)
        									{
        										return iccMeasurementType;
        									};
			iccNumberUInt64					GetStandardObserver(void) const
											{
												return m_standardObserver;
											}
	const	iccNumberXYZ&					GetTristimulus(void) const
											{
												return m_tristimulus;
											}
			iccNumberUInt64					GetMeasurementGeometry(void) const
											{
												return m_measurementGeometry;
											}
			iccNumberUInt64					GetMeasurementFlare(void) const
											{
												return m_measurementFlare;
											}
			iccNumberUInt64					GetStandardIlluminant(void) const
											{
												return m_standardIlluminant;
											}
			void							SetStandardObserver(iccNumberUInt64 inNumber)
											{
												m_standardObserver = inNumber;
											}
        	void							SetTristimulus(const iccNumberXYZ& inNumber)
											{
												m_tristimulus = inNumber;
											}
			void							SetMeasurementGeometry(iccNumberUInt64 inNumber)
											{
												m_measurementGeometry = inNumber;
											}
			void							SetMeasurementFlare(iccNumberUInt64 inNumber)
											{
												m_measurementFlare = inNumber;
											}
			void							SetStandardIlluminant(iccNumberUInt64 inNumber)
											{
												m_standardIlluminant = inNumber;
											}

protected:
	virtual	iccError						LoadSelf(std::istream& inStream,unsigned long inSize );
	virtual	iccError						SaveSelf(std::ostream& outStream,unsigned long& outSize) const;
	virtual	unsigned long					GetSizeSelf(void) const;
	virtual	void							InspectSelf(std::vector<iccTagInspector>& outErrorList) const;
	virtual	void							AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList);

private:
			iccNumberUInt64					m_standardObserver;
			iccNumberXYZ					m_tristimulus;
			iccNumberUInt64					m_measurementGeometry;
			iccNumberUInt64					m_measurementFlare;
			iccNumberUInt64					m_standardIlluminant;
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccTagMeasurement_H_
