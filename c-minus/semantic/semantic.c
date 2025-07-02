#include "semantic.h"
#include "utils.h"
#include <stdarg.h>
#define _GNU_SOURCE
#include <string.h>

/* Contexto semântico global */
static SemanticContext *global_context = NULL;

/**
 * Inicializa a análise semântica
 */
void init_semantic_analysis(void) {
    global_context = (SemanticContext*)malloc(sizeof(SemanticContext));
    if (!global_context) {
        fprintf(stderr, "Erro fatal: Não foi possível alocar contexto semântico\n");
        exit(1);
    }
    
    init_symbol_table();
    init_code_generator();
    
    global_context->symbol_table = get_symbol_table();
    global_context->code_list = get_instruction_list();
    global_context->current_function_return_type = TYPE_VOID;
    global_context->semantic_errors = 0;
    global_context->in_function = 0;
    
    printf(">>> Análise semântica inicializada\n");
}

/**
 * Finaliza a análise semântica
 */
void finalize_semantic_analysis(void) {
    if (global_context) {
        printf("\n>>> Análise semântica finalizada\n");
        printf(">>> Erros semânticos encontrados: %d\n", global_context->semantic_errors);
        
        if (global_context->semantic_errors == 0) {
            printf(">>> Programa semanticamente correto!\n");
        }
        
        print_symbol_table(global_context->symbol_table);
        finalize_code_generator();
        finalize_symbol_table();
        
        free(global_context);
        global_context = NULL;
    }
}

/**
 * Obtém o contexto semântico
 */
SemanticContext* get_semantic_context(void) {
    return global_context;
}

/**
 * Verifica um programa
 */
int check_program(ASTNode *program) {
    if (!program || !global_context) return 0;
    
    printf(">>> Verificando programa...\n");
    
    if (program->node_type != NODE_PROGRAM) {
        semantic_error(program->line_number, "Nó raiz inválido do programa");
        return 0;
    }
    
    /* As declarações estão no campo next do nó programa */
    return check_declaration_list(program->next);
}

/**
 * Verifica uma lista de declarações
 */
int check_declaration_list(ASTNode *decl_list) {
    if (!decl_list) return 1;
    
    ASTNode *current = decl_list;
    int success = 1;
    
    while (current) {
        switch (current->node_type) {
            case NODE_VAR_DECLARATION:
                success &= check_var_declaration(current);
                break;
            case NODE_FUN_DECLARATION:
                success &= check_fun_declaration(current);
                break;
            default:
                semantic_error(current->line_number, "Tipo de declaração inválido");
                success = 0;
        }
        current = current->next;
    }
    
    return success;
}

/**
 * Verifica uma declaração de variável
 */
int check_var_declaration(ASTNode *var_decl) {
    if (!var_decl || !global_context) return 0;
    
    const char *name = var_decl->data.var_decl.name;
    DataType type = var_decl->data.var_decl.type;
    int line = var_decl->line_number;
    
    /* Verifica se o tipo é válido */
    if (type == TYPE_VOID) {
        semantic_error(line, "Variável '%s' não pode ter tipo void", name);
        return 0;
    }
    
    /* Insere na tabela de símbolos */
    if (!insert_symbol(global_context->symbol_table, name, type, SYMBOL_VARIABLE, line)) {
        return 0;
    }
    
    printf(">>> Variável '%s' declarada com tipo %s\n", name, type_to_string(type));
    return 1;
}

/**
 * Verifica uma declaração de função
 */
