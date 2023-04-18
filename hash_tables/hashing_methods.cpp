#include <iostream>
#include <cstring>
#include <cmath>

class Hashing {
private:
	Hashing() {}

public:
	// ---------------------------------------------------------------
	//
	//                          Metoda deljenja
	//
	// ---------------------------------------------------------------
	// 
	// Metod deljenja je odlican izbor ukoliko se u zadatku ne trazi
	// da hash funkcija bude efikasna. Za konstantu deljenja 
	// (division_constant) mozemo da odaberemo bilo koju vrednost ali
	// se preporucuje da odaberemo neki prost broj.
	//
	// ---------------------------------------------------------------

	static unsigned int division(const int key) {
		const int division_constant = 11;
		return key % division_constant;
	}


	// ---------------------------------------------------------------
	//
	//                        Metoda mnozenja
	//
	// ---------------------------------------------------------------
	// 
	// Ukoliko se u zadatku trazi da hash funkcija bude efektivna metod
	// mnozenja koji za konstantu mnozenja (multiplication_constant)
	// koristi konstantu zlatnog preseka (fibonacijev metod) je odlican
	// izbor.
	// 
	// ---------------------------------------------------------------

	static unsigned int multiplication(const int key, const int size) {
		const double multiplication_constant = 0.6180339887;
		return floor(size * (key * multiplication_constant - floor(key * multiplication_constant)));
	}


	// ---------------------------------------------------------------
	//
	//                       Metod presavijanja
	//
	// ---------------------------------------------------------------
	// 
	// Metod presavijanja je odlican ukoliko je kljuc ili veoma veliki
	// broj ili string. Velicina konstante za savijanje se bira u odnosu
	// ne velicinu hash tablice.
	// 
	// Pogodno za vece tablice (folding_constant = 1000):
	// h(257346542) = (257 + 346 + 542) mod size;
	// 
	// Pogodno za manje tablice (folding_constant = 100):
	// h(257346542) = (2 + 57 + 34 + 65 + 42) mod size;
	// 
	// Vrednost konstante za savijanje dosta utice na performanse hash
	// funckije.
	// 
	// ---------------------------------------------------------------

	static unsigned int folding(int key, const int size) {
		const int folding_constant = 100;
		unsigned int index = 0;

		while (key != 0) {
			index += key % folding_constant;
			key /= folding_constant;
		}

		return index % size;
	}

	static unsigned int folding(const char* key, const int size) {
		unsigned int index = 0;
		for (int i = 0; i < strlen(key); i++) {
			index += key[i] - '0';
		}
		return index % size;
	}
};

int main() {
	std::cout << "-- Metoda deljenja --" << std::endl;
	std::cout << Hashing::division(54) << std::endl << std::endl;

	std::cout << "-- Metoda mnozenja --" << std::endl;
	std::cout << Hashing::multiplication(54, 10) << std::endl << std::endl;

	std::cout << "-- Metoda presavijanja (int) --" << std::endl;
	std::cout << Hashing::folding(54, 10) << std::endl << std::endl;

	std::cout << "-- Metoda presavijanja (char) --" << std::endl;
	std::cout << Hashing::folding("54", 10) << std::endl;
}
