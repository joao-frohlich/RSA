#include "../header.hpp"

std::wstring process(std::wstring message, std::pair<keyType,keyType> key){
    std::wstring ret;
    int chunkSize = N_BITS_INT/16;
    for (int i = 0; i < message.size()/chunkSize + (message.size()%chunkSize > 0); i++){
        std::wstring chunk(chunkSize,0);
        for (int j = 0; j < chunkSize && i*chunkSize+j < message.size(); j++) chunk[j] = message[i*chunkSize+j];
        ret += unhash(power2(hash(chunk,chunkSize),key.first,key.second),chunkSize);
    }
    return ret;
}
