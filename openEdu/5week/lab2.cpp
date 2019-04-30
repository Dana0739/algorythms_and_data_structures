#include <fstream>
#include <iostream>

using namespace std;

class Heap {
public:
    Heap() : heap(new Node[1'000'001]), size(0), positions(new int[1'000'001]) {}

    struct Node {
        int position;
        int value;

        bool operator<(const Node &rhs) {
            return value < rhs.value;
        }
    };

    int get_size() {
        return size;
    }

    void append(int value, int position) {
        heap[++size] = {position, value};
        positions[position] = size;
        siftUp(size);
    }

    int remove() {
        int result = heap[1].value;
        heap[1] = heap[size--];
        positions[heap[1].position] = 1;
        heapify(1);
        return result;
    }

    void change(int position, int new_value) {
        heap[positions[position]].value = new_value;
        siftUp(positions[position]);
    }

    void printStats() {
        for (int i = 1; i <= size; i++)
            cout << '{' << heap[i].value << " : " << heap[i].position << "} ";
        cout << '\n';
        for (int i = 1; i <= size; i++)
            cout << '{' << positions[i] << "} ";
        cout << '\n';
    }

private:
    void siftUp(int index) {
        while (heap[index] < heap[index / 2] && index > 1) {
            swap(positions[heap[index].position], positions[heap[index / 2].position]);
            swap(heap[index], heap[index / 2]);
            index /= 2;
        }
    }

    int min_index(int index1, int index2, int index3) {
        int min = index1;
        Node min_result = heap[index1];
        if (heap[index2] < min_result) {
            min_result = heap[index2];
            min = index2;
        }
        if (heap[index3] < min_result) {
            min = index3;
        }
        return min;
    }

    void heapify(int index) {
        int prev_index;
        while (index * 2 <= size) {
            prev_index = index;
            if (index * 2 + 1 <= size) {
                index = min_index(index, index * 2, index * 2 + 1);
            } else {
                index = min_index(index, index, index * 2);
            }
            if (index == prev_index)
                break;
            swap(positions[heap[prev_index].position], positions[heap[index].position]);
            swap(heap[prev_index], heap[index]);
        };
    }


    Node *heap;
    int *positions;
    int size;
};

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n, number1, number2;
    input >> n;
    Heap heap;

    char temp;
    for (int i = 1; i <= n; i++) {
        input >> temp;
        if (temp == 'A') {
            input >> number1;
            heap.append(number1, i);
            //heap.printStats();
            continue;
        }
        if (temp == 'X') {
            if (heap.get_size() == 0) {
                output << '*' << '\n';
            } else {
                output << heap.remove() << '\n';
            }
            //heap.printStats();
            continue;
        }
        if (temp == 'D') {
            input >> number1 >> number2;
            heap.change(number1, number2);
            //heap.printStats();
        }
    }
}
