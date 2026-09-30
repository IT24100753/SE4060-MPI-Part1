# Makefile for SE4060 MPI Part 1 Lab Exercises

MPICC ?= mpicc
MPICXX ?= mpicxx
CC ?= gcc
CFLAGS ?= -O2 -Wall
CXXFLAGS ?= -O2 -Wall
OMPFLAGS ?= -fopenmp
LDFLAGS ?= -lm

TARGETS = HelloMPI job1 messages1 messaage2 messages2 \
          exercise2_sum exercise3_pi exercise5_mismatch exercise5_bsend \
          exercise6_anysource exercise7_bsend Archer2OpenMP/hello

all: $(TARGETS)

HelloMPI: HelloMPI.c
	$(MPICC) $(CFLAGS) -o $@ $<

job1: HelloMPI.c
	$(MPICC) $(CFLAGS) -o $@ $<

messages1: messages1.cc
	$(MPICXX) $(CXXFLAGS) -o $@ $<

messaage2: messaage2.cc
	$(MPICXX) $(CXXFLAGS) -o $@ $<

messages2: messages2.cc
	$(MPICXX) $(CXXFLAGS) -o $@ $<

exercise2_sum: exercise2_sum.c
	$(MPICC) $(CFLAGS) -o $@ $< $(LDFLAGS)

exercise3_pi: exercise3_pi.c
	$(MPICC) $(CFLAGS) -o $@ $< $(LDFLAGS)

exercise5_mismatch: exercise5_mismatch.cc
	$(MPICXX) $(CXXFLAGS) -o $@ $<

exercise5_bsend: exercise5_bsend.cc
	$(MPICXX) $(CXXFLAGS) -o $@ $<

exercise6_anysource: exercise6_anysource.c
	$(MPICC) $(CFLAGS) -o $@ $< $(LDFLAGS)

exercise7_bsend: exercise7_bsend.c
	$(MPICC) $(CFLAGS) -o $@ $< $(LDFLAGS)

Archer2OpenMP/hello: Archer2OpenMP/hello.c
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS) *.o Archer2OpenMP/*.o *.png *.csv

.PHONY: all clean
