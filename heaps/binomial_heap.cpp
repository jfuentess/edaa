/* Author: GeeksForGeeks
 * 
 * Se mantendran los comentarios originales y todo el codigo original tomado de
 * la pagina. Se hara un wrap en una clase y se renombraran los metodos para que
 * haya mayor compatibilidad con binary_heap. */

#ifndef BINOMIAL_HEAP
#define BINOMIAL_HEAP

#include <iostream>
#include <list>
#include <vector>

using namespace std;

// A Binomial Tree node.
struct Node
{
    int data, degree; // data es la llave y degree el orden
    Node *child, *sibling, *parent;
};

class binomial_heap
{
    protected:
        list<Node *> roots;

    private:
        // crea un nuevo nodo sin referencias
        Node* newNode(int key)
        {
            Node *temp = new Node;
            temp->data = key;
            temp->degree = 0;
            temp->child = temp->parent = temp->sibling = NULL;
            return temp;
        }

        // This function merge two Binomial Trees.
        Node* mergeBinomialTrees(Node *b1, Node *b2)
        {
            // Make sure b1 is smaller
            if (b1->data > b2->data) // preservar la propiedad de heap
                    swap(b1, b2);

            // We basically make larger valued tree
            // a child of smaller valued tree
            b2->parent = b1;
            b2->sibling = b1->child;
            b1->child = b2;
            b1->degree++;
            // lo anterior reestructuro el arbol en tiempo constante

            return b1;
        }

        // This function perform union operation on two
        // binomial heap i.e. l1 & l2
        // en realidad no hace la union de tal manera que el resultado es un heap binomial
        // lo unico que hace es colocar las raices de los heaps en una lista enlazada de
        // tal manera que los ordenes sean no decrecientes
        // en terminos de estilo los push_back y los incrementos se podian hacer todos en
        // una linea con (*it++) pero acepto esto porque podria decirse que es mas claro :P
        list<Node*> unionBionomialHeap(list<Node*> l1, list<Node*> l2)
        {
            // _new to another binomial heap which contain
            // new heap after merging l1 & l2
            list<Node*> _new;
            list<Node*>::iterator it = l1.begin();
            list<Node*>::iterator ot = l2.begin();
            while (it!=l1.end() && ot!=l2.end())
            {
                    // if D(l1) <= D(l2)
                    if((*it)->degree <= (*ot)->degree)
                    {
                        _new.push_back(*it);
                        it++;
                    }
                    // if D(l1) > D(l2)
                    else
                    {
                        _new.push_back(*ot);
                        ot++;
                    }
            }

            // if there remains some elements in l1
            // binomial heap
            while (it != l1.end())
            {
                    _new.push_back(*it);
                    it++;
            }

            // if there remains some elements in l2
            // binomial heap
            while (ot!=l2.end())
            {
                    _new.push_back(*ot);
                    ot++;
            }
            return _new;
        }

        // adjust function rearranges the heap so that
        // heap is in increasing order of degree and
        // no two binomial trees have same degree in this heap
        // DEBE SER LLAMADO DESPUES DE unionBionomialHeap
        list<Node*> adjust(list<Node*> _heap)
        {
            if (_heap.size() <= 1) // nada que ajustar, _heap ya es un heap
                    return _heap;
            list<Node*> new_heap;
            list<Node*>::iterator it1,it2,it3;
            it1 = it2 = it3 = _heap.begin();

            // alinear los iteradores para que it2 = it1 + 1 y que it3 = it1 + 2
            if (_heap.size() == 2)
            {
                    it2 = it1; // redundante
                    it2++;
                    it3 = _heap.end();
            }
            else
            {
                    it2++;
                    it3=it2;
                    it3++;
            }
            while (it1 != _heap.end())
            {
                    // if only one element remains to be processed
                    if (it2 == _heap.end())
                        it1++;

                    // If D(it1) < D(it2) i.e. merging of Binomial
                    // Tree pointed by it1 & it2 is not possible
                    // then move next in heap
                    else if ((*it1)->degree < (*it2)->degree) // solo hay que avanzar pues no hay que unir
                    {
                        it1++;
                        it2++;
                        if(it3!=_heap.end())
                                it3++;
                    }

                    // if D(it1),D(it2) & D(it3) are same i.e.
                    // degree of three consecutive Binomial Tree are same
                    // in heap
                    else if (it3!=_heap.end() &&
                            (*it1)->degree == (*it2)->degree &&
                            (*it1)->degree == (*it3)->degree)
                    {
                        // como en unionBionomial heap, los input eran ya heaps, a lo mas
                        // hay tres arboles del mismo orden en cualquier momento de la computacion
                        // asi que en el siguiente paso se pasara a la siguiente condicion de este
                        // if y se hara el merge que corresponde para que solamente haya un arbol de
                        // cada orden en todo el bosque
                        it1++;
                        it2++;
                        it3++;
                    }

                    // if degree of two Binomial Tree are same in heap
                    else if ((*it1)->degree == (*it2)->degree) // unir en un arbol del siguiente orden
                    {
                        //Node *temp; // variable inutilizada
                        *it1 = mergeBinomialTrees(*it1,*it2);
                        it2 = _heap.erase(it2);
                        if(it3 != _heap.end())
                                it3++;
                    }
            }
            return _heap;
        }

