cmake_minimum_required(VERSION 3.26.3)

project(data_structures)

set (CMAKE_CXX_STANDARD 11)

set(STRUCTURES
    hash_tables
)

foreach(_dir IN ITEMS ${STRUCTURES})
    file(GLOB _files "${_dir}/*.cpp")
    message(STATUS "Pattern `${_dir}':")

    foreach(_file IN ITEMS ${_files})

        get_filename_component(_file_name
                ${_file} NAME
                )

        set(_project_name "${_file_name}")
        message(STATUS "  ${_dir}/${_file_name} is going to be built")

        add_executable(${_project_name} "${_dir}/${_file_name}")
    endforeach()

endforeach()
