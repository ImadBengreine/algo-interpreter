#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Lexer lexer_init(char *source) {
	Lexer lexer;
	lexer.source = source;
	lexer.pos = 0;
	lexer.line = 1;
	lexer.column = 1;
	return lexer;
}

char current_char(Lexer* lexer) {
	lexer->source[lexer->pos];
}

void advance(Lexer* lexer) {
	if (current_char() == '\n')
	{
		lexer->line++;
	}
	lexer->pos++;
}

// Ignore les espaces, tabulations, sauts de ligne
void skip_whitespace(Lexer* lexer) {
	while (current_char() == ' '  || 
           current_char() == '\t' || 
           current_char() == '\n' || 
           current_char() == '\r') {
		advance();
	}
}

TokenType check_keyword(const char* word) {
	if (strcmp(word, "ALGORITHME") == 0) return TOKEN_ALGORITHME;
    if (strcmp(word, "DEBUT") == 0)      return TOKEN_DEBUT;
    if (strcmp(word, "FIN") == 0)        return TOKEN_FIN;
    if (strcmp(word, "ECRIRE") == 0)     return TOKEN_ECRIRE;

    return TOKEN_IDENT;
}

Token get_next_token(Lexer* lexer) {
	skip_whitespace();

	Token tok;
	tok.line = lexer->line;
	tok.value[0] = '\0';

	if (current_char() == '\0') {
		tok.type = TOKEN_EOF;
		strcpy(tok.value, "EOF");
		return tok;
	}

	if (isalpha(current_char())) {
		int i = 0;
		while (isalnum(current_char()) || current_char() == '_') {
			tok.value[i++] = current_char();
			advance();
		}
		tok.value[i] = '\0';
		tok.type = check_keyword(tok.value);
		return tok;
	}
}