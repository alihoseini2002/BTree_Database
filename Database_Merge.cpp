#include <iostream>
#include <vector>
using namespace std;

class Times{
    public:
        Times(){
            year=0;
            month=0;
            day=0;
        }
        void insert(int a,int b,int c){
            if(a>0){
                year=a;
                if(year>0){
                    if(year%4==0){
                        if(year%100==0){
                            if(year%400==0){
                                mahha[1]=29;
                            }
                        }
                        else{
                            mahha[1]=29;
                        }
                    }
                }
            }
            if(b>0 && b<=12){
                month=b;
            }
            if(c>0 && c<=mahha[month-1]){
                day=c;
            }
        }
        void unhash(int x){
            day=x%100;
            x/=100;
            month=x%100;
            x/=100;
            year=x;
        }
        int hash(){
            return ((year*10000)+(month*100)+(day));
        }
        void display(){
            cout<<year<<"/"<<month<<"/"<<day;
        }
        int year;
        int day;
        int month;
    private:
        int mahha[12]={31,28,31,30,31,30,31,31,30,31,30,31};
};

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

template <typename tmptype,int maxdegree>
string Delete_two_condition(AvlTree<tmptype,maxdegree>&,string*,int,string,string,string,string,string,string);

template <typename tmptype,int maxdegree>
vector<Node<long long,maxdegree>*> find_same(vector<Node<long long,maxdegree>*>,vector<Node<long long,maxdegree>*>);

template <typename tmptype,int maxdegree>
int binary_search(vector<Node<long long,maxdegree>*>,int);

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

bool check_time(string &a,Times & zaman){
    string tmp="";
    int year,month,day;
    if(a.length()<8 || a.length()>10){
        return false;
    }
    for(int i=0;i<4;i++){
        if(a[i]>=48 && a[i]<=57){
            tmp+=a[i];
        }
        else{
            return false;
        }
    }
    year=str_to_int(tmp);
    tmp="";
    if(a[4]!='/'){
        return false;
    }
    if(a[6]=='/'){
        if(a[5]>=48 && a[5]<=57){
            tmp+=a[5];
        }
        else{
            return false;
        }
        month=str_to_int(tmp);
        tmp="";
        for(int i=7;i<a.length();i++){
            if(a[i]>=48 && a[i]<=57){
                tmp+=a[i];
            }
            else{
                return false;
            }
        }
        day=str_to_int(tmp);
    }
    else if(a[7]=='/'){
        for(int i=5;i<7;i++){
            if(a[i]>=48 && a[i]<=57){
                tmp+=a[i];
            }
            else{
                return false;
            }
        }
        month=str_to_int(tmp);
        tmp="";
        for(int i=8;i<a.length();i++){
            if(a[i]>=48 && a[i]<=57){
                tmp+=a[i];
            }
            else{
                return false;
            }
        }
        day=str_to_int(tmp);
    }
    else{
        return false;
    }
    zaman.insert(year,month,day);
    if((zaman.year==0) || (zaman.month==0) || (zaman.day==0)){
        return false;
    }
    return true;
}

bool check_int(string & a){
    for(int i=0;i<a.length();i++){
        if(a[i]<48 || a[i]>57){
            return false;
        }
    }
    return true;
}

long long str_to_int(string &a){
    long long x=0;
    for(int i=0;i<a.length();i++){
        x*=10;
        x+=((int)a[i])-48;
    }
    return x;
}

