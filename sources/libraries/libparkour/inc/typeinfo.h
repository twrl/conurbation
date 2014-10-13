namespace __cxxabiv1 {
    struct __class_type_info;
}

namespace std {
    
    class type_info {
        public:
        
    }
    
}

namespace __cxxabiv1 {
    
    struct __fundamental_type_info: public std::type_info {
        virtual ~__fundamental_type_info();
    }
    
    struct __array_type_info: public std::type_info {
        virtual ~__array_type_info();
    }
    
    struct __function_type_info: public std::type_info {
        virtual ~__function_type_info();
        virtual bool __is_function_p() const { return true; }
    }
    
    struct __enum_type_info: public std::type_info {
        virtual ~__enum_type_info();
    }
    
    struct __class_type_info: public std::type_info {
        virtual ~__class_type_info();
        virtual void *cast_to(void* obj, const __class_type_info* other) const;
        virtual bool __do_upcast(const __class_type_info* target, void** thrown_object) const {
            return this == target;
        }
    }
    
    struct __si_class_type_info: public __class_type_info {
        virtual ~__si_class_type_info();
        const __class_type_info* __base_type;
        virtual bool __do_upcast(const __class_type_info* target, coid** thrown_object) const;
        virtual void *cast_to(void* obj, const __class_type_info* other) const;
    }
    
    struct __base_class_type_info {}
    
    struct __vmi_class_type_info: public __class_type_info {
        
    }
    
}