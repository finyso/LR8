project(Task_2)

add_executable(Task_2 task.cpp source.cpp functions.h struc.h typedf.h)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
endif()