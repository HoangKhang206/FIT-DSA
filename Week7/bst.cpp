#include <iostream>

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

NODE* Search(NODE* pRoot, int x) {
    if (pRoot == NULL) return NULL;
    if (x == pRoot->key) return pRoot;
    if (x < pRoot->key) return Search(pRoot->p_left, x);
    else return Search(pRoot->p_right, x);
}

void Insert(NODE* &pRoot, int x) {
    if (pRoot == NULL) pRoot = createNode(x);
    else {
        if (x < pRoot->key) {
            Insert(pRoot->p_left, x);
        }
        else {
            Insert(pRoot->p_right, x);
        }
    }
}

void Remove(NODE* &pRoot, int x) {
    if (pRoot == NULL) return;
    if (x < pRoot->key) Remove(pRoot->p_left, x);
    else if (x > pRoot->key) Remove(pRoot->p_right, x);
    else {
        if (pRoot->p_left == NULL && pRoot->p_right == NULL) {
            delete pRoot;
            pRoot = NULL;
        }
        else if (pRoot->p_left == NULL) {
            NODE *pTemp = pRoot;
            pRoot = pRoot->p_right;
            delete pTemp;
        }
        else if (pRoot->p_right == NULL) {
            NODE *pTemp = pRoot;
            pRoot = pRoot->p_left;
            delete pTemp;
        }
        else {
            NODE *mostr = pRoot->p_left;
            while (mostr->p_right != NULL) mostr = mostr->p_right;
            pRoot->key = mostr->key;
            Remove(pRoot->p_left, mostr->key);
        }
    }
}

NODE* createTree(int a[], int n) {
    NODE *root = NULL;
    for (int i = 0; i < n; i++) {
        Insert(root, a[i]);
    }
    return root;
}

void removeTree(NODE* &pRoot) {
    if (pRoot == NULL) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = NULL;
}

int Height(NODE* pRoot) {
    if (pRoot == NULL) return -1;
    return 1 + max(Height(pRoot->p_left), Height(pRoot->p_right));
}

int countLess(NODE* pRoot, int x) {
    if (pRoot == NULL) return 0;
    if (x > pRoot->key) return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    else return countLess(pRoot->p_left, x);
}

int countGreater(NODE* pRoot, int x) {
    if (pRoot == NULL) return 0;
    if(x < pRoot->key) return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    else return countGreater(pRoot->p_right, x);
}

bool isBSTtemp(NODE* pRoot, int Min, int Max) {
    if (pRoot == NULL) return true;
    if (pRoot->key <= Min || pRoot->key >= Max) return false;
    return isBSTtemp(pRoot->p_left, Min, pRoot->key) && isBSTtemp(pRoot->p_right, pRoot->key, Max);
}

bool isBST(NODE* pRoot) {
    return isBSTtemp(pRoot, INT_MIN, INT_MAX);
}

bool isFullBSTtemp(NODE* pRoot) {
    if (pRoot == NULL) return true;
    if ((pRoot->p_left == NULL && pRoot->p_right != NULL) || (pRoot->p_left != NULL && pRoot->p_right == NULL)) return false;
    return isFullBSTtemp(pRoot->p_left) && isFullBSTtemp(pRoot->p_right);
}

bool isFullBST(NODE* pRoot) {
    return isFullBSTtemp(pRoot) && isBST(pRoot);
}

int main()
{
    int a[] = {10, 5, 15, 3, 7, 13, 17}; // Một cây nhị phân tìm kiếm đầy đủ (Full BST)
    int n = sizeof(a) / sizeof(a[0]);

    NODE* root = createTree(a, n);

    cout << "Cay duoc tao thanh cong.\n";

    // Chiều cao cây
    cout << "Chieu cao cua cay: " << Height(root) << endl;

    // Đếm số node nhỏ hơn một giá trị
    int x = 12;
    cout << "So node co gia tri nho hon " << x << ": " << countLess(root, x) << endl;

    // Đếm số node lớn hơn một giá trị
    cout << "So node co gia tri lon hon " << x << ": " << countGreater(root, x) << endl;

    // Kiểm tra BST
    cout << "Cay la BST? " << (isBST(root) ? "Yes" : "No") << endl;

    // Kiểm tra full BST
    cout << "Cay la Full BST? " << (isFullBST(root) ? "Yes" : "No") << endl;

    // Tìm kiếm
    int searchKey = 7;
    NODE* found = Search(root, searchKey);
    cout << "Tim thay " << searchKey << "? " << (found ? "Yes" : "No") << endl;

    // Xóa 1 node
    int delKey = 5;
    cout << "Xoa node co khoa " << delKey << "." << endl;
    Remove(root, delKey);
    cout << "Cay sau khi xoa " << delKey << " la BST? " << (isBST(root) ? "Yes" : "No") << endl;

    // Giải phóng bộ nhớ
    removeTree(root);
    cout << "Da giai phong cay." << endl;

    return 0;
}
