# Backtracking via Context Rollback

A demonstration of using `ucontext` (raw context save/restore, no threads
involved) to implement backtracking search **without an explicit loop** —
failing an assertion rewinds execution to retry the next candidate,
instead of returning an error.

## How it works

`conjecture(len, options, sz, fn)` saves the current execution context
with `getcontext`, then calls `fn` on the first element of `options`.
`assert(b)` checks a condition; if it is false, it calls `setcontext` to
jump back to the point right after `getcontext` was saved — which
re-runs the "advance to next element" step and calls `fn` again on the
*next* element. Each failed assertion is effectively "try the next
candidate."

## Example

```c
int mynums[] = {11, 23, 42, 39, 55};
conjecture(5, mynums, sizeof(int), &app);
```

`app` only accepts numbers under 40, then squares them if they are
*not* prime (via `nested`, which asserts `!is_prime(i)`):

| i | passes `is_lt_40`? | passes `!is_prime`? | result |
|---|---|---|---|
| 11 | yes | no (11 is prime) | rolled back |
| 23 | yes | no (23 is prime) | rolled back |
| 42 | no | — | rolled back |
| 39 | yes | yes (39 = 3×13) | prints `1521` (39²) |
| 55 | no | — | rolled back |

```bash
gcc -D_XOPEN_SOURCE=600 -o rollback main.c
./rollback
```

Verified: this actually prints a single line, `1521`.
