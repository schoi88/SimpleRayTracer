This is a RayTracing project I have been working on using the popular textbooks in 
the Ray Tracing in One Weekend series by Peter Shirley, Trevor David Black, and
Steve Hollasch.

There are slight modifications so that I may learn how to use cmake and incorporate
some practices I have learned from my time in Operating Systems mostly to make this
program use multithreaded programming in a memory safe manner.

This project does use cmake to run so to build and execute the program:
1. have cmake and build dependencies installed along with c/c++ compiler (I am working
    on this project using wsl so I used the gnu compiler)
2. create a build directory using "cmake -B build"
3. build/compile the program using "cmake --build build"
4. run the executable using "./build/RayTrace > image.ppm"

other approaches to compile and execute the program are also okay, I just wanted to
learn cmake.

-Sean Choi

citation:
"Ray Tracing in One Weekend." raytracing.github.io/books/RayTracingInOneWeekend.html
(accessed 10. 30, 2025)