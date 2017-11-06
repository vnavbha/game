#include<type_traits>


template <typename T> class ZDelegate;

template<class R, class ...Args>
class ZDelegate <R(Args...)> final
{
private:
	using stub_type = R(*)(const ZDelegate&, Args&&...);
	using deleter_type = void(*)(void*);

	typedef R(*F)(Args...);

	template<typename Callable>
	const Callable& Callee() const {
		return *static_cast<Callable*>(object_ptr);
	}

	static R function_stub(const ZDelegate& delegate, Args&&... args)
	{
		return delegate.function_ptr(std::forward<Args>(args)...);
	}

	template<typename F>
	static R function_stub(const ZDelegate& delegate, Args&&... args) {
		return delegate.Callee<F>()(std::forward<Args>(args)...);
	}

	template<typename T>
	static void free(void *p) {
		T* pf = static_cast<T*>(p);
		pf->~T();
	}

	static void free(void *p) {
		p = nullptr;
	}

private:
	enum
	{
		SPACE_SIZE = 6 * sizeof(void *)
	};

private:
	stub_type stub_ptr = nullptr;
	deleter_type deleter_ptr = nullptr;

	union {
		F function_ptr;
		void* object_ptr;
	};

	uint8_t space[SPACE_SIZE];

public:
	ZDelegate(F f) {
		stub_ptr = function_stub;
		function_ptr = f;
	}

	template<typename Fn>
	ZDelegate(Fn fn) {
		using Decay = std::decay_t<Fn>;
		stub_ptr = function_stub<Decay>;

		Decay *p = static_cast<Decay*>((void *)space);

		object_ptr = new(p)Decay(std::move(fn));

		deleter_ptr = free<Decay>;
	}

	~ZDelegate() noexcept
	{
		if (deleter_ptr != nullptr)
		{
			deleter_ptr(object_ptr);
		}
	}

	ZDelegate(ZDelegate const&) = default;
	ZDelegate& operator=(ZDelegate const&) = default;

	ZDelegate() noexcept = default;

	ZDelegate(ZDelegate&&) noexcept = default;

	ZDelegate& operator=(ZDelegate&&) noexcept = default;

	ZDelegate(std::nullptr_t const) noexcept : ZDelegate() { }

	operator bool() const noexcept
	{
		return stub_ptr == nullptr;
	}

	bool operator ==(ZDelegate const& rhs) const noexcept
	{
		return (stub_ptr == rhs.stub_ptr) && (object_ptr == rhs.object_ptr);
	}

	bool operator !=(ZDelegate const& rhs) const noexcept
	{
		return !(operator==(rhs));
	}

	bool operator ==(std::nullptr_t const) const noexcept
	{
		return stub_ptr == nullptr;
	}

	bool operator !=(std::nullptr_t const) const noexcept
	{
		return stub_ptr != nullptr;
	}

	R operator ()(Args... args)  const {
		return (*stub_ptr)(*this, std::forward<Args>(args)...);
	}
};