#pragma once 

#include <cstdint>

// 寄存器
template<uint32_t address>
class CRegister
{
public:
	uint32_t get() const
	{
		return *reinterpret_cast<volatile uint32_t*>(address);
	}

	void set(uint32_t value)
	{
		*reinterpret_cast<volatile uint32_t*>(address) = value;
	}

	void set(uint32_t value, uint32_t bitmask) const
	{
		uint32_t reg = get();
		reg &= ~bitmask;
		reg |= (value & bitmask);
		*reinterpret_cast<volatile uint32_t*>(address) = reg;
	}

	void set_bits(uint32_t bitmask)
	{
		uint32_t reg = get();
		reg |= bitmask;
		set(reg);
	}

	void clear_bits(uint32_t bitmask)
	{
		uint32_t reg = get();
		reg &= ~bitmask;
		set(reg);
	}
};
