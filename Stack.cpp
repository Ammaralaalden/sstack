#include "Stack.h"
#include "Vector.h"
#include "List.h"
#include <stdexcept>
#include <cstddef> // Добавлено для size_t

IStackImplementation* createImplementation(StackContainer container) 
{
	switch (container) 
	{
		case StackContainer::Vector:
		return new VectorStack();
		case StackContainer::List:
		return new ListStack();
		default:
		throw std::invalid_argument("Неизвестный тип контейнера");
	}
}

Stack::Stack(StackContainer container) : _containerType(container) 
{
	_pimpl = createImplementation(_containerType);
}

Stack::Stack(const ValueType* valueArray, size_t arraySize, StackContainer container): _containerType(container) 
{
	_pimpl = createImplementation(_containerType);
	for (size_t i = 0; i < arraySize; ++i) 
	{
		_pimpl->push(valueArray[i]);
	}
}



void Stack::copyFrom(const Stack& other) 
{
	// Получаем размер исходного стека
	size_t size = other.size();
    
	// Создаем временный массив для элементов в правильном порядке
	ValueType* tempArray = new ValueType[size];
    
	// Создаем временный стек для извлечения элементов
	Stack tmp;
	tmp._containerType = other._containerType;
	tmp._pimpl = createImplementation(tmp._containerType);
    	
	// Копируем элементы из исходного стека в массив
	for (size_t i = 0; i < size; ++i) 
	{
		tempArray[i] = other.top(); // Получаем верхний элемент
		tmp.push(tempArray[i]);     // Сохраняем во временный стек
		const_cast<Stack&>(other).pop(); // Удаляем из исходного стека
	}
    
	// Восстанавливаем исходный стек из временного
	for (size_t i = 0; i < size; ++i) 
	{
		const_cast<Stack&>(other).push(tmp.top());
		tmp.pop();
	}
    
	// Копируем элементы в текущий стек в исходном порядке
	for (size_t i = 0; i < size; ++i) 
	{
		_pimpl->push(tempArray[size - i - 1]); // Инвертируем порядок
	}
    
	delete[] tempArray;
}




// Конструктор копирования
Stack::Stack(const Stack& other): _containerType(other._containerType) 
{
	_pimpl = createImplementation(_containerType);
	copyFrom(other); // Копируем элементы
}


Stack& Stack::operator=(const Stack& other) 
{
	if (this != &other) 
	{
		Stack temp(other);
		std::swap(_pimpl, temp._pimpl);
		std::swap(_containerType, temp._containerType);
	}
	return *this;
}



Stack::~Stack() 
{
	delete _pimpl;
}

void Stack::push(const ValueType& value) 
{
	_pimpl->push(value);
}

void Stack::pop() 
{
	_pimpl->pop();
}

const ValueType& Stack::top() const 
{
	return _pimpl->top();
}

bool Stack::isEmpty() const 
{
	return _pimpl->isEmpty();
}

size_t Stack::size() const 
{
	return _pimpl->size();
}

