//
// Created by Dylan on 4/16/2024.
//
#pragma once
#ifndef TESTING_TRIE2_H
#define TESTING_TRIE2_H
#include <iostream>
#include "food.h"
using namespace std;
#define VOCAB_SIZE 26
struct TrieNode{
    vector<Food*> foods;
    vector<TrieNode*> next;
    bool isWord;
    TrieNode(){
        next = vector<TrieNode*>(VOCAB_SIZE, nullptr);
        isWord = false;
    }
};

class Trie{
    TrieNode* root;


public:

    Trie(){
        root = new TrieNode();
    }

    void insert(Food*& food) {
        TrieNode *curr = root;
        string name = food->getKey(); //Fruits
        for (int i = 0; i < name.size(); i++) {
            char c = tolower(name[i]);
            if( curr->next[c - 'a'] == nullptr ){
                curr->next[c - 'a'] = new TrieNode();
            }
            curr = curr->next[c - 'a'];
        }
        curr->isWord = true;
        curr->foods.push_back(food);
    }

    vector<Food*> search(string word){
        TrieNode *curr = root;
        for (int i = 0; i < word.size(); i++){
            char c = tolower(word[i]);
            if( curr->next[c - 'a'] == nullptr ){
                return {};
            }
            curr = curr->next[c - 'a'];
        }
        if( curr->isWord)
            return curr->foods;
        return {};
    }

};
#endif //TESTING_TRIE_H
