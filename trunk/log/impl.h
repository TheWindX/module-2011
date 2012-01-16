#pragma once
#include "interface.h"

#include "../head/ref_counter.h"
#include "../head/smart_ptr.h"

#include "../filesystem/interface.h"
#include "../data/interface.h"
#include "../datetime/interface.h"
#include "../driver/interface.h"

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>

#include "../head/thread.h"

#include "../console/interface.h"


namespace ns_base
{
	using namespace ns_common;

	//log out type
	enum
	{
		e_console_log = 0,
		e_file_log,
	};

	//log format token type
	enum
	{	
		e_name = 0,
		e_time,
		e_lv,
		e_content,
		e_token_str,
	};

	//log level
	const char* get_lv_str(int lv)
	{
		if(lv == e_info)
		{
			return "info";
		}
		else if(lv == e_warning)
		{
			return "warning";
		}
		else if(lv == e_error)
		{
			return "error";
		}
		else if(lv == e_fatal)
		{
			return "fatal";
		}
		else return "";
	}

	struct st_format
	{
		int m_format_flag;
		std::string m_str;
	};

	struct log_config_base
	{
		std::string m_name;

		bool m_on;//是否打开
		int m_lv;//打开等级

		std::vector<st_format> m_format;

		std::string format(const char* cont)
		{
			std::string ret;

			for(size_t i=0; i<m_format.size(); ++i)
			{
				st_format f = m_format[i];
				if(f.m_format_flag == e_name)
				{
					ret += m_name;
				}
				else if(f.m_format_flag == e_time)
				{
					ns_base::h_datetime * i_dt;
					ns_base::get(i_dt);
					ret += i_dt->now_local_format("%M_%D %h:%m:%s");
				}
				else if(f.m_format_flag == e_lv)
				{
					ret += get_lv_str(m_lv);
				}
				else if(f.m_format_flag == e_token_str)
				{
					ret += f.m_str;
				}
				else if(f.m_format_flag == e_content)
				{
					ret += cont;
				}
			}
			return ret;
		}

		virtual void output(const char* cont) = 0;

		log_config_base(const char* name):m_name(name),m_on(true),m_lv(e_info)
		{
			st_format f1;
			f1.m_format_flag = e_name;
			m_format.push_back(f1);
			f1.m_format_flag = e_token_str;
			f1.m_str = " ";
			m_format.push_back(f1);

			f1.m_format_flag = e_time;
			m_format.push_back(f1);
			f1.m_format_flag = e_token_str;
			f1.m_str = " ";
			m_format.push_back(f1);

			f1.m_format_flag = e_lv;
			m_format.push_back(f1);
			f1.m_format_flag = e_token_str;
			f1.m_str = " ";
			m_format.push_back(f1);

			f1.m_format_flag = e_content;
			m_format.push_back(f1);
		}

		log_config_base():m_name(""),m_on(true),m_lv(e_info)
		{
			st_format f1;
			f1.m_format_flag = e_name;
			m_format.push_back(f1);
			f1.m_format_flag = e_token_str;
			f1.m_str = " ";
			m_format.push_back(f1);

			f1.m_format_flag = e_time;
			m_format.push_back(f1);
			f1.m_format_flag = e_token_str;
			f1.m_str = " ";
			m_format.push_back(f1);

			f1.m_format_flag = e_lv;
			m_format.push_back(f1);
			f1.m_format_flag = e_token_str;
			f1.m_str = " ";
			m_format.push_back(f1);

			f1.m_format_flag = e_content;
			m_format.push_back(f1);
		}
	};

	struct log_config_console : public log_config_base
	{
		int m_fc;//前景
		int m_bc;//后景

		log_config_console():m_fc(ns_base::white), m_bc(ns_base::black){};
		void output(const char* cont)
		{
			if(!m_on) return;
			std::string str_out = format(cont);
			//设置前景， 后景
			ns_base::h_console* p_console;
			ns_base::get(p_console);

			p_console->set_text_color(m_fc, m_bc);

			std::cout<<str_out<<std::endl;
		}
	};


	struct log_config_file : public log_config_base
	{
		typedef ns_base::i_write_file file_t;
		ns_common::smart_ptr<file_t> m_file;

		log_config_file()
		{
			//std::cout<<"log_config_file"<<this<<std::endl;
		}

