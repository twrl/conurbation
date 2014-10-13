namespace std {
    
    template <typename T, T v>
    struct integral_constant {
        static constexpr T value = v;
        typedef T value_type;
        typedef integral_constant type;
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator ()() const noexcept { return value; }
    }
    
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
    
    
    
    template <typename T, typename U>
    struct is_same: std::false_type {}
    
    template <typename T>
    struct is_same<T, T>: std::true_type {}
    
    
    
    template <typename T>
    struct remove_const<const T> { typedef T type; }
    
    template <typename T>
    struct remove_const { typedef T type; }
    
    template <typename T>
    struct remove_volatile<volatile T> { typedef T type; }
    
    template <typename T>
    struct remove_volatile { typedef T type; }
    
    template <typename T>
    struct remove_cv { typedef typename remove_volatile<typename remove_const<T>::type>::type type; }
    
    
    
    
    template <typename T>
    struct is_null_pointer: is_same<std::nullptr_t, typename remove_cv<T>::type > {}
    
    template <typename T>
    struct is_void: is_same<void, typename remove_cv<T>::type> {}
    
    template <typename T>
    struct is_union: integral_constant<bool, __is_union(T)> {}
    
    
    
    
    template <typename T>
    struct is_integral: std::false_type {}
    struct is_integral<uint8_t>: std::true_type {}
    struct is_integral<uint16_t>: std::true_type {}
    struct is_integral<uint32_t>: std::true_type {}
    struct is_integral<uint64_t>: std::true_type {}
    struct is_integral<int8_t>: std::true_type {}
    struct is_integral<int16_t>: std::true_type {}
    struct is_integral<int32_t>: std::true_type {}
    struct is_integral<int64_t>: std::true_type {}
    struct is_integral<bool>: std::true_type {}
    struct is_integral<char>: std::true_type {}
    struct is_integral<char16_t>: std::true_type {}
    struct is_integral<char32_t>: std::true_type {}
    
    
    
    
}