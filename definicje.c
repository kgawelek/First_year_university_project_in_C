/** @file */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "deklaracje.h"

void add_to_list(words ** pHead, char * new_word, int line_nr)
{
    // first added element

//    printf("%s ", new_word);
    if(*pHead == NULL) {
        words * temp;

        if(temp = (words *) malloc(sizeof(words))) {

            if(temp->word = (char *) malloc(sizeof(char *) * strlen(new_word)))
                strcpy(temp->word, new_word);

            temp->pNext = NULL;
            if(temp->lines_head = (lines *) malloc(sizeof(lines))) {
                temp->lines_head->line = line_nr;
                temp->lines_head->pNext = NULL;
            }
            *pHead = temp;
        }
    }

    // new word is alphabetically before word in pHead
    else if(strcmp(new_word, (*pHead)->word) < 0){
        struct words * temp;

        if(temp = (words *) malloc(sizeof(words))) {
            if (temp->word = (char *) malloc(sizeof(char *) * strlen(new_word)))
                strcpy(temp->word, new_word);

            temp->pNext = *pHead;
            if(temp->lines_head = (lines *) malloc(sizeof(lines))) {
                temp->lines_head->line = line_nr;
                temp->lines_head->pNext = NULL;
            }
            *pHead = temp;
        }
    }

    else{

        words * temp = *pHead;
        while (temp->pNext != NULL && strcmp(temp->pNext->word, new_word) < 0)
            temp = temp->pNext;

        // word was before in the list in head, adding new line number
        if (strcmp(temp->word, new_word) == 0){
            lines * nr = temp->lines_head;
            while (nr->pNext != NULL)
                nr = nr->pNext;

            if(nr->pNext = (lines *) malloc(sizeof(lines))) {
                nr->pNext->pNext = NULL;
                nr->pNext->line = line_nr;
            }
        }

        // word was before in the list but not in the head, adding new line number
        else if (temp->pNext != NULL && strcmp(temp->pNext->word, new_word) == 0){
            lines * nr = temp->pNext->lines_head;
            while (nr->pNext != NULL)
                nr = nr->pNext;

            if(nr->pNext = (lines *) malloc(sizeof(lines))) {
                nr->pNext->pNext = NULL;
                nr->pNext->line = line_nr;
            }
        }

        // adding to the end of the list
        else if (temp->pNext == NULL){

            if(temp->pNext = (words *) malloc(sizeof(words))) {

                temp->pNext->pNext = NULL;
                if(temp->pNext->word = (char *) malloc(sizeof(char *) * strlen(new_word)))
                    strcpy(temp->pNext->word, new_word);

                if(temp->pNext->lines_head = (lines *) malloc(sizeof(lines))) {
                    temp->pNext->lines_head->line = line_nr;
                    temp->pNext->lines_head->pNext = NULL;
                }
            }
        }

        // adding new word in proper place
        else{
            words * temp2;
            if(temp2 = (words *) malloc(sizeof(words))) {

                temp2->word = (char *) malloc(sizeof(char *) * strlen(new_word));
                strcpy(temp2->word, new_word);
                temp2->pNext = temp->pNext;
                if(temp2->lines_head = (lines *) malloc(sizeof(lines))) {
                    temp2->lines_head->line = line_nr;
                    temp2->lines_head->pNext = NULL;
                }
                temp->pNext = temp2;

            }
        }
    }
}

void print_list(words * pHead)
{
    while (pHead != NULL){
        printf("%s\n", pHead->word);
        while (pHead->lines_head != NULL){
            printf("%d ", pHead->lines_head->line);
            pHead->lines_head = pHead->lines_head->pNext;
        }
        printf("\n");
        pHead = pHead->pNext;
    }
}

void read_input(char * input_name, words ** pHead)
{
    FILE * input = fopen(input_name, "r");
    int line_nr = 1;

    if(input == NULL){
        printf("Could not open the file!");
        return;
    }
    char c;
    char word[100];

    while(fscanf(input, "%s", word) != EOF){
        word[0] = tolower(word[0]); // changing first letter of the word to lowercase

        // if scanned string is a number, dont add it to the list
        // checking only first character, if a number is in different place in the word,
        // word will be added anyway
        bool is_a_number = false;
        if (isdigit(word[0]))
            is_a_number = true;

        // if there is the ending of the sentence, this code cuts it off
        for(int i = 0; i < strlen(word); i++){
            if(word[i] == '.' || word[i] == ',' || word[i] == '!' ||word[i] == '?')
                word[i] = '\0';
        }
//        printf("%s %d\n", word, line_nr);
        if(!is_a_number)
            add_to_list(pHead, word, line_nr);
        c = getc(input);

        if (c == '\n')
            line_nr++;
    }
    fclose(input);
}

void create_output(words * pHead, char * output_name)
{
    FILE * output = fopen(output_name, "w");

    if (output == NULL) {
        printf("Could not open output file!");
    }

    else{
        while (pHead != NULL){
            fprintf(output, "%s: ", pHead->word);
            while (pHead->lines_head != NULL){

                if(pHead->lines_head->pNext == NULL)
                    fprintf(output,"%d", pHead->lines_head->line);
                else
                    fprintf(output,"%d, ", pHead->lines_head->line);
                pHead->lines_head = pHead->lines_head->pNext;
            }

            fprintf(output, "\n");
            pHead = pHead->pNext;
        }
    }

    fclose(output);
    printf("Output file has been created successfully!");
}

void delete_list(words ** pHead)
{
    while(*pHead != NULL){
        words * tmp = (*pHead)->pNext;
        free((*pHead)->word);
        while ((*pHead)->lines_head != NULL){
            lines * l_tmp = (*pHead)->lines_head->pNext;
            free((*pHead)->lines_head);
            (*pHead)->lines_head = l_tmp;
        }
        free(*pHead);
        *pHead = tmp;
    }
}