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

void insert(struct Node **listRef, struct Node **last, struct Data data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prox = NULL;

    // primeiro a ser inserido
    if (empty(*listRef)) {
        (*listRef) = newNode;
        (*last) = newNode;
        return;
    }
    // se nao for insere na ultima posição
    (*last)->prox = newNode;
    (*last) = newNode;
}

void printData(struct Data data) {
    printf("%d\n", data.number);
}

void printList(struct Node *list) {
    // system("clear");
    printf("\n\n");
    if (empty(list)) {
        printf("\nLista vazia!\n\n");
        return;
    }

    while (list != NULL) {
        printData(list->data);
        list = list->prox;
    }
}

void delete (struct Node **listRef, struct Node **last, struct Data data) {
    struct Node *current = (*listRef), *previous;

    // verificar se a lista esta vazia
    if (empty(*listRef)) {
        printf("\nLista vazia!\n");
        return;
    }

    // apagando se for a primeira posição
    if (current && current->data.number == data.number) {
        (*listRef) = current->prox;
        printf("\n\nDado deletado com sucesso: ");
        printData(current->data);
        free(current);
        return;
    }

    // achar a referencia do dado
    while (current && !(current->data.number == data.number)) {
        // armazenando sempre o dado anterior
        previous = current;
        current = current->prox;
    }

    // validar se o dado foi encontrado
    if (!current) {
        printf("Dado nao encontrado!");
        return;
    }

    // pulando para a proxima referencia do dado
    previous->prox = current->prox;

    // se for o ultimo entao mudamos a referencia do last
    if (current->prox == NULL) {
        (*last)->prox = previous;
    }

    // system("clear");

    printf("\n\nDado deletado com sucesso: ");
    printData(current->data);

    // liberando o espaço usado no increment
    free(current);
}

void searchByData(struct Node *list, struct Data data) {
    if (empty(list)) {
        printf("Lista vazia!");
        return;
    }
    while (list) {
        if (list->data.number == data.number) {
            printf("\nDado encontrado: ");
            printData(list->data);
            return;
        }
        list = list->prox;
    }
    printf("\nDado não encontrado!\n");
}

int main(int argc, char const *argv[]) {
    struct Node *list = NULL, *last = NULL;
    struct Data data;

    data.number = 100;
    insert(&list, &last, data);
    data.number = 101;
    insert(&list, &last, data);
    data.number = 102;
    insert(&list, &last, data);
    data.number = 103;
    insert(&list, &last, data);
    printList(list);

    data.number = 103;
    delete (&list, &last, data);

    printList(list);

    data.number = 101;
    searchByData(list, data);
    return 0;
}
