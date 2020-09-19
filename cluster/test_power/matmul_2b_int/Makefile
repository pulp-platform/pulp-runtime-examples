PULP_APP = test
PULP_APP_SRCS = test.c
PULP_CFLAGS=-O3

fc=0
cluster=1
PULP_ARCH_CFLAGS  = -march=rv32imcXpulpnn -D__riscv__
PULP_ARCH_LDFLAGS =  -march=rv32imcXpulpnn -D__riscv__
PULP_ARCH_OBJDFLAGS = -Mmarch=rv32imcXpulpnn 
include $(PULP_SDK_HOME)/install/rules/pulp.mk
