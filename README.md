CS 310 Inheritance and Exceptions lab

contains 3 main classes used for testing Inheritance and exceptions: Student, Instructor, and Course.
All three classes are Serializable into json, yaml, and csv formats.
Both Student and Instructor have get_name functions for use in Course serialization functions.
Course uses Student and Instructor names in place of their serialization when serializing.
Both student and Instructor have initializers that utilize the from_json function .
test_serialization has 2 additional tests for the from_json function and the Course class
