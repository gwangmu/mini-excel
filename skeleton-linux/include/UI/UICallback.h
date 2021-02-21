#ifndef ASSN2_UI_CALLBACK_H
#define ASSN2_UI_CALLBACK_H

/* NOTE: This implementation is heavily supported by
 * Sergey Ryazanov's 'The Impossibly Fast C++ Delegates' code.
 * (Link: http://www.codeproject.com/Articles/11015/
 *  The-Impossibly-Fast-C-Delegates) */

class UIObject;

class UICallback {
private:
	typedef void (*SubType) (void *ptrObj, UIObject *);

	void *ptrObj;
	SubType ptrSub;

	template <class T, void (T::*TMethod) (UIObject *)>
	inline static void methodStub (void *ptrObj, UIObject *emitter) {
		T *ptrT = static_cast<T *>(ptrObj);
		return (ptrT->*TMethod (emitter));
	}

	template <void (*TMethod) (UIObject *)>
	inline static void functionStub (void *unused, UIObject *emitter) {
		return (TMethod (emitter));
	}

public:
	UICallback () {
		ptrObj = NULL;
		ptrSub = (SubType)NULL;
	}

	template <class T, void (T::*TMethod) (UIObject *)>
	inline void bind (T *ptrObj) {
		this->ptrObj = ptrObj;
		this->ptrSub = &methodStub<T, TMethod>;
	}

	template <void (*TMethod) (UIObject *)>
	inline void bind () {
		this->ptrObj = NULL;
		this->ptrSub = &functionStub<TMethod>;
	}

	inline void emit (UIObject *emitter) {
		if (ptrSub) {
			(*ptrSub) (ptrObj, emitter);
		}
	}
};

#endif
