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

#include <assert.h>
#include <thread>
#include <type_traits>
#include "base/callback/callback.h"
#include "base/thread/thread_manager.h"

namespace nbase
{
#define SUPPORT_HOST_THREAD 0

	template<typename T, typename SupportGuardPtrT = SupportWeakCallback, typename = std::enable_if_t<std::is_base_of<SupportGuardPtrT, T>::value>>
	class BASE_EXPORT GuardPtr
	{
	public:
		typedef decltype(std::declval<SupportGuardPtrT>().GetWeakFlag()) WeakFlag;
#if SUPPORT_HOST_THREAD
		typedef decltype(std::declval<SupportGuardPtrT>().HostThreadId()) ThreadId;
#endif
		
	public:
		inline GuardPtr() {}
		inline GuardPtr(T* ptr)
			: ptr_(ptr)
			, weak_flag_(ptr ? ptr->GetWeakFlag() : WeakFlag())
#if SUPPORT_HOST_THREAD
			, host_thread_id_(ptr ? ptr->HostThreadId() : ThreadId{})
#endif
		{}
		inline ~GuardPtr() {}
		// compiler-generated copy/move ctor/assignment operators are fine!

		inline GuardPtr& operator=(T* ptr) { this->Reset(ptr); return (*this); }

		inline bool IsNull() const { return (!ptr_ || weak_flag_.expired()); }

		inline T* Get() const { return IsNull() ? nullptr : ptr_; }
		inline T* operator->() const { return Get(); }
		inline T& operator*() const { return *Get(); }
		inline operator T*() const { return Get(); }

		inline void Reset() { this->Reset(nullptr); }
		inline void Reset(T* ptr)
		{
			ptr_ = ptr;
			weak_flag_ = ptr ? ptr->GetWeakFlag() : WeakFlag();
#if SUPPORT_HOST_THREAD
			host_thread_id_ = ptr ? ptr->HostThreadId() : ThreadId{};
#endif
		}

#if SUPPORT_HOST_THREAD
		ThreadId HostThreadId() const { return host_thread_id_; }

		void PerformClosureOnHostThread(const std::function<void()>& closure) const
		{
			assert(closure);

			if (host_thread_id_ != ThreadId{})
			{
				ThreadManager::PerformTaskOnThread(host_thread_id_, closure);
			}
		}

		void TryToPerformClosureOnHostThread(const std::function<void()>& closure) const
		{
			assert(closure);

			if (host_thread_id_ != ThreadId{})
			{
				GuardPtr guard = *this;
				ThreadManager::PerformTaskOnThread(host_thread_id_, [=]{
					if (!guard.IsNull()) // not null, meaning the ptr_ guarded is still valid!
					{
						closure();
					}
				});
			}
		}
#endif

		void PerformClosureOnThread(int thread_identifier, const std::function<void()>& closure) const
		{
			assert(closure);

			ThreadManager::PostTask(thread_identifier, closure);
		}

		void TryToPerformClosureOnThread(int thread_identifier, const std::function<void()>& closure) const
		{
			assert(closure);

			GuardPtr guard = *this;
			ThreadManager::PostTask(thread_identifier, [=]{
				if (!guard.IsNull()) // not null, meaning the ptr_ guarded is still valid!
				{
					closure();
				}
			});
		}

	private:
		T* ptr_{ nullptr };
		WeakFlag weak_flag_;
#if SUPPORT_HOST_THREAD
		ThreadId host_thread_id_;
#endif
	};

#undef SUPPORT_HOST_THREAD
}

#endif