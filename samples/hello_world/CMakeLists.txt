# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

add_definitions(-DFOO_EN)
add_definitions(-DFOO_VAL=3)

set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(
	${include_dir}
)

set(src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_sources(app PRIVATE ${src_dir}/main.c ${src_dir}/foo.c )
