#ifndef _H_iccTagLut16_H_
#define _H_iccTagLut16_H_

#include "iccTag.h"
#include "iccBasicNumericTypes.h"
#include "iccDefines.h"
#include <vector>

ICC_LIB_NAMESPACE_START

class iccTagLut16:	public iccTag
{
public:
	       										iccTagLut16(void)
												:	m_nbInputChannels(0),m_nbOutputChannels(0),
													m_nbClutGridPoints(0),m_padding(0),m_matrix(),
													m_nbInputTableEntries(0),m_nbOutputTableEntries(0),
													m_inputTables(NULL),m_clutValues(NULL),m_outputTables(NULL)
												{}
        										iccTagLut16(const iccTagLut16& inTag)
        										{
        											*this = inTag;
        										};
    virtual										~iccTagLut16(void);
	
			iccTagLut16&						operator=(const iccTagLut16& inTag);

	virtual	iccNumberUInt32						GetSpecifiedTypeSignature(void)
        										{
        											return iccLut16Type;
        										};
			iccNumberUInt8						GetNbInputChannels(void) const
												{
													return m_nbInputChannels;
												}
			iccNumberUInt8						GetNbOutputChannels(void) const
												{
													return m_nbOutputChannels;
												}
			iccNumberUInt8						GetNbClutGridPoints(void) const
												{
													return m_nbClutGridPoints;
												}
			iccNumberUInt8						GetPadding(void) const
												{
													return m_padding;
												}
	const	std::vector<iccNumberS15Fixed16>	GetMatrix(void) const
												{
													return m_matrix;
												}
			iccNumberUInt16						GetNbInputTableEntries(void) const
												{
													return m_nbInputTableEntries;
												}
			iccNumberUInt16						GetNbOutputTableEntries(void) const
												{
													return m_nbOutputTableEntries;
												}
			iccNumberUInt32						GetInputTablesSize(void) const
												{
													return m_nbInputChannels * m_nbInputTableEntries;
												}
	const	iccNumberUInt16*					GetInputTables(void) const
												{
													return m_inputTables;
												}
			iccNumberUInt32						GetClutValuesSize(void) const
												{
													return	(unsigned long)pow((float)m_nbClutGridPoints,(float)m_nbInputChannels)
															* m_nbOutputChannels;
												}
	const	iccNumberUInt16*					GetClutValues(void) const
												{
													return m_clutValues;
												}
			iccNumberUInt32						GetOutputTablesSize(void) const
												{
													return m_nbOutputChannels * m_nbOutputTableEntries;
												}
	const	iccNumberUInt16*					GetOutputTables(void) const
												{
													return m_outputTables;
												}

protected:
	virtual	iccError							LoadSelf(std::istream& inStream,unsigned long inSize );
	virtual	iccError							SaveSelf(std::ostream& outStream,unsigned long& outSize) const;
	virtual	unsigned long						GetSizeSelf(void) const;
	virtual	void								InspectSelf(std::vector<iccTagInspector>& outErrorList) const;
	virtual	void								AutoCorrectSelf(const std::vector<iccTagInspector>& inErrorList);

private:
			iccNumberUInt8						m_nbInputChannels;
			iccNumberUInt8						m_nbOutputChannels;
			iccNumberUInt8						m_nbClutGridPoints;
			iccNumberUInt8						m_padding;
			std::vector<iccNumberS15Fixed16>	m_matrix;
			iccNumberUInt16						m_nbInputTableEntries;
			iccNumberUInt16						m_nbOutputTableEntries;
			iccNumberUInt16*					m_inputTables;
			iccNumberUInt16*					m_clutValues;
			iccNumberUInt16*					m_outputTables;
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccTagLut16_H_
