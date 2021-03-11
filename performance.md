# Performance Measuring and Improvements

## Detection of most time consuming part and improvement

For timestep of $10^{-5}$ and Explicit Euler solver we have observed that only  7 to 20 percent of total execution time used in computation and 90 to 80 percent of total time is spent while writing to file. We have and obvious problem that writing to file is took really huge percentage of the total execution time used. To handle this one we have implemented a new version of writeToFile function called writeToFilev2 it takes same arguments as an input. This new function reduces function time to 1/5th of original one. To total runtime was reduced to 1/4th of original one. 

Using timestep of $10^{-5}$ 


|Method         | New Runtime (ms) | Old Runtime (ms)  | Speedup (Before/After) |
|-------------- | ---------------- | --------------  | ----------------------   |
|Explicit Euler  | 579             | 2321            | 4                        |
|Implicit Euler	| 1116            | 3059            | 2.7                      |
|Runge-Kutta -4  | 732             | 2637            | 3.6                      |


## Effect of loop unrolling 

A loop unrolling is applied to Explicit Euler Solver. The time spent in EESolver is roughly 110-120 ms before the loop unrolling. After the loop unrooling this time does down to 90 ms which means we have a speed-up of 1.3 times in EESolver.

## Effect of Boundary Check

Initial code was used .at() method of std::vector which automaticly does a bound check. To investigate effect of boundary checking rk4solver has been changed at [] operator to access vector elements. Timing results how that bound checking has little/no effect on timing of rk4solver. 

## Effect of Optimization Option

Compile option -O1,-O2 and -O3 are tested. All three options enjoy similar performance improvement. The speed up is about 4 times compare to not using the optimization option.


|Method         | Raw Runtime (ms) | -O1 Runtime (ms)  | -O2 Runtime (ms) | -O3 Runtime (ms)
|-------------- | ---------------- | --------------  | ----------------------   |-----------------
|Explicit Euler  | 200             | 59            | 58                        | 63

