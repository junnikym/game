#include "control.hpp"

namespace input {

BinaryControl::BinaryControl(Input& input, int positive_key, int negative_key) {
	this->input = &input;
	this->positive_key = move(positive_key);
	this->negative_key = move(negative_key);
}

void BinaryControl::connect(Input& input) {
	this->input = &input;
}

void BinaryControl::set_positive(int key) {
	this->positive_key = move(key);
}

void BinaryControl::set_negative(int key) {
	this->negative_key = move(key);
}

void BinaryControl::update() {
	
	// Positive key
	//--------------------------------------------------
	if ( input->is_key_down(positive_key) ) {	// Pressed
		if(buffer == 1) {
			negative_buf = 1;
		}
		buffer = -1;
	}
	else {											// Not Pressed
		if(negative_buf == 1)			// Opposite Direction
			buffer = 1;
		else if(negative_buf != -1)
			buffer = 0;

		negative_buf = 0;
	}

	// Negative key
	//--------------------------------------------------
	if ( input->is_key_down(negative_key) ) {		// Pressed
		if(buffer == -1) {
			negative_buf = -1;
		}
		buffer = 1;
	}
	else {											// Not Pressed
		if(negative_buf == -1)			// Opposite Direction
			buffer = -1;
		else if(negative_buf != 1)
			buffer = 0;

		negative_buf = 0;
	}

}

} // end of namespace : input