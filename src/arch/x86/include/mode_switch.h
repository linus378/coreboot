/* SPDX-License-Identifier: GPL-2.0-only */

#include <stdint.h>

#if ENV_X86_64
/*
 * Assembly code that drops into protected mode and calls the function
 * specified as first argument, which must have been compiled for x86_32.
 * After the function returns it enters long mode again.
 * The function pointer destination must be below 4GiB in physical memory.
 *
 * The called function has 0-3 arguments and returns an int.
 */
int protected_mode_call_wrapper(uint32_t func_ptr,
				uint32_t opt_arg1,
				uint32_t opt_arg2,
				uint32_t opt_arg3);

/*
 * Drops into protected mode and calls the function, which must have been compiled for x86_32.
 * After the function returns it enters long mode again.
 * The function pointer destination must be below 4GiB in physical memory.
 *
 * The called function doesn't have arguments and returns an int.
 */
static inline int protected_mode_call(void *func)
{
	return protected_mode_call_wrapper((uintptr_t)func, 0, 0, 0);
}

/*
 * Drops into protected mode and calls the function, which must have been compiled for x86_32.
 * After the function returns it enters long mode again.
 * The function pointer destination must be below 4GiB in physical memory.
 * Only the lower 32bits of the argument are passed to the called function.
 *
 * The called function have one argument and returns an int.
 */
static inline int protected_mode_call_1arg(void *func, uint32_t arg1)
{
	return protected_mode_call_wrapper((uintptr_t)func, arg1, 0, 0);
}

/*
 * Drops into protected mode and calls the function, which must have been compiled for x86_32.
 * After the function returns it enters long mode again.
 * The function pointer destination must be below 4GiB in physical memory.
 * Only the lower 32bits of the argument are passed to the called function.
 *
 * The called function has two arguments and returns an int.
 */
static inline int protected_mode_call_2arg(void *func, uint32_t arg1, uint32_t arg2)
{
	return protected_mode_call_wrapper((uintptr_t)func, arg1, arg2, 0);
}

/*
 * Drops into protected mode and calls the function, which must have been compiled for x86_32.
 * After the function returns it enters long mode again.
 * The function pointer destination must be below 4GiB in physical memory.
 * Only the lower 32bits of the argument are passed to the called function.
 *
 * The called function has two arguments and returns an int.
 */
static inline int protected_mode_call_3arg(void *func, uint32_t arg1, uint32_t arg2,
					   uint32_t arg3)
{
	return protected_mode_call_wrapper((uintptr_t)func, arg1, arg2, arg3);
}
#else
static inline int protected_mode_call(void *func)
{
	int (*doit)(void) = func;

	return doit();
}

static inline int protected_mode_call_1arg(void *func, uint32_t arg1)
{
	int (*doit)(uint32_t arg1) = func;

	return doit(arg1);
}

static inline int protected_mode_call_2arg(void *func, uint32_t arg1, uint32_t arg2)
{
	int (*doit)(uint32_t arg1, uint32_t arg2) = func;

	return doit(arg1, arg2);
}

static inline int protected_mode_call_3arg(void *func, uint32_t arg1, uint32_t arg2,
					   uint32_t arg3)
{
	int (*doit)(uint32_t arg1, uint32_t arg2, uint32_t arg3) = func;

	return doit(arg1, arg2, arg3);
}
#endif
