#Generate the local Makefile

find_package(Threads)
add_penn_cloud_executable(httpServer httpServer.cc request.cc response.cc utils/utils.cc)
target_link_libraries(httpServer ${CMAKE_THREAD_LIBS_INIT})