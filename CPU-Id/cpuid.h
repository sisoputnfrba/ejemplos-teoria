/* cpuid "functions" (operands) */
#define FUNC_GET_DETAIL	0x0000001


/* Bit Masks */
#define STEPPING_NUMBER 0x000F
#define MODEL_NUMBER	0x00F0
#define FAMILY_NUMBER	0x0F00
#define PROCESSOR	0x3000
#define EXT_MODEL      0xF0000


/* Function Prototypes */
unsigned int * read_cpu();
unsigned int read_field();


/* Helper Functions */
void error(char *message)
{
	fprintf(stderr, "ERROR: %s\n", message);
	exit(1);
}

