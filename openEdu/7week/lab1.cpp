#include <fstream>
#include <stack>

using namespace std;

int maximum(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

class binary_tree {
public:
    struct Node {
        int value;
        int left_child;
        int right_child;
        int balance = -1;
        int height = 0;
        int number;
    };

    binary_tree(ifstream &input, int new_size) : size(new_size) {
        tree = new Node[size + 1];
        int K, L, R;
        for (int i = 1; i <= size; i++) {
            input >> K >> L >> R;
            tree[i] = {K, L, R, 0};
        }
        tree[0] = {0, 0, 0, 0, 0, 0};
        height(&tree[1]);
        balance(&tree[1]);
    }

    void print_balance(ofstream &output) {
        for (int i = 1; i <= size; i++) {
            output << tree[i].balance << '\n';
        }
    }

    void print_tree(ofstream &output) {
        int number = 1;
        numerate(&tree[1], &number);
        output << size << '\n';
        print(output, &tree[1]);
    }

    void rotateRight(Node *node) {
        if (tree[node->left_child].balance == 1) {
            int B = node->left_child;
            int C = tree[B].right_child;
            int X = tree[C].right_child;
            int Y = tree[C].left_child;
            node->left_child = X;
            tree[B].left_child = Y;
            auto temp = *node;
            *node = tree[C];
            tree[C] = temp;
            node->right_child = C;
            node->left_child = B;
        } else {
            int B = node->left_child;
            int Y = tree[node->left_child].right_child;
            tree[B].right_child = B;
            Node temp = tree[B];
            node->left_child = Y;
            tree[B] = *node;
            *node = temp;
        }
    }

    void rotateLeft(Node *node) {
        if (tree[node->right_child].balance == -1) {
            int B = node->right_child;
            int C = tree[B].left_child;
            int X = tree[C].left_child;
            int Y = tree[C].right_child;
            node->right_child = X;
            tree[B].left_child = Y;
            auto temp = *node;
            *node = tree[C];
            tree[C] = temp;
            node->left_child = C;
            node->right_child = B;
        } else {
            int B = node->right_child;
            int Y = tree[node->right_child].left_child;
            tree[B].left_child = B;
            Node temp = tree[B];
            node->right_child = Y;
            tree[B] = *node;
            *node = temp;
        }
    }

private:
    Node *tree;
    int size;

    int height(Node *current_node) {
        if (current_node->right_child == 0 && current_node->left_child == 0) {
            current_node->height = 1;
            return 1;
        }
        int left_h = 0, right_h = 0;
        if (current_node->left_child != 0)
            left_h = height(&tree[current_node->left_child]);
        if (current_node->right_child != 0)
            right_h = height(&tree[current_node->right_child]);
        current_node->height = maximum(left_h, right_h) + 1;
        return current_node->height;
    }

    Node *find(Node *node, int x) {
        if (node->value == x || (node->right_child == 0 && node->left_child == 0))
            return node;
        if (node->value < x) {
            if (node->right_child == 0)
                return node;
            else
                return find(&tree[node->right_child], x);
        } else {
            if (node->left_child == 0)
                return node;
            else
                return find(&tree[node->left_child], x);
        }
    }

    void balance(Node *node) {
        int left_h, right_h;
        left_h = tree[node->left_child].height;
        right_h = tree[node->right_child].height;
        node->balance = right_h - left_h;
        if (left_h == 0 && right_h == 0)
            return;
        if (left_h != 0)
            balance(&tree[node->left_child]);
        if (right_h != 0)
            balance(&tree[node->right_child]);
    }

    void numerate(Node *current_node, int *current_number) {
        current_node->number = (*current_number)++;
        if (current_node->left_child != 0)
            numerate(&tree[current_node->left_child], current_number);
        if (current_node->right_child != 0)
            numerate(&tree[current_node->right_child], current_number);
    }

    void print(ofstream &output, Node *node) {
        output << node->value << ' ';
        if (node->left_child != 0)
            output << tree[node->left_child].number << ' ';
        else
            output << 0 << ' ';
        if (node->right_child != 0)
            output << tree[node->right_child].number << '\n';
        else
            output << 0 << '\n';
        if (node->left_child != 0)
            print(output, &tree[node->left_child]);
        if (node->right_child != 0)
            print(output, &tree[node->right_child]);
    }
};

int main() {
    ifstream input ("input.txt");
    ofstream output("output.txt");

    int n;
    input >> n;
    binary_tree tree(input, n);
    tree.print_balance(output);
}