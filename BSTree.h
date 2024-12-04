#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include "BSNode.h"
#include <stdexcept>

template <typename T> 
class BSTree {
    private:
        //miembros privados
	int nelem;
	BSNode<T> *root;

	BSNode<T>* search(BSNode<T>* n, T e) const {
		if(n == nullptr){
			std::runtime_error("elemento no encontrado");
		}
		if(n->value == e){
			return n;
		}
		if(e < n->elem){
			return search(n->left, e);
		}else{
			return search(n->right, e);
		}
	}
	BSNode<T>* insert(BSNode<T>* n, T e){
		if(n == nullptr){
			nelem++;
			return new BSNode<T>(e);
		}
		if(n->elem == e){
			throw std::runtime_error("Valor ya existente");
		}
		if(n->elem > e){
			n->left = insert(n->left, e);
		}
		 if(n->elem < e){
			n->right = insert(n->right, e);
		}
		 return n;
	}

	void print_inorder(std::ostream &out, BSNode<T>* n) const {
		if(n == nullptr){
			return;
		}
		print_inorder(out, n->left);
		out << n->elem << " ";
		print_inorder(out, n->right);	
	}

	BSNode<T>* remove(BSNode<T>* n, T e){
		 if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado"); // Lanzar excepción si no se encuentra
        }
        if (e < n->elem) {
            n->left = remove(n->left, e); // Buscar en el subárbol izquierdo
        } else if (e > n->elem) {
            n->right = remove(n->right, e); // Buscar en el subárbol derecho
        } else {
            // Nodo encontrado
            if (n->left == nullptr) {
                BSNode<T>* rightChild = n->right;
                delete n;
                nelem--;
                return rightChild;
            } else if (n->right == nullptr) {
                BSNode<T>* leftChild = n->left;
                delete n;
                nelem--;
                return leftChild;
            } else {
                // Nodo con dos hijos
                T maxValue = max(n->left);
                n->value = maxValue;
                n->left = remove_max(n->left);
            }
        }
        return n;
    }

	T max(BSNode<T>* n) const {
		if(n->right == nullptr){
			return n->elem;
		}
		return max(n->right);
	}

	BSNode<T>* remove_max(BSNode<T>* n){
		if(n->right == nullptr){
			BSNode<T> *LeftChild = n->left;
			delete n;
			nelem--;
			return LeftChild;
		}
		n->right = remove_max(n->right);
		return n;
	}

	void delete_cascade(BSNode<T>* n){
		if (n == nullptr) {
            return; // Caso base: nodo nulo
        }
        delete_cascade(n->left); // Liberar subárbol izquierdo
        delete_cascade(n->right); // Liberar subárbol derecho
        delete n; // Eliminar nodo actual
	}

    public:
        // miembros públicos
    	BSTree(): root(nullptr), nelem(0) {};

	int size() const {
		return nelem;
	}

	T search(T e) const {
		BSNode<T> *result = search(root, e);

		return result->value;
	}

	T operator[](T e) const{
		return search(e);
	}

	void insert(T e){
		return insert(root, e);
	}

	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		bst.print_inorder(out);
		return out;
	}

	void remove(T e){
		root = remove(root, e);
	}

	~BSTree(){
		delete_cascade(root);
	}

};

#endif
