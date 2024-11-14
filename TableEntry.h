#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V> 
class TableEntry {
    public:
	   //mienbros publicos
	   std::string key;
	   V value;

	   TableEntry(std::string key, V value): key(key), value(value) {}

	   TableEntry(std::string key) : key(key), value(V()) {}

	   TableEntry(): key(""), value(V()) {}

	   friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){
		   return &te1.Key == &te2.key;
	   }
	  friend bool operator!=(TableEntry<V> &te1, const TableEntry<V> &te2){
		return	&te1.key != &te2.key;
	   }
	
	  friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te){
		  out<< "Key: " << &te.key << "Value: " << &te.value;
		  return out;
	  } 
		   
};

#endif
