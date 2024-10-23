#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <ctype.h>

#define MAX_WORD_LENGTH 10
#define MAX_WORDS 100
#define MAX_LINE 100

typedef struct
{
    char word[MAX_WORD_LENGTH];
    int occurrence;
} words;

void read_words(char *, words [], int *);
/* There is an integer pointer here since we'll need to update count. */
void read_paragraph(char * , words [], int);
/* No need of a pointer to integer here, we will just use the number alone.*/
void print_end(words [], int);
// Passing the structure with the data and number of words we need to print.
int compare (char *, char *);
// Function to compare two words if they're the same.

int main(int argc, char *argv[])
{
    words list1[MAX_WORDS];
    int word_count;

    read_words(argv[2], list1, &word_count);
    read_paragraph(argv[1], list1, word_count);
    print_end(list1, word_count);

    return 0;
}

// Let's code the word reading function first:
void read_words(char *filename, words list1[], int *count_pointer)
{
    FILE *fp;

    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File error!\n");
        exit(1);
    }

    while (count < MAX_WORDS && fscanf(fp, "%s", list1[count].word) != EOF)
    {
        list1[count].occurrence = 0;
        count++;
    }

    *count_pointer = count;

    fclose(fp);
}

// Now the string comparison part:
int compare (char *word1, char *word2)
{
    int count;

    // We return a negative value immediately if words are not even same length.
    if (strlen(word1) != strlen(word2))
    {
        return 0;
    }

    // Loop for checking letter by letter ignoring capitalization.
    for (count = 0; count < strlen(word1); count++)
        {
        if (tolower(word1[count]) != tolower(word2[count]))
        {
            return 0;
        }
    }

    return 1; // If it passes both of the checks, we return 1 (positive) here.
}

// Printing loop to use at the end for outputs.
void print_end(words list1[], int total)
{
    int i;

    for (i = 0; i < total; i++)
    {
        printf("%s - %d occurrence(s)\n", list1[i].word, list1[i].occurrence);
    }
}

// Essential function to read from the first file and append the list we created.
void read_paragraph(char *filename, words list1[], int word_count)
{
    char word[MAX_WORD_LENGTH];
    int loop_count;
    FILE *fp;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File error!\n");
        exit(1);
    }

    while (fscanf (fp, "%s", word) != EOF) // Taking every single word in the file, one by one.
    {
        for (loop_count = 0; loop_count < word_count; loop_count++) // Trying with each word we have in the dictionary one by one.
        {
            if (compare(word, list1[loop_count].word) == 1)
            {
                list1[loop_count].occurrence++; // If found, increase by one.
            }
        }
    }

    fclose(fp);
}