project(kontrTask)
add_executable(kontrTask kontrTask.cpp kontrTask.report.md.in.txt)
target_link_libraries(kontrTask ${OpenCV_LIBS})

file(READ kontrTask.cpp cpp_source)
# prepare report md file
configure_file(kontrTask.report.md.in.txt ${CMAKE_CURRENT_BINARY_DIR}/kontrTask.report.md @ONLY)
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/kontrTask.report.md" "$<TARGET_FILE_DIR:${PROJECT_NAME}>")