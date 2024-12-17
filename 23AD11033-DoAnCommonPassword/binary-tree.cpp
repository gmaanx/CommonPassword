#include <iostream>
#include <fstream>
#include <sstream>
#include "binary-tree.h"
#define MAX_PASS_LENGTH 100 

using namespace std;


// Function definitions
BinaryNode* newNode(const Passwords& pass) 
{
    BinaryNode* node = new (nothrow) BinaryNode();
    if (!node) {
        cout << "Out of memory." << endl;
        abort();
    }
    node->data = pass;
    node->left = node->right = nullptr;
    return node;
}
BinaryNode* insertBinaryNode(BinaryNode* root, Passwords& pass) 
{
    if (root == NULL) return newNode(pass);
    if (pass.password < root->data.password) {
        root->left = insertBinaryNode(root->left, pass);
    }
    else {
        root->right = insertBinaryNode(root->right, pass);
    }
    return root;
}
Passwords createObject(const string& s) 
{
    Passwords pass;
    stringstream ss(s);
    string item;

    try {
        getline(ss, pass.password, ',');

        getline(ss, item, ',');
        pass.length = stoi(item);

        getline(ss, item, ',');
        pass.num_chars = stoi(item);

        getline(ss, item, ',');
        pass.num_digits = stoi(item);

        getline(ss, item, ',');
        pass.num_upper = stoi(item);

        getline(ss, item, ',');
        pass.num_lower = stoi(item);

        getline(ss, item, ',');
        pass.num_special = stoi(item);

        getline(ss, item, ',');
        pass.num_vowels = stoi(item);

        getline(ss, item, ',');
        pass.num_syllables = stoi(item);
    }
    catch (const exception& e) {
        cout << "Dong loi: " << s << endl;
    }

    return pass;
}

void readFileAndInsert(BinaryNode*& root, const string& filePath)
{
    ifstream input(filePath);
    if (!input.is_open()) {
        cout << "Khong the mo file." << endl;
        return;
    }

    string line;
    getline(input, line);
    while (getline(input, line)) {
        Passwords pass = createObject(line);
        root = insertBinaryNode(root, pass);
    }

    input.close();
}

void printPasswordsListPaged(BinaryNode* root, int totalRecords, int recordsPerPage) {
    int totalPages = (totalRecords + recordsPerPage - 1) / recordsPerPage; // Tổng số trang
    int currentPage = 1;

    Passwords* passwordArray = treeToArray(root, totalRecords);

    if (passwordArray == nullptr) {
        cout << "Khong co du lieu de hien thi." << endl;
        return;
    }

    while (true) {
        // Tính khoảng bắt đầu và kết thúc của trang hiện tại
        int start = (currentPage - 1) * recordsPerPage;
        int end = min(currentPage * recordsPerPage, totalRecords);

        for (int i = start; i < end; ++i) {
            cout << "Password: " << passwordArray[i].password
                << ", Length: " << passwordArray[i].length << endl;
        }
        cout << "\nTrang " << currentPage << " / " << totalPages << ":" << endl;
        cout << "--------------------------------\n";

        // In menu điều hướng
        cout << "\nNhap lua chon:\n";
        cout << "1. Trang truoc\n";
        cout << "2. Trang sau\n";
        cout << "3. Chon trang de sort\n";
        cout << "4. Thoat\n";
        cout << "Lua chon: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            if (currentPage > 1) {
                currentPage--;
            }
            else {
                cout << "Day la trang dau tien.\n";
            }
        }
        else if (choice == 2) {
            if (currentPage < totalPages) {
                currentPage++;
            }
            else {
                cout << "Day la trang cuoi cung.\n";
            }
        }
        else if (choice == 3) {
            cout << "Nhap trang de sort (1-" << totalPages << "): ";
            int sortPage;
            cin >> sortPage;

            if (sortPage >= 1 && sortPage <= totalPages) {
                start = (sortPage - 1) * recordsPerPage;
                end = min(sortPage * recordsPerPage, totalRecords);

                cout << "Sap xep tang dan tren trang " << sortPage << ":\n";
                quickSort(passwordArray + start, 0, end - start - 1);

                for (int i = start; i < end; ++i) {
                    cout << "Password: " << passwordArray[i].password
                        << ", Length: " << passwordArray[i].length << endl;
                }
            }
            else {
                cout << "Trang khong hop le.\n";
            }
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Lua chon khong hop le.\n";
        }
    }

    delete[] passwordArray;
}
void flattenTreeToArray(BinaryNode* root, Passwords* arr, int& index, int limit) 
{
    if (!root || index >= limit) return;

    flattenTreeToArray(root->left, arr, index, limit);
    if (index < limit) {
        arr[index++] = root->data;
    }
    flattenTreeToArray(root->right, arr, index, limit);
}
Passwords* treeToArray(BinaryNode* root, int limit) 
{
    if (limit <= 0) return nullptr;

    Passwords* arr = new Passwords[limit];
    int index = 0;
    flattenTreeToArray(root, arr, index, limit);
    return arr;
}

