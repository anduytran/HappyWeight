//
// Created by Dylan on 4/16/2024.
//

#ifndef TESTING_FOOD_H
#define TESTING_FOOD_H

#endif //TESTING_FOOD_H
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
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
    Food(float calories, float protein, float fiber, float insoluble_fiber, float carbohydrates, float sugars, float soluble_fiber, float cholesterol, float saturated_fats, float trans_fat, float monounsaturated_fats, float polyunsaturated_fats, float caffeine, float sw, float sw2, float sw3, float sw4, float sw5, float sw6, float sw7, float sw8, float sw9, float twohundredcal_weight){
        this->calories = calories;
        this->protein = protein;
        this->fiber = fiber;
        this->insoluble_fiber = insoluble_fiber;
        this->carbohydrates = carbohydrates;
        this->sugars = sugars;
        this->soluble_fiber = soluble_fiber;
        this->cholesterol = cholesterol;
        this->trans_fats = trans_fat;
        this->saturated_fats = saturated_fats;
        this->monounsaturated_fats = monounsaturated_fats;
        this->polyunsaturated_fats = polyunsaturated_fats;
        this->caffeine = caffeine;
        this->sw = sw;
    }
    Food* operator=(Food* ptr){
        this->key = ptr->key;
        this->value = ptr->value;
        return this;
    }
};