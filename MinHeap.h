#ifndef MINHEAP_H
#define MINHEAP_H

class MinHeap{
    public:
        MinHeap();
        MinHeap(int);
        void insert(int);
        int deletemin();
        int getsize();
    private:
        void Heapify(int);
        int father(int);
        int leftchild(int);
        int rightchild(int);
        void swap(int,int);
        int* minnheap;
        int size;
        int last;
};

#endif