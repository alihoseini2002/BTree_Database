#include <iostream>
#include "BTree.h"
#include <vector>
using namespace std;

//start BTree:

template <typename tmptype,int maxdegree>
BTreeNode<tmptype,maxdegree>::BTreeNode(){   
    size=0;
    father=0;
    Nodes=new Node<tmptype,maxdegree>* [maxdegree];
    childrens=new BTreeNode<tmptype,maxdegree>*[maxdegree+1];
    for(int i=0;i<maxdegree;i++){
        Nodes[i]=0;
        childrens[i]=0;
    }
    childrens[maxdegree]=0;
}

//end BTreeNode

//start BTree
template <typename tmptype,int maxdegree>
BTree<tmptype,maxdegree>::BTree(){
    root=0;
}

template <typename tmptype,int maxdegree>
bool BTree<tmptype,maxdegree>::isEmpty(){
    if(root!=0 && root->size!=0){
        return false;
    }
    return true;
}

template <typename tmptype,int maxdegree>
Node<tmptype,maxdegree>* BTree<tmptype,maxdegree>::findmin(){
    BTreeNode<tmptype,maxdegree>* tmp=root;
    while(tmp->childrens[0]!=0){
        tmp=tmp->childrens[0];
    }
    return tmp->Nodes[0];
}

template <typename tmptype,int maxdegree>
Node<tmptype,maxdegree>* BTree<tmptype,maxdegree>::findmax(){
    BTreeNode<tmptype,maxdegree>* tmp=root;
    while(tmp->childrens[(tmp->size)]!=0){
        tmp=tmp->childrens[tmp->size];
    }
    return tmp->Nodes[tmp->size-1];
}

template <typename tmptype,int maxdegree>
Node<tmptype,maxdegree>* BTree<tmptype,maxdegree>::find(tmptype a){
    BTreeNode<tmptype,maxdegree>* tmp=root;
    while(tmp!=0){
        if(a>tmp->Nodes[(tmp->size)-1]->data){
                tmp=tmp->childrens[tmp->size];
                continue;
        }
        for(int i=0;i<(tmp->size);i++){
            if(a==tmp->Nodes[i]->data){
                return tmp->Nodes[i];
            }
            if(a<tmp->Nodes[i]->data){
                tmp=tmp->childrens[i];
                break;
            }
        }
    }
    return 0;
}

template <typename tmptype,int maxdegree>
Node<tmptype,maxdegree>* BTree<tmptype,maxdegree>::findpredecessor(Node<tmptype,maxdegree>* a){
    BTreeNode<tmptype,maxdegree>* tmpBTreeNode=a->self;
    int x;
    for(int i=0;i<(tmpBTreeNode->size);i++){
        if(tmpBTreeNode->Nodes[i]==a){
            x=i;
            break;
        }
    }
    tmpBTreeNode=tmpBTreeNode->childrens[x];
    while(tmpBTreeNode->childrens[(tmpBTreeNode->size)]!=0){
        tmpBTreeNode=tmpBTreeNode->childrens[(tmpBTreeNode->size)];
    }
    return tmpBTreeNode->Nodes[(tmpBTreeNode->size)-1];
}

template <typename tmptype,int maxdegree>
Node<tmptype,maxdegree>* BTree<tmptype,maxdegree>::insertNode(tmptype a){
    Node<tmptype,maxdegree>* newnode=new Node<tmptype,maxdegree>();
    if(isEmpty()){
        BTreeNode<tmptype,maxdegree>* tmp=new BTreeNode<tmptype,maxdegree>();
        tmp->Nodes[0]=newnode;
        tmp->Nodes[0]->data=a;
        tmp->Nodes[0]->self=tmp;
        (tmp->size)++;
        root=tmp;
    }
    else{
        BTreeNode<tmptype,maxdegree>* tmp=root;
        while(tmp->childrens[0]!=0){
            if(a>tmp->Nodes[(tmp->size)-1]->data){
                tmp=tmp->childrens[tmp->size];
                continue;
            }
            for(int i=0;i<(tmp->size);i++){
                if(a<=tmp->Nodes[i]->data){
                    tmp=tmp->childrens[i];
                    break;
                }
            }
        }
        newnode->data=a;
        tmp->Nodes[tmp->size]=newnode;
        tmp->Nodes[tmp->size]->self=tmp;
        (tmp->size)++;
        Node<tmptype,maxdegree>* x;
        int i=tmp->size-1;
        while((tmp->Nodes[i-1]->data)>(tmp->Nodes[i]->data)){
            x=tmp->Nodes[i];
            tmp->Nodes[i]=tmp->Nodes[i-1];
            tmp->Nodes[i-1]=x;
            i--;
            if(i<=0){
                break;
            }
        }
        if((tmp->size)>=maxdegree){
            fixhigh(tmp);
        }
    }
    return newnode;
}

