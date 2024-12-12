files := game.c
ofiles := game.o
outfile := game
libraries := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
game:
	gcc $(files) -c $(libraries)
	gcc $(ofiles) $(libraries) -o $(outfile)
clean:
	rm $(ofiles)
	rm $(outfile)
