all: main-v1.exe main-v2.exe main-v3.exe generator.exe

CC=clang++
CFLAGS=-Wall -O2

iMKL=`pkg-config --cflags mkl-intel`
lMKL=`pkg-config --libs mkl-intel`
OBJ= stopWatch.o

%.o: %.cpp 
	$(CC) $(CFLAGS) -c $< -o $@  $(iMKL) $(lMKL)
main-v1.exe: main.o v1/mmm.o $(OBJ)
	$(CC) $(CFLAGS) $< -o $@ v1/mmm.o  $(OBJ)

main-v2.exe: main.o v2/mmm.o $(OBJ)
	$(CC) $(CFLAGS) $< -o $@ v2/mmm.o  $(OBJ)

main-v3.exe: main.o v3/mmm.o $(OBJ)
	$(CC) $(CFLAGS) $< -o $@ v3/mmm.o  $(iMKL) $(lMKL) $(OBJ)

generator.exe:generator.o
	$(CC) $(CFLAGS) $< -o $@

data:
	@arg1=1 arg2=1 arg3=0;\
	while [[ $$arg1 -le 20 ]] ; do \
		((arg3 = 64 * (2 ** (arg1))));\
		((arg4 = arg3));\
		((arg5 = arg2));\
		((arg6 = arg1));\
		./generator.exe $$arg1 $$arg2 $$arg3 $$arg4 $$arg5 vv-$$arg6.dat;\
		echo "./generator.exe " $$arg1 $$arg2 $$arg3 $$arg4 $$arg5 vv-$$arg6.dat;\
		((arg1 = arg1 + 1)) ; \
	done
	
	@arg1=1 arg2=16 arg5=1;\
	while [[ $$arg1 -le 20 ]] ; do \
		((arg3 = arg2));\
		((arg2 += arg2 * ((arg1-1)%2)));\
		((arg4 = arg3));\
		((arg6 = arg1));\
		./generator.exe $$arg1 $$arg2 $$arg3 $$arg4 $$arg5 mv-$$arg6.dat;\
		echo "./generator.exe " $$arg1 $$arg2 $$arg3 $$arg4 $$arg5 mv-$$arg6.dat;\
		((arg1 = arg1 + 1)) ; \
	done

	@arg1=1 arg2=16;\
	while [[ $$arg1 -le 15 ]] ; do \
		((arg3 = arg2));\
		((arg2 += arg2 * ((arg1-1)%2)));\
		((arg5 = arg2));\
		((arg4 = arg3));\
		((arg6 = arg1));\
		./generator.exe $$arg1 $$arg2 $$arg3 $$arg4 $$arg5 mm-$$arg6.dat;\
		echo "./generator.exe " $$arg1 $$arg2 $$arg3 $$arg4 $$arg5 mm-$$arg6.dat;\
		((arg1 = arg1 + 1)) ; \
	done	


benchmark:
	@cat>vv.out<<"eof"
	@i=1;\
	while [[ $$i -le 20 ]] ; do\
		j=1;\
		while [[ $$j -le 3 ]] ; do\
			echo "./main-v"$$j".exe vv-"$$i".dat vv-"$$i".out >>vv.out";\
			./main-v$$j.exe vv-$$i.dat vv-$$i.out >>vv.out;\
			((j = j + 1));\
		done;\
		((i = i + 1));\
	done

	@cat>mv.out<<"eof"
	@i=1;\
	while [[ $$i -le 20 ]] ; do\
		j=1;\
		while [[ $$j -le 3 ]] ; do\
			echo "./main-v"$$j".exe mv-"$$i".dat mv-"$$i".out >>mv.out";\
			./main-v$$j.exe mv-$$i.dat mv-$$i.out >>mv.out;\
			((j = j + 1));\
		done;\
		((i = i + 1));\
	done

	@cat>mm.out<<"eof"
	@i=1;\
	while [[ $$i -le 15 ]] ; do\
		j=1;\
		while [[ $$j -le 3 ]] ; do\
			echo "./main-v"$$j".exe mm-"$$i".dat mm-"$$i".out >>mm.out";\
			./main-v$$j.exe mm-$$i.dat mm-$$i.out >>mm.out;\
			((j = j + 1));\
		done;\
		((i = i + 1));\
	done

clean: 
	rm *.exe *n.o *r.o *.out v1/*.o v2/*.o v3/*.o *.dat

test:
	echo "01.dat" "01-v1.out" | ./main-v1.exe
	echo "02.dat" "02-v1.out" | ./main-v1.exe
	echo "03.dat" "03-v1.out" | ./main-v1.exe
	echo "01.dat" "01-v2.out" | ./main-v2.exe
	echo "02.dat" "02-v2.out" | ./main-v2.exe
	echo "03.dat" "03-v2.out" | ./main-v2.exe
	echo "01.dat" "01-v3.out" | ./main-v3.exe
	echo "02.dat" "02-v3.out" | ./main-v3.exe
	echo "03.dat" "03-v3.out" | ./main-v3.exe

