#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "elf.h"
#include "util.h"

static char * strtab = NULL;
static char * shstrtab = NULL;
static Elf32_Sym * symbols = NULL;
static Elf32_Shdr * sectionHeaders = NULL;
static Elf32_Phdr * programHeaders = NULL;
static Elf32_Ehdr elfHeader = {};
static int initialized = 0;
unsigned int nSymbols = 0;
static FILE * elfFile = NULL;
unsigned char * elfContents = NULL;

#ifdef _MSC_VER
#define DEBUG_MSG(fmt, ...) // fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_MSG(fmt, ...) // fprintf(stderr, fmt, ##__VA_ARGS__)
#endif

unsigned char * OpenAndReadWholeFile(const char * filename) {
    FILE * file = fopen(filename, "rb");
    if (file == NULL) {
        FATAL_ERROR("Unable to open file \"%s\" for reading\n", filename);
    }
    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char * ret = malloc(fsize);
    if (fread(ret, 1, fsize, file) != fsize) {
        fclose(file);
        FATAL_ERROR("Error reading file \"%s\"\n", filename);
    };
    fclose(file);
    return ret;
}

unsigned char * ReadWholeFile(FILE * file) {
    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char * ret = malloc(fsize);
    if (fread(ret, 1, fsize, file) != fsize) {
        FATAL_ERROR("Error reading file");
    };
    return ret;
}

static void ReadElfHeader(void)
{
    DEBUG_MSG("ReadElfHeader\n");

    elfHeader = *(Elf32_Ehdr *)elfContents;
    if (memcmp(elfHeader.e_ident, ELFMAG, SELFMAG) != 0) {
        FATAL_ERROR("malformed ELF header\n");
    }
    if (elfHeader.e_ident[EI_CLASS] != ELFCLASS32) {
        FATAL_ERROR("%s elf detected (this utility only supports 32-bit)\n", elfHeader.e_ident[EI_CLASS] == ELFCLASS64 ? "64-bit" : "unknown");
    }
    initialized = 1;
}

static void ReadProgramHeaders(void)
{
    DEBUG_MSG("ReadProgramHeaders\n");

    if (!initialized) {
        FATAL_ERROR("ELF not initialized\n");
    }
    programHeaders = (Elf32_Phdr *)(elfContents + elfHeader.e_phoff);
}

static void ReadSectionHeaders(void)
{
    DEBUG_MSG("ReadSectionHeaders\n");

    if (!initialized) {
        FATAL_ERROR("ELF not initialized\n");
    }
    sectionHeaders = (Elf32_Shdr *)(elfContents + elfHeader.e_shoff);
}

static void ReadStringTables(void)
{
    DEBUG_MSG("ReadStringTables\n");

    if (sectionHeaders == NULL) {
        FATAL_ERROR("need to read section headers first\n");
    }
    shstrtab = (char *)elfContents + sectionHeaders[elfHeader.e_shstrndx].sh_offset;
    for (int i = 0; i < elfHeader.e_shnum; i++)
    {
        if (i == elfHeader.e_shstrndx) continue;
        if (sectionHeaders[i].sh_type == SHT_STRTAB) {
            strtab = (char *)elfContents + sectionHeaders[i].sh_offset;
            break;
        }
    }
    if (strtab == NULL) {
        FATAL_ERROR("failed to find strings table\n");
    }
}

static int symcmp(const void * a, const void * b)
{
    const Elf32_Sym * aa = (const Elf32_Sym *)a;
    const Elf32_Sym * bb = (const Elf32_Sym *)b;
    return aa->st_value > bb->st_value;
}

