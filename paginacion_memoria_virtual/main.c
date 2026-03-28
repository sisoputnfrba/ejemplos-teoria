#include <unistd.h>
#include <locale.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>

#define PAGEMAP_ENTRY_SIZE      8
#define PAGE_PRESENT            (1ULL<<63)
#define PAGE_SWAPPED            (1ULL<<62)
#define PFN_MASK                ((1ULL << 55) - 1)

#define ERROR                   ((uint64_t)-1)
#define PAGE_NOT_PRESENT        ((uint64_t)-2)
#define PAGE_IN_SWAP            ((uint64_t)-3)

int globalInicializada = 73;        // Global inicializada (.data)
int globalNoInicializada;           // Global no inicializada (.bss)
char* literal = "constante";        // Cadena literal (.rodata)

int pageSizeExponent;
long pages;
long pageSize;

bool hasPermission = false;

void printPointer(const char* str, void* ptr);
void printHumanSize(uint64_t bytes);
uint64_t getFrame(void* vaddr);

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "es_AR.UTF-8");

    pid_t pid = getpid();
    printf("PID: %d\n", pid);
    printf("\n");

    pages = sysconf(_SC_PHYS_PAGES);
    if (pages == -1) {
        printf("sysconf() retornó '%s'\n", strerror(errno));
        return 1;
    }

    pageSize = sysconf(_SC_PAGESIZE);
    if (pageSize == -1) {
        printf("sysconf() retornó '%s'\n", strerror(errno));
        return 1;
    }

    pageSizeExponent = __builtin_ctz(pageSize);

    printf("La memoria física está dividida en %'ld frames de %'ld (2^%d) bytes cada uno.\n", pages, pageSize, pageSizeExponent);
    printf("\n");

    void* heapAddress = malloc(sizeof(int));
    int f = open("Makefile", O_RDONLY);
    int g = open("Makefile", O_RDWR);
    if (f == -1 || g == -1) {
        perror("open");
        return 1;
    }

    struct stat st;
    if (fstat(f, &st) == -1) {
        perror("fstat");
        close(f);
        return 1;
    }

    if (fstat(g, &st) == -1) {
        perror("fstat");
        close(g);
        return 1;
    }

    size_t size = st.st_size;
    void *mapReadOnly = mmap(NULL, size, PROT_READ, MAP_PRIVATE, f, 0);
    if (mapReadOnly == MAP_FAILED) {
        perror("mmap");
        close(f);
        return 1;
    }

    void *mapWriteOnly = mmap(NULL, size, PROT_READ, MAP_PRIVATE, g, 0);
    if (mapWriteOnly == MAP_FAILED) {
        perror("mmap");
        close(g);
        return 1;
    }

    close(f);
    close(g);
    volatile char c = *((char*) mapReadOnly);    // Leemos algo para que el SO cargue de hecho el archivo a memoria
    c = *((char*) mapWriteOnly);   // Leemos algo para que el SO cargue de hecho el archivo a memoria



    printPointer("Variable en el stack                  ", (void*) &pid);
    puts("(...)");
    printPointer("'Makefile' mapeado a memoria (read)   ", mapReadOnly);
    printPointer("'Makefile' mapeado a memoria (r+w)    ", mapWriteOnly);
    printPointer("Función de librería compartida        ", (void*) printf);
    puts("(...)");
    printPointer("Variable en la heap                   ", heapAddress);
    printPointer("Global inicializada                   ", (void*) &globalInicializada);
    printPointer("Global no inicializada                ", (void*) &globalNoInicializada);
    printPointer("String literal (\"string literal\")     ", (void*) literal);
    printPointer("Función del programa (printPointer)   ", (void*) printPointer);

    free(heapAddress);
    munmap(mapReadOnly, size);
    munmap(mapWriteOnly, size);

    if (!hasPermission)
        puts("\n[ El programa no obtuvo los permisos requeridos para mostrar los frames físicos. ]");

    if (argc > 1)
        if (strcmp(argv[1], "--wait") == 0 || strcmp(argv[1], "-w") == 0)
            //puts("\n\nEsperando... (los números de frame no se están actualizando)");
            getchar();

    return 0;
}

void printPointer(const char* str, void* ptr) {
    uintptr_t addr   = (uintptr_t) ptr;
    uintptr_t offset = addr & (pageSize - 1);
    uintptr_t base   = addr - offset;
    uintptr_t page   = addr >> pageSizeExponent;

    printf("%s:\t%p (%p + 0x%lx)\t\tpágina %'" PRIuPTR,
           str, ptr, (void*) base, (unsigned long) offset, page);

    uint64_t pfn = getFrame(ptr);
    if (pfn == 0);
    else if (pfn == ERROR)
        printf(" [Error]");
    else if (pfn == PAGE_NOT_PRESENT)
        printf(" [Página no presente]");
    else if (pfn == PAGE_IN_SWAP)
        printf(" [Página en swap]");
    else {
        printf("  ->  frame %'" PRIu64 " (0x%" PRIx64 ")", pfn, pfn);
        hasPermission = true;
    }
    puts("");
}

void printHumanSize(uint64_t bytes) {
    const char *units[] = {"B", "KiB", "MiB", "GiB", "TiB", "PiB"};
    double size = (double)bytes;
    int unit = 0;

    while (size >= 1024.0 && unit < 5) {
        size /= 1024.0;
        unit++;
    }
    printf("%.2f %s", size, units[unit]);
}

// Source: https://fivelinesofcode.blogspot.com/2014/03/how-to-translate-virtual-to-physical.html
// Docu: https://www.kernel.org/doc/Documentation/vm/pagemap.txt
uint64_t getFrame(void* vaddr) {
    const char *path = "/proc/self/pagemap";
    FILE *f = fopen(path, "rb");
    if (!f) {
        perror("fopen");
        return ERROR;
    }

    uintptr_t virt_addr = (uintptr_t)vaddr;
    off_t file_offset = ((uint64_t)virt_addr / pageSize) * PAGEMAP_ENTRY_SIZE;
    if (fseeko(f, file_offset, SEEK_SET) != 0) {
        perror("fseeko");
        fclose(f);
        return ERROR;
    }

    unsigned char buf[PAGEMAP_ENTRY_SIZE];
    if (fread(buf, 1, PAGEMAP_ENTRY_SIZE, f) != PAGEMAP_ENTRY_SIZE) {
        perror("fread");
        fclose(f);
        return ERROR;
    }
    fclose(f);

    uint64_t entry = 0;
    for (size_t i = 0; i < sizeof(uint64_t); i++)
        entry |= ((uint64_t)buf[i]) << (8 * i);

    if (entry & PAGE_SWAPPED)
        return PAGE_IN_SWAP;

    if (!(entry & PAGE_PRESENT))
        return PAGE_NOT_PRESENT;

    return entry & PFN_MASK;
}
