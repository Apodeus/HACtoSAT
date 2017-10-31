#include <stdio.h>
#include <stdlib.h>

enum t_condition{
  DISJONCTIVE = 0, CONJONCTIVE
};

typedef enum t_Condition Condition;

typedef struct t_clause *Clause;

struct t_clause {
  int cond;
  int length;
  int* vars;
};

Clause create_clause(int n, int cond);
void destroyClause(Clause c);

void showClause(Clause c);
