#include<stdio.h>
#include<stdlib.h>
#include<elf.h>
#include<libelf.h>
#include<unistd.h>
#include<fcntl.h>
#include<gelf.h>
#include<string.h>

void my_fun()
{
    int a = 19;
    printf("my_fun is excute, a is %d \n", a);
}

void my_fun2()
{
    printf("my_fun2 is excute\n");
    return;
}

void my_fun3()
{
    return;
}

void excute_fun(char *program_name, char *function_name)
{
    int i, count;
    Elf32_Ehdr *ehdr;
    GElf_Shdr   shdr;
    Elf *elf;
    Elf_Scn *scn = NULL;
    Elf_Data *data;
    int flag = 0;
    int fd = open(program_name, O_RDONLY);
    if(fd < 0) {
        perror("open\n");
        exit(1);
    }
    if(elf_version(EV_CURRENT) == EV_NONE) {
        perror("elf_version == EV_NONE");
        exit(1);
    }
    elf = elf_begin(fd, ELF_C_READ, (Elf *) NULL);
    if(!elf) {
        perror("elf error\n");
        exit(1);
    }
    /* Elf32_Off e_shoff; */
    /* if ((ehdr = elf32_getehdr(elf)) != 0) { */
    /*     e_shoff = ehdr->e_shoff; */
    /* } */
    /* scn = elf_getscn(elf, 0); */
    /* printf("e_shoff is %u\n", e_shoff); */
    /* scn += e_shoff; */
    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_SYMTAB) {
            /* found a symbol table. */
            break;
        }
    }
    data = elf_getdata(scn, NULL);
    if(!shdr.sh_entsize)
        count = 0;
    else
        count = shdr.sh_size / shdr.sh_entsize;
    for (i = 0; i < count; ++i) {
        GElf_Sym sym;
        gelf_getsym(data, i, &sym);
        char *sym_name = elf_strptr(elf, shdr.sh_link, sym.st_name);
        if(sym_name != NULL && sym_name[0] != '_' && sym_name[0] != '\0' && sym_name[0] != ' ' && sym.st_value != 0)
        {
            /* printf("sym_name is %s\n", sym_name); */
            /* printf("%s = %X\n", elf_strptr(elf, shdr.sh_link, sym.st_name), sym.st_value); */
            if(!strcmp(sym_name, function_name)) {
                void (*fun)(void) = (void*)sym.st_value;
                (*fun)();
                flag = 1;
            }
        }
    }
    if(!flag)
        printf("can not find this function\n");

    elf_end(elf);
    close(fd);
}

int main(int argc, char *argv[])
{
    char *input = (char*)malloc(100);
    for(;;) {
        printf("input function_name to excute: ");
        scanf("%s", input);
        excute_fun(argv[0], input);
        memset(input, 0, sizeof(input));
        printf("\n");
    }
    free(input);
    return 0;
}
