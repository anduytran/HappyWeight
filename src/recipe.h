//
// Created by Dylan on 4/18/2024.
//

#ifndef HAPPYWEIGHT_RECIPE_H
#define HAPPYWEIGHT_RECIPE_H

#endif //HAPPYWEIGHT_RECIPE_H
#pragma once
#include <chrono>
#include <hashmap.h>
#include <trie.h>

class Recipe{
    vector<pair<Food*, float>> foodsHash;
    vector<pair<Food*, float>> foodsTrie;
    float calories = 0, protein = 0, fiber = 0, insoluble_fiber = 0, carbohydrates = 0, sugars = 0, soluble_fiber = 0, cholesterol = 0, saturated_fats = 0, trans_fats = 0, monounsaturated_fats = 0, polyunsaturated_fats = 0, caffeine = 0;
    HashMap* map;
    Trie* trie;
public:
    Recipe(){
        HashMap* map = new HashMap();
        Trie* trie = new Trie();
        this->map = map;
        this->trie = trie;
    }
    ~Recipe(){
        for(int i = 0; i < foodsHash.size(); i++){
            Food* ptr = foodsHash[i].first;
            delete ptr;
            foodsHash[i].first = nullptr;
            foodsTrie[i].first = nullptr;
        }
    }
    void load(){
        fstream file;
        file.open("MyFoodData Nutrition Facts SpreadSheet Release 1.4 - SR Legacy and FNDDS.csv");
        string temp, line, word, code, description, nutrient_code;
        getline(file, temp);
        getline(file, temp);
        getline(file, temp);
        getline(file, temp);
        while (getline(file, line)) {
            stringstream s(line);
            getline(s, word, ',');
            //ptr->ID = stof(word);
            getline(s, word, ',');
            string name = word;
            getline(s, word, ',');
            string food_group = word;
            getline(s, word, ',');
            float calories = stof(word);
            getline(s, word, ',');
            float protein = stof(word);
            getline(s, word, ',');
            float carbohydrates = stof(word);
            getline(s, word, ',');
            float sugars = stof(word);
            getline(s, word, ',');
            float fiber = stof(word);
            getline(s, word, ',');
            float cholesterol = stof(word);
            getline(s, word, ',');
            float saturated_fats = stof(word);
            getline(s, word, ',');
            float trans_fats = stof(word);
            getline(s, word, ',');
            float soluble_fiber = stof(word);
            getline(s, word, ',');
            float insoluble_fiber = stof(word);
            getline(s, word, ',');
            float monounsaturated_fats = stof(word);
            getline(s, word, ',');
            float polyunsaturated_fats = stof(word);
            getline(s, word, ',');
            float caffeine = stof(word);
            getline(s, word, ',');
            float sw = stof(word);
            getline(s, word, ',');
            string sd = word;
            getline(s, word, ',');
            float sw2 = stof(word);
            getline(s, word, ',');
            string sd2 = word;
            getline(s, word, ',');
            float sw3 = stof(word);
            getline(s, word, ',');
            string sd3 = word;
            getline(s, word, ',');
            float sw4 = stof(word);
            getline(s, word, ',');
            string sd4 = word;
            getline(s, word, ',');
            float sw5 = stof(word);
            getline(s, word, ',');
            string sd5 = word;
            getline(s, word, ',');
            float sw6 = stof(word);
            getline(s, word, ',');
            string sd6 = word;
            getline(s, word, ',');
            float sw7 = stof(word);
            getline(s, word, ',');
            string sd7 = word;
            getline(s, word, ',');
            float sw8 = stof(word);
            getline(s, word, ',');
            string sd8 = word;
            getline(s, word, ',');
            float sw9 = stof(word);
            getline(s, word, ',');
            string sd9 = word;
            getline(s, word, ',');
            float twohundredcal_weight = stof(word);
            vector<float> v = { calories, protein, carbohydrates, sugars, fiber, cholesterol, saturated_fats, trans_fats, soluble_fiber, insoluble_fiber, monounsaturated_fats, polyunsaturated_fats, caffeine, sw, sw2, sw3, sw4, sw5, sw6, sw7, sw8, sw9, twohundredcal_weight };
            Food* ptr = new Food(name, make_pair(food_group, v));
            map->set(name, ptr);
            trie->insert(ptr);
        }
    }
    void removeNutritionUpdate(const string& name, float amount){
        calories -= map->get(name)->getValue().second[0] / 100 * amount;
        protein -= map->get(name)->getValue().second[1] / 100 * amount;
        fiber -= map->get(name)->getValue().second[2] / 100 * amount;
        insoluble_fiber -= map->get(name)->getValue().second[3] / 100 * amount;
        carbohydrates -= map->get(name)->getValue().second[4] / 100 * amount;
        sugars -= map->get(name)->getValue().second[5] / 100 * amount;
        soluble_fiber -= map->get(name)->getValue().second[6] / 100 * amount;
        cholesterol -= map->get(name)->getValue().second[7] / 100 * amount;
        saturated_fats -= map->get(name)->getValue().second[8] / 100 * amount;
        trans_fats -= map->get(name)->getValue().second[9] / 100 * amount;
        monounsaturated_fats -= map->get(name)->getValue().second[10] / 100 * amount;
        polyunsaturated_fats -= map->get(name)->getValue().second[11] / 100 * amount;
        caffeine -= map->get(name)->getValue().second[12] / 100 * amount;
    }
    void insert(const string& name, float amount = 100){
        int sizeHash = foodsHash.size();
        int sizeTrie = foodsTrie.size();

        auto start = chrono::high_resolution_clock::now();
        foodsHash.emplace_back(map->get(name), amount);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Time using the hashmap: " << duration.count() << " microseconds" << endl;
        start = chrono::high_resolution_clock::now();
        foodsTrie.emplace_back(trie->search(name), amount);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Time using the trie: " << duration.count() << " microseconds" << endl;
        if(sizeHash + 1 == foodsHash.size() && sizeTrie + 1== foodsTrie.size()){
            cout << "Insert Successful!" << endl << endl;
        }
        calories += map->get(name)->getValue().second[0] / 100 * amount;
        protein += map->get(name)->getValue().second[1] / 100 * amount;
        fiber += map->get(name)->getValue().second[2] / 100 * amount;
        insoluble_fiber += map->get(name)->getValue().second[3] / 100 * amount;
        carbohydrates += map->get(name)->getValue().second[4] / 100 * amount;
        sugars += map->get(name)->getValue().second[5] / 100 * amount;
        soluble_fiber += map->get(name)->getValue().second[6] / 100 * amount;
        cholesterol += map->get(name)->getValue().second[7] / 100 * amount;
        saturated_fats += map->get(name)->getValue().second[8] / 100 * amount;
        trans_fats += map->get(name)->getValue().second[9] / 100 * amount;
        monounsaturated_fats += map->get(name)->getValue().second[10] / 100 * amount;
        polyunsaturated_fats += map->get(name)->getValue().second[11] / 100 * amount;
        caffeine += map->get(name)->getValue().second[12] / 100 * amount;
    }
    void remove(const string& name, float amount = -1){
        for(int i = 0; i < foodsHash.size(); i++){
            if(foodsHash[i].first->getKey() == name){
                if(amount == -1) {
                    amount = foodsHash[i].second;
                    removeNutritionUpdate(name, amount);
                    foodsHash.erase(foodsHash.begin() + i);
                    foodsTrie.erase(foodsHash.begin() + i);
                }
                else if(amount <= 0){
                    cout << "Please input a valid amount to remove." << endl;
                }
                else if(foodsHash[i].second - amount == 0){
                    removeNutritionUpdate(name, amount);
                    foodsHash.erase(foodsHash.begin() + i);
                    foodsTrie.erase(foodsHash.begin() + i);
                }
                else{
                    foodsHash[i].second -= amount;
                    foodsTrie[i].second -= amount;
                    removeNutritionUpdate(name, amount);
                    if(foodsHash[i].second <= 0){
                        foodsHash.erase(foodsHash.begin() + i);
                        foodsTrie.erase(foodsHash.begin() + i);
                    }
                }
            }
        }
    }
    void displayFoodInRecipe(){
        for(int i = 0; i < foodsHash.size(); i++){
            cout << foodsHash[i].first->getKey() << ": " << foodsHash[i].second << "g" << endl;
        }
        cout << endl;
    }
    void displayNutrition() const{
        // cout <<
        cout << "Displaying nutritional information about the inputted recipe:" << endl;
        cout << "Total Calories: " << calories << " (g)" <<  endl;
        cout << "Total Protein: " << protein << " (g)"<< endl;
        cout << "Total Carbohydrates: " << carbohydrates << " (g)" << endl;
        cout << "Total Fiber: " << fiber << " (g)"<< endl;
        cout << "Total Sugar: " << sugars << " (g)" << endl;
        cout << "Total Insoluble Fiber: " << insoluble_fiber << " (g)"<< endl;
        cout << "Total Soluble Fiber: " << soluble_fiber << " (g)"<< endl;
        cout << "Total Caffeine: " << caffeine << " (mg)"<< endl;

        cout << "Total Trans Fats: " << trans_fats << " (g)" << endl;
        cout << "Total Polyunsaturated Fats: " << polyunsaturated_fats << " (mg)" << endl;
        cout << "Total Monounsaturated Fats: " << monounsaturated_fats << " (mg)"<< endl;
        cout << "Total Saturated Fats: " << saturated_fats << " (g)" << endl << endl;
    }
    void displayTen(const string& category, const string& nutrition, const string& comp){
        auto start = chrono::high_resolution_clock::now();
        map->tenValues(category, nutrition, comp);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "* Time using the hashmap: " << duration.count() << " milliseconds" << endl << endl;
        start = chrono::high_resolution_clock::now();
        trie->tenValues(category, nutrition, comp);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "* Time using the trie: " << duration.count() << " milliseconds" << endl << endl;

    }
    void search(const string& s){
        auto start = chrono::high_resolution_clock::now();
        map->search(s);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "* Time using the hashmap: " << duration.count() << " milliseconds" << endl << endl;
        start = chrono::high_resolution_clock::now();
        trie->searchForKey(s);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "* Time using the trie: " << duration.count() << " milliseconds" << endl << endl;
    }
};