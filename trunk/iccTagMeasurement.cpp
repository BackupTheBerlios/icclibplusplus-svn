#include "iccTagMeasurement.h"

using namespace std;
USING_ICC_LIB_NAMESPACE

//--------------------------------------------------------------------
iccTagMeasurement& iccTagMeasurement::operator=(const iccTagMeasurement& inTag)
{
	if(this != &inTag)
	{
		*(iccTag*)this = *(iccTag*)&inTag;

		m_standardObserver		= inTag.GetStandardObserver();
		m_tristimulus			= inTag.GetTristimulus();
		m_measurementGeometry	= inTag.GetMeasurementGeometry();
		m_measurementFlare		= inTag.GetMeasurementFlare();
		m_standardIlluminant	= inTag.GetStandardIlluminant();
	}
	return *this;
}

//--------------------------------------------------------------------
unsigned long iccTagMeasurement::GetSizeSelf(void) const
{
	return	sizeof m_standardObserver
			+ m_tristimulus.GetSize()
			+ sizeof m_measurementGeometry
			+ sizeof m_measurementFlare
			+ sizeof m_standardIlluminant;
}

//--------------------------------------------------------------------
iccError iccTagMeasurement::LoadSelf(istream& inStream,unsigned long inSize)
{
	inStream >> m_standardObserver;
	inSize -= sizeof m_standardObserver;

	inStream >> m_tristimulus;
	inSize -= m_tristimulus.GetSize();

	inStream >> m_measurementGeometry;
	inSize -= sizeof m_measurementGeometry;

	inStream >> m_measurementFlare;
	inSize -= sizeof m_measurementFlare;

	inStream >> m_standardIlluminant;
	inSize -= sizeof m_standardIlluminant;

	return iccErrorNone;
}

//--------------------------------------------------------------------
iccError iccTagMeasurement::SaveSelf(ostream& outStream,unsigned long& outSize) const
{
	outStream << m_standardObserver;
	outSize += sizeof m_standardObserver;

	outStream << m_tristimulus;
	outSize +=  m_tristimulus.GetSize();

	outStream << m_measurementGeometry;
	outSize += sizeof m_measurementGeometry;

	outStream << m_measurementFlare;
	outSize += sizeof m_measurementFlare;

	outStream << m_standardIlluminant;
	outSize += sizeof m_standardIlluminant;

	return iccErrorNone;
}

//--------------------------------------------------------------------
void iccTagMeasurement::InspectSelf(std::vector<iccTagInspector>& outErrorList) const
{
	if(kStandardObserver_Max <= m_standardObserver)
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_ERROR_MEASUREMENT_BAD_STANDARD_OBSERVER_VALUE
								) );

	if(!m_tristimulus.IsValid())
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_ERROR_MEASUREMENT_BAD_TRISTIMULUS_VALUE
								) );

	if(kMeasurementGeometry_Max <= m_measurementGeometry)
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_ERROR_MEASUREMENT_BAD_MEASUREMENT_GEOMETRY_VALUE
								) );

	if(kMeasurementFlare_Max <= m_measurementFlare)
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_ERROR_MEASUREMENT_BAD_MEASUREMENT_FLARE_VALUE
								) );

	if(iccStandardIlluminant_Max <= m_standardIlluminant)
		outErrorList.push_back(	iccTagInspector(
									GetSignature(),
									GetTypeSignature(),
									iccTagInspector::ICC_TAG_ERROR_SEVERITY_MINOR,
									true,
									iccTagInspector::ICC_TAG_GENERIC_ERROR_BAD_VALUE,
									iccTagInspector::ICC_TAG_ERROR_MEASUREMENT_BAD_STANDARD_ILLUMINANT_VALUE
								) );
}

//--------------------------------------------------------------------
void iccTagMeasurement::AutoCorrectSelf(const vector<iccTagInspector>& inErrorList)
{
	vector<iccTagInspector>::const_iterator	itError,
											itErrorEnd;

	for(itError=inErrorList.begin(),itErrorEnd=inErrorList.end(); itError!=itErrorEnd; itError++)
	{
		if(
			itError->GetTagSignature() == GetSignature()
			&& itError->GetTagTypeSignature() == GetTypeSignature()
			&& itError->IsAutoCorrective()
		)
			switch(itError->GetSpecificError())
			{
				case iccTagInspector::ICC_TAG_ERROR_MEASUREMENT_BAD_STANDARD_OBSERVER_VALUE:
					m_standardObserver = kStandardObserver_Unknown;
					break;
				case iccTagInspector::ICC_TAG_ERROR_MEASUREMENT_BAD_TRISTIMULUS_VALUE:
					m_tristimulus.AutoCorrect();
					break;
				case iccTagInspector::ICC_TAG_ERROR_MEASUREMENT_BAD_MEASUREMENT_GEOMETRY_VALUE:
					m_measurementGeometry = kMeasurementGeometry_Unknown;
					break;
				case iccTagInspector::ICC_TAG_ERROR_MEASUREMENT_BAD_MEASUREMENT_FLARE_VALUE:
					m_measurementFlare = kMeasurementFlare_0;
					break;
				case iccTagInspector::ICC_TAG_ERROR_MEASUREMENT_BAD_STANDARD_ILLUMINANT_VALUE:
					m_standardIlluminant = iccStandardIlluminant_Unknown;
					break;
				default:
					break;
			}
	}
}
