

#include "edit_text.h"
#include "impl.h"
#include <sstream>
namespace ns_base
{

	namespace ns_telnet
	{
		//光标位置
		int st_edit_text::get_posx()
		{
			return m_x;
		}
		int st_edit_text::get_posy()
		{
			return m_y;
		}

		//起始位置
		int st_edit_text::get_start_posx()
		{
			return m_start_x;
		}

		int st_edit_text::get_start_posy()
		{
			return m_start_y;
		}

		void st_edit_text::set_start_pos(int col, int row)
		{
			m_start_x = col;
			m_start_y = row;
		}

		std::string st_edit_text::get_str()
		{
			return m_str;
		}

		void st_edit_text::set_str(const std::string& str)
		{
			m_str = str;
			m_pos = m_str.length();
		}

		void st_edit_text::on_action(char ch)
		{
			gen_lines();
			//这里edit, 并refresh
			if(ch == 12)//ctrl+j
			{
				this->set_str(pre_history() );
			}
			else if(ch == 11)//ctrl+k
			{
				this->set_str(post_history() );
			}
			else if(ch == VK_UP)
			{
				if(m_y == 0) return;
				m_y--;
				size_t len = m_lines[m_y].length();
				m_x = m_x>len? len:m_x;
				gen_pos();
			}
			else if(ch == VK_DOWN)
			{
				if(m_y == m_lines.size()-1 ) return;
				m_y++;
				size_t len = m_lines[m_y].length();
				m_x = m_x>len? len:m_x;
				gen_pos();
			}
			else if(ch == VK_LEFT)
			{
				if(m_pos == 0) return;
				m_pos--;
			}
			else if(ch == VK_RIGHT)
			{
				if(m_pos == m_str.length() ) return;
				m_pos++;
			}
			else if( ch == VK_RETURN)
			{
				insert_char('\n');
			}
			else if( ch == VK_BACK)
			{
				if(m_pos != 0)
				{
					m_pos--;
					m_str.erase(m_pos, 1);
				}
			}
			else if(ch == 127)//DEL
			{
				if(m_pos == m_str.length() ) return;
				m_str.erase(m_pos, 1);
			}

			gen_lines();
			m_fsm->refresh();
		}

		void st_edit_text::on_char(char ch)
		{	
			gen_lines();
			insert_char(ch);
			gen_lines();
			m_fsm->refresh();
		}


		void st_edit_text::gen_lines()
		{
			m_locations_1.clear();
			m_locations_2.clear();
			m_lines.clear();

			if(m_pos > m_str.length() ) m_pos = m_str.length();

			std::stringstream ss(m_str);
			std::string line = "";
			size_t pos = 0;
			do 
			{
				getline(ss, line, '\n');
				m_lines.push_back(line);
				size_t right = ss.tellg();
				size_t left = pos;
				pos = right;
				if(m_str == "")
				{
					right = 1;
					left = 0;
				}
				if(m_pos>=left)
				{	
					m_y = m_lines.size()-1;
					m_x = m_pos-left;
				}
				m_locations_1.push_back(left);
				m_locations_2.push_back(right );

			} while (!ss.eof() );
		}

		void st_edit_text::gen_pos()
		{
			m_pos = m_locations_1[m_y]+m_x;
		}

		void st_edit_text::insert_char(char ch)
		{
			std::string left, right = "";
			left = m_str.substr(0, m_pos);
			left.push_back(ch);

			if(m_pos != m_str.length() )
			{
				right = m_str.substr(m_pos, std::string::npos);
			}

			m_str = left+right;
			m_pos++;
		}

	}
}