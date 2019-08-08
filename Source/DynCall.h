extern "C" void* _DynCall(uint64_t);

// Define the "context", a memory area to hold the function calling information
// The header is an uint64_t array:
// nnnnnnnn - Number of parameters to be passed
// aaaaaaaa - Address of the function to call (JMP to)
// 11111111 - Arg1
// 22222222 - Arg2
// ........ - And so on
//

template <typename TRet = void, typename... TArgs, typename TAddr>
constexpr inline TRet nioCall(TAddr address, TArgs... args) {
	return reinterpret_cast<TRet(*)(TArgs...)>(address)(args ...);
}

#define MAX_ARGS 32
class DynCallContext {
	// Data fields
private:
	uint64_t nArgs = 0;
	uint64_t Address = 0;
	uint64_t Args[MAX_ARGS];

public:
	// Initalize Context
	template<typename T>
	void Init(T address) {
		nArgs = 0;
		Address = (uint64_t)address;
		for(int i = 0; i < MAX_ARGS; i++)
			Args[i] = 0x0;
	}
	// Push a value onto the context
	template<typename T>
	void Push(T val) {
		if(nArgs < MAX_ARGS)
			*reinterpret_cast<T*>(&Args[nArgs++]) = val;
	}
	// Make the call
    template <typename R>
    inline R Call() {
		return reinterpret_cast<R(__fastcall *)(uint64_t)>(_DynCall)((uint64_t)this);
    }
};