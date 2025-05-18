#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
struct NODE {
    int key;
    NODE *p_left;
    NODE *p_right;
};

NODE* createNode(int data) {
    NODE *NewNode = new NODE;
    NewNode->key = data;
    NewNode->p_left = NULL;
    NewNode->p_right = NULL;
    return NewNode;
}

vector<int> NLR(NODE* pRoot) {
    vector<int> v;
    stack<NODE*> S;
    S.push(pRoot);
    while(!S.empty()) {
        NODE *p = S.top();
        S.pop();
        v.push_back(p->key);
        if(p->p_right != NULL) S.push(p->p_right);
        if(p->p_left != NULL) S.push(p->p_left);
    }
    return v;
}

vector<int> LNR(NODE* pRoot) {
    vector<int> v;
    stack<NODE*> S;
    NODE *p = pRoot;
    while (p != NULL || !S.empty()) {
        while (p != NULL) {
            S.push(p);
            p = p->p_left;
        }
        p = S.top();
        S.pop();
        v.push_back(p->key);
        p = p->p_right;
    }
    return v;
}

void LRNtemp(NODE* pRoot, vector<int>& v) {
    if(pRoot == NULL) return;
    LRNtemp(pRoot->p_left, v);
    LRNtemp(pRoot->p_right, v);
    v.push_back(pRoot->key);
}
vector<int> LRN(NODE* pRoot) {
    vector<int> v;
    LRNtemp(pRoot, v);
    return v;
}

void LevelOrdertemp(NODE* pRoot, int level, vector<vector<int>> &res) {
    if (pRoot == NULL) return;
    if (res.size() == level) res.push_back(vector<int>());
    res[level].push_back(pRoot->key);
    LevelOrdertemp(pRoot->p_left, level+1, res);
    LevelOrdertemp(pRoot->p_right, level+1, res);
}

vector<vector<int>> LevelOrder(NODE* pRoot) {
    vector<vector<int>> res;
    LevelOrdertemp(pRoot, 0, res);
    return res;
}

int countNode(NODE* pRoot) {
    if (pRoot == NULL) return 0;
    return 1+ countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot) {
    if (pRoot == NULL) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

NODE* findNode(NODE* pRoot, int key) {
    if (pRoot == NULL) return NULL;
    if (pRoot->key == key) return pRoot;
    NODE* findleft = findNode(pRoot->p_left, key);
    if (findleft != NULL) return findleft;
    return findNode(pRoot->p_right, key);
}

int getheight(NODE* pRoot) {
    if (pRoot == NULL) return -1;
    return 1 + max(getheight(pRoot->p_left), getheight(pRoot->p_right));
}

int heightNode(NODE* pRoot, int value) {
    return getheight(findNode(pRoot, value));
}

int Leveltemp(NODE* pRoot, NODE* p, int level) {
    if (pRoot == NULL) return -1;
    if (pRoot == p) return level;
    int left = Leveltemp(pRoot->p_left, p, level+1);
    if (left != -1) return left;
    return Leveltemp(pRoot->p_right, p, level+1);
}

int Level(NODE* pRoot, NODE* p) {
    return Leveltemp(pRoot, p, 0);
}

int countLeaf(NODE* pRoot) {
    if (pRoot == NULL) return 0;
    if (pRoot->p_left == NULL && pRoot->p_right == NULL) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}

int main()
{
    // Tạo cây nhị phân mẫu
    NODE* root = createNode(10);
    root->p_left = createNode(5);
    root->p_right = createNode(15);
    root->p_left->p_left = createNode(3);
    root->p_left->p_right = createNode(6);
    root->p_right->p_right = createNode(20);

    // Test các hàm
    vector<int> NLRresult = NLR(root);
    vector<int> LNRresult = LNR(root);
    vector<int> LRNresult = LRN(root);
    vector<vector<int>> LevelOrderResult = LevelOrder(root);

    cout << "NLR (Pre-order): ";
    for (int i = 0; i < NLRresult.size(); i++) {
        cout << NLRresult[i]<<" ";
    }
    cout << endl;

    cout << "LNR (In-order): ";
    for (int i = 0; i < LNRresult.size(); i++) {
        cout << LNRresult[i]<<" ";
    }
    cout << endl;

    cout << "LRN (Post-order): ";
    for (int i = 0; i < LRNresult.size(); i++) {
        cout << LRNresult[i]<<" ";
    }
    cout << endl;

    cout << "Level Order: " << endl;
   for (int i = 0; i < LevelOrderResult.size(); i++) {
       for(int j=0;j< LevelOrderResult[i].size();j++) {
           cout << LevelOrderResult[i][j]<<" ";
       }
       cout << endl;
   }

    cout << "Total number of nodes: " << countNode(root) << endl;
    cout << "Sum of all nodes: " << sumNode(root) << endl;
    cout << "Height of tree: " << heightNode(root,10) << endl;

    NODE* foundNode = findNode(root, 6);
    if (foundNode != NULL) {
        cout << "Node with key 6 found." << endl;
    } else {
        cout << "Node with key 6 not found." << endl;
    }

    cout << "Height of node with value 6: " << heightNode(root, 6) << endl;
    cout << "Level of node with value 6: " << Level(root, foundNode) << endl;
    cout << "Number of leaf nodes: " << countLeaf(root) << endl;

    return 0;
}
