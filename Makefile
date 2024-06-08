all: gauss-seidel

gauss-seidel: gauss_seidel.c
	gcc gauss_seidel.c -o gauss-seidel -lm

clean:
	rm -rf  a.out *.o gauss-seidel ans.csv
