Files = FilePrint.o TerminalPrint.o Logging.o LoggingInv.o Sigmoid.o DSigmoid.o Perform.o GradientDescent.o Learn.o Compare.o Main.o

Executable: $(Files) MainHeader.h
	@echo "Linking All Object Files..."
	g++ -I /usr/include/eigen3/ $(Files) -o Executable

FilePrint.o: FilePrint.cpp
	@echo "Build File Printing..."
	g++ -I /usr/include/eigen3/ -c FilePrint.cpp -o FilePrint.o

TerminalPrint.o: TerminalPrint.cpp
	@echo "Build Terminal Printing..."
	g++ -I /usr/include/eigen3/ -c TerminalPrint.cpp -o TerminalPrint.o

Logging.o: Logging.cpp
	@echo "Build Logging.."
	g++ -I /usr/include/eigen3/ -c Logging.cpp -o Logging.o

LoggingInv.o: LoggingInv.cpp
	@echo "Build Logging Inverse..."
	g++ -I /usr/include/eigen3/ -c LoggingInv.cpp -o LoggingInv.o

Sigmoid.o: Sigmoid.cpp
	@echo "Build Sigmoid..."
	g++ -I /usr/include/eigen3/ -c Sigmoid.cpp -o Sigmoid.o

DSigmoid.o: DSigmoid.cpp
	@echo "Build Derivative Sigmoid..."
	g++ -I /usr/include/eigen3/ -c DSigmoid.cpp -o DSigmoid.o

Perform.o: Perform.cpp
	@echo "Build Perform..."
	g++ -I /usr/include/eigen3/ -c Perform.cpp -o Perform.o

GradientDescent.o: GradientDescent.cpp
	@echo "Build Gradient Descent.."
	g++ -I /usr/include/eigen3/ -c GradientDescent.cpp -o GradientDescent.o 

Learn.o: Learn.cpp
	@echo "Build Learning Algorithm..."
	g++ -I /usr/include/eigen3/ -c Learn.cpp -o Learn.o

Compare.o: Compare.cpp
	@echo "Build Compare..."
	g++ -I /usr/include/eigen3/ -c Compare.cpp -o Compare.o

Main.o: Main.cpp
	@echo "Build Main Function..."
	g++ -I /usr/include/eigen3/ -c Main.cpp -o Main.o

clean:
	@echo "Removing all Object Files..."
	rm *.o