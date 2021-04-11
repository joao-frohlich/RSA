#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <bits/stdc++.h>
using namespace boost::multiprecision;
using namespace boost::random;

typedef uint256_t primeType;
typedef uint512_t keyType;
typedef uint1024_t superType;

#define P_SIZE 512
#define N_BITS_INT 512



int c = 0;

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

keyType abs_diff(keyType x, keyType y){
    return (x >= y) ? x-y : y-x;
}

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

bool is_composite(primeType n, primeType a, primeType d, primeType s) {
    primeType x = power(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (primeType r = 1; r < s; r++) {
        x = (primeType)((keyType)x * x % n);
        if (x == n - 1) return false;
    }
    return true;
}

bool miller_rabin(primeType n) {
    if (n < 2) return false;
    primeType r = 0;
    primeType d = n - 1;
    while ((d & 1) == 0) d >>= 1, ++r;
    for (primeType a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59}) {
        if (n == a) return true;
        if (is_composite(n, a, d, r)) return false;
    }
    return true;
}

std::tuple<keyType,keyType,keyType> euclid(keyType a, keyType b){
    if (b == 0) return std::make_tuple(a,1,0);
    else {
        std::tuple<keyType,keyType,keyType> aux = euclid(b,a%b);
        return std::make_tuple(std::get<0>(aux),std::get<2>(aux),std::get<1>(aux)-(keyType)(a/b)*std::get<2>(aux));
    }
}

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

std::pair<keyType,keyType> break_rsa(std::pair<keyType,keyType> key, independent_bits_engine<std::mt19937, P_SIZE, primeType> gen){
    keyType p1; std::tie(p1,gen) = pollard_rho(key.second, gen);
    while (p1 == key.second) std::tie(p1,gen) = pollard_rho(key.second, gen);
    keyType p2 = key.second/p1;
    keyType t = (p1-1)*(p2-1);
    keyType d = (std::get<2>(euclid(t,key.first)))%t;
    return std::make_pair(d,key.second);
}

int main(int argc, char const *argv[]) {
    //primeType: inteiro de 256 bits sem sinal
    //keyType: inteiro de 512 bits sem sinal

    independent_bits_engine<std::mt19937, P_SIZE, primeType> genPrimeType;

    primeType p = 1, q = 1;
    while (!miller_rabin(p)){
        //sleep(1);
        p = genPrimeType();
        // std::cout << p << std::endl;
    }
    while (!(miller_rabin(q) && q != p)){
        //sleep(1);
        q = genPrimeType();
        // std::cout << q << std::endl;
    }
    std::cout << "Números primos gerados" << std::endl;
    std::cout << p << std::endl;
    std::cout << q << std::endl << std::endl;
    keyType n = (keyType)p*(keyType)q;
    keyType t = (keyType)(p-1)*(keyType)(q-1);
    keyType e = 3;
    while (std::__gcd(e,t) != 1){
        e += 2;
    }
    keyType d = (std::get<2>(euclid(t,e)))%t;

    std::cout << "Chave pública P" << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "n: " << n << std::endl << std::endl;

    std::cout << "Chave privada S" << std::endl;
    std::cout << "d: " << d << std::endl;
    std::cout << "n: " << n << std::endl << std::endl;

    std::pair<keyType,keyType> P(e,n), S(d,n);


    std::wstring a;
    std::cout << "Insira a mensagem a ser criptografada" << std::endl;
    std::wcin >> a;
    std::wstring crypt = process(a,P);
    std::wcout << "Mensagem criptografada: " << crypt << std::endl;
    std::wstring decrypt = process(crypt,S);
    std::wcout << "Mensagem descriptografada: " << decrypt << std::endl << std::endl;

    std::cout << "Iniciando quebra da chave" << std::endl << std::endl;
    std::pair<keyType,keyType> B = break_rsa(P, genPrimeType);
    std::cout << "Chave encontrada" << std::endl;
    std::cout << "d: " << B.first << std::endl;
    std::cout << "n: " << B.second << std::endl << std::endl;

    std::cout << "Chave original" << std::endl;
    std::cout << "d: " << S.first << std::endl;
    std::cout << "n: " << S.second << std::endl << std::endl;
    //std::wcout << process(process(a,P),S) << std::endl;
    //std::cout << power2(power2(500,e,n),d,n) << std::endl;
    return 0;
}