string* input_to_query(string &a,int& size,int& querysize){
    int x=1,y=1,index=0;
    for(int i=0;i<a.length()-1;i++){
        if((a[i]==' ' || a[i]==',') && (a[i+1]!=' ' && a[i+1]!=',')){
            x++;
        }
        if(a[i]==','){y++;}
    }
    string* query=new string[x];
    querysize=x;
    size=y;
    string tmp="";
    for(int i=0;i<a.length();i++){
        if(a[i]!=' ' && a[i]!=',' && a[i]!='(' && a[i]!=')'){
            tmp+=a[i];
        }
        else if((a[i]==',' || a[i]==' ') & tmp!=""){
            query[index]=tmp;
            tmp="";
            index++;
        }
    }
    if(tmp!=""){
        query[index]=tmp;
        index++;
    }
    int c=-1,p=-1;
    for(int i=0;i<querysize;i++){
        if(query[i]=="WHERE"){
            c=i;
        }
        else if(query[i][0]=='|' || query[i][0]=='&'){
            p=i;
            break;
        }
    }
    if(c!=-1){
        if(p!=-1){
            if(querysize-c==4){
                return query;
            }
            else{
                string tmp1="",tmp2="";
                for(int i=c+1;i<p;i++){
                    tmp1+=query[i];
                }
                for(int i=p+1;i<querysize;i++){
                    tmp2+=query[i];
                }
                string * qq=new string [c+4];
                for(int i=0;i<=c;i++){
                    qq[i]=query[i];
                }
                qq[c+1]=tmp1;
                qq[c+2]=query[p];
                qq[c+3]=tmp2;
                querysize=c+4;
                return qq;
            }
        }
        else{
            if(querysize-c==2){
                return query;
            }
            else{
                string tmp="";
                for(int i=c+1;i<querysize;i++){
                    tmp+=query[i];
                }
                string * qq=new string [c+2];
                for(int i=0;i<=c;i++){
                    qq[i]=query[i];
                }
                qq[c+1]=tmp;
                querysize=c+2;
                return qq;
            }
        }
    }
    return query;
}

string recog_condition(string &a,string& c1,string& c2){
    string tmp="";
    int index=0;
    while(true){
        if((a[index]=='=') || (a[index]=='<') || (a[index]=='>') || (a[index]==' ')){
            break;
        }
        else{
            tmp+=a[index];
        }
        index++;
    }
    c1=tmp;
    tmp="";
    while(true){
        if((a[index]=='=') || (a[index]=='<') || (a[index]=='>')){
            tmp+=a[index];
        }
        else{
            break;
        }
        index++;
    }
    while(a[index]==' '){
        index++;
    }
    c2=a.substr(index,(a.length()-index));
    return tmp;
}

long long hash_str_to_int(string a){
    long long x=0,adad;
    for(int i=0;i<a.length();i++){
        if((a[i]>=97) && (a[i]<=122)){
            adad=(((int)a[i])-96);
        }
        else if((a[i]>=48) && (a[i]<=57)){
            adad=((int)a[i])-21;
        }
        x=(x*37)+adad;
    }
    return x;
}

string unhash_int_to_str(long long a){
    string tmp="";
    char c;
    while(a!=0){
        c=a%37;
        if(c<27){
            c+=96;
        }
        else{
            c+=21;
        }
        tmp=c+tmp;
        a/=37;
    }
    return tmp;
}

template <typename tmptype,int maxdegree>
string Create_table(AvlTree<tmptype,maxdegree>& tables,string* query,int size,int querysize,int n){
    string * col=new string [size+1];
    MinHeap *get_id=new MinHeap(n);
    get_id->insert(1);
    string * coltype=new string [size+1];
    string data=query[2];
    col[0]="id";
    coltype[0]="int";
    int index=1;
    for(int i=3;i<querysize;i+=2){
        col[index]=query[i];
        index++;
    }
    index=1;
    for(int i=4;i<querysize;i+=2){
        coltype[index]=query[i];
        index++;
    }
    size++;
    BTree<long long,maxdegree>* one_table=new BTree<long long,maxdegree> [size];
    tables.insertnode(data,size,col,coltype,one_table,get_id);
    return "T";
}

