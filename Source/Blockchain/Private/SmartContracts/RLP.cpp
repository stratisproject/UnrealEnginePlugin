#include "SmartContracts/RLP.h"

namespace RLP
{
    namespace 
    {
        std::vector<uint8_t> encodeLength(size_t length)
        {
            std::vector<uint8_t> lengthBytes;

            bool leadingNull = true;

            for (size_t iteration = sizeof(size_t); iteration > 0; iteration--)
            {
                uint8_t currentByte = (length >> ((iteration - 1) * 8)) & 0xFF;
                
                if (currentByte != 0 || !leadingNull) 
                {
                    leadingNull = false;
                    lengthBytes.push_back(currentByte);
                }
            }

            return lengthBytes;
        }

        void pushFlatten(std::vector<uint8_t>& out, const std::vector< std::vector<uint8_t> >& data)
        {
            for (auto& buffer: data)
            {
                out.insert(out.end(), buffer.begin(), buffer.end());
            }
        }
    }

    std::vector<uint8_t> encodeString(const std::vector<uint8_t>& data)
    {
        size_t bufferSize = data.size();

        std::vector<uint8_t> encodedData;

        if (bufferSize == 1 && data[0] < 0x7F) 
        {
            encodedData.push_back(data[0]);
        } 
        else if (bufferSize <= 55) 
        {
            encodedData.reserve(bufferSize + 1);
            encodedData.push_back(0x80 + bufferSize);
            encodedData.insert(encodedData.end(), data.begin(), data.end());
        } 
        else 
        {
            std::vector<uint8_t> lengthBytes(encodeLength(bufferSize));

            encodedData.reserve(bufferSize + lengthBytes.size() + 1);
            encodedData.push_back(0xB7 + lengthBytes.size());
            encodedData.insert(encodedData.end(), lengthBytes.begin(), lengthBytes.end());
            encodedData.insert(encodedData.end(), data.begin(), data.end());
        }

        return encodedData;
    }

    std::vector<uint8_t> encodeList(const std::vector< std::vector<uint8_t> >& data)
    {
        size_t totalSize = 0;

        for (auto& buffer: data)
        {
            totalSize += buffer.size();
        }
        
        std::vector<uint8_t> encodedData;

        if (totalSize <= 55) 
        {
            encodedData.reserve(totalSize + 1);
            encodedData.push_back(0xC0 + totalSize);
            pushFlatten(encodedData, data);
        } 
        else 
        {
            std::vector<uint8_t> lengthBytes(encodeLength(totalSize));

            encodedData.reserve(totalSize + lengthBytes.size() + 1);
            encodedData.push_back(0xF7 + lengthBytes.size());
            encodedData.insert(encodedData.end(), lengthBytes.begin(), lengthBytes.end());
            pushFlatten(encodedData, data);
        }

        return encodedData;
    }

    std::vector<uint8_t> encodeListAndItems(const std::vector< std::vector<uint8_t> >& data)
    {
        std::vector< std::vector<uint8_t> > encodedData(data.size());

        for (size_t i = 0; i < data.size(); i++)
        {
            encodedData[i] = RLP::encodeString(data[i]);
        }
        
        return RLP::encodeList(encodedData);
    }
}