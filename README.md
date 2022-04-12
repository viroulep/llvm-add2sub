## Sample plugin

This is a simple pass example to illustrate how creating an out-of-tree pass works,
with an example slightly more complicated than a HelloWorld.

## Build

Requires LLVM 13, if you are using an apt-based distribution I recommend
following the instruction on LLVM's [dedicated page](https://apt.llvm.org/).

If your installation isn't in a standard path, set `LLVM_DIR` to llvm's cmake integration:
```bash
mkdir build && cd build
cmake -DLLVM_DIR=/path/to/llvm-13/lib/cmake/llvm ..
make
```

## Running the thing

The cmake creates an executable `opt_with_plugin` which automatically load the plugin;
you can use it to run the pass over `inputs/add_sub.ll` using either:
```bash
./opt_with_plugin -S -O1 ../inputs/add_sub.ll
```
(the pass is registered at the beginning of any optimization pipeline)

Or by invoking the pass on its own:
```bash
./opt_with_plugin -S -passes=add2sub ../inputs/add_sub.ll
```

You may also want to try the MBA pass by running it through opt:

```bash
./opt_with_plugin -S -passes=mba ../inputs/add_sub.ll
```
