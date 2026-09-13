# User-Level Thread Library

An Operating Systems assignment (IIT Delhi, COP290) building a
cooperative thread library from scratch on top of `ucontext` — the raw
mechanism the OS itself uses for context switching, exposed to
user-space C.

| Project | What it is |
|---|---|
| [thread-library](thread-library) | The actual deliverable: green threads, locks, a hash map and linked list built to test them |
| [backtracking-rollback](backtracking-rollback) | A separate small exercise using the same `ucontext` mechanism for backtracking search |
| [warmup](warmup) | Small C/`ucontext` exercises done first |

Start with [thread-library](thread-library) if you want the main thing.
