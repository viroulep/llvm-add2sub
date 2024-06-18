## Add2sub

This is a simple pass example to illustrate how creating an out-of-tree pass works,
with an example slightly more complicated than a HelloWorld.

It was used as an example in an introduction talk to LLVM.

TODO: add a link to the aforementioned talk

## Build

Requires LLVM 15, if you are using an apt-based distribution I recommend
following the instruction on LLVM's [dedicated page](https://apt.llvm.org/).

If your installation isn't in a standard path, set `LLVM_DIR` to llvm's cmake integration:
```bash
mkdir build && cd build
cmake -DLLVM_DIR=/path/to/llvm-13/lib/cmake/llvm ..
make
```

## Running the thing

The cmake creates an executable `opt_add2sub` which automatically load the plugin;
you can use it to run the pass over `inputs/add.ll` using either:
```bash
./opt_add2sub -S -O1 ../inputs/add.ll
```
(the pass is registered at the beginning of any optimization pipeline)

Or by invoking the pass on its own:
```bash
./opt_add2sub -S -passes=add2sub ../inputs/add.ll
```
