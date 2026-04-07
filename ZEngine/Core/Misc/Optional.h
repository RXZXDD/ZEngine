#pragma once

template<class T>
struct TOptional
{
	using ValueType = T;
	ValueType Value;
	bool bHasValue = false;
	public:
		TOptional() {};
		TOptional(ValueType&& Val) {
			SetValue(std::forward(Val));
		}
		TOptional(const ValueType& Val) {
			SetValue(std::forward(Val));
		}
		TOptional(bool inVal) {
			bHasValue = inVal;
		}

		void Reset() {
			Value = nullptr;
			bHasValue = false;
		}

		ValueType GetValue() const {
			if (bHasValue) {
				return Value;
			}
			//TODO: throw exception or assert
			return nullptr;
		}

		bool HasValue() const {
			return bHasValue;
		}

		void SetValue(T&& Val) {
			Value = std::move(Val);
			bHasValue = true;
		}
		//TODO unique_ptr free unimplemented
		~TOptional() {
			if (bHasValue) {
				bHasValue = false;
			}
		}
};