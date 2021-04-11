#include "../header.hpp"

std::tuple<keyType,keyType,keyType> euclid(keyType a, keyType b){
    if (b == 0) return std::make_tuple(a,1,0);
    else {
        std::tuple<keyType,keyType,keyType> aux = euclid(b,a%b);
        return std::make_tuple(std::get<0>(aux),std::get<2>(aux),std::get<1>(aux)-(keyType)(a/b)*std::get<2>(aux));
    }
}