BinaryNode* insertNode(BinaryNode* root, Passwords newPass) 
{
    if (root == NULL) {
        BinaryNode* newNode = new BinaryNode{ newPass, nullptr, nullptr };
        return newNode;
    }

    if (newPass.password < root->data.password)
        root->left = insertNode(root->left, newPass);
    else if (newPass.password > root->data.password)
        root->right = insertNode(root->right, newPass);

    return root;
}
bool containsSubstring(const string& password, const string& substring) {
    return password.find(substring) != string::npos;
}
void passwordCheck(BinaryNode* node, const string& substring) {
    if (node == nullptr) return;

    if (containsSubstring(node->data.password, substring)) {
        cout << node->data.password << endl;
    }

    passwordCheck(node->left, substring);
    passwordCheck(node->right, substring);
}

void inOrderPrint(BinaryNode* root) 
{
    if (root == NULL) return;
    inOrderPrint(root->left);
    cout << "Password: " << root->data.password << ", Length: " << root->data.length << endl;
    inOrderPrint(root->right);
}
int partition(Passwords arr[], int low, int high) 
{
    int pivot = arr[high].length;
    int i = (low - 1);

    for (int j = low; j < high; ++j) {
        if (arr[j].length > pivot) {
            i++;
            Passwords temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Passwords temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
void quickSort(Passwords arr[], int low, int high) 
{
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void selectionSort(Passwords arr[], int n) 
{
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].length < arr[minIndex].length) {
                minIndex = j;
            }
        }
        Passwords temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}
Passwords MinLength(BinaryNode* root) 
{
    if (root == NULL) {
        return Passwords(); // trả về một Password rỗng nếu cây trống
    }

    Passwords minPass = root->data;
    if (root->left) {
        Passwords leftMin = MinLength(root->left);
        if (leftMin.length < minPass.length) {
            minPass = leftMin;
        }
    }
    if (root->right) {
        Passwords rightMin = MinLength(root->right);
        if (rightMin.length < minPass.length) {
            minPass = rightMin;
        }
    }

    return minPass;
}

Passwords MaxLength(BinaryNode* root) 
{
    if (root == NULL) {
        return Passwords(); // trả về một Password rỗng nếu cây trống
    }

    Passwords maxPass = root->data;
    if (root->left) {
        Passwords leftMax = MaxLength(root->left);
        if (leftMax.length > maxPass.length) {
            maxPass = leftMax;
        }
    }
    if (root->right) {
        Passwords rightMax = MaxLength(root->right);
        if (rightMax.length > maxPass.length) {
            maxPass = rightMax;
        }
    }

    return maxPass;
}
void calculatePasswordStats(Passwords& pass) 
{
    pass.length = pass.password.length();
    pass.num_chars = pass.length;
    pass.num_digits = 0;
    pass.num_lower = 0;
    pass.num_special = 0;
    pass.num_syllables = 0;
    pass.num_upper = 0;
    pass.num_vowels = 0;

    for (int i = 0; i < pass.password.length(); ++i) {
        char c = pass.password[i];
        if (isdigit(c)) {
            pass.num_digits++;
        }
        else if (islower(c)) {
            pass.num_lower++;
        }
        else if (isupper(c)) {
            pass.num_upper++;
        }
        else if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            pass.num_vowels++;
        }
        else {
            pass.num_special++;
        }
    }
}

