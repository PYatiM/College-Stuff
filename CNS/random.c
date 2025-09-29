#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX 100

// --- Linked List ---
struct Node {
    int data;
    struct Node* next;
};

void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// --- Stack ---
int stack[MAX];
int top = -1;

void push(int val) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
    } else {
        stack[++top] = val;
    }
}

int pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return -1;
    } else {
        return stack[top--];
    }
}

int peek() {
    if (top != -1)
        return stack[top];
    return -1;
}

// --- Queue ---
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// --- Binary Search Tree ---
struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
};

struct BSTNode* insertBST(struct BSTNode* node, int data) {
    if (node == NULL) {
        struct BSTNode* new_node = (struct BSTNode*)malloc(sizeof(struct BSTNode));
        new_node->data = data;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

    if (data < node->data)
        node->left = insertBST(node->left, data);
    else if (data > node->data)
        node->right = insertBST(node->right, data);

    return node;
}

void inorderTraversal(struct BSTNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d -> ", root->data);
        inorderTraversal(root->right);
    }
}

// --- AVL Tree ---
struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

int height(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct AVLNode* rightRotate(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct AVLNode* leftRotate(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct AVLNode* insertAVL(struct AVLNode* node, int data) {
    if (node == NULL) {
        struct AVLNode* new_node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
        new_node->data = data;
        new_node->left = new_node->right = NULL;
        new_node->height = 1;
        return new_node;
    }

    if (data < node->data)
        node->left = insertAVL(node->left, data);
    else if (data > node->data)
        node->right = insertAVL(node->right, data);
    else
        return node;

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// --- Sorting Algorithms ---
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// --- Matrix Operations ---
void multiplyMatrices(int A[3][3], int B[3][3], int result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void printMatrix(int mat[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

// --- File Operations ---
void writeToFile(char* filename, char* text) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fputs(text, file);
    fclose(file);
}

void readFromFile(char* filename) {
    char ch;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

// --- Fibonacci Series ---
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

int fibDP(int n) {
    int dp[n+1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

// --- Prime Factorization ---
void primeFactorization(int n) {
    printf("Prime factors of %d are: ", n);
    for (int i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            printf("%d ", i);
            n = n / i;
        }
    }
    if (n > 1)
        printf("%d", n);
    printf("\n");
}

// --- Dijkstra's Algorithm ---
#define INF 9999999
void dijkstra(int graph[5][5], int start) {
    int dist[5], sptSet[5];

    for (int i = 0; i < 5; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
    }

    dist[start] = 0;

    for (int count = 0; count < 4; count++) {
        int u = -1;
        for (int i = 0; i < 5; i++) {
            if (!sptSet[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        sptSet[u] = 1;

        for (int v = 0; v < 5; v++) {
            if (graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Shortest distances from node %d:\n", start);
    for (int i = 0; i < 5; i++) {
        printf("%d: %d\n", i, dist[i]);
    }
}

// --- Knapsack Problem ---
int knapsack(int W, int wt[], int val[], int n) {
    int dp[n + 1][W + 1];
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

int main() {
    int choice, data, index, n, val;
    struct Node* head = NULL;
    struct Queue* queue = createQueue(100);
    struct BSTNode* bstRoot = NULL;
    struct AVLNode* avlRoot = NULL;
    int stackTop = -1;
    int stack[MAX];
    
    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Linked List: Append and Print\n");
        printf("2. Stack: Push, Pop, Peek\n");
        printf("3. Queue: Enqueue, Dequeue\n");
        printf("4. Binary Search Tree: Insert and Inorder Traverse\n");
        printf("5. AVL Tree: Insert and Inorder Traverse\n");
        printf("6. Sorting: QuickSort and MergeSort\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to append to linked list: ");
                scanf("%d", &data);
                append(&head, data);
                printf("Linked list contents: ");
                printList(head);
                break;

            case 2:
                printf("Stack Operations:\n");
                printf(" 1: Push\n 2: Pop\n 3: Peek\n");
                printf("Choose operation: ");
                scanf("%d", &val);
                if (val == 1) {
                    printf("Enter value to push: ");
                    scanf("%d", &data);
                    if (stackTop < MAX - 1) {
                        stack[++stackTop] = data;
                        printf("Pushed %d\n", data);
                    } else {
                        printf("Stack Overflow\n");
                    }
                } else if (val == 2) {
                    if (stackTop >= 0) {
                        printf("Popped %d\n", stack[stackTop--]);
                    } else {
                        printf("Stack Underflow\n");
                    }
                } else if (val == 3) {
                    if (stackTop >= 0) {
                        printf("Top element: %d\n", stack[stackTop]);
                    } else {
                        printf("Stack is empty\n");
                    }
                } else {
                    printf("Invalid operation\n");
                }
                break;

            case 3:
                printf("Queue Operations:\n");
                printf(" 1: Enqueue\n 2: Dequeue\n");
                printf("Choose operation: ");
                scanf("%d", &val);
                if (val == 1) {
                    printf("Enter value to enqueue: ");
                    scanf("%d", &data);
                    enqueue(queue, data);
                } else if (val == 2) {
                    int dequeued = dequeue(queue);
                    if (dequeued != -1) {
                        printf("Dequeued: %d\n", dequeued);
                    }
                } else {
                    printf("Invalid operation\n");
                }
                break;

            case 4:
                printf("Enter value to insert into BST: ");
                scanf("%d", &data);
                bstRoot = insertBST(bstRoot, data);
                printf("BST inorder traversal: ");
                inorderTraversal(bstRoot);
                printf("NULL\n");
                break;

            case 5:
                printf("Enter value to insert into AVL Tree: ");
                scanf("%d", &data);
                avlRoot = insertAVL(avlRoot, data);
                printf("AVL inorder traversal: ");
                inorderTraversal((struct BSTNode*)avlRoot);
                printf("NULL\n");
                break;

            case 6: {
                printf("Enter number of elements for sorting: ");
                scanf("%d", &n);
                int arr[n], arr2[n];
                printf("Enter elements:\n");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                    arr2[i] = arr[i];
                }
                quickSort(arr, 0, n - 1);
                printf("QuickSorted array: ");
                for (int i = 0; i < n; i++)
                    printf("%d ", arr[i]);
                printf("\n");

                mergeSort(arr2, 0, n - 1);
                printf("MergeSorted array: ");
                for (int i = 0; i < n; i++)
                    printf("%d ", arr2[i]);
                printf("\n");
                break;
            }

            case 0:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
