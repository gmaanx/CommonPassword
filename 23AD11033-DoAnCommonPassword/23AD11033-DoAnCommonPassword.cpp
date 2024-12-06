// 23AD11033-DoAnCommonPassword.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "binary-tree.h"
#include <iostream>

using namespace std;

int main() {
    BinaryNode* root = NULL;
    readFileAndInsert(root, "D:/UTE-DataStructure/common_passwords.csv");
    Menu(root, "D:/UTE-DataStructure/common_passwords.csv");
    return 0;
}