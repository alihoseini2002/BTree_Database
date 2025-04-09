#ifndef BTREE_H
#define BTREE_H
#include <vector>

template <typename tmptype,int maxdegree> class BTree;
template <typename tmptype,int maxdegree> class BTreeNode;

template <typename tmptype,int maxdegree> 
class Node{
    public:
        tmptype data;
        Node<tmptype,maxdegree>* nextField;
        BTreeNode<tmptype,maxdegree>* self;
};

template <typename tmptype,int maxdegree> 
class BTreeNode{
    friend class BTree<tmptype,maxdegree>;
    public:
        BTreeNode();
    private:
        int size;
        Node<tmptype,maxdegree>** Nodes;
        BTreeNode<tmptype,maxdegree>* father;
        BTreeNode<tmptype,maxdegree>** childrens;
};

template <typename tmptype,int maxdegree>
class BTree{
    public:
        //void display();
        BTree();
        vector<Node<tmptype,maxdegree>*> itaratormin(tmptype,string);
        vector<Node<tmptype,maxdegree>*> itaratormax(tmptype,string);
        Node<tmptype,maxdegree>* find(tmptype);
        Node<tmptype,maxdegree>* findmin();
        Node<tmptype,maxdegree>* findmax();
        Node<tmptype,maxdegree>* insertNode(tmptype);
        Node<tmptype,maxdegree>* deleteNode(tmptype);
        Node<tmptype,maxdegree>* deleteNode_by_node(Node<tmptype,maxdegree>*);
        Node<tmptype,maxdegree>* updateNodeint(tmptype,tmptype);
        Node<tmptype,maxdegree>* updateNodeNode(Node<tmptype,maxdegree>*,tmptype);
    private:
        void itaratorminhelper(tmptype,BTreeNode<tmptype,maxdegree>*,string,vector<Node<tmptype,maxdegree>*>&);
        void itaratormaxhelper(tmptype,BTreeNode<tmptype,maxdegree>*,string,vector<Node<tmptype,maxdegree>*>&);
        void fixhigh(BTreeNode<tmptype,maxdegree>*);
        void fixlow(BTreeNode<tmptype,maxdegree>*);
        Node<tmptype,maxdegree>* findpredecessor(Node<tmptype,maxdegree>*);
        BTreeNode<tmptype,maxdegree>* root;
        bool isEmpty();
        bool iterate;
};

#endif