int check_fun_declaration(ASTNode *fun_decl) {
    if (!fun_decl || !global_context) return 0;
    
    const char *name = fun_decl->data.fun_decl.name;
    DataType return_type = fun_decl->data.fun_decl.return_type;
    int line = fun_decl->line_number;
    
    /* Insere função na tabela de símbolos */
    if (!insert_symbol(global_context->symbol_table, name, return_type, SYMBOL_FUNCTION, line)) {
        return 0;
    }
    
    printf(">>> Função '%s' declarada com tipo de retorno %s\n", name, type_to_string(return_type));
    
    /* Entra no escopo da função */
    enter_scope(global_context->symbol_table);
    global_context->in_function = 1;
    global_context->current_function_return_type = return_type;
    
    /* Verifica parâmetros */
    int success = 1;
    ASTNode *param = fun_decl->data.fun_decl.params;
    while (param) {
        if (param->node_type == NODE_PARAM) {
            success &= insert_symbol(global_context->symbol_table, 
                                   param->data.var_decl.name,
                                   param->data.var_decl.type,
                                   SYMBOL_PARAMETER,
                                   param->line_number);
        }
        param = param->next;
    }
    
    /* Verifica corpo da função */
    if (fun_decl->data.fun_decl.body) {
        success &= check_compound_statement(fun_decl->data.fun_decl.body);
    }
    
    /* Sai do escopo da função */
    exit_scope(global_context->symbol_table);
    global_context->in_function = 0;
    global_context->current_function_return_type = TYPE_VOID;
    
    return success;
}

/**
 * Verifica um comando composto
 */
int check_compound_statement(ASTNode *compound) {
    if (!compound) return 1;
    
    enter_scope(global_context->symbol_table);
    
    int success = 1;
    ASTNode *current = compound;
    
    while (current) {
        success &= check_statement(current);
        current = current->next;
    }
    
    exit_scope(global_context->symbol_table);
    return success;
}

/**
 * Verifica um comando
 */
int check_statement(ASTNode *stmt) {
    if (!stmt) return 1;
    
    switch (stmt->node_type) {
        case NODE_VAR_DECLARATION:
            return check_var_declaration(stmt);
            
        case NODE_COMPOUND_STMT:
            return check_compound_statement(stmt);
            
        case NODE_EXPRESSION_STMT:
            if (stmt->data.return_stmt.expression) {
                ExpressionNode *expr = check_expression(stmt->data.return_stmt.expression);
                if (expr) {
                    free(expr);
                    return 1;
                }
            }
            return 1;
            
        case NODE_SELECTION_STMT:
            return check_selection_statement(stmt);
            
        case NODE_ITERATION_STMT:
            return check_iteration_statement(stmt);
            
        case NODE_RETURN_STMT:
            return check_return_statement(stmt);
            
        case NODE_ASSIGN:
            return check_assignment(stmt);
            
        default:
            semantic_error(stmt->line_number, "Tipo de comando desconhecido");
            return 0;
    }
}

/**
 * Verifica uma expressão
 */
ExpressionNode* check_expression(ASTNode *expr) {
    if (!expr) return NULL;
    
    ExpressionNode *result = (ExpressionNode*)malloc(sizeof(ExpressionNode));
    if (!result) return NULL;
    
    result->addr = NULL;
    result->type = TYPE_ERROR;
    result->is_lvalue = 0;
    
    switch (expr->node_type) {
        case NODE_IDENTIFIER: {
            SymbolEntry *symbol = lookup_symbol(global_context->symbol_table, expr->data.identifier);
            if (!symbol) {
                semantic_error(expr->line_number, "Identificador '%s' não declarado", expr->data.identifier);
                free(result);
                return NULL;
            }
            
            result->type = symbol->type;
            result->is_lvalue = (symbol->category == SYMBOL_VARIABLE);
            result->addr = create_var_address(symbol->name);
            break;
        }
        
        case NODE_CONSTANT:
            result->type = expr->data.constant.type;
            result->is_lvalue = 0;
            
            switch (expr->data.constant.type) {
                case TYPE_INT:
                    result->addr = create_int_const_address(expr->data.constant.value.int_value);
                    break;
                case TYPE_FLOAT:
                    result->addr = create_float_const_address(expr->data.constant.value.float_value);
                    break;
                case TYPE_CHAR:
                    result->addr = create_char_const_address(expr->data.constant.value.char_value);
                    break;
                default:
                    semantic_error(expr->line_number, "Tipo de constante inválido");
                    free(result);
                    return NULL;
            }
            break;
            
        case NODE_BINARY_OP: {
            ExpressionNode *left = check_expression(expr->data.binary_op.left);
            ExpressionNode *right = check_expression(expr->data.binary_op.right);
            
            if (!left || !right) {
                if (left) free(left);
                if (right) free(right);
                free(result);
                return NULL;
            }
            
            /* Verifica compatibilidade de tipos */
            DataType result_type = get_binary_result_type(left->type, right->type, expr->data.binary_op.operator);
            if (result_type == TYPE_ERROR) {
                semantic_error(expr->line_number, "Tipos incompatíveis na operação");
                free(left);
                free(right);
                free(result);
                return NULL;
            }
            
            result->type = result_type;
            result->is_lvalue = 0;
            
            /* Gera código */
            int temp = get_new_temp(global_context->code_list);
            result->addr = create_temp_address(temp);
            emit_binary_op(global_context->code_list, expr->data.binary_op.operator,
                          result->addr, left->addr, right->addr);
            
            free(left);
            free(right);
            break;
        }
        
        case NODE_CALL:
            return check_function_call_expression(expr);
            
        case NODE_ARRAY_ACCESS:
            return check_array_access(expr);
            
        default:
            semantic_error(expr->line_number, "Tipo de expressão desconhecido");
            free(result);
            return NULL;
    }
    
    return result;
}

