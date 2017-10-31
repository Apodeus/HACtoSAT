#include <stdio.h>
#include <stdlib.h>
#include "clause.h"

struct t_formula {
  int max_clause;
  int nb_clause;
  Clause* clauses;
};

typedef struct t_formula *SAT_Formula;

SAT_Formula create_formula();
void destroyFormula(SAT_Formula formula);
void add(SAT_Formula f, Clause c);
void showFormula(SAT_Formula f);