void addPassword(BinaryNode*& root, const string& filename, const Passwords& pass) 
{
    // Thêm vào file CSV
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << pass.password << "," << pass.length << "," << pass.num_chars << ","
            << pass.num_digits << "," << pass.num_upper << "," << pass.num_lower << ","
            << pass.num_special << "," << pass.num_vowels << "," << pass.num_syllables << "\n";
        file.close();
        cout << "Password added successfully: " << pass.password << "\n";
    }
    else {
        cout << "Error opening file to add password.\n";
    }

    // Thêm vào cây nhị phân
    root = insertBinaryNode(root, const_cast<Passwords&>(pass));
}
BinaryNode* findMin(BinaryNode* node) 
{
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

BinaryNode* deletePassword(BinaryNode* root, const string& password) 
{
    if (root == nullptr) return root;

    if (password < root->data.password) {
        root->left = deletePassword(root->left, password);
    }
    else if (password > root->data.password) {
        root->right = deletePassword(root->right, password);
    }
    else {
        // Nếu tìm thấy node
        // Trường hợp 1: Node không có con hoặc chỉ có một con
        if (root->left == nullptr) {
            BinaryNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            BinaryNode* temp = root->left;
            delete root;
            return temp;
        }

        // Trường hợp 2: Node có cả hai con
        BinaryNode* temp = findMin(root->right);  // Tìm giá trị nhỏ nhất bên phải
        root->data = temp->data;                 // Thay thế dữ liệu
        root->right = deletePassword(root->right, temp->data.password); // Xóa nút tối thiểu bên phải
    }

    return root;
}
void saveNodeToFile(BinaryNode* node, ofstream& outFile) 
{
    if (node == nullptr) return;

    // Ghi thông tin mật khẩu vào file CSV
    outFile << node->data.password << ","
        << node->data.length << ","
        << node->data.num_chars << ","
        << node->data.num_digits << ","
        << node->data.num_lower << ","
        << node->data.num_special << ","
        << node->data.num_syllables << ","
        << node->data.num_upper << ","
        << node->data.num_vowels << endl;

    // Ghi tiếp các node con
    saveNodeToFile(node->left, outFile);
    saveNodeToFile(node->right, outFile);
}
void saveTreeToFile(BinaryNode* root, const string& filePath) 
{
    // Mở file để ghi lại các mật khẩu trong cây nhị phân
    ofstream outFile(filePath, ios::trunc);  // Ghi đè lên file
    if (!outFile) {
        cout << "Khong the mo file de ghi.\n";
        return;
    }

    saveNodeToFile(root, outFile);
    outFile.close();
}

BinaryNode* deletePasswordFromFileAndTree(BinaryNode* root, const string& filePath, const string& password) 
{
    // Xóa mật khẩu trong cây
    if (root == nullptr) {
        return root; // Nếu cây rỗng
    }

    if (password < root->data.password) {
        root->left = deletePasswordFromFileAndTree(root->left, filePath, password);
    }
    else if (password > root->data.password) {
        root->right = deletePasswordFromFileAndTree(root->right, filePath, password);
    }
    else {  // Nếu tìm thấy password cần xóa
        if (root->left == nullptr) {
            BinaryNode* temp = root->right;
            delete root;
            root = temp;
        }
        else if (root->right == nullptr) {
            BinaryNode* temp = root->left;
            delete root;
            root = temp;
        }
        else {
            // Có 2 con, tìm người kế nhiệm (smallest trong cây phải)
            BinaryNode* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deletePasswordFromFileAndTree(root->right, filePath, temp->data.password);
        }
    }

    // Cập nhật lại cây nhị phân sau khi xóa
    saveTreeToFile(root, filePath);
    return root;
}



void filterByLength(BinaryNode* root, int* lengthCount, int maxLength)
{
    if (root == nullptr) return;

    if (root->data.length <= maxLength) {
        lengthCount[root->data.length]++;
    }

    filterByLength(root->left, lengthCount, maxLength);
    filterByLength(root->right, lengthCount, maxLength);
}
void findPasswordsByLength(BinaryNode* root, int length) 
{
    if (root == nullptr) return;

    if (root->data.length == length) {
        cout << "Password: " << root->data.password << " | Length: " << root->data.length << endl;
    }

    findPasswordsByLength(root->left, length);
    findPasswordsByLength(root->right, length);
}
void drawChart(int* lengthCount, int maxLength, int maxColumnHeight) 
{
    int maxCount = 0;

    // Tìm giá trị lớn nhất trong mảng đếm
    for (int i = 1; i <= maxLength; ++i) {
        if (lengthCount[i] > maxCount) {
            maxCount = lengthCount[i];
        }
    }

    // Nếu không có dữ liệu, thoát hàm
    if (maxCount == 0) {
        cout << "Khong co du lieu de ve bieu do.\n";
        return;
    }

    // Tính tỷ lệ thu nhỏ
    double scale = static_cast<double>(maxColumnHeight) / maxCount;

    cout << "Bieu do tan suat do dai password:\n";
    cout << "--------------------------------\n";

    // Vẽ biểu đồ
    for (int i = 1; i <= maxLength; ++i) {
        if (lengthCount[i] > 0) {
            // Căn chỉnh hiển thị số độ dài
            if (i < 10)
                cout << " " << i << " | "; // Thêm dấu cách trước các số có 1 chữ số
            else
                cout << i << " | "; // Không thêm dấu cách cho các số có 2 chữ số

            int columnHeight = static_cast<int>(lengthCount[i] * scale);
            for (int j = 0; j < columnHeight; ++j) {
                cout << "#";
            }

            cout << " (" << lengthCount[i] << ")\n"; // Hiển thị giá trị
        }
    }

    cout << "--------------------------------\n";
}
void Menu(BinaryNode* root, const string& filename)
{
    int option;
    Passwords passList[MAX_PASS_LENGTH];
    int current_idx = 0;
    int recordsPerPage;
    bool case1Flag = false; 

    do {
        cout << "Chon cac hanh dong sau: \n";
        cout << "0. Thoat.\n";
        cout << "1. In danh sach n mat khau. \n";
        cout << "2. Tim mat khau.\n";
        cout << "3. Sap xep danh sach mat khau.\n";
        cout << "4. Tim mat khau lon nhat, be nhat.\n";
        cout << "5. Them mat khau.\n";
        cout << "6. Xoa mat khau.\n";
        cout << "7. Thong ke so luong password theo do dai.\n";
        cout << "Lua chon: ";

        cin >> option;


        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Nhap khong hop le. Vui long nhap lai!\n";
            continue;
        }

        cout << "-----------------------\n";
        switch (option) {
        case 1: {
            cout << "Nhap so dong muon in tren moi trang: ";
            cin >> recordsPerPage;

            if (recordsPerPage > 0) {
                printPasswordsListPaged(root, 10000, recordsPerPage);
            }
            else {
                cout << "So dong khong hop le.\n";
            }
            break;
        }
        case 2: {
            string passcheck;
            cout << "Nhap password: ";
            cin >> passcheck;

            // In tất cả các mật khẩu phù hợp
            cout << "Cac password tim duoc:\n";
            passwordCheck(root, passcheck);

            // Dừng màn hình để người dùng đọc kết quả
            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 3:
        {
            cout << "Nhap so dong muon sap xep tren moi trang: ";
            cin >> recordsPerPage;

            if (recordsPerPage > 0) {
                printPasswordsListPaged(root, 10000, recordsPerPage);
            }
            else {
                cout << "So dong khong hop le.\n";
            }
            break;
        }
        case 4: {
            Passwords minPass = MinLength(root);
            Passwords maxPass = MaxLength(root);
            if (minPass.length != MAX_LENGTH)
                cout << "Mat khau ngan nhat: " << minPass.password << " (Do dai: " << minPass.length << ")" << endl;
            if (maxPass.length != MIN_LENGTH)
                cout << "Mat khau dai nhat: " << maxPass.password << " (Do dai: " << maxPass.length << ")" << endl;
            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 5: {
            Passwords pass;
            cout << "Enter password: ";
            cin >> pass.password;

            // Tính toán các thông số của mật khẩu
            calculatePasswordStats(pass);

            addPassword(root, filename, pass);
            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 6: {
            string passDelete;
            cout << "Nhap mat khau can xoa: ";
            cin >> passDelete;

            // Xóa mật khẩu khỏi cây và file CSV
            root = deletePasswordFromFileAndTree(root, filename, passDelete);

            if (root) {
                cout << "Da xoa thanh cong mat khau: " << passDelete << endl;
            }
            else {
                cout << "Khong tim thay mat khau can xoa!" << endl;
            }

            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 7: {
            const int MAX_LENGTH = 100; // Giới hạn cố định
            int* lengthCount = new int[MAX_LENGTH + 1] {0}; // Mảng đếm độ dài

            // Gọi hàm thống kê
            filterByLength(root, lengthCount, MAX_LENGTH);

            // Vẽ biểu đồ
            drawChart(lengthCount, MAX_LENGTH);

            // In kết quả thống kê
            cout << "Thong ke so luong password theo do dai:\n";
            for (int i = 1; i <= MAX_LENGTH; ++i) {
                if (lengthCount[i] > 0) {
                    cout << "Do dai " << i << ": " << lengthCount[i] << " mat khau.\n";
                }
            }

            cout << "Ban co muon in ra tat ca password theo do dai? (y/n): ";
            char choice;
            cin >> choice;
            //Xử lý in
            if (tolower(choice) == 'y') {
                int targetLength;
                cout << "Nhap do dai muon in: ";
                cin >> targetLength;

                if (targetLength > 0 && targetLength <= MAX_LENGTH && lengthCount[targetLength] > 0) {
                    cout << "Cac password co do dai " << targetLength << ":\n";
                    findPasswordsByLength(root, targetLength);
                }
                else {
                    cout << "Khong co password nao co do dai " << targetLength << ".\n";
                }
            }

            delete[] lengthCount; // Giải phóng bộ nhớ
            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 0:
            cout << "Da thoat!\n";
            break;
        default:
            cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }
        cout << "-----------------------\n";
    } while (option != 0);
}