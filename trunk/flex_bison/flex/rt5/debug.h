
#pragma once

#include "types.h"
#include "easy_map.h"
#include "easy_set.h"

#include <vector>

namespace ns_core
{
	using namespace ns_base;

	namespace ns_debug
	{
		using namespace ns_base;
		struct st_range
		{
			u32 m_left;
			u32 m_right;

			st_range():m_left(0),m_right(0){}
			st_range(u32 l, u32 r):m_left(l),m_right(r){}


			bool is_NA()
			{
				return m_left == 0 && m_right == 0;
			}

			std::string to_string()const
			{
				std::string ret = "(";
				char buff[256];
				ret += itoa(m_left, buff, 10);
				ret += " ,";
				ret += itoa(m_right, buff, 10);
				ret += "]";
				return ret;
			}
		};



		//这里的比较假设不会出现区域交叉的情况
		inline bool operator<(const st_range& first, const st_range& other)
		{
			if(other.m_left >= first.m_right) return true;
			else return false;
		}

		struct st_range_pair
		{
			st_range m_r1;
			st_range m_r2;

			st_range_pair(u32 r1l, u32 r1r, u32 r2l, u32 r2r):m_r1(r1l, r1r), m_r2(r2l, r2r){}

			std::vector<st_range_pair> split_by(const st_range_pair& other) const;

			std::string to_string()const
			{	
				std::string ret;
				ret = m_r1.to_string();
				ret += "->";
				ret += m_r2.to_string();
				return ret;
			}
		};

		inline std::vector<st_range_pair> st_range_pair::split_by(const st_range_pair& other)const
		{
			std::vector<st_range_pair> ret;
			
			//bool b = m_r1.is_in_range(other.m_r1);
			//assert(b);

			if(m_r1.m_left != other.m_r1.m_left
				||m_r2.m_left != other.m_r2.m_left//TODO, 需要把operator<是否需要更改
				)
			{
				st_range_pair rp(m_r1.m_left, other.m_r1.m_left, m_r2.m_left, other.m_r2.m_left);
				ret.push_back(rp);
			}
			
			ret.push_back(other);

			if(m_r1.m_right != other.m_r1.m_right
				||m_r2.m_right != other.m_r2.m_right)
			{
				st_range_pair rp(other.m_r1.m_right, m_r1.m_right, other.m_r2.m_right, m_r2.m_right);
				ret.push_back(rp);
			}

			return ret;
		}

		//这里的比较假设不会出现区域交叉的情况
		inline bool operator<(const st_range_pair& first, const st_range_pair& second)
		{
			return first.m_r1<second.m_r1;
		}


		struct st_src_text
		{
			void reset(const char* buff, size_t sz);

			//(line , pos_range)
			void analyze();

			u32 get_line_by_pos(u32 idx);
			const char* get_line(u32 ln);

			void on_new_line(u32 idx);

			const char* get_segment(u32 left, u32 right);//TODO, private
			
		private:
			std::string m_src;

			std::vector<st_range> m_ln2pos;
			ns_util::st_map<st_range, u32> m_pos2ln;

			st_range m_range;//temprorate use

			bool get_line_range(u32 ln);
			u32 get_left();
			u32 get_right();
		};


		struct st_debug_src_2_code
		{
			void add(u32 sbegin, u32 send, u32 cbegin, u32 cend);
			void analyze();//整成src <-> code映射
			st_range code2src(u32 code_idx);

		private://(pos_range, code_range)
			typedef ns_core::ns_debug::st_range_pair rp_t;
			ns_util::st_set<rp_t> m_src_code_pairs;

			ns_util::st_map<st_range, st_range> m_src2code;
			ns_util::st_map<st_range, st_range> m_code2src;
		};

		struct st_debug
		{
			st_src_text m_src_text;
			st_debug_src_2_code m_src2code;
			std::string code2line(u32 code_idx);
		};

		extern st_src_text* g_debug;
		extern void on_new_line(size_t idx);//to be use by bison_use
	}


	
}