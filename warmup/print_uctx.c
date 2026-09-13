/* Only works on x86 Linux systems */

#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#define MEM 64000
#include <stdio.h>
#include <ucontext.h>

static ucontext_t ctx[2];

static void f1(void) {
	puts("start f1");
	puts("finish f1");
	swapcontext(&ctx[1], &ctx[0]);
}

void print_mctx(mcontext_t mctx) {
	printf("gregs: ");
	for(int i = 0; i < __NGREG; i++) {
		printf("%llx, ", mctx.__gregs[i]);
	}
	printf("\n");

	printf("fpregs: "); 
	printf("%x, %x, %x, %x, %x, %x, %x, %x", 
		mctx.__fpregs->__cwd, mctx.__fpregs->__swd, 
		mctx.__fpregs->__ftw, mctx.__fpregs->__fop,
		mctx.__fpregs->__rip, mctx.__fpregs->__rdp,
		mctx.__fpregs->__mxcsr, mctx.__fpregs->__mxcr_mask);
	printf("... \n"); 
}

void print_ctx(ucontext_t *ctx) {
	printf("uc_link: %p\n", ctx->uc_link);
	printf("uc_stack.ss_sp: %p, uc_stack.ss_size: %ld, uc_stack.ss_flags: %d\n", 
		ctx->uc_stack.ss_sp, ctx->uc_stack.ss_size, ctx->uc_stack.ss_flags);
	print_mctx(ctx->uc_mcontext);
}

int main(void) {
	char st1[8192];

	/* Prepares ctx[1]. */
	getcontext(&ctx[1]);
	// Setup stack
	ctx[1].uc_stack.ss_sp = st1;
	ctx[1].uc_stack.ss_size = sizeof st1;
	// When ctx[1] ends swap to ctx[0]
	ctx[1].uc_link = &ctx[0];

	// ucontext_t *cpy = clone_ctx(&ctx[1]);
	print_ctx(&ctx[1]);

	makecontext(&ctx[1], f1, 0);
	print_ctx(&ctx[1]); // 11, 15, 16 gregs changed: RBX, RSP, RIP
	// RBX: Pointer to data in the DS segment
	// RSP: Stack pointer
	// RIP: Instruction pointer

	printf("Running orig context\n");
	swapcontext(&ctx[0], &ctx[1]);
	print_ctx(&ctx[1]); // 0: R8, 9: RSI, 10: RBP, 12: RDX, 14: RCX, 15: RSP, 16: RIP
	// RSI: Pointer to Data segment for string operations; ; source pointer for string operations
	// RBP: Pointer to Data on the stack
	// RDX: I/O pointer
	// RCX: Counter for string and loop operations 
	// RSP: Stack pointer
	// RIP: Instruction pointer

	// No changes in floating point registers because f1 doesn't do any flops
	return 0;
}
