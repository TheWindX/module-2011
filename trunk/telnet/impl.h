#pragma once

#include <map>
#include <deque>

#include "interface.h"
#include "../head/ref_counter.h"
#include "../head/exception.h"


#include "../asio_net/interface.h"

#include "edit_text.h"


#pragma comment(lib,"lua5.1.lib")

namespace ns_base
{
	struct i_telnet;
	namespace ns_telnet
	{
		const int IAC = 255;
		const int reset = 0;
		const int bright = 1;
		const int hidden = 8;
		//foreground
		const int e_fblack = 30;
		const int e_fred = 31;
		const int e_fgreen = 32;
		const int e_fyellow = 33;
		const int e_fblue = 34;
		const int e_fmagenta = 35;
		const int e_fcyan = 36;
		const int e_fwhite = 37;

		//background
		const int e_bblack = 40;
		const int e_bred = 41;
		const int e_bgreen = 42;
		const int e_byellow = 43;
		const int e_bblue = 44;
		const int e_bmagenta = 45;
		const int e_bcyan = 46;
		const int e_bwhite = 47;

		const std::string& set_input_title();

		const std::string& set_output_title();

		const std::string& set_normal_text();

		const std::string& set_console_pos(int x, int y);

		const std::string& get_console_pos();

		const std::string& erase_from_line(int r);
		
		struct st_fsm
		{	
			i_session* m_sess;//TODO, 改成id
			i_telnet* m_command;
			
			
			std::deque<std::pair<bool, std::string> > m_outputs;


			void on_recv_buff(long sz);
			st_fsm(ns_base::i_session* s, i_telnet* tel);

			
			void output(const std::string& str1);
			void input(const std::string& str1);
			void clear();



			st_edit_text m_str;
			//wait状态下刷新
			void refresh();

			enum
			{
				e_init = 0,
				e_new_line,
				e_command_esc,
				e_command_esc1,//'['
				e_row,
				e_col,
				e_command_end,
			};
			int m_status;
			std::string m_col;
			std::string m_row;

			void on_recv(char c);
		};


	};

	//接口导出 
	struct impl_telnet : public virtual i_telnet, public virtual ns_common::impl_ref_counter
	{	
		static std::map<long, ns_telnet::st_fsm*> m_fsms;


		impl_telnet(ns_base::i_server* serv)
		{
			m_status = e_close;
			m_server = serv;
			m_max_line = 120;

			m_server->s_accept += std::make_pair(this, impl_telnet::on_accept);
			m_server->s_listen_error += std::make_pair(this, impl_telnet::on_except);
			m_server->s_session_error += std::make_pair(this, impl_telnet::on_session_break);
		}

		virtual ~impl_telnet()
		{
		}

		void on_accept(long id)
		{
			s_accept(id);
			i_session* sess = m_server->get_session(id);
			ns_telnet::st_fsm* pfsm = new ns_telnet::st_fsm(sess, this);
			m_fsms[id] = pfsm;
		}

		void on_except(long ec)
		{
			m_status = e_close;
			s_except(ec);
		}

		void on_session_break(long id, long ec)
		{
			s_session_break(id, ec);
			remove(id);
		}

		void bind(unsigned short port)
		{
			m_server->bind(port);
		}
		void listen(bool btrue)
		{
			m_server->listen(btrue);
			m_status = e_establish;
		}

		int m_status;
		int get_status()
		{
			return m_status;
		}


		i_server* m_server;
		//遍历
		bool first(long& id)
		{
			i_session* s = m_server->first_session();
			if(!s) return false;

			id = s->get_id();
			return true;
		}

		virtual bool next(long& id)
		{
			i_session* s = m_server->next_session();
			if(!s) return false;

			id = s->get_id();
			return true;
		}

		bool exist(long id)
		{
			i_session* s = m_server->get_session(id);
			if(s) return true;
			return false;
		}

		void remove(long id)
		{
			m_server->remove_session(id);
			std::map<long, ns_telnet::st_fsm*>::iterator it = m_fsms.find(id);
			if(it != m_fsms.end() )
			{
				delete it->second;
			}
		}

		//terminor print
		void output_ostr(long id, const char* str)
		{
			ns_telnet::st_fsm* pfsm = m_fsms[id];
			if(!pfsm)
			{
				RAISE_EXCEPTION("");
				return;
			}
			pfsm->output(str);
		}

		void output_istr(long id, const char* str)
		{
			ns_telnet::st_fsm* pfsm = m_fsms[id];
			if(!pfsm)
			{
				RAISE_EXCEPTION("");
				return;
			}
			pfsm->input(str);
		}

		void clear(long id)
		{
			ns_telnet::st_fsm* pfsm = m_fsms[id];
			if(!pfsm)
			{
				RAISE_EXCEPTION("");
				return;
			}

			pfsm->clear();
		}

		size_t m_max_line;
		void set_max_line(long ln)
		{
			m_max_line = ln;
		}

		size_t get_max_line()
		{
			return m_max_line;
		}
	};



	struct  impl_telnet_srcipt : public i_telnet_srcipt, public impl_telnet
	{	
		std::map<long, i_lua*> m_luas;

		void on_accept(long id);

		void on_command(int id, const char* cmd)
		{
			i_lua* pl = get_script(id);
			if(pl)
			{
				pl->do_string(cmd);
			}
			else
				RAISE_EXCEPTION("");
		}

		impl_telnet_srcipt(i_server* serv) : impl_telnet(serv)
		{	
			s_accept += std::make_pair(this, impl_telnet_srcipt::on_accept);
			s_command_from_client += std::make_pair(this, impl_telnet_srcipt::on_command);
		}

		i_lua* get_script(long id)
		{
			std::map<long, i_lua*>::iterator it = m_luas.find(id);

			if(it != m_luas.end() )
			{
				i_lua* pl = it->second;
				return pl;
			}
			return 0;
		}

		virtual ~impl_telnet_srcipt()
		{
			//std::map<long, i_lua*>::iterator it = m_luas->begin();

			//for(; it != m_luas.end(); ++it)
			//{
			//	i_lua* l = it->second;
			//	l->release();
			//}
		}
	};


	struct h_impl_telnet : h_telnet
	{
		i_telnet* create_telnet()
		{
			ns_base::h_asio_net* han;
			get(han);


			i_server* serv = han->create_server();
			impl_telnet* ret = new impl_telnet(serv);
			return ret;
		}

		i_telnet_srcipt* create_telnet_script()
		{
			ns_base::h_asio_net* han;
			get(han);


			i_server* serv = han->create_server();
			impl_telnet_srcipt* ret = new impl_telnet_srcipt(serv);
			return ret;
		}
	};
}