#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

int tamMatriz = 0;
int qtdThreads = 1;
int **a, **b, **c;

struct slice {
	int offset;
	int lines;
	pthread_t tid;
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

void *multiplyMatriz(void *arg)
{ 
  int i, linha;
	struct slice *s = (struct slice *)arg;
  double somaLocal = 0.0;

  for (linha = s->offset; linha < ( s->offset + s->lines); linha++) {
    for (int col = 0; col < tamMatriz; col++) {
      for (int i = 0; i < tamMatriz; i++) {
          c[linha][col] += a[linha][i] * b[i][col];
      }
    }
  }


	pthread_exit(NULL);
}

void calcThreads(int **a, int **b, int tamMatriz, int qtdThreads)
{
	int i;
	struct slice *slices = malloc(qtdThreads * sizeof(struct slice));

	int div = tamMatriz / qtdThreads;
	int rem = tamMatriz % qtdThreads;

	for (i = 0; i < qtdThreads; i++) {
		struct slice *s = &slices[i];
		s->offset = i * div;
		s->lines = (i < (qtdThreads - 1)) ? div : div + rem;
		pthread_create(&s->tid, NULL, multiplyMatriz, s);
	}

	for (i = 0; i < qtdThreads; i++) {
		pthread_join(slices[i].tid, NULL);
	}

	free(slices);
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
      printf("Informe o tamanho da matriz e o número de threas respectivamente.");
      exit(-1);
  }

  tamMatriz = atoi(argv[1]);
  qtdThreads = atoi(argv[2]);

	if(qtdThreads > tamMatriz) {
		printf("O Tamanho da matriz precisa ser maior que o número de threads.");
		return 0;
	}
  
	int i, j;
  a = (int **)malloc(tamMatriz * sizeof(int*));
  b = (int **)malloc(tamMatriz * sizeof(int*));
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

  struct timeval start, end;
  gettimeofday(&start, NULL);
	calcThreads(a, b, tamMatriz, qtdThreads);
  gettimeofday(&end, NULL);
  double timePassed = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 1000000.0;

  printf("%d, %d, %f \n", tamMatriz, qtdThreads, timePassed);

  free(a);
  free(b);
  free(c);
	return 0;
}
