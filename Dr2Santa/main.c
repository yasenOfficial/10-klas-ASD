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

#define MAX_ITEMS 10
typedef struct Item {
    char *name;
    int quantity;
} Item;

typedef struct Inventory {
    Item items[MAX_ITEMS];
} Inventory;

typedef struct ChoiceNode {
    char *choice;
    struct ChoiceNode *next;
    struct DialogNode *nextStep;
    char *requiredItem;  
    int requiredQuantity; 
} ChoiceNode;

typedef struct DialogNode {
    char *npcCue;
    struct ChoiceNode *playerChoices;
    struct DialogNode *nextSteps;
} DialogNode;

DialogNode *create_node(char *npcCue, ChoiceNode *playerChoices, DialogNode *nextSteps) {
    DialogNode *node = (DialogNode *)malloc(sizeof(DialogNode));

    node->npcCue = npcCue;
    node->playerChoices = playerChoices;
    node->nextSteps = nextSteps;

    return node;
}

ChoiceNode *init_choice(char *choice, DialogNode *nextStep, char *requiredItem, int requiredQuantity) {
    ChoiceNode *choiceNode = (ChoiceNode *)malloc(sizeof(ChoiceNode));

    choiceNode->choice = choice;
    choiceNode->next = NULL;
    choiceNode->nextStep = nextStep;
    choiceNode->requiredItem = requiredItem;
    choiceNode->requiredQuantity = requiredQuantity;

    return choiceNode;
}

