#ifndef BASE_MEMORY_OBJECT_COUNTER_H_
#define BASE_MEMORY_OBJECT_COUNTER_H_
#include <atomic> // for std::atomic
#include <stddef.h> // for std::size_t

namespace nbase
{
	template<typename CountedType>
	class ObjectCounter
	{
	private:
		static std::atomic<std::size_t> count_; // number of existing objects

	protected:
		// default constructor
		ObjectCounter() { count_ += 1; }

		// copy constructor
		ObjectCounter(const ObjectCounter<CountedType>&) { count_ += 1; }

		// move constructor
		ObjectCounter(ObjectCounter<CountedType>&&) { count_ += 1; }

		// destructor
		~ObjectCounter() { count_ -= 1; }

	public:
		// return number of existing objects
		static std::size_t live() { return count_; }
	};

	// initialize counter with zero
	template<typename CountedType>
	std::atomic<std::size_t> ObjectCounter<CountedType>::count_ = 0;
}

#define COUNT_LIVE_OBJECTS_VIA_MEMBER(memberName) \
private: struct MyCounter : public nbase::ObjectCounter<MyCounter> {}; \
public: static size_t live() { return MyCounter::live(); } \
private: MyCounter memberName

#endif