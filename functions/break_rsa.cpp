#include "../header.hpp"

std::pair<keyType,keyType> break_rsa(std::pair<keyType,keyType> key, independent_bits_engine<std::mt19937, P_SIZE, primeType> gen){
    keyType p1; std::tie(p1,gen) = pollard_rho(key.second, gen);
    while (p1 == key.second) std::tie(p1,gen) = pollard_rho(key.second, gen);
    keyType p2 = key.second/p1;
    keyType t = (p1-1)*(p2-1);
    keyType d = (std::get<2>(euclid(t,key.first)))%t;
    return std::make_pair(d,key.second);
}
