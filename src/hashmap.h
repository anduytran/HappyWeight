//
// Created by Dylan on 4/9/2024.
//
#ifndef HAPPYWEIGHT_HASHMAP_H
#define HAPPYWEIGHT_HASHMAP_H

#endif //HAPPYWEIGHT_HASHMAP_H

#include <vector>
#include <bits/stdc++.h>
using namespace std;

bool sortbysecond(const pair<string, float> &a, const pair<string, float> &b)
{
    return (a.second < b.second);
}

class HashNode{
    string key;
    pair<string, vector<float>> value;
public:
    HashNode(string k = "", pair<string, vector<float>> v = {"NULL", {}}){
        key = k;
        value = v;
    }
    string getKey(){
        return key;
    }
    pair<string, vector<float>> getValue(){
        return value;
    }

    HashNode* operator=(HashNode* ptr){
        this->key = ptr->key;
        this->value = ptr->value;
        return this;
    }
};

class HashMap{
    vector<HashNode*> map;
    int current_size = 0;
    int max_size;
    float lf = .7;

public:
    hash<string> hash;
    HashMap(){
        max_size = 100;
        vector<HashNode*> v(max_size);
        this->map = v;
    }
    ~HashMap(){
        for(int i = 0; i < map.size(); i++){
            HashNode* ptr = map[i];
            delete ptr;
            map[i] = nullptr;
        }
    }
    int getSize(){
        return max_size;
    }
    int getCurrentSize(){
        return current_size;
    }
    HashNode*& operator[](string name){
        current_size += 1;
        int index = hash(name) % (max_size - 1);
        if(!map[index]){
            return map[index];
        }
        if(map[index]->getKey() != name){
            while(map[index] != nullptr){
                int power = 0;
                index += pow(2, power);
                power++;
                if(index == getSize()){
                    index = 0;
                }
            }
        }
        if((float)current_size / (float)max_size >= lf){
            max_size *= 2;
            if(max_size == 12800){
                max_size = 20300;
            }
            index = hash(name) % (max_size - 1);
            vector<HashNode*> temp(max_size);
            for(int i = 0; i < map.size(); i++){
                if(map[i] != nullptr){
                    temp[index] = map[i];
                }
            }
            map = temp;
        }
        return map[index];
    }
    HashNode* operator[](string name) const{
        return map[hash(name) % (max_size - 1)];
    }
    void tenLowestCalorie(const string& category) {
        vector<pair<string, float>> temp;
        for (int i = 0; i < getSize(); i++) {
            if (map[i] != nullptr) {
                if (map[i]->getValue().first == category) {
                    float norm_cal = map[i]->getValue().second[1] * (map[i]->getValue().second[14] / 100);
                    if(norm_cal < 0){
                        continue;
                    }
                    if (temp.size() < 10) {
                        temp.emplace_back(map[i]->getKey(), norm_cal);
                        if (temp.size() == 10) {
                            sort(temp.begin(), temp.end(), sortbysecond);
                        }
                    } else {
                        if (norm_cal < temp.back().second && norm_cal > 0) {
                            sort(temp.begin(), temp.end(), sortbysecond);
                            temp.pop_back();
                            temp.emplace_back(map[i]->getKey(), norm_cal);
                        }
                    }
                }
            }
        }
        sort(temp.begin(), temp.end(), sortbysecond);
        cout << "The 10 foods with the lowest calorie values are: " << endl;
        for (int i = 0; i < temp.size(); i++) {
            cout << i + 1 << ". " << temp[i].first << ": " << temp[i].second << endl;
        }
    }
};