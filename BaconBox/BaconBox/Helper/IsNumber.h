/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_IS_NUMBER_H
#define RB_IS_NUMBER_H

namespace BaconBox {
	template <typename T>
	struct IsNumber {
		static const bool RESULT = false;
	};
	
	template <>
	struct IsNumber<char> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<signed char> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<unsigned char> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<short int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<unsigned short int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<unsigned int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<long int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<unsigned long int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<float> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<double> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsNumber<long double> {
		static const bool RESULT = true;
	};
	
	template <typename T>
	struct IsFloatingPointNumber {
		static const bool RESULT = false;
	};
	
	template <>
	struct IsFloatingPointNumber<float> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsFloatingPointNumber<double> {
		static const bool RESULT = true;
	};

	template <>
	struct IsFloatingPointNumber<long double> {
		static const bool RESULT = true;
	};
	
	template <typename T>
	struct IsIntegerNumber {
		static const bool RESULT = false;
	};
	
	template <>
	struct IsIntegerNumber<char> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsIntegerNumber<signed char> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsIntegerNumber<unsigned char> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsIntegerNumber<short int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsIntegerNumber<unsigned short int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsIntegerNumber<int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsIntegerNumber<unsigned int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsIntegerNumber<long int> {
		static const bool RESULT = true;
	};
	
	template <>
	struct IsIntegerNumber<unsigned long int> {
		static const bool RESULT = true;
	};
}

#endif
