#include <bits/stdc++.h>

using namespace std;


struct node{
	int valor;
	struct node* next;
};

struct node *Create_node(int x){
	struct node* tmp;
	tmp = (struct node *) malloc(sizeof(struct node));
	tmp->valor = x;
	tmp->next = NULL;

	return tmp;
}

struct node *Insert(int val, struct node *head){
	struct node *tmp, *put;

	tmp = Create_node(val);

	if(head == NULL){
		head = tmp;
		return head;
	}

	put = head;

	while(put->next != NULL){
		put = put->next;
	}

	put->next = tmp;
	return head;
}

struct node *Insert_begin(int val, struct node *head){
	struct node *tmp, *put;

	tmp = head;
	put = Create_node(val);

	put->next = tmp;
	head = put;

	return head;
}

struct node *Delete_value(int val, struct node *head){
	struct node *atual, *cut;

	atual = head;

	if(head->valor == val){
		head = atual->next;
		free(atual);
		return head;
	}

	while(atual->valor != val){
		cut = atual;
		atual = atual->next;
	}
	cut->next = atual->next;

	free(atual);

	return head;
}

struct node *Insert_in_posicion(int val, struct node* head, int pos){
    struct node *temp;

    temp = Create_node(val);

    if(pos == 1){
        temp->next = head;
        head = temp;
        return head;
    }

    struct node *aux;

    aux = head;

    int i;

    for(i = 0; i < pos-2; i++){
        aux = aux->next;
    }

    temp->next = aux->next;
    aux->next = temp;

    return head;

}

void Print(struct node *head){
	struct node* tmp;
	tmp = head;

	while(tmp != NULL){
		printf("%d\n", tmp->valor);
		tmp = tmp->next;
	}
}


int main(){

	struct node *head = NULL;

	head = Insert(1, head);
	head = Insert(2, head);
	head = Insert_begin(3, head);
	Print(head);
	head = Delete_value(3, head);
	Print(head);

	return 0;
}
