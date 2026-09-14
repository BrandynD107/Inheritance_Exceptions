#pragma once
#include "person.hpp"
#include "student.hpp"
#include "instructor.hpp"
#include "csv.hpp"
#include <string>
#include <vector>

class Course : public Serializable
{
  std::string title_;
  std::vector<const Student*> roster_;
  const Instructor& prof_;

public:
  Course(std::string title, const std::vector<const Student*>& roster, const Instructor& prof)
      : title_(title), roster_(roster), prof_(prof)
  {
  }
  nlohmann::json to_json() const override
  {
    nlohmann::json json;
    json["title"] = title_;
    json["roster"] = nlohmann::json::array();
    for (const auto& student : roster_) {
      json["roster"].push_back(student->get_name());
    }
    json["professor"] = prof_.get_name();
    return json;
  }
  YAML::Node to_yaml() const override 
  {
    YAML::Node n;
    n["title"] = title_;
    for (const auto& student : roster_) n["roster"].push_back(student->get_name());
    n["professor"] = prof_.get_name();
    return n;
  }
    std::string csv_header() const override {
    return "title,roster,professor";
  }

  std::string csv_row() const override
   {
    std::string roster_csv;
    for (const auto& student : roster_)
    {
        roster_csv += student->get_name() + ";";
    }

    return csv_escape(title_) + "," + csv_escape(roster_csv) + "," +
           csv_escape(prof_.get_name());
  }
};