all: goals

goals: 
	g++ -o goals goals.cpp -std=c++11

clean:
	rm ~/scripts/goals
	rm ~/scripts/goals.txt

update: goals
	mv goals ~/scripts/goals

install: goals
	mkdir -p ~/scripts
	mv goals ~/scripts
	cp goals.txt ~/scripts
	@echo 'export PATH=$$PATH:~/scripts' >> ~/.bashrc
	@echo 'source ~/.bashrc'
