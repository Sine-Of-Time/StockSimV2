# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("HelloWorld")

find_package(curl CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
#find_package(wxWidgets CONFIG REQUIRED)





# Add source to this project's executable.
add_executable (HelloWorld "helloWorld.cpp" "curl_function.cpp" "curl_function.h" "user.h" "user.cpp" "stock.cpp" "stock.h" "Company.cpp" "Company.h")

target_link_libraries(HelloWorld PRIVATE CURL::libcurl)
target_link_libraries(HelloWorld PRIVATE JsonCpp::JsonCpp)
#target_link_libraries(HelloWorld PRIVATE wxWidgets::wxWidgets)

#/target_link_libraries(HelloWorld PRIVATE wxgtk)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HelloWorld PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
