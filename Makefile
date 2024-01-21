run: threadHoarder.c
	cc -Wall -o threadHoarder threadHoarder.c  

clean: 
	rm psOutput threadHoarder
