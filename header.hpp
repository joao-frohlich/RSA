#ifndef HEADER_RSA_HPP
#define HEADER_RSA_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <bits/stdc++.h>
using namespace boost::multiprecision;
using namespace boost::random;

typedef uint32_t primeType;
typedef uint64_t keyType;
typedef uint128_t superType;

#define P_SIZE 64
#define N_BITS_INT 64

primeType power(primeType base, primeType e, primeType mod);
keyType power2(keyType base, keyType e, keyType mod);
keyType abs_diff(keyType x, keyType y);
std::pair<keyType,independent_bits_engine<std::mt19937, P_SIZE, primeType>> pollard_rho(keyType n, independent_bits_engine<std::mt19937, P_SIZE, primeType> gen);
bool is_composite(primeType n, primeType a, primeType d, primeType s);
bool miller_rabin(primeType n);
std::tuple<keyType,keyType,keyType> euclid(keyType a, keyType b);
keyType hash(std::wstring chunk, int chunkSize);
std::wstring unhash(keyType chunk, int chunkSize);
std::wstring process(std::wstring message, std::pair<keyType,keyType> key);
std::pair<keyType,keyType> break_rsa(std::pair<keyType,keyType> key, independent_bits_engine<std::mt19937, P_SIZE, primeType> gen);

#endif