/**
 * Verifica uma atribuição
 */
int check_assignment(ASTNode *assign) {
    if (!assign || assign->node_type != NODE_ASSIGN) return 0;
    
    ExpressionNode *left = check_expression(assign->data.binary_op.left);
    ExpressionNode *right = check_expression(assign->data.binary_op.right);
    
    if (!left || !right) {
        if (left) free(left);
        if (right) free(right);
        return 0;
    }
    
    /* Verifica se o lado esquerdo é um lvalue */
    if (!left->is_lvalue) {
        semantic_error(assign->line_number, "Lado esquerdo da atribuição deve ser uma variável");
        free(left);
        free(right);
        return 0;
    }
    
    /* Verifica compatibilidade de tipos */
    if (!types_compatible(left->type, right->type)) {
        semantic_error(assign->line_number, "Tipos incompatíveis na atribuição");
        free(left);
        free(right);
        return 0;
    }
    
    /* Gera código */
    emit_assign(global_context->code_list, left->addr, right->addr);
    
    free(left);
    free(right);
    return 1;
}

/**
 * Verifica compatibilidade de tipos
 */
int types_compatible(DataType type1, DataType type2) {
    if (type1 == type2) return 1;
    
    /* Permite conversão implícita entre tipos numéricos */
    if (is_numeric_type(type1) && is_numeric_type(type2)) {
        return 1;
    }
    
    return 0;
}

/**
 * Obtém o tipo resultante de uma operação binária
 */
DataType get_binary_result_type(DataType left, DataType right, Operator op) {
    /* Operadores relacionais sempre retornam int (boolean) */
    if (is_relational_op(op)) {
        if (types_compatible(left, right) && is_numeric_type(left)) {
            return TYPE_INT;
        }
        return TYPE_ERROR;
    }
    
    /* Operadores aritméticos */
    if (is_arithmetic_op(op)) {
        if (!is_numeric_type(left) || !is_numeric_type(right)) {
            return TYPE_ERROR;
        }
        
        /* Se algum é float, o resultado é float */
        if (left == TYPE_FLOAT || right == TYPE_FLOAT) {
            return TYPE_FLOAT;
        }
        
        return TYPE_INT;
    }
    
    return TYPE_ERROR;
}

/**
 * Verifica se é tipo aritmético
 */
int is_arithmetic_type(DataType type) {
    return (type == TYPE_INT || type == TYPE_FLOAT);
}

/**
 * Verifica se é tipo numérico
 */
int is_numeric_type(DataType type) {
    return (type == TYPE_INT || type == TYPE_FLOAT || type == TYPE_CHAR);
}

/**
 * Converte token para tipo de dados
 */
DataType token_to_data_type(int token) {
    switch (token) {
        case 257: /* INT_TYPE */ return TYPE_INT;
        case 258: /* FLOAT_TYPE */ return TYPE_FLOAT;
        case 259: /* CHAR_TYPE */ return TYPE_CHAR;
        case 261: /* VOID_TYPE */ return TYPE_VOID;
        default: return TYPE_ERROR;
    }
}

/**
 * Emite erro semântico
 */
void semantic_error(int line, const char *format, ...) {
    if (!global_context) return;
    
    global_context->semantic_errors++;
    
    fprintf(stderr, "(%d) Erro semântico na linha %d: ", 
            global_context->semantic_errors, line);
    
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
}

