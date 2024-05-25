#include <iostream>

class LinkedList {
public:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAt(int index, int value) {
        if (index < 0 || index > size) {
            std::cout << "Index out of bounds." << std::endl;
            return;
        }

        Node* newNode = new Node(value);

        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        ++size;
    }

    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index out of bounds." << std::endl;
            return;
        }

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
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

        Node* oldTail = head;
        Node* newTail = head;
        Node* newHead = head;
        int steps = size - k - 1;

        while (oldTail->next) {
            oldTail = oldTail->next;
        }
        for (int i = 0; i < steps; ++i) {
            newTail = newTail->next;
        }

        newHead = newTail->next;
        oldTail->next = head;
        head = newHead;
        newTail->next = nullptr;
    }

    void reverse() {
        if (isEmpty()) return;

        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        ++size;
    }

    void prepend(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        ++size;
    }

    void merge(LinkedList& other) {
        if (other.isEmpty()) return;
        if (isEmpty()) {
            head = other.head;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = other.head;
        }
        size += other.size;
        other.head = nullptr;
        other.size = 0;
    }

    void interleave(LinkedList& other) {
        Node* p1 = head;
        Node* p2 = other.head;
        Node* next1 = nullptr;
        Node* next2 = nullptr;

        while (p1 && p2) {
            next1 = p1->next;
            next2 = p2->next;

            p1->next = p2;
            p2->next = next1;

            p1 = next1;
            p2 = next2;
        }

        other.head = nullptr;
        other.size = 0;
        size += other.size;
    }

    int getMiddle() const {
        if (isEmpty()) throw std::runtime_error("List is empty");

        Node* slow = head;
        Node* fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow->data;
    }

    int indexOf(int value) const {
        Node* current = head;
        int index = 0;

        while (current) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            ++index;
        }

        return -1;
    }

    void splitAt(int index, LinkedList& secondList) {
        if (index < 0 || index >= size) {
            std::cout << "Index out of bounds." << std::endl;
            return;
        }

        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }

        secondList.head = current->next;
        current->next = nullptr;
        secondList.size = size - index - 1;
        size = index + 1;
    }

    void printList() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

private:
    Node* head;
    int size;
};

int main() {
    LinkedList list;

    list.insertAt(0, 10);
    list.insertAt(1, 20);
    list.insertAt(2, 30);
    list.insertAt(1, 15);

    list.printList();
    std::cout << "Size of the list: " << list.getSize() << std::endl;

    list.deleteAt(1);
    list.printList();
    std::cout << "Size of the list: " << list.getSize() << std::endl;

    list.append(40);
    list.printList();
    list.prepend(5);
    list.printList();

    list.reverse();
    list.printList();

    list.rotateRight(2);
    list.printList();

    std::cout << "Middle element: " << list.getMiddle() << std::endl;
    std::cout << "Index of 20: " << list.indexOf(20) << std::endl;

    LinkedList secondList;
    list.splitAt(2, secondList);
    list.printList();
    secondList.printList();

    LinkedList list2;
    list2.append(50);
    list2.append(60);
    list2.append(70);

    list.merge(list2);
    list.printList();

    LinkedList list3;
    list3.append(100);
    list3.append(200);

    list.interleave(list3);
    list.printList();

    return 0;
}
