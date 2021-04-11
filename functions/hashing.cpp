#include "../header.hpp"

keyType hash(std::wstring chunk, int chunkSize){
    keyType ret = 0;
    keyType m = 1;
    for (int i = 0; i < chunkSize; i++){
        ret = ret+m*chunk[i];
        m = m*65536;
    }
    return ret;
}

std::wstring unhash(keyType chunk, int chunkSize){
    std::wstring ret(chunkSize,0);
    keyType m = 1;
    for (int i = 0; i < chunkSize-1; i++) m = m*65536;
    for (int i = chunkSize-1; i >= 0; i--){
        ret[i] = (wchar_t)(chunk/m);
        chunk = chunk%m;
        m = m/65536;
    }
    return ret;
}
