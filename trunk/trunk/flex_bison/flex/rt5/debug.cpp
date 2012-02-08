
#include "debug.h"

namespace ns_core
{
	namespace ns_debug
	{
		st_src_text* g_debug = 0;

		void on_new_line(size_t idx)
		{
			if(g_debug)
				g_debug->on_new_line((u32)idx);
		}

		void st_src_text::on_new_line(u32 idx)
		{
			st_range r;
			if(m_ln2pos.size() != 0)
			{
				r.m_left = m_ln2pos.back().m_right;
			}//default is 0
			;
			r.m_right = idx;
			m_ln2pos.push_back(r);

			m_pos2ln.insert(r, (u32)m_ln2pos.size()-1);
		}

		void st_src_text::reset(const char* buff, size_t sz)
		{
			m_ln2pos.clear();
			m_pos2ln.clear();
			m_src.assign(buff, sz);

			g_debug = this;
		}

		void st_src_text::analyze()
		{
			u32 i = 0;
			for(; i<m_src.size(); ++i)
			{
				if(m_src[i] == '\n')
				{
					on_new_line(i);
				}
			}
			on_new_line(i);
		}

		u32 st_src_text::get_line_by_pos(u32 idx)
		{
			st_range r(idx, idx+1);
			if(m_pos2ln.find(r) )
			{
				return m_pos2ln.get_val();
			}
			return U32_NA;
		}

		bool st_src_text::get_line_range(u32 ln)
		{
			if(ln < m_ln2pos.size() )
			{
				m_range = m_ln2pos[ln];
				return true;
			}
			return false;
		}

		u32 st_src_text::get_left()
		{
			return m_range.m_left;
		}

		u32 st_src_text::get_right()
		{
			return m_range.m_right;
		}

		const char* st_src_text::get_segment(u32 left, u32 right)
		{
			static std::string ret;
			ret = m_src.substr(left, right-left);
			return ret.c_str();
		}

		const char* st_src_text::get_line(u32 ln)
		{
			if(!get_line_range(ln) ) return 0;
			return get_segment(m_range.m_left, m_range.m_right);
		}

		void st_debug_src_2_code::add(u32 sbegin, u32 send, u32 cbegin, u32 cend)
		{

			rp_t rp(sbegin, send, cbegin, cend);
			bool b = m_src_code_pairs.find(rp);
			if(b)
			{
				rp_t rp_found = m_src_code_pairs.get();
				m_src_code_pairs.erase();
				std::vector<rp_t>& rps = rp_found.split_by(rp);
				for(size_t i = 0; i<rps.size(); ++i)
				{
					m_src_code_pairs.insert(rps[i]);
				}
			}
			else
			{
				m_src_code_pairs.insert(rp);
			}

			////TODO, debug print
			//system("cls");
			//for(bool b = m_src_code_pairs.first(); b; b = m_src_code_pairs.next() )
			//{
			//	printf("%s\n", m_src_code_pairs.get().to_string().c_str() );
			//}
			
		}

		void st_debug_src_2_code::analyze()//’˚≥…src <-> code”≥…‰
		{
			for(bool b = m_src_code_pairs.first(); b ; b = m_src_code_pairs.next() )
			{
				const rp_t& rp = m_src_code_pairs.get();
				m_src2code.insert(rp.m_r1, rp.m_r2);
				m_code2src.insert(rp.m_r2, rp.m_r1);
			}
		}

		st_range st_debug_src_2_code::code2src(u32 code_idx)
		{
			st_range tmp(code_idx, code_idx+1);
			bool b = m_code2src.find(tmp);
			if(b)
			{
				return m_code2src.get_val();
			}
			else
			{
				return st_range();
			}
		}

		std::string st_debug::code2line(u32 code_idx)
		{
			st_range r = m_src2code.code2src(code_idx);
			u32 l1 = m_src_text.get_line_by_pos(r.m_left);
			u32 l2 = m_src_text.get_line_by_pos(r.m_right);

			std::string str;
			str += m_src_text.get_line(l1);
			if(l2 != l1)
			{
				str += "...\n";
				str += m_src_text.get_line(l2);
			}
			return str;
		}
	}
}