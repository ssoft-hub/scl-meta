# Проверка существования оператора на этапе компиляции

## Макроопределения

Для проверки существования операторов определены следующие макроопределения:

```cpp
#define SCL_IS_PREFIX_UNARY_OPERATOR_EXISTS_TRAIT( symbol, Invokable )
#define SCL_IS_POSTFIX_UNARY_OPERATOR_EXISTS_TRAIT( symbol, Invokable )
#define SCL_IS_POSTFIX_UNARY_OPERATOR_WITH_ARGUMENT_EXISTS_TRAIT( symbol, Invokable )
#define SCL_IS_POSTFIX_UNARY_OPERATOR_WITH_ARGUMENTS_EXISTS_TRAIT( symbol, Invokable )
#define SCL_IS_BINARY_OPERATOR_EXISTS_TRAIT( symbol, Invokable )
```

Все эти макроопределения позволяют свормировать структуры и переменные для возможности проверки наличия подходящего оператора. В качестве параметра передается символ оператора и его желаемое наименование.

Макросы явно определяют вспомогательные типы ```Is ## Invokable ## OperatorExistsHelper```, ```Is ## Invokable ## OperatorExists``` и переменную ```inline constexpr bool is_ ## Invokable ## _operator_exists```, поэтому рекомендуется их использовать в отдельных пространствах имен.

## Пример

```cpp
namespace Test // struct, class, etc.
{
    SCL_IS_PREFIX_UNARY_OPERATOR_EXISTS_TRAIT( ++, UnaryPrefixPlusPlus )
    SCL_IS_POSTFIX_UNARY_OPERATOR_EXISTS_TRAIT( ++, UnaryPostfixPlusPlus )
    SCL_IS_POSTFIX_UNARY_OPERATOR_WITH_ARGUMENT_EXISTS_TRAIT( [], SquareBrackets )
}

static constexpr bool a1 = ::Test::is_UnaryPrefixPlusPlus_operator_exists< int >; // true
static constexpr bool a2 = ::Test::is_UnaryPrefixPlusPlus_operator_exists< const int >; // false
static constexpr bool a3 = ::Test::is_UnaryPostfixPlusPlus_operator_exists< int >; // true
static constexpr bool a4 = ::Test::is_UnaryPostfixPlusPlus_operator_exists< const int >; // false
static constexpr bool a5 = ::Test::is_SquareBrackets_operator_exists< int, int >; // false
static constexpr bool a6 = ::Test::is_SquareBrackets_operator_exists< int[10], int >; // true
static constexpr bool a7 = ::Test::is_SquareBrackets_operator_exists< ::std::vector< int >, int >; // true
```

Применение ```::Test::is_UnaryPrefixPlusPlus_operator_exists< int >``` эквивалентно ```::Test::Is_UnaryPrefixPlusPlus_OperatorExists< int >::value``` и ```::Test::Is_UnaryPrefixPlusPlus_OperatorExistsHelper< int >::Type::value```.
