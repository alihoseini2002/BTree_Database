#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <BTree.h>
#include <AvlTree.h>
#include <MinHeap.h>
#include <functions.h>

bool check_time(string &,Times&);
bool check_int(string &);
long long str_to_int(string &);
long long hash_str_to_int(string);
string unhash_int_to_str(long long);
string* input_to_query(string &,int&,int&);
string recog_condition(string &);

template <typename tmptype,int maxdegree>
string Create_table(AvlTree<tmptype,maxdegree>&,string*,int,int,int);

template <typename tmptype,int maxdegree>
string Insert_in_table(AvlTree<tmptype,maxdegree>&,string*,int);

template <typename tmptype,int maxdegree>
string Delete_from_table(AvlTree<tmptype,maxdegree>&,string*,int);

template <typename tmptype,int maxdegree>
string Update_table(AvlTree<tmptype,maxdegree>&,string*,int);

template <typename tmptype,int maxdegree>
string Select_table(AvlTree<tmptype,maxdegree>&,string*,int);

template <typename tmptype,int maxdegree>
string Delete_one_condition(AvlTree<tmptype,maxdegree>&,string*,int,string,string,string);

//template <typename tmptype,int maxdegree>
//string Delete_two_condition(AvlTree<tmptype,maxdegree>&,string*,MinHeap&,int,string,string,string,string,string,string,int&);

template <typename tmptype,int maxdegree>
vector<Node<long long,maxdegree>*> find_same(vector<Node<long long,maxdegree>*>,vector<Node<long long,maxdegree>*>);

template <typename tmptype,int maxdegree>
int binary_search(vector<Node<long long,maxdegree>*>,int);

#endif