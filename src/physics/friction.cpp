#include "friction.hpp"

Friction::Friction(double constant) 
			: m_constant(std::move(constant)) {

}

void Friction::apply(Force& f) {
	
}