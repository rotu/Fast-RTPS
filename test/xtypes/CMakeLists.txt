# Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

macro(add_xtypes_gtest test)
    # Parse arguments
    set(multiValueArgs SOURCES ENVIRONMENTS)
    cmake_parse_arguments(GTEST "" "" "${multiValueArgs}" ${ARGN})

    if(GTEST_INDIVIDUAL)
        if(WIN32)
            set(WIN_PATH "$ENV{PATH}")
            get_target_property(LINK_LIBRARIES_ ${test} LINK_LIBRARIES)
            if(NOT "${LINK_LIBRARIES_}" STREQUAL "LINK_LIBRARIES_-NOTFOUND")
                foreach(LIBRARY_LINKED ${LINK_LIBRARIES_})
                    if(TARGET ${LIBRARY_LINKED})
                        set(WIN_PATH "$<TARGET_FILE_DIR:${LIBRARY_LINKED}>;${WIN_PATH}")
                    endif()
                endforeach()
            endif()
            string(REPLACE ";" "\\;" WIN_PATH "${WIN_PATH}")
        endif()

        foreach(GTEST_SOURCE_FILE ${GTEST_SOURCES})
            file(STRINGS ${GTEST_SOURCE_FILE} GTEST_NAMES REGEX ^TEST)
            foreach(GTEST_NAME ${GTEST_NAMES})
                string(REGEX REPLACE ["\) \(,"] ";" GTEST_NAME ${GTEST_NAME})
                list(GET GTEST_NAME 1 GTEST_GROUP_NAME)
                list(GET GTEST_NAME 3 GTEST_NAME)
                add_test(NAME ${GTEST_GROUP_NAME}.${GTEST_NAME}
                    COMMAND ${test}
                    --gtest_filter=${GTEST_GROUP_NAME}.${GTEST_NAME})

                # Add environment
                if(WIN32)
                    set_tests_properties(${GTEST_GROUP_NAME}.${GTEST_NAME} PROPERTIES ENVIRONMENT "PATH=${WIN_PATH}")
                endif()

                foreach(property ${GTEST_ENVIRONMENTS})
                    set_property(TEST ${GTEST_GROUP_NAME}.${GTEST_NAME} APPEND PROPERTY ENVIRONMENT "${property}")
                endforeach()
            endforeach()
        endforeach()
    else()
        add_test(NAME ${test} COMMAND ${test})

        # Add environment
        if(WIN32)
            set(WIN_PATH "$ENV{PATH}")
            get_target_property(LINK_LIBRARIES_ ${test} LINK_LIBRARIES)
            if(NOT "${LINK_LIBRARIES_}" STREQUAL "LINK_LIBRARIES_-NOTFOUND")
                foreach(LIBRARY_LINKED ${LINK_LIBRARIES_})
                    if(TARGET ${LIBRARY_LINKED})
                        set(WIN_PATH "$<TARGET_FILE_DIR:${LIBRARY_LINKED}>;${WIN_PATH}")
                    endif()
                endforeach()
            endif()
            string(REPLACE ";" "\\;" WIN_PATH "${WIN_PATH}")
            set_tests_properties(${test} PROPERTIES ENVIRONMENT "PATH=${WIN_PATH}")
        endif()

        foreach(property ${GTEST_ENVIRONMENTS})
            set_property(TEST ${test} APPEND PROPERTY ENVIRONMENT "${property}")
        endforeach()
    endif()
endmacro()

if(NOT ((MSVC OR MSVC_IDE) AND EPROSIMA_INSTALLER) AND fastcdr_FOUND)
    include(${PROJECT_SOURCE_DIR}/cmake/common/gtest.cmake)
    check_gtest()

    if(GTEST_FOUND)
        if(WIN32)
            add_definitions(
                -D_WIN32_WINNT=0x0601
                -D_CRT_SECURE_NO_WARNINGS
                )
        endif()

        add_definitions(
          -DEPROSIMA_SHAPES_DLL_EXPORT
          -DBUILD_SHARED_LIBS
          -DBOOST_ASIO_STANDALONE
          -DASIO_STANDALONE
        )

        include_directories(${ASIO_INCLUDE_DIR})

        ###############################################################################
        # Unit tests
        ###############################################################################
        set(XTYPES_TESTS_SOURCE XTypesTests.cpp
            idl/Types.cxx
            idl/TypesPubSubTypes.cxx
            idl/TypesTypeObject.cxx
            TestPublisher.cpp
            TestSubscriber.cpp
            )

        add_executable(XTypesBlackBoxTests ${XTYPES_TESTS_SOURCE})
        target_include_directories(XTypesBlackBoxTests PRIVATE ${GTEST_INCLUDE_DIRS})
        target_link_libraries(XTypesBlackBoxTests fastrtps fastcdr ${GTEST_LIBRARIES})
        add_xtypes_gtest(XTypesBlackBoxTests SOURCES ${XTYPES_TESTS_SOURCE})
    endif()
endif()

# DYNAMIC -> DYNAMIC TRANSFORM
#file(GLOB TYPES_LIB_SOURCE "typeslib.cpp")
#add_library(Types SHARED ${TYPES_LIB_SOURCE})
#target_link_libraries(Types fastrtps fastcdr ${CMAKE_DL_LIBS})
