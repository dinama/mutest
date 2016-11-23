function(add_mutest)
  cmake_parse_arguments(mutest "" "FILE;MUTEST" "DEPENDS"  ${ARGN})

  get_filename_component(FNAME ${mutest_FILE} NAME)
  get_filename_component(TNAME ${mutest_FILE} NAME_WE)

  add_library(${TNAME}obj OBJECT ${mutest_FILE})
  set_target_properties(${TNAME}obj PROPERTIES COMPILE_DEFINITIONS "MUTEST")

  include_directories(${mutest_MUTEST})
  set(RUN_SRC ${CMAKE_SOURCE_DIR}/.build/tests/CMakeFiles/${TNAME}.dir/run.c)
  set(RUN_OBJ ${CMAKE_SOURCE_DIR}/.build/tests/CMakeFiles/${TNAME}obj.dir/${FNAME}.o)
  add_custom_command(
    OUTPUT ${RUN_SRC}
    COMMAND ${mutest_MUTEST}/mkmutest
            ${mutest_MUTEST}/mutest.h ${RUN_OBJ} > ${RUN_SRC}
    DEPENDS ${mutest_FILE}
  )
  set_source_files_properties(${RUN_SRC} PROPERTIES GENERATED TRUE)

  add_executable(${TNAME} $<TARGET_OBJECTS:${TNAME}obj> ${RUN_SRC} ${mutest_MUTEST}/mutest.c)
  target_link_libraries(${TNAME} ${mutest_DEPENDS})
  add_test(NAME ${TNAME} COMMAND ${TNAME})
endfunction(add_mutest)
