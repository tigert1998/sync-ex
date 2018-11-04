# Synchronization & Exclusion

![](https://upload.wikimedia.org/wikipedia/commons/thumb/7/7b/An_illustration_of_the_dining_philosophers_problem.png/440px-An_illustration_of_the_dining_philosophers_problem.png)

![](https://www.cs.fsu.edu/~engelen/courses/COP4610/lab2.gif)

## Prerequisite

- `-std=c++11`
- `cmake`
- `python3`

## Build

1. `cmake . && make && cd bin`

## Usage

1. If you are going to run batch test, just run `test.py`

2. Or you can just type your favorite car directions and orders, like `./main nsewwewn`. And it may give the following result (probably not exactly the same every time).

   ```
   car 1 from North arrives at crossing
   DEADLOCK: car jam detected
   car 1 from North leaving crossing
   car 2 from South arrives at crossing
   car 2 from South leaving crossing
   car 4 from West arrives at crossing
   car 4 from West leaving crossing
   car 8 from North arrives at crossing
   car 8 from North leaving crossing
   car 3 from East arrives at crossing
   car 3 from East leaving crossing
   car 5 from West arrives at crossing
   car 5 from West leaving crossing
   car 6 from East arrives at crossing
   car 6 from East leaving crossing
   car 7 from West arrives at crossing
   car 7 from West leaving crossing
   ```
