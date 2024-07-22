#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void removeQuotes(char *str, char **ptr);
void removeComma(char *str, char **ptr);

// int main (int argc, char **argv) {
//     FILE *files[argc];
//     int cardCount = 0;
//     for (int i = 0; i < argc - 1; i++){
//         FILE *curFile = fopen(argv[i + 1], "r");
//         if (curFile == NULL){
//             printf("file null, %s\n", argv[i + 1]);
//             exit(1);
//         }
//         char line[1024];
//         fgets(line, sizeof(line), curFile);
//         while (fgets(line, sizeof(line), curFile)) {
//             printf("hello\n");
//             char *token;
//             token = strtok(line, ",");
//             while (token != NULL) {
//                 token = strtok(NULL, ",");
//                 token = strtok(NULL, ",");
//                 token[0] = '*';
//                 if (strstr(token, "\"")){
//                     token = strtok(NULL, ",");
//                 } else {
//                     token = strtok(NULL, ",");
//                     char *extra;
//                     char *temp;
//                     token = strtok(NULL, ",");
//                     temp = strtok(NULL, ",");
//                     strcpy(extra, temp);
//                     strcat(token, ",");
//                     strcat(token, extra);
//                 }
//                 char *store;
//                 removeQuotes(token, &store);
//                 printf("%s\n", store);
                
//                 if (strstr(store, "Island") || strstr(store, "Forest") || strstr(store, "Plains") || strstr(store, "Mountain") || strstr(store, "Swamp")){
//                     cardCount --;
//                 }
//                 cardCount ++;
//                 //printf("%s ", token);
//                 removeComma(token, &store);
//                 token = store;
//                 //free(store);
//                 token = strtok(NULL, ",");
//             }
//         }
//     }
//     printf("%d", cardCount);
// }

// void removeQuotes(char *curArg, char **ptr){
//     int len = strlen(curArg);
//     char *ret = malloc(len + 1);
//     int sourceInd = 0;
//     int destInd = 0;

//     //if the source has a quote, we skip that char (advance source)
//     //otherwise, we copy the source to the current dest and advance both
//     while (sourceInd < len){
//         if (isspace(curArg[sourceInd]) && curArg[sourceInd] != ' '){
//             curArg[destInd] = '\0';
//             sourceInd = len;
//         } else if (curArg[sourceInd] != '\"'){
//             curArg[destInd] = curArg[sourceInd];
//             if (isspace(curArg[sourceInd])){
                
//             }
//             destInd++;
//         } 
//         sourceInd++;
//     }
//     *ptr = curArg;
// }

// void removeComma(char *curArg, char **ptr){
//     int len = strlen(curArg);
//     char *ret = malloc(len + 1);
//     int sourceInd = 0;
//     int destInd = 0;

//     //if the source has a quote, we skip that char (advance source)
//     //otherwise, we copy the source to the current dest and advance both
//     while (sourceInd < len){
//         if (isspace(curArg[sourceInd]) && curArg[sourceInd] != ' '){
//             curArg[destInd] = '\0';
//             sourceInd = len;
//         } else if (curArg[sourceInd] != ','){
//             curArg[destInd] = curArg[sourceInd];
//             if (isspace(curArg[sourceInd])){
                
//             }
//             destInd++;
//         } 
//         sourceInd++;
//     }
//     *ptr = curArg;
// }

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <csv_file1> <csv_file2> ...\n", argv[0]);
        return 1;
    }

    int cardCount = 0;
    FILE *output = fopen("mtgList.txt", "w");
    if (output == NULL) {
        printf("Error opening output file\n");
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        FILE *curFile = fopen(argv[i], "r");
        if (curFile == NULL) {
            printf("Error opening file: %s\n", argv[i]);
            return 1;
        }

        char line[1024];
        fgets(line, sizeof(line), curFile);
        while (fgets(line, sizeof(line), curFile)) {
            char *token;
            char *saveptr;
            int tokenCount = 0;
            
            token = strtok_r(line, ",", &saveptr);
            while (token != NULL) {
                if (tokenCount >= 3) {
                    char *store;
                    if (tokenCount == 3){
                        if (isspace(token[0])){
                            token = strtok_r(NULL, ",", &saveptr);
                            char *extra = malloc(1024);
                            char *temp = malloc(1024);
                            temp = strtok_r(NULL, ",", &saveptr);
                            //printf("%s\n", temp);
                            strcpy(extra, temp);
                            strcat(token, ",");
                            strcat(token, extra);
                            free(extra);
                        }
                        //printf("to be printed: %s\n", token);
                    }
                    removeQuotes(token, &store);

                    if (strstr(store, "Island") || strstr(store, "Forest") || strstr(store, "Plains") || strstr(store, "Mountain") || strstr(store, "Swamp")) {
                        cardCount--;
                    }
                    cardCount++;
                    fprintf(output, "%s", store);
                    removeComma(store, &store);
                    free(store);  // Free the allocated memory after use
                }

                tokenCount++;
                token = strtok_r(NULL, ",", &saveptr);
            }
        }
        fclose(curFile);
    }
    printf("Card Count, without basics: %d\n", cardCount);
    fseek(output, -1, SEEK_CUR);
    fprintf(output, " ");
    fclose(output);
    return 0;
}

void removeQuotes(char *curArg, char **ptr) {
    //printf("removing quotes on: %s\n", curArg);
    int len = strlen(curArg);
    char *ret = malloc(len + 1);
    if (!ret) {
        perror("Memory allocation error");
        exit(1);
    }

    int destInd = 0;
    for (int sourceInd = 0; sourceInd < len; sourceInd++) {
        if (curArg[sourceInd] != '\"') {
            ret[destInd++] = curArg[sourceInd];
        }
    }
    ret[destInd] = '\0';
    *ptr = ret;
}

void removeComma(char *curArg, char **ptr) {
    int len = strlen(curArg);
    char *ret = malloc(len + 1);
    if (!ret) {
        perror("Memory allocation error");
        exit(1);
    }

    int destInd = 0;
    for (int sourceInd = 0; sourceInd < len; sourceInd++) {
        if (curArg[sourceInd] != ',') {
            ret[destInd++] = curArg[sourceInd];
        }
    }
    ret[destInd] = '\0';
    *ptr = ret;
}