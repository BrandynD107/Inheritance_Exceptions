#include <catch2/catch_test_macros.hpp>
#include "student.hpp"
#include "instructor.hpp"
#include "course.hpp"

TEST_CASE("Student JSON serialization") {
  Student s(10,"Alice","alice@uni.edu",2027, {"CS101","HIST110"});
  auto j = s.to_json();
  CHECK(j.at("role") == "Student");
  CHECK(j.at("name") == "Alice");
  CHECK(j.at("grad_year") == 2027);
}

TEST_CASE("Instructor YAML serialization") {
  Instructor i(11,"Bob","bob@uni.edu","C-210", {"CS101"});
  auto y = i.to_yaml();
  CHECK(y["role"].as<std::string>() == "Instructor");
  CHECK(y["office"].as<std::string>() == "C-210");
}

TEST_CASE("CSV escaping handles commas and quotes") {
  Student s(12,"Eve, \"The Great\"","eve@uni.edu",2028, {"CS,101","AI\"Lab"});
  auto row = s.csv_row();
  REQUIRE(row.find("\"Eve, \"\"The Great\"\"\"") != std::string::npos);
}

TEST_CASE("Validation throws on bad email") {
  REQUIRE_THROWS_AS(Student(13,"Zed","not-an-email",2026), ValidationError);
}

TEST_CASE("Course JSON serialization") {
  Instructor i(11,"Bob","bob@uni.edu","C-210", {"CS101"});
  Student a(10,"Alice","alice@uni.edu",2027, {"CS101","HIST110"});
  Student s(12,"Eve, \"The Great\"","eve@uni.edu",2028, {"CS,101","AI\"Lab"});
  Course c("Intro to CS", {&a, &s}, i);
  auto j = c.to_json();
  CHECK(j.at("title") == "Intro to CS");
  CHECK(j.at("professor") == "Bob");
  auto roster = j.at("roster");
  REQUIRE(roster.is_array());
  CHECK(roster.size() == 2);
  CHECK(roster[0] == "Alice");
  CHECK(roster[1] == "Eve, \"The Great\"");
}

TEST_CASE("Student from_json deserialization") 
  {
    Student a(10,"Alice","alice@uni.edu",2027, {"CS101","HIST110"});
    nlohmann::json j = a.to_json();
    Student s(j);
    nlohmann::json js = s.to_json();

    CHECK(j.at("role") == js.at("role"));
    CHECK(j.at("name") == js.at("name"));
    CHECK(j.at("grad_year") == js.at("grad_year"));
    

  }