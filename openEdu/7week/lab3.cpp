#include <fstream>
#include <vector>

using namespace std;

int maximum(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

class AVL_tree {
public:
    struct Node {
        int value;
        Node *left_child;
        Node *right_child;
        int height;
        int number;
    };

    AVL_tree(ifstream &input, int n) {
        int K, L, R;
        vector<Node *> parents(n + 1);
        for (int i = 1; i <= n; i++) {
            input >> K >> L >> R;
            Node *new_node = new Node{K, nullptr, nullptr, 0, 0};
            parents[L] = new_node;
            parents[R] = new_node;
            if (i == 1) {
                tree = new_node;
            } else {
                if (K < parents[i]->value) {
                    parents[i]->left_child = new_node;
                } else {
                    parents[i]->right_child = new_node;
                }
            }
        }
        height(tree);
    }

    AVL_tree() {
        tree = nullptr;
    }

    void rotate_right(Node *node) {
        if (count_balance(node->left_child) == 1) {
            Node *A = node;
            Node *B = node->left_child;
            Node *C = B->right_child;
            Node *X = C->left_child;
            Node *Y = C->right_child;

            B->right_child = X;
            A->left_child = Y;
            swap(*A, *C);
            A->left_child = B;
            A->right_child = C;
            fix_height(C);
            fix_height(B);
            fix_height(A);
        } else {
            Node *B = node->left_child;
            Node *Y = B->right_child;
            Node *A = node;

            A->left_child = Y;
            swap(*A, *B);
            A->right_child = B;
            fix_height(B);
            fix_height(A);
        }
    }

    void rotate_left(Node *node) {
        if (count_balance(node->right_child) == -1) {
            Node *A = node;
            Node *B = node->right_child;
            Node *C = B->left_child;
            Node *X = C->left_child;
            Node *Y = C->right_child;

            A->right_child = X;
            B->left_child = Y;

            Node temp = *C;
            *C = *A;
            *A = temp;

            A->left_child = C;
            A->right_child = B;
            fix_height(C);
            fix_height(B);
            fix_height(A);
        } else {
            Node *B = node->right_child;
            Node *Y = B->left_child;
            Node *A = node;

            A->right_child = Y;

            Node temp = *B;
            *B = *A;
            *A = temp;

            A->left_child = B;
            fix_height(B);
            fix_height(A);
        }
    }

    void print_tree(ofstream &output) {
        int counter = 1;
        numerate(tree, &counter);
        output << counter - 1 << '\n';
        print(output, tree);
    }

    void insert(int value) {
        tree = append(tree, value);
    }

    void remove(int value) {
        tree = remove(tree, value);
    }

    int root_balance() {
        if (tree != nullptr) {
            return count_balance(tree);
        } else {
            return 0;
        }
    }

    bool contains(int x) {
        Node* temp = find(tree, x);
        if (temp != nullptr) {
            return temp->value == x;
        } else {
            return false;
        }
    }

private:
    Node *find(Node *node, int x) {
        if (node == nullptr)
            return node;
        if (node->value == x) {
            return node;
        }
        if (node->value < x) {
            if (node->right_child == nullptr) {
                return node;
            } else {
                return find(node->right_child, x);
            }
        } else {
            if (node->left_child == nullptr) {
                return node;
            } else {
                return find(node->left_child, x);
            }
        }
    }

    Node* max_right(Node* node) {
        while (node->right_child != nullptr) {
            node = node->right_child;
        }
        return node;
    }

    Node* remove(Node* node, int value) {
        if (node == nullptr || node->value == value) {
            if (node == nullptr)
                return node;
            if (node->right_child == nullptr && node->left_child == nullptr) {
                return nullptr;
            }
            if (node->left_child == nullptr) {
                return node->right_child;
            }
            Node* m_right = max_right(node->left_child);
            node->value = m_right->value;
            node->left_child = remove(node->left_child, m_right->value);
        }
        if (node->value < value) {
            node->right_child = remove(node->right_child, value);
        } else {
            node->left_child = remove(node->left_child, value);
        }
        return balance(node);
    }

    Node* append(Node* node, int value) {
        if (node == nullptr || node->value == value) {
            if (node != nullptr) {
                return node;
            } else {
                return new Node{value, nullptr, nullptr, 1, 0};
            }
        }
        if (node->value < value) {
            node->right_child = append(node->right_child, value);
        } else {
            node->left_child = append(node->left_child, value);
        }
        return balance(node);
    }

    Node *balance(Node *node) {
        fix_height(node);
        if (count_balance(node) == 2) {
            rotate_left(node);
            return node;
        }
        if (count_balance(node) == -2) {
            rotate_right(node);
            return node;
        }
        return node;
    }

    int count_balance(Node *node) {
        if (node == nullptr)
            return 0;
        int left_h = 0, right_h = 0;
        if (node->right_child != nullptr) {
            right_h = node->right_child->height;
        }
        if (node->left_child != nullptr) {
            left_h = node->left_child->height;
        }
        return right_h - left_h;
    }

    void fix_height(Node *node) {
        int h = 0;
        if (node->left_child != nullptr) {
            h = node->left_child->height;
        }
        if (node->right_child != nullptr) {
            h = maximum(h, node->right_child->height);
        }
        node->height = ++h;
    }

    int height(Node *node) {
        if (node == nullptr)
            return 0;
        int h = 0;
        if (node->left_child != nullptr) {
            h = maximum(h, height(node->left_child));
        }
        if (node->right_child != nullptr) {
            h = maximum(h, height(node->right_child));
        }
        node->height = ++h;
        return h;
    }

    void numerate(Node *node, int *current_number) {
        if (node == nullptr)
            return;
        node->number = (*current_number)++;
        if (node->left_child != nullptr) {
            numerate(node->left_child, current_number);
        }
        if (node->right_child != nullptr) {
            numerate(node->right_child, current_number);
        }
    }

    void print(ofstream &output, Node *node) {
        if (node == nullptr)
            return;
        output << node->value << ' ';
        if (node->left_child != nullptr) {
            output << node->left_child->number << ' ';
        } else {
            output << 0 << ' ';
        }
        if (node->right_child != nullptr) {
            output << node->right_child->number << '\n';
        } else {
            output << 0 << '\n';
        }
        if (node->left_child != nullptr) {
            print(output, node->left_child);
        }
        if (node->right_child != nullptr) {
            print(output, node->right_child);
        }
    }

    Node *tree = nullptr;
};

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n, x;
    char command;
    input >> n;

    AVL_tree tree(input, n);
    input >> x;
    tree.insert(x);
    tree.print_tree(output);
}
