# ParallaxEdu2015-Ex1
This repository contains first exercise and its solution for Parallax Education Day 2015. In addition, it also consists of a test program to test your environment setup. The details are given below.

## Requirements

1. An x86_64 CPU
2. Preferably a Linux OS 
3. [Git](http://git-scm.com/downloads)
4. [Docker](https://docs.docker.com/installation/)

### Environment Setup

The exercise uses

1. [OpenCL 1.2](https://www.khronos.org/opencl/),
2. [Git](http://git-scm.com/), and
3. [Cmake](http://www.cmake.org/).

You can install these components independently on your own, or use a docker image which has all the necessary components included. The following steps assumes that you are using the docker image.

* To use the docker image, [Docker](https://docs.docker.com/installation/) needs to be installed. Start docker using terminal in linux based systems or boot2docker in non-linux based systems. When running boot2docker, a terminal window pops up.
* To clone this repository in your workspace run the following command. Here it is assumed to be your home directory.
```bash
$ git clone https://github.com/skanur/ParallaxEdu2015-Ex1.git
```
* To test the docker image, run to see gcc installed in the docker image. Type the following window in the terminal (In Linux systems, docker runs as priviledged user. So you might need to use `sudo`) 
```bash
$ docker run -ti --rm wictory/parallax_edu gcc --version
```
* To run this exercise you need to bind your current directory to docker image's home directory. Navigate to the repository in your host machine. Once inside, run the following command in terminal to **enter inside** the docker image. 
```bash
$ docker run -ti --rm -v $PWD:/src  wictory/parallax_edu
```

### Environment Verification
You can test OpenCL and Cmake installation in the docker image by running the following commands **inside** docker image.

#### Run Test Program
Navigate to Test directory of this repository and then run
```bash
$ cd /src/ParallaxEdu2015-Ex1/Test
Test]$ mkdir -p build && cd build && cmake .. && make && ./Test
```

#### Run Exercise
Navigate to Exercise directory of this repository and then run
```bash
cd /src/ParallaxEdu2015-Ex1/Exercise
Exercise]$ mkdir -p build && cd build && cmake .. && make && ./Matrix
```

#### Run Solution
Navigate to Solution directory of this repository and then run
```bash
cd /src/ParallaxEdu2015-Ex1/Solution
Solution]$ mkdir -p build && cd build && cmake .. && make && ./Matrix
```

### Development and compilation
To write/edit the code, use your favorite text editor. The changes should be reflected inside the docker image. Compile the project **inside** docker image by using instructions given above.

