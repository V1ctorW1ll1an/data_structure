#include <stdio.h>
#include <stdlib.h>

// data
struct Data {
    int number;
};
// node
struct Node {
    struct Data data;
    struct Node *prox;
};

int empty(struct Node *list) {
    return (list == NULL);
}

void insert(struct Node **listRef, struct Node **tail, struct Data data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prox = NULL;

    // primeiro a ser inserido
    if (empty(*listRef)) {
        (*listRef) = newNode;
        (*tail) = newNode;
        return;
    }
    // se nao for insere na ultima posição
    (*tail)->prox = newNode;
    (*tail) = newNode;
}

void printData(struct Data data) {
    printf("%d\n", data.number);
}

void printList(struct Node *node) {
    // system("clear");
    printf("\n\n");
    if (empty(node)) {
        printf("\nLista vazia!\n\n");
        return;
    }

    while (node != NULL) {
        printData(node->data);
        node = node->prox;
    }
}

void delete (struct Node **headRef, struct Node **tail, struct Data data) {
    struct Node *increment = (*headRef), *previous;

    // verificar se a lista esta vazia
    if (empty(*headRef)) {
        printf("\nLista vazia!\n");
        return;
    }

    // apagando se for a primeira posição
    if (increment && increment->data.number == data.number) {
        (*headRef) = increment->prox;
        printf("\n\nDado deletado com sucesso: ");
        printData(increment->data);
        free(increment);
        return;
    }

    // achar a referencia do dado
    while (increment && !(increment->data.number == data.number)) {
        // armazenando sempre o dado anterior
        previous = increment;
        increment = increment->prox;
    }

    // validar se o dado foi encontrado
    if (!increment) {
        printf("Dado nao encontrado!");
        return;
    }

    // pulando para a proxima referencia do dado
    previous->prox = increment->prox;

    // se for o ultimo entao mudamos a referencia do tail
    if (increment->prox == NULL) {
        (*tail)->prox = previous;
    }

    // system("clear");

    printf("\n\nDado deletado com sucesso: ");
    printData(increment->data);

    // liberando o espaço usado no increment
    free(increment);
}

void searchByData(struct Node *head, struct Data data) {
    if (empty(head)) {
        printf("Lista vazia!");
        return;
    }
    while (head) {
        if (head->data.number == data.number) {
            printf("\nDado encontrado: ");
            printData(head->data);
            return;
        }
        head = head->prox;
    }
    printf("\nDado não encontrado!\n");
}

int main(int argc, char const *argv[]) {
    struct Node *head = NULL, *tail = NULL;
    struct Data data;

    data.number = 100;
    insert(&head, &tail, data);
    data.number = 101;
    insert(&head, &tail, data);
    data.number = 102;
    insert(&head, &tail, data);
    data.number = 103;
    insert(&head, &tail, data);
    printList(head);

    data.number = 103;
    delete (&head, &tail, data);

    printList(head);

    data.number = 101;
    searchByData(head, data);
    return 0;
}
