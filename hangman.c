#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 20

struct Node {
    char word[MAX_LENGTH];
    struct Node* next;
};

void addWord(struct Node** head, const char* word) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->word, word);
    newNode->next = *head;
    *head = newNode;
}

const char* getRandomWord(struct Node* head) {
    int count = 0;
    struct Node* current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    int randomIndex = rand() % count;

    current = head;
    for (int i = 0; i < randomIndex; i++) {
        current = current->next;
    }

    return current->word;
}

void displayHangman(int incorrectGuesses) {
    switch (incorrectGuesses) {
        case 0:
            printf("  +---+\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 1:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 2:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 3:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 4:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|   |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 5:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf("      |\n");
            printf("      |\n");
            break;
        case 6:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" /    |\n");
            printf("      |\n");
            break;
        case 7:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" / \\  |\n");
            printf("      |\n");
            break;
    }
}

void displayWord(const char* word, const char* guessedLetters) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (strchr(guessedLetters, word[i]) != NULL) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int hasPlayerWon(const char* word, const char* guessedLetters) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (strchr(guessedLetters, word[i]) == NULL) {
            return 0;
        }
    }
    return 1;
}

int main() {
    srand(time(NULL));

    FILE* file = fopen("word_list.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        return EXIT_FAILURE;
    }

    struct Node* word_list = NULL;
    char word[MAX_LENGTH];

    while (fscanf(file, "%s", word) == 1) {
        addWord(&word_list, word);
    }

    fclose(file);

    const char* chosenWord = getRandomWord(word_list);
    int incorrectGuesses = 0;
    char guessedLetters[26] = {'\0'};

    printf("Welcome to Hangman!\n");

    while (incorrectGuesses < 7) {
        displayHangman(incorrectGuesses);
        displayWord(chosenWord, guessedLetters);

        printf("Enter a letter: ");
        char guess;
        scanf(" %c", &guess);

        if (strchr(chosenWord, guess) != NULL) {
            printf("Correct guess!\n");
        } else {
            printf("Incorrect guess!\n");
            incorrectGuesses++;
        }

        strncat(guessedLetters, &guess, 1);

        if (hasPlayerWon(chosenWord, guessedLetters)) {
            displayHangman(incorrectGuesses);
            displayWord(chosenWord, guessedLetters);
            printf("Congratulations! You've won!\n");
            break;
        }
    }

    if (incorrectGuesses == 7) {
        displayHangman(incorrectGuesses);
        printf("Sorry, you've run out of attempts. The correct word was: %s\n", chosenWord);
    }

    struct Node* current = word_list;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

