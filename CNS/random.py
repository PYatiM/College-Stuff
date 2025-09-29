class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return
        last = self.head
        while last.next:
            last = last.next
        last.next = new_node

    def print_list(self):
        if not self.head:
            print("The list is empty.")
            return
        temp = self.head
        while temp:
            print(temp.data, end=" -> ")
            temp = temp.next
        print("None")

class Stack:
    def __init__(self):
        self.stack = []

    def push(self, val):
        self.stack.append(val)
        print(f"Pushed {val} onto the stack.")

    def pop(self):
        if self.is_empty():
            print("Stack Underflow")
            return None
        return self.stack.pop()

    def peek(self):
        if self.is_empty():
            return None
        return self.stack[-1]

    def is_empty(self):
        return len(self.stack) == 0

class Queue:
    def __init__(self, capacity=100):
        self.queue = []
        self.capacity = capacity

    def enqueue(self, val):
        if len(self.queue) == self.capacity:
            print("Queue is full")
            return
        self.queue.append(val)
        print(f"Enqueued {val} to the queue.")

    def dequeue(self):
        if self.is_empty():
            print("Queue is empty")
            return None
        return self.queue.pop(0)

    def is_empty(self):
        return len(self.queue) == 0

class BSTNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, root, data):
        if root is None:
            return BSTNode(data)
        if data < root.data:
            root.left = self.insert(root.left, data)
        elif data > root.data:
            root.right = self.insert(root.right, data)
        return root

    def inorder(self, root):
        if root:
            self.inorder(root.left)
            print(root.data, end=" -> ")
            self.inorder(root.right)

class AVLNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1

class AVL:
    def __init__(self):
        self.root = None

    def get_height(self, root):
        if not root:
            return 0
        return root.height

    def get_balance(self, root):
        if not root:
            return 0
        return self.get_height(root.left) - self.get_height(root.right)

    def right_rotate(self, z):
        y = z.left
        T3 = y.right
        y.right = z
        z.left = T3

        z.height = 1 + max(self.get_height(z.left), self.get_height(z.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))
        return y

    def left_rotate(self, z):
        y = z.right
        T2 = y.left
        y.left = z
        z.right = T2

        z.height = 1 + max(self.get_height(z.left), self.get_height(z.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))
        return y

    def insert(self, root, key):
        if not root:
            return AVLNode(key)
        elif key < root.data:
            root.left = self.insert(root.left, key)
        elif key > root.data:
            root.right = self.insert(root.right, key)
        else:
            return root

        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        balance = self.get_balance(root)

        # Left Left
        if balance > 1 and key < root.left.data:
            return self.right_rotate(root)

        # Right Right
        if balance < -1 and key > root.right.data:
            return self.left_rotate(root)

        # Left Right
        if balance > 1 and key > root.left.data:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)

        # Right Left
        if balance < -1 and key < root.right.data:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)

        return root

    def inorder(self, root):
        if root:
            self.inorder(root.left)
            print(root.data, end=" -> ")
            self.inorder(root.right)

def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr)//2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr)//2
        L = arr[:mid]
        R = arr[mid:]

        merge_sort(L)
        merge_sort(R)

        i = j = k = 0
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1
    return arr

def main():
    linked_list = LinkedList()
    stack = Stack()
    queue = Queue()
    bst = BST()
    avl = AVL()

    while True:
        print("\n--- MENU ---")
        print("1. Linked List: Append and Print")
        print("2. Stack: Push, Pop, Peek")
        print("3. Queue: Enqueue, Dequeue")
        print("4. Binary Search Tree: Insert and Inorder Traverse")
        print("5. AVL Tree: Insert and Inorder Traverse")
        print("6. Sorting: QuickSort and MergeSort")
        print("0. Exit")
        choice = input("Enter your choice: ")

        if choice == '1':
            val = int(input("Enter value to append to linked list: "))
            linked_list.append(val)
            print("Linked list contents:")
            linked_list.print_list()

        elif choice == '2':
            print("Stack Operations:")
            print(" 1: Push\n 2: Pop\n 3: Peek")
            op = input("Choose operation: ")
            if op == '1':
                val = int(input("Enter value to push: "))
                stack.push(val)
            elif op == '2':
                popped = stack.pop()
                if popped is not None:
                    print(f"Popped: {popped}")
            elif op == '3':
                top = stack.peek()
                if top is None:
                    print("Stack is empty")
                else:
                    print(f"Top element: {top}")
            else:
                print("Invalid operation")

        elif choice == '3':
            print("Queue Operations:")
            print(" 1: Enqueue\n 2: Dequeue")
            op = input("Choose operation: ")
            if op == '1':
                val = int(input("Enter value to enqueue: "))
                queue.enqueue(val)
            elif op == '2':
                deq = queue.dequeue()
                if deq is not None:
                    print(f"Dequeued: {deq}")
            else:
                print("Invalid operation")

        elif choice == '4':
            val = int(input("Enter value to insert into BST: "))
            bst.root = bst.insert(bst.root, val)
            print("BST inorder traversal: ", end="")
            bst.inorder(bst.root)
            print("None")

        elif choice == '5':
            val = int(input("Enter value to insert into AVL Tree: "))
            avl.root = avl.insert(avl.root, val)
            print("AVL inorder traversal: ", end="")
            avl.inorder(avl.root)
            print("None")

        elif choice == '6':
            n = int(input("Enter number of elements for sorting: "))
            arr = []
            print("Enter elements:")
            for _ in range(n):
                arr.append(int(input()))
            print("QuickSorted array:", quick_sort(arr[:]))
            merge_sorted = arr[:]  # make copy
            merge_sort(merge_sorted)
            print("MergeSorted array:", merge_sorted)

        elif choice == '0':
            print("Exiting program.")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
