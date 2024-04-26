#ifndef STUPIDPTR_H
#define STUPIDPTR_H

//Para el forward
#include <utility>

template<typename T>
class StupidPtr {
	T* elemento;
public:
	template <typename ...TArgs>
	StupidPtr(TArgs&& ...args) {
		//forward es la forma en la que se extrae todos los args
		//que se pasan
		elemento = new T(std::forward<TArgs>(args)...);
	}

	~StupidPtr() {
		delete elemento;
	}

	T* operator->() {
		return elemento;
	}
};

#endif // !STUPIDPTR_H
