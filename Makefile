run:
	@echo "Compiling..."
	@g++ -o detector.out src/detector.cpp src/Car.cpp
	@echo "finished!"
	./detector.out

tests:
	@echo "compiling test..."
	@g++ -o test.out test/test.cpp src/Car.cpp
	@echo "finished!"
	./test.out
	rm test.out

clean:
	rm *.out
