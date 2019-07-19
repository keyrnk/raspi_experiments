#ifndef __ARENA_ALLOCATOR_H_
#define __ARENA_ALLOCATOR_H_

#include <cstddef>
#include "arena.h"

extern char heap_start;
extern char heap_end;

template <class T>
class ArenaAllocator
{
public:
	using value_type = T;	
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;

	template <class U>
	struct rebind {
		typedef ArenaAllocator<U> other;	
	};

	static Arena<T> arena;

	ArenaAllocator()
	{
		arena.Init((&heap_end - &heap_start), &heap_start);
	}

	pointer allocate(size_type n, ArenaAllocator<T>::const_pointer hint = 0)
	{
		return arena.allocate(n);
	}

	void deallocate(pointer p, size_type n)
	{
		arena.deallocate(p, n);
	}

};

template <class T>
Arena<T> ArenaAllocator<T>::arena;

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

#endif
