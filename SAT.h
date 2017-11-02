#include <stdio.h>
#include <stdlib.h>
#include "clause.h"

struct t_formula {
  int max_clause;
  int nb_clause;
  Clause* clauses;
};

typedef struct t_formula *SAT_Formula;

//Return a SAT struct
SAT_Formula create_formula();

//Free all allocation in the SAT formula struct
void destroyFormula(SAT_Formula formula);

//Add the clause c to the SAT formula
//If the array of clause of the SAT formula is full, it allocates a new array twice larger.
void add(SAT_Formula f, Clause c);

//Display the SAT_Formula with the Glucose Format
void showFormula(SAT_Formula f, int nbVars);
