find_package(rostest REQUIRED)

add_rostest_gtest(test_homework1
  homework1.test
  homework1_test.cpp
)
add_dependencies(test_homework1
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(test_homework1
  ${catkin_LIBRARIES}
)

