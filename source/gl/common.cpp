#include "../../include/gl/common.hpp"

GLuint gl::object::name() const { return _name; }

gl::object::object () { }

gl::object::operator GLuint() const { return _name; }
