#pragma once
#include <string>
#include <iostream>
#include <map>

#include "interface.h"

#include "../head/ref_counter.h"
#include <boost/filesystem.hpp>

#include "../head/curl/curl.h"
#include "../head/curl/types.h"
#include "../head/curl/easy.h"

namespace ns_base
{
	using ns_common::impl_ref_counter;

	struct impl_file_transfer_syn : public i_file_transfer_syn, public virtual impl_ref_counter
	{
		CURL* m_curl;
		bool m_bfile_or_buffer;
		union
		{
			FILE* m_file;
			i_buffer* m_buffer;
		};
		impl_file_transfer_syn(const char* url);
		~impl_file_transfer_syn();

		void verbose_on(bool);
		void set_password(const char* user_name, const char* pass_word);

		void download(const char* remote_path, const char* local_path);
		void upload(const char* local_path, const char* remote_path);

		i_buffer* download_buff(const char* remote_path);
		void upload_buff(i_buffer* buff, const char* remote_path);
	};

	//接口导出
	struct impl_h_file_transfer : public h_file_transfer
	{
		impl_h_file_transfer();
		~impl_h_file_transfer();

		i_file_transfer_syn* create_file_transfer(const char* url);
	};
}