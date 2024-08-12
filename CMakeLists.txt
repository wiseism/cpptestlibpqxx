cmake_minimum_required(VERSION 3.15)
project(cpptestlibpqxx)

set(CMAKE_CXX_STANDARD 11)

find_package(libpqxx CONFIG REQUIRED)
add_executable(main_pq src/main_pg.cpp)
add_executable(51version_test src/51version_test.cpp)
add_executable(pq_brief src/pg_brief.cpp)

target_link_libraries(main_pq libpqxx::pqxx libpq::pgport libpq::pgcommon libpq::pq)
target_link_libraries(51version_test libpqxx::pqxx  libpq::pgport libpq::pgcommon libpq::pq)
target_link_libraries(pq_brief libpqxx::pqxx libpq::pgport libpq::pgcommon libpq::pq)
