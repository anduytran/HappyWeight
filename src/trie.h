//
// Created by Dylan on 4/16/2024.
//

#ifndef TESTING_TRIE_H
#define TESTING_TRIE_H

#endif //TESTING_TRIE_H
#include "food.h"

struct TrieNode{
    char character;
    Food* food = nullptr;
    vector<TrieNode*> next;
    TrieNode(char c, Food& food){
        character = c;
        for(int i = 0; i < 26; i++){
            next.push_back(nullptr);
        }

        for(int i = 0; i < food.getKey().size(); i++){
            food.getKey()[i];
        }
    }
    explicit TrieNode(char c){
        character = c;
    }
    TrieNode(){
        character = '\0';
    }
};

class Trie{
    TrieNode* root;
public:
    void insert(TrieNode* root, Food& food) {
        TrieNode *curr = root;
        for (int i = 0; i < food.getKey().size(); i++) {
            char c = food.getKey()[i];
            auto it = curr->next.begin();
            bool found = false;
            TrieNode* ptr = *it;
            while(it != curr->next.end()){
                if(ptr->character == food.getKey()[i]){
                    found = true;
                }
                it++;
            }
            if(!found){
                if(food.getKey()[i] != food.getKey().back()) {
                    auto* node = new TrieNode(c);
                    curr->next[c] = node;
                }else{
                    auto* node = new TrieNode(c, food);
                    curr->next[c] = node;
                }
            }
            curr = curr->next[c];
        }
    }
};