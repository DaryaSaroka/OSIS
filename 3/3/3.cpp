#include <stdio.h>
#include <stdlib.h>

struct Node
{
	Node* next;
	Node* prev;
	char* str;
};

Node* head = nullptr;

Node* get_first() {
	return head;
}

Node* get_last() {
	Node* temp = get_first();

	while (temp != nullptr && temp->next != nullptr) {
		temp = temp->next;
	}

	return temp;
}

void push_back(char* str) {
	Node* temp = get_last();
	Node* new_item = new Node();
	new_item->next = nullptr;
	new_item->prev = temp;
	if (temp != nullptr) {
		temp->next = new_item;
	}
	else {
		head = new_item;
	}
	new_item->str = str;
}

void push_front(char* str) {
	Node* temp = get_first();
	Node* new_item = new Node();
	new_item->next = temp;
	new_item->prev = nullptr;
	if (temp != nullptr) {
		temp->prev = new_item;
	}
	head = new_item;
	new_item->str = str;
}

bool is_empty() {
	return head == nullptr;
}

Node* get_item(int index) {
	if (is_empty()) {
		//throw "There is no such item.";
		return nullptr;
	}

	int i = 0;
	Node* cur = head;
	for (i = 0; i < index && cur->next != nullptr; ++i) {
		cur = cur->next;
	}

	if (i != index) {
		//throw "There is no such item.";
		return nullptr;
	}

	return cur;
}

void remove(int index) {
	Node* cur = get_item(index);
	if (cur == nullptr) {
		printf("No such item.\n");
		return;
	}

	Node* next = cur->next;
	Node* prev = cur->prev;

	if (prev != nullptr) {
		prev->next = next;
	}

	if (next != nullptr) {
		next->prev = prev;
	}

	if (cur == head) {
		head = cur->next;
	}

	delete cur;
}

void clear() {
	while (head != nullptr) {
		remove(0);
	}
}

void output() {
	Node* cur = head;
	while (cur != nullptr) {
		printf("%s\n", cur->str);
		cur = cur->next;
	}
}

int main()
{
	char cmd[16];
	int index;
	printf("Available commands: \n 1.push_back,\n 2.push_front,\n 3.remove 'index',\n 4.clear,\n 5.output,\n 6.exit\n");

	do {
		char* str = new char[256];
		printf("\nChoose action: ");
		scanf("%s", cmd);

		if (cmd[0] == '1') {
			printf("Enter your string:\n");
			scanf("%s", str);
			push_back(str);
		}

		if (cmd[0] == '2') {
			printf("Enter your string:\n");
			scanf("%s", str);
			push_front(str);
		}

		if (cmd[0] == '3') {
			printf("Enter the index:\n");
			scanf("%d", &index);
			remove(index);
		}

		if (cmd[0] == '4') {
			clear();
		}

		if (cmd[0] == '5') {
			printf("Your list:\n");
			output();
		}

		if (cmd[0] == '6') {
			break;
		}

	} while (true);

	return 0;
}