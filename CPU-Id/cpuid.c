/*
 * cpuid.c: Query x86 / x64 processor details, across operating systems.
 * Craig J Perry, <craigp84@gmail.com>
 *
 * If we need to query CPU details of hosts, there are a few approaches
 * we can take:
 *
 *   On Linux we can parse the file /proc/cpuinfo
 *   On MacOS we can parse the output of the "sysctl machdep.cpu" command
 *   On other BSDs we can parse the output of the "sysctl hw" command
 * 
 * And so on. All these operating systems expose a similar syscall(2)
 * which makes portability even easier. Until, we throw Windows into
 * the mix.
 *
 * Another method is to use the cpuid instruction in the x86 instruction
 * set, which is the approach taken here.
 *
 * Please note, this code uses syntax only usable with the GCC compiler
 * toolchain. This is due to the need for assembly language to invoke
 * the cpuid instruction.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "cpuid.h"

int main(int argc, char *argv[])
{
	unsigned int *cpu = read_cpu();
	if(-1 == *cpu)
		/* BUG: Leaking *cpu, however error() results in termination. */
		error("Failed to read CPU.");
	printf("Processor:\t%d\n", read_field(cpu, PROCESSOR) >> 12);
	printf("Model Number:\t%d\n", read_field(cpu, MODEL_NUMBER) >> 4);
	printf("Extended Model:\t%d\n", read_field(cpu, EXT_MODEL) >> 16);
	printf("Family Number:\t%d\n", read_field(cpu, FAMILY_NUMBER) >> 8);
	printf("Stepping:\t%d\n", read_field(cpu, STEPPING_NUMBER));
	free(cpu);

	return EXIT_SUCCESS;
}

unsigned int * read_cpu()
{
	unsigned int *cpuid = calloc(1, sizeof *cpuid); /* calloc for init to 0 */
	if(NULL == cpuid)
		error("Failed to reserve memory for results.");
	__asm__ __volatile__ ("cpuid": "=a" (*cpuid) : "a" (FUNC_GET_DETAIL));
	return cpuid;
}

unsigned int read_field(const unsigned int *cpu, int bitmask)
{
	unsigned int field = *cpu;
	field &= bitmask;
	return field;
}

