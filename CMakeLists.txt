cmake_minimum_required(VERSION 3.26.0)
project(ITWS VERSION 0.1.0)

include(CTest)
enable_testing()

# find_package( OpenCV REQUIRED )
# include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(ITWS main.cpp)

# target_link_libraries(ITWS ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#Local header files here ONLY
SET(TARGET_H
    Image.h
    stb_image.h
    stb_image_write.h
    stb_image_resize.h  
   )

# Local source files here
SET(TARGET_SRC
    main.cpp
    Image.cpp
    )
include(CPack)