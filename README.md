# MarkSweep
A simple C++ implementation of mark-and-sweep garbage collector

## Implementation

Class `State` is responsible for creating new objects and garbage collection. When an object is created, its mark bit is set to 0(false). Class `VM` simulates a virtual machine which executes opcodes.

Mark-and-Sweep Algorithm is consist of two phases:

### Mark Phase
In this phase, we set the marked bit for all the objects which the virtual machine can refer to to 1(true).

### Sweep Phase
It clears the heap memory for all the unreachable objects. All those objects whose marked value is set to false are cleared from the heap memory, for all other objects (reachable objects) the marked bit is set to false.
Now the mark value for all the reachable objects is set to false, since we will run the algorithm (if required) and again we will go through the mark phase to mark all the reachable objects.

The mark-and-sweep algorithm is called a tracing garbage collector because is traces out the entire collection of objects that are directly or indirectly accessible by the program.

## References

1. [garbage-collector](http://journal.stuffwithstuff.com/2013/12/08/babys-first-garbage-collector/) and [code on GitHub](https://github.com/munificent/mark-sweep)
2. [generational garbage collection](http://airtrack.me/posts/2013/11/17/初级分代GC/) and [luna on GitHub](https://github.com/airtrack/luna)
