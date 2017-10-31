#ifndef TOKENIZER_H
#define TOKENIZER_H


typedef struct Tokenizer {
	char*			pToken;												// Token
	//
	char*			current_pointer;									// Points to current char at the line to tokenize
	//
	int				delimiter;												// Delimiter
	int				quote;													// Quote
	//
	int 				isEnded;												// Indicates that no more tokens need to be parsed
} Tokenizer;


/*
Initilizes the tokenizer
*/
void initTokenizer(Tokenizer* pTokenizer, char* _current_pointer, int _delimiter, int _quote);


/*
Tokenizes next token

return either the token or NULL if no more token.
Token could be an empty string.
This function changes the input string.

Handling token quoted with \"
Trim the token
*/
char* getNextToken(Tokenizer* pTokenizer);


/*
Trims leading and trailing whitespace
This function changes the input string
*/
char* trim(char* input);


#endif