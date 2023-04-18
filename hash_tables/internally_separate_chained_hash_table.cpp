#pragma once

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
	int pointer;
	int size;

	unsigned int hash(const int key) {
		return key % this->size;
	}

	unsigned int probe(int key) {
		static int coefficient = 0;
		int result = (key + coefficient * coefficient) % this->size;
		coefficient++;
		return result;
	}

	//unsigned int probe(int key) {		
    //	return ++key % this->size;
	//}
public:
	HashTable(const int size) {
		this->buckets = new Node<K, V>[2 * size];
		this->pointer = size;
		this->capacity = 0;
		this->size = size;
	}

	~HashTable() {
		delete[] this->buckets;
	}

	void insert(const K key, const V value) {
		unsigned int index = this->hash(key);
		unsigned int target = index;

		if (this->capacity == this->size) {
			return;
		}

		while (this->buckets[target].next != -1) {
			target = this->buckets[target].next;
		}

		if (this->buckets[index].status == Occupied && this->buckets[index].key != key) {
			int counter = 0;
			do {
				if (counter > this->size) return;
				this->pointer = this->size + this->probe(this->pointer);
				counter++;
			} while (this->buckets[this->pointer].status == Occupied);
			index = this->pointer;
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
	}

	void print() {
		for (int i = 0; i < this->size; i++) {
			std::cout << i << " " << this->buckets[i].key << " " << this->buckets[i].value << " " << this->buckets[i].next << " " << this->buckets[i].status << std::endl;
		}
		std::cout << "--------------------------------" << std::endl;
		for (int i = this->size; i < 2 * this->size; i++) {
			std::cout << i << " " << this->buckets[i].key << " " << this->buckets[i].value << " " << this->buckets[i].next << " " << this->buckets[i].status << std::endl;
		}
	}
};


int main() {
	HashTable<int, int>* table = new HashTable<int, int>(10);

	table->insert(10, 15);
	table->insert(12, 20);
	table->insert(20, 25);
	table->insert(30, 30);
	table->insert(22, 50);
	table->insert(40, 70);
	table->insert(50, 70);
	table->insert(60, 70);
	table->insert(70, 70);

	table->remove(20);

	table->print();

	std::cout << table->search(30) << std::endl;

	delete table;
	return 0;
}
