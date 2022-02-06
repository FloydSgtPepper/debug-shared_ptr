# add a target to generate API documentation with Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    file(TO_CMAKE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/doxy/doxygen.in" DOXYGEN_IN)
    file(TO_CMAKE_PATH "${CMAKE_CURRENT_BINARY_DIR}/doc/doxyfile" DOXYFILE)
    set(doxyfile )

    configure_file(${DOXYGEN_IN} ${DOXYFILE} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc"
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html DESTINATION ../doc)
else()
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
endif()