static void ReadSymbols(void)
{
    DEBUG_MSG("ReadSymbols\n");

    if (sectionHeaders == NULL) {
        FATAL_ERROR("need to read section headers first\n");
    }
    for (int i = 0; i < elfHeader.e_shnum; i++)
    {
        if (sectionHeaders[i].sh_type == SHT_SYMTAB) {
            nSymbols = sectionHeaders[i].sh_size / sizeof(Elf32_Sym);
            DEBUG_MSG("nSymbols: %d\n", nSymbols);
            symbols = malloc(sectionHeaders[i].sh_size);
            if (symbols == NULL) {
                FATAL_ERROR("failed to allocate symbol table\n");
            }
            memcpy(symbols, elfContents + sectionHeaders[i].sh_offset, sectionHeaders[i].sh_size);
            msort(symbols, nSymbols, sizeof(Elf32_Sym), symcmp);
            return;
        }
    }

    FATAL_ERROR("failed to find symbol table\n");
}

Elf32_Sym * GetSymbol(unsigned int st_idx)
{
    DEBUG_MSG("GetSymbol\n");

    if (symbols == NULL) {
        FATAL_ERROR("must read symbols first\n");
    }
    if (st_idx >= nSymbols) {
        FATAL_ERROR("symbol index out of array\n");
    }
    return &symbols[st_idx];
}

Elf32_Sym * GetSymbolByName(const char * name)
{
    DEBUG_MSG("GetSymbolByName\n");

    if (symbols == NULL) {
        FATAL_ERROR("must read symbols first\n");
    }
    for (unsigned int i = 0; i < nSymbols; i++) {
        const char *checkName = strtab + symbols[i].st_name;
        if (strcmp(checkName, name) == 0) {
            return &symbols[i];
        }
    }
    return NULL;
}

Elf32_Shdr * GetSectionHeader(unsigned int sh_idx)
{
    DEBUG_MSG("GetSectionHeader\n");

    if (sh_idx >= SHN_LORESERVE) {  // reserved indices
        return NULL;
    }
    if (sh_idx >= elfHeader.e_shnum) {
        FATAL_ERROR("section index out of array\n");
    }
    return &sectionHeaders[sh_idx];
}

Elf32_Shdr * GetSectionHeaderByName(const char * shname)
{
    DEBUG_MSG("GetSectionHeader\n");

    for (int sh_idx = 0; sh_idx < elfHeader.e_shnum; sh_idx++) {
        if (strcmp(&shstrtab[sectionHeaders[sh_idx].sh_name], shname) == 0)
            return &sectionHeaders[sh_idx];
    }
    return NULL;
}

Elf32_Phdr * GetProgramHeader(unsigned int ph_idx)
{
    DEBUG_MSG("GetProgramHeader\n");

    if (ph_idx >= elfHeader.e_phnum) {
        FATAL_ERROR("program index out of array\n");
    }
    return &programHeaders[ph_idx];
}

const char * GetSymbolName(Elf32_Sym * symbol)
{
    DEBUG_MSG("GetSymbolName\n");

    if (strtab == NULL) {
        FATAL_ERROR("must read strings first\n");
    }
    return strtab + symbol->st_name;
}

const char * GetSectionName(Elf32_Shdr * section)
{
    DEBUG_MSG("GetSectionName\n");

    if (shstrtab == NULL) {
        FATAL_ERROR("must read strings first\n");
    }
    return shstrtab + section->sh_name;
}

uint32_t GetEntryPoint(void)
{
    return elfHeader.e_entry;
}

int GetSectionHeaderCount(void)
{
    return elfHeader.e_shnum;
}

void InitElf(FILE * file)
{
    elfFile = file;

    elfContents = ReadWholeFile(file);
    ReadElfHeader();
    ReadProgramHeaders();
    ReadSectionHeaders();
    ReadStringTables();
    ReadSymbols();
}

void DestroyResources(void)
{
    DEBUG_MSG("DestroyResources\n");

    strtab = NULL;
    shstrtab = NULL;
    programHeaders = NULL;
    sectionHeaders = NULL;
    free(symbols);
    symbols = NULL;
    nSymbols = 0;
    elfHeader = (Elf32_Ehdr){};
    initialized = 0;
    free(elfContents);
    elfContents = NULL;
    elfFile = NULL;
}
