//Stack Initialization
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
typedef struct {
int *data;
int top;
int size;
} Stack;
void initStack(Stack *stack, int size) {
stack->data = malloc(sizeof(int) * size);
stack->top = -1;
stack->size = size;
}
//Push and Pop
void push(Stack *stack, int value) {
if (stack->top == stack->size - 1) {
// Stack overflow
return;
}
stack->data[++stack->top] = value;
}
int pop(Stack *stack) {
if (stack->top == -1) {
// Stack underflow
return -1;
}
return stack->data[stack->top--];
}
//Destroy Stack
void destroyStack(Stack *stack) {
free(stack->data);
}
//The Game: Russian Roulette
void playRussianRoulette(Stack *bullets) {
int currentPlayer = 1;
while (true) {
printf("Player %d, pull the trigger? (y/n) ", currentPlayer);
char answer = getchar();
if (answer == 'n') {
currentPlayer = (currentPlayer == 1) ? 2 : 1;
continue;
}
int bullet = pop(bullets);
if (bullet == 0) {
printf("Player %d is dead!\n", currentPlayer);
break;
}
printf("Player %d is alive!\n", currentPlayer);
currentPlayer = (currentPlayer == 1) ? 2 : 1;
}
}
//Main Function
int main() {
char menuChoice;
Stack bullets;
srand(time(NULL));
do {
printf("----- MENU -----\n");
printf("P - Start Game\n");
printf("H - Get Help\n");
printf("X - Exit\n");
printf("Enter your choice: ");
scanf(" %c", &menuChoice);
switch (menuChoice) {
case 'P':
case 'p':
initStack(&bullets, 6);
int bulletChamber = rand() % 6;
for (int i = 0; i < 6; i++) {
if (i == bulletChamber) {
push(&bullets, 0);
} else {
push(&bullets, i + 1);
}
}
playRussianRoulette(&bullets);
// Print the chamber where the bullet was
printf("The bullet was in chamber %d.\n", bulletChamber + 1);
// Announce the winner
printf("GAME OVER! Player %d wins!\n", (bullets.top == -1) ? 2 : 1);
// Ask if the user wants to play again
printf("Do you want to play again? (y/n): ");
scanf(" %c", &menuChoice);
break;
case 'H':
case 'h':
// Provide information about the game
printf("Russian Roulette Game:\n");
printf("Two players take turns pulling the trigger.\n");
printf("One chamber contains a bullet. If a player\n");
printf("pulls the trigger on the chamber with the\n");
printf("bullet, that player loses.\n");
break;
case 'X':
case 'x':
// Exit the program
printf("Exiting the program. Goodbye!\n");
break;
default:
// Invalid choice
printf("Invalid choice. Please try again.\n");
break;
}
// Flush the input buffer
while (getchar() != '\n');
} while (menuChoice == 'Y' || menuChoice == 'y');
return 0;
}
