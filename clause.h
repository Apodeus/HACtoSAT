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

//Return a Clause struct of length n.
//The integer 'cond' is here to know if the clause is Disjonctiv or Conjonctiv
Clause create_clause(int n, int cond);

//Free all allocation of the clause c
void destroyClause(Clause c);

//Display the vars in the clause c
void showClause(Clause c);
