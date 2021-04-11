#include "../header.hpp"

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

bool is_composite(primeType n, primeType a, primeType d, primeType s) {
    primeType x = power(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (primeType r = 1; r < s; r++) {
        x = (primeType)((keyType)x * x % n);
        if (x == n - 1) return false;
    }
    return true;
}
