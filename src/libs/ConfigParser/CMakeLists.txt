# ConfigParser
################################################################################
add_library( ConfigParser ConfigParser.cpp)
target_link_libraries(ConfigParser Orientation tinyxml2)