template <typename tmptype,int maxdegree>
string Insert_in_table(AvlTree<tmptype,maxdegree>& tables,string* query,int querysize){
    MinHeap* get_id;
    string tablename=query[2];
    string* col;
    string check="T";
    string* coltype;
    int size;
    BTree<long long,maxdegree>* this_table=tables.find(tablename,size,col,coltype,get_id);    
    if(this_table==0){
        check="Fthere is no table with this name or wrong syntax!\n";
        return check;
    }
    if(querysize-3!=size){
        check="Fthere isn't enough input for inserting!\n";
        return check;
    }
    int index=4;
    for(int i=1;i<size;i++){
        if(coltype[i]=="string"){
            if((query[index][0]!='\"') || (query[index][query[index].length()-1]!='\"')){
                check="Fyou're input should be string! like \"ali\" \n";
                return check;
            }
        }
        else if(coltype[i]=="int"){
            if(!check_int(query[index])){
                check="Fyou're input should be integer!\n";
                return check;
            }
        }
        else if(coltype[i]=="timestamp"){
            Times tt;
            if(!check_time(query[index],tt)){
                check="Fyou're input should be timestamp of youre input is not valid!\n";
                return check;
            }
        }
        index++;
    }
    int id=get_id->deletemin();
    if(get_id->getsize()==0){
        get_id->insert(id+1);
    }
    Node<long long,maxdegree>* tmp=this_table[0].insertNode(id);
    Node<long long,maxdegree>* tmp2;
    Node<long long,maxdegree>* first=tmp;
    index=4;
    for(int i=1;i<size;i++){
        if(coltype[i]=="string"){
            long long x=hash_str_to_int(query[index].substr(1,(query[index].length()-2)));
            tmp2=this_table[i].insertNode(x);
        }
        else if(coltype[i]=="int"){
            long long x=str_to_int(query[index]);
            tmp2=this_table[i].insertNode(x);
        }
        else if(coltype[i]=="timestamp"){
            Times zaman;
            check_time(query[index],zaman);
            long long x=zaman.hash();
            tmp2=this_table[i].insertNode(x);
        }
        index++;
        tmp->nextField=tmp2;
        tmp=tmp2;
    }
    tmp->nextField=first;
    return check;
}

template <typename tmptype,int maxdegree>
string Delete_from_table(AvlTree<tmptype,maxdegree>& tables,string* query,int querysize){
    MinHeap *get_id;
    string tablename=query[2];
    string* col;
    string check="T";
    string* coltype;
    int size;
    BTree<long long,maxdegree>* this_table=tables.find(tablename,size,col,coltype,get_id);
    if(this_table==0){
        check="Fthere is no table with this name or wrong syntax!\n";
        return check;
    }
    if(querysize==5){
        string c1,c2,tmp;
        tmp=recog_condition(query[4],c1,c2);
        check=Delete_one_condition(tables,query,querysize,c1,tmp,c2);
    }
    else if(querysize==7){
        char x;
        string c1_1,c1_2,c2_1,c2_2,tmp1,tmp2;
        x=query[5][0];
        tmp1=recog_condition(query[4],c1_1,c1_2);
        tmp2=recog_condition(query[6],c2_1,c2_2);
        if(x=='&'){
            check=Delete_two_condition(tables,query,querysize,c1_1,tmp1,c1_2,c2_1,tmp2,c2_2);
        }
        else if(x=='|'){
            check=Delete_one_condition(tables,query,querysize,c1_1,tmp1,c1_2);
            if(check[0]!='T'){
                return check;
            }
            check=Delete_one_condition(tables,query,querysize,c2_1,tmp2,c2_2);
        }
        else{
            check="FWrong syntax\n";
            return check;
        }
    }
    else{
        check="FWrong syntax\n";
        return check;
    }
    return check;
}

template <typename tmptype,int maxdegree>
string Delete_one_condition(AvlTree<tmptype,maxdegree>& tables,string* query,int querysize,string left,string compare,string right){
    MinHeap *get_id;
    string tablename=query[2];
    string* col;
    string check="T";
    string* coltype;
    int size;
    BTree<long long,maxdegree>* this_table=tables.find(tablename,size,col,coltype,get_id);
    if(this_table==0){
        check="Fthere is no table with this name or wrong syntax!\n";
        return check;
    }
    int index=0;
    long long moghayese;
    for(int i=0;i<size;i++){
        if(col[i]==left){
            index=i;
            break;
        }
    }
    if(coltype[index]=="int"){
        if(check_int(right)){
            moghayese=str_to_int(right);
        }
        else{
            check="Fshould be integer\n";
            return check;
        }
    }
    else if(coltype[index]=="timestamp"){
        Times zaman;
        if(check_time(right,zaman)){
            moghayese=zaman.hash();
        }
        else{
            check="Fshould be time and valid\n";
            return check;
        }
    }
    else if(coltype[index]=="string"){
        moghayese=hash_str_to_int(right.substr(1,(right.length()-2)));
    }
    Node<long long,maxdegree>* tmp;
    Node<long long,maxdegree>* tmp2;
    if((compare=="==") || (compare=="<")){
        vector<Node<long long,maxdegree>*> output=this_table[index].itaratormin(moghayese,compare);
        for(int i=0;i<output.size();i++){
            tmp=output[i];
            tmp2=this_table[index].deleteNode_by_node(tmp);
            tmp=tmp2;
            if(((index+1)%size) == 0){
                int id=tmp2->data;
                get_id->insert(id);
            }
            for(int j=1;j<size;j++){
                tmp2=this_table[(index+j)%size].deleteNode_by_node(tmp);
                tmp=tmp2;
                if((j!=size-1) && ((index+j+1)%size) == 0){
                    int id=tmp2->data;
                    get_id->insert(id);
                }
            }
        }
    }
    else if(compare==">"){
        vector<Node<long long,maxdegree>*> output=this_table[index].itaratormax(moghayese,compare);
        for(int i=0;i<output.size();i++){
            tmp=output[i];
            tmp2=this_table[index].deleteNode_by_node(tmp);
            tmp=tmp2;
            if(((index+1)%size) == 0){
                int id=tmp2->data;
                get_id->insert(id);
            }
            for(int j=1;j<size;j++){
                tmp2=this_table[(index+j)%size].deleteNode_by_node(tmp);
                tmp=tmp2;
                if((j!=size-1) && ((index+j+1)%size) == 0){
                    int id=tmp2->data;
                    get_id->insert(id);
                }
            }
        }
    }
    else{
        check="Fwrong syntax(just use < or > or ==)\n";
        return check;
    }
    return check;
}

