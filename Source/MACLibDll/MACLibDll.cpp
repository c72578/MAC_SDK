#include "MACLibDll.h"
#include "IO.h"

using namespace APE;

class CallbackCIO : public CIO
{
public:
	// construction / destruction
	CallbackCIO(APE_CIO_Callbacks* pCIO) { m_pCIO = pCIO; }
	~CallbackCIO() {}

	// open / close
	int Open(const wchar_t * pName, bool bOpenReadOnly = false) 
	{ 
		return -1; 
	}
	int Close()
	{ 
		return -1;
	}

	// read / write
	int Read(void * pBuffer, unsigned int nBytesToRead, unsigned int * pBytesRead)
	{
		return m_pCIO->Read(m_pCIO, pBuffer, nBytesToRead, pBytesRead);
	}
	int Write(const void * pBuffer, unsigned int nBytesToWrite, unsigned int * pBytesWritten)
	{
		return m_pCIO->Write(m_pCIO, pBuffer, nBytesToWrite, pBytesWritten);
	}

	// seek
	int Seek(intn nDistance, unsigned int nMoveMode)
	{
		return m_pCIO->Seek(m_pCIO, nDistance, nMoveMode);
	}

	// other functions
	int SetEOF()
	{ 
		return -1;
	}

	// creation / destruction
	int Create(const wchar_t * pName)
	{ 
		return -1;
	}
	int Delete() 
	{ 
		return -1;
	}

	// attributes
	int GetPosition()
    { 
        return m_pCIO->GetPosition(m_pCIO); 
    }
	unsigned int GetSize()
    { 
        return m_pCIO->GetSize(m_pCIO);
    }
	int GetName(wchar_t * pBuffer) 
	{ 
		return -1;
	}

private:
	APE_CIO_Callbacks * m_pCIO;
};

int __stdcall GetVersionNumber()
{
    return MAC_FILE_VERSION_NUMBER;
}

const wchar_t *__stdcall GetVersionString()
{
    return MAC_VERSION_STRING;
}

/*****************************************************************************************
CAPEDecompress wrapper(s)
*****************************************************************************************/
#ifndef EXCLUDE_CIO
APE_DECOMPRESS_HANDLE __stdcall c_APEDecompress_Create(const str_ansi * pFilename, int * pErrorCode)
{
	CSmartPtr<wchar_t> spFilename(CAPECharacterHelper::GetUTF16FromANSI(pFilename), TRUE);
	return (APE_DECOMPRESS_HANDLE)CreateIAPEDecompress(spFilename, pErrorCode);
}

APE_DECOMPRESS_HANDLE __stdcall c_APEDecompress_CreateW(const str_utfn * pFilename, int * pErrorCode)
{
    return (APE_DECOMPRESS_HANDLE) CreateIAPEDecompress(pFilename, pErrorCode);
}
#endif

APE_DECOMPRESS_HANDLE __stdcall c_APEDecompress_CreateEx(APE_CIO_Callbacks* pCIO, int * pErrorCode)
{
    return (APE_DECOMPRESS_HANDLE)CreateIAPEDecompressEx(new CallbackCIO(pCIO), pErrorCode);
}

void __stdcall c_APEDecompress_Destroy(APE_DECOMPRESS_HANDLE hAPEDecompress)
{
    IAPEDecompress * pAPEDecompress = (IAPEDecompress *) hAPEDecompress;
    if (pAPEDecompress)
        delete pAPEDecompress;
}

int __stdcall c_APEDecompress_GetData(APE_DECOMPRESS_HANDLE hAPEDecompress, char * pBuffer, intn nBlocks, intn * pBlocksRetrieved)
{
    return ((IAPEDecompress *) hAPEDecompress)->GetData(pBuffer, nBlocks, pBlocksRetrieved);
}

int __stdcall c_APEDecompress_Seek(APE_DECOMPRESS_HANDLE hAPEDecompress, int nBlockOffset)
{
    return ((IAPEDecompress *) hAPEDecompress)->Seek(nBlockOffset);
}

