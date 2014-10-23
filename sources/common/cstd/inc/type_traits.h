namespace std {

    template <typename T, T v>
    struct integral_constant {
        static constexpr T value = v;
        typedef T value_type;
        typedef integral_constant type;
        constexpr operator value_type() const noexcept {
            return value;
        }
        constexpr value_type operator()() const noexcept {
            return value;
        }
    } typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <typename T, typename U>
    struct is_same : std::false_type {
    } template <typename T>
    struct is_same<T, T> : std::true_type {
    } template <typename T>
    struct remove_const<const T> {
        typedef T type;
    } template <typename T>
    struct remove_const {
        typedef T type;
    } template <typename T>
    struct remove_volatile<volatile T> {
        typedef T type;
    } template <typename T>
    struct remove_volatile {
        typedef T type;
    } template <typename T>
    struct remove_cv {
        typedef typename remove_volatile<typename remove_const<T>::type>::type type;
    } template <typename A, typename... B>
      struct _trait_or : integral_constant < bool,
      A::value || _trait_or<B...>::value > {
    } template <typename A, typename... B>
    struct _trait_and : integral_constant<bool, A::value&& _trait_and<B...>::value> {
    } template <typename A, typename... B>
    struct _trait_xor : integral_constant<bool, A::value ^ _trait_xor<B...>::value> {
    } template <typename A>
    struct _trait_not : integral_constant<bool, !A::value> {
    } template <typename T>
    struct is_null_pointer : is_same<std::nullptr_t, typename remove_cv<T>::type> {
    } template <typename T>
    struct is_void : is_same<void, typename remove_cv<T>::type> {
    } template <typename T>
    struct is_union : integral_constant<bool, __is_union(T)> {
    } template <typename T>
    struct is_integral
        : std::_trait_or<is_same<remove_cv<T>, bool_t>, is_same<remove_cv<T>, uint8_t>,
                         is_same<remove_cv<T>, uint16_t>, is_same<remove_cv<T>, uint32_t>,
                         is_same<remove_cv<T>, uint64_t>, is_same<remove_cv<T>, int8_t>,
                         is_same<remove_cv<T>, int16_t>, is_same<remove_cv<T>, int32_t>,
                         is_same<remove_cv<T>, int64_t>, is_same<remove_cv<T>, char_t>,
                         is_same<remove_cv<T>, char16_t>, is_same<remove_cv<T>, char32_t>> {
    }
}