#ifndef LEXER_H
#define LEXER_H

/* ============================================================
   PARTIE 1 : LES TYPES DE TOKENS
   ============================================================
   Un enum = une liste de constantes numérotées automatiquement.
   Chaque valeur représente un type de "mot" dans notre langage.
   ============================================================ */
typedef enum {
    TOKEN_ALGORITHME,   // 0
    TOKEN_DEBUT,        // 1
    TOKEN_FIN,          // 2
    TOKEN_ECRIRE,       // 3
    TOKEN_IDENT,        // 4  (noms: variables, algorithmes...)
    TOKEN_STRING,       // 5  ("texte entre guillemets")
    TOKEN_LPAREN,       // 6  (
    TOKEN_RPAREN,       // 7  )
    TOKEN_SEMICOLON,    // 8  ;
    TOKEN_EOF,          // 9  (fin du fichier)
    TOKEN_UNKNOWN       // 10 (caractère inconnu)
} TokenType;


typedef struct
{
	TokenType type;
	char value[256];	// The actual text
	int position;	// Character index in source
	int length;		// How many char this token span
	int line;		// Line number (for error messages)
	int column;		// Column number (for error messages)
} Token;

typedef struct
{
	const char* source;     // The entire source code
	int pos;          // Current character position
	int line;         // Current line number
	int column;       // Current column number
} Lexer;

Lexer lexer_init(const char *source);
char current_char(Lexer* lexer);
void advance(Lexer* lexer);
void skip_whitespace(Lexer* lexer);
TokenType check_keyword(const char* word);
Token get_next_token(Lexer* lexer);

#endif