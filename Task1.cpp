
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class TreeNode {
public:
    int key;
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k, int v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

class HybridDataStructure {

public:

    map<int, int> hash_map;
    TreeNode* root;
    TreeNode* getRoot(){
        return root;
    }
    TreeNode* insertNode(TreeNode* node, int key, int value) {
        if (node == nullptr) {
            return new TreeNode(key, value);
        }
        if (key < node->key) {
            node->left = insertNode(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insertNode(node->right, key, value);
        }
        else {
            node->value = value;
        }
        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int key) {
        if (node == nullptr) {
            return node;
        }
        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    HybridDataStructure() : root(nullptr) {}

    void insert(int key, int value) {
        if (hash_map.find(key) != hash_map.end()) {
            hash_map[key] = value;
        }
        else {
            // Insert into BST
            root = insertNode(root, key, value);
            // Update hash map
            hash_map[key] = value;
        }
    }

    void remove(int key) {
        if (hash_map.find(key) != hash_map.end()) {
            // Remove from hash map
            hash_map.erase(key);
            // Remove from BST
            root = deleteNode(root, key);
        }
    }

    int* search(int key) {
        if (hash_map.find(key) != hash_map.end()) {
            return &hash_map[key];
        }
        else {
            return nullptr;
        }
    }

    int nearest(int key) {
        if (root == nullptr) {
            return -1; 
        }
        return nearestHelper(root, key)->key;
    }

    TreeNode* nearestHelper(TreeNode* node, int key) {
        if (node == nullptr) {
            return node; 
        }
        if (node->key == key) {
            return node;
        }
        if (key < node->key) {
            TreeNode* leftNearest = nearestHelper(node->left, key);
            if(leftNearest==nullptr){
                return node;
            }
            else{
                     return nearestHelper(leftNearest, key);
                
            }
        }
        else {
            TreeNode* rightNearest = nearestHelper(node->right, key);
            if(rightNearest==nullptr){
                return node;
            }
            else{
                    return nearestHelper(rightNearest, key);
                
            }
        }
    }
};

vector<pair<int, int>> productsInRange(HybridDataStructure& data_structure, int minPrice, int maxPrice) {
    vector<pair<int, int>> products;
    const TreeNode* current = data_structure.root; // Access root via public method
    int ln=0;
    int un=0;

    while (current != nullptr) {
        
        if (current->value >= minPrice && current->value <= maxPrice) {
            products.push_back({ current->key, current->value });
            
        }
        else if (current->value < minPrice && ln==0) {
            
            int lowernearestExpensive = data_structure.nearest(current->key);
            // cout<<lowernearestExpensive<<endl;
            if (lowernearestExpensive != -1) {
                int* found = data_structure.search(lowernearestExpensive);
                // cout<<found<<endl;
                if (found != nullptr) {
                    
                    products.push_back({lowernearestExpensive, *found});
                }
            }
            ln==1;
        }
        else if (current->value > maxPrice &&   un==0) {
            int uppernearestExpensive = data_structure.nearest(current->key);
            // cout<<"lol"<<current->key<<endl;
            if (uppernearestExpensive != -1) {
                int* found = data_structure.search(uppernearestExpensive);
                // cout<<*found<<endl;
                if (found != nullptr) {
                    products.push_back({uppernearestExpensive, *found});
                }
            }
            un=1;

        }
        else{
            break;
        }
        if(current->right!=nullptr)
            current =  current->right;
        else{
             break;
        }
    }

    return products;
}


int main() {
    HybridDataStructure hybridDS;
    // Example data
    hybridDS.insert(1, 10);
    hybridDS.insert(2, 20);
    hybridDS.insert(3, 30);
    hybridDS.insert(4, 40);
    hybridDS.insert(5, 50);
    hybridDS.insert(7, 70);

    // Example usage
    int minPrice = 15;
    int maxPrice = 45;
    vector<pair<int, int>> result = productsInRange(hybridDS, minPrice, maxPrice);
    cout << "Products within the price range:" << endl;
    for (const auto& product : result) {
        cout << "Product ID: " << product.first << ", Price: " << product.second << endl;
    }

    return 0;
}
