if(CMAKE_BUILD_TYPE STREQUAL "Release")
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS ${Qt5_DIR}/../../../bin)
    if(WINDEPLOYQT_EXECUTABLE)
        execute_process(
            COMMAND ${WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE:${PROJECT_NAME}>
            WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()
endif()