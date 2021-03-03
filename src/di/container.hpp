#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "../common.hpp"

namespace DI {

class Container {

	public:
		Container();

	private:
		string name;
		int size;

		void* content;
		
		void* init_func;
		void* run_func;
};

}

#endif