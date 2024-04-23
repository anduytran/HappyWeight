#pragma once
#ifndef COMPARATORS_H
#define COMPARATORS_H
#include <iostream>
#include <string>
using std::string;
using std::pair;

// Comparator used to store the top ten values in a MinHeap
struct MinHeapCompare {
    bool operator()(const pair<string, float>& p1, const pair<string, float>& p2) const {
        return p1.second > p2.second || (p1.second == p2.second && p1.first < p2.first);
    }
};

// Comparator used to store the ten lowest  values in a MaxHeap
struct MaxHeapCompare {
    bool operator()(const pair<string, float>& p1, const pair<string, float>& p2) const {
        return p1.second < p2.second || (p1.second == p2.second && p1.first < p2.first);
    }
};

// Verify that both characters are case insensitive
bool caseinsensitive(char a, char b){
    return tolower(a) == tolower(b);
}

// Get the Nutrition index given its name
int getNutritionIndex(const string& nutrition){
    int n = -1;
    if(nutrition == "Calories" || nutrition == "calories"){
        n = 0;
    } else if(nutrition == "Protein" || nutrition == "protein"){
        n = 1;
    } else if(nutrition == "Carbohydrates" || nutrition == "carbohydrates"){
        n = 2;
    } else if(nutrition == "Sugars" || nutrition == "sugars"){
        n = 3;
    } else if(nutrition == "Fiber" || nutrition == "fiber"){
        n = 4;
    } else if(nutrition == "Cholesterol" || nutrition == "cholesterol"){
        n = 5;
    } else if(nutrition == "Saturated Fats" || nutrition == "saturated Fats" || nutrition == "saturated fats" || nutrition == "Saturated fats"){
        n = 6;
    } else if(nutrition == "Trans Fatty Acids" || nutrition == "trans Fatty Acids" || nutrition == "trans fatty Acids" || nutrition == "trans fatty acids" || nutrition == "Trans fatty Acids" || nutrition == "Trans Fatty acids"){
        n = 7;
    } else if(nutrition == "Soluble Fiber" || nutrition == "soluble Fiber" || nutrition == "soluble fiber" || nutrition == "Soluble fiber"){
        n = 8;
    } else if(nutrition == "Insoluble Fiber" || nutrition == "insoluble Fiber" || nutrition == "insoluble fiber" || nutrition == "Insoluble fiber"){
        n = 9;
    } else if(nutrition == "Monounsaturated Fats" || nutrition == "monounsaturated fats" || nutrition == "monounsaturated Fats" || nutrition == "Monounsaturated fats"){
        n = 10;
    } else if(nutrition == "Polyunsaturated Fats" || nutrition == "polyunsaturated fats" || nutrition == "Polyunsaturated fats" || nutrition == "polyunsaturated Fats"){
        n = 11;
    } else if(nutrition == "Caffeine" || nutrition == "caffeine") {
        n = 12;
    }
    return n;
}

#endif