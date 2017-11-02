#include <string.h>
#include "SAT.h"
#include "all.h"
#include "vars.h"
#include "queue.h"

//First clause of the Question
void number1(SAT_Formula f, int** vars, int k){
  int nbVertex = orderG();
  for(int vertex = 0; vertex < nbVertex; vertex++){
    Clause c = create_clause(k, DISJONCTIVE);
    int h = 0;
    for(int i = 0; i < c->length; i++){
        c->vars[i] = vars[vertex][h];
        h++;
    }
    add(f, c);
    for(int i = 0; i < k - 1; i++){
      for(int j = i + 1; j < k; j++){
        Clause c2 = create_clause(2, DISJONCTIVE);
        c2->vars[0] = -vars[vertex][i];
        c2->vars[1] = -vars[vertex][j];
        add(f, c2);
      }
    }
  }
}

//Second clause of the Question
void number2(SAT_Formula f, int** vars, int k){
  int nbVertex = orderG();
  Clause c1 = create_clause(nbVertex, DISJONCTIVE);
  for(int i = 0; i < nbVertex; i++){
    c1->vars[i] = vars[i][0];
  }
  add(f, c1);

  for(int i = 0; i < nbVertex - 1; i++){
    for(int j = i + 1; j < nbVertex; j++){
      Clause c = create_clause(2, DISJONCTIVE);
      c->vars[0] = -vars[i][0];
      c->vars[1] = -vars[j][0];
      add(f, c);
    }
  }
}

//Third clause of the Question
void number3(SAT_Formula f, int** vars, int k){
  Clause c = create_clause(orderG(), DISJONCTIVE);
  for(int i = 0; i < orderG(); i++){
    c->vars[i] = vars[i][k-1];
  }
  add(f, c);
}

//Return the number of neighbours of the vertex u.
int nbNeighbours(int u){
  int n = 0;
  for(int i = 0; i < orderG(); i++){
    if(are_adjacent(u, i))
      n++;
  }
  return n;
}

//Fourth clause of the Question
void number4(SAT_Formula f, int** vars, int k){
  int nbVertex = orderG();
  for(int vertex = 0; vertex < nbVertex; vertex++){
    for(int i = 1; i < k; i++){
      Clause c = create_clause(nbNeighbours(vertex) + 1, DISJONCTIVE);
      c->vars[0] = -vars[vertex][i];
      int cursor = 1;
      for(int voisin = 0; voisin < nbVertex; voisin++){
        if(are_adjacent(vertex, voisin)){
          c->vars[cursor] = vars[voisin][i - 1];
          cursor++;
        }
      }
      add(f, c);
    }
  }
}

void printResultGraph(int nbVertex, int k){

    //init vars and stuff
    char* var = (char*) malloc(sizeof(char) * 255);
    int* r = (int*) malloc(sizeof(int) * nbVertex);

    //malloc of the adjacent matrix & fill with 0
    int** result = (int**) malloc(sizeof(int*) * nbVertex);
    for (int i = 0; i < nbVertex; i++){
        result[i] = (int*) malloc(sizeof(int) * nbVertex);
        for (int j = 0; j < nbVertex; j++)
            result[i][j] = 0;
    }

    int i = 0;

    //get all the positives values from stdin
    while (var[0] != '0'){
        scanf("%s", var);
        int n = atoi(var);
        if (n > 0){
            r[i] = n;
            i++;
        }
    }

    //translate values from Glucz to vertex identifier + their d(v)
    int* d = (int*) malloc(sizeof(int) * nbVertex);
    int* v = (int*) malloc(sizeof(int) * nbVertex);
    for (i = 0; i < nbVertex; i++){
        d[i] = (r[i] - 1) % (k + 1);
        v[i] = 0;
    }

    int degree = 0; //root
    queue q = newQueue(0);
    queue first = q;
    int root_i = -1;
    while (q != NULL){
        queue t = q;
        while (t!= NULL){
            t = t->next;
        }

        for (i = 0; i < nbVertex; i++){
            if (d[i] == degree){
                if (degree == 0 && root_i == -1)
                    root_i = i;
                addToQueue(q, i);
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

        int new_degree = d[q->value] + 1;

        degree = new_degree;
    }

    //display
    printf("Root vertex is v%d\n", root_i);
    for (i = 0; i < nbVertex; i++){
        for (int j = 0; j < nbVertex; j++){
            printf("%d ", result[i][j]);
        }

        printf("\n");
    }

    destroyQueue(first);
    free(v);
    free(d);
    free(var);
    free(r);
    for(int i = 0; i < nbVertex; i ++){
      free(result[i]);
    }
    free(result);
}


int main(int argc, char* argv[]){

  if (argc == 3 && strcmp(argv[1], "-r") == 0){
    printResultGraph(orderG(), atoi(argv[2]));
    return 0;
  } else if(argc != 2){
    printf("Use './main k > formula.txt' to create your file for glucose.\n");
    printf("Use './main -r k < result.txt' to display the adjacent matrix of the tree with k height.\n");
    printf("Replace the k with the height of your tree\n");
    return 1;
  }

  int nbVertex = orderG();
  int k = atoi(argv[1]) + 1;

  int** vars = createVars(nbVertex, k);
  SAT_Formula formula = create_formula();

  number1(formula, vars, k);
  number2(formula, vars, k);
  number3(formula, vars, k);
  number4(formula, vars, k);

  showFormula(formula, nbVertex * k);

  destroyFormula(formula);
  destroyVars(vars, nbVertex);
  return 0;
}