template <typename tmptype,int maxdegree>
void BTree<tmptype,maxdegree>::fixhigh(BTreeNode<tmptype,maxdegree>* a){
    if(a==root){
        BTreeNode<tmptype,maxdegree>* dad=new BTreeNode<tmptype,maxdegree>();
        dad->Nodes[0]=a->Nodes[((maxdegree-1)/2)];
        dad->Nodes[0]->self=dad;
        (dad->size)++;
        BTreeNode<tmptype,maxdegree>* left=new BTreeNode<tmptype,maxdegree>();
        for(int i=0;i<((maxdegree-1)/2);i++){
            left->Nodes[i]=a->Nodes[i];
            left->Nodes[i]->self=left;
            (left->size)++;
        }
        for(int i=0;i<=(left->size);i++){
            left->childrens[i]=a->childrens[i];
            if(left->childrens[i]!=0){
                left->childrens[i]->father=left;
            }
        }
        BTreeNode<tmptype,maxdegree>* right=new BTreeNode<tmptype,maxdegree>();
        for(int i=((maxdegree+1)/2);i<(a->size);i++){
            right->Nodes[i-((maxdegree+1)/2)]=a->Nodes[i];
            right->Nodes[i-((maxdegree+1)/2)]->self=right;
            (right->size)++;
        }
        for(int i=0;i<=(right->size);i++){
            right->childrens[i]=a->childrens[i+((maxdegree+1)/2)];
            if(right->childrens[i]!=0){
                right->childrens[i]->father=right;
            }
        }
        dad->childrens[0]=left;
        dad->childrens[1]=right;
        left->father=dad;
        right->father=dad;
        delete a;
        root=dad;
    }
    else{
        BTreeNode<tmptype,maxdegree>* dad=a->father;
        tmptype x=a->Nodes[((maxdegree-1)/2)]->data;
        int y=dad->size;
        for(int i=((dad->size)-1);i>=0;i--){
            if(dad->Nodes[i]->data>x){
                dad->Nodes[i+1]=dad->Nodes[i];
                dad->childrens[i+2]=dad->childrens[i+1];
                dad->childrens[i+2]->father=dad;
                y--;
            }
        }
        BTreeNode<tmptype,maxdegree>* left=new BTreeNode<tmptype,maxdegree>();
        for(int i=0;i<((maxdegree-1)/2);i++){
            left->Nodes[i]=a->Nodes[i];
            left->Nodes[i]->self=left;
            (left->size)++;
        }
        for(int i=0;i<=(left->size);i++){
            left->childrens[i]=a->childrens[i];
            if(left->childrens[i]!=0){
                left->childrens[i]->father=left;
            }
        }
        BTreeNode<tmptype,maxdegree>* right=new BTreeNode<tmptype,maxdegree>();
        for(int i=((maxdegree+1)/2);i<(a->size);i++){
            right->Nodes[i-((maxdegree+1)/2)]=a->Nodes[i];
            right->Nodes[i-((maxdegree+1)/2)]->self=right;
            (right->size)++;
        }
        for(int i=0;i<=(right->size);i++){
            right->childrens[i]=a->childrens[i+((maxdegree+1)/2)];
            if(right->childrens[i]!=0){
                right->childrens[i]->father=right;
            }
        }
        dad->Nodes[y]=a->Nodes[((maxdegree-1)/2)];
        dad->Nodes[y]->self=dad;
        dad->childrens[y]=left;
        dad->childrens[y+1]=right;
        left->father=dad;
        right->father=dad;
        (dad->size)++;
        if((dad->size)>=maxdegree){
            fixhigh(dad);
        }
    }
}

