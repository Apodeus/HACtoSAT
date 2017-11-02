#include <string.h>
#include "SAT.h"
#include "all.h"
#include "vars.h"
#include "queue.h"


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

void printResultGraph(int nbSommet, int k){

    //init vars and stuff
    char* c = (char*) malloc(sizeof(char) * 255);
    int* r = (int*) malloc(sizeof(int) * nbSommet);

    //adjacent matrix
    int** result = (int**) malloc(sizeof(int*) * nbSommet);
    for (int i = 0; i < nbSommet; i++){
        result[i] = (int*) malloc(sizeof(int) * nbSommet);
        for (int j = 0; j < nbSommet; j++)
            result[i][j] = 0;
    }

    int i = 0;

    //get all the positives values from stdin
    while (c[0] != '0'){
        scanf("%s", c);
        int n = atoi(c);
        if (n > 0){
            r[i] = n;
            i++;
        }
    }

    // for (i = 0; i < nbSommet; i++)
    //     fprintf(stderr, "%d\n", r[i]);

    //translate values from Glucz to vertex identifier + their d(v)
    int* d = (int*) malloc(sizeof(int) * nbSommet);
    int* v = (int*) malloc(sizeof(int) * nbSommet);
    for (i = 0; i < nbSommet; i++){
        d[i] = (r[i] - 1) % (k + 1);
        v[i] = 0;
        //fprintf(stderr, "i = %d, value is %d; computed v = %d, computed d = %d\n", i, r[i], v[i], d[i]);
    }

    int degree = 0; //root
    queue q = newQueue(0);
    int root_i = -1;
    while (q != NULL){
        queue t = q;
        while (t!= NULL){
            // fprintf(stderr, "%d->", t->value);
            t = t->next;
        }
        // if (q != NULL)
        //     fprintf(stderr, "current: v%d\n", q->value);
        for (i = 0; i < nbSommet; i++){
            //fprintf(stderr, "looking for v%d and v%d\n", v[q->value], v[i]);
            if (d[i] == degree){
                if (degree == 0 && root_i == -1)
                    root_i = i;
                addToQueue(q, i);
                //fprintf(stderr, "ADDED (%d): v%d\n",degree, v[i]);
                if (q != NULL && v[i] == 0 && are_adjacent(q->value, i)){
                    fprintf(stderr, "v%d and v%d are adjacent\n", q->value, i);
                    result[i][q->value] = 1;
                    result[q->value][i] = 1;
                    v[i] = 1;
                }
            }
        }

        q = q->next;
        if (q == NULL)
            break;
        //fprintf(stderr, "new loop\n");
        int new_degree = d[q->value] + 1;
        // if (new_degree != degree){
            // fprintf(stderr, "nd = %d; d = %d\n", new_degree, degree);
        // }

        degree = new_degree;
    }

    //display
    printf("Root vertex is v%d\n", root_i);
    for (i = 0; i < nbSommet; i++){
        for (int j = 0; j < nbSommet; j++){
            printf("%d ", result[i][j]);
        }

        printf("\n");
    }
}


int main(int argc, char* argv[]){
  //Init vars

  if (strcmp(argv[1], "-r") && argc == 3){
    printResultGraph(orderG(), atoi(argv[2]));
    return 0;
  } else if(argc != 2){
    return 1;
  }

  int nbSommet = orderG();
  int k;
  k = atoi(argv[1]) + 1;

  int** vars = createVars(nbSommet, k);
  SAT_Formula formula = create_formula();

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
  destroyVars(vars, nbSommet);
  return 0;
}
