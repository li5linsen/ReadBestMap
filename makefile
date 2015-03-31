objs = main.o assistant.o genProcess.o map_mulPreKey.o
ReadBestMap : $(objs)
	cc -o ReadBestMap $(objs)
main.o : main.c head.h
	cc -c main.c
assistant.o : assistant.c head.h 
	cc -c assistant.c
genProcess.o : genProcess.c head.h assistant.c
	cc -c genProcess.c assistant.c
map_mulPreKey.o : map_mulPreKey.c head.h assistant.c
	cc -c map_mulPreKey.c assistant.c
clean :
	rm $(objs)
#for GNU environment
