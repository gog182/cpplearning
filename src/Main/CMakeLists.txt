# Add executable that is built from the source files
add_executable (Main.exe Main.cpp)

# Link the executable to the libraries. 
target_link_libraries (Main.exe LINK_PUBLIC Images)