#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET_COLOR "\x1b[0m"
#define RED_COLOR "\x1b[31m"
#define GREEN_COLOR "\x1b[32m"
#define YELLOW_COLOR "\x1b[33m"
#define BLUE_COLOR "\x1b[34m"
#define MAGENTA_COLOR "\x1b[35m"
#define CYAN_COLOR "\x1b[36m"

typedef struct Item {
    char *name;
    int quantity;
} Item;

typedef struct Inventory {
    Item items[10];
} Inventory;

typedef struct ChoiceNode {
    char *choice;
    struct ChoiceNode *next;
    struct DialogueNode *nextStep;
    char *requiredItem;  // New field for required item
    int requiredQuantity;  // New field for required quantity
} ChoiceNode;

typedef struct DialogueNode {
    char *npcCue;
    struct ChoiceNode *playerChoices;
    struct DialogueNode *nextSteps;
} DialogueNode;

DialogueNode *init_node(char *npcCue, ChoiceNode *playerChoices, DialogueNode *nextSteps) {
    DialogueNode *node = (DialogueNode *)malloc(sizeof(DialogueNode));

    node->npcCue = npcCue;
    node->playerChoices = playerChoices;
    node->nextSteps = nextSteps;

    return node;
}

ChoiceNode *init_choice(char *choice, DialogueNode *nextStep, char *requiredItem, int requiredQuantity) {
    ChoiceNode *choiceNode = (ChoiceNode *)malloc(sizeof(ChoiceNode));

    choiceNode->choice = choice;
    choiceNode->next = NULL;
    choiceNode->nextStep = nextStep;
    choiceNode->requiredItem = requiredItem;
    choiceNode->requiredQuantity = requiredQuantity;

    return choiceNode;
}

