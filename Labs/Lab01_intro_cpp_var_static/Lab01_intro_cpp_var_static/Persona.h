#ifndef PERSONA_H
#define PERSONA_H

class IPersona {
protected:
	static int nextId;
};

template<typename TypePersona>
class Persona : public IPersona {
public:
	static int getId() {
		static int id = nextId++;
		return id;
	}
};

class Musico {
public:
	Musico() = default;
};

class Artista {
public:
	Artista() = default;
};

class Empleado {
public:
	Empleado() = default;
};

#endif // !PERSONA_H

