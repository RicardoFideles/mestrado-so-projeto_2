#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int tamMatriz = 0;
int processos = 1;
int **c;

struct slice {
	int offset;
	int lines;
	int  **a;
  int  **b;
};

void printMatriz(int **mat){
	int i, j;
	
	for (i = 0; i < tamMatriz; i++) {
		printf("\n\t| ");
		for (j = 0; j < tamMatriz; j++){
			printf("%4d", mat[i][j]);
		}
		printf("    |");
	}
	printf("\n\n");
}

void multiplyMatriz(void *arg)
{ 
  int i, linha;
	struct slice *s = (struct slice *)arg;
  double somaLocal = 0.0;

  for (linha = s->offset; linha < ( s->offset + s->lines); linha++) {
    for (int col = 0; col < tamMatriz; col++) {
      // Multiplica a linha de A pela coluna de B.
      for (int i = 0; i < tamMatriz; i++) {
          // pthread_mutex_lock(&f_lock);
          c[linha][col] += s->a[linha][i] * s->b[i][col];
          // pthread_mutex_unlock(&f_lock);
      }
    }
  }
}

void calc(int **a, int **b, int tamMatriz, int processos)
{
	int i;
	struct slice *slices = malloc(processos * sizeof(struct slice));

	int div = tamMatriz / processos;
	int rem = tamMatriz % processos;
  pid_t pids[processos];
  int semaforo = processos;

	for (i = 0; i < processos; i++) {
		struct slice *s = &slices[i];
		s->a = a;
    s->b = b;
		s->offset = i * div;
		s->lines = (i < (processos - 1)) ? div : div + rem;

    if(pids[i] == 0) {
      exit(0);
    }

		multiplyMatriz(s);
		wait(NULL);
	}

	free(slices);
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
      printf("Informe o tamanho da matriz e o número de processos");
      exit(-1);
  }

  tamMatriz = atoi(argv[1]);
  processos = atoi(argv[2]);

	if(processos > tamMatriz) {
		printf("O tamanho da matriz deve ser maior que o número de processos.");
		return 0;
	}
  
	int i, j;
  int **a = (int **)malloc(tamMatriz * sizeof(int*));
  int **b = (int **)malloc(tamMatriz * sizeof(int*));
  c = (int **)malloc(tamMatriz * sizeof(int*));

  for (i = 0; i < tamMatriz; i++) {
    a[i] = (int *)malloc(tamMatriz * sizeof(int));
    b[i] = (int *)malloc(tamMatriz * sizeof(int));
    c[i] = (int *)malloc(tamMatriz * sizeof(int));
    for (j = 0; j < tamMatriz; j++) {
      a[i][j] = 1;
      b[i][j] = 2;
      c[i][j] = 0;
    }
  }

  clock_t inicioProcessamento = clock();
	calc(a, b, tamMatriz, processos);
  clock_t fimProcessamento = clock();
  double timepassed = (double)(fimProcessamento - inicioProcessamento) / CLOCKS_PER_SEC;

  printf("%d, %d, %f \n", tamMatriz, processos, timepassed);
  free(a);
  free(b);
  free(c);
	return 0;
}
