#
# usage:
# include(path/to/add_mutest.cmake RESULT_VARIABLE MUTEST)
# add_mutest(FILE test.cc DEPENDS rt system)
#

function(add_mutest)
  cmake_parse_arguments(mutest "" "FILE" "DEPENDS"  ${ARGN})

  get_filename_component(mutest_SOURCE ${mutest_FILE} NAME)
  get_filename_component(mutest_NAME ${mutest_FILE} NAME_WE)

  file(RELATIVE_PATH subdir ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
  set(CMakeFiles ${CMAKE_BINARY_DIR}/${subdir}${CMAKE_FILES_DIRECTORY})
  get_filename_component(MUTEST_DIR ${MUTEST} DIRECTORY)

  add_library(${mutest_NAME}obj OBJECT ${mutest_FILE})
  set_target_properties(${mutest_NAME}obj PROPERTIES COMPILE_DEFINITIONS "MUTEST")

  include_directories(${MUTEST_DIR})
  set(RUN_SRC ${CMakeFiles}/${mutest_NAME}.dir/run.c)
  set(RUN_OBJ ${CMakeFiles}/${mutest_NAME}obj.dir/${mutest_SOURCE}.o)
  add_custom_command(
    OUTPUT ${RUN_SRC}
    COMMAND ${MUTEST_DIR}/mkmutest
            ${MUTEST_DIR}/mutest.h ${RUN_OBJ} > ${RUN_SRC}
    DEPENDS ${mutest_FILE}
  )
  set_source_files_properties(${RUN_SRC} PROPERTIES GENERATED TRUE)

  add_executable(${mutest_NAME} $<TARGET_OBJECTS:${mutest_NAME}obj> ${RUN_SRC} ${MUTEST_DIR}/mutest.c)
  target_link_libraries(${mutest_NAME} ${mutest_DEPENDS})
  add_test(NAME ${mutest_NAME} COMMAND ${mutest_NAME})
endfunction(add_mutest)
