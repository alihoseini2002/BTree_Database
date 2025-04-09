#include <iostream>
#include <MinHeap.h>
using namespace std;

//start MinHeap
MinHeap::MinHeap(){
    last=0;
}

MinHeap::MinHeap(int a){
    minnheap=new int[a];
    last=0;
    size=a;
}

void MinHeap::insert(int k){
    minnheap[last]=k;
    int index=last;
    last++;
    while(index>0 && minnheap[father(index)]>minnheap[index]){
        swap(index,father(index));
        index=father(index);
    }
    return;
}

int MinHeap::deletemin(){
    if(last==0){return 0;}
    int s=minnheap[0];
    swap(last-1,0);
    last--;
    Heapify(0);
    return s;
}

int MinHeap::getsize(){
    return last;
}

void MinHeap::Heapify(int index){
    int smallchild=index;
    int l=leftchild(index);
    int r=rightchild(index);
    if(l<last && minnheap[l]<minnheap[smallchild]){
        smallchild=l;
    }
    if(r<last && minnheap[r]<minnheap[smallchild]){
        smallchild=r;
    }
    if(smallchild!=index){
        swap(index,smallchild);
        Heapify(smallchild);
    }
}

int MinHeap::father(int index){
    return (index-1)/2;
}

int MinHeap::leftchild(int index){
    return 2*index+1;
}

int MinHeap::rightchild(int index){
    return 2*index+2;
}

void MinHeap::swap(int i,int j){
    int tmp=minnheap[i];
    minnheap[i]=minnheap[j];
    minnheap[j]=tmp;
}

//end MinHeap