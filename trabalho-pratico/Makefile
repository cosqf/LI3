CC =gcc
CFLAGS =-c -g -Wall -Wextra -Iinclude 

LDFLAGS =

OBJDIR =obj

all: dirs main

main: $(OBJDIR)/main.o $(OBJDIR)/query1.o $(OBJDIR)/query2.o $(OBJDIR)/query3.o $(OBJDIR)/processInput.o $(OBJDIR)/getdata.o
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJDIR)/main.o: src/main.c 
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/processInput.o: src/processInput.c 
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/query1.o: src/query1.c
	$(CC) $(CFLAGS) $< -o $@ 

$(OBJDIR)/query2.o: src/query2.c
	$(CC) $(CFLAGS) $< -o $@ 
	
$(OBJDIR)/query3.o: src/query3.c
	$(CC) $(CFLAGS) $< -o $@ 

$(OBJDIR)/getdata.o: src/getdata.c
	$(CC) $(CFLAGS) $< -o $@ 


clean:
	rm -r obj
	rm main

dirs: 
	mkdir -p $(OBJDIR) 