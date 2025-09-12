echo compiling
   as86 -o  s.o  s.s
   bcc  -c -ansi  t.c
   
echo linking
   ld86 -d s.o t.o mylib /usr/lib/bcc/libc.a

echo cp a.out to mtximage/boot/mtx
   mount -o loop mtximage /mnt
   cp a.out /mnt/boot/mtx
   umount /mnt
echo done

echo booting...
qemu-system-i386 -fda mtximage -no-fd-bootchk

#  Use YOUR MTX booter of LAB#1 to boot up MTX


