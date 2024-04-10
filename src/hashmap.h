//
// Created by Dylan on 4/9/2024.
//
#ifndef HAPPYWEIGHT_HASHMAP_H
#define HAPPYWEIGHT_HASHMAP_H

#endif //HAPPYWEIGHT_HASHMAP_H

#include <vector>
#include <bits/stdc++.h>
using namespace std;

class HashNode{
    string key;
    HashNode* next = nullptr;
    pair<string, vector<float>> value;
public:
    HashNode(string k = "", pair<string, vector<float>> v = {"NULL", {}}){
        key = k;
        value = v;
    }
    string getKey(){
        return key;
    }
    void setValue(pair<string, vector<float>> value){
        this->value = value;
    }
    pair<string, vector<float>> getValue(){
        return value;
    }

};

class HashMap{
    vector<HashNode*> map;

public:
    HashMap(){
        vector<HashNode*> map(4294967295);
        this->map = map;
    }
    ~HashMap(){
        for(int i = 0; i < map.size(); i++){
            HashNode* ptr = map[i];
            delete ptr;
            map[i] = nullptr;
        }
    }
    void set(string name, int key, pair<string, vector<float>> value){
        HashNode* position = map[key];
        if(position == nullptr){
            position = new HashNode(name, value);
        }
        else{
            if(map[key]->getKey() != name){
                //probing
            }
            position->setValue(value);
        }
    }
    pair<string, vector<float>> operator[](string name){
        hash<string> hash;
        return map[hash(name)]->getValue();
    }
    const pair<string, vector<float>>& operator[](string name) const{
        hash<string> hash;
        return map[hash(name)]->getValue();
    }

};