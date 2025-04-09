#include <iostream>
#include <BTree.h>
#include <AvlTree.h>
#include <MinHeap.h>
#include <functions.h>
using namespace std;

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
        check="Fthere is no table with this name!\n";
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
                check="Fyou're input should be string!\n";
                return check;
            }
        }
        else if(coltype[i]=="int"){
            if(!check_int(query[index])){
                check="Fyou're input should be string!\n";
                return check;
            }
        }
        else if(coltype[i]=="timestamp"){
            Times tt;
            if(!check_time(query[index],tt)){
                check="Fyou're input should be timestamp!\n";
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
    /*else if(querysize==7){
        char x;
        string c1_1,c1_2,c2_1,c2_2,tmp1,tmp2;
        x=query[5][0];
        tmp1=recog_condition(query[4],c1_1,c1_2);
        tmp2=recog_condition(query[6],c2_1,c2_2);
        if(x=='&'){
            check=Delete_two_condition(tables,query,get_id,querysize,c1_1,tmp1,c1_2,c2_1,tmp2,c2_2,ss);
        }
        else if(x=='|'){
            check=Delete_one_condition(tables,query,get_id,querysize,c1_1,tmp1,c1_2,ss);
            if(check[0]!='T'){
                return check;
            }
            check=Delete_one_condition(tables,query,get_id,querysize,c2_1,tmp2,c2_2,ss);
        }
        else{
            check="FWrong syntax\n";
            return check;
        }
    }*/
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
            check="Fshould be time\n";
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

/*template <typename tmptype,int maxdegree>
string Delete_two_condition(AvlTree<tmptype,maxdegree>& tables,string* query,MinHeap& get_id,int querysize,string left1,string comp1,string right1,string left2,string comp2,string right2,int& ss){
    string tablename=query[2];
    string* col;
    string check="T";
    string* coltype;
    int size;
    BTree<long long,maxdegree>* this_table=tables.find(tablename,size,col,coltype);
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
            check="Fshould be time\n";
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
            check="Fshould be time\n";
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
        index2=index1;
    }
    Node<long long,maxdegree>* tmp;
    Node<long long,maxdegree>* tmp2;
    vector<Node<long long,maxdegree>*> final=find_same(output2,output1);
    for(int i=0;i<final.size();i++){
        tmp=final[i];
        tmp2=this_table[index2].deleteNode_by_node(tmp);
        tmp=tmp2;
        for(int i=1;i<size;i++){
            tmp2=this_table[(index2+i)%size].deleteNode_by_node(tmp);
            tmp=tmp2;
            if(((index2+i+1)%size) == 0){
                int id=tmp2->data;
                get_id->insert(id);
            }
        }
        ss++;
    }
    return check;
}*/

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
                check="Fshould be time\n";
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
    return check;
}

template <typename tmptype,int maxdegree>
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

template <typename tmptype,int maxdegree>
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
                check="Fshould be time\n";
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
    /*else if(querysize-condition==3){
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
                check="Fshould be time\n";
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
                check="Fshould be time\n";
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
                finall.push_back(output1[i]);
            }
            for(int i=0;i<output2.size();i++){
                finall.push_back(output2[i]);
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
        for(int i=0;i<(finall.size()-1);i++){
            x=i;
            for(int j=i+1;j<(finall.size());j++){
                if(finall[x]->data>finall[j]->data){
                    x=j;
                }
            }
            if(x!=i){
                tmp=finall[i];
                finall[i]=finall[x];
                finall[x]=tmp;
            }
            tmp=finall[i];
            if(soton[0]){
                cout<<tmp->data;
            }
            tmp=tmp->nextField;
            for(int i=1;i<size;i++){
                if(soton[i]){
                    cout<<" ";
                    if(col[i]=="int"){
                        cout<<tmp->data;
                    }
                    else if(col[i]=="timestamp"){
                        Times zaman;
                        zaman.unhash(tmp->data);
                        zaman.display();
                    }
                    else if(col[i]=="string"){
                        cout<<unhash_int_to_str(tmp->data);
                    }
                }
                tmp=tmp->nextField;
            }
            cout<<endl;
        }

    }*/
    else{
        check="FWrong syntax\n";
        return check;
    }
    return check;
}
