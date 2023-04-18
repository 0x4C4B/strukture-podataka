#include <iostream>

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
	K next;
	K key;

	Node(K key, V value) {
		this->status = Occupied;
		this->value = value;
		this->key = key;
		this->next = -1;
	}

	Node() {
		this->status = Empty;
		this->next = -1;
	}
};

template <typename K, typename V>
class HashTable {
private:
	Node<K, V>* buckets;
	int capacity;
	int size;

	unsigned int hash(const int key) {
		return key % 10;
	}
        
    // Kvadratno trazenje
	unsigned int probe(int key) {
		static int coefficient = 0;
		int result = (key + coefficient * coefficient) % this->size;
		coefficient++;
		return result;
	}

    // Linearno trazenje
	//unsigned int probe(int key) {
	//	return ++key % 10;
	//}
public:
	HashTable(const int size) {
		this->buckets = new Node<K, V>[size];
		this->capacity = 0;
		this->size = size;
	}

	~HashTable() {
		delete[] this->buckets;
	}

	void insert(const K key, const V value) {
		unsigned int index = this->hash(key);
		unsigned int target = index;

		while (this->buckets[target].next != -1) {
			target = this->buckets[target].next;
		}

		while (this->buckets[index].status == Occupied && this->buckets[index].key != key) {
			int test = this->probe(index);
			index = test;
		}

		if (this->buckets[index].status == Empty || this->buckets[index].status == Deleted) {
			if (index != target) this->buckets[target].next = index;
			this->capacity++;
		}

		this->buckets[index].key = key;
		this->buckets[index].value = value;
		this->buckets[index].status = Occupied;
	}

	void remove(const K key) {
		unsigned int index = this->hash(key);

		while (index != -1) {
			if (this->buckets[index].key == key && this->buckets[index].status != Deleted) {
				this->buckets[index].status = Deleted;
				this->capacity--;
				return;
			}
			index = this->buckets[index].next;
		}
	}

	V& search(const K key) {
		unsigned int index = this->hash(key);

		while (index != -1) {
			if (this->buckets[index].key == key && this->buckets[index].status != Deleted) {
				return this->buckets[index].value;
			}

			index = this->buckets[index].next;
		}
        throw "Not found.";
	}

	void print() {
		for (int i = 0; i < this->size; i++) {
			std::cout << i << " " << this->buckets[i].key << " " << this->buckets[i].value << " " << this->buckets[i].next << " " << this->buckets[i].status << std::endl;
		}
	}
};

int main() {
    HashTable<int, int>* table = new HashTable<int, int>(100);

	table->insert(10, 15);
	table->insert(12, 20);
	table->insert(20, 25);
	table->insert(40, 30);

	table->remove(40);

	table->print();

	std::cout << table->search(20) << std::endl;

	delete table;
    return 0;
}
