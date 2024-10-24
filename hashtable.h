// hashtable.h - A hash table template for storing objects of some data  type
//	using string keys.
#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <exception>

template <typename T>
class HashTable {
public:
	static const size_t TABLE_SIZE = 1000; // Size of the table

private:
	class Entry { // An entry in the table
	public:
		std::string key;	// The key for this table entry
		T object;			// The object stored in this table entry
		bool used;			// Is this entry used?
		Entry() { used = false; }
	};

	Entry entries[TABLE_SIZE];

	// The hash function. This is a simple hash function that simply adds
	// the ASCII values of the characters and mods by the table size.
	// This is hash function shown in Figure 5.2 in the textbook.
	size_t hash(const std::string &key) const {
		size_t hashVal = 0;
		for (int i = 0; i < key.size(); i++)
			hashVal += key[i];
		return hashVal % TABLE_SIZE;
	}

public:
	// Access an object using the array index operator. If an object does
	// not exist with the given key, an entry is created.
	T &operator[](const std::string &k);

	// Access an object using the array index operator, when the table is
	// read-only. If the key does not exist, an exception is thrown.
	const T &operator[](const std::string &k) const;

	// Used to determine if a key exists in the table.
	bool is_key(const std::string& k) const;

	// A function to print all used entries in table. This is not typically
	// part of a hash table, but is included for debugging purposes.
	void print(std::ostream &out) const;
};

template <typename T>
T &HashTable<T>::operator[](const std::string &k) {

	// Determine hash value, then use linear probing if necessary
	size_t index = hash(k);
	size_t count = 0;
	while (entries[index].used && entries[index].key != k) {
		if (++count > TABLE_SIZE)
			throw std::overflow_error("Hash table overflow");
		index = (index + 1) % TABLE_SIZE;
	}

	// If the index identified is not already used, create a new entry.
	if (!entries[index].used) {
		entries[index].key = k;
		entries[index].used = true;
	}

	// Return the object stored in this entry.
	return entries[index].object;
}

template <typename T>
const T &HashTable<T>::operator[](const std::string &k) const {

	// Determine hash value, then use linear probing if necessary
	size_t index = hash(k);
	size_t count = 0;
	while (entries[index].used && entries[index].key != k && ++count <= TABLE_SIZE)
		index = (index + 1) % TABLE_SIZE;

	// If not found, throw an exception
	if (!entries[index].used || entries[index].key != k)
		throw std::out_of_range("Key not found");

	// Return the object in this entry
	return entries[index].object;
}

template <typename T>
void HashTable<T>::print(std::ostream &out) const {
	out << "   Index    Hash  Key / Value\n";
	out << "   -----    ----  -----------\n";
	for (size_t i = 0; i < TABLE_SIZE; i++)
		if (entries[i].used)
			out << std::setw(8) << i << std::setw(8) << hash(entries[i].key)
				<< "  " << entries[i].key << " / "
				<< entries[i].object << std::endl;
}
