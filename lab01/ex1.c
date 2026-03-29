#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// grep flag pattern file
// ./ex1 "lala" ~/Documents/networks/data.txt

int main(int argc, char* argv[])
{
    // flag being optional and now ignored completely
    if(argc < 3 || argc < 1) 
    {
        printf("error: wrong number of parameters.\n");
        return EXIT_FAILURE;
    }
        
    argv[1]; // pattern
    argv[2]; // path

    FILE* text = fopen(argv[2], "rb+");
    if(NULL == text)
        return EXIT_FAILURE;
    
    char line[100];
    while(fgets(line, sizeof(line), text))
        if(strstr(line, argv[1]))
            printf("%s\n", argv[1]);

    return 0;
}
