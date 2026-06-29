cmake_minimum_required(VERSION 3.25)

project(c-dsa-study LANGUAGES C)

# ================================
# C 표준 설정
# ================================
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ================================
# 실행 파일 출력 경로
#
# 수정된 부분:
# 각 실행 파일의 세부 출력 경로는
# 아래 foreach 내부에서 설정한다.
# ================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/bin"
)

# ================================
# 공통 컴파일 옵션
# ================================
add_library(dsa_project_options INTERFACE)

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(
            dsa_project_options
            INTERFACE
            -Wall
            -Wextra
            -Wpedantic
    )
elseif (MSVC)
    target_compile_options(
            dsa_project_options
            INTERFACE
            /W4
    )
endif ()

# ================================
# Sanitizer 옵션
#
# AddressSanitizer:
# 잘못된 메모리 접근, use-after-free 등을 검사
#
# UndefinedBehaviorSanitizer:
# 정의되지 않은 동작을 검사
# ================================
option(
        ENABLE_SANITIZER
        "Enable AddressSanitizer and UndefinedBehaviorSanitizer"
        ON
)

add_library(dsa_sanitizer_options INTERFACE)

if (
        ENABLE_SANITIZER
        AND CMAKE_C_COMPILER_ID MATCHES "Clang|GNU"
)
    target_compile_options(
            dsa_sanitizer_options
            INTERFACE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
    )

    target_link_options(
            dsa_sanitizer_options
            INTERFACE
            -fsanitize=address,undefined
    )
endif ()

# ================================
# 학습용 .c 파일 자동 탐색
#
# 수정된 부분:
# 현재 실제 프로젝트 구조에 맞게 경로 변경
#
# 탐색 대상:
# c_review/**/*.c
# data_structures/**/*.c
# algorithms/**/*.c
# problems/**/*.c
#
# 이 폴더 아래의 각 .c 파일은
# 독립적인 main() 함수를 가져야 한다.
# ================================
file(
        GLOB_RECURSE
        STUDY_SOURCE_FILES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/c_review/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/data_structures/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/algorithms/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/problems/*.c"
)

# ================================
# 각 .c 파일을 독립 실행 타깃으로 등록
#
# 예:
# c_review/08_function/p_01.c
#
# CMake 타깃 이름:
# c_review_08_function_p_01
#
# 실행 파일:
# cmake-build-debug/bin/
# └── c_review/
#     └── 08_function/
#         └── p_01
# ================================
foreach (STUDY_SOURCE_FILE IN LISTS STUDY_SOURCE_FILES)

    # 수정된 부분:
    # src 기준이 아니라 프로젝트 루트 기준으로 상대 경로 계산
    file(
            RELATIVE_PATH
            STUDY_RELATIVE_PATH
            "${CMAKE_CURRENT_SOURCE_DIR}"
            "${STUDY_SOURCE_FILE}"
    )

    # 예:
    # STUDY_RELATIVE_PATH
    # = c_review/08_function/p_01.c

    get_filename_component(
            STUDY_RELATIVE_DIRECTORY
            "${STUDY_RELATIVE_PATH}"
            DIRECTORY
    )

    # 예:
    # STUDY_RELATIVE_DIRECTORY
    # = c_review/08_function

    get_filename_component(
            STUDY_FILE_NAME
            "${STUDY_SOURCE_FILE}"
            NAME_WE
    )

    # 예:
    # STUDY_FILE_NAME
    # = p_01

    # 수정된 부분:
    # 디렉터리와 파일 이름을 조합해서
    # 프로젝트 전체에서 고유한 타깃 이름 생성
    set(
            STUDY_TARGET_RAW_NAME
            "${STUDY_RELATIVE_DIRECTORY}_${STUDY_FILE_NAME}"
    )

    # 수정된 부분:
    # '/', '-', 공백 등 CMake 타깃 이름에 불편한 문자를
    # '_' 형태의 안전한 식별자로 변경
    string(
            MAKE_C_IDENTIFIER
            "${STUDY_TARGET_RAW_NAME}"
            STUDY_TARGET_NAME
    )

    # 예:
    # STUDY_TARGET_NAME
    # = c_review_08_function_p_01

    add_executable(
            "${STUDY_TARGET_NAME}"
            "${STUDY_SOURCE_FILE}"
    )

    # 수정된 부분:
    # 실제 실행 파일은 원래 파일 이름으로 생성하고
    # 소스 디렉터리 구조를 빌드 디렉터리 안에 유지
    set_target_properties(
            "${STUDY_TARGET_NAME}"
            PROPERTIES
            OUTPUT_NAME "${STUDY_FILE_NAME}"
            RUNTIME_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/bin/${STUDY_RELATIVE_DIRECTORY}"
    )

    target_link_libraries(
            "${STUDY_TARGET_NAME}"
            PRIVATE
            dsa_project_options
            dsa_sanitizer_options
    )

endforeach ()