#include "recipe.h"
//
// Created by Dylan on 4/9/2024. Anya contributed on this file.
//

using namespace std;

void option(){
    cout << fixed << setprecision(2);
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
        cout << "Which category of food would you like to display? (Please type in the exact string)" << endl;
        cout << setw(25) << "1. American Indian\t\t2. Baby Foods\t\t3. Baked Foods\n"<< setw(25) <<"4. Beans and Lentils\t\t5. Beverages\t\t6. Breakfast Cereal"<< setw(25) <<"\n7. Dairy and Egg Products\t8. Fast Foods\t\t9. Fats and Oils"<< setw(25) <<"\n10. Fish\t\t\t11. Fruits\t\t12. Grains and Pasta"<< setw(25) <<"\n13. Meats\t\t\t14. Nuts and Seeds\t15. Prepared Meals"<< setw(25) <<"\n16. Restaurant Foods\t\t17. Snacks\t\t"<< setw(25) <<"18. Soups and Sauces\n19. Spices and Herbs\t\t20. Sweets\t\t"<< "21. Vegetables" << endl <<"22. All" << endl;
        getline(cin, category);
        string nutrition;

        cout << "Which nutrition type would you like the 10 highest values for? (Please type in the exact string)" << endl;
        cout << setw(25)<< "1. Calories\t\t2. Protein\t\t\t\t3. Carbohydrates\n4. Sugars\t\t5. Fiber\t\t\t\t6. Cholesterol\n7. Saturated Fats\t8. Trans Fatty acids\t\t\t9. Soluble Fiber\n10. Insoluble Fiber\t11. Fatty Acids Total (monounsaturated)\t12. Fatty Acids Total (polyunsaturated)\n13. Caffeine" << endl;
        getline(cin, nutrition);

        recipe.displayTen(category, nutrition, n);
    }
    if(input == 2){
        string n = "Lowest";
        string category;
        cout << "Which category of food would you like to display? (Please type in the exact string)" << endl;
        cout << setw(25) << "1. American Indian\t\t2. Baby Foods\t\t3. Baked Foods\n"<< setw(25) <<"4. Beans and Lentils\t\t5. Beverages\t\t6. Breakfast Cereal"<< setw(25) <<"\n7. Dairy and Egg Products\t8. Fast Foods\t\t9. Fats and Oils"<< setw(25) <<"\n10. Fish\t\t\t11. Fruits\t\t12. Grains and Pasta"<< setw(25) <<"\n13. Meats\t\t\t14. Nuts and Seeds\t15. Prepared Meals"<< setw(25) <<"\n16. Restaurant Foods\t\t17. Snacks\t\t"<< setw(25) <<"18. Soups and Sauces\n19. Spices and Herbs\t\t20. Sweets\t\t"<< "21. Vegetables" << endl <<"22. All" << endl;
        getline(cin, category);

        string nutrition;

        cout << "\nWhich nutrition type would you like the 10 lowest values for? (Please type in the exact string)" << endl;
        cout << setw(25)<< "1. Calories\t\t2. Protein\t\t\t\t3. Carbohydrates\n4. Sugars\t\t5. Fiber\t\t\t\t6. Cholesterol\n7. Saturated Fats\t8. Trans Fatty acids\t\t\t9. Soluble Fiber\n10. Insoluble Fiber\t11. Fatty Acids Total (monounsaturated)\t12. Fatty Acids Total (polyunsaturated)\n13. Caffeine" << endl;
        getline(cin, nutrition);

        recipe.displayTen(category, nutrition, n);
    }
    if(input == 3){
        int opt;
        bool trigger = true;
        cout << "Welcome to our recipe maker!" << endl;
        cout << "Please choose an option 1-6." << endl;
        while(trigger) {
            cout << setw(10) << "1. Search\t2. Insert\t3. Remove\n" << setw(25) << "4. Display Nutrition Facts\t5. Display Food in Recipe \t6. Exit" << endl;
            cin >> opt;
            cin.ignore();

            if(opt == 1){
                //search
                string s;
                cout << "Please enter a food item: " << endl;
                getline(cin, s);
                recipe.search(s);
            }
            if(opt == 2){
                //insert
                string s;
                int choice = 0;
                cout << "What would you like to add to your recipe?" << endl;
                getline(cin, s);
                cout << "Would you like to choose from the preset serving sizes? Please choose an option 1-2. \n1. Yes\t2. No" << endl;
                cin >> choice;
                cin.ignore();
                if(choice == 1){
                    recipe.getServingSizes(s);
                }
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
                int choice;
                cout << "What would you like to remove from your recipe?" << endl;
                getline(cin, s);
                cout << "Would you like to choose from the preset serving sizes? \n1. Yes\t2. No" << endl;
                cin >> choice;
                cin.ignore();
                if(choice == 1){
                    recipe.getServingSizes(s);
                }
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
                recipe.displayFoodInRecipe();
            }
            if(opt == 6){
                trigger = false;
            }
        }
    }
}

int main() {
    option();

    return 0;
}
