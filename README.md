# CMultithreads-Multiply

This is a demo repo that implement two algorithm of large number multiply
* Single thread, vertical-calculation like algorithm
* 3 threads Self-implemented Karatsuba-like algorithm
* Single thread Karatsuba algorithm
* 3 threads Karatsuba algorithm

Test machine: i7-10750H 2GB RAM

| Test case | time |
| ----- | -----|
| Single thread 50000 | 6.393974 |
| 3 threads Self-implemented 50000 | 1.248952 |
| Single thread Karatsuba 50000 | 1.901492 |
| 3 threads Karatsuba 50000 | 1.725530 |
| Single thread 150000 | 53.556499 |
| 3 threads Self-implemented 150000 |15.656759|
| Single thread Karatsuba 150000 | 4.309122|
| 3 threads Karatsuba 150000 | 1.126843|

Note: Karatsuba algorithm costs 1GB RAM at around 150000 scale, others cost little RAM compared to 1GB.