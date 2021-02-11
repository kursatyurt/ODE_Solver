# Performance Measuring and Improvements


For timestep of 1e-5 and Explicit Euler solver we have observed that only  7 to 20 percent of total execution time used in computation and 90 to 80 percent of total time is spent while writing to file. We have and obvious problem that writing to file is took really huge percentage of the total execution time used. To handle this one we have implemented a new version of writeToFile function called writeToFilev2 it takes same arguments as an input. This new function reduces function time to 1/5th of original one. To total runtime was reduced to 1/4th of original one. 

Using timestep of 1e-5 


|Method         | New Runtime (ms) | Old Runtime (ms)  | Speedup (Before/After) |
|-------------- | ---------------- | --------------  | ----------------------   |
|Explicit Euler  | 579             | 2321            | 4                        |
|Implicit Euler	| 1116            | 3059            | 2.7                      |
|Runge-Kutta -4  | 732             | 2637            | 3.6                      |


