#include <iostream>
#include <BTree.h>
#include <AvlTree.h>
#include <MinHeap.h>
#include <functions.h>
using namespace std;

int main()
{
    const int maxdegree=3;
    AvlTree<string,maxdegree> tables;
    int n,size=0,m,querysize,ss;
    cin>>n;
    m=n;
    cin.ignore();
    string input="",check="";
    string* query;
    while(n)
    {
        getline(cin,input);
        query=input_to_query(input,size,querysize);
        if(query[0]=="CREATE"){
            check=Create_table(tables,query,size,querysize,m);
            if(check[0]!='T'){
                cout<<check.substr(1,(check.length()-1));
            }
        }
        else if(query[0]=="INSERT"){
            check=Insert_in_table(tables,query,querysize);
            if(check[0]!='T'){
                cout<<check.substr(1,(check.length()-1));
            }
        }
        else if(query[0]=="DELETE"){
            check=Delete_from_table(tables,query,querysize);
            if(check[0]!='T'){
                cout<<check.substr(1,(check.length()-1));
            }
        }
        else if(query[0]=="UPDATE"){
            check=Update_table(tables,query,querysize);
            if(check[0]!='T'){
                cout<<check.substr(1,(check.length()-1));
            }
        }
        else if(query[0]=="SELECT"){
            check=Select_table(tables,query,querysize);
            if(check[0]!='T'){
                cout<<check.substr(1,(check.length()-1));
            }
        }
        else{
            cout<<"wrong input:( \n try again:";
            n++;
        }
        n--;
    }
}