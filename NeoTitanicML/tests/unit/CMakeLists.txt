set(TEST ${CMAKE_PROJECT_NAME}_test)


get_filename_component(DIR_WHITH_TEST_DATA "../data" ABSOLUTE)
configure_file(settings.h.in settings.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
    main.cc
    tools/preparation/utility_test.cc
    tools/preparation/csv_reader_test.cc
    model/data/preprocessing/label_encoder_test.cc
    model/data/preprocessing/standart_scaler_test.cc
)

add_executable(${TEST} ${SOURCES})

add_test(NAME ${TEST} COMMAND ${TEST})

message(${TEST})
target_link_libraries(${TEST} ${PROJECT_NAME} GTest::GTest ${PREP_LIB})