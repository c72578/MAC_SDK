/*****************************************************************************************
Monkey's Audio MACDll.h (include for using MACDll.dll in your projects)
Copyright (C) 2000-2011 by Matthew T. Ashland   All Rights Reserved.

Overview:

Basically all this dll does is wrap MACLib.lib, so browse through MACLib.h for documentation
on how to use the interfaces.
*****************************************************************************************/

#pragma once

/*****************************************************************************************
Includes
*****************************************************************************************/
#include "All.h"
#include "MACLib.h"

/*****************************************************************************************
Helper functions
*****************************************************************************************/
extern "C"
{
    __declspec( dllexport ) int __stdcall GetVersionNumber();
    __declspec( dllexport ) const wchar_t *__stdcall GetVersionString();
}

typedef int (__stdcall * proc_GetVersionNumber)();

struct APE_CIO_Callbacks
{   
    int (__stdcall *Read)(struct APE_CIO_Callbacks* pCIO, void * pBuffer, unsigned int nBytesToRead, unsigned int * pBytesRead);
    int (__stdcall *Write)(struct APE_CIO_Callbacks* pCIO, const void * pBuffer, unsigned int nBytesToWrite, unsigned int * pBytesWritten);
    int (__stdcall *Seek)(struct APE_CIO_Callbacks* pCIO, APE::intn nDistance, unsigned int nMoveMode);
    int (__stdcall *GetPosition)(struct APE_CIO_Callbacks* pCIO);
    unsigned int (__stdcall *GetSize)(struct APE_CIO_Callbacks* pCIO);
};

/*****************************************************************************************
IAPECompress wrapper(s)
*****************************************************************************************/
typedef void * APE_COMPRESS_HANDLE;

typedef APE_COMPRESS_HANDLE (__stdcall * proc_APECompress_Create)(int *); 
typedef void (__stdcall * proc_APECompress_Destroy)(APE_COMPRESS_HANDLE); 
#ifndef EXCLUDE_CIO
typedef int (__stdcall * proc_APECompress_Start)(APE_COMPRESS_HANDLE, const char *, const APE::WAVEFORMATEX *, int, int, const void *, int);
typedef int (__stdcall * proc_APECompress_StartW)(APE_COMPRESS_HANDLE, const APE::str_utfn *, const APE::WAVEFORMATEX *, int, int, const void *, int);
#endif
typedef int (__stdcall * proc_APECompress_StartEx)(APE_COMPRESS_HANDLE, APE_CIO_Callbacks*, const APE::WAVEFORMATEX *, int, int, const void *, int);
typedef int (__stdcall * proc_APECompress_AddData)(APE_COMPRESS_HANDLE, unsigned char *, int);
typedef int (__stdcall * proc_APECompress_GetBufferBytesAvailable)(APE_COMPRESS_HANDLE);
typedef unsigned char * (__stdcall * proc_APECompress_LockBuffer)(APE_COMPRESS_HANDLE, APE::intn *);
typedef int (__stdcall * proc_APECompress_UnlockBuffer)(APE_COMPRESS_HANDLE, int, BOOL);
typedef int (__stdcall * proc_APECompress_Finish)(APE_COMPRESS_HANDLE, unsigned char *, int, int);
typedef int (__stdcall * proc_APECompress_Kill)(APE_COMPRESS_HANDLE);

