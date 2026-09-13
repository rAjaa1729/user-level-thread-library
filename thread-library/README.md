# User-Level Thread Library

A cooperative ("green") threading library built from scratch on top of
`ucontext` — no OS threads — plus a thread-safe hash map and linked list
used to test it.

## API (`include/mythread.h`)

```c
void mythread_init();                              // set up the thread list
ucontext_t* mythread_create(void func(void*), void* arg);  // spawn a thread
void mythread_yield();                              // cooperative context switch
void mythread_join();                               // wait for all threads

struct lock* lock_new();
void lock_acquire(struct lock* lk);
int  lock_release(struct lock* lk);
```

## Hash map (`include/hm.h`)

A chained hash map (`SZ = 4096` buckets, each a linked list) with a
**separate lock per bucket** (`struct lock* lk[SZ]`) rather than one
global lock, so threads touching different buckets don't block each
other — `acquire_bucket`/`release_bucket` lock just the bucket a given
key hashes to.

## Build & run

```bash
make list   # builds and runs the linked-list tests
```

`test/hashmap_test.c` and `test/main.c` (which reads `data/in1.txt`–
`in4.txt` and exercises the hash map from multiple threads) exist but
have no `make` target wired up yet — the original assignment left adding
`hashmap`/`all` targets to the student, and that step wasn't finished
here. Build them directly, e.g. (verified working):

```bash
mkdir -p obj
gcc -D_XOPEN_SOURCE=600 -I include/ -o obj/hashmap_test test/hashmap_test.c src/hm.c src/list.c src/mythread.c
./obj/hashmap_test
```

Written and tested on Linux (see the comment in `warmup/print_uctx.c`);
on macOS, `-D_XOPEN_SOURCE=600` is required for `ucontext` to compile at
all with the system headers.

## `archive/`

`mythread-pthread-variant.c` — the same `mythread_*` API reimplemented
over real POSIX threads (`pthread_create`/`pthread_mutex_*`) instead of
`ucontext`, as a comparison against the cooperative version above.
Incomplete: the hash map and list source files for this variant were
never filled in, so it doesn't build as-is. `Doxyfile` is a Doxygen
config for generating docs from this variant.
