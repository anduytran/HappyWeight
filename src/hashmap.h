//
// Created by Dylan on 4/9/2024.
//
#pragma once
#ifndef HAPPYWEIGHT_HASHMAP_H
#define HAPPYWEIGHT_HASHMAP_H

#endif //HAPPYWEIGHT_HASHMAP_H

#include "food.h"
#include "comparators.h"
#include <queue>
using namespace std;

class HashMap{
    vector<Food*> map;
    int current_size = 0;
    int max_size;
    float lf = .56;

    using PriorityQueueMin = priority_queue<pair<string, float>, vector<pair<string, float>>, MinHeapCompare>;
    using PriorityQueueMax = priority_queue<pair<string, float>, vector<pair<string, float>>, MaxHeapCompare>;

private:
    int getNutritionIndex(const string& nutrition){
        int n = -1;
        if(nutrition == "Calories"){
            n = 0;
        } else if(nutrition == "Protein"){
            n = 1;
        } else if(nutrition == "Carbohydrates"){
            n = 2;
        } else if(nutrition == "Sugars"){
            n = 3;
        } else if(nutrition == "Fiber"){
            n = 4;
        } else if(nutrition == "Cholesterol"){
            n = 5;
        } else if(nutrition == "Saturated Fats"){
            n = 6;
        } else if(nutrition == "Trans Fatty Acids"){
            n = 7;
        } else if(nutrition == "Soluble Fiber"){
            n = 8;
        } else if(nutrition == "Insoluble Fiber"){
            n = 9;
        } else if(nutrition == "Monounsaturated Fats"){
            n = 10;
        } else if(nutrition == "Polyunsaturated Fats"){
            n = 11;
        } else if(nutrition == "Caffeine") {
            n = 12;
        }
        return n;
    }

    template<typename T, typename C>
    void findTop10(priority_queue<T, vector<T>, C> &PQ,
                   const string& category, int nutrition_index){

        for (int i = 0; i < getSize(); i++) {
            if (map[i] != nullptr) {
                if (map[i]->getValue().first == category) {
                    float val = map[i]->getValue().second[nutrition_index];
                    if(val < 0){
                        continue;
                    }
                    PQ.push(make_pair(map[i]->getKey(), val));
                    if( PQ.size() > 10){
                        PQ.pop();
                    }
                }
            }
        }
    }

public:
    hash<string> hash;
    HashMap(){
        max_size = 400;
        vector<Food*> v(max_size);
        this->map = v;
    }
    ~HashMap(){
        for(auto & i : map) {
            if (i != nullptr) {
                Food *ptr = i;
                delete ptr;
                i = nullptr;
            }
        }
    }
    int getSize() const{
        return max_size;
    }
    int getCurrentSize() const{
        return current_size;
    }
    void search(const string& s){
        for(int i = 0; i < map.size(); i++){
            if(map[i] != nullptr){
                string str = map[i]->getKey();
                auto it = ::search(str.begin(), str.end(), s.begin(), s.end(),
                                   caseinsensitive);
                if(it != str.end()){
                    cout << map[i]->getKey() << endl;
                }
            }
        }
        cout << endl;
    }
    void set(string name, Food* food){
        current_size += 1;
        int index;
        if((float)current_size / (float)max_size >= lf) {
            // cout << "Resizing!" << endl;
            max_size *= 2;
            vector<Food *> temp(max_size);
            for (auto &i: map) {
                if (i != nullptr) {
                    index = hash(i->getKey()) % (max_size - 5);
                    if(index >= max_size){
                        // cout << "Problem!" << endl;
                    }
                    if (temp[index] == nullptr) {
                        temp[index] = i;
                    } else if (temp[index]->getKey() != i->getKey()) {
                        for(int j = 0; j < max_size; j++){
                            index = (hash(i->getKey()) + (j * j)) % (max_size - 5);
                            if(!temp[index]){
                                temp[index] = i;
                                break;
                            }
                        }
                    }
                }
            }
            map = temp;
        }
        index = hash(name) % (max_size - 5);
        if(map[index] == nullptr){
            map[index] = food;
        }
        else if(map[index]->getKey() != name){
            for(int j = 0; j < max_size; j++){
                index = (hash(name) + (j * j)) % (max_size - 5);
                if(!map[index]){
                    map[index] = food;
                    break;
                }
            }
        }
    }
    Food* get(string name){
        int index = hash(name) % (max_size - 5);
        if(map[index] != nullptr) {
            if (map[index]->getKey() == name) {
                return map[index];
            } else if (map[index]->getKey() != name) {
                for(int j = 0; j < max_size; j++){
                    index = (hash(name) + (j * j)) % (max_size - 5);
                    if(map[index] != nullptr) {
                        if (map[index]->getKey() == name) {
                            return map[index];
                        }
                    }
                }
            }
        }else{
            cout << "Food doesn't exist" << endl;

        }
        return nullptr;
    }

    void tenValues(const string& category, const string& nutrition, const string& comp){
        int nutrition_index = getNutritionIndex(nutrition);
        if(nutrition_index < 0 ){
            cout << "Not Valid" << endl;
            return;
        }
        vector<pair<string, float>> top10;
        string label = "lowest";
        if(comp == "Lowest"){
            PriorityQueueMax PQ;
            findTop10(PQ, category, nutrition_index);
            while(!PQ.empty()){
                top10.push_back(PQ.top());
                PQ.pop();
            }
        }else{
            label = "highest";
            PriorityQueueMin PQ;
            findTop10(PQ, category, nutrition_index);
            while(!PQ.empty()){
                top10.push_back(PQ.top());
                PQ.pop();
            }
        }
        cout << "Using the Hashmap, " << endl;
        cout << "The 10 foods with the "<<label<<" values are: " << endl;
        for (int i = top10.size() - 1, j = 1; i >= 0; i--, j++) {
            cout << j << ". " << top10[i].first << ": " << top10[i].second << endl;
        }
        cout << endl;
    }


};
