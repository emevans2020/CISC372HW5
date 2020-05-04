 /*  Emily Evans and Hannah Bridge
  * 
  * PThread on macbook pro: 
  * srun -c 40 ./pin_pt 100000000 40
  * The PIN is 6586 (nthreads = 40, time = 0.174676 sec.)
  * 
  * MPI runtime below on macbook pro:
  * srun -n 40 ./pin_mpi 100000000
  * The PIN is 6586 (nprocs = 40, time = 0.134965 sec.)
  *
  * According to the runtimes above MPI is faster than pthreads.
  **/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <sys/time.h>

int *nthreads;
pthread_mutex_t lock;
double stop;
int result; 

void *getPin (void *arg); // function to have threads get pin
	
int main(int argc, char *argv[]) {
  assert(argc==3);
  nthreads = malloc(sizeof(int));
  *nthreads = atoi(argv[2]); 
  
  stop = (double)atol(argv[1]);

  assert(stop >= 1.0);

  struct timeval start;
  gettimeofday(&start, NULL);

  pthread_mutex_init(&lock, NULL);
  
  result = 0;
  
  pthread_t *threads = (pthread_t *) malloc (*nthreads *sizeof(pthread_t)); 
  for (long int tid = 0; tid < *nthreads; tid++) {
 	pthread_create(&threads[tid], NULL, getPin, (void*)tid);
  }
  for (long int tid = 0; tid < *nthreads; tid++){
	pthread_join(threads[tid], NULL);
  }
  result = result % 10000;

  struct timeval end;
  gettimeofday(&end,NULL);

  double t_total = (double) (((end.tv_sec - start.tv_sec)*1000000L + end.tv_usec) - start.tv_usec) /1000000.0;
  
  printf("The PIN is %1d (nthreads = %d, time = %f sec.)\n", result, *nthreads, t_total);
  fflush(stdout);
  free(nthreads);
  return 0;
}

void *getPin (void *arg) {
    int local_result = 0;
    long int tid = (long int) arg;

    for (double x = tid*1.0; x < stop; x+= *nthreads*1.0) {
	double tmp = sin(x);
	double tmp2 = tmp*tmp;
        int z = (int)(tmp2*10000.0);
        local_result = (local_result + z) % 10000;
    }
    pthread_mutex_lock(&lock);
    result += local_result;
    pthread_mutex_unlock(&lock);
    return NULL;
}