/**
 * Emite aviso semântico
 */
void semantic_warning(int line, const char *format, ...) {
    fprintf(stderr, "Aviso na linha %d: ", line);
    
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
}

/* Implementações adicionais para comandos específicos */

int check_selection_statement(ASTNode *stmt) {
    if (!stmt || stmt->node_type != NODE_SELECTION_STMT) return 0;
    
    /* Verifica condição */
    ExpressionNode *condition = check_expression(stmt->data.selection.condition);
    if (!condition) return 0;
    
    if (!is_numeric_type(condition->type)) {
        semantic_error(stmt->line_number, "Condição do if deve ser de tipo numérico");
        free(condition);
        return 0;
    }
    
    /* Gera código para if */
    char *else_label = get_new_label(global_context->code_list);
    char *end_label = get_new_label(global_context->code_list);
    
    /* Se condição for falsa, pula para else */
    Address *else_addr = create_label_address(else_label);
    emit_if_goto(global_context->code_list, condition->addr, else_addr);
    
    free(condition);
    
    /* Verifica comando then */
    int success = check_statement(stmt->data.selection.then_stmt);
    
    /* Pula para o fim se houver else */
    if (stmt->data.selection.else_stmt) {
        Address *end_addr = create_label_address(end_label);
        emit_goto(global_context->code_list, end_addr);
    }
    
    /* Label do else */
    emit_label(global_context->code_list, else_addr);
    
    /* Verifica comando else se existir */
    if (stmt->data.selection.else_stmt) {
        success &= check_statement(stmt->data.selection.else_stmt);
        Address *end_addr = create_label_address(end_label);
        emit_label(global_context->code_list, end_addr);
        free(end_addr);
    }
    
    free(else_addr);
    free(else_label);
    if (stmt->data.selection.else_stmt) {
        free(end_label);
    }
    
    return success;
}

int check_iteration_statement(ASTNode *stmt) {
    if (!stmt || stmt->node_type != NODE_ITERATION_STMT) return 0;
    
    char *loop_label = get_new_label(global_context->code_list);
    char *end_label = get_new_label(global_context->code_list);
    
    /* Label do início do loop */
    Address *loop_addr = create_label_address(loop_label);
    emit_label(global_context->code_list, loop_addr);
    
    /* Verifica condição */
    ExpressionNode *condition = check_expression(stmt->data.iteration.condition);
    if (!condition) {
        free(loop_addr);
        free(loop_label);
        free(end_label);
        return 0;
    }
    
    if (!is_numeric_type(condition->type)) {
        semantic_error(stmt->line_number, "Condição do while deve ser de tipo numérico");
        free(condition);
        free(loop_addr);
        free(loop_label);
        free(end_label);
        return 0;
    }
    
    /* Se condição for falsa, sai do loop */
    Address *end_addr = create_label_address(end_label);
    emit_if_goto(global_context->code_list, condition->addr, end_addr);
    
    free(condition);
    
    /* Verifica corpo do loop */
    int success = check_statement(stmt->data.iteration.body);
    
    /* Volta para o início do loop */
    emit_goto(global_context->code_list, loop_addr);
    
    /* Label do fim do loop */
    emit_label(global_context->code_list, end_addr);
    
    free(loop_addr);
    free(end_addr);
    free(loop_label);
    free(end_label);
    
    return success;
}

int check_return_statement(ASTNode *stmt) {
    if (!stmt || stmt->node_type != NODE_RETURN_STMT) return 0;
    
    if (!global_context->in_function) {
        semantic_error(stmt->line_number, "Return fora de função");
        return 0;
    }
    
    if (stmt->data.return_stmt.expression) {
        ExpressionNode *expr = check_expression(stmt->data.return_stmt.expression);
        if (!expr) return 0;
        
        if (!types_compatible(expr->type, global_context->current_function_return_type)) {
            semantic_error(stmt->line_number, "Tipo de retorno incompatível");
            free(expr);
            return 0;
        }
        
        emit_return(global_context->code_list, expr->addr);
        free(expr);
    } else {
        if (global_context->current_function_return_type != TYPE_VOID) {
            semantic_error(stmt->line_number, "Função deve retornar um valor");
            return 0;
        }
        
        emit_return(global_context->code_list, NULL);
    }
    
    return 1;
}

