find_package(Doxygen REQUIRED)

# Options to set when generating Doxyfile.docs
set(DOXYGEN_PROJECT_NAME "birthdays")
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/docs")
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md")
set(DOXYGEN_EXCLUDE_PATTERNS 
    "*/build/*" 
    "*/install/*"
    "*/python/*"
    )
set(DOXYGEN_GENERATE_LATEX NO)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_SOURCE_BROWSER YES)
set(DOXYGEN_FULL_SIDEBAR YES)

doxygen_add_docs(
    docs
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generating API documentation"
)
