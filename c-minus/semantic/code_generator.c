#include "code_generator.h"
#include "utils.h"
#define _GNU_SOURCE
#include <string.h>

/* Lista de instruções global */
static InstructionList *global_code = NULL;

/**
 * Cria uma nova lista de instruções
 */
InstructionList* create_instruction_list(void) {
    InstructionList *list = (InstructionList*)malloc(sizeof(InstructionList));
    if (!list) {
        fprintf(stderr, "Erro: Não foi possível alocar memória para lista de instruções\n");
        return NULL;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->temp_counter = 0;
    list->label_counter = 0;
    
    return list;
}

/**
 * Destrói a lista de instruções
 */
void destroy_instruction_list(InstructionList *list) {
    if (!list) return;
    
    Instruction *current = list->head;
    while (current) {
        Instruction *temp = current;
        current = current->next;
        free_instruction(temp);
    }
    
    free(list);
}

/**
 * Cria um endereço para variável temporária
 */
Address* create_temp_address(int temp_num) {
    Address *addr = (Address*)malloc(sizeof(Address));
    if (!addr) return NULL;
    
    addr->type = ADDR_TEMP;
    addr->addr.temp_num = temp_num;
    return addr;
}

/**
 * Cria um endereço para variável
 */
Address* create_var_address(const char *var_name) {
    Address *addr = (Address*)malloc(sizeof(Address));
    if (!addr) return NULL;
    
    addr->type = ADDR_VAR;
    addr->addr.var_name = strdup(var_name);
    return addr;
}

/**
 * Cria um endereço para constante inteira
 */
Address* create_int_const_address(int value) {
    Address *addr = (Address*)malloc(sizeof(Address));
    if (!addr) return NULL;
    
    addr->type = ADDR_CONST;
    addr->addr.constant.type = TYPE_INT;
    addr->addr.constant.value.int_val = value;
    return addr;
}

/**
 * Cria um endereço para constante real
 */
Address* create_float_const_address(float value) {
    Address *addr = (Address*)malloc(sizeof(Address));
    if (!addr) return NULL;
    
    addr->type = ADDR_CONST;
    addr->addr.constant.type = TYPE_FLOAT;
    addr->addr.constant.value.float_val = value;
    return addr;
}

/**
 * Cria um endereço para constante de caractere
 */
Address* create_char_const_address(char value) {
    Address *addr = (Address*)malloc(sizeof(Address));
    if (!addr) return NULL;
    
    addr->type = ADDR_CONST;
    addr->addr.constant.type = TYPE_CHAR;
    addr->addr.constant.value.char_val = value;
    return addr;
}

/**
 * Cria um endereço para label
 */
Address* create_label_address(const char *label_name) {
    Address *addr = (Address*)malloc(sizeof(Address));
    if (!addr) return NULL;
    
    addr->type = ADDR_LABEL;
    addr->addr.label_name = strdup(label_name);
    return addr;
}

/**
 * Cria uma nova instrução
 */
Instruction* create_instruction(Operator op, Address *result, Address *arg1, Address *arg2) {
    Instruction *instr = (Instruction*)malloc(sizeof(Instruction));
    if (!instr) return NULL;
    
    instr->op = op;
    instr->result = result;
    instr->arg1 = arg1;
    instr->arg2 = arg2;
    instr->next = NULL;
    
    return instr;
}

/**
 * Adiciona uma instrução à lista
 */
void add_instruction(InstructionList *list, Instruction *instr) {
    if (!list || !instr) return;
    
    if (!list->head) {
        list->head = list->tail = instr;
    } else {
        list->tail->next = instr;
        list->tail = instr;
    }
}

/**
 * Gera um novo número de temporária
 */
int get_new_temp(InstructionList *list) {
    if (!list) return -1;
    return list->temp_counter++;
}

/**
 * Gera um novo label
 */
char* get_new_label(InstructionList *list) {
    if (!list) return NULL;
    
    char *label = (char*)malloc(16);
    if (!label) return NULL;
    
    sprintf(label, "L%d", list->label_counter++);
    return label;
}

/**
 * Emite uma instrução de atribuição
 */
void emit_assign(InstructionList *list, Address *dest, Address *src) {
    Instruction *instr = create_instruction(OP_ASSIGN, dest, src, NULL);
    add_instruction(list, instr);
}

/**
 * Emite uma instrução de operação binária
 */
void emit_binary_op(InstructionList *list, Operator op, Address *result, Address *arg1, Address *arg2) {
    Instruction *instr = create_instruction(op, result, arg1, arg2);
    add_instruction(list, instr);
}

/**
 * Emite uma instrução goto
 */
void emit_goto(InstructionList *list, Address *label) {
    Instruction *instr = create_instruction(OP_GOTO, NULL, label, NULL);
    add_instruction(list, instr);
}

/**
 * Emite uma instrução if-goto
 */
void emit_if_goto(InstructionList *list, Address *condition, Address *label) {
    Instruction *instr = create_instruction(OP_IF_GOTO, NULL, condition, label);
    add_instruction(list, instr);
}

/**
 * Emite um label
 */
void emit_label(InstructionList *list, Address *label) {
    Instruction *instr = create_instruction(OP_LABEL, label, NULL, NULL);
    add_instruction(list, instr);
}

/**
 * Emite uma chamada de função
 */
void emit_call(InstructionList *list, Address *result, Address *function, int param_count) {
    Instruction *instr = create_instruction(OP_CALL, result, function, create_int_const_address(param_count));
    add_instruction(list, instr);
}

/**
 * Emite um parâmetro
 */
void emit_param(InstructionList *list, Address *param) {
    Instruction *instr = create_instruction(OP_PARAM, NULL, param, NULL);
    add_instruction(list, instr);
}

/**
 * Emite um return
 */
void emit_return(InstructionList *list, Address *value) {
    Instruction *instr = create_instruction(OP_RETURN, NULL, value, NULL);
    add_instruction(list, instr);
}

/**
 * Imprime a lista de instruções
 */
void print_instruction_list(InstructionList *list) {
    if (!list) return;
    
    printf("\n=== CÓDIGO DE TRÊS ENDEREÇOS ===\n");
    
    Instruction *current = list->head;
    int line_num = 1;
    
    while (current) {
        printf("%3d: ", line_num++);
        print_instruction(current);
        printf("\n");
        current = current->next;
    }
    
    printf("================================\n\n");
}

/**
 * Imprime uma instrução
 */
void print_instruction(Instruction *instr) {
    if (!instr) return;
    
    switch (instr->op) {
        case OP_ASSIGN:
            print_address(instr->result);
            printf(" := ");
            print_address(instr->arg1);
            break;
            
        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV:
        case OP_LT:
        case OP_LE:
        case OP_GT:
        case OP_GE:
        case OP_EQ:
        case OP_NE:
            print_address(instr->result);
            printf(" := ");
            print_address(instr->arg1);
            printf(" %s ", operator_to_string(instr->op));
            print_address(instr->arg2);
            break;
            
        case OP_GOTO:
            printf("goto ");
            print_address(instr->arg1);
            break;
            
        case OP_IF_GOTO:
            printf("if ");
            print_address(instr->arg1);
            printf(" goto ");
            print_address(instr->arg2);
            break;
            
        case OP_LABEL:
            print_address(instr->result);
            printf(":");
            break;
            
        case OP_CALL:
            if (instr->result) {
                print_address(instr->result);
                printf(" := ");
            }
            printf("call ");
            print_address(instr->arg1);
            break;
            
        case OP_PARAM:
            printf("param ");
            print_address(instr->arg1);
            break;
            
        case OP_RETURN:
            printf("return");
            if (instr->arg1) {
                printf(" ");
                print_address(instr->arg1);
            }
            break;
            
        case OP_ARRAY_ACCESS:
            print_address(instr->result);
            printf(" := ");
            print_address(instr->arg1);
            printf("[");
            print_address(instr->arg2);
            printf("]");
            break;
            
        case OP_ARRAY_STORE:
            print_address(instr->arg1);
            printf("[");
            print_address(instr->arg2);
            printf("] := ");
            print_address(instr->result);
            break;
            
        default:
            printf("instrução desconhecida");
            break;
    }
}

/**
 * Imprime um endereço
 */
void print_address(Address *addr) {
    if (!addr) {
        printf("NULL");
        return;
    }
    
    switch (addr->type) {
        case ADDR_TEMP:
            printf("t%d", addr->addr.temp_num);
            break;
            
        case ADDR_VAR:
            printf("%s", addr->addr.var_name);
            break;
            
        case ADDR_CONST:
            switch (addr->addr.constant.type) {
                case TYPE_INT:
                    printf("%d", addr->addr.constant.value.int_val);
                    break;
                case TYPE_FLOAT:
                    printf("%.2f", addr->addr.constant.value.float_val);
                    break;
                case TYPE_CHAR:
                    printf("'%c'", addr->addr.constant.value.char_val);
                    break;
                default:
                    printf("const");
                    break;
            }
            break;
            
        case ADDR_LABEL:
            printf("%s", addr->addr.label_name);
            break;
            
        default:
            printf("addr_unknown");
            break;
    }
}

/**
 * Converte operador para string
 */
const char* operator_to_string(Operator op) {
    switch (op) {
        case OP_ADD: return "+";
        case OP_SUB: return "-";
        case OP_MUL: return "*";
        case OP_DIV: return "/";
        case OP_LT: return "<";
        case OP_LE: return "<=";
        case OP_GT: return ">";
        case OP_GE: return ">=";
        case OP_EQ: return "==";
        case OP_NE: return "!=";
        default: return "?";
    }
}

/**
 * Libera memória de um endereço
 */
void free_address(Address *addr) {
    if (!addr) return;
    
    if (addr->type == ADDR_VAR && addr->addr.var_name) {
        free(addr->addr.var_name);
    }
    if (addr->type == ADDR_LABEL && addr->addr.label_name) {
        free(addr->addr.label_name);
    }
    
    free(addr);
}

/**
 * Libera memória de uma instrução
 */
void free_instruction(Instruction *instr) {
    if (!instr) return;
    
    free_address(instr->result);
    free_address(instr->arg1);
    free_address(instr->arg2);
    free(instr);
}

/**
 * Copia um endereço
 */
Address* copy_address(Address *addr) {
    if (!addr) return NULL;
    
    switch (addr->type) {
        case ADDR_TEMP:
            return create_temp_address(addr->addr.temp_num);
            
        case ADDR_VAR:
            return create_var_address(addr->addr.var_name);
            
        case ADDR_CONST:
            switch (addr->addr.constant.type) {
                case TYPE_INT:
                    return create_int_const_address(addr->addr.constant.value.int_val);
                case TYPE_FLOAT:
                    return create_float_const_address(addr->addr.constant.value.float_val);
                case TYPE_CHAR:
                    return create_char_const_address(addr->addr.constant.value.char_val);
                default:
                    return NULL;
            }
            
        case ADDR_LABEL:
            return create_label_address(addr->addr.label_name);
            
        default:
            return NULL;
    }
}

/**
 * Verifica se é operador aritmético
 */
int is_arithmetic_op(Operator op) {
    return (op == OP_ADD || op == OP_SUB || op == OP_MUL || op == OP_DIV);
}

/**
 * Verifica se é operador relacional
 */
int is_relational_op(Operator op) {
    return (op == OP_LT || op == OP_LE || op == OP_GT || op == OP_GE || op == OP_EQ || op == OP_NE);
}

/**
 * Inicializa o gerador de código
 */
void init_code_generator(void) {
    global_code = create_instruction_list();
    if (!global_code) {
        fprintf(stderr, "Erro fatal: Não foi possível criar lista de instruções\n");
        exit(1);
    }
}

/**
 * Finaliza o gerador de código
 */
void finalize_code_generator(void) {
    if (global_code) {
        print_instruction_list(global_code);
        destroy_instruction_list(global_code);
        global_code = NULL;
    }
}

/**
 * Obtém a lista de instruções global
 */
InstructionList* get_instruction_list(void) {
    return global_code;
}
