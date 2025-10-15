#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define LINE_LENGTH 100
#define WORD_SIZE 20
#define MAX_WORDS 100

typedef struct
{
    char word[WORD_SIZE+1];
    int frequency;
} index_t;



char words[MAX_WORDS][WORD_SIZE];

// read the files

/* Prototypes */
void read_words(const char *, index_t [], int *); // The last var is a pointer to an integer since this function will update the value.
void read_text(const char *, index_t [], int); // The last var here is just an int value to know how many words are there in the struct.
void to_lower_case(char *string);

int main(void) {
    index_t words[MAX_WORDS];
    int word_count;

    // Step 1: read the list of target words
    read_words("lab00/ex01/e01inB.txt", words, &word_count);

    // Step 2: scan the text and count occurrences
    read_text("lab00/ex01/e01inA.txt", words, word_count);

    // Step 3: print the results
    for (int i = 0; i < word_count; i++)
        printf("%s - %d occurrence(s)\n", words[i].word, words[i].frequency);

    return 0;
}

void read_words(const char* filename, index_t index[], int *word_count)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int i = 0;
    while (i < MAX_WORDS && fscanf(fp, "%s", index[i].word) != EOF)
    {
        index[i].frequency = 0; // Set the frequency to 0 for all the words we would be checking
        i++;
    }
    *word_count = i; // Set the value of the word_count as i (numbers of words counted)

    fclose(fp);
}

void read_text(const char* filename, index_t index[], int word_count)
{
    char word[WORD_SIZE+1];

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while (fscanf(fp, "%s", word) != EOF)
    {
        to_lower_case(word);
        for (int i = 0; i < word_count; i++)
        {
            if (strcmp(word, index[i].word) == 0)
            {
                index[i].frequency++;
            }
        }
    }
}

void to_lower_case(char *string)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        string[i] = (char)tolower(string[i]);
    }
}