template <typename tmptype,int maxdegree>
string Delete_two_condition(AvlTree<tmptype,maxdegree>& tables,string* query,int querysize,string left1,string comp1,string right1,string left2,string comp2,string right2){
    MinHeap *get_id;
    string tablename=query[2];
    string* col;
    string check="T";
    string* coltype;
    int size;
    BTree<long long,maxdegree>* this_table=tables.find(tablename,size,col,coltype,get_id);
    if(this_table==0){
        check="Fthere is no table with this name or wrong syntax!\n";
        return check;
    }
    int index1=0,index2=0,moghayese1,moghayese2;
    for(int i=0;i<size;i++){
        if(col[i]==left1){
            index1=i;
            break;
        }
    }
    for(int i=0;i<size;i++){
        if(col[i]==left2){
            index2=i;
            break;
        }
    }
    if(coltype[index1]=="int"){
        if(check_int(right1)){
            moghayese1=str_to_int(right1);
        }
        else{
            check="Fshould be integer\n";
            return check;
        }
    }
    else if(coltype[index1]=="timestamp"){
        Times zaman;
        if(check_time(right1,zaman)){
            moghayese1=zaman.hash();
        }
        else{
            check="Fshould be time and valid\n";
            return check;
        }
    }
    else if(coltype[index1]=="string"){
        moghayese1=hash_str_to_int(right1.substr(1,(right1.length()-2)));
    }
    if(coltype[index2]=="int"){
        if(check_int(right2)){
            moghayese2=str_to_int(right2);
        }
        else{
            check="Fshould be integer\n";
            return check;
        }
    }
    else if(coltype[index2]=="timestamp"){
        Times zaman;
        if(check_time(right2,zaman)){
            moghayese2=zaman.hash();
        }
        else{
            check="Fshould be time and valid\n";
            return check;
        }
    }
    else if(coltype[index2]=="string"){
        moghayese2=hash_str_to_int(right2.substr(1,(right2.length()-2)));
    }
    vector<Node<long long,maxdegree>*> output1;
    vector<Node<long long,maxdegree>*> output2;
    if((comp1=="==") || (comp1=="<")){
        output1=this_table[index1].itaratormin(moghayese1,comp1);
    }
    else{
        output1=this_table[index1].itaratormax(moghayese1,comp1);
    }
    if((comp2=="==") || (comp2=="<")){
        output2=this_table[index2].itaratormin(moghayese2,comp2);
    }
    else{
        output2=this_table[index2].itaratormax(moghayese2,comp2);
    }
    if(index1!=index2){
        vector<Node<long long,maxdegree>*> output;
        Node<long long,maxdegree>* tmp;
        int tasavi=(size+(index2-index1))%size;
        for(int i=0;i<output1.size();i++){
            tmp=output1[i];
            for(int j=0;j<tasavi;j++){
                tmp=tmp->nextField;
            }
            output.push_back(tmp);
        }
        output1=output;
        index2=index1;
    }
    Node<long long,maxdegree>* tmp;
    Node<long long,maxdegree>* tmp2;
    vector<Node<long long,maxdegree>*> final=find_same(output2,output1);
    for(int i=0;i<final.size();i++){
            tmp=final[i];
            tmp2=this_table[index2].deleteNode_by_node(tmp);
            tmp=tmp2;
            if(((index2+1)%size) == 0){
                int id=tmp2->data;
                get_id->insert(id);
            }
            for(int j=1;j<size;j++){
                tmp2=this_table[(index2+j)%size].deleteNode_by_node(tmp);
                tmp=tmp2;
                if((j!=size-1) && ((index2+j+1)%size) == 0){
                    int id=tmp2->data;
                    get_id->insert(id);
                }
            }
        }
    return check;
}

