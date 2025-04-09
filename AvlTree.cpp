#include <iostream>
#include <BTree.h>
#include <AvlTree.h>
using namespace std;

//start AvlNode

template <typename tmptype,int maxdegree>
AvlNode<tmptype,maxdegree>::AvlNode(tmptype a,int s,string* col,string* coltype,BTree<long long,maxdegree>* one_table,MinHeap *g){
    setdata(a);
    size=s;
    columns=col;
    columnstype=coltype;
    table=one_table;
    right=0;
    left=0;
    father=0;
    compare=0;
    get_id=g;
}

template <typename tmptype,int maxdegree>
tmptype AvlNode<tmptype,maxdegree>::getdata(){
    return data;
}

template <typename tmptype,int maxdegree>
void AvlNode<tmptype,maxdegree>::setdata(tmptype a){
    data=a;
}

//end AvlNode

//start AvlTree

template <typename tmptype,int maxdegree>
AvlTree<tmptype,maxdegree>::AvlTree(){
    root=0;
    size=0;
}

template <typename tmptype,int maxdegree>
int AvlTree<tmptype,maxdegree>::getsize(){
    return size;
}

template <typename tmptype,int maxdegree>
bool AvlTree<tmptype,maxdegree>::isEmpty(){
    if(size==0){
        return true;
    }
    return false;
}

template <typename tmptype,int maxdegree>
void AvlTree<tmptype,maxdegree>::insertnode(tmptype a,int s,string* col,string* coltype,BTree<long long,maxdegree>* one_table,MinHeap *g){
    AvlNode<tmptype,maxdegree>* tmp=new AvlNode<tmptype,maxdegree>(a,s,col,coltype,one_table,g);
    if(size==0){
        root=tmp;
    }
    else{
        AvlNode<tmptype,maxdegree>* tmp2=root;
        while(true){
            if(a>=tmp2->getdata()){
                if(tmp2->right==0){
                    tmp2->right=tmp;
                    tmp->father=tmp2;
                    break;
                }
                tmp2=tmp2->right;
            }
            else{
                if(tmp2->left==0){
                    tmp2->left=tmp;
                    tmp->father=tmp2;
                    break;
                }
                tmp2=tmp2->left;
            }
        }
        AvlNode<tmptype,maxdegree>* tmp3=tmp;
        while(tmp3->father!=0){
            if(tmp3->father->right==tmp3){
                tmp3->father->compare++;
            }
            else{
                tmp3->father->compare--;
            }
            if(tmp3->father->compare==0){
                break;
            }
            else if (tmp3->father->compare==2){
                tmp3=tmp3->father->right;
                if(tmp3->compare==1){
                    rotate_left(tmp3->father,tmp3);
                    tmp3->compare=0;
                    tmp3->left->compare=0;
                    break;
                }
                else if(tmp3->compare==-1){
                    bool a=false,b=false;
                    rotate_right(tmp3,tmp3->left);
                    rotate_left(tmp3->father->father,tmp3->father);
                    if(tmp3->father->compare==1){
                        b=true;
                    }
                    else if(tmp3->father->compare==-1){
                        a=true;
                    }
                    tmp3->compare=0;
                    tmp3->father->compare=0;
                    tmp3->father->left->compare=0;
                    if(a){
                        tmp3->father->left->compare=-1;
                    }
                    if(b){
                        tmp3->compare=1;
                    }
                    break;
                }
            }
            else if(tmp3->father->compare==-2){
                tmp3=tmp3->father->left;
                if(tmp3->compare==-1){
                    rotate_right(tmp3->father,tmp3);
                    tmp3->compare=0;
                    tmp3->right->compare=0;
                    break;
                }
                else if(tmp3->compare==1){
                    bool a=false,b=false;
                    rotate_left(tmp3,tmp3->right);
                    rotate_right(tmp3->father->father,tmp3->father);
                    if(tmp3->father->compare==1){
                        b=true;
                    }
                    else if(tmp3->father->compare==-1){
                        a=true;
                    }
                    tmp3->compare=0;
                    tmp3->father->compare=0;
                    tmp3->father->right->compare=0;
                    if(a){
                        tmp3->father->right->compare=1;
                    }
                    if(b){
                        tmp3->compare=-1;
                    }
                    break;
                }
            }
            tmp3=tmp3->father;
        }
    }
    size++;
}

template <typename tmptype,int maxdegree>
void AvlTree<tmptype,maxdegree>::rotate_right(AvlNode<tmptype,maxdegree>* a,AvlNode<tmptype,maxdegree>* aleft){
    if(a==root){
        AvlNode<tmptype,maxdegree>* tmp=aleft->right;
        aleft->right=a;
        a->father=aleft;
        aleft->father=0;
        root=aleft;
        a->left=tmp;
        if(tmp!=0){
            tmp->father=a;   
        }
    }
    else{
        AvlNode<tmptype,maxdegree>* tmp=a->father;
        if(tmp->right==a){
            tmp->right=aleft;
        }
        else{
            tmp->left=aleft;
        }
        aleft->father=tmp;
        AvlNode<tmptype,maxdegree>* tmp2=aleft->right;
        aleft->right=a;
        a->father=aleft;
        a->left=tmp2;
        if(tmp2!=0){
            tmp2->father=a;
        }
    }
}

template <typename tmptype,int maxdegree>
void AvlTree<tmptype,maxdegree>::rotate_left(AvlNode<tmptype,maxdegree>* a,AvlNode<tmptype,maxdegree>* aright){
    if(a==root){
        AvlNode<tmptype,maxdegree>* tmp=aright->left;
        aright->left=a;
        a->father=aright;
        aright->father=0;
        root=aright;
        a->right=tmp;
        if(tmp!=0){
            tmp->father=a;   
        }
    }
    else{
        AvlNode<tmptype,maxdegree>* tmp=a->father;
        if(tmp->right==a){
            tmp->right=aright;
        }
        else{
            tmp->left=aright;
        }
        aright->father=tmp;
        AvlNode<tmptype,maxdegree>* tmp2=aright->left;
        aright->left=a;
        a->father=aright;
        a->right=tmp2;
        if(tmp2!=0){
            tmp2->father=a;
        }
    }
}

template <typename tmptype,int maxdegree>
BTree<long long,maxdegree>* AvlTree<tmptype,maxdegree>::find(tmptype a,int& s,string*& col,string*& coltype,MinHeap *&g){
    AvlNode<tmptype,maxdegree>* tmp=root;
    BTree<long long,maxdegree>* this_table=0;
    while(tmp!=0){
        if(a==tmp->getdata()){
            g=tmp->get_id;
            s=tmp->size;
            col=tmp->columns;
            coltype=tmp->columnstype;
            this_table=tmp->table;
            break;
        }
        else if(a>tmp->getdata()){
            tmp=tmp->right;
        }
        else if(a<tmp->getdata()){
            tmp=tmp->left;
        }
    }
    return this_table;
}

//end AvlTree