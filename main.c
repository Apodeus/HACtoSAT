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

int abs(int n){
  if(n < 0)
    return -n;
  return n;
}

void printResultGraph(int nbVertex){

    //init vars and stuff
    char* varString = (char*) malloc(sizeof(char) * 255);
    int* positiveVars = (int*) malloc(sizeof(int) * nbVertex);

    //malloc of the adjacent matrix & fill with 0
    int** result = (int**) malloc(sizeof(int*) * nbVertex);
    for (int i = 0; i < nbVertex; i++){
        result[i] = (int*) malloc(sizeof(int) * nbVertex);
        for (int j = 0; j < nbVertex; j++)
            result[i][j] = 0;
    }


    //get all the positives values from stdin
    int i = 0;
    int nbVars = 0;
    while (varString[0] != '0'){
        scanf("%s", varString);
        int var = atoi(varString);
        if(nbVars < abs(var)){
          nbVars = abs(var);
        }
        if (var > 0){
            positiveVars[i] = var;
            i++;
        }
    }

    int k = (nbVars / nbVertex) - 1;
    //translate values from Glucz to vertex identifier + their d(v)
    int* heightVertex = (int*) malloc(sizeof(int) * nbVertex);
    int* markOnVertex = (int*) malloc(sizeof(int) * nbVertex);
    for (i = 0; i < nbVertex; i++){
        heightVertex[i] = (positiveVars[i] - 1) % (k + 1);
        markOnVertex[i] = 0;
    }

    int height = 0; //root
    queue q = newQueue(0);
    queue first = q; //queue first is just here for free the queue
    int root_i = -1;
    //Construction of the queue
    while (q != NULL){
        for (i = 0; i < nbVertex; i++){
            if (heightVertex[i] == height){
                if (height == 0 && root_i == -1) // if it's the root
                    root_i = i;
                // We had the index i which has the good height
                addToQueue(q, i);
                //If the vertex at index i is not marked and is adjacent with the first in the queue
                //We update the adjacent matrix (result here). And we mark the index i
                if (q != NULL && markOnVertex[i] == 0 && are_adjacent(q->value, i)){
                    fprintf(stderr, "v%d and v%d are adjacent\n", q->value, i);
                    result[i][q->value] = 1;
                    result[q->value][i] = 1;
                    markOnVertex[i] = 1;
                }
            }
        }

        //We take the next in queue
        //And update the the height.
        q = q->next;
        if (q != NULL)
          height = heightVertex[q->value] + 1;
    }

    //display the matrix
    printf("Root vertex is v%d\n", root_i);
    for (i = 0; i < nbVertex; i++){
        for (int j = 0; j < nbVertex; j++){
            printf("%d ", result[i][j]);
        }

        printf("\n");
    }

    //free all
    destroyQueue(first);
    free(markOnVertex);
    free(heightVertex);
    free(varString);
    free(positiveVars);
    for(int i = 0; i < nbVertex; i ++){
      free(result[i]);
    }
    free(result);
}


int main(int argc, char* argv[]){

  if (argc == 2 && strcmp(argv[1], "-r") == 0){
    printResultGraph(orderG());
    return 0;
  } else if(argc == 3 && strcmp(argv[1], "-k") == 0){
    int nbVertex = orderG();
    int k = atoi(argv[2]) + 1;

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

  printf("Use './main -k k > formula.txt' to create your file for glucose.\n");
  printf("Use './main -r k < result.txt' to display the adjacent matrix of the tree with k height from the file generated by glucose.\n");
  printf("Replace the k with the height of your tree.\n");
  return 1;

}
