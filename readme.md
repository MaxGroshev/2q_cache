# caches
- This repository consits of 2 kinds of caches:
    - 2 queue cache
    - perfect cache


# Install and run?
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

#### How to choose mode ?
- run 2 queue cache:
```
> make
> ./lru -2q
```
- run perfect cache;
```
> make
> ./lru -pc
```
- if no key is selected, one of the caches will be run
```
> make
> ./lru
```
---

#### How to run debug mode
- go to /debug_utils/error_control.h
- #define DEBUG


---

