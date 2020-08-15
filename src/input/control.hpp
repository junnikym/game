#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "../common.hpp"
#include "input.hpp"

namespace input {

class Control;
class BinaryControl;

class Control {

};

class BinaryControl {
	public:
		BinaryControl(Input& input, int positive_key, int negative_key);

		void connect(Input& input);
		void set_positive(int key);
		void set_negative(int key);

		void update();
	private:
		Input* input;

		int positive_key = -1;
		int negative_key = -1;

		int buffer = 0;
		int negative_buf = 0;
};


} // end of namespace : input

#endif /* CONTROL_HPP */