//----------------------------------------------------------------------
// FILE: hash_table_collection
// NAME: Scott Tornquist
// DATE: 10/25/2020
// DESC: Implements a hash table version of the collection
//       class. Includes all member function inherited from collection
//       as well as the constructor, destructor, copy constructor, and
//       assignment operator and three public statistic functions
//----------------------------------------------------------------------


#ifndef HASH_TABLE_COLLECTION_H
#define HASH_TABLE_COLLECTION_H

#include "array_list.h"
#include "collection.h"
#include <functional>

template<typename K, typename V>
class HashTableCollection : public Collection<K,V>
{
public:
  // add a new key-value pair into the collection 
    void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collection
    void remove(const K& a_key);

  // find and return the value associated with the key
  // if key isn't found, returns false, otherwise true
    bool find(const K& search_key, V& the_val) const;

  // find and return each key >= k1 and <= k2 
    void find(const K& k1, const K& k2, ArrayList<K>& keys) const;
  
  // return all of the keys in the collection 
    void keys(ArrayList<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
    void sort(ArrayList<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
    size_t size() const;

    // constructor
    HashTableCollection();

    //destructor
    ~HashTableCollection();

    //copy constructor
    HashTableCollection(const HashTableCollection <K,V>& rhs);

    // assignment operator
    HashTableCollection& operator=(const HashTableCollection<K,V>& rhs);

    //three public statistics functions
    size_t min_chain_length();

    size_t max_chain_length();

    double avg_chain_length();


private:

    //the chain (linkedlist) nodes
    struct Node{
        K key;
        V value;
        Node* next;
    };

    // the (resizable) hash table 
    Node** hash_table;

    // number of k-v pairs stored in the collection
    size_t length;

    //current number of buckets in the hash table
    size_t table_capacity;

    //current load factor of the hash table
    double load_factor_threshold = .75;

    // double size and rehash the hash table
    void resize_and_rehash();

    //ArrayList<std::pair<K,V>> kv_list;

};



template<typename K, typename V>
void HashTableCollection<K,V>::resize_and_rehash(){

};

template<typename K, typename V>
HashTableCollection<K,V>::HashTableCollection(){
    length =0;
    table_capacity = 16;
    hash_table = new Node*[table_capacity];
    for(int i=0; i<16; i++){
        hash_table[i] = nullptr;
    }
};

    //destructor
template<typename K, typename V>
HashTableCollection<K,V>::~HashTableCollection(){
  length = 0;
  table_capacity = 0;
  delete [] hash_table;
};

    //copy constructor
template<typename K, typename V>
HashTableCollection<K,V>::HashTableCollection(const HashTableCollection <K,V>& rhs){
    
};

    // assignment operator
template<typename K, typename V>
HashTableCollection<K,V>& HashTableCollection<K,V>::operator=(const HashTableCollection<K,V>& rhs){

};

    //three public statistics functions
template<typename K, typename V>
size_t HashTableCollection<K,V>:: min_chain_length(){

};

template<typename K, typename V>
size_t HashTableCollection<K,V>::max_chain_length(){

};

template<typename K, typename V>
double HashTableCollection<K,V>::avg_chain_length(){
    
};

template<typename K, typename V>
void HashTableCollection<K,V>:: add(const K& a_key, const V& a_val){
if(length/table_capacity >= load_factor_threshold){
    resize_and_rehash();
}
std::hash<K> hash_fun;
size_t code = hash_fun(a_key);
size_t index = code%table_capacity;

Node* ptr = new Node;
ptr->key = a_key;
ptr->value = a_val;
ptr->next = hash_table[index];
hash_table[index] = ptr;
length++;
};



 template<typename K, typename V>
 void HashTableCollection<K,V>:: remove(const K& a_key){
   if((size() > 0)){ //there are keys in the table
    std::hash<K> hash_fun;
    size_t code = hash_fun(a_key);
    size_t index = code%table_capacity;
    if(hash_table[index]!= nullptr){// there are key(s) in the bucket
        Node* ptr2 = hash_table[index];
        if(hash_table[index]->next == nullptr){ //if there is only one key in the bucket
            if(ptr2->key == a_key){ //if it is the correct key
                hash_table[index] = nullptr;
                delete ptr2;
                length--;
                return;
            }
            else{ //if it not the correct key
                return;
            }
        }
        Node* ptr = hash_table[index]->next; // there is at least 2 keys
        if(ptr2->key == a_key){ //if it is the first key
                hash_table[index] = ptr;
                delete ptr2;
                length--;
                return;
        }
        while(ptr!= nullptr){
            if(ptr->key == a_key){
                ptr2->next=ptr->next;
                delete ptr;
                length--;
                return;
            }
        ptr= ptr->next;
        ptr2 = ptr2->next;
        }
    }
   }
 };

 template<typename K, typename V>
 bool HashTableCollection<K,V>:: find(const K& search_key, V& the_val) const{
   if((size() > 0)){
    std::hash<K> hash_fun;
    size_t code = hash_fun(search_key);
    size_t index = code%table_capacity;
    Node* ptr = hash_table[index];
    while(ptr!= nullptr){
        if(ptr->key == search_key){
            the_val = ptr->value;
            return true;
        }
        ptr= ptr->next;
    }
   }
     return false; // if not found return false
 };

 template<typename K, typename V>
 void HashTableCollection<K,V>:: find(const K& k1, const K& k2, ArrayList<K>& keys) const{ 
    if((k2 >= k1) && (size() > 0)){
        while(keys.size()>0){
            keys.remove(0);
        }
        for(int i=0; i<table_capacity; i++){
            if(hash_table[i]!=nullptr){
                Node* ptr = hash_table[i];
                while(ptr!=nullptr){
                    if(ptr->key >= k1 && ptr->key<= k2){
                        keys.add(ptr->key);
                    }
                    ptr = ptr->next;
                }
            }
        }         
    }
 };

template<typename K, typename V>
 void HashTableCollection<K,V>:: keys(ArrayList<K>& all_keys) const{
if(size() > 0){
        while(all_keys.size()>0){
            all_keys.remove(0);
        }
        for(int i=0; i<table_capacity; i++){
            if(hash_table[i]!=nullptr){
                Node* ptr = hash_table[i];
                while(ptr!=nullptr){
                    all_keys.add(ptr->key);
                    ptr = ptr->next;
                }
            }
        }         
    }
 };

 template<typename K, typename V>
 void HashTableCollection<K,V>:: sort(ArrayList<K>& all_keys_sorted) const{ 
    if((size() > 0)){
      while(all_keys_sorted.size()>0){
       all_keys_sorted.remove(0);
      }
     keys(all_keys_sorted); 
     all_keys_sorted.sort();
   }
 };

 template<typename K, typename V>
 size_t HashTableCollection<K,V>:: size() const{
     return length;
 };


#endif