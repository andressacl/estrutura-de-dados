#ifndef CPF_H
#define CPF_H

#include "../Util/Util.h"

typedef struct cpflist_st CPF_list;

CPF_list *cpf_create(char *cpf);

void CPF_print(CPF_list *cpf_list);
void CPF_format_print(CPF_list *cpf_list);

boolean maior(CPF_list *cpf1, CPF_list *cpf2);
boolean igual(CPF_list *cpf1, CPF_list *cpf2);

void cpf_delete(CPF_list **cpf_ref);

#endif //CPF_H