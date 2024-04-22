#include "recipe.h"
//
// Created by Dylan on 4/9/2024. Anya contributed on this file.
//

using namespace std;

void option(){
    cout << fixed << setprecision(2);
    //load recipe class
    Recipe recipe;
    recipe.load();
    int input;

    //ask for first menu option
    cout << "Hello! Please choose an option 1-3." << endl;
    cout << "1. Show 10 Highest Foods (calories, protein, fiber, etc.)\n2. Show 10 Lowest Foods (calories, protein, fiber, etc.)\n3. Create a Recipe" << endl;
    //get user input
    cin >> input;
    cin.ignore();

    //if user chooses 10 highest foods
    if(input == 1){
        string n = "Highest";
        string category;
        //prompt for category
        cout << "Which category of food would you like to display? (Please type in the exact string)" << endl;
        cout << setw(25) << "1. American Indian\t\t2. Baby Foods\t\t3. Baked Foods\n"<< setw(25) <<"4. Beans and Lentils\t\t5. Beverages\t\t6. Breakfast Cereal"<< setw(25) <<"\n7. Dairy and Egg Products\t8. Fast Foods\t\t9. Fats and Oils"<< setw(25) <<"\n10. Fish\t\t\t11. Fruits\t\t12. Grains and Pasta"<< setw(25) <<"\n13. Meats\t\t\t14. Nuts and Seeds\t15. Prepared Meals"<< setw(25) <<"\n16. Restaurant Foods\t\t17. Snacks\t\t"<< setw(25) <<"18. Soups and Sauces\n19. Spices and Herbs\t\t20. Sweets\t\t"<< "21. Vegetables" << endl <<"22. All" << endl;
        getline(cin, category);
        string nutrition;
        //prompt for nutrition
        cout << "Which nutrition type would you like the 10 highest values for? (Please type in the exact string)" << endl;
        cout << setw(25)<< "1. Calories\t\t2. Protein\t\t\t\t3. Carbohydrates\n4. Sugars\t\t5. Fiber\t\t\t\t6. Cholesterol\n7. Saturated Fats\t8. Trans Fatty acids\t\t\t9. Soluble Fiber\n10. Insoluble Fiber\t11. Fatty Acids Total (monounsaturated)\t12. Fatty Acids Total (polyunsaturated)\n13. Caffeine" << endl;
        getline(cin, nutrition);
        //call function to display 10 highest
        recipe.displayTen(category, nutrition, n);
    }
    //if user chooses 10 lowest foods
    if(input == 2){
        string n = "Lowest";
        string category;
        //prompt for category
        cout << "Which category of food would you like to display? (Please type in the exact string)" << endl;
        cout << setw(25) << "1. American Indian\t\t2. Baby Foods\t\t3. Baked Foods\n"<< setw(25) <<"4. Beans and Lentils\t\t5. Beverages\t\t6. Breakfast Cereal"<< setw(25) <<"\n7. Dairy and Egg Products\t8. Fast Foods\t\t9. Fats and Oils"<< setw(25) <<"\n10. Fish\t\t\t11. Fruits\t\t12. Grains and Pasta"<< setw(25) <<"\n13. Meats\t\t\t14. Nuts and Seeds\t15. Prepared Meals"<< setw(25) <<"\n16. Restaurant Foods\t\t17. Snacks\t\t"<< setw(25) <<"18. Soups and Sauces\n19. Spices and Herbs\t\t20. Sweets\t\t"<< "21. Vegetables" << endl <<"22. All" << endl;
        getline(cin, category);

        string nutrition;
        //prompt for nutrition type
        cout << "\nWhich nutrition type would you like the 10 lowest values for? (Please type in the exact string)" << endl;
        cout << setw(25)<< "1. Calories\t\t2. Protein\t\t\t\t3. Carbohydrates\n4. Sugars\t\t5. Fiber\t\t\t\t6. Cholesterol\n7. Saturated Fats\t8. Trans Fatty acids\t\t\t9. Soluble Fiber\n10. Insoluble Fiber\t11. Fatty Acids Total (monounsaturated)\t12. Fatty Acids Total (polyunsaturated)\n13. Caffeine" << endl;
        getline(cin, nutrition);
        //call function for the 10 lowest foods
        recipe.displayTen(category, nutrition, n);
    }
    //if user chooses to create a recipe
    if(input == 3){
        int opt;
        //boolean for while loop
        bool trigger = true;
        cout << "Welcome to our recipe maker!" << endl;
        cout << "Please choose an option 1-6." << endl;
        while(trigger) {
            //display recipe making options
            cout << setw(10) << "1. Search\t2. Insert\t3. Remove\n" << setw(25) << "4. Display Nutrition Facts\t5. Display Food in Recipe \t6. Exit" << endl;
            cin >> opt;
            cin.ignore();
            //if user chooses to search for specific foods available in catalog
            if(opt == 1){
                //search
                string s;
                cout << "Please enter a food item: ";
                getline(cin, s);
                //call fucntion to search for specific food in catalog
                recipe.search(s);
            }
            //if user chooses to insert food into recipe
            if(opt == 2){
                //insert
                string s;
                int choice = 0;
                //prompt for ingredient/food type
                cout << "What would you like to add to your recipe?" << endl;
                getline(cin, s);
                //prompt for a specific serving size
                cout << "Would you like to choose from the preset serving sizes? \n1. Yes\t2. No" << endl;
                cin >> choice;
                cin.ignore();
                //if user chooses specific serving size get the rationale
                if(choice == 1){
                    recipe.getServingSizes(s);
                }
                //prompt user for any specific amount of grams for that food item
                cout << "How many grams of this would you like to add?" << endl;
                float grams;
                cin >> grams;
                cin.ignore();
                //grams cannot be <= 0
                //if user enters <=0 for grams
                while (grams <= 0){
                    cout << "Please enter a valid amount.";
                    cin >> grams;
                    cin.ignore();
                }
                //continue to insert the ingredient/food into recipe
                recipe.insert(s, grams);
            }
            //if user chooses to remove an ingredient from recipe
            if(opt == 3){
                //remove
                string s;
                int choice;
                //prompt for while item they would like to delete
                cout << "What would you like to remove from your recipe?" << endl;
                getline(cin, s);
                //how many serving sizes would they like to remove from recipe
                cout << "Would you like to choose from the preset serving sizes? \n1. Yes\t2. No" << endl;
                cin >> choice;
                cin.ignore();
                //find rationale of serving size
                if(choice == 1){
                    recipe.getServingSizes(s);
                }
                //prompt user for how many grams they would like to remove
                cout << "How many grams of this would you like to remove?" << endl;
                float grams;
                cin >> grams;
                cin.ignore();
                //ensure grams entered is > 0
                while (grams <= 0){
                    cout << "Please enter a valid amount.";
                    cin >> grams;
                    cin.ignore();
                }
                //remove the item from recipe based off previous input
                recipe.remove(s, grams);
            }
            //if user chooses to display recipe nutrition facts
            if(opt == 4){
                //display nutrition facts
                recipe.displayNutrition();
            }
            //if user chooses to display the food in their current recipe
            if(opt == 5){
                recipe.displayFoodInRecipe();
            }
            //if user decides to exit the program
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
