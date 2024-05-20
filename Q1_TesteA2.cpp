#include <iostream>
#include <cstdlib> // Para malloc e free

struct Node {
    int id;         // ID da música
    Node* next;     // Ponteiro para o próximo nó
    Node* prev;     // Ponteiro para o nó anterior
};

// Função para criar um novo nó
Node* createNode(int id) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (newNode) {
        newNode->id = id;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    return newNode;
}

// Função para inserir um nó na lista duplamente encadeada circular
void insertNode(Node*& head, int id) {
    Node* newNode = createNode(id);
    if (!head) {
        head = newNode;
    } else {
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
    }
}

// Função para inicializar a lista a partir de um array de IDs
void createList(Node*& head, int ids[], int n) {
    head = nullptr;
    for (int i = 0; i < n; ++i) {
        insertNode(head, ids[i]);
    }
}

// Função para obter o ID da música atual
int currentSong(Node* head) {
    if (!head) return -1;
    return head->id;
}

// Função para avançar para a próxima música e obter o ID da música atual
int nextSong(Node*& head) {
    if (!head) return -1;
    head = head->next;
    return head->id;
}

// Função para retroceder para a música anterior e obter o ID da música atual
int prevSong(Node*& head) {
    if (!head) return -1;
    head = head->prev;
    return head->id;
}

// Função para remover um nó por ID
void removeSong(Node*& head, int id) {
    if (!head) return;
    Node* current = head;
    do {
        if (current->id == id) {
            if (current->next == current) { // Apenas um nó na lista
                free(current);
                head = nullptr;
                return;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            if (current == head) head = head->next;
            free(current);
            return;
        }
        current = current->next;
    } while (current != head);
}

// Função para deletar a lista e liberar memória
void deleteList(Node*& head) {
    if (!head) return;
    Node* current = head;
    do {
        Node* next = current->next;
        free(current);
        current = next;
    } while (current != head);
    head = nullptr;
}

// Função para mesclar duas listas alternando as músicas
Node* mergeLists(Node* head1, Node* head2) {
    if (!head1) return head2;
    if (!head2) return head1;

    Node* head = nullptr;
    Node* current1 = head1;
    Node* current2 = head2;
    bool toggle = true; // Alternar entre duas listas

    while (head1 || head2) {
        if (toggle && head1) {
            insertNode(head, current1->id);
            current1 = current1->next;
            if (current1 == head1) head1 = nullptr;
        } else if (!toggle && head2) {
            insertNode(head, current2->id);
            current2 = current2->next;
            if (current2 == head2) head2 = nullptr;
        }
        toggle = !toggle;
    }

    return head;
}

// Função para imprimir a lista
void printList(Node* head) {
    if (!head) return;
    Node* current = head;
    do {
        std::cout << current->id << " ";
        current = current->next;
    } while (current != head);
    std::cout << std::endl;
}

int main() {
    Node* head1 = nullptr;
    Node* head2 = nullptr;

    int ids1[] = {1, 2, 3, 4};
    int ids2[] = {5, 6, 7, 8};

    createList(head1, ids1, 4);
    createList(head2, ids2, 4);

    std::cout << "Lista 1: ";
    printList(head1);
    std::cout << "Lista 2: ";
    printList(head2);

    std::cout << "ID da música atual: " << currentSong(head1) << std::endl;
    std::cout << "ID da próxima música: " << nextSong(head1) << std::endl;
    std::cout << "ID da música atual: " << currentSong(head1) << std::endl;
    std::cout << "ID da música anterior: " << prevSong(head1) << std::endl;
    std::cout << "ID da música atual: " << currentSong(head1) << std::endl;

    removeSong(head1, 3);
    std::cout << "Após remover a música 3, lista 1: ";
    printList(head1);

    Node* mergedList = mergeLists(head1, head2);
    std::cout << "Lista mesclada: ";
    printList(mergedList);

    deleteList(head1);
    deleteList(head2);
    deleteList(mergedList);

    return 0;
}
