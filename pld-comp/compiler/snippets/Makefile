
ARCH=x86

demo: ../ifcc 
	mkdir -p out
	../ifcc demo.c --arch=$(ARCH) > out/demo.s
	gcc -c out/demo.s -o out/demo.o
	gcc out/demo.o -o out/demo
	./out/demo

demo_multi:
	mkdir -p out
	../ifcc demo_multi.c --arch=$(ARCH) > out/demo_multi.s
	../ifcc demo_multi2.c --arch=$(ARCH) > out/demo_multi2.s
	gcc -c out/demo_multi.s -o out/demo_multi.o
	gcc -c out/demo_multi2.s -o out/demo_multi2.o
	gcc out/demo_multi.o out/demo_multi2.o -o out/demo_multi
	./out/demo_multi