/* Implementações das funções de criação de nós da AST */

/**
 * Cria um nó de programa
 */
ASTNode* create_program_node(ASTNode *declarations) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) return NULL;
    
    node->node_type = NODE_PROGRAM;
    node->data_type = TYPE_VOID;
    node->line_number = 1;
    node->next = declarations;
    node->code_addr = NULL;
    
    return node;
}

/**
 * Cria um nó de declaração de variável
 */
ASTNode* create_var_declaration_node(const char *name, DataType type, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) return NULL;
    
    node->node_type = NODE_VAR_DECLARATION;
    node->data_type = type;
    node->line_number = line;
    node->data.var_decl.name = strdup(name);
    node->data.var_decl.type = type;
    node->data.var_decl.array_size = 0;
    node->next = NULL;
    node->code_addr = NULL;
    
    return node;
}

/**
 * Cria um nó de declaração de função
 */
ASTNode* create_fun_declaration_node(const char *name, DataType return_type, 
                                   ASTNode *params, ASTNode *body, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) return NULL;
    
    node->node_type = NODE_FUN_DECLARATION;
    node->data_type = return_type;
    node->line_number = line;
    node->data.fun_decl.name = strdup(name);
    node->data.fun_decl.return_type = return_type;
    node->data.fun_decl.params = params;
    node->data.fun_decl.body = body;
    node->next = NULL;
    node->code_addr = NULL;
    
    return node;
}

/**
 * Cria um nó de operação binária
 */
ASTNode* create_binary_op_node(Operator op, ASTNode *left, ASTNode *right, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) return NULL;
    
    node->node_type = NODE_BINARY_OP;
    node->data_type = TYPE_ERROR; /* Será determinado durante análise semântica */
    node->line_number = line;
    node->data.binary_op.operator = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->next = NULL;
    node->code_addr = NULL;
    
    return node;
}

/**
 * Cria um nó de identificador
 */
ASTNode* create_identifier_node(const char *name, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) return NULL;
    
    node->node_type = NODE_IDENTIFIER;
    node->data_type = TYPE_ERROR; /* Será determinado durante análise semântica */
    node->line_number = line;
    node->data.identifier = strdup(name);
    node->next = NULL;
    node->code_addr = NULL;
    
    return node;
}

/**
 * Cria um nó de constante
 */
ASTNode* create_constant_node(DataType type, void *value, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) return NULL;
    
    node->node_type = NODE_CONSTANT;
    node->data_type = type;
    node->line_number = line;
    node->data.constant.type = type;
    
    switch (type) {
        case TYPE_INT:
            node->data.constant.value.int_value = *(int*)value;
            break;
        case TYPE_FLOAT:
            node->data.constant.value.float_value = *(float*)value;
            break;
        case TYPE_CHAR:
            node->data.constant.value.char_value = *(char*)value;
            break;
        default:
            free(node);
            return NULL;
    }
    
    node->next = NULL;
    node->code_addr = NULL;
    
    return node;
}

/**
 * Cria um nó de chamada de função
 */
ASTNode* create_call_node(const char *name, ASTNode *args, int line) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) return NULL;
    
    node->node_type = NODE_CALL;
    node->data_type = TYPE_ERROR; /* Será determinado durante análise semântica */
    node->line_number = line;
    node->data.call.name = strdup(name);
    node->data.call.args = args;
    node->next = NULL;
    node->code_addr = NULL;
    
    return node;
}

/**
 * Libera memória de um nó da AST
 */
void free_ast_node(ASTNode *node) {
    if (!node) return;
    
    switch (node->node_type) {
        case NODE_VAR_DECLARATION:
            free(node->data.var_decl.name);
            break;
        case NODE_FUN_DECLARATION:
            free(node->data.fun_decl.name);
            free_ast_node(node->data.fun_decl.params);
            free_ast_node(node->data.fun_decl.body);
            break;
        case NODE_BINARY_OP:
            free_ast_node(node->data.binary_op.left);
            free_ast_node(node->data.binary_op.right);
            break;
        case NODE_IDENTIFIER:
            free(node->data.identifier);
            break;
        case NODE_CALL:
            free(node->data.call.name);
            free_ast_node(node->data.call.args);
            break;
        default:
            break;
    }
    
    if (node->code_addr) {
        free_address(node->code_addr);
    }
    
    free_ast_node(node->next);
    free(node);
}

