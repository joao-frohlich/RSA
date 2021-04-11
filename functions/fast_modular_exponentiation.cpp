#include "../header.hpp"

primeType power(primeType base, primeType e, primeType mod) {
    primeType result = 1;
    base = base%mod;
    while (e) {
        if (e & 1) result = (primeType)((keyType)result * base % mod);
        base = (primeType)((keyType)base * base % mod);
        e = e>>1;
    }
    return result;
}

keyType power2(keyType base, keyType e, keyType mod){
    keyType result = 1;
    base = base%mod;
    while (e) {
        if (e & 1) result = (keyType)((superType)result * base % mod);
        base = (keyType)((superType)base * base % mod);
        e = e>>1;
    }
    return result;
}
