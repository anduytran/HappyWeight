#pragma once
#ifndef COMPARATORS_H
#define COMPARATORS_H
#include <iostream>
#include <string>
using std::string;
using std::pair;

struct MinHeapCompare {
    bool operator()(const pair<string, float>& p1, const pair<string, float>& p2) const {
        return p1.second > p2.second || (p1.second == p2.second && p1.first < p2.first);
    }
};

struct MaxHeapCompare {
    bool operator()(const pair<string, float>& p1, const pair<string, float>& p2) const {
        return p1.second < p2.second || (p1.second == p2.second && p1.first < p2.first);
    }
};

bool caseinsensitive(char a, char b)
{
    return tolower(a) == tolower(b);
}

#endif