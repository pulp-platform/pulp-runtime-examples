PULP_APP = test
PULP_APP_SRCS = test.c
PULP_CFLAGS=-O3 -fno-tree-loop-optimize -fno-tree-loop-distribute-patterns

fc=0
cluster=1
PULP_ARCH_CFLAGS  = -march=rv32imcXpulpnn -D__riscv__
PULP_ARCH_LDFLAGS =  -march=rv32imcXpulpnn -D__riscv__
PULP_ARCH_OBJDFLAGS = -Mmarch=rv32imcXpulpnn 

disopt = --disassembler-options="march=rv32imcXpulpnn" -d

include $(PULP_SDK_HOME)/install/rules/pulp.mk