# C_eval

A demo C/C++ equivalent of eval(“function(arg1, arg2)”)

This implementation is based on [Example of Printing the ELF Symbol Table](https://docs.oracle.com/cd/E19683-01/817-0679/6mgfb878d/index.html)

# Preparation
You need to install gelf and libelf.

# Command

``` gcc main.c -std=c99 -g -l elf ; ./a.out ```

# TO_DO

* Add parameters.
