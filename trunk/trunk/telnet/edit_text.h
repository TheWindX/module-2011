
#pragma once

#include <vector>
#include <string>


namespace ns_base
{

	namespace ns_telnet
	{
		struct st_fsm;

		struct st_edit_text
		{
			static const size_t max_his = 5;

			std::string m_his[max_his];
			size_t m_his_idx;
			void push_history(const std::string& str)
			{
				m_his_idx = m_his_idx+1%max_his;
				m_his[m_his_idx] = str;
			}
			const std::string& pre_history()
			{
				if(m_his_idx == 0) m_his_idx = max_his-1;
				else m_his_idx--;
				return m_his[m_his_idx];
			}
			const std::string& post_history()
			{
				if(m_his_idx == max_his-1) m_his_idx = 0;
				else m_his_idx++;
				return m_his[m_his_idx];
			}
			
			st_fsm* m_fsm;
			//光标位置
			int get_posx();
			int get_posy();

			//起始位置
			int get_start_posx();
			int get_start_posy();

			void set_start_pos(int col, int row);

			std::string get_str();
			void set_str(const std::string& str);

			void on_action(char ch);
			void on_char(char ch);


			//////////////////////////////////////////////////////////////////////////
			std::string m_str;
			size_t m_pos;

			std::string m_title;

			size_t m_start_x;
			size_t m_start_y;


			std::vector<std::string> m_lines;
			std::vector<size_t> m_locations_1;
			std::vector<size_t> m_locations_2;
			size_t m_x;
			size_t m_y;

			st_edit_text(st_fsm* fsm, size_t x, size_t y)
				:m_fsm(fsm),
				m_str(""),
				m_his_idx(0),
				m_pos(0),
				m_title("<<< "),
				m_start_x(x),
				m_start_y(y),
				m_x(0),
				m_y(0)
			{	
			}

			//////////////////////////////////////////////////////////////////////////
			void gen_lines();
			void gen_pos();

			void insert_char(char ch);
		};


	}
}