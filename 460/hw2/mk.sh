echo "cleaning .o's"
   rm *.o
   rm a.out

set -e

echo compiling
   as86 -o  s.o  s.s
   bcc -c -ansi t.c kernel.c func.c queue.c

echo linking
    ld86 -d s.o t.o queue.o func.o kernel.o mylib mtxlib /usr/lib/bcc/libc.a

echo cp a.out to mtximage/boot/mtx
   mount -o loop mtximage /mnt
   cp a.out /mnt/boot/mtx
   umount /mnt
echo done

echo booting...
qemu-system-i386 -fda mtximage -no-fd-bootchk
