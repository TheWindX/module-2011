#pragma once

#include <map>

#include "interface.h"
#include "../head/ref_counter.h"
#include "../head/exception.h"


#include "../asio_net/interface.h"

#include "edit_text.h"

namespace ns_base
{

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

		const std::string& get_console_pos(int r, int c);

		const std::string& erase_from_line(int r);
		
		struct st_fsm
		{
			void on_recv_buff(long sz);
			st_fsm(ns_base::i_session* s);

			ns_delegate::Delegate<void(int, const char*)> s_command;
			i_session* m_sess;//TODO, 改成id
			void output(const std::string& str1);
			void input(const std::string& str1);

			st_edit_text m_str;
			//wait状态下刷新
			void refresh();

			enum
			{
				e_init = 0,
				e_command_esc,
				e_command_esc1,//'['
				e_row,
				e_col,
				e_command_end,
				

			};
			int m_status;
			std::string m_col;
			std::string m_row;
			void on_edit(char c);

			void on_recv(char c);
		};


	};

	//接口导出 
	struct impl_telnet_commander : public i_telnet_commander, public virtual ns_common::impl_ref_counter
	{	
		std::map<long, ns_telnet::st_fsm*> m_fsms;


		impl_telnet_commander(ns_base::i_server* serv)
		{
			m_status = e_close;
			m_server = serv;

			m_server->s_accept += std::make_pair(this, impl_telnet_commander::on_accept);
			m_server->s_listen_error += std::make_pair(this, impl_telnet_commander::on_except);
			m_server->s_session_error += std::make_pair(this, impl_telnet_commander::on_session_break);
		}

		void on_accept(long id)
		{
			s_accept(id);
			i_session* sess = m_server->get_session(id);
			ns_telnet::st_fsm* pfsm = new ns_telnet::st_fsm(sess);
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
			m_server->remove_session(id);
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
		bool first(unsigned int& id)
		{
			i_session* s = m_server->first_session();
			if(!s) return false;

			id = s->get_id();
			return true;
		}

		virtual bool next(unsigned int& id)
		{
			i_session* s = m_server->next_session();
			if(!s) return false;

			id = s->get_id();
			return true;
		}

		virtual bool exist(unsigned int id)
		{
			i_session* s = m_server->get_session(id);
			if(s) return true;
			return false;
		}

		//terminor print
		void output_ostr(unsigned int id, const char* str)
		{
			ns_telnet::st_fsm* pfsm = m_fsms[id];
			if(!pfsm)
			{
				RAISE_EXCEPTION("");
				return;
			}
			pfsm->output(str);
		}

		void output_istr(unsigned int id, const char* str)
		{
			ns_telnet::st_fsm* pfsm = m_fsms[id];
			if(!pfsm)
			{
				RAISE_EXCEPTION("");
				return;
			}
			pfsm->input(str);
		}
	};


	struct h_impl_telnet : h_telnet
	{
		i_telnet_commander* create_telnet()
		{
			ns_base::h_asio_net* han;
			get(han);


			i_server* serv = han->create_server();
			impl_telnet_commander* ret = new impl_telnet_commander(serv);
			return ret;
		}
	};
}