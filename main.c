/** @file */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "deklaracje.h"

int main(int argc, char **argv)
{
    char * input_name;
    char * output_name;
    if(argc == 5){
        for(int i = 0; i < 5; i++){
            if(strcmp(argv[i], "-i") == 0)
                input_name = argv[++i];
            else if(strcmp(argv[i], "-o") == 0)
                output_name = argv[++i];
        }
//        printf("%s\n", input_name);
//        printf("%s\n", output_name);
    }
    else if (argc == 2 && strcmp(argv[1], "-h") == 0){
        printf("To use the program: \n use -i switch and type input file name/location and -o switch and type output file name/location\n for example: app -i input.txt -o output.txt\n");
        return -1;
    }
    else{
        printf("Wrong program arguments, use -h to show help message\n");
        return -1;
    }

    words * pHead = NULL;

    read_input(input_name, &pHead);

    create_output(pHead, output_name);

    delete_list(&pHead);

    print_list(pHead);
    return 0;
}
