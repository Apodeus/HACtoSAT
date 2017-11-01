#include "SAT.h"
#include "test.h"


void showVars(int** vars, int w, int h){
  for(int i = 0; i < w; i++){
    for(int j = 0; j < h; j++){
      printf("%02d ", vars[i][j]);
    }
    printf("\n");
  }
}

void destroyVars(int** vars){
  for(int i = 0; i < orderG(); i++){
    free(vars[i]);
  }
  free(vars);
}

void number1(SAT_Formula f, int** vars, int k){
  int nbSommet = orderG();
  for(int sommet = 0; sommet < nbSommet; sommet++){//begin orange Part
    Clause c = create_clause(k, DISJONCTIVE);//begin Yellow Part
    int h = 0;
    for(int i = 0; i < c->length; i++){
        c->vars[i] = vars[sommet][h];
        h++;
    }
    add(f, c);
    //end yellow part
    //begin green Part
    for(int i = 0; i < k - 1; i++){
      for(int j = i + 1; j < k; j++){
        Clause c2 = create_clause(2, DISJONCTIVE);
        c2->vars[0] = -vars[sommet][i];
        c2->vars[1] = -vars[sommet][j];
        add(f, c2);
      }
    }//end green Part
  }//end Orange Part
}


void number2(SAT_Formula f, int** vars, int k){
  int nbSommet = orderG();
  Clause c1 = create_clause(nbSommet, DISJONCTIVE);
  for(int i = 0; i < nbSommet; i++){
    c1->vars[i] = vars[i][0];
  }
  add(f, c1);
  //
  //n² +n / 2
  int nb = ((nbSommet * nbSommet) + nbSommet) / 2;
  //printf("\n NB CLAUSES NUMBER 2 : %d\n\n", nb);
  for(int i = 0; i < nbSommet - 1; i++){
    for(int j = i + 1; j < nbSommet; j++){
      Clause c = create_clause(2, DISJONCTIVE);
      c->vars[0] = -vars[i][0];
      c->vars[1] = -vars[j][0];
      add(f, c);
    }
  }
}

void number3(SAT_Formula f, int** vars, int k){
  Clause c = create_clause(orderG(), DISJONCTIVE);
  for(int i = 0; i < orderG(); i++){
    c->vars[i] = vars[i][k-1];
  }
  add(f, c);
  //return c;
}

int nbVoisin(int u){
  int n = 0;
  for(int i = 0; i < orderG(); i++){
    if(are_adjacent(u, i))
      n++;
  }
  return n;
}

void number4(SAT_Formula f, int** vars, int k){
  int nbSommet = orderG();
  for(int sommet = 0; sommet < nbSommet; sommet++){
    for(int i = 1; i < k; i++){
      Clause c = create_clause(nbVoisin(sommet) + 1, DISJONCTIVE);
      c->vars[0] = -vars[sommet][i];
      int cursor = 1;
      for(int voisin = 0; voisin < nbSommet; voisin++){
        if(are_adjacent(sommet, voisin)){
          c->vars[cursor] = vars[voisin][i - 1];
          cursor++;
        }
      }
      add(f, c);

    }
  }
}

int main(int argc, char* argv[]){
  //Init vars

  int nbSommet = orderG();
  int k = 1;
  if(argc > 1)
    k = atoi(argv[1]);
  k++;

  int** vars = (int**) malloc(sizeof(int*) * nbSommet);// All vars we need Xu,i, with u€V and i€[0;k]
  SAT_Formula formula = create_formula();

  int n = 1;
  for(int i = 0; i < nbSommet; i++){
    vars[i] = malloc(sizeof(int) * k);
    for(int j = 0; j < k; j++){
      vars[i][j] = n;
      n++;
    }
  }


  //showVars(vars, nbSommet, k);
  //printf("\n\n");

  number1(formula, vars, k);
  number2(formula, vars, k);
  number3(formula, vars, k);
  number4(formula, vars, k);
  /*
  1-
  */
  showFormula(formula, nbSommet * k);
  destroyFormula(formula);
  destroyVars(vars);
  return 0;
}
