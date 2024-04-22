//
// Created by Dylan on 4/16/2024.
//

#ifndef TESTING_FOOD_H
#define TESTING_FOOD_H
#endif //TESTING_FOOD_H
#pragma once
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

bool sortbysecondlt(const pair<string, float> &a, const pair<string, float> &b)
{
    return (a.second < b.second);
}
bool sortbysecondgt(const pair<string, float> &a, const pair<string, float> &b)
{
    return (a.second > b.second);
}



class Food{
    float calories, fat, protein, fiber, insoluble_fiber, carbohydrates, sugars, soluble_fiber, cholesterol, saturated_fats, trans_fats, monounsaturated_fats, polyunsaturated_fats, alcohol, caffeine;
    string name, food_group;
    string key;
    pair<string, vector<float>> value;
    vector<pair<string, float>> servings;
public:
    Food(string k, const pair<string, vector<float>>& v, vector<pair<string, float>> s){
        key = k;
        value = v;
        servings = s;
    }
    string getKey(){
        return key;
    }
    pair<string, vector<float>> getValue(){
        return value;
    }
    Food(float calories, float fat, float protein, float fiber, float insoluble_fiber, float carbohydrates, float sugars, float soluble_fiber, float cholesterol, float saturated_fats, float trans_fat, float monounsaturated_fats, float polyunsaturated_fats, float alcohol, float caffeine){
        this->calories = calories;
        this->fat = fat;
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
        this->alcohol = alcohol;
        this->caffeine = caffeine;
    }
    Food* operator=(Food* ptr){
        this->key = ptr->key;
        this->value = ptr->value;
        return this;
    }
    void showServingSizes(){
        if(servings[0].first == "NULL"){
            cout << "This item does not have a preset serving size. :(" << endl;
            return;
        }
        int index = 0;
        string out = "";
        while(servings[index].first != "NULL"){

            out += servings[index].first + ": "  + to_string(servings[index].second) + "g" + "\n";
            index++;
        }
        cout << "This food item has " << index << " preset serving sizes: " << endl;
        cout << fixed << setprecision(2) << out << endl;
    }
};