/**
 * Imprime a AST (para debug)
 */
void print_ast(ASTNode *node, int indent) {
    if (!node) return;
    
    for (int i = 0; i < indent; i++) printf("  ");
    
    switch (node->node_type) {
        case NODE_PROGRAM:
            printf("PROGRAM\n");
            break;
        case NODE_VAR_DECLARATION:
            printf("VAR_DECL: %s (%s)\n", node->data.var_decl.name, 
                   type_to_string(node->data.var_decl.type));
            break;
        case NODE_FUN_DECLARATION:
            printf("FUN_DECL: %s -> %s\n", node->data.fun_decl.name, 
                   type_to_string(node->data.fun_decl.return_type));
            print_ast(node->data.fun_decl.params, indent + 1);
            print_ast(node->data.fun_decl.body, indent + 1);
            break;
        case NODE_IDENTIFIER:
            printf("ID: %s\n", node->data.identifier);
            break;
        case NODE_CONSTANT:
            printf("CONST: ");
            switch (node->data.constant.type) {
                case TYPE_INT:
                    printf("%d (int)\n", node->data.constant.value.int_value);
                    break;
                case TYPE_FLOAT:
                    printf("%.2f (float)\n", node->data.constant.value.float_value);
                    break;
                case TYPE_CHAR:
                    printf("'%c' (char)\n", node->data.constant.value.char_value);
                    break;
                default:
                    printf("unknown\n");
            }
            break;
        case NODE_BINARY_OP:
            printf("BINARY_OP: %s\n", operator_to_string(node->data.binary_op.operator));
            print_ast(node->data.binary_op.left, indent + 1);
            print_ast(node->data.binary_op.right, indent + 1);
            break;
        case NODE_CALL:
            printf("CALL: %s\n", node->data.call.name);
            print_ast(node->data.call.args, indent + 1);
            break;
        default:
            printf("UNKNOWN_NODE\n");
    }
    
    print_ast(node->next, indent);
}

/**
 * Verifica uma chamada de função como expressão
 */
ExpressionNode* check_function_call_expression(ASTNode *call) {
    if (!call || call->node_type != NODE_CALL) return NULL;
    
    const char *func_name = call->data.call.name;
    SymbolEntry *func_symbol = lookup_symbol(global_context->symbol_table, func_name);
    
    if (!func_symbol) {
        semantic_error(call->line_number, "Função '%s' não declarada", func_name);
        return NULL;
    }
    
    if (func_symbol->category != SYMBOL_FUNCTION) {
        semantic_error(call->line_number, "'%s' não é uma função", func_name);
        return NULL;
    }
    
    ExpressionNode *result = (ExpressionNode*)malloc(sizeof(ExpressionNode));
    if (!result) return NULL;
    
    result->type = func_symbol->type;
    result->is_lvalue = 0;
    
    /* Gera código para chamada de função */
    int temp = get_new_temp(global_context->code_list);
    result->addr = create_temp_address(temp);
    
    /* Emite parâmetros */
    ASTNode *arg = call->data.call.args;
    int param_count = 0;
    while (arg) {
        ExpressionNode *arg_expr = check_expression(arg);
        if (arg_expr) {
            emit_param(global_context->code_list, arg_expr->addr);
            param_count++;
            free(arg_expr);
        }
        arg = arg->next;
    }
    
    /* Emite chamada */
    Address *func_addr = create_var_address(func_name);
    emit_call(global_context->code_list, result->addr, func_addr, param_count);
    free(func_addr);
    
    return result;
}

/**
 * Verifica acesso a array
 */
ExpressionNode* check_array_access(ASTNode *array_access) {
    if (!array_access) return NULL;
    
    /* Implementação simplificada - só retorna um resultado básico */
    ExpressionNode *result = (ExpressionNode*)malloc(sizeof(ExpressionNode));
    if (!result) return NULL;
    
    result->type = TYPE_INT; /* Assume int por enquanto */
    result->is_lvalue = 1;
    
    int temp = get_new_temp(global_context->code_list);
    result->addr = create_temp_address(temp);
    
    return result;
}
