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
#define VOCAB_SIZE 255
//47
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
            int index = (int)c;
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
            int index = (int)c;
            if(curr->next[index] == nullptr ){
                return nullptr;
            }
            curr = curr->next[index];
        }
        if(curr->isWord)
            return curr->food;
        return nullptr;
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