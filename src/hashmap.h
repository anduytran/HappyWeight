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

    //  Create an alias for a MinHeap and MaxHeap (PQ)
    using PriorityQueueMin = priority_queue<pair<string, float>, vector<pair<string, float>>, MinHeapCompare>;
    using PriorityQueueMax = priority_queue<pair<string, float>, vector<pair<string, float>>, MaxHeapCompare>;

private:
    template<typename T, typename C>
    // Generic Function to get the ten lowest or ten highest values using a MaxHeap or MinHeap
    void findTop10(priority_queue<T, vector<T>, C> &PQ,
                   const string& category, int nutrition_index){
        // Iterate over hashmap
        for (int i = 0; i < getSize(); i++) {
            if (map[i] != nullptr) {
                // If a valid category was found
                if (map[i]->getValue().first == category || category == "All") {
                    // Get the value, given the nutrition index
                    float val = map[i]->getValue().second[nutrition_index];
                    if(val < 0){
                        continue;
                    }
                    // Store the name and value of the current food in the PQ
                    PQ.push(make_pair(map[i]->getKey(), val));
                    // If the size is larger than ten, we pop that element from the PQ
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
        int entries = 0;
        string output = "";
        for(int i = 0; i < map.size(); i++){
            if(map[i] != nullptr){
                string str = map[i]->getKey();
                auto it = ::search(str.begin(), str.end(), s.begin(), s.end(),
                                   caseinsensitive);
                if(it != str.end()){
                    entries++;
                    output += map[i]->getKey() + "\n";
                }
            }
        }
        cout << entries << " entries found for \"" << s << "\"" << endl << output << endl;
    }
    void set(string name, Food* food){
        current_size += 1;
        int index;
        if((float)current_size / (float)max_size >= lf) {
            max_size *= 2;
            vector<Food *> temp(max_size);
            for (auto &i: map) {
                if (i != nullptr) {
                    index = hash(i->getKey()) % (max_size - 5);
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
        }else {
            return nullptr;
        }
    }
    // Function to print the top ten food with the highest or lowest nutritional values
    void tenValues(const string& category, const string& nutrition, const string& comp){
        int nutrition_index = getNutritionIndex(nutrition);
        // Checking if nutrition index is valid
        if(nutrition_index < 0 ){
            cout << "Not Valid" << endl;
            return;
        }
        // Decide whether to display the lowest or highest values
        vector<pair<string, float>> top10;
        string label = "lowest";
        if(comp == "Lowest"){
            // Create a MaxHeap
            PriorityQueueMax PQ;
            // Find top ten food names and values
            findTop10(PQ, category, nutrition_index);
            // Pop the elements from the MaxHeap and store them in the top ten vector
            while(!PQ.empty()){
                top10.push_back(PQ.top());
                PQ.pop();
            }
        }else{
            label = "highest";
            // Create a MinHeap
            PriorityQueueMin PQ;
            // Find top ten food names and values
            findTop10(PQ, category, nutrition_index);
            // Pop the elements from the MinHeap and store them in the top ten vector
            while(!PQ.empty()){
                top10.push_back(PQ.top());
                PQ.pop();
            }
        }
        // Print out the results
        cout << "Using the Hashmap, " << endl;
        cout << "The 10 foods with the "<< label << " " << nutrition << " are: " << endl;
        for (int i = top10.size() - 1, j = 1; i >= 0; i--, j++) {
            cout << j << ". " << top10[i].first << ": " << top10[i].second << endl;
        }
        cout << endl;
    }


};
