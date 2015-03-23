#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_STRING_SIZE 256

typedef enum Type_ {animalType, questionType} Type;

typedef struct Info_
{
	char stroka [MAX_STRING_SIZE];
	Type type;
} Info;

typedef struct Node_
{
	Info info;
	struct Node_ *yesLink, *noLink;
} Node;

void addNewKnowlege(Node *target, Info newAnimal,
					Info question, bool rightAnswer);

Node *goToLeaf(Node *root);

void createNode(Node **node, Info info);

int main()
{
	Node *root = NULL;
	Info catInfo = {"кот", animalType};
	createNode(&root, catInfo);
	Info whaleInfo = {"кит", animalType},
		 questionInfo = {"Оно большое?", questionType};
    addNewKnowlege(root, whaleInfo, questionInfo, true);
    Node *target=goToLeaf(root);
    printf ("Это %s?\n", target->info.stroka);
	return 0;
}

void addNewKnowlege(Node *target, Info newAnimal,
					Info question, bool rightYesAnswer)
{
	assert(target);
	Info oldAnimal = target->info;
	target->info = question;
	Node *newAnimalNode, *oldAnimalNode;
	createNode(&newAnimalNode, newAnimal);
	createNode(&oldAnimalNode, oldAnimal);

	if(rightYesAnswer)
	{
		target->yesLink = newAnimalNode;
		target->noLink = oldAnimalNode;
	}
	else
	{
		target->noLink = newAnimalNode;
		target->yesLink = oldAnimalNode;
	}
}

void createNode(Node **node, Info info)
{
	*node = (Node *) malloc(sizeof(Node));

	if(*node != NULL)
	{
		(*node)->info = info;
		(*node)->yesLink = NULL;
		(*node)->noLink = NULL;
	}
}

Node *goToLeaf(Node *root)
{
	assert(root);
	Node *p = root;

	while(p->info.type == questionType)
	{
		printf("%s\n", p->info.stroka);
		printf("Y/N: ");
		char answer;
		scanf(" %c", &answer);

		if(answer == 'Y')
			p = p->yesLink;
		else
			p = p->noLink;
	}
	return p;
}

