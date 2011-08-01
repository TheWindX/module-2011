#pragma once
#include "../head/delegate.h"
#include "../head/ref_counter.h"
#include "../filesystem/interface.h"

namespace ns_base
{
	struct i_file_transfer_syn : public virtual i_ref_counter
	{

		virtual void verbose_on(bool) = 0;
		virtual void set_password(const char* user_name, const char* pass_word) = 0;
		
		virtual void download(const char* remote_path, const char* local_path) = 0;
		virtual void upload(const char* local_path, const char* remote_path) = 0;

		virtual i_buffer* download_buff(const char* remote_path) = 0;
		virtual void upload_buff(i_buffer* buff, const char* remote_path) = 0;

		ns_delegate::Delegate<void(long, long)> s_progress;
	};

	struct h_file_transfer
	{
		virtual i_file_transfer_syn* create_file_transfer(const char* url) = 0;
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_file_transfer, "file_transfer.dll");
