#ifndef TREE_HPP
#define TREE_HPP

// Add any standard library you need.
#include <string>
#include <vector>
#include <map>
using namespace std;
// ==================== trie (prefix tree) ======================
struct TrieNode {
    string piece;
    map<char, TrieNode*> next;
    TrieNode(string a = "\0") :piece(a) {};//root
    TrieNode(char a) { piece = a; };
};
//TrieNode* emp = NULL;
class Trie {
private:
    TrieNode* root;
    void deletenode(TrieNode*& a) {
        for (auto tmp : a->next) {
            deletenode(tmp.second);
        }
        delete a;
    }
    void insert(string word, TrieNode* ptr, int layer) {
        if (ptr->piece == word)return;
        if (ptr->next.empty()) {
            if (ptr->piece == "\0") {//root
                TrieNode* leaf = new TrieNode(word);
                ptr->next.insert(make_pair(word[0], leaf));
            }
            else {
                string other = ptr->piece;
                ptr->piece = other[layer-1];
                if (other.length() > word.length())swap(word, other);//other is shorter
                int now_layer = layer;
                while (now_layer < other.length() && word[now_layer] == other[now_layer]) {
                    TrieNode* next_layer = new TrieNode(word[now_layer]);
                    ptr->next.insert(make_pair(word[now_layer], next_layer));
                    ptr = next_layer;
                    ++now_layer;
                }
                TrieNode* leaf;
                if (now_layer == other.length()) {
                    leaf = new TrieNode(other);//end
                    ptr->next.insert(make_pair('\n', leaf));
                }
                else{
                    leaf = new TrieNode(other);
                    ptr->next.insert(make_pair(other[now_layer], leaf));
                }
                leaf = new TrieNode(word);
                ptr->next.insert(make_pair(word[now_layer], leaf));
            }
        }
        else {
            if (layer == word.length()) {
                TrieNode* leaf = new TrieNode(word);
                ptr->next.insert(make_pair('\n', leaf));
                return;
            }
            auto iter = ptr->next.find(word[layer]);
            if (iter == ptr->next.end()) {
                TrieNode* leaf = new TrieNode(word);
                ptr->next.insert(make_pair(word[layer], leaf));
            }
            else {
                insert(word, iter->second, layer + 1);
            }
        }
    };
    bool search(string word, TrieNode* ptr, int layer) {
        if (ptr->next.empty()) {
            if (word == ptr->piece)return true;
            else return false;
        }
        else {
            if (word.length() == layer) {
                auto iter = ptr->next.find('\n');
                if (iter == ptr->next.end())return false;
                else return true;
            }
            else {
                auto iter = ptr->next.find(word[layer]);
                if (iter == ptr->next.end())return false;
                else return search(word, iter->second, layer + 1);
            }
        }
    }
    bool startsWith(string word, TrieNode* ptr, int layer) {
        if (ptr->next.empty()) {
            if (word.length() > ptr->piece.length())return false;
            for (int i = layer; i < word.length(); ++i) {
                if (word[i] != ptr->piece[i])return false;
            }
            return true;
        }
        else{
            map<char, TrieNode*>::iterator iter;
            if (layer == word.length()) 
                return true;
            else {
                iter = ptr->next.find(word[layer]);
                if (iter == ptr->next.end())return false;
                else return startsWith(word, iter->second, layer + 1);
            }

        }
    }
public:
    Trie();
    ~Trie();
    // Insert a word into the trie.
    void insert(string word);
    // Return true if the word is in the trie.
    bool search(string word);
     //Return true if there is any word in the trie that starts with the given prefix.
    bool startsWith(string prefix);
};

Trie::Trie() {
    root = new TrieNode;
}
Trie::~Trie() {
    deletenode(root);
}
void Trie::insert(string word) {
    insert(word, root,0);
}


