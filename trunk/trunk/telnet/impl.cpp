#include "impl.h"


#include "../head/M_interface.h"

#include "impl.h"


namespace ns_base
{
	namespace ns_telnet
	{

		const std::string& set_input_title()
		{
			static std::string buff;
			buff = "";
			buff.push_back(char(27) );
			buff += "[1;31;40m";
			return buff;
		}

		const std::string& set_output_title()
		{
			static std::string buff;
			buff = "";
			buff.push_back(char(27) );
			buff += "[1;33;40m";

			return buff;
		}

		const std::string& set_normal_text()
		{
			static std::string buff;
			buff = "";
			buff.push_back(char(27) );
			buff += "[1;37;40m";

			return buff;
		}

		const std::string& set_console_pos(int x, int y)
		{
			static std::string buff;

			char cbuff[256] = {0};
			cbuff[0] = 27;
			sprintf(cbuff+1, "[%d;%dH", y, x);

			buff = cbuff;

			return buff;
		}

		const std::string& get_console_pos(int r, int c)
		{
			static std::string buff;

			buff.push_back(char(27) );
			buff += "[6n";

			return buff;
		}

		const std::string& erase_from_line(int r)
		{
			static std::string buff;

			buff = set_console_pos(r, 0);

			buff.push_back(char(27) );
			buff += "[J";
			return buff;
		}
		void st_fsm::on_recv_buff(long sz)
		{
			static char buff[8092];
			size_t sz1 = m_sess->recv(buff, 8092);
			std::printf(buff);
			for(size_t i = 0; i<sz1; ++i)
			{
				on_recv(buff[i]);
			}
		}

		st_fsm::st_fsm(ns_base::i_session* s)
			:m_str(this, 1, 1)
		{
			m_sess = s;
			m_status = e_init;
			m_col = "";
			m_row = "";
			m_str.m_fsm = this;

			s->s_recv += std::make_pair(this, st_fsm::on_recv_buff);
		}

		void st_fsm::output(const std::string& str1)
		{
			std::string str = set_output_title();
			m_sess->send(str.c_str(), str.size() );
			str = set_normal_text();
			m_sess->send(str.c_str(), str.size() );
			m_sess->send(str1.c_str(), str1.size() );
		}

		void st_fsm::input(const std::string& str1)
		{
			std::string str = set_input_title();
			m_sess->send(str.c_str(), str.size() );
			str = set_normal_text();
			m_sess->send(str.c_str(), str.size() );
			m_sess->send(str1.c_str(), str1.size() );
		}


		//wait状态下刷新
		void st_fsm::refresh()
		{
			std::string cmd;
			int y = m_str.get_start_posy();
			int x = m_str.get_start_posx();
			cmd = erase_from_line(y);

			cmd += set_console_pos(1, y);
			cmd += set_input_title();
			cmd += m_str.m_title;
			cmd += set_normal_text();
			cmd += m_str.get_str();
			
			//cursor位置
			x += m_str.get_posx();
			if(m_str.get_posy() == 0)
			{
				x += m_str.m_title.length();
			}
			y += m_str.get_posy();
			cmd += set_console_pos(x, y);
			std::string cmd1 = "";
			for(size_t i = 0; i<cmd.length(); ++i)
			{
				char ch = cmd[i];
				if(ch == '\n')
				{
					cmd1.push_back('\r');
				}
				cmd1.push_back(cmd[i]);
			}
			m_sess->send(cmd1.c_str(), cmd1.size() );
		}

		void st_fsm::on_edit(char c)
		{
			//TODO
			m_str.on_char(c);
		}

		void st_fsm::on_recv(char c)
		{
			if(m_status == e_init)
			{
				if(c == char(27) )
				{
					m_status = e_command_esc;
				}
				else if( c== 10)//NL
				{
					return;
				}
				else if(c == 13)
				{
					m_str.on_char(VK_RETURN);
				}
				else
				{
					//编辑
					m_str.on_char(c);
				}
				return ;
			}
			else if(m_status == e_command_esc)
			{
				if(c == char('[') )
				{
					m_status = e_command_esc1;
					m_row = "";
					m_col = "";
				}
				return;
			}
			else if(m_status == e_command_esc1)
			{
				if(c == 'A')//up
				{
					m_status = e_init;
					m_str.on_char(VK_UP);
				}
				else if(c == 'B')
				{
					m_status = e_init;
					m_str.on_char(VK_DOWN);
				}
				else if(c == 'C')
				{
					m_status = e_init;
					m_str.on_char(VK_RIGHT);
				}
				else if(c == 'D')
				{
					m_status = e_init;
					m_str.on_char(VK_LEFT);
				}
				else if(c == char(';') )
				{
					m_status = e_row;
					return;
				}
				if(isalnum(c) )
					m_row.push_back(c);
			}
			else if(m_status == e_row)
			{
				if(isdigit(c) )
					m_col.push_back(c);
				else
				{
					m_status = e_init;
					m_str.set_str("");
					int x = atoi(m_col.c_str() );
					int y = atoi(m_row.c_str() );
					m_str.set_start_pos(x, y);
					refresh();
				}
			}
			else
			{
				RAISE_EXCEPTION("");
			}
		}


	}
}



M_IMPL(ns_base::h_telnet, ns_base::h_impl_telnet);//2. 接口实现
M_OPEN();//3. 模块建立
