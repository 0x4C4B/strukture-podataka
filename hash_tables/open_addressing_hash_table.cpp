#include <iostream>

// ────────────────────────────────────────────────────────
// Hash tablica sa otvorenim adresiranjem sinonima.
// Ova implementacija koristi linearno trazenje za
// smestanje sinonima.
// ────────────────────────────────────────────────────────

enum Status {
	Empty,
	Deleted,
	Occupied
};

template <typename K, typename V>
class Node {
public:
	Status status;
	V value;
	K key;

	Node(K key, V value) {
		this->status = Occupied;
		this->value = value;
		this->key = key;
	}

	Node() {
		this->status = Empty;
	}
};

template <typename K, typename V>
class HashTable {
private:
	Node<K, V>* buckets;
	int capacity;
	int size;

	unsigned int hash(const int key) {
		return key % this->size;
	}

	// Linearno trazenje.
	//unsigned int probe(int key) {
	//	return ++key % this->size;
	//}

	// Kvadratno trazenje
	unsigned int probe(int key) {
		static int coefficient = 0;
		int result = (key + coefficient * coefficient) % this->size;
		coefficient++;
		return result;
	}
public:
	HashTable(const int size) {
		// ∙ Predstavlja niz koji drzi elemente tablice.
		this->buckets = new Node<K, V>[size];

		// ∙ Predstavlja trenutan broj elemenata u tablici.
		this->capacity = 0;

		// ∙ Predstavlja maksimalan broj elemenata u tablici.
		this->size = size;
	}

	~HashTable() {
		delete[] this->buckets;
	}

	void insert(const K key, const V value) {
		unsigned int index = this->hash(key);

		// ∙ Pretrazujemo tablicu sve dok ne dodjemo do prvog slobodnog mesta ili dok ne dodjemo
		//   do objekta koji se ponavlja.
		while (this->buckets[index].status == Occupied && this->buckets[index].key != key) {
			index = this->probe(index);
		}

		// ∙ Ukoliko je mesto gde cemo da upisemo novu vrednost prethodno bilo slobodno povecavamo
		//   broj elemenata u hash tablici za 1.
		if (this->buckets[index].status == Empty || this->buckets[index].status == Deleted) {
			this->capacity++;
		}

		// ∙ Upisujemo vrednosti na zeljenu poziciju.
		this->buckets[index].key = key;
		this->buckets[index].value = value;
		this->buckets[index].status = Occupied;
	}

	void remove(const K key) {
		unsigned int index = this->hash(key);

		// ∙ Prolazimo kroz tablicu dok ne nadjemo element koji zelimo da obrisemo.
		while (this->buckets[index].status != Empty) {
			if (this->buckets[index].key == key && this->buckets[index].status != Deleted) {
				// ∙ Za brisanje elementa je dovoljno da mu promenimo status.
				this->buckets[index].status = Deleted;
				this->capacity--;
				return;
			}
			index = this->probe(index);
		}
	}

	V& search(const K key) {
		int index = this->hash(key);
		int counter = 0;

		// ∙ Prolazimo kroz tablicu sve dok ne dodjemo do kraja.
		while (this->buckets[index].status != Empty) {
			// ∙ Ukoliko counter predje velicinu tablice znamo da trazeni element ne postoji.
			if (counter++ > this->size) {
				throw "Element not found.";
			}

			// ∙ Ukoliko je zeljeni element nadjen i on nije obrisan vracamo njegovu vrednost.
			if (this->buckets[index].key == key && this->buckets[index].status != Deleted) {
				return this->buckets[index].value;
			}

			index = this->probe(index);
		}
	}
};

int main() {
    HashTable<int, int>* table = new HashTable<int, int>(100);

	table->insert(1, 2);
	table->insert(23, 7);
	table->insert(42, 89);

	table->remove(1);

	std::cout << table->search(42) << std::endl;

	delete table;
	return 0;
}

