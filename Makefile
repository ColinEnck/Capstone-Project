in := battleship.cpp
out := battleship

$(out): $(in)
	g++ $(in) -lncursesw -g -o $(out)
