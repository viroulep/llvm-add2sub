add_llvm_pass_plugin(RegisterAdd2Sub add2sub.cpp)
configure_file(opt_add2sub.in ${CMAKE_BINARY_DIR}/opt_add2sub @ONLY)
