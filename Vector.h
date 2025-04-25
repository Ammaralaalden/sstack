#pragma once
#include "StackImplementation.h"
#include <vector>
#include <stdexcept>
#include <cstddef> // для size_t

class VectorStack : public IStackImplementation 
{
private:
	std::vector<ValueType> _data;
public:
	void push(const ValueType& value) override 
	{
		_data.push_back(value);
	}

	void pop() override 
	{
		if (_data.empty()) 
		{
			throw std::out_of_range("Стек пуст");
		}
		_data.pop_back();
	}

	const ValueType& top() const override 
	{
		if (_data.empty()) 
		{
			throw std::out_of_range("Стек пуст");
		}
		return _data.back();
	}

	bool isEmpty() const override 
	{
		return _data.empty();
	}

	size_t size() const override 
	{
		return _data.size();
	}
};