void add_item_to_inventory(Inventory *inventory, char *itemName, int quantity) {
    for (int i = 0; i < MAX_ITEMS; ++i) {
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

void add_choice(ChoiceNode **head, char *choice, DialogNode *nextStep, char *requiredItem, int requiredQuantity, Inventory *inventory, char *itemName, int quantity, DialogNode *currentNode) {
    ChoiceNode *newChoice = init_choice(choice, nextStep, requiredItem, requiredQuantity);
    newChoice->next = *head;
    *head = newChoice;
    // printf("DEBUG: Current Node: %p\n", currentNode); // DEBUG
    // printf("DEBUG: Next Step: %p\n", nextStep); // DEBUG

    if (currentNode != NULL && currentNode == nextStep) {
        // printf("DEBUG: Item Name: %s\n", itemName); // DEBUG
        // printf("DEBUG: Quantity: %d\n", quantity); // DEBUG
        if (itemName != NULL && quantity > 0) {
            add_item_to_inventory(inventory, itemName, quantity);
            print_inventory(inventory, 5);
        }
    }
}


void free_node(DialogNode *node) {
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

void print_inventory(Inventory *inventory, int color) {
    printf("Inventory:\n");
    for (int i = 0; i < MAX_ITEMS; ++i) {
        if (inventory->items[i].name != NULL) {
            if (color == 0){
                printf("%s: %d\n", inventory->items[i].name, inventory->items[i].quantity);
            }else if (color == 1){
                printf(GREEN_COLOR "%s: %d\n" RESET_COLOR, inventory->items[i].name, inventory->items[i].quantity);
            }else if (color == 2){
                printf(RED_COLOR "%s: %d\n" RESET_COLOR, inventory->items[i].name, inventory->items[i].quantity);
            }else if (color == 3){
                printf(YELLOW_COLOR "%s: %d\n" RESET_COLOR, inventory->items[i].name, inventory->items[i].quantity);
            }else if (color == 4){
                printf(BLUE_COLOR "%s: %d\n" RESET_COLOR, inventory->items[i].name, inventory->items[i].quantity);
            }else if (color == 5){
                printf(MAGENTA_COLOR "%s: %d\n" RESET_COLOR, inventory->items[i].name, inventory->items[i].quantity);
            }else if (color == 6){
                printf(CYAN_COLOR "%s: %d\n" RESET_COLOR, inventory->items[i].name, inventory->items[i].quantity);
            }

        }
    }
    printf("\n");
}

void play_dialogue(DialogNode *node, Inventory *playerInventory, DialogNode *root) {
    int flag = 0;
    int hasPrinted = 0;
    int skip = 0;
    int playerChoice = 0;


    while (node != NULL) {
        printf(GREEN_COLOR "NPC: %s\n" RESET_COLOR, node->npcCue);

        ChoiceNode *currentChoice = node->playerChoices;
        int choiceNum = 1;
        while (currentChoice != NULL) {
            /*
            if (currentChoice->nextStep->nextSteps == root) {
                printf("0. NPC: %s\n", currentChoice->nextStep->npcCue);
                printf("%d. %s\n", choiceNum, currentChoice->choice);
            } else {
                printf("%d. %s\n", choiceNum, currentChoice->choice);
                printf("----------\n"); // DEBUG
                printf("DEBUG: Current Choice: %s\n", currentChoice->choice); // DEBUG
                printf("DEBUG: Current Choice Next Step: %p\n", currentChoice->nextStep->nextSteps); // DEBUG
                printf("DEBUG: Root: %p\n", root); // DEBUG
                printf("----------\n"); // DEBUG


            }
            */
            if(flag == 1 && hasPrinted == 0){
                printf(GREEN_COLOR "NPC: %s\n" RESET_COLOR, root->npcCue);
                hasPrinted = 1;
                flag = 0;
                // printf("DEBUG: Player Choice: %d\n", playerChoice); // DEBUG

            }else if (flag == 0){
                if(skip == 0){
                    printf("%d. %s\n", choiceNum, currentChoice->choice); // INSTEAD OF SKIPPING THE FIRST CHOICE, POP IT
                }else{
                    skip = 0;
                }
                currentChoice = currentChoice->next;
                choiceNum++;
            }
            
        }

        printf(CYAN_COLOR "Enter your choice: " RESET_COLOR);
        scanf("%d", &playerChoice);

        currentChoice = node->playerChoices;
        int count = 1;
        while (count < playerChoice && currentChoice != NULL) {
            count++;
            currentChoice = currentChoice->next;
        }

        if (currentChoice != NULL) {
            if (currentChoice->nextStep->playerChoices == root) {
                // printf("NPC: %s\n", root->npcCue);
                flag = 1;
                hasPrinted = 0;
                skip = 1;
            }//else {
            //     printf("----------\n"); // DEBUG
            //     printf("DEBUG: Current Choice: %s\n", currentChoice->choice); // DEBUG
            //     printf("DEBUG: Current Choice Next Step: %p\n", currentChoice->nextStep->nextSteps); // DEBUG
            //     printf("DEBUG: Root: %p\n", root); // DEBUG
            //     printf("DEBUG: Flag: %d\n", flag); // DEBUG

            //     printf("----------\n"); // DEBUG


            // }
            if ((currentChoice->requiredItem == NULL) || (currentChoice->requiredItem != NULL && currentChoice->requiredQuantity <= 0) || (currentChoice->requiredItem != NULL && currentChoice->requiredQuantity > 0 &&
                find_item_quantity(playerInventory, currentChoice->requiredItem) >= currentChoice->requiredQuantity)) {

                if (currentChoice->requiredItem != NULL && currentChoice->requiredQuantity > 0) {
                    decrease_item_quantity(playerInventory, currentChoice->requiredItem, currentChoice->requiredQuantity);
                }

                node = currentChoice->nextStep;
                printf("\n");
            } else {
                printf(RED_COLOR "Lujec! Nqmash materialite za da zapochnesh!.\n\n" RESET_COLOR);
                print_inventory(playerInventory, 2);
                node = root;
                skip = 0;
                flag = 0;

            }
        } else {
            printf(RED_COLOR "Kapak opitaj pak.\n\n" RESET_COLOR);
        }
    }
}

int find_item_quantity(Inventory *inventory, char *itemName) {
    for (int i = 0; i < MAX_ITEMS; ++i) {
        if (inventory->items[i].name != NULL && strcmp(inventory->items[i].name, itemName) == 0) {
            return inventory->items[i].quantity;
        }
    }
    return 0;
}

void decrease_item_quantity(Inventory *inventory, char *itemName, int quantity) {
    for (int i = 0; i < MAX_ITEMS; ++i) {
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

<<<<<<< HEAD
=======
void add_item_to_inventory(Inventory *inventory, char *itemName, int quantity) {
    for (int i = 0; i < MAX_ITEMS; ++i) {
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
void(){
    
}

>>>>>>> 618fbb630a82e59defe654e92b423d1262e5b808
int main() {
    Inventory playerInventory = {0};
    DialogNode *root = create_node("Zdravej i dobre doshul v Kaspichan", NULL, NULL);

    add_choice(&(root->playerChoices), "Pitaj za Quest", create_node("Mnogo si smel! Iskash li da namerish sukrovishte?", NULL, NULL), NULL, 0, &playerInventory, NULL, 0, NULL);

    DialogNode *questNode = root->playerChoices->nextStep;
    add_choice(&(questNode->playerChoices), "Priemi Quest-a (-1x Map) (+10x cards)", create_node("Super! Otidi do centura na tezi koordinati 45.23, 56.21", root, NULL), "Map", 1, &playerInventory, NULL, 0, NULL);
    add_choice(&(questNode->playerChoices), "Otkazji Quest-a", create_node("Ne iskash sukrovishte? Tvoq volq.", root, NULL), NULL, 0, &playerInventory, NULL, 0, NULL);
    add_choice(&(questNode->playerChoices), "Vurni se nazad!", root, NULL, 0, &playerInventory, NULL, 0, NULL);

    add_choice(&(root->playerChoices), "Razpitaj za seloto", create_node("Tova e naj-gotinoto selo - Kaspichan. Kakwo iskash da znaesh?", NULL, NULL), NULL, 0, &playerInventory, NULL, 0, NULL);

    DialogNode *townNode = root->playerChoices->nextStep;
    add_choice(&(townNode->playerChoices), "Pitaj za istoriq na seloto", create_node("Tova selo e osnovano ot 3ma bratq - Stamat, Gulubin i Goran.", root, NULL), NULL, 0, &playerInventory, NULL, 0, NULL);
    add_choice(&(townNode->playerChoices), "Pitaj kolko zhitelq ima seloto", create_node("Kaspichan ima 3,260 (Dec 2009)", root, NULL), NULL, 0, &playerInventory, NULL, 0, NULL);
    add_choice(&(townNode->playerChoices), "Vurni se nazad!", root, NULL, 0, &playerInventory, NULL, 0, NULL);

    add_choice(&(root->playerChoices), "Igraj belot s mestnite", create_node("Ti si pod ruka", NULL, NULL), NULL, 0, &playerInventory, NULL, 0, NULL);

    DialogNode *belotNode = root->playerChoices->nextStep;
    add_choice(&(belotNode->playerChoices), "Pika (-5x Cards)", create_node("Pass, Bez Kos, VSICHKO KOS!", root, NULL), "Cards", 5, &playerInventory, NULL, 0, NULL);
    add_choice(&(belotNode->playerChoices), "Pass (-5x Cards)", create_node("Pass, Pass, Kupa", root, NULL), "Cards", 5, &playerInventory, NULL, 0, NULL);
    add_choice(&(belotNode->playerChoices), "Bez Kos (-5x Cards)", create_node("kakuv bez kos, tova si e vsichko kos!, KONTRA!", root, NULL), "Cards", 5, &playerInventory, NULL, 0, NULL);
                                                        
    add_choice(&(belotNode->playerChoices), "Vurni se nazad!", root, NULL, 0, &playerInventory, NULL, 0, NULL);

    add_item_to_inventory(&playerInventory, "Book", 1);
    add_item_to_inventory(&playerInventory, "Cards", 5);
    add_item_to_inventory(&playerInventory, "Map", 1);



    print_inventory(&playerInventory, 3);

    play_dialogue(root, &playerInventory, root);

    free_node(root);

    return 0;
}