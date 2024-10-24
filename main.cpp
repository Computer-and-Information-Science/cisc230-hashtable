#include "hashtable.h"
#include <iostream>
using namespace std;

int main () {
    // Create a hash table of int's
    HashTable<int> ht;

    // Add a few entries
    ht["cat"] = 10;
    ht["dog"] = 20;
    ht["bird"] = 30;

    // Add entries that should cause a collision
    ht["act"] = 40;
    ht["tac"] = 50;

    // Print the table
    ht.print(cout);
}