template <typename tmptype,int maxdegree>
Node<tmptype,maxdegree>* BTree<tmptype,maxdegree>::deleteNode(tmptype a){
    int index=0;
    Node<tmptype,maxdegree>* anode=find(a);
    BTreeNode<tmptype,maxdegree>* aBTnode=anode->self;
    Node<tmptype,maxdegree>* nn=anode->nextField;
    for(int i=0;i<aBTnode->size;i++){
        if(aBTnode->Nodes[i]==anode){
            index=i;
            break;
        }
    }
    if(anode==0){
        return 0;
    }
    else{
        if(aBTnode->childrens[0]!=0){
            Node<tmptype,maxdegree>* pred=findpredecessor(anode);
            BTreeNode<tmptype,maxdegree>* predBt=pred->self;
            aBTnode->Nodes[index]=pred;
            pred->self=aBTnode;
            predBt->Nodes[predBt->size-1]=0;
            predBt->size--;
            if((predBt->size)<((maxdegree-1)/2)){
                fixlow(predBt);
            }
        }
        else{
            for(int i=index;i<(aBTnode->size-1);i++){
                aBTnode->Nodes[i]=aBTnode->Nodes[i+1];
            }
            aBTnode->size--;
            aBTnode->Nodes[aBTnode->size]=0;
            if((aBTnode->size)<((maxdegree-1)/2)){
                fixlow(aBTnode);
            }
        }
    }
    delete anode;
    return nn;
}

template <typename tmptype,int maxdegree>
Node<tmptype,maxdegree>* BTree<tmptype,maxdegree>::deleteNode_by_node(Node<tmptype,maxdegree>* anode){
    int index=0;
    BTreeNode<tmptype,maxdegree>* aBTnode=anode->self;
    Node<tmptype,maxdegree>* nn=anode->nextField;
    for(int i=0;i<aBTnode->size;i++){
        if(aBTnode->Nodes[i]==anode){
            index=i;
            break;
        }
    }
    if(anode==0){
        return 0;
    }
    else{
        if(aBTnode->childrens[0]!=0){
            Node<tmptype,maxdegree>* pred=findpredecessor(anode);
            BTreeNode<tmptype,maxdegree>* predBt=pred->self;
            aBTnode->Nodes[index]=pred;
            pred->self=aBTnode;
            predBt->Nodes[predBt->size-1]=0;
            predBt->size--;
            if((predBt->size)<((maxdegree-1)/2)){
                fixlow(predBt);
            }
        }
        else{
            for(int i=index;i<(aBTnode->size-1);i++){
                aBTnode->Nodes[i]=aBTnode->Nodes[i+1];
            }
            aBTnode->size--;
            aBTnode->Nodes[aBTnode->size]=0;
            if((aBTnode->size)<((maxdegree-1)/2)){
                fixlow(aBTnode);
            }
        }
    }
    delete anode;
    return nn;
}

