#pragma once

#include "..\math\math.hpp"
#include <string>

namespace seed
{
	class Window
	{
	public:
		Window(void);
		~Window(void);

	public:
		virtual const bool Initalize(const std::string & caption, const math::float2 & size);
		virtual const bool Run(void);
		virtual const bool Finalize(void);

	private:
		virtual void * const getHwnd(void);

	public:
		virtual const math::float2 & getSize(void);
		virtual const std::string & getCaption(void);
		template<class _Type> const _Type getHwnd(void) { return static_cast<_Type>(this->getHwnd()); }

	private:
		class Impl;

		std::unique_ptr<Impl> impl_;
	};
}