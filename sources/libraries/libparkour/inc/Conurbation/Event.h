namespace Conurbation {
    
    template <typename Ret, typename... Args>
    class Event {
        private:
            
            class InternalDelegate {
                public:
                    virtual Ret operator()(Args) = 0;
                
            }
            
        public:
            
            template <typename Class>
            class MemberDelegate: InternalDelegate {
                private:
                    typedef Ret (Class::*Func)(Args);
                    Class*          inst;
                    Func            func;
                public:
                    MemberDelegate(Class* pinst, Func pfunc) : inst(pinst), func(pfunc) {}
                    virtual Ret operator()(Args ...args) {
                        return (inst->*func)(args);
                    }
            }
            
            class StaticDelegate: InternalDelegate {
                private:
                    typedef Ret (*Func)(Args);
                    Func            func;
                public:
                    StaticDelegate(Func pfunc) : func(pfunc) {}
                    virtual Ret operator()(Args ...args) {
                        return func(args);
                    }
            }
            
            Event& operator += (InternalDelegate* del) {
                // linked listage
                return this;
            }
            
            Ret operator() (Args ...args) {
                // Iterate list and call
            }
    }
    
}