int __stdcall c_APEDecompress_GetInfo(APE_DECOMPRESS_HANDLE hAPEDecompress, APE_DECOMPRESS_FIELDS Field, int nParam1, int nParam2)
{
    return ((IAPEDecompress *) hAPEDecompress)->GetInfo(Field, nParam1, nParam2);
}

/*****************************************************************************************
CAPECompress wrapper(s)
*****************************************************************************************/
APE_COMPRESS_HANDLE __stdcall c_APECompress_Create(int * pErrorCode)
{
    return (APE_COMPRESS_HANDLE) CreateIAPECompress(pErrorCode);
}

void __stdcall c_APECompress_Destroy(APE_COMPRESS_HANDLE hAPECompress)
{
    IAPECompress * pAPECompress = (IAPECompress *) hAPECompress;
    if (pAPECompress)
        delete pAPECompress;
}

#ifndef EXCLUDE_CIO
int __stdcall c_APECompress_StartW(APE_COMPRESS_HANDLE hAPECompress, const str_utfn * pOutputFilename, const APE::WAVEFORMATEX * pwfeInput, int nMaxAudioBytes, int nCompressionLevel, const void * pHeaderData, int nHeaderBytes)
{
	return ((IAPECompress *)hAPECompress)->Start(pOutputFilename, pwfeInput, nMaxAudioBytes, nCompressionLevel, pHeaderData, nHeaderBytes);
}

int __stdcall c_APECompress_StartW(APE_COMPRESS_HANDLE hAPECompress, const str_utfn * pOutputFilename, const APE::WAVEFORMATEX * pwfeInput, int nMaxAudioBytes, int nCompressionLevel, const void * pHeaderData, int nHeaderBytes)
{
    return ((IAPECompress *) hAPECompress)->Start(pOutputFilename, pwfeInput, nMaxAudioBytes, nCompressionLevel, pHeaderData, nHeaderBytes);
}
#endif

int __stdcall c_APECompress_StartEx(APE_COMPRESS_HANDLE hAPECompress, APE_CIO_Callbacks* pCIO, const APE::WAVEFORMATEX * pwfeInput, int nMaxAudioBytes, int nCompressionLevel, const void * pHeaderData, int nHeaderBytes)
{
	return ((IAPECompress *)hAPECompress)->StartEx(new CallbackCIO(pCIO), pwfeInput, nMaxAudioBytes, nCompressionLevel, pHeaderData, nHeaderBytes);
}

int __stdcall c_APECompress_AddData(APE_COMPRESS_HANDLE hAPECompress, unsigned char * pData, int nBytes)
{
    return ((IAPECompress *) hAPECompress)->AddData(pData, nBytes);
}

int __stdcall c_APECompress_GetBufferBytesAvailable(APE_COMPRESS_HANDLE hAPECompress)
{
    return ((IAPECompress *) hAPECompress)->GetBufferBytesAvailable();
}

unsigned char * __stdcall c_APECompress_LockBuffer(APE_COMPRESS_HANDLE hAPECompress, intn * pBytesAvailable)
{
    return ((IAPECompress *) hAPECompress)->LockBuffer(pBytesAvailable);
}

int __stdcall c_APECompress_UnlockBuffer(APE_COMPRESS_HANDLE hAPECompress, int nBytesAdded, BOOL bProcess)
{
    return ((IAPECompress *) hAPECompress)->UnlockBuffer(nBytesAdded, bProcess);
}

int __stdcall c_APECompress_Finish(APE_COMPRESS_HANDLE hAPECompress, unsigned char * pTerminatingData, int nTerminatingBytes, int nWAVTerminatingBytes)
{
    return ((IAPECompress *) hAPECompress)->Finish(pTerminatingData, nTerminatingBytes, nWAVTerminatingBytes);
}

int __stdcall c_APECompress_Kill(APE_COMPRESS_HANDLE hAPECompress)
{
    return ((IAPECompress *) hAPECompress)->Kill();
}

