CC = cc -pedantic -std=c11
MPICC = mpicc -pedantic -std=c11
MPIRUN = srun
LINKS = -lm
SMALL  =        100
MEDIUM =   10000000
LARGE =  1000000000

pin : pin.c
	$(CC) -o pin pin.c $(LINKS)

pin_mpi : pin_mpi.c
	$(MPICC) -o pin_mpi pin_mpi.c $(LINKS)

pin_pt : pin_pt.c
	$(CC) -o pin_pt pin_pt.c -lpthread $(LINKS)

.PHONY : seq_small
seq_small : pin
	./pin $(SMALL)

.PHONY : seq_medium
seq_medium: pin
	./pin $(MEDIUM)

.PHONY : seq_large
seq_large: pin
	./pin $(LARGE)

.PHONY : mpi_small
mpi_small : pin_mpi
	$(MPIRUN) -n 40 ./pin_mpi $(SMALL)

.PHONY : mpi_medium
mpi_medium: pin_mpi
	$(MPIRUN) -n 40 ./pin_mpi $(MEDIUM)

.PHONY : mpi_large
mpi_large: pin_mpi
	$(MPIRUN) -n 40 ./pin_mpi $(LARGE)

.PHONY : pt_small
pt_small: pin_pt
	srun -c 15 ./pin_pt $(SMALL) 15

.PHONY: pt_medium
pt_medium: pin_pt
	srun -c 40 ./pin_pt $(MEDIUM) 40

.PHONY: pt_large
pt_large: pin_pt
	srun -c 40 ./pin_pt $(LARGE) 40
	
clean :
	rm -f pin pin_mpi pin_pt *~
