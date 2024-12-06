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

void printPasswordsList(BinaryNode* root, int start, int end, int& currentIndex, Passwords arr[]) 
{
    if (!root || currentIndex >= end) return;

    printPasswordsList(root->left, start, end, currentIndex, arr);

    if (currentIndex >= start && currentIndex < end) {
        arr[currentIndex] = root->data;  // Lưu mật khẩu vào mảng
        cout << "Password: " << root->data.password << ", Length: " << root->data.length << endl;
    }
    currentIndex++;

    printPasswordsList(root->right, start, end, currentIndex, arr);
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
BinaryNode* passWordCheck(BinaryNode* node, const string& passcheck) 
{
    if (node == nullptr) return nullptr;  // Nếu nút trống, trả về nullptr
    if (node->data.password == passcheck) return node;  // Nếu tìm thấy mật khẩu, trả về con trỏ đến nút

    // Duyệt cây theo chiều sâu (DFS)
    BinaryNode* leftResult = passWordCheck(node->left, passcheck);
    if (leftResult != nullptr) return leftResult;  // Nếu tìm thấy ở cây trái, trả về kết quả

    return passWordCheck(node->right, passcheck);  // Tìm tiếp ở cây phải
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
    /*Passwords newPass;
    cout << "Nhap password moi: ";
    cin >> newPass.password;

    // Tính toán các thông số của password
    calculatePasswordStats(newPass);

    // In ra thông tin của password vừa nhập
    cout << "Mat khau: " << newPass.password << endl;
    cout << "Do dai: " << newPass.length << endl;
    cout << "So ki tu: " << newPass.num_chars << endl;
    cout << "So chu so: " << newPass.num_digits << endl;
    cout << "So chu thuong: " << newPass.num_lower << endl;
    cout << "So ky tu dac biet: " << newPass.num_special << endl;
    cout << "So syllables: " << newPass.num_syllables << endl;
    cout << "So chu hoa: " << newPass.num_upper << endl;
    cout << "So nguyen am: " << newPass.num_vowels << endl; */
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
    int limited = 0; //limit của ArrList
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
            cout << "Nhap gioi han can in: ";
            int limit;
            cin >> limit;
            limited = limit;
            current_idx = 0;
            cout << "First " << limit << " password: \n";
            printPasswordsList(root, 0, limit, current_idx, passList);
            case1Flag = true;
            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 2: {
            string passcheck;
            cout << "Nhap password: ";
            cin >> passcheck;

            // Tìm mật khẩu trong toàn bộ cây
            BinaryNode* node = passWordCheck(root, passcheck);

            if (node == nullptr) {
                cout << "Khong co password can tim.\n";
            }
            else {
                // In ra các thông tin của mật khẩu tìm thấy
                cout << "Tim thay password: " << node->data.password << endl;
                cout << "Do dai password: " << node->data.length << endl;
                cout << "So ki tu: " << node->data.num_chars << endl;
                cout << "So chu so: " << node->data.num_digits << endl;
                cout << "So chu thuong: " << node->data.num_lower << endl;
                cout << "So ky tu dac biet: " << node->data.num_special << endl;
                cout << "So syllables: " << node->data.num_syllables << endl;
                cout << "So chu hoa: " << node->data.num_upper << endl;
                cout << "So nguyen am: " << node->data.num_vowels << endl;
            }

            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 3:
        {
            if (case1Flag == false)
            {
                cout << "Chua co danh sach, vui long chon lai.\n";
                break;
            }
            // Khai báo passListArr trong khối lệnh của case 3
            Passwords* passListArr = treeToArray(root, limited);
            if (!passListArr) {
                cout << "Cay rong hoac khong co du lieu de in.\n";
                break;
            }
            else {
                cout << "Danh sach " << limited << " mat khau dau tien: \n";
                for (int i = 0; i < limited; ++i) {
                    cout << "Password: " << passListArr[i].password << ", Length: " << passListArr[i].length << endl;
                }
            }

            int sortOption;
            cout << "Chon kieu sap xep:\n";
            cout << "1. Sap xep tang dan (Selection Sort)\n";
            cout << "2. Sap xep giam dan (Quick Sort)\n";
            cout << "Lua chon: ";
            cin >> sortOption;

            if (limited == 0) {
                cout << "Cay rong hoac khong co du lieu de sap xep.\n";
                break;
            }

            // Sắp xếp theo yêu cầu
            if (sortOption == 1) {
                // Sắp xếp tăng dần (Selection Sort)
                selectionSort(passListArr, limited);
                cout << "Danh sach da duoc sap xep tang dan:\n";
            }
            else if (sortOption == 2) {
                // Sắp xếp giảm dần (Quick Sort)
                quickSort(passListArr, 0, limited - 1);
                cout << "Danh sach da duoc sap xep giam dan:\n";
            }
            else {
                cout << "Lua chon khong hop le. Vui long thu lai!\n";
                break;
            }

            // In danh sách sau khi sắp xếp
            for (int i = 0; i < limited; ++i) {
                cout << "Password: " << passListArr[i].password << ", Length: " << passListArr[i].length << endl;
            }

            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
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
            /*addPassword();
            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
            break;*/
            Passwords pass;
            std::cout << "Enter password: ";
            std::cin >> pass.password;

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
            /*string passDelete;
            cout << "Nhap password can xoa: ";
            cin >> passDelete;

            BinaryNode* searchResult = passWordCheck(root, passDelete);
            if (searchResult == NULL) {
                cout << "Khong tim thay mat khau can xoa.\n";
            }
            else {
                root = deletePassword(root, passDelete);
                cout << "Da xoa thanh cong password: " << passDelete << endl;
            }
            cout << "Nhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
            system("cls");
            break; */
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