# caches
- This repository consits of 2 kinds of caches:
    - 2 queue cache
    - perfect cache


# Install and run
```
> git clone https://github.com/MaxGroshev/2q_cache.git
> make
> ./lru
```
---

#### How to run my tests
```
> make
> ./lru -tc
```
---

#### How to choose cache for teacher testing?
- go to main.cpp choose one of two functions
    - run_two_q_cache (); - for 2q cache
    - run_perf_cache ();  - for perfect cache
---

#### How to run optimized compilation
```
> make optimized
> ./lru
```
- You are able to change optimization flag in  /makefile
---

#### How to run debug mode
- go to /debug_utils/error_control.h
- #define DEBUG


---

