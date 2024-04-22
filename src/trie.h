//
// Created by Dylan on 4/16/2024, Julio contributed on this file
//
#pragma once
#ifndef TESTING_TRIE2_H
#define TESTING_TRIE2_H
#include <iostream>
#include <queue>
#include "food.h"
#include "comparators.h"
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

class Trie{
    using PriorityQueueMin = priority_queue<pair<string, float>, vector<pair<string, float>>, MinHeapCompare>;
    using PriorityQueueMax = priority_queue<pair<string, float>, vector<pair<string, float>>, MaxHeapCompare>;
    TrieNode* root;
    int item_count = 0;

private:
    void searchKey(TrieNode* ptr, const string& s, int& entries, string& output) {
        if (ptr == nullptr) {
            return;
        }
        for (int i = 0; i < VOCAB_SIZE; i++) {
            searchKey(ptr->next[i], s, entries, output);
            if (ptr->next[i] != nullptr) {
                if(ptr -> next[i] -> isWord){
                    string str = ptr->next[i]->food->getKey();
                    auto it = ::search(str.begin(), str.end(), s.begin(), s.end(),
                                       caseinsensitive);
                    if(it != str.end()){
                        entries++;
                        output += ptr->next[i]->food->getKey() + "\n";
                    }
                }
            }
        }
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

    template<typename T, typename C>
    void findTop10(TrieNode* root, priority_queue<T, vector<T>, C> &PQ,
                   const string& category, int nutrition_index){
        if(root == nullptr){
            return;
        }
        for(int i = 0; i < VOCAB_SIZE; i++){
            if( root -> next[i] != nullptr){
                if(root -> next[i] -> isWord && category == root -> next[i] -> food -> getValue().first){

                    float val = root -> next[i] -> food -> getValue().second[nutrition_index];
                    if(val < 0){
                        continue;
                    }
                    PQ.push(make_pair(root->next[i]->food->getKey(), val));
                    if( PQ.size() > 10){
                        PQ.pop();
                    }
                }
                findTop10(root -> next[i], PQ, category, nutrition_index);
            }
        }
    }

public:

    Trie(){
        root = new TrieNode();
    }
    ~Trie(){
        cleanUp(root);
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

    void tenValues(const string& category, const string& nutrition, const string& comp){
        int nutrition_index = getNutritionIndex(nutrition);
        if(nutrition_index < 0 ){
            cout << "Not Valid" << endl;
            return;
        }
        vector<pair<string, float>> top10;
        string label = "lowest";
        if(comp == "Lowest"){
            PriorityQueueMax PQ;
            findTop10(root, PQ, category, nutrition_index);
            while(!PQ.empty()){
                top10.push_back(PQ.top());
                PQ.pop();
            }
        }else{
            label = "highest";
            PriorityQueueMin PQ;
            findTop10(root, PQ, category, nutrition_index);
            while(!PQ.empty()){
                top10.push_back(PQ.top());
                PQ.pop();
            }
        }
        cout << "Using the Trie, " << endl;
        cout << "The 10 foods with the "<< label << " " << nutrition << " are: " << endl;
        for (int i = top10.size() - 1, j = 1; i >= 0; i--, j++) {
            cout << j << ". " << top10[i].first << ": " << top10[i].second << endl;
        }
        cout << endl;
    }

    void searchForKey(const string& s){
        int entries = 0;
        string output = "";
        searchKey(root, s, entries, output);
        cout << entries << " entries found for \"" << s << "\"" << endl << output << endl;
    }

};
#endif //TESTING_TRIE_H