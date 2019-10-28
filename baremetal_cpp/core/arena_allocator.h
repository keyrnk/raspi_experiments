#ifndef __ARENA_ALLOCATOR_H_
#define __ARENA_ALLOCATOR_H_

#include <cstddef>
#include "bit_map_arena.h"

class Base
{
protected:
	static BitMapArena arena;
};

BitMapArena Base::arena;

template <class T>
class ArenaAllocator : public Base
{
public:
	using value_type = T;

//gcc 4.8 for esp8266 doesn't have full support for C++11 allocator
//and requires all using below and rebind	
	using pointer = T*;
	using const_pointer = const T*;
        using size_type = std::size_t;
	using reference = T&;
	using const_reference = const T&;
	using difference_type = std::ptrdiff_t;

	template <typename U>
	struct rebind {
		typedef ArenaAllocator<U> other;
	};

public:
	ArenaAllocator() noexcept = default;
	
	template<typename U>
	ArenaAllocator(const ArenaAllocator<U>& other) noexcept {};	

public:
	static pointer allocate(size_type n, const_pointer hint = 0)
	{
		return static_cast<pointer>(arena.allocate(n * sizeof(T)));
	}

	static void deallocate(pointer p, size_type n)
	{
		arena.deallocate(p, n * sizeof(T));
	}

};

template <class T1, class T2>
bool operator == (const ArenaAllocator<T1>& first, const ArenaAllocator<T2>& second) noexcept
{
	return true;
}

template <class T1, class T2>
bool operator != (const ArenaAllocator<T1>& first, const ArenaAllocator<T2>& second) noexcept
{
	return false;
}

template <class T>
using BaremetalAllocator = ArenaAllocator<T>;
#endif
