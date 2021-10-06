run:
	@echo "Compiling..."
	@g++ src/detector.cpp src/Car.cpp
	@echo "finished!"
	./a.out

clean:
	rm *.out
