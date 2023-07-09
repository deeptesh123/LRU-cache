#include<bits/stdc++.h>
using namespace std;
class node{
    public:
        string key;
        int value;
        node(string key,int val){
            this->key=key;
            this->value=val;
        }
};
class lru_cache{
    public:
        list<node> cache;
        unordered_map<string,list<node>::iterator> map;
        int max_size;
        lru_cache(int size){
            this->max_size=size;
        }
        void insert(string str,int val){
            if(map.count(str)) map[str]->value=val;
            else{
                if(cache.size()==max_size){
                    node last=cache.back();
                    map.erase(last.key);
                    cache.pop_back();
                }
                node new_node(str,val);
                cache.push_front(new_node);
                map[str]=cache.begin();
            }
        }
        int* get_value(string key){
                if(!map.count(key)) return NULL;
                auto it=map[key];
                cache.push_front(node(key,it->value));
                cache.erase(it);
                map[key]=cache.begin();
                return &cache.begin()->value;
        }
        int most_recently_used(){
            return cache.begin()->value;
        }
};
int main(){
    lru_cache lc(3);
    lc.insert("first",1);
    lc.insert("second",2);
    lc.insert("third",3);
    string chk="fourth";
    if(!lc.get_value(chk)) cout<<"not found";
    else cout<<*lc.get_value(chk)<<endl;
    chk="third";
    if(!lc.get_value(chk)) cout<<"chal bsdk";
    else cout<<*lc.get_value(chk);
    cout<<lc.most_recently_used();
}