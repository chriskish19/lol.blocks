/****************************************************************
	Header: lol.math.hpp

	Purpose: some math stuff

****************************************************************/

#pragma once

// errors
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

namespace math {
	template<typename t_float>
	class line {
	public:
		line(t_float m, t_float b) :m_m(m),m_b(b) {}

		t_float get_y(t_float x) {
			return m_m * x + m_b;
		}

	protected:
		t_float m_m;
		t_float m_b;
	};

	template<typename t_float>
	class parabola {
	public:
		parabola(t_float a,t_float b,t_float c) 
		:m_a(a),m_b(b),m_c(c) { }

		t_float get_y(t_float x) {
			return m_a * x * x + m_b * x + m_c;
		}

	protected:
		t_float m_a;
		t_float m_b;
		t_float m_c;
	};
}