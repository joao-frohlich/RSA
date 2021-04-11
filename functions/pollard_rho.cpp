#include "../header.hpp"

std::pair<keyType,independent_bits_engine<std::mt19937, P_SIZE, primeType>> pollard_rho(keyType n, independent_bits_engine<std::mt19937, P_SIZE, primeType> gen){
    if (n==1) return std::make_pair(n,gen);
    if (n % 2 == 0) return std::make_pair(2,gen);
    keyType x = (keyType)gen();
    keyType y = x;
    keyType c = (keyType)gen();
    keyType d = 1;

    while (d==1) {
        x = (keyType)((superType)(power2(x, 2, n) + c + n)%n);
        y = (keyType)((superType)(power2(y, 2, n) + c + n)%n);
        y = (keyType)((superType)(power2(y, 2, n) + c + n)%n);
        d = std::__gcd(abs_diff(x,y), n);
    }

    return std::make_pair(d,gen);
}

keyType abs_diff(keyType x, keyType y){
    return (x >= y) ? x-y : y-x;
}
