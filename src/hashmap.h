//
// Created by Dylan on 4/9/2024.
//
#ifndef HAPPYWEIGHT_HASHMAP_H
#define HAPPYWEIGHT_HASHMAP_H

#endif //HAPPYWEIGHT_HASHMAP_H

#include "food.h"
using namespace std;

bool sortbysecondlt(const pair<string, float> &a, const pair<string, float> &b)
{
    return (a.second < b.second);
}
bool sortbysecondgt(const pair<string, float> &a, const pair<string, float> &b)
{
    return (a.second > b.second);
}


class HashMap{
    vector<Food*> map;
    int current_size = 0;
    int max_size;
    float lf = .7;

public:
    hash<string> hash;
    HashMap(){
        max_size = 100;
        vector<Food*> v(max_size);
        this->map = v;
    }
    ~HashMap(){
        for(int i = 0; i < map.size(); i++){
            Food* ptr = map[i];
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
    Food*& operator[](string name){
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
            vector<Food*> temp(max_size);
            for(int i = 0; i < map.size(); i++){
                if(map[i] != nullptr){
                    temp[index] = map[i];
                }
            }
            map = temp;
        }
        return map[index];
    }
    Food* operator[](string name) const{
        return map[hash(name) % (max_size - 1)];
    }
    void tenLowestCalorie(const string& category) {
        vector<pair<string, float>> temp;
        for (int i = 0; i < getSize(); i++) {
            if (map[i] != nullptr) {
                if (map[i]->getValue().first == category) {
                    float norm_cal = map[i]->getValue().second[1] * (map[i]->getValue().second[14] / 100);
                    norm_cal = map[i]->getValue().second[1];
                    if(norm_cal < 0){
                        continue;
                    }
                    if (temp.size() < 10) {
                        temp.emplace_back(map[i]->getKey(), norm_cal);
                        if (temp.size() == 10) {
                            sort(temp.begin(), temp.end(), sortbysecondlt);
                        }
                    } else {
                        if (norm_cal < temp.back().second && norm_cal > 0) {
                            sort(temp.begin(), temp.end(), sortbysecondlt);
                            temp.pop_back();
                            temp.emplace_back(map[i]->getKey(), norm_cal);
                        }
                    }
                }
            }
        }
        sort(temp.begin(), temp.end(), sortbysecondlt);
        cout << "The 10 foods with the lowest calorie values are: " << endl;
        for (int i = 0; i < temp.size(); i++) {
            cout << i + 1 << ". " << temp[i].first << ": " << temp[i].second << endl;
        }
    }
    void tenHighestCalorie(const string& category) {
        vector<pair<string, float>> temp;
        for (int i = 0; i < getSize(); i++) {
            if (map[i] != nullptr) {
                if (map[i]->getValue().first == category) {
                    float norm_cal = map[i]->getValue().second[1] * (map[i]->getValue().second[14] / 100);
                    norm_cal = map[i]->getValue().second[1];
                    if(norm_cal < 0){
                        continue;
                    }
                    if (temp.size() < 10) {
                        temp.emplace_back(map[i]->getKey(), norm_cal);
                        if (temp.size() == 10) {
                            sort(temp.begin(), temp.end(), sortbysecondgt);
                        }
                    } else {
                        if (norm_cal > temp.back().second && norm_cal > 0) {
                            sort(temp.begin(), temp.end(), sortbysecondgt);
                            temp.pop_back();
                            temp.emplace_back(map[i]->getKey(), norm_cal);
                        }
                    }
                }
            }
        }
        sort(temp.begin(), temp.end(), sortbysecondgt);
        cout << "The 10 foods with the highest calorie values are: " << endl;
        for (int i = 0; i < temp.size(); i++) {
            cout << i + 1 << ". " << temp[i].first << ": " << temp[i].second << endl;
        }
    }
};