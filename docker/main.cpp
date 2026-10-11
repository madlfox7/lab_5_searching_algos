#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void print_arr(int *arr, int size) {
    cout << "Array: ";
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

// =============== 1. Linear Search ====================
void Linear_search(int *arr, int size, int target) {
    cout << "\n--- Linear Search ---\n";
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            cout << "Found at index: " << i << endl;
            return;
        }
    }
    cout << "Not found\n";
}

// =============2. Binary Search ====================
void Binary_search(int *arr, int size, int target) {
    cout << "\n--- Binary Search ---\n";
    int *sorted = new int[size];
    for (int i = 0; i < size; i++) sorted[i] = arr[i];
    sort(sorted, sorted + size);

    cout << "Sorted array: ";
    print_arr(sorted, size);

    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (sorted[mid] == target) {
            cout << "Found at index (in sorted array): " << mid << endl;
            delete[] sorted;
            return;
        } else if (target < sorted[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << "Not found\n";
    delete[] sorted;
}

// ====================    3. Binary Search Tree ====================
struct BSTNode {
    int value;
    BSTNode *left;
    BSTNode *right;
    BSTNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

BSTNode* bst_insert(BSTNode *root, int value) {
    if (!root) return new BSTNode(value);
    if (value < root->value)
        root->left = bst_insert(root->left, value);
    else
        root->right = bst_insert(root->right, value);
    return root;
}

BSTNode* bst_search(BSTNode *node, int target) {
    if (!node || node->value == target) return node;
    if (target < node->value)
        return bst_search(node->left, target);
    else
        return bst_search(node->right, target);
}

void bst_inorder(BSTNode *node) {
    if (node) {
        bst_inorder(node->left);
        cout << node->value << " ";
        bst_inorder(node->right);
    }
}

void BST_search(int *arr, int size, int target) {
    cout << "\n--- Binary Search Tree ---\n";

    BSTNode *root = nullptr;
    for (int i = 0; i < size; i++)
        root = bst_insert(root, arr[i]);

    cout << "Tree (in-order): ";
    bst_inorder(root);
    cout << endl;

    cout << "Searching for " << target << "...\n";
    BSTNode *res = bst_search(root, target);
    if (res)
        cout << "Found: " << res->value << endl;
    else
        cout << "Not found\n";
}

// ====================    4. Trie ====================
struct TrieNode {
    TrieNode *children[26];
    bool is_end;
    TrieNode() {
        is_end = false;
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};

class Trie {
public:
    TrieNode *root;
    Trie() { root = new TrieNode(); }

    void insert(const string &word) {
        TrieNode *node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (idx < 0 || idx >= 26) continue;
            if (!node->children[idx])
                node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->is_end = true;
    }

    bool search(const string &word) {
        TrieNode *node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (idx < 0 || idx >= 26 || !node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->is_end;
    }
};

void Trie_demo() {
    cout << "\n--- Trie (Hash Trie) ---\n";
    Trie trie;
    string words[] = {"cat", "car", "card", "dog", "apple"};
    for (auto &w : words) trie.insert(w);

    cout << "Inserted words: cat, car, card, dog, apple\n";

    string tests[] = {"car", "card", "ca", "dog", "cow", "apple"};
    for (auto &t : tests) {
        cout << "Search \"" << t << "\": " 
             << (trie.search(t) ? "Found" : "Not found") << endl;
    }
}


int choose_algo() {
    cout << "\nChoose algorithm:\n";
    cout << "1. Linear search\n";
    cout << "2. Binary search\n";
    cout << "3. Binary Search Tree\n";
    cout << "4. Trie demo on preset dictionary\n";
    cout << "choice: ";
    int choice;
    cin >> choice;
    return choice;
}

void run_algo(int choice, int *arr, int size, int target) {
    switch (choice) {
        case 1:
            Linear_search(arr, size, target);
            break;
        case 2:
            Binary_search(arr, size, target);
            break;
        case 3:
            BST_search(arr, size, target);
            break;
        case 4:
            Trie_demo();
            break;
        default:
            cout << "Unknown algorithm\n";
    }
}


int main()
 {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    if (size <= 0)
     {
        cout << "Size must be > 0\n";
        return 1;
    }
    int *arr = new int[size];
    cout << "Enter elements: ";
    for (int i = 0; i < size; ++i)
        cin >> arr[i];

    print_arr(arr, size);
    int target;
    cout << "Enter target to search: ";
    cin >> target;
    int algo = choose_algo();
    run_algo(algo, arr, size, target);

    delete[] arr;
    return 0;
}