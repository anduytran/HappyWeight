//
// Created by Dylan on 4/16/2024.
//

#ifndef TESTING_FOOD_H
#define TESTING_FOOD_H

#endif //TESTING_FOOD_H
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class Food{
    float ID, calories, protein, fiber, insoluble_fiber, carbohydrates, sugars, soluble_fiber, cholesterol, saturated_fats, trans_fats, monounsaturated_fats, polyunsaturated_fats, caffeine, sw, sw2, sw3, sw4, sw5, sw6, sw7, sw8, sw9, twohundredcal_weight;
    string name, food_group, sd, sd2, sd3, sd4, sd5, sd6, sd7, sd8, sd9;
    string key;
    pair<string, vector<float>> value;
public:
    Food(string k = "", pair<string, vector<float>> v = {"NULL", {}}){
        key = k;
        value = v;
    }
    string getKey(){
        return key;
    }
    pair<string, vector<float>> getValue(){
        return value;
    }

    Food* operator=(Food* ptr){
        this->key = ptr->key;
        this->value = ptr->value;
        return this;
    }
};