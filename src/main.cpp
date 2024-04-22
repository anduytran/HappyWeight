#include "recipe.h"
//
// Created by Dylan on 4/9/2024.
//

using namespace std;

void option(){
    Recipe recipe;
    recipe.load();
    int input;

    cout << "Hello! Please choose an option 1-3." << endl;
    cout << "1. Show 10 Highest Foods (calories, protein, fiber, etc.)\n2. Show 10 Lowest Foods (calories, protein, fiber, etc.)\n3. Create a Recipe" << endl;

    cin >> input;
    cin.ignore();
    if(input == 1){
        string n = "Highest";
        string category;
        cout << setw(25) << "\n1. American Indian\t2. Baby Foods\t3. Baked Foods\n"<< setw(25) <<"4. Beans and Lentils\t5. Beverages\t6. Breakfast Cereal"<< setw(25) <<"\n7. Dairy and Egg Products\t8. Fast Foods\t9. Fats and Oils"<< setw(25) <<"\n10. Fish\t11. Fruits\t12. Grains and Pasta"<< setw(25) <<"\n13. Meats\t14. Nuts and Seeds\t15. Prepared Meals"<< setw(25) <<"\n16. Restaurant Foods\t17. Sandwich\t18. Snacks"<< setw(25) <<"\n19. Soups and Sauces\t20. Spices and Herbs\t21. Sweets"<< setw(25) <<"\n22. Vegetables\t23. Yogurt" << endl;
        cout << "Which category would you like to display? " << endl;
        getline(cin, category);
        cout << "\nPlease enter the name: " << category;

        string nutrition;

        cout << "\nWhich nutrition type would you like the 10 highest for? " << endl;
        cout << setw(25)<< "1. Calories\t2. Protein\t3. Carbohydrates\n4. Sugars\t5. Fiber\t6. Cholesterol\n7. Saturated Fats\t8. Trans Fatty acids\t9. Soluble Fiber\n10. Insoluble Fiber\t11. Fatty Acids Total (monounsaturated)\t 12. Fatty Acids Total (polyunsaturated)\n 13. Caffeine" << endl;
        getline(cin, nutrition);
        cout << "Please enter the name: " << nutrition;

        recipe.displayTen(category, nutrition, n);
    }
    if(input == 2){
        string n = "Lowest";
        string category;
        cout << setw(25) << "\n1. American Indian\t2. Baby Foods\t3. Baked Foods\n"<< setw(25) <<"4. Beans and Lentils\t5. Beverages\t6. Breakfast Cereal"<< setw(25) <<"\n7. Dairy and Egg Products\t8. Fast Foods\t9. Fats and Oils"<< setw(25) <<"\n10. Fish\t11. Fruits\t12. Grains and Pasta"<< setw(25) <<"\n13. Meats\t14. Nuts and Seeds\t15. Prepared Meals"<< setw(25) <<"\n16. Restaurant Foods\t17. Sandwich\t18. Snacks"<< setw(25) <<"\n19. Soups and Sauces\t20. Spices and Herbs\t21. Sweets"<< setw(25) <<"\n22. Vegetables\t23. Yogurt" << endl;
        cout << "Which category would you like to display? " << endl;
        getline(cin, category);
        cout << "\nPlease enter the name: " << category;

        string nutrition;

        cout << "\nWhich nutrition type would you like the 10 highest for? " << endl;
        cout << setw(25)<< "1. Calories\t2. Protein\t3. Carbohydrates\n4. Sugars\t5. Fiber\t6. Cholesterol\n7. Saturated Fats\t8. Trans Fatty acids\t9. Soluble Fiber\n10. Insoluble Fiber\t11. Fatty Acids Total (monounsaturated)\t 12. Fatty Acids Total (polyunsaturated)\n 13. Caffeine" << endl;
        getline(cin, nutrition);
        cout << "Please enter the name: " << nutrition;

        recipe.displayTen(category, nutrition, n);
    }
    if(input == 3){
        int opt;
        bool trigger = true;
        cout << "Welcome to our recipe maker!" << endl;
        cout << "Please choose an option 1-4." << endl;
        while(trigger) {
            cout << setw(10) << "1. Search\t2. Insert\n3. Remove\t" << setw(25) << "4. Display Nutrition Facts\t5. Exit" << endl;
            cin >> opt;
            cin.ignore();

            if(opt == 1){
                //search
                string s;
                cout << "Please enter a food item: ";
                getline(cin, s);
                recipe.search(s);
            }
            if(opt == 2){
                //insert
                string s;
                cout << "What would you like to add to your recipe?" << endl;
                getline(cin, s);
                cout << "How many grams of this would you like to add?" << endl;
                float grams;
                cin >> grams;
                cin.ignore();
                while (grams <= 0){
                    cout << "Please enter a valid amount.";
                    cin >> grams;
                    cin.ignore();
                }
                recipe.insert(s, grams);
            }
            if(opt == 3){
                //remove
                string s;
                cout << "What would you like to remove from your recipe?" << endl;
                getline(cin, s);
                cout << "How many grams of this would you like to remove?" << endl;
                float grams;
                cin >> grams;
                cin.ignore();
                while (grams <= 0){
                    cout << "Please enter a valid amount.";
                    cin >> grams;
                    cin.ignore();
                }
                recipe.remove(s, grams);
            }
            if(opt == 4){
                //display nutrition facts
                recipe.displayNutrition();
            }
            if(opt == 5){
                trigger = false;
            }
        }
    }
}

int main() {
    /*Recipe recipe;
    recipe.load();
    recipe.insert("Salisbury Steak With Gravy Whipped Potatoes Vegetable Dessert Frozen Meal");
    recipe.insert("Spinach Cooked From Canned Made With Oil");
    recipe.displayFoodInRecipe();
    recipe.displayNutrition();
    recipe.remove("Spinach Cooked From Canned Made With Oil");
    recipe.displayFoodInRecipe();
    recipe.displayNutrition();*/
    // recipe.displayTen("Restaurant Foods", "Calories", "Largest");
    // recipe.search("poop");

    option();

    return 0;
}
