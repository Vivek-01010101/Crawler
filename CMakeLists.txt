cmake_minimum_required(VERSION 3.16)

project(WebCrawler)

set(CMAKE_CXX_STANDARD 17)

# ============================
# Dependencies
# ============================

find_package(SQLite3 REQUIRED)
find_package(CURL REQUIRED)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(include)

# ============================
# Main Executable
# ============================

add_executable(crawler
    main.cpp
    src/Crawler/Crawler.cpp
    src/Fetcher/Fetcher.cpp
    src/Frontier/Frontier.cpp
    src/LinkExtractor/LinkExtractor.cpp
    src/URLNormalizer/URLNormalizer.cpp
    src/SeenStore/SeenStore.cpp
    src/PageStorage/PageStorage.cpp
)

target_include_directories(crawler PRIVATE
    ${SQLite3_INCLUDE_DIRS}
)

target_link_libraries(crawler
    PRIVATE
    SQLite3::SQLite3
    CURL::libcurl
)

# ============================
# Unit Tests
# ============================

add_executable(runTests
    tests/test_frontier.cpp
    src/Frontier/Frontier.cpp

    tests/seen_store.cpp
    src/SeenStore/SeenStore.cpp

    tests/URL_normalizer.cpp
    src/URLNormalizer/URLNormalizer.cpp

    tests/page_storage.cpp
    src/PageStorage/PageStorage.cpp

    tests/Link_extractor.cpp
    src/LinkExtractor/LinkExtractor.cpp

    tests/Fetcher_test.cpp
    src/Fetcher/Fetcher.cpp

    tests/Crawler_test.cpp
    src/Crawler/Crawler.cpp
)

target_include_directories(runTests PRIVATE
    include
    ${SQLite3_INCLUDE_DIRS}
)

target_link_libraries(runTests
    PRIVATE
    GTest::gtest_main
    SQLite3::SQLite3
    CURL::libcurl
)

include(GoogleTest)
gtest_discover_tests(runTests)