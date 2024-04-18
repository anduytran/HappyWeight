#include "hashmap.h"
#include "trie.h"
//
// Created by Dylan on 4/9/2024.
//
#include <iostream>
#include <unordered_map>

using namespace std;

void load(HashMap &hashmap, Trie &trie){
    fstream file;
    file.open("MyFoodData Nutrition Facts SpreadSheet Release 1.4 - SR Legacy and FNDDS.csv", ios::in | ios::app);
    string temp, line, word, code, description, nutrient_code;
    getline(file, temp);
    getline(file, temp);
    getline(file, temp);
    getline(file, temp);
    while(getline(file, line)){
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
        vector<float> v = {calories, protein, carbohydrates, sugars, fiber, cholesterol, saturated_fats, trans_fats, soluble_fiber, insoluble_fiber, monounsaturated_fats, polyunsaturated_fats, caffeine, sw, sw2, sw3, sw4, sw5, sw6, sw7, sw8, sw9, twohundredcal_weight};
        Food* ptr = new Food(name, make_pair(food_group, v));
        hashmap[name] = ptr;
        trie.insert(ptr);
    }
}

int main() {
    HashMap map;
    Trie trie;
    load(map, trie);
    map.tenLowest("Meats", "Calories");
    map.tenHighest("Meats", "Protein");
    cout << map.get("Pork Cured Bacon Cooked Microwaved")->getKey() << ": " << map.get("Pork Cured Bacon Cooked Microwaved")->getValue().second[1] << endl;
    trie.tenHighestCalorie("Meats");
    return 0;
}
