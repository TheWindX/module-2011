//-------------------------------------------------------------------------
//
// Copyright (C) 2004-2005 Yingle Jia
//
// Permission to copy, use, modify, sell and distribute this software is 
// granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.
//
// ns_delegateDelegateTemplate.h
//

// Note: this header is a header template and must NOT have multiple-inclusion
// protection.

#define ns_delegate_DELEGATE_TEMPLATE_PARAMS    ns_delegate_MAKE_PARAMS1(ns_delegate_DELEGATE_NUM_ARGS, class T)
	// class T0, class T1, class T2, ...
#define ns_delegate_DELEGATE_TEMPLATE_ARGS      ns_delegate_MAKE_PARAMS1(ns_delegate_DELEGATE_NUM_ARGS, T)
	// T0, T1, T2, ...
#define ns_delegate_DELEGATE_FUNCTION_PARAMS    ns_delegate_MAKE_PARAMS2(ns_delegate_DELEGATE_NUM_ARGS, T, a)
	// T0 a0, T1 a1, T2 a2, ...
#define ns_delegate_DELEGATE_FUNCTION_ARGS      ns_delegate_MAKE_PARAMS1(ns_delegate_DELEGATE_NUM_ARGS, a)
	// a0, a1, a2, ...

// Comma if nonzero number of arguments
#if ns_delegate_DELEGATE_NUM_ARGS == 0
#define ns_delegate_DELEGATE_COMMA
#else
#define ns_delegate_DELEGATE_COMMA    ,
#endif

namespace ns_delegate {

//-------------------------------------------------------------------------
// class Delegate<R (T1, T2, ..., TN)>

template <class R ns_delegate_DELEGATE_COMMA ns_delegate_DELEGATE_TEMPLATE_PARAMS>
class Delegate<R (ns_delegate_DELEGATE_TEMPLATE_ARGS)>
{
// Declaractions
private:
    class DelegateImplBase
    {
    // Fields
    public:
        DelegateImplBase* Previous; // singly-linked list

    // Constructor/Destructor
    protected:
        DelegateImplBase() : Previous(NULL) { }
        DelegateImplBase(const DelegateImplBase& other) : Previous(NULL) { }
    public:
        virtual ~DelegateImplBase() { }

    // Methods
    public:
        virtual DelegateImplBase* Clone() const = 0;
        virtual R Invoke(ns_delegate_DELEGATE_FUNCTION_PARAMS) const = 0;
    };

    template <class TFunctor>
    struct Invoker
    {
        static R Invoke(const TFunctor& f ns_delegate_DELEGATE_COMMA ns_delegate_DELEGATE_FUNCTION_PARAMS)
        {
            return (const_cast<TFunctor&>(f))(ns_delegate_DELEGATE_FUNCTION_ARGS);
        }
    };

    template <class TPtr, class TFunctionPtr>
    struct Invoker<std::pair<TPtr, TFunctionPtr> >
    {
        static R Invoke(const std::pair<TPtr, TFunctionPtr>& mf ns_delegate_DELEGATE_COMMA ns_delegate_DELEGATE_FUNCTION_PARAMS)
        {
            return ((*mf.first).*mf.second)(ns_delegate_DELEGATE_FUNCTION_ARGS);
        }
    };

    template <class TFunctor>
    class DelegateImpl : public DelegateImplBase
    {
    // Fields
    public:
        TFunctor Functor;

    // Constructor
    public:
        DelegateImpl(const TFunctor& f) : Functor(f)
        {
        }
        DelegateImpl(const DelegateImpl& other) : Functor(other.Functor)
        {
        }

    // Methods
    public:
        virtual DelegateImplBase* Clone() const
        {
            return new DelegateImpl(*this);
        }
        virtual R Invoke(ns_delegate_DELEGATE_FUNCTION_PARAMS) const
        {
            return Invoker<TFunctor>::Invoke(this->Functor ns_delegate_DELEGATE_COMMA ns_delegate_DELEGATE_FUNCTION_ARGS);
        }
    };

// Fields
private:
    DelegateImplBase* _last;

// Constructor/Destructor
public:
    Delegate()
    {
        this->_last = NULL;
    }

    template <class TFunctor>
    Delegate(const TFunctor& f)
    {
        this->_last = NULL;
        *this = f;
    }

	template<class TPtr, class TFunctionPtr>
    Delegate(const TPtr& obj, const TFunctionPtr& mfp)
    {
        this->_last = NULL;
        *this = std::make_pair(obj, mfp);
    }

    Delegate(const Delegate& d)
    {
        this->_last = NULL;
        *this = d;
    }

    ~Delegate()
    {
        Clear();
    }

// Properties
public:
    bool IsEmpty() const
    {
        return (this->_last == NULL);
    }

    bool IsMulticast() const
    {
        return (this->_last != NULL && this->_last->Previous != NULL);
    }

// Static Methods
private:
    static DelegateImplBase* CloneDelegateList(DelegateImplBase* list, /*out*/ DelegateImplBase** first)
    {
        DelegateImplBase* list2 = list;
        DelegateImplBase* newList = NULL;
        DelegateImplBase** pp = &newList;
        DelegateImplBase* temp = NULL;

        try
        {
            while (list2 != NULL)
            {
                temp = list2->Clone();
                *pp = temp;
                pp = &temp->Previous;
                list2 = list2->Previous;
            }
        }
        catch (...)
        {
            FreeDelegateList(newList);
            throw;
        }

        if (first != NULL)
            *first = temp;
        return newList;
    }

