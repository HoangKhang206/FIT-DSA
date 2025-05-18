#include <iostream>
using namespace std;
struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

NODE* createNode(int data) {
    NODE* NewNode = new NODE;
    NewNode->key = data;
    NewNode->p_left = NULL;
    NewNode->p_right = NULL;
    NewNode->height = 0;
    return NewNode;
}

int height(NODE* root) {
    if (root == NULL) return 0;
    return root->height;
}

NODE* RotateRight(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;
    x->p_right = y;
    y->p_left = T2;
    y->height = 1 + max(height(y->p_left), height(y->p_right));
    x->height = 1 + max(height(x->p_left), height(x->p_right));
    return x;
}

NODE* RotateLeft(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;
    y->p_left = x;
    x->p_right = T2;
    x->height = 1 + max(height(x->p_left), height(x->p_right));
    y->height = 1 + max(height(y->p_left), height(y->p_right));
    return y;
}

int Balance(NODE* p) {
    if (p == NULL) return 0;
    return height(p->p_left) - height(p->p_right);
}

void Insert(NODE* &pRoot, int x) {
    if (pRoot == NULL) pRoot = createNode(x);
    else {
        if (x < pRoot->key) Insert(pRoot->p_left, x);
        else if(x > pRoot->key) Insert(pRoot->p_right, x);
        else return;
    }
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
    int balance = Balance(pRoot);
    if (balance > 1 && Balance(pRoot->p_left) >= 0) pRoot = RotateRight(pRoot);
    else if (balance > 1 && Balance(pRoot->p_left) < 0) {
        pRoot->p_left = RotateLeft(pRoot->p_left);
        pRoot = RotateRight(pRoot);
    }
    else if (balance < -1 && Balance(pRoot->p_right) <= 0) pRoot = RotateLeft(pRoot);
    else if (balance < -1 && Balance(pRoot->p_right) > 0) {
        pRoot->p_right = RotateRight(pRoot->p_right);
        pRoot = RotateLeft(pRoot);
    }
}

void Remove(NODE* &pRoot, int x) {
    if (pRoot == NULL) return;
    else if (x < pRoot->key) Remove(pRoot->p_left, x);
    else if (x > pRoot->key) Remove(pRoot->p_right, x);
    else {
        if (pRoot->p_left == NULL && pRoot->p_right == NULL) {
            delete pRoot;
            pRoot = NULL;
            return;
        }
        else if (pRoot->p_left == NULL) {
            NODE* temp = pRoot;
            pRoot = pRoot->p_right;
            delete temp;
        }
        else if (pRoot->p_right == NULL) {
            NODE* temp = pRoot;
            pRoot = pRoot->p_left;
            delete temp;
        }
        else {
            NODE* mostr= pRoot->p_left;
            while (mostr->p_right != NULL) mostr = mostr->p_right;
            pRoot->key = mostr->key;
            Remove(pRoot->p_left, mostr->key);
        }
    }
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
    int balance = Balance(pRoot);
    if (balance > 1 && Balance(pRoot->p_left) >= 0) pRoot = RotateRight(pRoot);
    else if (balance > 1 && Balance(pRoot->p_left) < 0) {
        pRoot->p_left = RotateLeft(pRoot->p_left);
        pRoot = RotateRight(pRoot);
    }
    else if (balance < -1 && Balance(pRoot->p_right) <= 0) pRoot = RotateLeft(pRoot);
    else if (balance < -1 && Balance(pRoot->p_right) > 0) {
        pRoot->p_right = RotateRight(pRoot->p_right);
        pRoot = RotateLeft(pRoot);
    }
}

bool isAVL(NODE* pRoot) {
    if (pRoot == NULL) return true;
    int height = Balance(pRoot);
    if(abs(height) > 1) return false;
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}

void preOrder(NODE* root) {
    if (root != NULL) {
        cout << root->key << " ";
        preOrder(root->p_left);
        preOrder(root->p_right);
    }
}

int main()
{
    NODE* root = NULL;

    // Thêm một số phần tử
    Insert(root, 10);
    Insert(root, 20);
    Insert(root, 30);
    Insert(root, 40);
    Insert(root, 50);
    Insert(root, 25);

    cout << "Cây AVL sau khi chèn các phần tử: ";
    preOrder(root);
    cout << endl;

    cout << "Cây AVL sau khi chèn các phần tử:\n";
    cout << "Kiểm tra AVL: " << (isAVL(root) ? "Đúng" : "Sai") << "\n";

    // Xóa phần tử
    Remove(root, 40);
    cout << "Cây AVL sau khi xóa 40:\n";
    cout << "Kiểm tra AVL: " << (isAVL(root) ? "Đúng" : "Sai") << "\n";
    cout << "Cây AVL sau khi chèn các phần tử: ";
    preOrder(root);
    cout << endl;
    Remove(root, 10);
    cout << "Cây AVL sau khi xóa 10:\n";
    cout << "Kiểm tra AVL: " << (isAVL(root) ? "Đúng" : "Sai") << "\n";
    cout << "Cây AVL sau khi chèn các phần tử: ";
    preOrder(root);
    cout << endl;
    Remove(root, 25);
    cout << "Cây AVL sau khi xóa 25:\n";
    cout << "Kiểm tra AVL: " << (isAVL(root) ? "Đúng" : "Sai") << "\n";
    cout << "Cây AVL sau khi chèn các phần tử: ";
    preOrder(root);
    cout << endl;
    return 0;
}
