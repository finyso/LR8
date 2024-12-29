project(Task_1)

add_executable(Task_1 task.cpp source.cpp functions.h struc.h)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
endif()