#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Lexer lexer_init(const char *source) {
	Lexer lexer;
	lexer.source = source;
	lexer.pos = 0;
	lexer.line = 1;
	lexer.column = 1;
	return lexer;
}

char current_char(Lexer* lexer) {
	return lexer->source[lexer->pos];
}

void advance(Lexer* lexer) {
	if (current_char(lexer) == '\n')
	{
		lexer->line++;
		lexer->column = 1;
	}
	else {
		lexer->column++;
	}

	lexer->pos++;
}

// Ignore les espaces, tabulations, sauts de ligne
void skip_whitespace(Lexer* lexer) {
	while (current_char(lexer) == ' '  || 
           current_char(lexer) == '\t' || 
           current_char(lexer) == '\n' || 
           current_char(lexer) == '\r') {
		advance(lexer);
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
	skip_whitespace(lexer);

	Token tok;
	tok.line = lexer->line;
	tok.value[0] = '\0';

	if (current_char(lexer) == '\0') {
		tok.type = TOKEN_EOF;
		strcpy(tok.value, "EOF");
		return tok;
	}

	if (isalpha(current_char(lexer))) {
		int i = 0;
		while (isalnum(current_char(lexer)) || current_char(lexer) == '_') {
			tok.value[i++] = current_char(lexer);
			advance(lexer);
		}
		tok.value[i] = '\0';
		tok.type = check_keyword(tok.value);
		return tok;
	}

	if (current_char(lexer) == '"') {
		advance(lexer);
		int i = 0;
		while (current_char(lexer) != '"' && current_char(lexer) != '\0') {
			tok.value[i++] = current_char(lexer);
            advance(lexer);
		}
		tok.value[i] = '\0';
		if (current_char(lexer) == '"') {
			advance(lexer);
		}

		tok.type = TOKEN_STRING;
		return tok;
	}

	char c = current_char(lexer);
	advance(lexer);
	tok.value[0] = c;
    tok.value[1] = '\0';

    switch (c) {
    	case '(': tok.type = TOKEN_LPAREN;	break;
    	case ')': tok.type = TOKEN_RPAREN;	break;
    	case ';': tok.type = TOKEN_SEMICOLON;	break;
    	default: tok.type = TOKEN_UNKNOWN;	break;
    }
    return tok;
}