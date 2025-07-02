#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "symbol_table.h"
#include "code_generator.h"

/* Estrutura para nós da árvore sintática */
typedef struct ASTNode {
    enum {
        NODE_PROGRAM,
        NODE_DECLARATION_LIST,
        NODE_VAR_DECLARATION,
        NODE_FUN_DECLARATION,
        NODE_PARAM,
        NODE_COMPOUND_STMT,
        NODE_EXPRESSION_STMT,
        NODE_SELECTION_STMT,
        NODE_ITERATION_STMT,
        NODE_RETURN_STMT,
        NODE_ASSIGN,
        NODE_BINARY_OP,
        NODE_UNARY_OP,
        NODE_CALL,
        NODE_VAR,
        NODE_ARRAY_ACCESS,
        NODE_CONSTANT,
        NODE_IDENTIFIER
    } node_type;
    
    DataType data_type;
    int line_number;
    
    union {
        struct {
            char *name;
            DataType type;
            int array_size;
        } var_decl;
        
        struct {
            char *name;
            DataType return_type;
            struct ASTNode *params;
            struct ASTNode *body;
        } fun_decl;
        
        struct {
            struct ASTNode *condition;
            struct ASTNode *then_stmt;
            struct ASTNode *else_stmt;
        } selection;
        
        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } iteration;
        
        struct {
            struct ASTNode *expression;
        } return_stmt;
        
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            Operator operator;
        } binary_op;
        
        struct {
            char *name;
            struct ASTNode *args;
        } call;
        
        struct {
            char *name;
            struct ASTNode *index;
        } var_ref;
        
        struct {
            DataType type;
            union {
                int int_value;
                float float_value;
                char char_value;
            } value;
        } constant;
        
        char *identifier;
    } data;
    
    struct ASTNode *next;
    Address *code_addr;  /* Endereço para geração de código */
} ASTNode;

/* Contexto semântico */
typedef struct SemanticContext {
    SymbolTable *symbol_table;
    InstructionList *code_list;
    DataType current_function_return_type;
    int semantic_errors;
    int in_function;
} SemanticContext;

/* Protótipos das funções de análise semântica */
void init_semantic_analysis(void);
void finalize_semantic_analysis(void);
SemanticContext* get_semantic_context(void);

/* Funções de verificação semântica */
int check_program(ASTNode *program);
int check_declaration_list(ASTNode *decl_list);
int check_var_declaration(ASTNode *var_decl);
int check_fun_declaration(ASTNode *fun_decl);
int check_compound_statement(ASTNode *compound);
int check_statement(ASTNode *stmt);
ExpressionNode* check_expression(ASTNode *expr);
int check_assignment(ASTNode *assign);
int check_function_call(ASTNode *call);
ExpressionNode* check_function_call_expression(ASTNode *call);
ExpressionNode* check_array_access(ASTNode *array_access);
int check_selection_statement(ASTNode *stmt);
int check_iteration_statement(ASTNode *stmt);
int check_return_statement(ASTNode *stmt);

/* Verificação de tipos */
int types_compatible(DataType type1, DataType type2);
DataType get_binary_result_type(DataType left, DataType right, Operator op);
int is_arithmetic_type(DataType type);
int is_numeric_type(DataType type);

/* Funções de criação de nós da AST */
ASTNode* create_program_node(ASTNode *declarations);
ASTNode* create_var_declaration_node(const char *name, DataType type, int line);
ASTNode* create_fun_declaration_node(const char *name, DataType return_type, 
                                   ASTNode *params, ASTNode *body, int line);
ASTNode* create_binary_op_node(Operator op, ASTNode *left, ASTNode *right, int line);
ASTNode* create_identifier_node(const char *name, int line);
ASTNode* create_constant_node(DataType type, void *value, int line);
ASTNode* create_call_node(const char *name, ASTNode *args, int line);

/* Geração de código para diferentes construtos */
ExpressionNode* generate_expression_code(ASTNode *expr);
void generate_statement_code(ASTNode *stmt);
void generate_assignment_code(ASTNode *assign);
void generate_if_code(ASTNode *if_stmt);
void generate_while_code(ASTNode *while_stmt);
void generate_call_code(ASTNode *call);

/* Utilitários */
void semantic_error(int line, const char *format, ...);
void semantic_warning(int line, const char *format, ...);
DataType token_to_data_type(int token);
void print_ast(ASTNode *node, int indent);

/* Liberação de memória */
void free_ast_node(ASTNode *node);

/* Funções da tabela de símbolos global */
void init_symbol_table(void);
void finalize_symbol_table(void);
SymbolTable* get_symbol_table(void);

/* Funções do gerador de código global */
void init_code_generator(void);
void finalize_code_generator(void);
InstructionList* get_instruction_list(void);

#endif /* SEMANTIC_H */
