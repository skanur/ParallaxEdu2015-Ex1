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
2. [Git](http://git-scm.com/)
3. [Cmake](http://www.cmake.org/)
4. GCC with c++11 support, and
5. Your favorite text editor

You can install these components independently on your own, or use a docker image which has all the necessary components included. The following steps assumes that you are using the docker image.

1. To use the docker image, [Docker](https://docs.docker.com/installation/) needs to be installed. Start docker using terminal in linux based systems or boot2docker in non-linux based systems. When running boot2docker, a terminal window pops up.
2. Navigate to home directory
  * Under boot2docker in *Windows*, your home directory could be in /c/Users/[your.username]
  * Under boot2docker in *MacOsX*, your home directory could be in /Users/[your.username]
3. To run this exercise, we make a new directory and navigate into that

```bash
$ cd $HOME #OS Specific. Check step 2
$ mkdir -p parallax_education_day
$ cd parallax_education_day
$ git clone https://github.com/skanur/ParallaxEdu2015-Ex1.git
$ docker run -ti --rm -v $PWD:/source wictory/parallax_edu gcc --version # Test your docker image
$ docker run -ti --rm -v $PWD:/source  wictory/parallax_edu # Enter the container
```

### Environment Verification
You can test OpenCL and Cmake installation in the docker image by running the following commands **inside** docker image.

#### Compile and run the Test Program
Check the environment setup by compiling and running Test program.If run successfully, it should display some platform and device information.
```bash
$ cd /source/ParallaxEdu2015-Ex1/Test
Test]$ mkdir -p build && cd build && cmake .. && make && ./Test
```

#### Compile and run the Exercise
Navigate to Exercise directory of this repository and then run
```bash
cd /source/ParallaxEdu2015-Ex1/Exercise
Exercise]$ mkdir -p build && cd build && cmake .. && make && ./Matrix
```

#### Compile and run the Solution
Navigate to Solution directory of this repository and then run
```bash
cd /source/ParallaxEdu2015-Ex1/Solution
Solution]$ mkdir -p build && cd build && cmake .. && make && ./Matrix
```

### Development and compilation
To write/edit the code, use your favorite text editor. The changes should be reflected inside the docker image. Compile the project **inside** docker image by using instructions given above.
