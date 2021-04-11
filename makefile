parametrosCompilacao = -std=c++11

all: rsa

rsa: main.o break_rsa.o encryption.o euclid.o fast_modular_exponentiation.o hashing.o miller_rabin.o pollard_rho.o
	g++ -o rsa main.o break_rsa.o encryption.o euclid.o fast_modular_exponentiation.o hashing.o miller_rabin.o pollard_rho.o $(parametrosCompilacao)
	rm *.o

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

break_rsa.o: functions/break_rsa.cpp
	g++ -c functions/break_rsa.cpp $(parametrosCompilacao)

encryption.o: functions/encryption.cpp
	g++ -c functions/encryption.cpp $(parametrosCompilacao)

euclid.o: functions/euclid.cpp
	g++ -c functions/euclid.cpp $(parametrosCompilacao)

fast_modular_exponentiation.o: functions/fast_modular_exponentiation.cpp
	g++ -c functions/fast_modular_exponentiation.cpp $(parametrosCompilacao)

hashing.o: functions/hashing.cpp
	g++ -c functions/hashing.cpp $(parametrosCompilacao)

miller_rabin.o: functions/miller_rabin.cpp
	g++ -c functions/miller_rabin.cpp $(parametrosCompilacao)

pollard_rho.o: functions/pollard_rho.cpp
	g++ -c functions/pollard_rho.cpp $(parametrosCompilacao)

clean:
	rm rsa
