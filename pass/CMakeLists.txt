add_llvm_pass_plugin(RegisterMyPlugin mba.cpp add2sub.cpp register.cpp)
configure_file(opt_with_plugin.in ${CMAKE_BINARY_DIR}/opt_with_plugin @ONLY)