template <typename tmptype,int maxdegree>
void BTree<tmptype,maxdegree>::fixlow(BTreeNode<tmptype,maxdegree>* a){
    if(root->size==0){
        root=0;
        return;
    }
    BTreeNode<tmptype,maxdegree>* b=a;
    bool t=true;
    if(a!=root){
        int index=0;
        for(int i=0;i<=(a->father->size);i++){
            if(a==a->father->childrens[i]){
                index=i;
                break;
            }
        }
        if(index==0){
            if(a->father->childrens[index+1]->size>=((maxdegree+1)/2)){
                a->Nodes[a->size]=a->father->Nodes[index];
                a->Nodes[a->size]->self=a;
                a->size++;
                a->father->Nodes[index]=a->father->childrens[index+1]->Nodes[0];
                a->father->Nodes[index]->self=a->father;
                for(int i=0;i<((a->father->childrens[index+1]->size)-1);i++){
                    a->father->childrens[index+1]->Nodes[i]=a->father->childrens[index+1]->Nodes[i+1];
                }
                a->father->childrens[index+1]->Nodes[(a->father->childrens[index+1]->size)-1]=0;
                a->childrens[a->size]=a->father->childrens[index+1]->childrens[0];
                if(a->childrens[a->size]!=0){
                    a->childrens[a->size]->father=a;
                }
                for(int i=0;i<=((a->father->childrens[index+1]->size)-1);i++){
                    a->father->childrens[index+1]->childrens[i]=a->father->childrens[index+1]->childrens[i+1];
                }
                a->father->childrens[index+1]->childrens[(a->father->childrens[index+1]->size)]=0;
                a->father->childrens[index+1]->size--;
            }
            else{
                BTreeNode<tmptype,maxdegree>* left=a;
                a=a->father->childrens[index+1];
                left->Nodes[left->size]=a->father->Nodes[index];
                left->Nodes[left->size]->self=left;
                for(int i=0;i<(a->size);i++){
                    left->Nodes[left->size+i+1]=a->Nodes[i];
                    left->Nodes[left->size+i+1]->self=left;
                }
                for(int i=0;i<=(a->size);i++){
                    left->childrens[left->size+i+1]=a->childrens[i];
                    if(left->childrens[left->size+i+1]!=0){
                        left->childrens[left->size+i+1]->father=left;
                    }
                }
                left->size=left->size+a->size+1;
                delete a;
                for(int i=index;i<left->father->size-1;i++){
                    left->father->Nodes[i]=left->father->Nodes[i+1];
                }
                for(int i=index+1;i<=left->father->size-1;i++){
                    left->father->childrens[i]=left->father->childrens[i+1];
                }
                left->father->Nodes[left->father->size-1]=0;
                left->father->childrens[left->father->size]=0;
                left->father->size--;
                if(left->father->size==0 && left->father==root){
                    root=left;
                    root->father=0;
                    t=false;
                }
            }
        }
        else if(index==(a->father->size)){
            if(a->father->childrens[index-1]->size>=((maxdegree+1)/2)){
                for(int i=(a->size-1);i>=0;i--){
                    a->Nodes[i+1]=a->Nodes[i];
                }
                for(int i=(a->size);i>=0;i--){
                    a->childrens[i+1]=a->childrens[i];
                }
                a->Nodes[0]=a->father->Nodes[index-1];
                a->Nodes[0]->self=a;
                a->size++;
                a->father->Nodes[index-1]=a->father->childrens[index-1]->Nodes[a->father->childrens[index-1]->size-1];
                a->father->Nodes[index-1]->self=a->father;
                a->father->childrens[index-1]->Nodes[a->father->childrens[index-1]->size-1]=0;
                a->childrens[0]=a->father->childrens[index-1]->childrens[a->father->childrens[index-1]->size];
                if(a->childrens[0]!=0){
                    a->childrens[0]->father=a;
                }
                a->father->childrens[index-1]->childrens[a->father->childrens[index-1]->size]=0;
                a->father->childrens[index-1]->size--;
            }
            else{
                BTreeNode<tmptype,maxdegree>* left=a->father->childrens[index-1];
                left->Nodes[left->size]=a->father->Nodes[index-1];
                left->Nodes[left->size]->self=left;
                for(int i=0;i<(a->size);i++){
                    left->Nodes[left->size+i+1]=a->Nodes[i];
                    left->Nodes[left->size+i+1]->self=left;
                }
                for(int i=0;i<=(a->size);i++){
                    left->childrens[left->size+i+1]=a->childrens[i];
                    if(left->childrens[left->size+i+1]!=0){
                        left->childrens[left->size+i+1]->father=left;
                    }
                }
                left->size=left->size+a->size+1;
                delete a;
                left->father->Nodes[left->father->size-1]=0;
                left->father->childrens[left->father->size]=0;
                left->father->size--;
                if(left->father->size==0 && left->father==root){
                    root=left;
                    root->father=0;
                    t=false;
                }
            }
        }
        else{
            if(a->father->childrens[index-1]->size>=((maxdegree+1)/2)){
                for(int i=(a->size-1);i>=0;i--){
                    a->Nodes[i+1]=a->Nodes[i];
                }
                for(int i=(a->size);i>=0;i--){
                    a->childrens[i+1]=a->childrens[i];
                }
                a->Nodes[0]=a->father->Nodes[index-1];
                a->Nodes[0]->self=a;
                a->size++;
                a->childrens[0]=a->father->childrens[index-1]->childrens[a->father->childrens[index-1]->size];
                if(a->childrens[0]!=0){
                    a->childrens[0]->father=a;
                }
                a->father->Nodes[index-1]=a->father->childrens[index-1]->Nodes[a->father->childrens[index-1]->size-1];
                a->father->Nodes[index-1]->self=a->father;
                a->father->childrens[index-1]->childrens[a->father->childrens[index-1]->size]=0;
                a->father->childrens[index-1]->Nodes[a->father->childrens[index-1]->size-1]=0;
                a->father->childrens[index-1]->size--;
            }
            else if(a->father->childrens[index+1]->size>=((maxdegree+1)/2)){
                a->Nodes[a->size]=a->father->Nodes[index];
                a->Nodes[a->size]->self=a;
                a->size++;
                a->childrens[a->size]=a->father->childrens[index+1]->childrens[0];
                if(a->childrens[a->size]!=0){
                    a->childrens[a->size]->father=a;
                }
                a->father->Nodes[index]=a->father->childrens[index+1]->Nodes[0];
                a->father->Nodes[index]->self=a->father;
                for(int i=0;i<((a->father->childrens[index+1]->size)-1);i++){
                    a->father->childrens[index+1]->Nodes[i]=a->father->childrens[index+1]->Nodes[i+1];
                }
                for(int i=0;i<=((a->father->childrens[index+1]->size)-1);i++){
                    a->father->childrens[index+1]->childrens[i]=a->father->childrens[index+1]->childrens[i+1];
                }
                a->father->childrens[index+1]->Nodes[a->father->childrens[index+1]->size-1]=0;
                a->father->childrens[index+1]->childrens[a->father->childrens[index+1]->size]=0;
                a->father->childrens[index+1]->size--;
            }
            else{
                BTreeNode<tmptype,maxdegree>* left=a->father->childrens[index-1];
                left->Nodes[left->size]=a->father->Nodes[index-1];
                left->Nodes[left->size]->self=left;
                for(int i=0;i<(a->size);i++){
                    left->Nodes[left->size+i+1]=a->Nodes[i];
                    left->Nodes[left->size+i+1]->self=left;
                }
                for(int i=0;i<=(a->size);i++){
                    left->childrens[left->size+i+1]=a->childrens[i];
                    if(left->childrens[left->size+i+1]!=0){
                        left->childrens[left->size+i+1]->father=left;
                    }
                }
                left->size=left->size+a->size+1;
                delete a;
                for(int i=index;i<(left->father->size);i++){
                    left->father->Nodes[i-1]=left->father->Nodes[i];
                }
                for(int i=index+1;i<=(left->father->size);i++){
                    left->father->childrens[i-1]=left->father->childrens[i];
                }
                left->father->Nodes[left->father->size-1]=0;
                left->father->childrens[left->father->size]=0;
                left->father->size--;
                if(left->father->size==0 && left->father==root){
                    root=left;
                    root->father=0;
                    t=false;
                }
            }
        }
    }
    if(t && (b->father!=0) && ((b->father->size)<((maxdegree-1)/2))){
        fixlow(b->father);
    }
}

