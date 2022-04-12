# Sample plugin

This is a simple pass example to illustrate how creating an out-of-tree pass works,
with an example slightly more complicated than a HelloWorld.

## Requirements

Requires LLVM 13, if you are using an apt-based distribution I recommend
following the instruction on LLVM's [dedicated page](https://apt.llvm.org/).

## Using Docker

### Pull from DockerHub

The latest image is available from DockerHub using `docker pull viroulep/midi-bidouille:latest`.

### Build from Dockerfile

You can use the Dockerfile provided to build the image with all the necessary dependencies for the tp.
Run `docker build -t midi-bidouille .` (you may obviously pick another name for the image).

### Using the image

The recommended way to work on the exercises is to mount the folder with the sources when running the docker container.
This way you can use your preferred text editor from the host machine, and use the docker only to compile the projects and run the tests.

To start an interactive session in a container, you may use the following command line:
``docker run -it -v `pwd`:/home/tp/sources -i viroulep/midi-bidouille /bin/bash`` (you need to replace `midi-bidouille` by the image name if you changed it).

The default user is `tp` and has sudo rights without password.

## Build

### From within the docker container

It should be easy enough to simply use a default cmake invocation:

```bash
mkdir build && cd build
cmake ..
make -j
```

### If you installed LLVM on your computer

If your installation isn't in a standard path, set `LLVM_DIR` to llvm's cmake integration:

```bash
mkdir build && cd build
cmake -DLLVM_DIR=/path/to/llvm-13/lib/cmake/llvm ..
make -j
```

## Running the thing

Get into the `build` folder.
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
