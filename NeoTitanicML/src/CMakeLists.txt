
# Model (shared lib)
set(MODEL ${PROJECT_NAME})
# Tools: dataset prep
set(PREPARATION preparation)
# Tools: train model
set(TRAIN train)


#
# Model (shared lib)
#
set(MODEL_SOURCES
    model/data/passenger_info_converter.cc
    model/data/preprocessing/label_encoder.cc
)

set(MODEL_HEADERS
    model/data/passenger_info.h
    model/data/passenger_info_converter.h
    model/data/preprocessing/label_encoder.h
)

add_library(${MODEL} STATIC ${MODEL_SOURCES} ${MODEL_HEADERS})

#
# Tools: dataset prep
#
set(PREP_SOURCES
    tools/preparation/csv_reader.cc
    tools/preparation/utility.cc
)

set(PREP_HEADERS
    tools/preparation/csv_reader.h
    tools/preparation/utility.h
)

add_library(${PREP_LIB} STATIC ${PREP_SOURCES} ${PREP_HEADERS})
add_executable(${PREPARATION} tools/preparation/main.cc)
target_link_libraries(${PREPARATION} ${PREP_LIB} ${MODEL})

#
# Tools: train model
#
set(TRAIN_SOURCES
    tools/train/main.cc
)

set(TRAIN_HEADERS
    tools/train/
)

add_executable(${TRAIN} ${TRAIN_SOURCES})

target_link_libraries(${TRAIN}
    Neo::NeoMathEngine
    Neo::NeoML
    nlohmann_json::nlohmann_json
    cxxopts::cxxopts
)