    static void FreeDelegateList(DelegateImplBase* list)
    {
        DelegateImplBase* temp = NULL;
        while (list != NULL)
        {
            temp = list->Previous;
            delete list;
            list = temp;
        }
    }

    static void InvokeDelegateList(DelegateImplBase* list ns_delegate_DELEGATE_COMMA ns_delegate_DELEGATE_FUNCTION_PARAMS)
    {
        if (list != NULL)
        {
            if (list->Previous != NULL)
                InvokeDelegateList(list->Previous ns_delegate_DELEGATE_COMMA ns_delegate_DELEGATE_FUNCTION_ARGS);
            list->Invoke(ns_delegate_DELEGATE_FUNCTION_ARGS);
        }
    }

// Methods
public:
    template <class TFunctor>
    void Add(const TFunctor& f)
    {
        DelegateImplBase* d = new DelegateImpl<TFunctor>(f);
        d->Previous = this->_last;
        this->_last = d;
    }

	template<class TPtr, class TFunctionPtr>
    void Add(const TPtr& obj, const TFunctionPtr& mfp)
    {
        DelegateImplBase* d = new DelegateImpl<std::pair<TPtr, TFunctionPtr> >(std::make_pair(obj, mfp));
        d->Previous = this->_last;
        this->_last = d;
    }

    template <class TFunctor>
    bool Remove(const TFunctor& f)
    {
        DelegateImplBase* d = this->_last;
        DelegateImplBase** pp = &this->_last;
        DelegateImpl<TFunctor>* impl = NULL;

        while (d != NULL)
        {
            impl = dynamic_cast<DelegateImpl<TFunctor>*>(d);
            if (impl != NULL && impl->Functor == f)
            {
                *pp = d->Previous;
                delete impl;
                return true;
            }
            pp = &d->Previous;
            d = d->Previous;
        }
        return false;
    }

	template<class TPtr, class TFunctionPtr>
    bool Remove(const TPtr& obj, const TFunctionPtr& mfp)
    {
        return Remove(std::make_pair(obj, mfp));
    }

    void Clear()
    {
        FreeDelegateList(this->_last);
        this->_last = NULL;
    }

private:
    template <class TFunctor>
    bool Equals(const TFunctor& f) const
    {
        if (this->_last == NULL || this->_last->Previous != NULL)
            return false;

        DelegateImpl<TFunctor>* impl = 
            dynamic_cast<DelegateImpl<TFunctor>*>(this->_last);
        if (impl == NULL)
            return false;
        return (impl->Functor == f);
    }

// Operators
public:
    operator bool() const
    {
        return !IsEmpty();
    }

    bool operator!() const
    {
        return IsEmpty();
    }

    template <class TFunctor>
    Delegate& operator=(const TFunctor& f)
    {
        DelegateImplBase* d = new DelegateImpl<TFunctor>(f);
        FreeDelegateList(this->_last);
        this->_last = d;
        return *this;
    }

    Delegate& operator=(const Delegate& d)
    {
        if (this != &d)
        {
            DelegateImplBase* list = CloneDelegateList(d._last, NULL);
            FreeDelegateList(this->_last);
            this->_last = list;
        }
        return *this;
    }

    template <class TFunctor>
    Delegate& operator+=(const TFunctor& f)
    {
        Add(f);
        return *this;
    }

    template <class TFunctor>
    friend Delegate operator+(const Delegate& d, const TFunctor& f)
    {
        return (Delegate(d) += f);
    }

    template <class TFunctor>
    friend Delegate operator+(const TFunctor& f, const Delegate& d)
    {
        return (d + f);
    }

    template <class TFunctor>
    Delegate& operator-=(const TFunctor& f)
    {
        Remove(f);
        return *this;
    }

    template <class TFunctor>
    Delegate operator-(const TFunctor& f) const
    {
        return (Delegate(*this) -= f);
    }

    template <class TFunctor>
    friend bool operator==(const Delegate& d, const TFunctor& f)
    {
        return d.Equals(f);
    }

    template <class TFunctor>
    friend bool operator==(const TFunctor& f, const Delegate& d)
    {
        return (d == f);
    }

    template <class TFunctor>
    friend bool operator!=(const Delegate& d, const TFunctor& f)
    {
        return !(d == f);
    }

    template <class TFunctor>
    friend bool operator!=(const TFunctor& f, const Delegate& d)
    {
        return (d != f);
    }

    R operator()(ns_delegate_DELEGATE_FUNCTION_PARAMS) const
    {
        if (this->_last == NULL)
            return _HandleInvalidCall<R>();

        if (this->_last->Previous != NULL)
            InvokeDelegateList(this->_last->Previous ns_delegate_DELEGATE_COMMA ns_delegate_DELEGATE_FUNCTION_ARGS);
        return this->_last->Invoke(ns_delegate_DELEGATE_FUNCTION_ARGS);
    }
};

} // namespace ns_delegate

#undef ns_delegate_DELEGATE_TEMPLATE_PARAMS
#undef ns_delegate_DELEGATE_TEMPLATE_ARGS
#undef ns_delegate_DELEGATE_FUNCTION_PARAMS
#undef ns_delegate_DELEGATE_FUNCTION_ARGS
#undef ns_delegate_DELEGATE_COMMA
