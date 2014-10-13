obj-m := RPInterface.o
srcdir :=.src/

all:
        gcc -C $(srcdir) M=$(PWD)

clean:
        make -C $(kerneldir) M=$(PWD) clean
