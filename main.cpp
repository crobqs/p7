#include <bits/stdc++.h>
// #define BST
// #include "./include/rb.hpp"
#include "./include/sdl_1.hpp"

using namespace std;

char* word_gen(const char* a, const char* b) {
    int aLen = strlen(a);
    int bLen = strlen(b);
    char* res = (char*)malloc(aLen + bLen + 1);
    memcpy(res, a, aLen);
    memcpy(res+aLen, b, bLen);
    return res;
}

char* substr(const char* s, int i, int j) {
    int len = j - i;
    char* res = (char*)malloc(len);
    memset(res, -1, len);
    memcpy(res, s+i, len);
    res[len] = 0;
    return res;
}

int main(int argc, char* argv[]) {
    char* a = substr("lmaoo", 0, 2);
    printf("[%s]\n", a);
    free(a);
}