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
    template<typename T, typename C>
    void findTop10(priority_queue<T, vector<T>, C> &PQ,
                   const string& category, int nutrition_index){

        for (int i = 0; i < getSize(); i++) {
            if (map[i] != nullptr) {
                if (map[i]->getValue().first == category || category == "All") {
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
    hash<string> hash; // using the hash function from STL
    HashMap(){
        max_size = 400; // because we know how big our map is, we can start "bigger" just to reduce amount of rehashings
        vector<Food*> v(max_size);
        this->map = v;
    }
    ~HashMap(){
        for(auto & i : map) { // iterate through map
            if (i != nullptr) { // if the item in map is actually a food item and not nullptr
                Food *ptr = i;
                delete ptr;
                i = nullptr; // delete and reassign to nullptr
            }
        }
    }
    int getSize() const{
        return max_size; // get the max capacity
    }
    int getCurrentSize() const{
        return current_size; // get the current size
    }
    void search(const string& s){ // look for item in map with only key-words
        int entries = 0;
        string output = "";
        for(int i = 0; i < map.size(); i++){
            if(map[i] != nullptr){
                string str = map[i]->getKey();
                auto it = ::search(str.begin(), str.end(), s.begin(), s.end(),
                                   caseinsensitive); // use custom comparator for case insensitivity
                if(it != str.end()){
                    entries++;
                    output += map[i]->getKey() + "\n";
                }
            }
        }
        cout << entries << " entries found for \"" << s << "\"" << endl << output << endl;
    }
    void set(string name, Food* food){ // set value in hashmap
        current_size += 1; // increase size
        int index;
        if((float)current_size / (float)max_size >= lf) { // if resize and rehash,
            max_size *= 2;
            vector<Food *> temp(max_size); // create a new vector that is double the previous size
            for (auto &i: map) { // iterate
                if (i != nullptr) { // if there is an item in the previous vector, rehash
                    index = hash(i->getKey()) % (max_size - 5);
                    if (temp[index] == nullptr) { // if there is no collision
                        temp[index] = i;
                    } else if (temp[index]->getKey() != i->getKey()) { // if there is a collision
                        for(int j = 0; j < max_size; j++){
                            index = (hash(i->getKey()) + (j * j)) % (max_size - 5); // quadratic probing
                            if(!temp[index]){ // until you find a spot that's not taken
                                temp[index] = i;
                                break;
                            }
                        }
                    }
                }
            }
            map = temp; // reassign the map ptr to the new vector
        }
        index = hash(name) % (max_size - 5); // recalculate index after rehashing or for the first time
        if(map[index] == nullptr){ // if no collision
            map[index] = food;
        }
        else if(map[index]->getKey() != name){ // if there is a collision, and this item is not the owner of the spot
            for(int j = 0; j < max_size; j++){
                index = (hash(name) + (j * j)) % (max_size - 5); // quadratic probing
                if(!map[index]){
                    map[index] = food;
                    break;
                }
            }
        }
    }
    Food* get(string name){ // retrieve item from hashmap
        int index = hash(name) % (max_size - 5); // calculate index
        if(map[index] != nullptr) { // if the hash calculates hits a spot that's not empty
            if (map[index]->getKey() == name) { // if this spot is the "name's" spot,
                return map[index];
            } else if (map[index]->getKey() != name) { // if this spot is not the "name's" spot
                for(int j = 0; j < max_size; j++){
                    index = (hash(name) + (j * j)) % (max_size - 5); // quadratic probing
                    if(map[index] != nullptr) {
                        if (map[index]->getKey() == name) { // if quadratic probing finds a new item, and it is the correct item
                            return map[index];
                        }
                    }
                }
            }
        }else {
            return nullptr;
        }
    }
    void tenValues(const string& category, const string& nutrition, const string& comp){
        int nutrition_index = getNutritionIndex(nutrition); // get correct index for nutrition
        if(nutrition_index < 0 ){ // getNutritionIndex() returns -1 for incorrect strings
            cout << "Not Valid" << endl;
            return;
        }
        vector<pair<string, float>> top10;
        string label = "lowest";
        if(comp == "Lowest"){ // min heap
            PriorityQueueMax PQ;
            findTop10(PQ, category, nutrition_index);
            while(!PQ.empty()){
                top10.push_back(PQ.top());
                PQ.pop();
            }
        }else{ // max heap
            label = "highest";
            PriorityQueueMin PQ;
            findTop10(PQ, category, nutrition_index);
            while(!PQ.empty()){
                top10.push_back(PQ.top());
                PQ.pop();
            }
        }
        cout << "Using the Hashmap, " << endl;
        cout << "The 10 foods [100 (g) serving sizes] with the "<< label << " " << nutrition << " are: " << endl;
        for (int i = top10.size() - 1, j = 1; i >= 0; i--, j++) {
            cout << j << ". " << top10[i].first << ": " << top10[i].second << endl;
        }
        cout << endl;
    }


};
