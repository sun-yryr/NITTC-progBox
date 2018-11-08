#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int size;
    printf("データ数2^N -> ");
    scanf("%d", &size);
    FILE *fp;
    if ((fp = fopen("./data/source.txt", "w")) == NULL) {
        printf("write_file open error.\n");
        exit(EXIT_FAILURE);
    }
    srand((unsigned)time(NULL));
    //double *data;
    //data = (double*)malloc(size * sizeof(double));
    for(int i=0; i<pow(2, size); i++) {
        fprintf(fp, "%lf\n", rand()/(double)rand());
    }
}