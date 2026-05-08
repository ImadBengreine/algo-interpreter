#include <stdio.h>
#include "src/lexer.h"

int main() {
    // Ton exemple
    const char* program = 
        "ALGORITHME bonjour\n"
        "DEBUT\n"
        "ECRIRE(\"aloo hhh\");\n"
        "FIN";
    
    printf("=== Code Source ===\n%s\n\n", program);
    printf("=== Tokens générés ===\n");
    printf("%-4s %-15s %s\n", "LIGNE", "TYPE", "VALEUR");
    printf("----------------------------\n");
    Lexer lexer = lexer_init(program);
    
    Token tok;
    do {
        tok = get_next_token(&lexer);
        
        const char* type_name;
        switch (tok.type) {
            case TOKEN_ALGORITHME: type_name = "ALGORITHME"; break;
            case TOKEN_DEBUT:      type_name = "DEBUT";      break;
            case TOKEN_FIN:        type_name = "FIN";        break;
            case TOKEN_ECRIRE:     type_name = "ECRIRE";     break;
            case TOKEN_IDENT:      type_name = "IDENT";      break;
            case TOKEN_STRING:     type_name = "STRING";     break;
            case TOKEN_LPAREN:     type_name = "LPAREN";     break;
            case TOKEN_RPAREN:     type_name = "RPAREN";     break;
            case TOKEN_SEMICOLON:  type_name = "SEMICOLON";  break;
            case TOKEN_EOF:        type_name = "EOF";        break;
            default:               type_name = "UNKNOWN";    break;
        }
        
        printf("%-4d %-15s '%s'\n", tok.line, type_name, tok.value);
        
    } while (tok.type != TOKEN_EOF);
    
    return 0;
}