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
#include <iomanip>

class Recipe{
    vector<pair<Food*, float>> foodsHash; // hold two vectors to keep track of foods
    vector<pair<Food*, float>> foodsTrie;
    float calories = 0, fat = 0, protein = 0, fiber = 0, insoluble_fiber = 0, carbohydrates = 0, sugars = 0, soluble_fiber = 0, cholesterol = 0, saturated_fats = 0, trans_fats = 0, monounsaturated_fats = 0, polyunsaturated_fats = 0, alcohol = 0, caffeine = 0;
    HashMap* map; // recipe holds both of our data structures
    Trie* trie;
public:
    Recipe(){
        HashMap* map = new HashMap(); // create data structures dynamically
        Trie* trie = new Trie();
        this->map = map;
        this->trie = trie;
    }
    ~Recipe(){
        delete map;
        delete trie;
        for(int i = 0; i < foodsHash.size(); i++){
            foodsHash[i].first = nullptr; // when destructing, we don't want our pointers to point to random spaces
            foodsTrie[i].first = nullptr;
        }
    }
    void load(){
        fstream file;
        file.open("MyFoodData Nutrition Facts SpreadSheet Release 1.4.csv"); // open our csv file of our data
        string temp, line, word, code, description, nutrient_code;
        getline(file, line); // skips the first line that denotes the format of the csv
        while (getline(file, line)) { // get all the values
            stringstream s(line);
            getline(s, word, ',');
            string name = word;
            getline(s, word, ',');
            string food_group = word;
            getline(s, word, ',');
            float calories = stof(word);
            getline(s, word, ',');
            float fat = stof(word);
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
            float alcohol = stof(word);
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
            // after getting values, create a vector of floats of our numerical values
            vector<float> v = {calories, fat, protein, carbohydrates, sugars, fiber, cholesterol, saturated_fats, trans_fats, soluble_fiber, insoluble_fiber, monounsaturated_fats, polyunsaturated_fats, alcohol, caffeine};
            // create a vector of pairs for the listed preset serving sizes
            vector<pair<string, float>> servings = {make_pair(sd, sw), make_pair(sd2, sw2), make_pair(sd3, sw3), make_pair(sd4, sw4), make_pair(sd5, sw5), make_pair(sd6, sw6), make_pair(sd7, sw7), make_pair(sd8, sw8), make_pair(sd9, sw9)};
            // create a new food item dynamically and keep track of the pointer
            Food* ptr = new Food(name, make_pair(food_group, v), servings);
            // add this food to both data structures
            map->set(name, ptr);
            trie->insert(ptr);
        }
    }
    void removeNutritionUpdate(const string& name, float amount){ // updates the recipe's nutritional values on each remove
        calories -= map->get(name)->getValue().second[0] / 100 * amount;
        fat -= map->get(name)->getValue().second[1] / 100 * amount;
        protein -= map->get(name)->getValue().second[2] / 100 * amount;
        fiber -= map->get(name)->getValue().second[3] / 100 * amount;
        insoluble_fiber -= map->get(name)->getValue().second[4] / 100 * amount;
        carbohydrates -= map->get(name)->getValue().second[5] / 100 * amount;
        sugars -= map->get(name)->getValue().second[6] / 100 * amount;
        soluble_fiber -= map->get(name)->getValue().second[7] / 100 * amount;
        cholesterol -= map->get(name)->getValue().second[8] / 100 * amount;
        saturated_fats -= map->get(name)->getValue().second[9] / 100 * amount;
        trans_fats -= map->get(name)->getValue().second[10] / 100 * amount;
        monounsaturated_fats -= map->get(name)->getValue().second[11] / 100 * amount;
        polyunsaturated_fats -= map->get(name)->getValue().second[12] / 100 * amount;
        alcohol -= map->get(name)->getValue().second[13] / 100 * amount;
        caffeine -= map->get(name)->getValue().second[14] / 100 * amount;
    }
    void insert(const string& name, float amount = 100){
        bool inserted = false; // keep track of inserted to see if item is already in vector
        auto start = chrono::high_resolution_clock::now(); // start "stopwatch"
        Food* food = map->get(name); // find food in hashmap
        if(food != nullptr){ // check if food is found
            for(int i = 0; i < foodsHash.size(); i++){ // check if food is found in vector
                if(name == foodsHash[i].first->getKey()){
                    foodsHash[i].second += amount;
                    inserted = true;
                    break;
                }
            }
            if(!inserted){ // if not found in vector, but found in map
                foodsHash.emplace_back(food, amount); // add to vector
            }
        }
        auto stop = chrono::high_resolution_clock::now(); // stop "stopwatch"
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); // calculate time to execute
        inserted = false; // reset bool to keep track if the item is already in the vector
        start = chrono::high_resolution_clock::now();
        food = trie->search(name); // find the item in trie
        if(food != nullptr){ // if the item is found in the tree
            for(int i = 0; i < foodsTrie.size(); i++){
                if(name == foodsTrie[i].first->getKey()){ // if the item is found in the vector already
                    foodsTrie[i].second += amount;
                    inserted = true;
                    break;
                }
            }
            if(!inserted){ // if foudn in the trie, but not in the vector
                foodsTrie.emplace_back(food, amount);
                inserted = true;
            }
        }
        stop = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Time using the hashmap: " << duration.count() << " microseconds" << endl;
        cout << "Time using the trie: " << duration2.count() << " microseconds" << endl;
        if(inserted){
            cout << "Insert Successful!" << endl << endl;
        }
        else{
            cout << "Insert Failed! Please enter the exact key!" << endl;
            return;
        }
        // update the recipe's nutritional values
        Food* ptr = map->get(name);
        calories += ptr->getValue().second[0] / 100 * amount;
        fat += ptr->getValue().second[1] / 100 * amount;
        protein += ptr->getValue().second[2] / 100 * amount;
        fiber += ptr->getValue().second[3] / 100 * amount;
        insoluble_fiber += ptr->getValue().second[4] / 100 * amount;
        carbohydrates += ptr->getValue().second[5] / 100 * amount;
        sugars += ptr->getValue().second[6] / 100 * amount;
        soluble_fiber += ptr->getValue().second[7] / 100 * amount;
        cholesterol += ptr->getValue().second[8] / 100 * amount;
        saturated_fats += ptr->getValue().second[9] / 100 * amount;
        trans_fats += ptr->getValue().second[10] / 100 * amount;
        monounsaturated_fats += ptr->getValue().second[11] / 100 * amount;
        polyunsaturated_fats += ptr->getValue().second[12] / 100 * amount;
        alcohol += ptr->getValue().second[13] / 100 * amount;
        caffeine += ptr->getValue().second[14] / 100 * amount;
    }
    void remove(const string& name, float amount = -1){
        for(int i = 0; i < foodsHash.size(); i++){
            if(foodsHash[i].first->getKey() == name){
                if(amount == -1) { // if no amount is specified, completely remove from the vector
                    amount = foodsHash[i].second;
                    removeNutritionUpdate(name, amount); // update the nutritional values
                    foodsHash.erase(foodsHash.begin() + i); // remove the item from the vectors
                    foodsTrie.erase(foodsTrie.begin() + i);
                    cout << "Remove Successful!" << endl;
                }
                else if(amount <= 0){
                    cout << "Please input a valid amount to remove." << endl; // amount can't be less than or equal to 0
                }
                else if(foodsHash[i].second - amount == 0){ // if users choose the exact amount that is in the vector
                    removeNutritionUpdate(name, amount); // completely remove agan
                    foodsHash.erase(foodsHash.begin() + i);
                    foodsTrie.erase(foodsTrie.begin() + i);
                    cout << "Remove Successful!" << endl;
                }
                else{ // if the amount is less than the amount in the vector
                    foodsHash[i].second -= amount; // remove the amount specified
                    foodsTrie[i].second -= amount;
                    removeNutritionUpdate(name, amount); // update the nutritional values
                    if(foodsHash[i].second <= 0){
                        foodsHash.erase(foodsHash.begin() + i);
                        foodsTrie.erase(foodsTrie.begin() + i);
                    }
                    cout << amount << "(g) Successfully Removed!" << endl;
                }
                return;
            }
        }
        cout << name << " not found in recipe. Please enter the exact key" << endl;
    }
    void displayFoodInRecipe(){
        if(foodsHash.empty()){
            cout << "No food currently in recipe!" << endl;
            return;
        }
        for(int i = 0; i < foodsHash.size(); i++){ // display items in vector with their amounts
            cout << foodsHash[i].first->getKey() << ": " << foodsHash[i].second << "g" << endl;
        }
        cout << endl;
    }
    void displayNutrition() const{ // display the nutritional values of the inputted recipe
        cout << "Displaying nutritional information about the inputted recipe:" << endl;
        cout << "Total Calories: " << calories << " Cal" <<  endl;
        cout << "Total Protein: " << protein << " (g)"<< endl;
        cout << "Total Fat: " << fat << " (g)" << endl;
        cout << "Total Carbohydrates: " << carbohydrates << " (g)" << endl;
        cout << "Total Fiber: " << fiber << " (g)"<< endl;
        cout << "Total Sugars: " << sugars << " (g)" << endl;
        cout << "Total Insoluble Fiber: " << insoluble_fiber << " (g)"<< endl;
        cout << "Total Soluble Fiber: " << soluble_fiber << " (g)"<< endl;
        cout << "Total Caffeine: " << caffeine << " (mg)"<< endl;
        cout << "Total Alcohol: " << alcohol << " (g)"<< endl;

        cout << "Total Cholesterol: " << cholesterol << " (mg)"<< endl;

        cout << "Total Trans Fats: " << trans_fats << " (g)" << endl;
        cout << "Total Polyunsaturated Fats: " << polyunsaturated_fats << " (mg)" << endl;
        cout << "Total Monounsaturated Fats: " << monounsaturated_fats << " (mg)"<< endl;
        cout << "Total Saturated Fats: " << saturated_fats << " (g)" << endl << endl;
    }
    void displayTen(const string& category, const string& nutrition, const string& comp){ // keep track of time taken
        auto start = chrono::high_resolution_clock::now(); // and use find ten value functions of both ds
        map->tenValues(category, nutrition, comp);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        start = chrono::high_resolution_clock::now();
        trie->tenValues(category, nutrition, comp);
        stop = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "* Time using the hashmap: " << duration.count() << " milliseconds" << endl;
        cout << "* Time using the trie: " << duration2.count() << " milliseconds" << endl << endl;

    }
    void search(const string& s){ // keep track of time taken and use search functions for both map and trie
        auto start = chrono::high_resolution_clock::now();
        map->search(s);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "* Time using the hashmap: " << duration.count() << " milliseconds" << endl << endl;
        start = chrono::high_resolution_clock::now();
        trie->searchForKey(s);
        stop = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "* Time using the hashmap: " << duration.count() << " milliseconds" << endl << endl;
        cout << "* Time using the trie: " << duration2.count() << " milliseconds" << endl << endl;
    }
    void getServingSizes(const string& s){ // get the serving sizes of the food
        Food* food = map->get(s);
        if(food != nullptr){
            food->showServingSizes();
        }
    }
};