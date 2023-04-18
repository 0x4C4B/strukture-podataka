#include <iostream>

// ────────────────────────────────────────────────────────
// Hash tablica sa spoljasnjim ulancavanjem sinonima.
// ────────────────────────────────────────────────────────

template <typename K, typename V>
class Node {
public:
	Node<K, V>* next;
	V value;
	K key;

	Node(K key, V value) {
		this->value = value;
		this->key = key;
	}
};

template <typename K, typename V>
class HashTable {
private:
	// ∙ Predstavlja niz koji sadrzi lancane liste u kojima se nalaze elementi
	//   tablice.
	Node<K, V>** buckets;

	// ∙ Predstavlja broj elemenata u tablici.
	int capacity;

	// ∙ Predstavlja maksimalan broj lancanih listi.
	int size;

	int hash(int key) {
		return key % this->size;
	}

public:
	HashTable(int size) {
		this->size = size;
		this->capacity = 0;
		this->buckets = new Node<K, V>*[size]();
	}

	~HashTable() {
		for (int i = 0; i < this->size; i++) {
			Node<K, V>* current = this->buckets[i];
			while (current != nullptr) {
				Node<K, V>* previous = current;
				current = current->next;
				delete previous;
			}
			this->buckets[i] = nullptr;
		}
		delete[] this->buckets;
	}

	void insert(K key, V value) {
		unsigned int index = this->hash(key);
		Node<K, V>* previous = nullptr;
		Node<K, V>* entry = this->buckets[index];

		// ∙ Prolazimo kroz lancanu listu dok ne dodjemo do kraja.
		while (entry != nullptr && entry->key != key) {
			previous = entry;
			entry = entry->next;
		}

		if (entry == nullptr) {
			entry = new Node<K, V>(key, value);
			if (previous == nullptr) {
				// ∙ Ukoliko je lancana lista prazna.
				this->buckets[index] = entry;
			} else {
				// ∙ Ukoliko lancana lista nije prazna.
				previous->next = entry;
			}
			this->capacity++;
		} else {
			// ∙ Ukoliko samo menjamo vec postojecu vrednost
			//   cvora.
			entry->value = value;
		}
	}

	void remove(const K& key) {
		unsigned int index = this->hash(key);
		Node<K, V>* previous = nullptr;
		Node<K, V>* entry = this->buckets[index];

		// ∙ Prolazimo kroz lancanu listu sve dok ne dodjemo do
		//   elementa za brisanje.
		while (entry != nullptr && entry->key != key) {
			previous = entry;
			entry = entry->next;
		}

		// ∙ Ukoliko nije nadjen element za brisanje.
		if (entry == nullptr) {
			return;
		} else {
			// ∙ Ukoliko je element za brisanje prvi u lancanoj listi.
			if (previous == nullptr) {
				this->buckets[index] = entry->next;
			} else {
				// ∙ Ukoliko element nije prvi u lancanoj listi.
				previous->next = entry->next;
			}
			delete entry;
		}
	}

	V& search(const int key) {
		// ∙ Nadjemo glavu lancane liste u tablici.
		int index = this->hash(key);
		Node<K, V>* current = this->buckets[index];

		// ∙ Prolazimo kroz lancanu listu dok ne nadjemo trazenu vrednost.
		while (current != nullptr) {
			if (current->key == key) {
				return current->value;
			}
			current = current->next;
		}
	}
};

int main() {
	HashTable<int, int>* table = new HashTable<int, int>(100);

	table->insert(1, 2);
	table->insert(3, 4);
	table->insert(23, 7);
	table->insert(42, 89);

	table->remove(1);

	std::cout << table->search(42) << std::endl;

	delete table;
}
