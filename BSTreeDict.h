#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        // ...
	BSTree<TableEntry<V>>* tree;

    public:
        // ...
        BSTreeDict(){
	tree = new BSTree<TableEntry<V>>();
	}
	~BSTreeDict(){
		delete tree;
	}

	friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
		out << *(bs.tree);
		return out;
	}

	V operator[](string key){
   		 return tree -> search(TableEntry<V>(key)).value;  //Devolvemos valor de la key
  	}

	 void insert(string key, V value) override{
   		 TableEntry<V> entry(key, value); //Crea una entrada con la clave y el valor
    		tree -> insert(entry); //Inserta la entrada en el ABB (usa el método insert() del fichero BSTree.h)
  }

	V search(string key) override{
    		TableEntry<V> entry(key);
    		return tree -> search(entry).value;
  	}

	V remove(string key) override{
    		V valor = tree -> search(TableEntry<V>(key)).value;
    		TableEntry<V> entry(key);
    		tree -> remove(entry);
    		return valor;
  	}

	 int entries() override{
    		return tree -> size();
  	}

};

#endif
