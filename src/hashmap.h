//
// Created by Dylan on 4/9/2024.
//
#ifndef HAPPYWEIGHT_HASHMAP_H
#define HAPPYWEIGHT_HASHMAP_H

#endif //HAPPYWEIGHT_HASHMAP_H

#include "food.h"
using namespace std;

class HashMap{
    vector<Food*> map;
    int current_size = 0;
    int max_size;
    float lf = .56;

public:
    hash<string> hash;
    HashMap(){
        max_size = 100;
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
    Food* get(const string& name){
        int index = hash(name) % (max_size);
        if(map[index] != nullptr) {
            if (map[index]->getKey() == name) {
                return map[index];
            } else if (map[index]->getKey() != name) {
                int power = 0;
                while (map[index] != nullptr) {
                    index += pow(2, power);
                    power++;
                    if (index >= max_size) {
                        index = index % max_size;
                    }
                }
                return map[index];
            }
        }
        else{
            return nullptr;
        }
    }
    void set(const string& name, Food* food){
        current_size += 1;
        int index;
        if((float)current_size / (float)max_size >= lf) {
            max_size *= 2;
            vector<Food *> temp(max_size);
            for (auto &i: map) {
                if (i != nullptr) {
                    index = hash(i->getKey()) % (max_size);
                    if (!temp[index]) {
                        temp[index] = i;
                    } else if (temp[index]->getKey() != i->getKey()) {
                        int power = 0;
                        while (temp[index] != nullptr) {
                            index += pow(2, power);
                            power++;
                            if (index >= max_size) {
                                index = index % max_size;
                            }
                        }
                        temp[index] = i;
                    }
                }
            }
            map = temp;
        }
        index = hash(name) % (max_size);
        if(map[index] == nullptr){
            map[index] = food;
        }
        if(map[index]->getKey() != name){
            int power = 0;
            while(map[index] != nullptr){
                index += pow(2, power);
                power++;
                if(index > getSize()){
                    index = index % max_size;
                }
            }
            map[index] = food;
        }
    }

    void tenLowest(const string& category, const string& nutrition) {
        vector<pair<string, float>> temp;
        int n;
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
        } else{
            cout << "Not Valid" << endl;
            return;
        }
        for (int i = 0; i < getSize(); i++) {
            if (map[i] != nullptr) {
                if (map[i]->getValue().first == category) {
                    float val = map[i]->getValue().second[n];
                    if(val < 0){
                        continue;
                    }
                    if(map[i]->getKey() == "Pork Cured Bacon Cooked Microwaved"){
                        cout << "here";
                    }
                    if (temp.size() < 10) {
                        temp.emplace_back(map[i]->getKey(), val);
                        if (temp.size() == 10) {
                            sort(temp.begin(), temp.end(), sortbysecondlt);
                        }
                    } else {
                        if (val < temp.back().second && val > 0) {
                            temp.pop_back();
                            temp.emplace_back(map[i]->getKey(), val);
                            sort(temp.begin(), temp.end(), sortbysecondlt);
                        }
                    }
                }
            }
        }
        sort(temp.begin(), temp.end(), sortbysecondlt);
        cout << "The 10 foods with the lowest " << nutrition << " values are: " << endl;
        for (int i = 0; i < temp.size(); i++) {
            cout << i + 1 << ". " << temp[i].first << ": " << temp[i].second << endl;
        }
    }
    void tenHighest(const string& category, const string& nutrition) {
        vector<pair<string, float>> temp;
        int n;
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
        } else{
            cout << "Not Valid" << endl;
            return;
        }
        for (int i = 0; i < getSize(); i++) {
            if (map[i] != nullptr) {
                if (map[i]->getValue().first == category) {
                    float val = map[i]->getValue().second[n];
                    if(val < 0){
                        continue;
                    }
                    if (temp.size() < 10) {
                        temp.emplace_back(map[i]->getKey(), val);
                        if (temp.size() == 10) {
                            sort(temp.begin(), temp.end(), sortbysecondgt);
                        }
                    } else {
                        if (val > temp.back().second && val > 0) {
                            temp.pop_back();
                            temp.emplace_back(map[i]->getKey(), val);
                            sort(temp.begin(), temp.end(), sortbysecondgt);
                        }
                    }
                }
            }
        }
        sort(temp.begin(), temp.end(), sortbysecondgt);
        cout << "The 10 foods with the highest " << nutrition << " values are: " << endl;
        for (int i = 0; i < temp.size(); i++) {
            cout << i + 1 << ". " << temp[i].first << ": " << temp[i].second << endl;
        }
    }
};