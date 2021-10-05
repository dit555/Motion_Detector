run:
	@echo "Compiling..."
	@g++ src/detector.cpp
	@echo "finished!"
	./a.out

clean:
	rm *.out
