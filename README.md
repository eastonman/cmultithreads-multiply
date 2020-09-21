# CMultithreads-Multiply

This is a demo repo that implement two algorithm of large number multiply
* Single thread, vertical-calculation like algorithm
* 3 threads Self-implemented Karatsuba-like algorithm
* Single thread Karatsuba algorithm

Test machine: i7-10750H 2GB RAM

| Test case | time |
| ----- | -----|
| Single thread 50000 | 6.393974 |
| 3 threads Self-implemented 50000 | 1.248952 |
| Single thread Karatsuba 50000 |1.901492|
| Single thread 150000 | 53.556499 |
| 3 threads Self-implemented 150000 |15.656759|
| Single thread Karatsuba 150000 | 4.309122|