		~log_config_file()
		{
			//std::cout<<"~log_config_file"<<this<<std::endl;
		}
		void make_name(const char* name)
		{
			using namespace ns_base;
			ns_base::h_filesystem* p_fs = 0;
			ns_base::get(p_fs);
			
			ns_base::h_datetime* p_dt = 0;
			ns_base::get(p_dt);

			
			//文件名称
			const char* fname = p_dt->now_local_format("%Y_%M_%D_%h_%m.txt");
			//路径
			std::string str_path = p_fs->get_module_path();
			str_path = p_fs->parent_path(str_path.c_str() );
			str_path = p_fs->append(str_path.c_str(), "log");
			str_path = p_fs->append(str_path.c_str(), m_name.c_str() );
			p_fs->make_directories(str_path.c_str() );
			str_path = p_fs->append(str_path.c_str(), fname);

			ns_base::i_write_file* p_file = p_fs->create_write_file(str_path.c_str(), true);
			m_file.reset(p_file);
		}

		void output(const char* cont)
		{
			if(!m_on) return;
			if(m_file.get() == 0)
			{
				make_name(m_name.c_str() );
			}
			std::string str_out = format(cont);

			m_file->write(str_out.c_str(), str_out.size() );
			m_file->write("\n", 1);
		}
	};

	struct st_token
	{
		size_t m_l, m_r;
		st_format m_format;

		bool operator<(const st_token& right)
		{
			return m_l<right.m_l;
		}
	};

	struct impl_logger : public h_logger
	{	
		std::map<std::string, log_config_console> m_log_configs_console;
		std::map<std::string, log_config_file> m_log_configs_file;

		CRITICAL_SECTION m_cs;

		void release()
		{
			locker lock(&m_cs);
			m_log_configs_file.clear();
			m_log_configs_console.clear();
		}

		impl_logger()
		{
			InitializeCriticalSection(&m_cs);
			//ns_base::h_driver* p_drv;
			//ns_base::get(p_drv);
			//p_drv->get_post_delegate(stage_level) += std::make_pair(this, impl_logger::clean );
			//主动release()
		}

		~impl_logger()
		{
			DeleteCriticalSection(&m_cs);
		}


		void console_on(const char* name, bool on)
		{
			locker lock(&m_cs);
			log_config_console& config = m_log_configs_console[name];
			config.m_name = name;
			m_log_configs_console[name].m_on = on;
		}

		bool is_console_on(const char* name)
		{
			locker lock(&m_cs);
			log_config_console& config = m_log_configs_console[name];
			config.m_name = name;
			return m_log_configs_console[name].m_on;
		}

		void set_console_lv(const char* name, int lv)
		{
			locker lock(&m_cs);
			log_config_console& config = m_log_configs_console[name];
			config.m_name = name;
			m_log_configs_console[name].m_lv = lv;
		}

		int get_console_lv(const char* name)
		{
			locker lock(&m_cs);
			log_config_console& config = m_log_configs_console[name];
			config.m_name = name;
			return m_log_configs_console[name].m_lv;
		}

		void set_console_color_for_name(const char* name, int fc, int bc)
		{
			locker lock(&m_cs);
			log_config_console& config = m_log_configs_console[name];
			config.m_name = name;
			config.m_fc = fc;
			config.m_bc = bc;
		}

		void get_console_color_for_name(const char* name, int& fc, int& bc)
		{
			locker lock(&m_cs);
			log_config_console& config = m_log_configs_console[name];
			config.m_name = name;
			fc = config.m_fc;
			bc = config.m_bc;
		}

		void set_console_format(const char* name, const char* format)
		{
			locker lock(&m_cs);
			log_config_console& config = m_log_configs_console[name];
			config.m_name = name;
			config.m_format.clear();
			//split
			/************************************************************************/
			/* %level, %time, %name                                                                     */
			/************************************************************************/
			std::string str_format = format;

			st_token tmp;
			std::vector<st_token> m_tokens;
			size_t pos = str_format.find("%level");
			if(pos != str_format.npos)
			{	
				tmp.m_l = pos;tmp.m_r = pos+6;tmp.m_format.m_format_flag = e_lv;
				m_tokens.push_back(tmp);
			}

			pos = str_format.find("%name");
			if(pos != str_format.npos)
			{	
				tmp.m_l = pos;tmp.m_r = pos+5;tmp.m_format.m_format_flag = e_name;
				m_tokens.push_back(tmp);
			}

			pos = str_format.find("%time");
			if(pos != str_format.npos)
			{	
				tmp.m_l = pos;tmp.m_r = pos+5;tmp.m_format.m_format_flag = e_time;
				m_tokens.push_back(tmp);
			}

			pos = str_format.find("%content");
			if(pos != str_format.npos)
			{	
				tmp.m_l = pos;tmp.m_r = pos+8;tmp.m_format.m_format_flag = e_content;
				m_tokens.push_back(tmp);
			}
			std::sort(m_tokens.begin(), m_tokens.end() );

			pos = 0;
			for(size_t i = 0; i<m_tokens.size(); ++i)
			{
				st_token& t = m_tokens[i];
				if(pos<t.m_l)
				{
					st_format fmt;
					fmt.m_format_flag = e_token_str;
					fmt.m_str = str_format.substr(pos, t.m_l-pos);
					config.m_format.push_back(fmt);
				}
				config.m_format.push_back(t.m_format);
				pos = t.m_r;
			}

			if(pos<str_format.length())
			{
				st_format fmt;
				fmt.m_format_flag = e_token_str;
				fmt.m_str = str_format.substr(pos);
				config.m_format.push_back(fmt);
			}
		}