template <typename tmptype,int maxdegree>
Node<tmptype,maxdegree>* BTree<tmptype,maxdegree>::updateNodeint(tmptype oldone,tmptype newone){
    int index;
    Node<tmptype,maxdegree>* oldnodenext=deleteNode(oldone);
    Node<tmptype,maxdegree>* newnode=insertNode(newone);
    newnode->nextField=oldnodenext;
    return newnode;
}

template <typename tmptype,int maxdegree>
Node<tmptype,maxdegree>* BTree<tmptype,maxdegree>::updateNodeNode(Node<tmptype,maxdegree>* oldone,tmptype newone){
    Node<tmptype,maxdegree>* oldnodenext=deleteNode_by_node(oldone);
    Node<tmptype,maxdegree>* newnode=insertNode(newone);
    newnode->nextField=oldnodenext;
    return newnode;
}


/*template <typename tmptype,int maxdegree>
void BTree<tmptype,maxdegree>::display(){
    BTreeNode<tmptype,maxdegree>* tmp=root;
    if(!isEmpty()){
        for(int i=0;i<(tmp->size);i++){
                cout<<tmp->Nodes[i]->data<<" , ";
            }
        cout<<endl;
        cout<<"tmp->Size: "<<tmp->size<<endl;
        if(root->childrens[0]!=0){
            for(int j=0;j<=(tmp->size);j++){
                cout<<"j: "<<j<<" tmp->childrens[j]->size: "<<tmp->childrens[j]->size<<endl;
                for(int i=0;i<(tmp->childrens[j]->size);i++){
                    cout<<tmp->childrens[j]->Nodes[i]->data<<" , ";
                }
                cout<<endl;
            }
        }
        for(int j=0;j<=(tmp->size);j++){
            for(int i=0;i<=(tmp->childrens[j]->size);i++){
                cout<<"j: "<<j<<" tmp->childrens[j]->childrens[i]->size: "<<tmp->childrens[j]->childrens[i]->size<<endl;
                for(int k=0;k<(tmp->childrens[j]->childrens[i]->size);k++){
                    cout<<tmp->childrens[j]->childrens[i]->Nodes[k]->data<<"  ,  ";
                }
                cout<<endl;
            }
        }
    }
    else{
        cout<<"khali\n";
    }
}*/

