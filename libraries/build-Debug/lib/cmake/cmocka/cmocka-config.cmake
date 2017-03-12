get_filename_component(CMOCKA_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

if (EXISTS "${CMOCKA_CMAKE_DIR}/CMakeCache.txt")
    # In build tree
    include(${CMOCKA_CMAKE_DIR}/cmocka-build-tree-settings.cmake)
else()
    set(CMOCKA_INCLUDE_DIR /home/sudeep03799/New2/libraries/build-Debug/include)
endif()

set(CMOCKA_LIBRARY /home/sudeep03799/New2/libraries/build-Debug/lib/libcmocka.so)
set(CMOCKA_LIBRARIES /home/sudeep03799/New2/libraries/build-Debug/lib/libcmocka.so)
