# binary-ish-search

Code to experiment with various memory layouts for binary-ish-search.

This will probably expand to explore various kinds of O(log(n)) search operations.

The binary search function is written by hand instead of using the stdlib bsearch function to later explore the differences in disassembly of these functions.

## Usage

Both files are simple C programs with no external dependencies.

To compile and run:
```
gcc -O2 binary_search.c -o bs

gcc -O2 serialised_preorder_bst.c -o pre
```