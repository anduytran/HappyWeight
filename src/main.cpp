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
    recipe.remove("Spinach Cooked From Canned Made With Oil");
    recipe.displayFoodInRecipe();
    recipe.displayNutrition();
    // recipe.displayTen("Restaurant Foods", "Calories", "Largest");
    // recipe.search("poop");

    return 0;
}
