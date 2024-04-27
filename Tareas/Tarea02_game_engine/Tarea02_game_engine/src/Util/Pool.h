#pragma once
#include <vector>

class IPool {
public:
	virtual ~IPool() {};
};

template<typename TComponent>
class Pool : public IPool {
	std::vector<TComponent> data;
public:
	Pool(size_t size = 200) {
		data.resize(size);
	}

	virtual ~Pool() = default;

	bool IsEmpty() const {
		return data.empty();
	}

	size_t GetSize() const {
		return data.size();
	}

	void Resize(size_t size) {
		data.resize(size);
	}

	void Clear() {
		data.clear();
	}

	void Add(TComponent object) {
		data.push_back(object);
	}

	void Set(unsigned int index, TComponent object) {
		data[index] = object;
	}

	TComponent& Get(unsigned int index) {
		return static_cast<TComponent&>(data[index]);
	}

	TComponent& operator[](unsigned int index) {
		return static_cast<TComponent&>(data[index]);
	}
};
