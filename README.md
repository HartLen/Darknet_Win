# Darknet_Win
static library of darknet in windows

## Modifications
1. Add third party header files into darknet/include, including pthread.h sched.h semaphore.h
2. Modify function what_time_is_it_now() in utils.c by commentting previous implementation and adding new implementation
3. Modify function sorta_shuffle() and shuffle() in utils.c by changing void* type into float* type
4. Modify struct list and data in darknet.h into linked_list and Data type to avoid the confict with c++ standard libraries
## Installation Guidlines
1. git clone https://github.com/HartLen/Darknet_Win
2. Place the project into your vs project and edit the CMakeLists.txt on line 15 with your directory path that contains the darknet project
3. Create build directory in the darknet directory and use cmake to generate vs project
4. Add the generated project into your vs project by adding darknet.vcxproj in build directory
