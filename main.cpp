#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// ==========================================
// 1. БІНАРНЕ ДЕРЕВО ПОШУКУ (BST)
// ==========================================
struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int val) : key(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BSTNode* root;

    BST() : root(nullptr) {}

    BSTNode* insert(BSTNode* node, int val) {
        if (node == nullptr) {
            return new BSTNode(val);
        }
        if (val < node->key) {
            node->left = insert(node->left, val);
        } else if (val > node->key) {
            node->right = insert(node->right, val);
        }
        return node;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    BSTNode* findMin(BSTNode* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    BSTNode* remove(BSTNode* node, int val) {
        if (node == nullptr) return nullptr;

        if (val < node->key) {
            node->left = remove(node->left, val);
        } else if (val > node->key) {
            node->right = remove(node->right, val);
        } else {
            if (node->left != nullptr && node->right != nullptr) {
                BSTNode* minRight = findMin(node->right);
                node->key = minRight->key;
                node->right = remove(node->right, minRight->key);
            } else {
                BSTNode* temp = (node->left != nullptr) ? node->left : node->right;
                delete node;
                return temp;
            }
        }
        return node;
    }

    void remove(int val) {
        root = remove(root, val);
    }

    void inorder(BSTNode* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    void preorder(BSTNode* node) {
        if (node != nullptr) {
            cout << node->key << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(BSTNode* node) {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            cout << node->key << " ";
        }
    }

    int height(BSTNode* node) {
        if (node == nullptr) return 0;
        int lh = height(node->left);
        int rh = height(node->right);
        return 1 + (lh > rh ? lh : rh);
    }
};

// ==========================================
// 2. ЧЕРВОНО-ЧОРНЕ ДЕРЕВО (RB TREE)
// ==========================================
enum Color { RED, BLACK };

struct RBNode {
    int key;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int val, Color col = RED)
        : key(val), color(col), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* NIL;

    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL || x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(RBNode* y) {
        RBNode* x = y->left;
        y->left = x->right;
        if (x->right != NIL) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == NIL || y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
    }

    void fixInsert(RBNode* z) {
        while (z->parent != NIL && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* uncle = z->parent->parent->right;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                RBNode* uncle = z->parent->parent->left;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(RBNode* u, RBNode* v) {
        if (u->parent == NIL || u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    RBNode* minimum(RBNode* node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

    void fixDelete(RBNode* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBNode* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                RBNode* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

public:
    RedBlackTree() {
        NIL = new RBNode(0, BLACK);
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = NIL;
        root = NIL;
    }

    void insert(int key) {
        RBNode* z = new RBNode(key, RED);
        z->left = NIL;
        z->right = NIL;

        RBNode* y = NIL;
        RBNode* x = root;

        while (x != NIL) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == NIL) {
            root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }

        fixInsert(z);
    }

    RBNode* search(int k) {
        RBNode* x = root;
        while (x != NIL && x->key != k) {
            if (k < x->key) x = x->left;
            else x = x->right;
        }
        return x;
    }

    void remove(int key) {
        RBNode* z = search(key);
        if (z == NIL) return;

        RBNode* y = z;
        Color y_original_color = y->color;
        RBNode* x;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;

        if (y_original_color == BLACK) {
            fixDelete(x);
        }
    }

    void inorder(RBNode* node) {
        if (node != NIL) {
            inorder(node->left);
            cout << node->key << (node->color == RED ? "(R) " : "(B) ");
            inorder(node->right);
        }
    }

    void preorder(RBNode* node) {
        if (node != NIL) {
            cout << node->key << (node->color == RED ? "(R) " : "(B) ");
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(RBNode* node) {
        if (node != NIL) {
            postorder(node->left);
            postorder(node->right);
            cout << node->key << (node->color == RED ? "(R) " : "(B) ");
        }
    }

    int height(RBNode* node) {
        if (node == NIL) return 0;
        int lh = height(node->left);
        int rh = height(node->right);
        return 1 + (lh > rh ? lh : rh);
    }

    int blackHeight() {
        int bh = 0;
        RBNode* curr = root;
        while (curr != NIL) {
            if (curr->color == BLACK) bh++;
            curr = curr->left;
        }
        return bh;
    }

    RBNode* getRoot() { return root; }
};

int main() {
    cout << "========================================================\n";
    cout << "  Laboratorna robota No. 7: BST & Red-Black Tree\n";
    cout << "  Variant 5. Student: Velieva L.A., Group AI-253\n";
    cout << "========================================================\n\n";

    vector<int> data = {95, 43, 98, 41, 68, 67, 10, 7, 69};

    cout << "Input sequence: ";
    for (int v : data) cout << v << " ";
    cout << "\n\n";

    // 1. BST
    BST bst;
    for (int v : data) bst.insert(v);

    cout << "--- 1. RESULTS FOR BINARY SEARCH TREE (BST) ---\n";
    cout << "BST Height: " << bst.height(bst.root) << "\n";
    cout << "Inorder:   "; bst.inorder(bst.root); cout << "\n";
    cout << "Preorder:  "; bst.preorder(bst.root); cout << "\n";
    cout << "Postorder: "; bst.postorder(bst.root); cout << "\n\n";

    // 2. Red-Black Tree
    RedBlackTree rbt;
    for (int v : data) rbt.insert(v);

    cout << "--- 2. RESULTS FOR RED-BLACK TREE (RB TREE) ---\n";
    cout << "RB Height:       " << rbt.height(rbt.getRoot()) << "\n";
    cout << "RB Black Height: " << rbt.blackHeight() << "\n";
    cout << "Inorder:   "; rbt.inorder(rbt.getRoot()); cout << "\n";
    cout << "Preorder:  "; rbt.preorder(rbt.getRoot()); cout << "\n";
    cout << "Postorder: "; rbt.postorder(rbt.getRoot()); cout << "\n\n";

    // 3. Deletion BST
    cout << "--- 3. DELETION FROM BST ---\n";
    cout << "1) Delete right root node 98:\n";
    bst.remove(98);
    cout << "   Inorder: "; bst.inorder(bst.root); cout << "\n";

    cout << "2) Delete left root node 43:\n";
    bst.remove(43);
    cout << "   Inorder: "; bst.inorder(bst.root); cout << "\n";

    cout << "3) Delete main root node 95:\n";
    bst.remove(95);
    cout << "   Inorder: "; bst.inorder(bst.root); cout << "\n\n";

    // 4. Deletion RB Tree
    cout << "--- 4. DELETION FROM RED-BLACK TREE ---\n";
    cout << "1) Delete black node 98:\n";
    rbt.remove(98);
    cout << "   Inorder: "; rbt.inorder(rbt.getRoot()); cout << "\n";

    cout << "2) Delete black root node 95:\n";
    rbt.remove(95);
    cout << "   Inorder: "; rbt.inorder(rbt.getRoot()); cout << "\n";

    cout << "3) Delete black node 67:\n";
    rbt.remove(67);
    cout << "   Inorder: "; rbt.inorder(rbt.getRoot()); cout << "\n\n";

    cout << "========================================================\n";
    cout << "  Program finished successfully!\n";
    cout << "========================================================\n";

    return 0;
}
