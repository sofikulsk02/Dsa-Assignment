#include <iostream>
class DynamicArray {
public:
    DynamicArray(int capacity = 10, int resizeFactor = 2.0) 
        : size(0), capacity(capacity), resizeFactor(resizeFactor) {
        arr = new int[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void insertAt(int index, int value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of bounds");
        }
        if (size == capacity) {
            resize(static_cast<int>(capacity * resizeFactor));
        }
        for (int i = size; i > index; --i) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        ++size;
    }

    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --size;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void rotateRight(int k) {
        if (isEmpty() || k <= 0) return;
        k = k % size;
        if (k == 0) return;

        reverseSection(0, size - 1);
        reverseSection(0, k - 1);
        reverseSection(k, size - 1);
    }

    void reverse() {
        reverseSection(0, size - 1);
    }

    void append(int value) {
        if (size == capacity) {
            resize(static_cast<int>(capacity * resizeFactor));
        }
        arr[size++] = value;
    }

    void prepend(int value) {
        insertAt(0, value);
    }

    void merge(const DynamicArray& other) {
        while (size + other.size > capacity) {
            resize(static_cast<int>(capacity * resizeFactor));
        }
        for (int i = 0; i < other.size; ++i) {
            arr[size++] = other.arr[i];
        }
    }

    void interleave(const DynamicArray& other) {
        DynamicArray result(size + other.size, resizeFactor);
        int i = 0, j = 0;
        while (i < size || j < other.size) {
            if (i < size) {
                result.append(arr[i++]);
            }
            if (j < other.size) {
                result.append(other.arr[j++]);
            }
        }
        *this = result;
    }

    int getMiddle() const {
        if (isEmpty()) {
            throw std::runtime_error("Array is empty");
        }
        return arr[size / 2];
    }

    int indexOf(int value) const {
        for (int i = 0; i < size; ++i) {
            if (arr[i] == value) {
                return i;
            }
        }
        return -1;
    }

    void splitAt(int index, DynamicArray& secondArray) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        secondArray.clear();
        for (int i = index; i < size; ++i) {
            secondArray.append(arr[i]);
        }
        size = index;
    }

    void clear() {
        size = 0;
    }

    void printArray() const {
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    int* arr;
    int size;
    int capacity;
    double resizeFactor;

    void resize(int newCapacity) {
        int* newArr = new int[newCapacity];
        for (int i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

    void reverseSection(int start, int end) {
        while (start < end) {
            std::swap(arr[start], arr[end]);
            ++start;
            --end;
        }
    }
};

int main() {
    DynamicArray arr(5);

    arr.append(10);
    arr.append(20);
    arr.append(30);
    arr.append(40);
    arr.append(50);

    arr.printArray();

    arr.insertAt(2, 25);
    arr.printArray();

    arr.deleteAt(3);
    arr.printArray();

    arr.prepend(5);
    arr.printArray();

    arr.reverse();
    arr.printArray();

    arr.rotateRight(2);
    arr.printArray();

    std::cout << "Size: " << arr.getSize() << std::endl;
    std::cout << "Is empty: " << (arr.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Middle element: " << arr.getMiddle() << std::endl;
    std::cout << "Index of 25: " << arr.indexOf(25) << std::endl;

    DynamicArray arr2;
    arr2.append(60);
    arr2.append(70);
    arr2.append(80);

    arr.merge(arr2);
    arr.printArray();

    DynamicArray arr3;
    arr3.append(100);
    arr3.append(200);

    arr.interleave(arr3);
    arr.printArray();

    DynamicArray splitArray;
    arr.splitAt(5, splitArray);
    arr.printArray();
    splitArray.printArray();

    return 0;
}