extern "C"
{
    __declspec( dllexport ) APE_COMPRESS_HANDLE __stdcall c_APECompress_Create(int * pErrorCode = NULL);
    __declspec( dllexport ) void __stdcall c_APECompress_Destroy(APE_COMPRESS_HANDLE hAPECompress);
#ifndef EXCLUDE_CIO
    __declspec( dllexport ) int __stdcall c_APECompress_Start(APE_COMPRESS_HANDLE hAPECompress, const char * pOutputFilename, const APE::WAVEFORMATEX * pwfeInput, int nMaxAudioBytes = MAX_AUDIO_BYTES_UNKNOWN, int nCompressionLevel = COMPRESSION_LEVEL_NORMAL, const void * pHeaderData = NULL, int nHeaderBytes = CREATE_WAV_HEADER_ON_DECOMPRESSION);
    __declspec( dllexport ) int __stdcall c_APECompress_StartW(APE_COMPRESS_HANDLE hAPECompress, const APE::str_utfn * pOutputFilename, const APE::WAVEFORMATEX * pwfeInput, int nMaxAudioBytes = MAX_AUDIO_BYTES_UNKNOWN, int nCompressionLevel = COMPRESSION_LEVEL_NORMAL, const void * pHeaderData = NULL, int nHeaderBytes = CREATE_WAV_HEADER_ON_DECOMPRESSION);
#endif
    __declspec( dllexport ) int __stdcall c_APECompress_StartEx(APE_COMPRESS_HANDLE hAPECompress, APE_CIO_Callbacks* pCIO, const APE::WAVEFORMATEX * pwfeInput, int nMaxAudioBytes = MAX_AUDIO_BYTES_UNKNOWN, int nCompressionLevel = COMPRESSION_LEVEL_NORMAL, const void * pHeaderData = NULL, int nHeaderBytes = CREATE_WAV_HEADER_ON_DECOMPRESSION);
    __declspec( dllexport ) int __stdcall c_APECompress_AddData(APE_COMPRESS_HANDLE hAPECompress, unsigned char * pData, int nBytes);
    __declspec( dllexport ) int __stdcall c_APECompress_GetBufferBytesAvailable(APE_COMPRESS_HANDLE hAPECompress);
    __declspec( dllexport ) unsigned char * __stdcall c_APECompress_LockBuffer(APE_COMPRESS_HANDLE hAPECompress, APE::intn * pBytesAvailable);
    __declspec( dllexport )    int __stdcall c_APECompress_UnlockBuffer(APE_COMPRESS_HANDLE hAPECompress, int nBytesAdded, BOOL bProcess = TRUE);
    __declspec( dllexport )    int __stdcall c_APECompress_Finish(APE_COMPRESS_HANDLE hAPECompress, unsigned char * pTerminatingData, int nTerminatingBytes, int nWAVTerminatingBytes);
    __declspec( dllexport )    int __stdcall c_APECompress_Kill(APE_COMPRESS_HANDLE hAPECompress);
}

/*****************************************************************************************
IAPEDecompress wrapper(s)
*****************************************************************************************/
typedef void * APE_DECOMPRESS_HANDLE;

#ifndef EXCLUDE_CIO
typedef APE_DECOMPRESS_HANDLE (__stdcall * proc_APEDecompress_Create)(const char *, int *);
typedef APE_DECOMPRESS_HANDLE (__stdcall * proc_APEDecompress_CreateW)(const APE::str_utfn *, int *);
#endif
typedef APE_DECOMPRESS_HANDLE(__stdcall * proc_APEDecompress_CreateW)(APE_CIO_Callbacks *, int *);
typedef void (__stdcall * proc_APEDecompress_Destroy)(APE_DECOMPRESS_HANDLE); 
typedef int (__stdcall * proc_APEDecompress_GetData)(APE_DECOMPRESS_HANDLE, char *, APE::intn, APE::intn *);
typedef int (__stdcall * proc_APEDecompress_Seek)(APE_DECOMPRESS_HANDLE, int); 
typedef int (__stdcall * proc_APEDecompress_GetInfo)(APE_DECOMPRESS_HANDLE, APE::APE_DECOMPRESS_FIELDS, int, int);

extern "C"
{
#ifndef EXCLUDE_CIO
    __declspec( dllexport ) APE_DECOMPRESS_HANDLE __stdcall c_APEDecompress_Create(const APE::str_ansi * pFilename, int * pErrorCode = NULL);
    __declspec( dllexport ) APE_DECOMPRESS_HANDLE __stdcall c_APEDecompress_CreateW(const APE::str_utfn * pFilename, int * pErrorCode = NULL);
#endif
    __declspec( dllexport ) APE_DECOMPRESS_HANDLE __stdcall c_APEDecompress_CreateEx(APE_CIO_Callbacks* pCIO, int * pErrorCode = NULL);
    __declspec( dllexport ) void __stdcall c_APEDecompress_Destroy(APE_DECOMPRESS_HANDLE hAPEDecompress);
    __declspec( dllexport ) int __stdcall c_APEDecompress_GetData(APE_DECOMPRESS_HANDLE hAPEDecompress, char * pBuffer, APE::intn nBlocks, APE::intn * pBlocksRetrieved);
    __declspec( dllexport ) int __stdcall c_APEDecompress_Seek(APE_DECOMPRESS_HANDLE hAPEDecompress, int nBlockOffset);
    __declspec( dllexport ) int __stdcall c_APEDecompress_GetInfo(APE_DECOMPRESS_HANDLE hAPEDecompress, APE::APE_DECOMPRESS_FIELDS Field, int nParam1 = 0, int nParam2 = 0);
}
