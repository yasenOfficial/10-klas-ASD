#include <stdio.h>
#include <stdlib.h>

typedef struct DialogueNode {
    char *npcCue;
    struct ChoiceNode *playerChoices;
    struct DialogueNode *nextSteps;
} DialogueNode;

typedef struct ChoiceNode {
    char *choice;
    struct ChoiceNode *next;
    struct DialogueNode *nextStep;
} ChoiceNode;

typedef struct Item {
    char *name;
    int quantity;
} Item;

typedef struct Inventory {
    Item items[10];
} Inventory;

DialogueNode *init_node(char *npcCue, ChoiceNode *playerChoices, DialogueNode *nextSteps) {
    DialogueNode *node = (DialogueNode *)malloc(sizeof(DialogueNode));

    node->npcCue = npcCue;
    node->playerChoices = playerChoices;
    node->nextSteps = nextSteps;

    return node;
}

ChoiceNode *init_choice(char *choice, DialogueNode *nextStep) {
    ChoiceNode *choiceNode = (ChoiceNode *)malloc(sizeof(ChoiceNode));

    choiceNode->choice = choice;
    choiceNode->next = NULL;
    choiceNode->nextStep = nextStep;

    return choiceNode;
}

void add_choice(ChoiceNode **head, char *choice, DialogueNode *nextStep) {
    ChoiceNode *newChoice = init_choice(choice, nextStep);
    newChoice->next = *head;
    *head = newChoice;
}

void free_node(DialogueNode *node) {
    free(node->npcCue);

    ChoiceNode *currentChoice = node->playerChoices;
    while (currentChoice != NULL) {
        ChoiceNode *temp = currentChoice;
        currentChoice = currentChoice->next;
        free(temp->choice);
        free(temp);
    }

    free_node(node->nextSteps);

    free(node);
}

void play_dialogue(DialogueNode *node) {
    while (node != NULL) {
        printf("NPC: %s\n", node->npcCue);

        ChoiceNode *currentChoice = node->playerChoices;
        int choiceNum = 1;
        while (currentChoice != NULL) {
            printf("%d. %s\n", choiceNum, currentChoice->choice);
            currentChoice = currentChoice->next;
            choiceNum++;
        }

        int playerChoice;
        printf("Enter your choice: ");
        scanf("%d", &playerChoice);

        // Find the selected choice
        currentChoice = node->playerChoices;
        int count = 1;
        while (count < playerChoice && currentChoice != NULL) {
            currentChoice = currentChoice->next;
            count++;
        }

        if (currentChoice != NULL) {
            node = currentChoice->nextStep;
            printf("\n");
        } else {
            printf("Kapak opitaj pak.\n\n");
        }
    }
    //това се повтаря докато се стигне края на дървото
    //ако играчът няма реплики директно се преминава на следващата стъпка без да се чака негов избор. 
    //Ако има само 1 възможна реплика тя се избира автоматично без да се изчаква играчът да го направи

}

int main() {
    // Create a cyclic dialogue tree
    DialogueNode *root = init_node("Zdravej i dobre doshul v Kaspichan", NULL, NULL);


    // 1. option
    add_choice(&(root->playerChoices), "Pitaj za Quest", init_node("Mnogo si smel! Iskash li da namerish sukrovishte?", NULL, NULL));

    DialogueNode *questNode = root->playerChoices->nextStep;
    add_choice(&(questNode->playerChoices), "Priemi Quest-a", init_node("Super! Otidi do centura na tezi koordinati 45.23, 56.21", NULL, NULL));
    add_choice(&(questNode->playerChoices), "Otkazji Quest-a", init_node("Ne iskash sukrovishte? Tvoq volq.", NULL, NULL));

    // 2. option
    add_choice(&(root->playerChoices), "Razpitaj za seloto", init_node("Tova e naj-gotinoto selo - Kaspichan. Kakwo iskash da znaesh?", NULL, NULL));

    DialogueNode *townNode = root->playerChoices->nextStep;
    add_choice(&(townNode->playerChoices), "Pitaj za istoriq na seloto", init_node("Tova selo e osnovano ot 3ma bratq - Stamat, Gulubin i Goran.", NULL, NULL));
    add_choice(&(townNode->playerChoices), "Pitaj kolko zhitelq ima seloto", init_node("Kaspichan ima 3,260 (Dec 2009)", NULL, NULL));
    add_choice(&(townNode->playerChoices), "Vurni se nazad!", root); // Po tozi nachin se pravi cikul v dialoga

    
    play_dialogue(root);

    free_node(root);

    return 0;
}


