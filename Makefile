

create:
	gcc main.c s21_helper.c binary.c -o test1

mac: create
	./test1

win: create
	./test1.exe