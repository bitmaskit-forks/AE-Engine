#pragma once

#include <memory>
#include <mutex>

#include "../../BUILD_OPTIONS.h"
#include "../../Platform.h"

#include "../MemoryTypes.h"

namespace AE
{

namespace engine_internal
{

class MemoryPool
{
public:
	MemoryPool();
	~MemoryPool();

	void	*	AllocateRaw( size_t size, size_t alignment );
	void	*	ReallocateRaw( void * old_ptr, size_t new_size, size_t alignment );
	void		FreeRaw( void * ptr );

	template<typename T, typename ...Args>
	T * Allocate( size_t alignment, Args&&... args )
	{
		return new( AllocateRaw( sizeof( T ), alignment ) )T( std::forward<Args>( args )... );
	}

	template<typename T>
	void Free( T * ptr )
	{
		ptr->~T();
		FreeRaw( ptr );
	}

private:
	std::mutex			mutex_general;

	int64_t				allocation_counter			= 0;
};

extern std::unique_ptr<MemoryPool>		memory_pool;

template<typename T, typename ...Args>
T * MemoryPool_Allocate( size_t alignment, Args&&... args )
{
	//	std::unique_ptr<T, engine_internal::MemoryDeleter<T>> ret;
	return memory_pool->Allocate<T>( alignment, std::forward<Args>( args )... );
}

template<typename T>
void		MemoryPool_Free( T * ptr )
{
	memory_pool->Free( ptr );
}

void	*	MemoryPool_AllocateRaw( size_t size, size_t alignment = 8 );

void	*	MemoryPool_ReallocateRaw( void * ptr, size_t new_size, size_t alignment = 8 );

void		MemoryPool_FreeRaw( void * ptr );

}

}
