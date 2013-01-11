CC=gcc
ORACLE_HOME=/home/oracle/app/oracle/product/11.2.0/dbhome_1
CFLAGS=-lclntsh
tea.o:tea.c
	proc tea.pc
	$(CC) -o tea $< -I $(ORACLE_HOME)/rdbms/public -L $(ORACLE_HOME)/lib -L $(ORACLE_HOME)/rdbms/lib $(CFLAGS)

clean:
	rm -rf tea