        // inserting a Binomial Tree into binomial heap
        // esto es hacer meld, pero con un heap de tamanyo igual a una potencia de 2
        list<Node*> insertATreeInHeap(list<Node*> _heap, Node *tree)
        {
            // creating a new heap i.e temp
            list<Node*> temp;

            // inserting Binomial Tree into heap
            temp.push_back(tree);

            // perform union operation to finally insert
            // Binomial Tree in original heap
            temp = unionBionomialHeap(_heap,temp);

            return adjust(temp);
        }

        // removing minimum key element from binomial heap
        // this function take Binomial Tree as input and return
        // binomial heap after
        // removing head of that tree i.e. minimum element
        list<Node*> removeMinFromTreeReturnBHeap(Node *tree)
        {
            list<Node*> heap;
            Node *temp = tree->child;
            Node *lo;

            // making a binomial heap from Binomial Tree
            while (temp)
            {
                // esto elimina la raiz de tree y luego, sus hijos quedan
                // disconexos en un bosque que es un un heap binomial
                // asi que hay que guardar estos nodos como raices en
                // la lista enlazada y eliminar referencias a sus siblings
                // pues ahora no estan en el mismo arbol
                    lo = temp;
                    temp = temp->sibling;
                    lo->sibling = NULL;
                    heap.push_front(lo);
            }
            return heap;
        }

        // inserting a key into the binomial heap
        list<Node*> insert(list<Node*> _head, int key)
        {
            // unir key como un arbol de orden 0 y agregarlo a todo el heap
            Node *temp = newNode(key);
            return insertATreeInHeap(_head,temp);
        }

        // return pointer of minimum value Node
        // present in the binomial heap
        // ESTO NO TOMA TIEMPO CONSTANTE COMO SE DIJO EN EL ANALISIS TEORICO
        // TOMA TIEMPO LOGARITMICO PUES RECORRE TODAS LAS RAICES
        Node* getMin(list<Node*> _heap)
        {
            list<Node*>::iterator it = _heap.begin();
            Node *temp = *it;
            while (it != _heap.end())
            {
                    if ((*it)->data < temp->data)
                    temp = *it;
                    it++;
            }
            return temp;
        }

        list<Node*> extractMin(list<Node*> _heap)
        {
            list<Node*> new_heap,lo;
            Node *temp;

            // temp contains the pointer of minimum value
            // element in heap
            temp = getMin(_heap); // ubicar nodo a eliminar
            list<Node*>::iterator it;
            it = _heap.begin();
            while (it != _heap.end()) // agregar el resto del bosque a una lista enlazada
            {
                    if (*it != temp)
                    {
                    // inserting all Binomial Tree into new
                    // binomial heap except the Binomial Tree
                    // contains minimum element
                        new_heap.push_back(*it);
                    }
                    it++;
            }
            lo = removeMinFromTreeReturnBHeap(temp); // este es un heap con los hijos del nodo que eliminamos
            new_heap = unionBionomialHeap(new_heap,lo);
            new_heap = adjust(new_heap);
            return new_heap;
        }
        //
        // print function for Binomial Tree
        void printTree(Node *h)
        {
            while (h)
            {
                    cout << h->data << " ";
                    printTree(h->child);
                    h = h->sibling;
            }
        }

        // print function for binomial heap
        void printHeap(list<Node*> _heap)
        {
            list<Node*> ::iterator it;
            it = _heap.begin();
            while (it != _heap.end())
            {
                    printTree(*it);
                    it++;
            }
        }

    /* Este es el wrap que sirve como interfaz */
    public:
        /* Empty constructor to make an empty heap */
        binomial_heap(void)
        {
        }

        binomial_heap(const vector<int> &v)
        {
            for (int k : v)
                roots = insert(roots, k);
        }

        int top(void)
        {
            return getMin(roots)->data;
        }

        void push(int key)
        {
            roots = insert(roots, key);
        }

        void pop(void)
        {
            roots = extractMin(roots);
        }

        void meld(const binomial_heap &h)
        {
            roots = adjust(unionBionomialHeap(roots, h.roots));
        }

        bool empty(void)
        {
            return roots.empty();
        }

        void print(void)
        {
            printHeap(roots);
        }
};

#endif
