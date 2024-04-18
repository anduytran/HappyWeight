//
// Created by Dylan on 4/16/2024, Julio contributed on this file
//
#pragma once
#ifndef TESTING_TRIE2_H
#define TESTING_TRIE2_H
#include <iostream>
#include "food.h"
using namespace std;
#define VOCAB_SIZE 47

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

class Trie{
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
            if(index == -65 || index == -64) {
                index += 91; // index 26 and 27
            }
            else if(-60 <= index && index <= -56){ // '%'
                index += 88; // index 28 - 32
            }

            else if(-52 <= index  && index <= -39){ // '-'
                index += 85; // index 33 - 46
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
        for (char i : word){
            char c = tolower(i);
            int index = c - 'a';
            if(index == -65 || index == -64) {
                index += 91; // index 26 and 27
            }
            else if(-60 <= index && index <= -56){ // '%'
                index += 88; // index 28 - 32
            }
            else if(-52 <= index  && index <= -39){ // '-'
                index += 85; // index 33 - 46
            }
            if(curr->next[index] == nullptr ){
                return nullptr;
            }
            curr = curr->next[index];
        }
        if(curr->isWord)
            return curr->food;
        return nullptr;
    }
    void iterate(TrieNode* ptr, vector<pair<string, float>> &temp, const string& category){
        if(ptr == nullptr){
            return;
        }
        for(int i = 0; i < VOCAB_SIZE; i++){
            iterate(ptr->next[i], temp, category);
            if(ptr->next[i] != nullptr){
                if(ptr->next[i]->isWord && category == ptr->next[i]->food->getValue().first){
                    float norm_cal = ptr->next[i]->food->getValue().second[0];
                    if(norm_cal < 0){
                        continue;
                    }
                    if (temp.size() < 10) {
                        temp.emplace_back(ptr->next[i]->food->getKey(), norm_cal);
                        if (temp.size() == 10) {
                            sort(temp.begin(), temp.end(), sortbysecondgt);
                        }
                    } else {
                        if (norm_cal > temp.back().second && norm_cal > 0) {
                            temp.pop_back();
                            temp.emplace_back(ptr->next[i]->food->getKey(), norm_cal);
                            sort(temp.begin(), temp.end(), sortbysecondgt);
                        }
                    }
                }
            }
        }
    }
    void tenHighestCalorie(const string& category) {
        vector<pair<string, float>> temp;
        TrieNode* ptr = root;
        iterate(ptr, temp, category);
        sort(temp.begin(), temp.end(), sortbysecondgt);
        cout << "The 10 foods with the highest calorie values are: " << endl;
        for (int i = 0; i < temp.size(); i++) {
            cout << i + 1 << ". " << temp[i].first << ": " << temp[i].second << endl;
        }
    }
};
#endif //TESTING_TRIE_H