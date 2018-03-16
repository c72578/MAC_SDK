#pragma once

namespace APE
{

/*************************************************************************************************
IPredictorCompress - the interface for compressing (predicting) data
*************************************************************************************************/
class IPredictorCompress
{
public:
    IPredictorCompress(intn nCompressionLevel) {}
    virtual ~IPredictorCompress() {}

    virtual int CompressValue(int nA, int nB = 0) = 0;
    virtual int Flush() = 0;
};

/*************************************************************************************************
IPredictorDecompress - the interface for decompressing (un-predicting) data
*************************************************************************************************/
class IPredictorDecompress
{
public:
    IPredictorDecompress(intn nCompressionLevel, intn nVersion) {}
    virtual ~IPredictorDecompress() {}

    virtual int DecompressValue(int nA, int nB = 0) = 0;
    virtual int Flush() = 0;
};

}
