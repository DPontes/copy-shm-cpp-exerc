# OWN NOTES

The work currently done - in the short available time that I had - consists of taking the implementations that have to do with memory manipulation:

```
// Create a shared memory object.
shared_memory_object shm(create_only, "MySharedMemory", read_write);
// Set size
shm.truncate(sizeof(Image));
// Map the whole shared memory in this process
mapped_region region(shm, read_write);
// Get the address of the mapped region
void* addr = region.get_address();
```

and place these in a class called `Memory`, so that the code in the `main` function becomes:

- more readable,
- more testable,
- easily expendable

At this point, only the implementation and usage of a `Memory` class for each file was achieved correctly (*by correctly I mean it compiles and I can run both executables without any coredump occurring*).

The next steps would be (given the time):
- Create a Memory library (`memory.hpp` and `memory.cpp`) to be used in the application (*partially implemented in commit `0d2822c` but not yet concluded*)
- Alter the original `Memory` class to have two child classes, where one would be responsible to create the shared object and the other to use (open) said object.
- Investigate the possibility of using `templates` so that the class could be used with other types of objects (and not just the `Image` type)

Things I've considered but not yet figured out ow to do:
- Unit testing using GTest (and GMock)
- Better implementation of the `mutex` process to better account for different (and corner-case) scenarios

# Take it to production

Can you turn this barely working prototype to a production-ready set of libraries?

## Introduction

This exercise/case/task is meant to evaluate potential team members in some recruitment process
I am probably involved in.
There is no right or wrong solution and the exercise is purposefully very open-ended.
At the same time, the domain is very relevant to what the team actually works with, i.e. interprocess communication.

Specifically, in our team we are often tasked to process data and transfer them from one process to another,
while code we write remains:

* Readable
* Maintainable
* Reusable
* Testable
* Performant

## The task

The team wants to create one or more libraries to handle the communication and necessary signaling between processes.
We have written a simple POC based on the
[Anonymous mutex example](https://www.boost.org/doc/libs/1_77_0/doc/html/interprocess/synchronization_mechanisms.html#interprocess.synchronization_mechanisms.mutexes.mutexes_anonymous_example)
found in the Boost library. It consists of the following files:
* [data_creator_writer_shm.cpp](example/data_creator_writer_shm.cpp)
  * Creates a shared memory "channel" and writes some data
  * Waits until some other process has changed the value (incremented by `1`) of the said data
* [data_reader_writer_shm.cpp](example/data_reader_writer_shm.cpp)
  * Reads an already existing shared memory "channel" and increments the value of the shared content by `1`
* [shared_data.h](example/shared_data.h)
  * The data structure to share between the two processes

It is up to you, to create a solution of high-enough quality that will handle the interprocess communication. The idea is that we end up with one or more libraries we can reuse.

Some ideas on what your libraries can support include:
* Transferring many kinds of images with different dimensions
* Waiting until new data is written to shared memory by another process

Sounds a bit vague? Well, it is! We expect you to get in touch if you would like to discuss further.

## Things to keep in mind

* You may partly or entirely rewrite the existing code.
* There are no "right" or "wrong" solutions. The goal is to understand how you work.
* Implement this as closely as you would in an industrial project, we want to see your style and craftsmanship.
  * Within reason of course. Feel free to get in touch if in doubt.
* You are allowed to use any library but please make sure that we can also compile your project. We suggest Boost.Interprocess that's already included with the project.
* Please ensure your project works on Linux. Having it work on Windows is nice, but not a priority.

## Please don't fork

If you want to work on this, please copy/clone this repository, push it to your own remote and then send me a link.
Creating a fork and putting a solution there may spoil the fun for others. 😇
