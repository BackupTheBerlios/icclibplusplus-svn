#include "iccTagLut16.h"

#define ICCTAGLUT16_MATRIX_SIZE 9

using namespace std;
USING_ICC_LIB_NAMESPACE

//--------------------------------------------------------------------
iccTagLut16::~iccTagLut16(void)
{
	delete[](m_inputTables);
	m_inputTables = NULL;
	delete[](m_clutValues);
	m_clutValues = NULL;
	delete[](m_outputTables);
	m_outputTables = NULL;
}

//--------------------------------------------------------------------
iccTagLut16& iccTagLut16::operator=(const iccTagLut16& inTag)
{
	if(this != &inTag)
	{
		*(iccTag*)this = *(iccTag*)&inTag;

		m_nbInputChannels = inTag.GetNbInputChannels();
		m_nbOutputChannels = inTag.GetNbOutputChannels();
		m_nbClutGridPoints = inTag.GetNbClutGridPoints();
		m_padding = inTag.GetPadding();
		m_matrix = inTag.m_matrix;
		m_nbInputTableEntries = inTag.GetNbInputTableEntries();
		m_nbOutputTableEntries = inTag.GetNbOutputTableEntries();

		delete[](m_inputTables);
		m_inputTables = NULL;
		if(inTag.GetInputTables() != NULL)
		{
			m_inputTables = new iccNumberUInt16[inTag.GetInputTablesSize()];
			memcpy(m_inputTables, inTag.GetInputTables(), inTag.GetInputTablesSize());
		}

		delete[](m_clutValues);
		m_clutValues = NULL;
		if(inTag.GetClutValues() != NULL)
		{
			m_clutValues = new iccNumberUInt16[inTag.GetClutValuesSize()];
			memcpy(m_clutValues, inTag.GetClutValues(), inTag.GetClutValuesSize());
		}

		delete[](m_outputTables);
		m_outputTables = NULL;
		if(inTag.GetClutValues() != NULL)
		{
			m_outputTables = new iccNumberUInt16[inTag.GetOutputTablesSize()];
			memcpy(m_outputTables, inTag.GetOutputTables(), inTag.GetOutputTablesSize());
		}
	}
	return *this;
}

//--------------------------------------------------------------------
unsigned long iccTagLut16::GetSizeSelf(void) const
{
	return	sizeof m_nbInputChannels
			+ sizeof m_nbOutputChannels
			+ sizeof m_nbClutGridPoints
			+ sizeof m_padding
			+ m_matrix.size()*m_matrix[0].GetSize()
			+ sizeof m_nbInputTableEntries
			+ sizeof m_nbOutputTableEntries
			+ sizeof m_inputTables
			+ sizeof m_clutValues
			+ sizeof m_outputTables;
}

//--------------------------------------------------------------------
iccError iccTagLut16::LoadSelf(istream& inStream,unsigned long inSize)
{
	iccNumberS15Fixed16	fixed;
	unsigned long		i		= 0,
						imax	= 0;

	inStream >> m_nbInputChannels;
	inSize -= sizeof m_nbInputChannels;

	inStream >> m_nbOutputChannels;
	inSize -= sizeof m_nbOutputChannels;

	inStream >> m_nbClutGridPoints;
	inSize -= sizeof m_nbClutGridPoints;

	inStream >> m_padding;
	inSize -= sizeof m_padding;

	m_matrix.clear();
	for(i=0,imax=ICCTAGLUT16_MATRIX_SIZE; i<imax; i++)
	{
		inStream >> fixed;
		m_matrix.push_back(fixed);
		inSize -= fixed.GetSize();
	}

	inStream >> m_nbInputTableEntries;
	inSize -= sizeof m_nbInputTableEntries;

	inStream >> m_nbOutputTableEntries;
	inSize -= sizeof m_nbOutputTableEntries;

	imax = GetInputTablesSize();
	m_inputTables = new iccNumberUInt16[imax];
	for(i=0; i<imax; i++)
	{
		inStream >> m_inputTables[i];
		inSize -= sizeof m_inputTables[i];
	}

	imax = GetClutValuesSize();
	m_clutValues = new iccNumberUInt16[imax];
	for(i=0; i<imax; i++)
	{
		inStream >> m_clutValues[i];
		inSize -= sizeof m_clutValues[i];
	}

	imax = GetOutputTablesSize();
	m_outputTables = new iccNumberUInt16[imax];
	for(i=0; i<imax; i++)
	{
		inStream >> m_outputTables[i];
		inSize -= sizeof m_outputTables[i];
	}

	return iccErrorNone;
}

//--------------------------------------------------------------------
iccError iccTagLut16::SaveSelf(ostream& outStream,unsigned long& outSize) const
{
	unsigned long		i		= 0,
						imax	= 0;

	outStream << m_nbInputChannels;
	outSize += sizeof m_nbInputChannels;

	outStream << m_nbOutputChannels;
	outSize += sizeof m_nbOutputChannels;

	outStream << m_nbClutGridPoints;
	outSize += sizeof m_nbClutGridPoints;

	outStream << m_padding;
	outSize += sizeof m_padding;

	for(i=0; i<ICCTAGLUT16_MATRIX_SIZE; i++)
	{
		outStream << m_matrix[i];
		outSize += m_matrix[i].GetSize();
	}

	outStream << m_nbInputTableEntries;
	outSize += sizeof m_nbInputTableEntries;

	outStream << m_nbOutputTableEntries;
	outSize += sizeof m_nbOutputTableEntries;

	imax = GetInputTablesSize();
	for(i=0; i<imax; i++)
		outStream << m_inputTables[i];
	outSize += sizeof m_inputTables;

	imax = GetClutValuesSize();
	for(i=0; i<imax; i++)
		outStream << m_clutValues[i];
	outSize += sizeof m_clutValues;

	imax = GetOutputTablesSize();
	for(i=0; i<imax; i++)
		outStream << m_outputTables[i];
	outSize += sizeof m_outputTables;

	return iccErrorNone;
}