bool Trie::search(string word) {
    return search(word, root, 0);
}
bool Trie::startsWith(string prefix) {
    return startsWith(prefix, root, 0);
}
struct kdNode {
    int key[2];
    kdNode* left, * right;
    kdNode() {
        left = right = NULL;
    }
    kdNode(int in[]) {
        left = right = NULL;
        key[0] = in[0];
        key[1] = in[1];
    }
};
kdNode* emp = NULL;
//// ==================== k-d tree ======================
//struct kdNode{
//    int key[2];  // To store 2 dimensional value
//    kdNode* left = nullptr;
//    kdNode* right = nullptr;
//}
class kdTree {
public:
    kdNode* root;
private:
    void denode(kdNode*& ptr) {
        if (!ptr->left)denode(ptr->left);
        if (!ptr->right)denode(ptr->right);
        delete ptr;
    }
    kdNode* kdmin(kdNode* a1, kdNode* a2, int dim) {
        if (a1 == NULL)return a2;
        else {
            if (a2 == NULL)return a1;
            else{
                if (a1->key[dim] < a2->key[dim])return a1;
                else return a2;
            }
        }
    }
    kdNode* findMin(kdNode* root, int dimCmp, int dim,int& node_dim) {
        if (root == NULL)return NULL;
        else {
            if (dimCmp == dim) {
                if (root->left != NULL)return findMin(root->left, dimCmp, !dim,node_dim);
                else {
                    node_dim = dim;
                    return root;
                }
            }
            else {
                int tmp=0;
                kdNode* a1 = findMin(root->left, dimCmp, !dim,tmp);
                kdNode* a2 = findMin(root->right, dimCmp, !dim,tmp);
                kdNode* min1 = kdmin(a1, a2,dimCmp);
                if (min1 == NULL|| root->key[dimCmp] < min1->key[dimCmp]) {
                    node_dim = dim;
                    return root;
                }
                else {
                    node_dim = tmp;
                    return min1;
                }
            }
        }
    }
    kdNode*& search(kdNode*& root, int arr[], int dim,int m) {
        if (root == NULL)return emp;
        if (root->key[0] == arr[0] && root->key[1] == arr[1])return root;
        else {
            if (root->key[dim] <= arr[dim])return search(root->right, arr, !dim,0);
            else return search(root->left, arr, !dim,0);
        }
    }
    void rangeSearch(kdNode* root, int dim, int lower_bound[], int upper_bound[], vector<struct kdNode*>& ans) {
        if (root == NULL) {
            return;
        }
        if (root->key[0] > lower_bound[0] && root->key[0]<upper_bound[0] && root->key[1]>lower_bound[1] && root->key[1] < upper_bound[1]) {
            ans.push_back(root);
        }
        if (root->key[dim] < lower_bound[dim])rangeSearch(root->right,!dim,lower_bound,upper_bound,ans);
        else {
            if (root->key[dim] > upper_bound[dim])rangeSearch(root->left, !dim, lower_bound, upper_bound, ans);
            else {
                rangeSearch(root->right, !dim, lower_bound, upper_bound, ans);
                rangeSearch(root->left, !dim, lower_bound, upper_bound, ans);
            }
        }
    }
public:
    kdTree() {
        root = NULL;
    };
    ~kdTree(){
        denode(root);
    }
    void insert(kdNode*& root, int arr[], int dim);

    kdNode* search(kdNode* root, int arr[], int dim);

    void remove(kdNode* root, int arr[], int dim);

    kdNode* findMin(kdNode* root, int dimCmp, int dim);

    vector<struct kdNode*> rangeSearch(kdNode* root, int dim, int lower_bound[], int upper_bound[]);
};
void kdTree::insert(kdNode*& root, int arr[], int dim) {
    if (root == NULL) root = new kdNode(arr);
    else {
        if (root->key[dim] < arr[dim])insert(root->right, arr, !dim);
        else insert(root->left, arr, !dim);
    }
}

kdNode* kdTree::search(kdNode* root, int arr[], int dim) {
    if (root == NULL)return NULL;
    if (root->key[0] == arr[0] && root->key[1] == arr[1])return root;
    else {
        if (root->key[dim] <= arr[dim])return search(root->right, arr, !dim);
        else return search(root->left, arr, !dim);
    }
}
void kdTree::remove(kdNode* root, int arr[], int dim) {
    kdNode*& node = search(root, arr, dim,0);
    if (node == NULL)return;
    else {
        if (node->right == NULL && node->left == NULL) {
            delete node;
            node = NULL;
        }
        else {
            if (node->right != NULL) {
                int tmp = 0;
                kdNode* instead = findMin(node, dim, dim, tmp);
                node->key[0] = instead->key[0];
                node->key[1] = instead->key[1];
                remove(instead, node->key, tmp);
            }
            else {
                node->key[0] = node->left->key[0];
                node->key[1] = node->left->key[1];
                remove(node->left, node->key, !dim);
            }
        }
    }
}

kdNode* kdTree::findMin(kdNode* root, int dimCmp, int dim) {
    int a;
    return findMin(root, dimCmp, dim, a);
}


vector<struct kdNode*> kdTree::rangeSearch(kdNode* root, int dim, int lower_bound[], int upper_bound[]) {
    vector<struct kdNode*> ans;
    rangeSearch(root, dim, lower_bound, upper_bound, ans);
    return ans;
}
//    // Insert a new node with 2 dimensional value `arr`.
//    // `dim` refers to the dimension of the root.
//
//    // Search node with value `arr`.
//    // Return NULL if not exist.
//    kdNode* search(kdNode* root, int arr[], int dim);
//    // Delete the node with value `arr`.
//    void remove(kdNode* root, int arr[], int dim);
//
//    // Find the node with the minimum value in dimension `dimCmp`.
//    // `dimCmp` equals to 0 or 1.
//    kdNode* findMin(kdNode* root, int dimCmp, int dim);
//
//    // Find a vector of nodes whose values are >= `lower_bound` and <= `upper_bound`.
//    // `lower_bound` contains lower bound for each dimension of the target nodes.
//    // `upper_bound`, on the contrary, holds upper bound per dimension.
//    // e.g. given lower_bound=[1, 2], upper_bound=[3, 4], node=[2, 3] will be chosen, because 1<=2<=3, 2<=3<=4.
//    vector<struct kdNode*> rangeSearch(kdNode* root, int dim, int lower_bound[], int upper_bound[]);
//}
//
#endif
