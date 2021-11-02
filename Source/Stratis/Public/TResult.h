#pragma once

#include "CoreMinimal.h"

#include <type_traits>

struct TError {
  TError(const FString &errorMessage) : message(errorMessage) {}
  FString message;
};

template <class T> using TResult = TVariant<T, TError>;

namespace result {

template <class T> inline TResult<typename std::decay<T>::type> ok(T &&value) {
  return TResult<typename std::decay<T>::type>(
      TInPlaceType<typename std::decay<T>::type>(), value);
}

template <class T> TResult<T> error(const TError &error) {
  return TResult<T>(TInPlaceType<TError>(), error);
}

template <class T> bool isSuccessful(const TResult<T> &result) {
  return result.template IsType<T>();
}

template <class T> const T &getValue(const TResult<T> &result) {
  return result.template Get<T>();
}

template <class T> const TError &getError(const TResult<T> &result) {
  return result.template Get<TError>();
}

template <class T> const FString &getErrorMessage(const TResult<T> &result) {
  return result.template Get<TError>().message;
}

template <class T, class R>
inline TResult<R> transform(const TResult<T> &value,
                            TFunction<TResult<R>(const T &)> transformation) {
  if (isSuccessful(value)) {
    return transformation(getValue(value));
  } else {
    return error(getError(value));
  }
}

} // namespace result

// template <class T> class TResult {
// public:
//   TResult(const T &value) : value_(MakeShared<T>(value)), isSuccessful(true)
//   {} TResult(T &&value)
//       : value_(MakeShared<T>(MoveTemp(value))), isSuccessful(true) {}
//   TResult(const TError &error)
//       : error_(MakeShared<T>(error)), isSuccessful(false) {}

//   bool IsSuccessful() const { return isSuccessful; }

//   const T &getResult() const { return value_.Get(); }
//   const TError &getError() const { return error_.Get(); }

// private:
//   TSharedPtr<T> value_;
//   TSharedPtr<T> error_;
//   bool isSuccessful;
// };

// template <class T> class TResult {
// public:
//   virtual ~TResult() {}
//   virtual bool IsSuccessful() const = 0;

//   virtual const T &getResult() const { throw 0; }
//   virtual const TError &getError() const { throw 0; }
// };

// namespace result {

// namespace impl {

// template <class T> class TSuccessResult : public TResult<T> {
// public:
//   TSuccessResult(const T &value) : value_(value) {}

//   bool IsSuccessful() const override { return true; }

//   const T &getResult() const override { return value_; }

// private:
//   T value_;
// };

// template <class T> class TFailureResult : public TResult<T> {
// public:
//   TFailureResult(const TError &error) : error_(error) {}

//   bool IsSuccessful() const override { return false; }
//   const TError &getError() const override { return error_; }

//   // template <class S>
//   // virtual TResult<S>
//   // transform(TFunction<TResult<S>(const T &)> transformation) = 0;

// private:
//   TError error_;
// };

// } // namespace impl

// template <class T> inline TResult<typename std::decay<T>::type> ok(T &&value)
// {
//   return TResult<typename std::decay<T>::type>(value);
// }

// template <class T> inline TResult<T> error(const TError &error) {
//   return TResult<T>(error);
// }

// template <class T, class R>
// inline TUniquePtr<TResult<R>>
// transform(const TResult<T> &value,
//           TFunction<TResult<R>(const T &)> transformation) {
//   return nullptr;
// }

// } // namespace result