template <typename tmptype,int maxdegree>
string Update_table(AvlTree<tmptype,maxdegree>& tables,string* query,int querysize){
    MinHeap *get_id;
    string tablename=query[1];
    string* col;
    string check="T";
    string* coltype;
    int size;
    BTree<long long,maxdegree>* this_table=tables.find(tablename,size,col,coltype,get_id);
    if(this_table==0){
        check="Fthere is no table with this name or wrong syntax!\n";
        return check;
    }
    int x=1;
    for(int i=0;i<querysize;i++){
        if((query[i]=="&") || (query[i]=="|")){
            x+=2;
            break;
        }
    }
    if(x==1){
        string left,right,compare;
        compare=recog_condition(query[querysize-1],left,right);
        int index=0,moghayese;
        for(int i=0;i<size;i++){
            if(col[i]==left){
                index=i;
                break;
            }
        }
        if(coltype[index]=="int"){
            if(check_int(right)){
                moghayese=str_to_int(right);
            }
            else{
                check="Fshould be integer\n";
                return check;
            }
        }
        else if(coltype[index]=="timestamp"){
            Times zaman;
            if(check_time(right,zaman)){
                moghayese=zaman.hash();
            }
            else{
                check="Fshould be time and valid\n";
                return check;
            }
        }
        else if(coltype[index]=="string"){
            moghayese=hash_str_to_int(right.substr(1,(right.length()-2)));
        }
        vector<Node<long long,maxdegree>*> output;
        if((compare=="==") || (compare=="<")){
            output=this_table[index].itaratormin(moghayese,compare);
        }
        else if(compare==">"){
            output=this_table[index].itaratormax(moghayese,compare);
        }
        Node<long long,maxdegree>* tmp;
        Node<long long,maxdegree>* tmp2;
        Node<long long,maxdegree>* tmp3;
        int idcol=(size-index)%size;
        vector<Node<long long,maxdegree>*> output1;
        for(int j=0;j<output.size();j++){
            tmp=output[j];
            for(int i=0;i<(idcol);i++){
                tmp=tmp->nextField;
            }
            output1.push_back(tmp);
        }
        long long x;
        output=output1;
        for(int i=0;i<output.size();i++){
            tmp=output[i];
            tmp2=tmp->nextField;
            for(int j=1;j<size;j++){
                if(coltype[j]=="string"){
                    x=hash_str_to_int(query[j+2].substr(1,(query[j+2].length()-2)));
                }
                else if(coltype[j]=="int"){
                    x=str_to_int(query[j+2]);
                }
                else if(coltype[j]=="timestamp"){
                    Times zaman;
                    check_time(query[j+2],zaman);
                    x=zaman.hash();
                }
                tmp3=this_table[j].updateNodeNode(tmp2,x);
                tmp->nextField=tmp3;
                tmp2=tmp3->nextField;
                tmp=tmp->nextField;
            }
        }
    }
    else if(x==3){
        string comp1,comp2,left1,left2,right1,right2;
        comp1=recog_condition(query[querysize-3],left1,right1);
        comp2=recog_condition(query[querysize-1],left2,right2);
        int index1=0,index2=0,moghayese1,moghayese2;
        for(int i=0;i<size;i++){
            if(col[i]==left1){
                index1=i;
                break;
            }
        }
        for(int i=0;i<size;i++){
            if(col[i]==left2){
                index2=i;
                break;
            }
        }
        if(coltype[index1]=="int"){
            if(check_int(right1)){
                moghayese1=str_to_int(right1);
            }
            else{
                check="Fshould be integer\n";
                return check;
            }
        }
        else if(coltype[index1]=="timestamp"){
            Times zaman;
            if(check_time(right1,zaman)){
                moghayese1=zaman.hash();
            }
            else{
                check="Fshould be time and valid\n";
                return check;
            }
        }
        else if(coltype[index1]=="string"){
            moghayese1=hash_str_to_int(right1.substr(1,(right1.length()-2)));
        }
        if(coltype[index2]=="int"){
            if(check_int(right2)){
                moghayese2=str_to_int(right2);
            }
            else{
                check="Fshould be integer\n";
                return check;
            }
        }
        else if(coltype[index2]=="timestamp"){
            Times zaman;
            if(check_time(right2,zaman)){
                moghayese2=zaman.hash();
            }
            else{
                check="Fshould be time and valid\n";
                return check;
            }
        }
        else if(coltype[index2]=="string"){
            moghayese2=hash_str_to_int(right2.substr(1,(right2.length()-2)));
        }
        vector<Node<long long,maxdegree>*> output1;
        vector<Node<long long,maxdegree>*> output2;
        if((comp1=="==") || (comp1=="<")){
            output1=this_table[index1].itaratormin(moghayese1,comp1);
        }
        else{
            output1=this_table[index1].itaratormax(moghayese1,comp1);
        }
        if((comp2=="==") || (comp2=="<")){
            output2=this_table[index2].itaratormin(moghayese2,comp2);
        }
        else{
            output2=this_table[index2].itaratormax(moghayese2,comp2);
        }
        if(index1!=index2){
            vector<Node<long long,maxdegree>*> output;
            Node<long long,maxdegree>* tmp;
            int tasavi=(size+(index2-index1))%size;
            for(int i=0;i<output1.size();i++){
                tmp=output1[i];
                for(int j=0;j<tasavi;j++){
                    tmp=tmp->nextField;
                }
                output.push_back(tmp);
            }
            output1=output;
            index1=index2;
        }
        vector<Node<long long,maxdegree>*> final;
        Node<long long,maxdegree>* tmp;
        if(query[querysize-2][0]=='|'){
            for(int i=0;i<output1.size();i++){
                tmp=output1[i];
                final.push_back(tmp);
            }
            for(int i=0;i<output2.size();i++){
                tmp=output2[i];
                final.push_back(tmp);
            }
        }
        else if(query[querysize-2][0]=='&'){
            final=find_same(output2,output1);
        }
        Node<long long,maxdegree>* tmp2;
        Node<long long,maxdegree>* tmp3;
        int idcol=(size-index2)%size;
        vector<Node<long long,maxdegree>*> output3;
        for(int j=0;j<final.size();j++){
            tmp=final[j];
            for(int i=0;i<(idcol);i++){
                tmp=tmp->nextField;
            }
            output3.push_back(tmp);
        }
        long long x;
        final=output3;
        for(int i=0;i<final.size();i++){
            tmp=final[i];
            tmp2=tmp->nextField;
            for(int j=1;j<size;j++){
                if(coltype[j]=="string"){
                    x=hash_str_to_int(query[j+2].substr(1,(query[j+2].length()-2)));
                }
                else if(coltype[j]=="int"){
                    x=str_to_int(query[j+2]);
                }
                else if(coltype[j]=="timestamp"){
                    Times zaman;
                    check_time(query[j+2],zaman);
                    x=zaman.hash();
                }
                tmp3=this_table[j].updateNodeNode(tmp2,x);
                tmp->nextField=tmp3;
                tmp2=tmp3->nextField;
                tmp=tmp->nextField;
            }
        }
    }
    return check;
}

