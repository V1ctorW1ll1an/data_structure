#include <stdio.h>
#include <stdlib.h>

struct Data {
    int number;
};

struct Node {
    struct Data data;
    struct Node *prox;
};

int isEmpty(struct Node *list) {
    return (list == NULL);
}

void printData(struct Data data) {
    printf("%d\n", data.number);
}

void printList(struct Node *list) {
    if (isEmpty(list)) {
        printf("\nLista Vazia!\n");
        return;
    }

    printf("\n\n lista \n\n");
    while (list) {
        printf("item lista: ");
        printData(list->data);
        list = list->prox;
    }
}

void insert(struct Node **listReference, struct Node **last, struct Data data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prox = NULL;

    // verificar se a lista esta vazia
    if (isEmpty(*listReference)) {
        // inserir o primeiro elemento da lista
        (*listReference) = newNode;
        (*last) = newNode;
        return;
    }

    // caso a lista nao esteja vazia
    (*last)->prox = newNode;
    (*last) = newNode;
}

void deleteNodeByData(struct Node **list, struct Node **last, struct Data data) {
    struct Node *previous, *current = (*list);

    // verificar se a lista esta vazia
    if (isEmpty(*list)) {
        printf("Lista vazia!\n");
        return;
    }

    // verificar se o item é o primeiro item da lista
    if (current && current->data.number == data.number) {
        (*list) = current->prox;
        free(current);
        return;
    }

    // verificar se existe algum item na lista que é igual ao dado passado
    while (current && current->data.number != data.number) {
        // armazenar o anterior para conseguir pular uma referencia
        previous = current;
        current = current->prox;
    }

    // verificar se foi encontrado algum item, caso contrario informamos
    // que nenhum item foi encontrado para o delete
    if (current == NULL) {
        printf("Item não encontrado!\n");
        return;
    }

    // caso o dado tenha sido encontrado, logo vamos remove-lo
    // vamos pular uma referencia, para o proximo
    // a referencia do anterior para o atual recebe uma nova referencia
    // para o que vem depois do atual
    previous->prox = current->prox;

    // validando se o atual é o ultimo item da lista
    if (current->prox == NULL) {
        // se sim, o ultimo agora é o anterior ao atual
        (*last) = previous;
    }
    // liberando o espaço alocado na memoria
    free(current);
}

void searchByData(struct Node *list, struct Data data) {
    // verificar se a lista ta vazia
    if (isEmpty(list)) {
        printf("Lista vazia!\n");
        return;
    }

    // se nao estiver vazia, vamos procurar o dado
    while (list) {
        if (list->data.number == data.number) {
            printf("Dado encontrado: ");
            printData(list->data);
            return;
        }
        list = list->prox;
    }

    printf("Dado não encontrado!\ndado: %d\n", data.number);
}

int main(int argc, char const *argv[]) {
    system("clear");
    struct Node *list = NULL, *last = NULL;
    struct Data data;

    // insert a new node
    data.number = 0;
    insert(&list, &last, data);
    data.number = 1;
    insert(&list, &last, data);
    data.number = 2;
    insert(&list, &last, data);
    data.number = 3;
    insert(&list, &last, data);

    // show list
    printList(list);

    // delete node
    // o item foi removido com sucesso
    // data.number = 3;
    // deleteNodeByData(&list, &last, data);
    // printList(list);

    // search by data
    // numero que vamos procurar
    data.number = 3;  // o 3 foi adicionado, porem foi removido nas linhas acima 😘
    searchByData(list, data);

    // FINISH

    return 0;
}