		const char* get_console_format(const char* name)
		{
			locker lock(&m_cs);
			log_config_console& config = m_log_configs_console[name];
			config.m_name = name;
			static std::string str_ret;
			str_ret = m_log_configs_console[name].m_name;
			return str_ret.c_str();
		}


		//file out
		void file_on(const char* name, bool on = true)
		{
			locker lock(&m_cs);
			log_config_file& config = m_log_configs_file[name];
			config.m_name = name;
			config.m_on = on;
		}

		bool is_file_on(const char* name)
		{
			locker lock(&m_cs);
			log_config_file& config = m_log_configs_file[name];
			config.m_name = name;
			return config.m_on;
		}

		void set_file_lv(const char* name, int lv)
		{
			locker lock(&m_cs);
			log_config_file& config = m_log_configs_file[name];
			config.m_name = name;
			config.m_lv = lv;
		}

		int get_file_lv(const char* name)
		{
			locker lock(&m_cs);
			log_config_file& config = m_log_configs_file[name];
			config.m_name = name;
			return config.m_lv;
		}

		void set_file_format(const char* name, const char* format)
		{
			locker lock(&m_cs);
			log_config_file& config = m_log_configs_file[name];
			config.m_name = name;
			config.m_format.clear();
			//split
			/************************************************************************/
			/* %level, %time, %name                                                                     */
			/************************************************************************/
			std::string str_format = format;

			st_token tmp;
			std::vector<st_token> m_tokens;
			size_t pos = str_format.find("%level");
			if(pos != str_format.npos)
			{	
				tmp.m_l = pos;tmp.m_r = pos+6;tmp.m_format.m_format_flag = e_lv;
				m_tokens.push_back(tmp);
			}

			pos = str_format.find("%name");
			if(pos != str_format.npos)
			{	
				tmp.m_l = pos;tmp.m_r = pos+5;tmp.m_format.m_format_flag = e_name;
				m_tokens.push_back(tmp);
			}

			pos = str_format.find("%time");
			if(pos != str_format.npos)
			{	
				tmp.m_l = pos;tmp.m_r = pos+5;tmp.m_format.m_format_flag = e_time;
				m_tokens.push_back(tmp);
			}

			pos = str_format.find("%content");
			if(pos != str_format.npos)
			{	
				tmp.m_l = pos;tmp.m_r = pos+8;tmp.m_format.m_format_flag = e_content;
				m_tokens.push_back(tmp);
			}
			std::sort(m_tokens.begin(), m_tokens.end() );

			pos = 0;
			for(size_t i = pos; i<m_tokens.size(); ++i)
				{
					st_token& t = m_tokens[i];
					if(pos<t.m_l)
					{
						st_format fmt;
						fmt.m_format_flag = e_token_str;
						fmt.m_str = str_format.substr(pos, t.m_l-pos);
						config.m_format.push_back(fmt);
					}
					config.m_format.push_back(t.m_format);
					pos = t.m_r;
				}

				if(pos<str_format.length())
				{
					st_format fmt;
					fmt.m_format_flag = e_token_str;
					fmt.m_str = str_format.substr(pos);
					config.m_format.push_back(fmt);
				}
		}

		const char* get_file_format(const char* name)
		{
			locker lock(&m_cs);
			//TODO
			log_config_file& config = m_log_configs_file[name];
			config.m_name = name;
			static std::string str_ret;
			str_ret = config.m_name;
			return str_ret.c_str();
		}

		void write(const char* name, int lv, const char* cont)
		{
			locker lock(&m_cs);
			log_config_console& config_console = m_log_configs_console[name];
			config_console.m_name = name;

			if(lv>=config_console.m_lv)
			{
				config_console.output(cont);
			}

			log_config_file& config_file = m_log_configs_file[name];
			config_file.m_name = name;

			if(lv>=config_file.m_lv)
			{
				config_file.output(cont);
			}
		}
	};
}