
#include <stdio.h>
#include <stdlib.h>
#include "SAT.h"

SAT_Formula create_formula(){
  SAT_Formula formula = (SAT_Formula)malloc(sizeof(SAT_Formula));
  formula->max_clause = 2;
  formula->nb_clause = 0;
  formula->clauses = (Clause*)malloc(sizeof(Clause) * formula->max_clause);

  return formula;
}

void destroyFormula(SAT_Formula f){
  for(int i = 0; i < f->nb_clause; i++){
    destroyClause(f->clauses[i]);
  }
  free(f->clauses);
  free(f);
}

void allocate(SAT_Formula f){
  Clause* arr = (Clause*)malloc(sizeof(Clause) * (f->max_clause * 2));
  for(int i = 0; i < f->nb_clause; i++){
    arr[i] = f->clauses[i];
  }
  free(f->clauses);
  f->clauses = arr;
  f->max_clause = f->max_clause * 2;
}

void add(SAT_Formula f, Clause c){

  if(f->nb_clause + 1 >= f->max_clause)
    allocate(f);

  f->clauses[f->nb_clause] = c;
  f->nb_clause++;

}

void showFormula(SAT_Formula f, int nbVars){
  //printf("Showing the SAT formula :\n");
  printf("p cnf %d %d\n", nbVars, f->nb_clause);
  for(int i = 0; i < f->nb_clause; i++){
    showClause(f->clauses[i]);
  }
  printf("\n");
}












//
