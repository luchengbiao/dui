/** 
* There are some types of raw pointers which we can not use such smart pointer as std::shared_ptr to protect/manage,
* such as pointers to UI/Widget objects which are generally already managed(especially destroying) by a corresponding framework,
* so here we implement another smart pointer to protect/guard such pointers, mainly detecting whether the pointed object was already destroyed/deleted.
* It is guard_ptr based on SupportWeakCallback, inspired by Qt::QPointer.
* NOTICE: the guard_ptr and SupportWeakCallback are both NOT THREAD-SAFE, 
* so when wanting to protect/manage some pointers thread-safely, consider std::shared_ptr.
*/

#ifndef BASE_MEMORY_GUARD_PTR_H_
#define BASE_MEMORY_GUARD_PTR_H_
#pragma once

#include <type_traits>
#include "base/callback/callback.h"

namespace nbase
{
	template<typename T, typename = std::enable_if_t<std::is_base_of<SupportWeakCallback, T>::value>>
	class BASE_EXPORT GuardPtr
	{
		typedef typename SupportWeakCallback::_TyWeakFlag WeakFlag;

	public:
		inline GuardPtr() {}
		inline GuardPtr(T* ptr)
		: ptr_(ptr)
		, weak_flag_(ptr ? ptr->GetWeakFlag() : WeakFlag()) 
		{}
		inline ~GuardPtr() {}
		// compiler-generated copy/move ctor/assignment operators are fine!

		inline GuardPtr& operator=(T* ptr)
		{
			ptr_ = ptr;
			weak_flag_ = ptr ? ptr->GetWeakFlag() : WeakFlag();

			return (*this);
		}

		inline bool IsNull() const { return (!ptr_ || weak_flag_.expired()); }

		inline T* Get() const { return IsNull() ? nullptr : ptr_; }
		inline T* operator->() const { return Get(); }
		inline T& operator*() const { return *Get(); }
		inline operator T*() const { return Get(); }

		inline void Clear()
		{
			ptr_ = nullptr;
			weak_flag_.reset();
		}

		inline void Swap(GuardPtr& guard_ptr)
		{
			if (this != &guard_ptr)
			{
				GuardPtr tmp(guard_ptr);
				guard_ptr = *this;
				*this = tmp;
			}
		}

	private:
		T* ptr_{ nullptr };
		WeakFlag weak_flag_;
	};
}



#endif