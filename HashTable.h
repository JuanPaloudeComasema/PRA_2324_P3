#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/PRA_2324_P1_Juan/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable: public Dict<V> {

    private:
        // ...
	int n;
	int max;
	ListLinked<TableEntry<V>>* table;
	int h(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum;
       	}


    public:
        // ...
	HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

	 ~HashTable() {
        delete[] table;
    }
	 int capacity() const {
        return max;
    }
	  friend std::ostream& operator<<(std::ostream &out, const HashTable &ht) {
        for (int i = 0; i < ht.max; ++i) {
            out << i << ": " << ht.table[i] << std::endl;
        }
        return out;
    }
	   V operator[](std::string key){
        int index = h(key);
	TableEntry<V> Tar = TableEntry<V>(key);
       /* for (auto &entry : table[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }*/
	if(table->search(index) == -1){
        	throw std::runtime_error("Key not found");
	}
	return table->search(Tar);
    }

	   void insert(std::string key, V value){
		int index = h(key);
		TableEntry<V> Tar = TableEntry<V>(key, value);
		/*for (auto &entry : table[index]) {
        		if (entry.key == key) {
            			throw std::runtime_error("Key already exists");
        		}
    		}*/
		if(table->search(Tar) != -1){
			throw std::runtime_error("LLave ya existente");
		}
		table->insert(index, Tar);
		n++;
	   }

	   V search(std::string key){
		TableEntry<V> Tar = TableEntry<V>(key);
		   int index = h(key);
		   return table->get(index);
	   }

	   V remove(std::string key){
		   TableEntry<V> Tar = TableEntry<V>(key);
		   if(table->search(key) == -1){
                        throw std::runtime_error("LLave no existente");
                }
		   int index = h(key);
		table->remove(index);
		n--;
	   }

	   int entries(){
		   return n;
	   }

				
};
#endif
