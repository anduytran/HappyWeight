#include "recipe.h"
//
// Created by Dylan on 4/9/2024.
//

using namespace std;


int main() {
    Recipe recipe;
    recipe.load();
    recipe.insert("Salisbury Steak With Gravy Whipped Potatoes Vegetable Dessert Frozen Meal");
    recipe.insert("Spinach Cooked From Canned Made With Oil");
    recipe.displayFoodInRecipe();
    recipe.displayNutrition();
    recipe.displayTen("Meats", "Protein", "Highest");


    /*
    map.tenLowest("Meats", "Calories");
    map.tenHighest("Meats", "Protein");
    cout << map.get("Pork Cured Bacon Cooked Microwaved")->getKey() << ": " << map.get("Pork Cured Bacon Cooked Microwaved")->getValue().second[1] << endl;
    trie.tenHighest("Meats", "Calories", "Highest");
     */

    return 0;
}
