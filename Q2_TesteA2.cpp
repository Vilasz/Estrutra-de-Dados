#include <iostream>
#include <cstdlib> // Para malloc e free

using std::endl;

struct Node {
    int id;         // ID da música
    Node* next;     // Ponteiro para o próximo nó
    Node* prev;     // Ponteiro para o nó anterior
};

// Função para criar um novo nó
Node* createNode(int id) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->id = id;
    newNode->next = nullptr; // Certifique-se de inicializar com nullptr
    newNode->prev = nullptr; // Certifique-se de inicializar com nullptr
    return newNode;
}

// Função para inserir um nó na lista duplamente encadeada (não circular)
void insertNode(Node*& head, Node*& tail, int id) {
    Node* newNode = createNode(id);
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Função para verificar se há um loop avançando
bool hasForwardLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) return true; // Loop detectado
    }

    return false; // Sem loop
}

// Função para verificar se há um loop retrocedendo
bool hasBackwardLoop(Node* tail) {
    Node* slow = tail;
    Node* fast = tail;

    while (fast && fast->prev) {
        slow = slow->prev;
        fast = fast->prev->prev;

        if (slow == fast) return true; // Loop detectado
    }

    return false; // Sem loop
}

// Função principal para verificar ambos os loops
bool hasLoop(Node* head, Node* tail) {
    return hasForwardLoop(head) || hasBackwardLoop(tail);
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    // Caso sem loop
    insertNode(head, tail, 1);
    insertNode(head, tail, 2);
    insertNode(head, tail, 3);
    insertNode(head, tail, 4);

    std::cout << "Testando lista sem loop (1, 2, 3, 4): ";
    bool loopExists = hasLoop(head, tail);
    std::cout << (loopExists ? "Loop encontrado (erro)" : "Nenhum loop encontrado (correto)") << std::endl;

    // Limpando lista
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    head = nullptr;
    tail = nullptr;

    // Caso com loop
    insertNode(head, tail, 1);
    insertNode(head, tail, 2);
    insertNode(head, tail, 3);
    insertNode(head, tail, 4);

    // Criando loop manualmente
    tail->next = head; // Faz o último nó apontar para o primeiro
    head->prev = tail; // Faz o primeiro nó apontar para o último

    std::cout << "Testando lista com loop (1, 2, 3, 4 -> 1): ";
    loopExists = hasLoop(head, tail);
    std::cout << (loopExists ? "Loop encontrado (correto)" : "Nenhum loop encontrado (erro)") << std::endl;

    return 0;
}