template <int maxdegree>
vector<Node<long long,maxdegree>*> find_same(vector<Node<long long,maxdegree>*> sorted,vector<Node<long long,maxdegree>*> unsorted){
    vector<Node<long long,maxdegree>*> finally;
    for(int i=0;i<unsorted.size();i++){
        int k=binary_search(sorted,unsorted[i]->data);
        if(k!=-1){
            finally.push_back(unsorted[i]);
        }
    }
    return finally;
}

template <int maxdegree>
int binary_search(vector<Node<long long,maxdegree>*> sorted,int tmp){
    int k=-1;
    int first=0,mid;
    int last=sorted.size();
    while(last>=first){
        mid=(first+last)/2;
        if((sorted[mid]->data)==tmp){
            k=mid;
            break;
        }
        else if((sorted[mid]->data)>tmp){
            first=mid+1;
        }
        else if((sorted[mid]->data)<tmp){
            last=mid-1;
        }
    }
    return k;
}

template <typename tmptype,int maxdegree>
string Select_table(AvlTree<tmptype,maxdegree>& tables,string* query,int querysize){
    int name,condition;
    for(int i=0;i<querysize;i++){
        if(query[i]=="FROM"){
            name=i+1;
        }
        else if(query[i]=="WHERE"){
            condition=i+1;
            break;
        }
    }
    MinHeap *get_id;
    string tablename=query[name];
    string* col;
    string check="T";
    string* coltype;
    int size,x;
    BTree<long long,maxdegree>* this_table=tables.find(tablename,size,col,coltype,get_id);
    if(this_table==0){
        check="Fthere is no table with this name!\n";
        return check;
    }
    bool soton[size];
    if(query[1]=="*"){
        for(int i=0;i<size;i++){
            soton[i]=true;
        }
    }
    else{
        for(int i=0;i<size;i++){
            soton[i]=false;
        }
        for(int i=1;i<name-1;i++){
            for(int j=0;j<size;j++){
                if(col[j]==query[i]){
                    soton[j]=true;
                }
            }
        }
    }
    if(querysize-condition==1){
        string left,right,compare;
        compare=recog_condition(query[condition],left,right);
        int index=0,moghayese;
        for(int i=0;i<size;i++){
            if(col[i]==left){
                index=i;
                break;
            }
        }
        if(coltype[index]=="int"){
            if(check_int(right)){
                moghayese=str_to_int(right);
            }
            else{
                check="Fshould be integer\n";
                return check;
            }
        }
        else if(coltype[index]=="timestamp"){
            Times zaman;
            if(check_time(right,zaman)){
                moghayese=zaman.hash();
            }
            else{
                check="Fshould be time and valid\n";
                return check;
            }
        }
        else if(coltype[index]=="string"){
            moghayese=hash_str_to_int(right.substr(1,(right.length()-2)));
        }
        vector<Node<long long,maxdegree>*> output;
        if((compare=="==") || (compare=="<")){
            output=this_table[index].itaratormin(moghayese,compare);
        }
        else if(compare==">"){
            output=this_table[index].itaratormax(moghayese,compare);
        }
        Node<long long,maxdegree>* tmp;
        int idcol=(size-index)%size;
        vector<Node<long long,maxdegree>*> output1;
        for(int j=0;j<output.size();j++){
            tmp=output[j];
            for(int i=0;i<(idcol);i++){
                tmp=tmp->nextField;
            }
            output1.push_back(tmp);
        }
        output=output1;
        int x;
        for(int i=0;i<(output.size());i++){
            x=i;
            for(int j=i+1;j<(output.size());j++){
                if(output[x]->data>output[j]->data){
                    x=j;
                }
            }
            if(x!=i){
                tmp=output[i];
                output[i]=output[x];
                output[x]=tmp;
            }
            bool start=false;
            tmp=output[i];
            if(soton[0]){
                cout<<tmp->data;
                start=true;
            }
            tmp=tmp->nextField;
            for(int k=1;k<size;k++){
                if(soton[k]){
                    if(start){cout<<" ";}
                    if(coltype[k]=="int"){
                        cout<<tmp->data;
                        start=true;
                    }
                    else if(coltype[k]=="timestamp"){
                        Times zaman;
                        zaman.unhash(tmp->data);
                        zaman.display();
                        start=true;
                    }
                    else if(coltype[k]=="string"){
                        start=true;
                        cout<<unhash_int_to_str(tmp->data);
                    }
                }
                tmp=tmp->nextField;
            }
            cout<<endl;
        }
    }
    else if(querysize-condition==3){
        string left1,right1,comp1;
        string left2,right2,comp2;
        comp1=recog_condition(query[condition],left1,right1);
        comp2=recog_condition(query[condition+2],left2,right2);
        int index1=0,index2=0,moghayese1,moghayese2;
        for(int i=0;i<size;i++){
            if(col[i]==left1){
                index1=i;
                break;
            }
        }
        for(int i=0;i<size;i++){
            if(col[i]==left2){
                index2=i;
                break;
            }
        }
        if(coltype[index1]=="int"){
            if(check_int(right1)){
                moghayese1=str_to_int(right1);
            }
            else{
                check="Fshould be integer\n";
                return check;
            }
        }
        else if(coltype[index1]=="timestamp"){
            Times zaman;
            if(check_time(right1,zaman)){
                moghayese1=zaman.hash();
            }
            else{
                check="Fshould be time and valid\n";
                return check;
            }
        }
        if(coltype[index2]=="int"){
            if(check_int(right2)){
                moghayese2=str_to_int(right2);
            }
            else{
                check="Fshould be integer\n";
                return check;
            }
        }
        else if(coltype[index2]=="timestamp"){
            Times zaman;
            if(check_time(right2,zaman)){
                moghayese2=zaman.hash();
            }
            else{
                check="Fshould be time and valid\n";
                return check;
            }
        }
        vector<Node<long long,maxdegree>*> output1;
        vector<Node<long long,maxdegree>*> output2;
        if((comp1=="==") || (comp1=="<")){
            output1=this_table[index1].itaratormin(moghayese1,comp1);
        }
        else{
            output1=this_table[index1].itaratormax(moghayese1,comp1);
        }
        if((comp2=="==") || (comp2=="<")){
            output2=this_table[index2].itaratormin(moghayese2,comp2);
        }
        else{
            output2=this_table[index2].itaratormax(moghayese2,comp2);
        }
        if(index1!=index2){
            vector<Node<long long,maxdegree>*> output;
            Node<long long,maxdegree>* tmp;
            int tasavi=(size+(index2-index1))%size;
            for(int i=0;i<output1.size();i++){
                tmp=output1[i];
                for(int j=0;j<tasavi;j++){
                    tmp=tmp->nextField;
                }
                output.push_back(tmp);
            }
            output1=output;
            index1=index2;
        }
        int idcol=(size-index1)%size;
        vector<Node<long long,maxdegree>*> output;
        vector<Node<long long,maxdegree>*> output3;
        Node<long long,maxdegree>* tmp;
        for(int j=0;j<output1.size();j++){
            tmp=output1[j];
            for(int i=0;i<(idcol);i++){
                tmp=tmp->nextField;
            }
            output.push_back(tmp);
        }
        output1=output;
        idcol=(size-index2)%size;
        for(int j=0;j<output2.size();j++){
            tmp=output2[j];
            for(int i=0;i<(idcol);i++){
                tmp=tmp->nextField;
            }
            output3.push_back(tmp);
        }
        output2=output3;
        vector<Node<long long,maxdegree>*> finall;
        if(query[condition+1]=="|"){
            for(int i=0;i<output1.size();i++){
                tmp=output1[i];
                finall.push_back(tmp);
            }
            for(int i=0;i<output2.size();i++){
                tmp=output2[i];
                finall.push_back(tmp);
            }
        }
        else if(query[condition+1]=="&"){
            for(int i=0;i<(output1.size()-1);i++){
                x=i;
                for(int j=i+1;j<(output1.size());j++){
                    if(output1[x]->data>output1[j]->data){
                        x=j;
                    }
                }
                if(x!=i){
                    tmp=output1[i];
                    output1[i]=output1[x];
                    output1[x]=tmp;
                }
            }
            finall=find_same(output1,output2);
        }
        output=finall;
        for(int i=0;i<(output.size());i++){
            x=i;
            for(int j=i+1;j<(output.size());j++){
                if(output[x]->data>output[j]->data){
                    x=j;
                }
            }
            if(x!=i){
                tmp=output[i];
                output[i]=output[x];
                output[x]=tmp;
            }
            bool start=false;
            tmp=output[i];
            if(soton[0]){
                cout<<tmp->data;
                start=true;
            }
            tmp=tmp->nextField;
            for(int k=1;k<size;k++){
                if(soton[k]){
                    if(start){cout<<" ";}
                    if(coltype[k]=="int"){
                        cout<<tmp->data;
                        start=true;
                    }
                    else if(coltype[k]=="timestamp"){
                        Times zaman;
                        zaman.unhash(tmp->data);
                        zaman.display();
                        start=true;
                    }
                    else if(coltype[k]=="string"){
                        start=true;
                        cout<<unhash_int_to_str(tmp->data);
                    }
                }
                tmp=tmp->nextField;
            }
            cout<<endl;
        }
    }
    else{
        check="FWrong syntax\n";
        return check;
    }
    return check;
}

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