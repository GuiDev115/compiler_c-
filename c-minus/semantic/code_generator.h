#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

/* Estrutura para representar um endereço no código de três endereços */
typedef struct Address {
    enum {
        ADDR_TEMP,      /* Variável temporária */
        ADDR_VAR,       /* Variável */
        ADDR_CONST,     /* Constante */
        ADDR_LABEL      /* Label */
    } type;
    
    union {
        int temp_num;     /* Número da temporária */
        char *var_name;   /* Nome da variável */
        struct {
            DataType type;
            union {
                int int_val;
                float float_val;
                char char_val;
            } value;
        } constant;
        char *label_name; /* Nome do label */
    } addr;
} Address;

/* Operadores para código de três endereços */
typedef enum {
    OP_ASSIGN,      /* = */
    OP_ADD,         /* + */
    OP_SUB,         /* - */
    OP_MUL,         /* * */
    OP_DIV,         /* / */
    OP_LT,          /* < */
    OP_LE,          /* <= */
    OP_GT,          /* > */
    OP_GE,          /* >= */
    OP_EQ,          /* == */
    OP_NE,          /* != */
    OP_GOTO,        /* goto */
    OP_IF_GOTO,     /* if goto */
    OP_CALL,        /* call */
    OP_RETURN,      /* return */
    OP_PARAM,       /* param */
    OP_ARRAY_ACCESS, /* array access */
    OP_ARRAY_STORE,  /* array store */
    OP_LABEL        /* label */
} Operator;

/* Instrução de código de três endereços */
typedef struct Instruction {
    Operator op;
    Address *result;
    Address *arg1;
    Address *arg2;
    struct Instruction *next;
} Instruction;

/* Lista de instruções */
typedef struct InstructionList {
    Instruction *head;
    Instruction *tail;
    int temp_counter;
    int label_counter;
} InstructionList;

/* Estrutura para expressões com atributos */
typedef struct ExpressionNode {
    Address *addr;      /* Endereço onde o resultado é armazenado */
    DataType type;      /* Tipo da expressão */
    int is_lvalue;      /* Se pode ser usado como lvalue */
} ExpressionNode;

/* Protótipos das funções */
InstructionList* create_instruction_list(void);
void destroy_instruction_list(InstructionList *list);

/* Criação de endereços */
Address* create_temp_address(int temp_num);
Address* create_var_address(const char *var_name);
Address* create_int_const_address(int value);
Address* create_float_const_address(float value);
Address* create_char_const_address(char value);
Address* create_label_address(const char *label_name);

/* Criação de instruções */
Instruction* create_instruction(Operator op, Address *result, Address *arg1, Address *arg2);
void add_instruction(InstructionList *list, Instruction *instr);

/* Geração de temporárias e labels */
int get_new_temp(InstructionList *list);
char* get_new_label(InstructionList *list);

/* Emissão de código */
void emit_assign(InstructionList *list, Address *dest, Address *src);
void emit_binary_op(InstructionList *list, Operator op, Address *result, Address *arg1, Address *arg2);
void emit_goto(InstructionList *list, Address *label);
void emit_if_goto(InstructionList *list, Address *condition, Address *label);
void emit_label(InstructionList *list, Address *label);
void emit_call(InstructionList *list, Address *result, Address *function, int param_count);
void emit_param(InstructionList *list, Address *param);
void emit_return(InstructionList *list, Address *value);

/* Impressão do código */
void print_instruction_list(InstructionList *list);
void print_instruction(Instruction *instr);
void print_address(Address *addr);
const char* operator_to_string(Operator op);

/* Liberação de memória */
void free_address(Address *addr);
void free_instruction(Instruction *instr);

/* Utilitários */
Address* copy_address(Address *addr);
int is_arithmetic_op(Operator op);
int is_relational_op(Operator op);

#endif /* CODE_GENERATOR_H */