template <typename tmptype,int maxdegree>
vector<Node<tmptype,maxdegree>*> BTree<tmptype,maxdegree>::itaratormin(tmptype a,string compare){
    vector<Node<tmptype,maxdegree>*> output;
    iterate=true;
    itaratorminhelper(a,root,compare,output);
    return output;
}

template <typename tmptype,int maxdegree>
void BTree<tmptype,maxdegree>::itaratorminhelper(tmptype a,BTreeNode<tmptype,maxdegree>* tmp,string compare,vector<Node<tmptype,maxdegree>*>& output){
    if(tmp==0){
        return;
    }
    else{
        for(int i=0;i<tmp->size;i++){
            if(iterate){
                itaratorminhelper(a,tmp->childrens[i],compare,output);
            }
            tmptype da=tmp->Nodes[i]->data;
            if(compare=="=="){
                if(da==a){
                    output.push_back(tmp->Nodes[i]);
                }
                else if(da>a){
                    iterate=false;
                    break;
                }
            }
            else if(compare=="<"){
                if(da<a){
                    output.push_back(tmp->Nodes[i]);
                }
                else if(da>=a){
                    iterate=false;
                    break;
                }
            }
        }
        if(iterate){
                itaratorminhelper(a,tmp->childrens[tmp->size],compare,output);
        }
    }
}

template <typename tmptype,int maxdegree>
vector<Node<tmptype,maxdegree>*> BTree<tmptype,maxdegree>::itaratormax(tmptype a,string compare){
    vector<Node<tmptype,maxdegree>*> output;
    iterate=true;
    itaratormaxhelper(a,root,compare,output);
    return output;
}

template <typename tmptype,int maxdegree>
void BTree<tmptype,maxdegree>::itaratormaxhelper(tmptype a,BTreeNode<tmptype,maxdegree>* tmp,string compare,vector<Node<tmptype,maxdegree>*>& output){
    if(tmp==0){
        return;
    }
    else{
        if(iterate){
            itaratormaxhelper(a,tmp->childrens[tmp->size],compare,output);
        }
        for(int i=tmp->size-1;i>=0;i--){
            tmptype da=tmp->Nodes[i]->data;
            if(compare==">"){
                if(da>a){
                    output.push_back(tmp->Nodes[i]);
                }
                else if(da<=a){
                    iterate=false;
                    break;
                }
            }
            if(iterate){
                itaratormaxhelper(a,tmp->childrens[i],compare,output);
            }
        }
    }
}

//end BTree