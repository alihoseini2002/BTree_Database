#ifndef AVLREE_H
#define AVLREE_H
#include <BTree.h>

template <typename tmptype,int maxdegree> class AvlTree;

template <typename tmptype,int maxdegree>
class AvlNode{
    friend class AvlTree<tmptype,maxdegree>;
    public:
        AvlNode(tmptype,int,string*,string*,BTree<long long,maxdegree>*,MinHeap*);
        tmptype getdata();
        void setdata(tmptype);
    private:
        AvlNode<tmptype,maxdegree>* right;
        AvlNode<tmptype,maxdegree>* left;
        AvlNode<tmptype,maxdegree>* father;
        tmptype data;
        string* columns;
        string* columnstype;
        MinHeap* get_id;
        BTree<long long,maxdegree>* table;
        int size;
        int compare;
};

template <typename tmptype,int maxdegree>
class AvlTree{
    public:
        AvlTree();
        void insertnode(tmptype,int,string*,string*,BTree<long long,maxdegree>*,MinHeap*);
        int getsize();
        bool isEmpty();
        BTree<long long,maxdegree>* find(tmptype,int&,string*&,string*&,MinHeap*&);
    private:
        void rotate_right(AvlNode<tmptype,maxdegree>*,AvlNode<tmptype,maxdegree>*);
        void rotate_left(AvlNode<tmptype,maxdegree>*,AvlNode<tmptype,maxdegree>*);
        AvlNode<tmptype,maxdegree>* root;
        int size;
};

#endif