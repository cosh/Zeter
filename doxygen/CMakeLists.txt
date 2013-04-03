#-- Add an Option to toggle the generation of the API documentation
option(BUILD_DOCUMENTATION "Use Doxygen to create the HTML based API documentation" ON)

if(BUILD_DOCUMENTATION)
  include (Documentation)

  FIND_PACKAGE(Doxygen)
  if (NOT DOXYGEN_FOUND)
    message(FATAL_ERROR 
      "Doxygen is needed to build the documentation. Please install it correctly")
  endif()

  #
  # Configure the script and the doxyfile, then add target
  #
  if(NOT DOT_PATH)
    get_filename_component(DOT_PATH ${DOT} PATH)
  endif()

  #-- Configure the Template Doxyfile for our specific project
  configure_file(Doxyfile.in 
                 ${ZETER_BINARY_DIR}/doxygen/Doxyfile  @ONLY IMMEDIATE)
  #-- Add a custom target to run Doxygen when ever the project is built
  add_custom_target (Docs_Zeter 
  	COMMAND ${DOXYGEN_EXECUTABLE} ${ZETER_BINARY_DIR}/doxygen/Doxyfile
  	SOURCES ${ZETER_BINARY_DIR}/doxygen/Doxyfile)
  # IF you do NOT want the documentation to be generated EVERY time you build the project
  # then leave out the 'ALL' keyword from the above command.
endif()
