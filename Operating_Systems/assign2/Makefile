all: compC compJava runC runJava

compC: pThreads.c
	gcc -o pThreads pThreads.c -pthread

runC: pThreads
	./pThreads 10
	./pThreads 1000
	./pThreads 5000
	./pThreads 10000

compJava: SorterThread.java
	javac SorterThread.java

runJava: compJava
	java SorterThread 10
	java SorterThread 1000
	java SorterThread 5000
	java SorterThread 10000

clean:
	rm -f *.class pThreads
