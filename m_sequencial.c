#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int tamM = 0;
int **a, **b, **c;

void printM(int **mat){
	int i, j;
	
	for (i = 0; i < tamM; i++) {
		printf("\n\t| ");
		for (j = 0; j < tamM; j++){
			printf("%4d", mat[i][j]);
		}
		printf("    |");
	}
	printf("\n\n");
}

void multiply(void *arg)
{ 
  int i, linha, col;

  for (linha = 0; linha < tamM; linha++) {
    for (col = 0; col < tamM; col++) {
      // Multiplica a linha de A pela coluna de B.
      for (int i = 0; i < tamM; i++) {
          // pthread_mutex_lock(&f_lock);
          c[linha][col] += a[linha][i] * b[i][col];
          // pthread_mutex_unlock(&f_lock);
      }
    }
  }
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
      printf("Informe o tamanho da matriz");
      exit(-1);
  }

  tamM = atoi(argv[1]);
  
	int i, j;
  a = (int **)malloc(tamM * sizeof(int*));
  b = (int **)malloc(tamM * sizeof(int*));
  c = (int **)malloc(tamM * sizeof(int*));

  for (i = 0; i < tamM; i++) {
    a[i] = (int *)malloc(tamM * sizeof(int));
    b[i] = (int *)malloc(tamM * sizeof(int));
    c[i] = (int *)malloc(tamM * sizeof(int));
    for (j = 0; j < tamM; j++) {
      a[i][j] = 1;
      b[i][j] = 2;
      c[i][j] = 0;
    }
  }

  struct timeval start, end;
  gettimeofday(&start, NULL);
	multiply(c);
  gettimeofday(&end, NULL);
  double tempoGasto = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 1000000.0;

  printf("%d, %f \n", tamM, tempoGasto);

  free(a);
  free(b);
  free(c);
	return 0;
}
