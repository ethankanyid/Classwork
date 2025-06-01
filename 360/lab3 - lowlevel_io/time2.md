1 MB file

1    ./raw_copy 1 big_data.bin ouput.bin  5.97s user 43.89s system 99% cpu 50.087 total
2    ./raw_copy 2 big_data.bin ouput.bin  2.93s user 21.50s system 99% cpu 24.534 total
4    ./raw_copy 4 big_data.bin ouput.bin  1.47s user 10.45s system 99% cpu 11.974 total
8    ./raw_copy 8 big_data.bin ouput.bin  0.74s user 5.34s system 99% cpu 6.126 total
16   ./raw_copy 16 big_data.bin ouput.bin  0.37s user 2.65s system 99% cpu 3.038 total
32   ./raw_copy 32 big_data.bin ouput.bin  0.19s user 1.39s system 97% cpu 1.614 total
64   ./raw_copy 64 big_data.bin ouput.bin  0.10s user 0.69s system 97% cpu 0.808 total
128  ./raw_copy 128 big_data.bin ouput.bin  0.05s user 0.36s system 97% cpu 0.417 total
256  ./raw_copy 256 big_data.bin ouput.bin  0.02s user 0.19s system 93% cpu 0.229 total
512  ./raw_copy 512 big_data.bin ouput.bin  0.01s user 0.11s system 89% cpu 0.139 total
1024 ./raw_copy 1024 big_data.bin ouput.bin  0.01s user 0.06s system 83% cpu 0.086 total
2048 ./raw_copy 2048 big_data.bin ouput.bin  0.00s user 0.04s system 77% cpu 0.054 total
4096 ./raw_copy 4096 big_data.bin ouput.bin  0.00s user 0.03s system 69% cpu 0.042 total
8192 ./raw_copy 8192 big_data.bin ouput.bin  0.00s user 0.02s system 67% cpu 0.036 total
16384 ./raw_copy 16384 big_data.bin ouput.bin  0.00s user 0.02s system 54% cpu 0.038 total


as the buffer size increases by poweres of 2, the execution time decreases roughly by powers of 2.
at large sizes for the buffer, there isnt as dramatic of a decrease in execution time.
cpu usage also decreases with larger buffers.