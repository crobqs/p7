#pragma once

#include <bits/stdc++.h>

using namespace std;

// #define forLoop(i__, s__, e__) for(int i__ = s__; i__ != e__; i__ += (s__ < e__) * 2 - 1)

int randomInt(int mn, int mx) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution dist(mn, mx);
    return dist(mt);
}

std::vector<int> randomIntVec(int sz, int mn, int mx) {
    std::vector<int> v;
    v.reserve(sz);
    for (int i = 0; i < sz; ++i) v.push_back(randomInt(mn, mx));
    return v;
}