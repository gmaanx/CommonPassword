#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <string>
using namespace std;

// Structs
struct Passwords {
    string password;
    int length;
    int num_chars;
    int num_digits;
    int num_upper;
    int num_lower;
    int num_special;
    int num_vowels;
    int num_syllables;
};

struct BinaryNode {
    Passwords data;
    BinaryNode* left;
    BinaryNode* right;
};

// Constants
const int MAX_LENGTH = 9999;
const int MIN_LENGTH = -1;

// Function declarations
// 1. Read file and print
BinaryNode* newNode(const Passwords& pass);
BinaryNode* insertBinaryNode(BinaryNode* root, Passwords& pass);
Passwords createObject(const string& s);
void readFileAndInsert(BinaryNode*& root, const string& filePath);
void printPasswordsList(BinaryNode* root, int start, int end, int& currentIndex, Passwords arr[]);
// 2. 
void flattenTreeToArray(BinaryNode* root, Passwords* arr, int& index, int limit);
Passwords* treeToArray(BinaryNode* root, int limit);
BinaryNode* insertNode(BinaryNode* root, Passwords newPass);
BinaryNode* passWordCheck(BinaryNode* node, const string& passcheck);
void inOrderPrint(BinaryNode* root);
int partition(Passwords arr[], int low, int high);
void quickSort(Passwords arr[], int low, int high);
void selectionSort(Passwords arr[], int n);
Passwords MinLength(BinaryNode* root);
Passwords MaxLength(BinaryNode* root);
void calculatePasswordStats(Passwords& pass);
void addPassword(BinaryNode*& root, const string& filename, const Passwords& pass);
BinaryNode* findMin(BinaryNode* node);
BinaryNode* deletePassword(BinaryNode* root, const string& password);
void saveNodeToFile(BinaryNode* node, ofstream& outFile);
void saveTreeToFile(BinaryNode* root, const string& filePath);
BinaryNode* deletePasswordFromFileAndTree(BinaryNode* root, const string& filePath, const string& password);
void filterByLength(BinaryNode* root, int* lengthCount, int maxLength);
void findPasswordsByLength(BinaryNode* root, int length);
void drawChart(int* lengthCount, int maxLength, int maxColumnHeight = 20);
void Menu(BinaryNode* root, const string& filename);


#endif // BINARY_TREE_H