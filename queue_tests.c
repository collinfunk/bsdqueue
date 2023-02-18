
#include <stdio.h>
#include "queue.h"

void list_tests(void);
void tailq_tests(void);
void slist_tests(void);
void simpleq_tests(void);
void stailq_tests(void);

int main(int argc, char **argv) {
	list_tests();
	tailq_tests();
	slist_tests();
	simpleq_tests();
	stailq_tests();
	return (0);
}

void list_tests(void) {
	printf("list_tests();\n");
	struct intnode {
		int val;
		LIST_ENTRY(intnode) link;
	};

	LIST_HEAD(inthead, intnode) head = LIST_HEAD_INITIALIZER(head);
	LIST_INIT(&head);

	struct intnode nodes[10];
	struct intnode n1, n2, n3;
	struct intnode *ptr;

	for (int i = 0; i < 10; i++) {
		nodes[i].val = i;
		LIST_INSERT_HEAD(&head, &nodes[i], link);
	}

	n1.val = 101;
	n2.val = 102;
	n3.val = 103;

	LIST_INSERT_AFTER(&nodes[1], &n1, link);
	LIST_INSERT_BEFORE(&nodes[2], &n2, link);
	LIST_INSERT_AFTER(&nodes[3], &n3, link);

	LIST_FOREACH(ptr, &head, link) {
		printf("%d\n", ptr->val);
	}
}

void tailq_tests(void) {
	printf("tailq_tests();\n");
	struct intnode {
		int val;
		TAILQ_ENTRY(intnode) link;
	};

	TAILQ_HEAD(inthead, intnode) head = TAILQ_HEAD_INITIALIZER(head);
	TAILQ_INIT(&head);

	struct intnode nodes[10];
	struct intnode n1, n2, n3, n4;
	struct intnode *ptr;

	for (int i = 0; i < 10; i++) {
		nodes[i].val = i;
		TAILQ_INSERT_HEAD(&head, &nodes[i], link);
	}

	n1.val = 101;
	n2.val = 102;
	n3.val = 103;
	n4.val = 104;

	TAILQ_INSERT_TAIL(&head, &n4, link);
	TAILQ_INSERT_AFTER(&head, &nodes[1], &n1, link);
	TAILQ_INSERT_BEFORE(&nodes[2], &n2, link);
	TAILQ_INSERT_AFTER(&head, &nodes[3], &n3, link);

	TAILQ_FOREACH(ptr, &head, link) {
		printf("%d\n", ptr->val);
	}
}

void slist_tests(void) {
	printf("slist_tests();\n");
	struct intnode {
		int val;
		SLIST_ENTRY(intnode) link;
	};

	SLIST_HEAD(inthead, intnode) head = SLIST_HEAD_INITIALIZER(head);
	SLIST_INIT(&head);

	struct intnode nodes[10];
	struct intnode n1, n2, n3;
	struct intnode *ptr;

	for (int i = 0; i < 10; i++) {
		nodes[i].val = i;
		SLIST_INSERT_HEAD(&head, &nodes[i], link);
	}

	n1.val = 101;
	n2.val = 102;
	n3.val = 103;

	SLIST_INSERT_AFTER(&nodes[1], &n1, link);
	SLIST_INSERT_AFTER(&nodes[2], &n2, link);
	SLIST_INSERT_AFTER(&nodes[3], &n3, link);

	SLIST_REMOVE_HEAD(&head, link);
	SLIST_REMOVE_HEAD(&head, link);
	SLIST_REMOVE_HEAD(&head, link);
	SLIST_REMOVE_AFTER(&nodes[1], link);

	SLIST_FOREACH(ptr, &head, link) {
		printf("%d\n", ptr->val);
	}
}

void simpleq_tests(void) {
	printf("simpleq_tests();\n");
	struct intnode {
		int val;
		SIMPLEQ_ENTRY(intnode) link;
	};

	SIMPLEQ_HEAD(inthead, intnode) head = SIMPLEQ_HEAD_INITIALIZER(head);
	SIMPLEQ_INIT(&head);

	struct intnode nodes[10];
	struct intnode n1, n2, n3, n4;
	struct intnode *ptr;

	for (int i = 0; i < 10; i++) {
		nodes[i].val = i;
		SIMPLEQ_INSERT_HEAD(&head, &nodes[i], link);
	}

	n1.val = 101;
	n2.val = 102;
	n3.val = 103;
	n4.val = 104;

	SIMPLEQ_INSERT_TAIL(&head, &n4, link);
	SIMPLEQ_INSERT_AFTER(&head, &nodes[1], &n1, link);
	SIMPLEQ_INSERT_AFTER(&head, &nodes[2], &n2, link);
	SIMPLEQ_INSERT_AFTER(&head, &nodes[3], &n3, link);

	SIMPLEQ_REMOVE_HEAD(&head, link);
	SIMPLEQ_REMOVE_HEAD(&head, link);
	SIMPLEQ_REMOVE_HEAD(&head, link);
	SIMPLEQ_REMOVE_AFTER(&head, &nodes[1], link);
	SIMPLEQ_REMOVE_AFTER(&head, &nodes[2], link);

	SIMPLEQ_FOREACH(ptr, &head, link) {
		printf("%d\n", ptr->val);
	}
}

void stailq_tests(void) {
	printf("stailq_tests();\n");
	struct intnode {
		int val;
		STAILQ_ENTRY(intnode) link;
	};

	STAILQ_HEAD(inthead, intnode) head = STAILQ_HEAD_INITIALIZER(head);
	STAILQ_INIT(&head);

	struct intnode nodes[10];
	struct intnode n1, n2, n3, n4;
	struct intnode *ptr;

	for (int i = 0; i < 10; i++) {
		nodes[i].val = i;
		STAILQ_INSERT_HEAD(&head, &nodes[i], link);
	}

	n1.val = 101;
	n2.val = 102;
	n3.val = 103;
	n4.val = 104;

	STAILQ_INSERT_TAIL(&head, &n4, link);
	STAILQ_INSERT_AFTER(&head, &nodes[1], &n1, link);
	STAILQ_INSERT_AFTER(&head, &nodes[2], &n2, link);
	STAILQ_INSERT_AFTER(&head, &nodes[3], &n3, link);

	STAILQ_REMOVE_HEAD(&head, link);
	STAILQ_REMOVE_HEAD(&head, link);
	STAILQ_REMOVE_HEAD(&head, link);
	STAILQ_REMOVE_AFTER(&head, &nodes[1], link);
	STAILQ_REMOVE_AFTER(&head, &nodes[2], link);

	STAILQ_FOREACH(ptr, &head, link) {
		printf("%d\n", ptr->val);
	}
}