void add_choice(ChoiceNode **head, char *choice, DialogueNode *nextStep, char *requiredItem, int requiredQuantity) {
    ChoiceNode *newChoice = init_choice(choice, nextStep, requiredItem, requiredQuantity);
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

void display_inventory(Inventory *inventory) {
    printf("Inventory:\n");
    for (int i = 0; i < 10; ++i) {
        if (inventory->items[i].name != NULL) {
            printf("%s: %d\n", inventory->items[i].name, inventory->items[i].quantity);
        }
    }
    printf("\n");
}

void play_dialogue(DialogueNode *node, Inventory *playerInventory) {
    while (node != NULL) {
        printf(GREEN_COLOR "NPC: %s\n" RESET_COLOR, node->npcCue);

        ChoiceNode *currentChoice = node->playerChoices;
        int choiceNum = 1;

        // Display all choices, regardless of requirements
        while (currentChoice != NULL) {
            printf("%d. %s\n", choiceNum, currentChoice->choice);
            currentChoice = currentChoice->next;
            choiceNum++;
        }

        int playerChoice;
        printf("Enter your choice: ");
        scanf("%d", &playerChoice);

        currentChoice = node->playerChoices;
        int count = 1;
        while (count < playerChoice && currentChoice != NULL) {
            count++;
            currentChoice = currentChoice->next;
        }

        if (currentChoice != NULL) {
            // Check requirements when player selects a choice
            if ((currentChoice->requiredItem == NULL) ||
                (currentChoice->requiredItem != NULL && currentChoice->requiredQuantity <= 0) ||
                (currentChoice->requiredItem != NULL && currentChoice->requiredQuantity > 0 &&
                 find_item_quantity(playerInventory, currentChoice->requiredItem) >= currentChoice->requiredQuantity)) {
                // Update player inventory based on the choice
                if (currentChoice->requiredItem != NULL && currentChoice->requiredQuantity > 0) {
                    decrease_item_quantity(playerInventory, currentChoice->requiredItem, currentChoice->requiredQuantity);
                }

                node = currentChoice->nextStep;
                printf("\n");
            } else {
                printf(RED_COLOR "Lujec! Nqmash materialite za da zapochnesh!.\n\n" RESET_COLOR);

            }
        } else {
            printf(RED_COLOR "Kapak opitaj pak.\n\n" RESET_COLOR);
        }
    }
}


int find_item_quantity(Inventory *inventory, char *itemName) {
    for (int i = 0; i < 10; ++i) {
        if (inventory->items[i].name != NULL && strcmp(inventory->items[i].name, itemName) == 0) {
            return inventory->items[i].quantity;
        }
    }
    return 0;
}

void decrease_item_quantity(Inventory *inventory, char *itemName, int quantity) {
    for (int i = 0; i < 10; ++i) {
        if (inventory->items[i].name != NULL && strcmp(inventory->items[i].name, itemName) == 0) {
            inventory->items[i].quantity -= quantity;
            if (inventory->items[i].quantity <= 0) {
                free(inventory->items[i].name);
                inventory->items[i].name = NULL;
            }
            break;
        }
    }
}

void add_item_to_inventory(Inventory *inventory, char *itemName, int quantity) {
    for (int i = 0; i < 10; ++i) {
        if (inventory->items[i].name == NULL) {
            inventory->items[i].name = strdup(itemName);
            inventory->items[i].quantity = quantity;
            break;
        } else if (strcmp(inventory->items[i].name, itemName) == 0) {
            inventory->items[i].quantity += quantity;
            break;
        }
    }
}

int main() {
    Inventory playerInventory = {0};
    DialogueNode *root = init_node("Zdravej i dobre doshul v Kaspichan", NULL, NULL);

    // 1. option
    add_choice(&(root->playerChoices), "Pitaj za Quest", init_node("Mnogo si smel! Iskash li da namerish sukrovishte?", NULL, NULL), NULL, 0);

    DialogueNode *questNode = root->playerChoices->nextStep;
    add_choice(&(questNode->playerChoices), "Priemi Quest-a (1x Map)", init_node("Super! Otidi do centura na tezi koordinati 45.23, 56.21", NULL, NULL), "Map", 1);
    add_choice(&(questNode->playerChoices), "Otkazji Quest-a", init_node("Ne iskash sukrovishte? Tvoq volq.", NULL, NULL), NULL, 0);
    add_choice(&(questNode->playerChoices), "Vurni se nazad!", root, NULL, 0);

    // 2. option
    add_choice(&(root->playerChoices), "Razpitaj za seloto", init_node("Tova e naj-gotinoto selo - Kaspichan. Kakwo iskash da znaesh?", NULL, NULL), NULL, 0);

    DialogueNode *townNode = root->playerChoices->nextStep;
    add_choice(&(townNode->playerChoices), "Pitaj za istoriq na seloto", init_node("Tova selo e osnovano ot 3ma bratq - Stamat, Gulubin i Goran.", NULL, NULL), NULL, 0);
    add_choice(&(townNode->playerChoices), "Pitaj kolko zhitelq ima seloto", init_node("Kaspichan ima 3,260 (Dec 2009)", NULL, NULL), NULL, 0);
    add_choice(&(townNode->playerChoices), "Vurni se nazad!", root, NULL, 0);

    add_choice(&(root->playerChoices), "Igraj belot s mestnite", init_node("Ti si pod ruka", NULL, NULL), NULL, 0);

    DialogueNode *belotNode = root->playerChoices->nextStep;
    add_choice(&(belotNode->playerChoices), "Pika (5x Cards)", init_node("Pass, Bez Kos, VSICHKO KOS!", NULL, NULL), "Cards", 5);
    add_choice(&(belotNode->playerChoices), "Pass (5x Cards)", init_node("Pass, Pass, Kupa", NULL, NULL), "Cards", 5);
    add_choice(&(belotNode->playerChoices), "Bez Kos (5x Cards)", init_node("kakuv bez kos, tova si e vsichko kos!, KONTRA!", NULL, NULL), "Cards", 5);
                                                        
    add_choice(&(belotNode->playerChoices), "Vurni se nazad!", root, NULL, 0);



    // Add an item to the player's inventory
    add_item_to_inventory(&playerInventory, "Book", 1);
    add_item_to_inventory(&playerInventory, "Cards", 5);


    // Display the player's inventory
    display_inventory(&playerInventory);

    play_dialogue(root, &playerInventory);

    // Free allocated memory
    free_node(root);

    return 0;
}
