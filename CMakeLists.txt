cmake_minimum_required(VERSION 3.25)

project(c_dsa_study C)

# ================================
# C 표준 설정
# ================================
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ================================
# 실행 파일 출력 경로
# ================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ================================
# 공통 컴파일 옵션
# ================================
add_library(dsa_project_options INTERFACE)

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(dsa_project_options
            INTERFACE
            -Wall
            -Wextra
            -Wpedantic
            -g
    )
elseif (MSVC)
    target_compile_options(dsa_project_options
            INTERFACE
            /W4
    )
endif ()

# ================================
# Sanitizer 옵션
# 메모리 오류, 배열 범위 초과, 정의되지 않은 동작을 잡기 위한 옵션
# macOS clang / Linux gcc, clang 기준으로 사용
# ================================
option(ENABLE_SANITIZER "Enable AddressSanitizer and UndefinedBehaviorSanitizer" ON)

add_library(dsa_sanitizer_options INTERFACE)

if (ENABLE_SANITIZER AND CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(dsa_sanitizer_options
            INTERFACE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
    )

    target_link_options(dsa_sanitizer_options
            INTERFACE
            -fsanitize=address,undefined
    )
endif ()

# ================================
# 공통 유틸 라이브러리
# 여기에 main()을 넣으면 안 됨
# ================================
add_library(dsa_common
        src/common/dsa_common.c
)

target_include_directories(dsa_common
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/common
)

target_link_libraries(dsa_common
        PUBLIC
        dsa_project_options
)

# ================================
# 학습용 .c 파일 자동 탐색
# src/data_structures/*.c
# src/algorithms/*.c
# 아래 두 폴더의 .c 파일은 모두 main()을 가져야 함
# ================================
file(GLOB_RECURSE STUDY_SOURCE_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/algorithms/*.c"
)

# ================================
# 각 .c 파일을 독립 실행 타깃으로 등록
# 예:
# src/data_structures/stack_array.c
# → data_structures_stack_array
# ================================
foreach (STUDY_SOURCE_FILE ${STUDY_SOURCE_FILES})
    file(RELATIVE_PATH STUDY_RELATIVE_PATH
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${STUDY_SOURCE_FILE}
    )

    get_filename_component(STUDY_RELATIVE_DIRECTORY
            ${STUDY_RELATIVE_PATH}
            DIRECTORY
    )

    get_filename_component(STUDY_FILE_NAME
            ${STUDY_SOURCE_FILE}
            NAME_WE
    )

    string(REPLACE "/" "_" STUDY_TARGET_PREFIX
            ${STUDY_RELATIVE_DIRECTORY}
    )

    string(REPLACE "-" "_" STUDY_TARGET_PREFIX
            ${STUDY_TARGET_PREFIX}
    )

    set(STUDY_TARGET_NAME
            "${STUDY_TARGET_PREFIX}_${STUDY_FILE_NAME}"
    )

    add_executable(${STUDY_TARGET_NAME}
            ${STUDY_SOURCE_FILE}
    )

    target_link_libraries(${STUDY_TARGET_NAME}
            PRIVATE
            dsa_common
            dsa_project_options
            dsa_sanitizer_options
    )
endforeach ()