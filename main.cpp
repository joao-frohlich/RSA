#include "header.hpp"

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
