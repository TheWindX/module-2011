#include "impl.h"


#include "../head/M_interface.h"

#include "impl.h"

#include "../head/exception.h"

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
			buff += "<<< ";
			return buff;
		}

		const std::string& set_output_title()
		{
			static std::string buff;
			buff = "";
			buff.push_back(char(27) );
			buff += "[1;33;40m";
			buff += ">>> ";
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
			buff.clear();

			char cbuff[256] = {0};
			cbuff[0] = 27;
			sprintf(cbuff+1, "[%d;%dH", y, x);

			buff = cbuff;

			return buff;
		}

		const std::string& get_console_pos()
		{
			static std::string buff;

			buff.clear();

			buff.push_back(char(27) );
			buff += "[6n";

			return buff;
		}

		const std::string& erase_from_line(int r)
		{
			static std::string buff;

			buff = set_console_pos(0, r);

			buff.push_back(char(27) );
			buff += "[J";
			return buff;
		}
		void st_fsm::on_recv_buff(long sz)
		{
			static char buff[8092];
			memset(buff, 0, 8092);
			size_t sz1 = m_sess->recv(buff, 8092);
			
			for(size_t i = 0; i<sz1; ++i)
			{
				on_recv(buff[i]);
			}
		}

		st_fsm::st_fsm(i_session* s, i_telnet* tel)
			:m_str(this, 1, 1)
		{	
			m_sess = s;
			m_command = tel;
			m_status = e_init;
			m_col = "";
			m_row = "";
			m_str.m_fsm = this;

			s->s_recv += std::make_pair(this, st_fsm::on_recv_buff);
		}

		void st_fsm::output(const std::string& str1)
		{
			int x = m_str.get_start_posx();
			int y = m_str.get_start_posy();
			
			std::string str = set_console_pos(x, y);
			str += set_output_title();
			str += set_normal_text();
			
			for(size_t i = 0; i<str1.size(); ++i)
			{
				char ch = str1[i];
				if(ch == '\n')
				{
					str.push_back('\r');
				}
				str.push_back(ch);
			}
			
			str += "\r\n";
			str += get_console_pos();

			m_sess->send(str.c_str(), str.size() );
		}

		void st_fsm::input(const std::string& str1)
		{
			int x = m_str.get_start_posx();
			int y = m_str.get_start_posy();

			std::string str = set_console_pos(x, y);
			str += set_input_title();
			str += set_normal_text();

			for(size_t i = 0; i<str1.size(); ++i)
			{
				char ch = str1[i];
				if(ch == '\n')
				{
					str.push_back('\r');
				}
				str.push_back(ch);
			}

			str += "\r\n";
			str += get_console_pos();

			m_sess->send(str.c_str(), str.size() );
		}

		void st_fsm::clear()
		{
			m_str.set_str("");
			m_str.set_start_pos(1, 1);
			refresh();
		}


		//wait状态下刷新
		void st_fsm::refresh()
		{
			std::string cmd;
			int y = m_str.get_start_posy();
			int x = m_str.get_start_posx();
			cmd = erase_from_line(y);
			cmd += set_input_title();
			cmd += set_normal_text();
			cmd += m_str.get_str();
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
			cmd.swap(cmd1);
			
			//cursor位置
			x += m_str.get_posx();
			if(m_str.get_posy() == 0)
			{
				x += m_str.m_title.length();
			}
			y += m_str.get_posy();
			cmd += set_console_pos(x, y);
			
			m_sess->send(cmd.c_str() , cmd.length() );
		}

		void st_fsm::on_recv(char c)
		{
			if(m_status == e_init)
			{
				if(c == char(27) )//<ESC>
				{
					m_status = e_command_esc;
				}
				else if(c == 10)//'\n'
				{
					//输出
					int id = m_sess->get_id();
					const char* str = m_str.m_str.c_str();
					try
					{
						if(std::string("__clear()") == str)
						{
							clear();
						}
						else
						{
							std::string cmd = set_console_pos(m_str.m_start_x, m_str.m_start_y);
							cmd += get_console_pos();
							m_sess->send(cmd.c_str(), cmd.size() );
							m_outputs.push_back(std::make_pair(true, str) );
							m_command->s_command_from_client(m_sess->get_id(), str);
						}

					}
					catch(ns_common::st_exception& ex)
					{
						m_outputs.push_back(std::make_pair(false, std::string(ex.what() ) ) );
					}
					m_str.push_history(m_str.m_str);
					m_str.set_str("");
					return;
				}
				else if(c == 13)//'\r'
				{
					m_status = e_new_line;
					return;	
				}
				else
				{
					if(isprint(c) )
						m_str.on_char(c);
					else
						m_str.on_action(c);
				}
				return ;
			}
			else if(m_status == e_new_line)
			{
				if(c == 10)
				{
					m_str.on_action(VK_RETURN);
					m_status = e_init;
				}
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
					m_str.on_action(VK_UP);
				}
				else if(c == 'B')
				{
					m_status = e_init;
					m_str.on_action(VK_DOWN);
				}
				else if(c == 'C')
				{
					m_status = e_init;
					m_str.on_action(VK_RIGHT);
				}
				else if(c == 'D')
				{
					m_status = e_init;
					m_str.on_action(VK_LEFT);
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
					//获得位置
					m_status = e_init;
					m_str.set_str("");
					int x = atoi(m_col.c_str() );
					int y = atoi(m_row.c_str() );

					int dely = y - this->m_command->get_max_line();
					if(dely > 0)
					{
						m_command->clear(m_sess->get_id() );
						m_str.set_start_pos(1, 1);
					}
					else
					{
						m_str.set_start_pos(1, y);
					}
					m_str.gen_lines();
					
					if(m_outputs.size() != 0)
					{
						std::pair<bool, std::string> cmd = m_outputs.front();
						m_outputs.pop_front();
						if(cmd.first)
						{
							input(cmd.second);
						}
						else
						{
							output(cmd.second);
						}
					}
					else
					{
						refresh();
					}
				}
			}
			else
			{
				RAISE_EXCEPTION("");
			}
		}




	}
	std::map<long, ns_telnet::st_fsm*> impl_telnet::m_fsms;

	static _lua_print(lua_State* st)
	{
		std::string str = lua_tostring(st, 1);
		lua_getglobal(st, "__session_id");
		int id = lua_tonumber(st, -1);
		std::map<long, ns_telnet::st_fsm*>::iterator it = impl_telnet::m_fsms.find(id);
		if(it == impl_telnet::m_fsms.end() ) return 0;

		ns_telnet::st_fsm* pf = it->second;
		
		pf->m_outputs.push_back(std::make_pair(false, str) );
		return 0;
	}


	void impl_telnet_srcipt::on_accept(long id)
	{
		h_script* hs;get(hs);
		i_lua* pl = hs->create_lua();
		m_luas[id] = pl;

		pl->reg_func("__print", _lua_print);

		char buff[256];
		sprintf(buff, "__session_id = %d", id);
		pl->do_string(buff);

		pl->do_string(
			"function print(...)\n\
			local paras = {...};\n\
			local str = \"\";\n\
			for i, v in ipairs(paras) do\n\
			str = str..tostring(v)..\"\t\"\n\
			end\n\
			__print(str)\n\
			end");
	}
}



M_IMPL(ns_base::h_telnet, ns_base::h_impl_telnet);//2. 接口实现
M_OPEN();//3. 模块建立
