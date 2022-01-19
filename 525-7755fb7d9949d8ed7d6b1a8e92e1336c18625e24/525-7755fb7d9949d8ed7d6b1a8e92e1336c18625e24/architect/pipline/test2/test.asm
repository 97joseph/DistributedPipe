0000 set R0 #50
0004 set R1 #50
0008 set R2 #1000
0012 set R3 #4000
0016 set R4 #7000
0020 set R5, #0
0024 set R6, #0
0028 sub R7, R5, R0
0032 sub R7, R6, R1
0036 mul R7, R6, #4
0040 mul R8, R5, R1
0044 mul R9, R8, #4
0048 add R10, R7, R9
0052 add R7, R2, R10
0056 add R7, R3, R10
0060 ret
