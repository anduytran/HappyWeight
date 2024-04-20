//
// Created by Dylan on 4/16/2024, Julio contributed on this file
//
#pragma once
#ifndef TESTING_TRIE2_H
#define TESTING_TRIE2_H
#include <iostream>
#include <queue>
#include "food.h"
using namespace std;
#define VOCAB_SIZE 50

struct TrieNode{
    char character;
    Food* food;
    vector<TrieNode*> next;
    bool isWord = false;
    TrieNode(){
        next = vector<TrieNode*>(VOCAB_SIZE, nullptr);
        isWord = false;
    }
};

struct PQCompare {
    bool operator()(const pair<string, float>& p1, const pair<string, float>& p2) const {
        return p1.second > p2.second;
    }
};

class Trie{
    using PriorityQueue = priority_queue<pair<string, float>, vector<pair<string, float>>, PQCompare>;
    TrieNode* root;
    int item_count = 0;

public:

    Trie(){
        root = new TrieNode();
    }
    ~Trie(){

    }
    void cleanUp(TrieNode* ptr) {
        if (ptr == nullptr) {
            return;
        }
        for (int i = 0; i < VOCAB_SIZE; i++) {
            cleanUp(ptr->next[i]);
            if (ptr->next[i] != nullptr) {
                delete ptr->next[i];
            }
        }
    }
    void insert(Food*& food) {
        TrieNode *curr = root;
        string name = food->getKey(); // Fruits
        for (char i : name) {
            char c = tolower(i);
            int index = c - 'a';
            if (-65 <= index && index <= -63) {
                index += 91; // index 26 - 28
            }
            else if (-60 <= index && index <= -56) { // '%'
                index += 89; // index 29 - 33
            }

            else if (-52 <= index && index <= -38) { // '-'
                index += 86; // index 34 - 47
            }
            else if (index == -54) {
                index = 49;
            }
            if(curr->next[index] == nullptr){
                curr->next[index] = new TrieNode();
                curr->next[index]->character = c;
            }
            curr = curr->next[index];
        }
        curr->isWord = true;
        item_count++;
        curr->food = food;
    }

    Food* search(string word){
        TrieNode *curr = root;
        for (char i : word) {
            char c = tolower(i);
            int index = c - 'a';
            if (-65 <= index && index <= -63) {
                index += 91; // index 26 - 28
            }
            else if (-60 <= index && index <= -56) { // '%'
                index += 89; // index 29 - 33
            }

            else if (-52 <= index && index <= -38) { // '-'
                index += 86; // index 34 - 47
            }
            else if (index == -54) {
                index = 49;
            }
            if(curr->next[index] == nullptr){
                return nullptr;
            }
            curr = curr->next[index];
        }
        if(curr->isWord) {
            return curr->food;
        }
        else{
            return nullptr;
        }
    }

    void iterate(TrieNode* ptr, vector<pair<string, float>> &temp, const string& category, const string& nutrition, const string& comp){
        if(ptr == nullptr){
            return;
        }
        int n;
        if(nutrition == "Calories"){
            n = 0;
        } else if(nutrition == "Protein"){
            n = 1;
        } else if(nutrition == "Carbohydrates"){
            n = 2;
        } else if(nutrition == "Sugars"){
            n = 3;
        } else if(nutrition == "Fiber"){
            n = 4;
        } else if(nutrition == "Cholesterol"){
            n = 5;
        } else if(nutrition == "Saturated Fats"){
            n = 6;
        } else if(nutrition == "Trans Fatty Acids"){
            n = 7;
        } else if(nutrition == "Soluble Fiber"){
            n = 8;
        } else if(nutrition == "Insoluble Fiber"){
            n = 9;
        } else if(nutrition == "Monounsaturated Fats"){
            n = 10;
        } else if(nutrition == "Polyunsaturated Fats"){
            n = 11;
        } else if(nutrition == "Caffeine") {
            n = 12;
        } else{
            cout << "Not Valid" << endl;
            return;
        }
        for(int i = 0; i < VOCAB_SIZE; i++){
            iterate(ptr->next[i], temp, category, nutrition, comp);
            if(ptr->next[i] != nullptr){
                if(ptr->next[i]->isWord && category == ptr->next[i]->food->getValue().first){
                    float val = ptr->next[i]->food->getValue().second[n];
                    if(val < 0){
                        continue;
                    }
                    if (temp.size() < 10) {
                        temp.emplace_back(ptr->next[i]->food->getKey(), val);
                        if (temp.size() == 10) {
                            if(comp == "Lowest"){
                                sort(temp.begin(), temp.end(), sortbysecondlt);
                            }
                            else if(comp == "Highest"){
                                sort(temp.begin(), temp.end(), sortbysecondgt);
                            }
                        }
                    } else {
                        if (val > temp.back().second && val > 0 && comp == "Highest") {
                            temp.pop_back();
                            temp.emplace_back(ptr->next[i]->food->getKey(), val);
                            sort(temp.begin(), temp.end(), sortbysecondgt);
                        }else if(val < temp.back().second && val > 0 && comp == "Lowest"){
                            temp.pop_back();
                            temp.emplace_back(ptr->next[i]->food->getKey(), val);
                            sort(temp.begin(), temp.end(), sortbysecondlt);
                        }
                    }
                }
            }
        }
    }
    void tenHighest(const string& category, const string& nutrition, const string& comp) {
        vector<pair<string, float>> temp;
        TrieNode* ptr = root;
        iterate(ptr, temp, category, nutrition, comp);
        if(comp == "Lowest"){
            sort(temp.begin(), temp.end(), sortbysecondlt);
        }
        else{
            sort(temp.begin(), temp.end(), sortbysecondgt);
        }
        cout << "The 10 foods with the highest calorie values are: " << endl;
        for (int i = 0; i < temp.size(); i++) {
            cout << i + 1 << ". " << temp[i].first << ": " << temp[i].second << endl;
        }
    }
    void findTop10Calories(TrieNode* root, PriorityQueue &PQ, const string& category){
        if(root == nullptr){
            return;
        }
        for(int i = 0; i < VOCAB_SIZE; i++){
            if( root -> next[i] != nullptr){
                if(root -> next[i] -> isWord && category == root -> next[i] -> food -> getValue().first){
                    float norm_cal = root -> next[i] -> food -> getValue().second[0];
                    if(norm_cal < 0){
                        continue;
                    }
                    PQ.push(make_pair(root->next[i]->food->getKey(), norm_cal));
                    if( PQ.size() > 10){
                        PQ.pop();
                    }
                }
                findTop10Calories(root -> next[i], PQ, category);
            }
        }
    }
    void tenHighestCalorie(const string& category){
        PriorityQueue PQ;
        findTop10Calories(root, PQ, category);
        cout << "The 10 foods with the highest calorie values are: " << endl;
        vector<pair<string, float>> top10;
        while(!PQ.empty()){
            top10.push_back(PQ.top());
            PQ.pop();
        }
        for (int i = top10.size() - 1, j = 1; i >= 0; i--, j++) {
            cout << j << ". " << top10[i].first << ": " << top10[i].second << endl;
        }
    }
};
#endif //TESTING_TRIE_H