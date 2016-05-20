/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//http://www.cplusplus.com/reference/cctype/ best reference ever for this assignment


/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
    char* input;
    int head;
    int next;
    char **words;
    int wordCount;
    char **tokenArray;
    char *tokenType;
    int tkCount;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */



//initializes tokenizer struct. temp is the input string which equals ts,
//tokenizer->input is going to be the string that will be divided into tokens
//tokenArray will be the array of tokens
TokenizerT *TKCreate( char * ts ) {
    char * temp = malloc(sizeof(char*)*100);
    TokenizerT *Tokenizer = malloc(sizeof(TokenizerT)*100);
    Tokenizer->input = malloc(sizeof(char*)*100);
    Tokenizer->tokenArray = malloc(sizeof(char*)*100);
    Tokenizer->tokenType = malloc(sizeof(char*)*100);
    Tokenizer->tkCount = 0;
    
    temp = ts;
    //Tokenizer = malloc(sizeof(TokenizerT));
    if (temp == NULL){
        return NULL;
    }
    strcpy(Tokenizer->input, temp);
    
    //    Tokenizer->head = Tokenizer->input[0];
    //    Tokenizer->next = Tokenizer->input[1];
    Tokenizer->head = 0;
    Tokenizer->next = 1;
    return Tokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

//take in tokenizer, get tokeinezer->input, find the next token and return it.
//shouldn't do the sorting of tokens into words, hex, etc. Do that in print tokens when iterating through tokenArray.
char *TKGetNextToken( TokenizerT * tk ) {
    
    char* tkn = malloc(sizeof(char*)*100);
    int count = 0;
    
    //********************************************************************************
    //kind of works as a trim function that will deal with white space all over the place
    if (isspace(tk->input[tk->head])){
        while (isspace(tk->input[tk->next])){
            tkn[count] = tk->input[tk->head];
            count++;
            tk->head++;
            tk->next++;
        }
        tk->tokenType[tk->tkCount] = 'n';
        tk->head = 0;
        tk->next = 1;
        tk->tkCount++;
        return tkn;
    }
    
    //********************************************************************************

    
    if (isalpha(tk->input[tk->head])){
        while (tk->input[count] != '\0'){
            if (isalnum(tk->input[tk->head])){
                //printf("%i\n", tk->h);
                tkn[count] = tk->input[tk->head];
                count++;
                tk->head++;
                tk->next++;
            }
            else{
                tk->head = 0;
                tk->next = 1;
                tk->tokenType[tk->tkCount] = 'w';
                tk->tkCount++;
                return tkn;
            }
        }
        tk->head = 0;
        tk->next = 1;
        tk->tokenType[tk->tkCount] = 'w';
        tk->tkCount++;
        return tkn;
    }
    //decimal integer constant
    if (isdigit(tk->input[tk->head])){
        while (tk->input[count] != '\0'){
            if (isdigit(tk->input[tk->head])){
                
                //hex
                if (tk->input[tk->head] == '0'){
                    if (tk->input[tk->next] == 'x'){
                        tkn[count] = tk->input[tk->head];
                        count++;
                        while(isalnum(tk->input[tk->next])){
                            tkn[count] = tk->input[tk->next];
                            tk->next++;
                            count++;
                        }
                        tk->head = 0;
                        tk->next = 1;
                        tk->tokenType[tk->tkCount] = 'h';
                        tk->tkCount++;
                        printf("%s\n", tkn);
                        return tkn;
                    }
                }
                
                
                //printf("%i\n", tk->h);
                tkn[count] = tk->input[tk->head];
                count++;
                tk->head++;
                tk->next++;
            }
            
            
           //*****************************************************************************************
            //float: this is new code along with the subsequent search if statement in print tokens
            if (tk->input[tk->head] == '.' && isdigit(tk->input[tk->next])){
                while (isdigit(tk->input[tk->next])){
                    tkn[count] = tk->input[tk->head];
                    count++;
                    tk->head++;
                    tk->next++;
                    if (tk->input[tk->next] == 'e' || tk->input[tk->next] == 'E'){
                        tkn[count] = tk->input[tk->head];
                        count++;
                        tk->head++;
                        tk->next++;
                        if (tk->input[tk->next] == '-'){
                            tkn[count] = tk->input[tk->head];
                            count++;
                            tk->head++;
                            tk->next++;
                        }
                    }
                }
                tkn[count] = tk->input[tk->head];
                tk->tokenType[tk->tkCount] = 'f';
                tk->head = 0;
                tk->next = 1;
                tk->tkCount++;
                return tkn;
            }
            //*****************************************************************************************
            
            //if (char = x ) then hex if  char = . then float
            else{
                tk->head = 0;
                tk->next = 1;
                tk->tokenType[tk->tkCount] = 'd';
                tk->tkCount++;
                return tkn;
            }
        }
        tk->head = 0;
        tk->next = 1;
        tk->tokenType[tk->tkCount] = 'd';
        tk->tkCount++;
        return tkn;
    }
    if (tk->input[tk->head] == '['){
        tkn[0] = '[';
        tk->head = 0;
        tk->next = 1;
        tk->tokenType[tk->tkCount] = '[';
        tk->tkCount++;
        return tkn;
    }
    if (tk->input[tk->head] == ']'){
        tkn[0] = ']';
        tk->head = 0;
        tk->next = 1;
        tk->tokenType[tk->tkCount] = ']';
        tk->tkCount++;
        return tkn;
    }
    tk->head = 0;
    tk->next = 1;
    return tkn;
    
    
    
    
    //    printf("%s\n", "--------------------------");
    //    printf("%s\n", tk->input);
    //    printf("%s\n", "--------------------------");
    //word
    
    
    
    
    //    int i = 0;
    //    while((!isspace(tk->input[tk->head])|| )){
    //        tkn[i] = tk->input[tk->head];
    //    }
    
    
    
    
    
    
    
    
    
    //----------------------------------------------------------
    
    //    while (tk->input[tk-head] != '\0'){
    //        //white space
    //        if (isspace(tk->input[tk->head])){
    //
    //        }
    //        //not a printable character
    //        if (!isprint(tk->input[tk->head])){
    //
    //        }//hex
    //        if (tk->input[tk->head]) == '0'){
    //            if (tk->input[tk->next] == 'x'){
    //
    //            }
    //        }
    //        //word or digit
    //        if (isalpha(tk->input[tk->head])){
    //
    //        }
    //
    //    }
    
    
    
    
    
    
    
    
    //--------------------------------------------------------------
    
    
    
    
}
int checkCKEYS(char *token){
    const char *cKeys[32] = {"auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
        "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
    //int boolean = -1;
    
    for (int i = 0; i < 32; i++){
        if (strcmp(token, cKeys[i]) == 0){
            return 0;
        }
    }
    return -1;
}

/*
 *printTokens will print the token array as well as sort types of tokens,
 *maybe a helper for the sorting
 */

int printTokens(TokenizerT * tk){
    int i = 0;
    while (tk->tokenArray[i] != '\0'){
        if (tk->tokenType[i] == 'n'){
            i++;
            continue;
        }
        if (tk->tokenType[i] == 'w'){
            int boolean = checkCKEYS(tk->tokenArray[i]);
            if (boolean >= 0){
                printf("C Keyword: %s\n", tk->tokenArray[i]);
                i++;
                continue;
            }
            //printf("%s", "word: ");
            printf("word: %s\n", tk->tokenArray[i]);
            i++;
            continue;
        }
        if (tk->tokenType[i] == 'd'){
            //printf("%s", "digit: ");
            printf("digit: %s\n", tk->tokenArray[i]);
            i++;
            continue;
        }
        if (tk->tokenType[i] == 'h'){
            //printf("%s", "hex constant: ");
            printf("hex constant: %s\n", tk->tokenArray[i]);
            i++;
            continue;
        }
        if (tk->tokenType[i] == '['){
            //printf("%s", "leftbrace: ");
            printf("leftbrace: %s\n", tk->tokenArray[i]);
            i++;
            continue;
        }
        if (tk->tokenType[i] == ']'){
            //printf("%s", "rightbrace: ");
            printf("rightbrace: %s\n", tk->tokenArray[i]);
            i++;
            continue;
        }
        if (tk->tokenType[i] == 'f'){
            printf("floating-point constant: %s\n", tk->tokenArray[i]);
            i++;
            continue;
        }
        printf("%s\n", tk->tokenArray[i]);
        i++;
    }
    return 0;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

//get input string, if incorrect return error message
//create the tokenizer, send to get next token, add token to token array, substring(memcpy) to string-token, continue
//call print tokens
int main(int argc, char **argv) {
    
    if (argc < 2 || argc > 2){
        printf("%s\n", "Enter valid input string");
        return 0;
    }
    
    
    
    
    int string_length = 0;
    int token_length = 0;
    
    char* input = argv[1];
    TokenizerT *tok = TKCreate(input);
    
    int temp = strlen(input);
    char* token = malloc(sizeof(char*)*100);
    
    
    char **words = malloc(sizeof(char*)*100);
    int tokenCount = 0;
    
    //while(temp > 0){
    while(tok->input[0] != '\0'){
        string_length = strlen(tok->input);
        token = TKGetNextToken(tok);
        tok->tokenArray[tokenCount] = token;
        tokenCount++;
        
        token_length = strlen(token)-1;
        temp = string_length - token_length;
        
        memcpy(tok->input, &tok->input[token_length]+1, temp);
        
        if (isspace(tok->input[0])||ispunct(tok->input[0])){
            if (tok->input[0] == '[' || tok->input[0] == ']'){
                continue;
            }
            tok->input++;
        }
        
        //string_length = strlen(tok->input);
        
        //token = TKGetNextToken(tok);
        
        //token_length = strlen(token);
        
        //temp = string_length - token_length;
    }
    //    printf("%lu\n", strlen(token));
    //token.length to substring after token is found
    
    //TKDestroy(tok);
    printTokens(tok);
    return 0;
    
}





