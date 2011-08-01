#include "impl.h"

#include "../head/exception.h"
#include "../head/smart_ptr.h"
#include "../head/utility_new.h"



namespace ns_base
{

	impl_file_transfer_syn::impl_file_transfer_syn(const char* url)
	{
		m_curl = curl_easy_init();
		if(!m_curl)
			RAISE_EXCEPTION("");
		curl_easy_setopt(m_curl, CURLOPT_URL, url);
		//maybe error
		//curl_easy_reset(m_curl)
	}

	impl_file_transfer_syn::~impl_file_transfer_syn()
	{
		if(m_curl)
			curl_easy_cleanup(m_curl);
		
		if(m_bfile_or_buffer)
		{
			if(m_file)
				fclose(m_file);
		}
		else
		{
			m_buffer->release();
		}

	}

	void impl_file_transfer_syn::verbose_on(bool enable)
	{
		if(enable)
			curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
		else
			curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 0);
	}

	void impl_file_transfer_syn::set_password(const char* user_name, const char* pass_word)
	{
		std::string str_user_psw = user_name;
		str_user_psw += ":";
		str_user_psw += pass_word;
		curl_easy_setopt(m_curl, CURLOPT_USERPWD, str_user_psw.c_str() );
	}

	static int my_fwrite(void *buffer, size_t size, size_t nmemb, impl_file_transfer_syn* translater)
	{
		if(translater->m_bfile_or_buffer)
		{
			//file
			if(translater->m_file)
			{
				return fwrite(buffer, size, nmemb, translater->m_file);
			}
		}
		else
		{
			translater->m_buffer->write((char*)buffer, size*nmemb);
			return size*nmemb;
		}
	}

	static int my_progress_func(void *Bar,
		double t, /* dltotal */
		double d, /* dlnow */
		double ultotal,
		double ulnow)
	{
		//printf("%d / %d (%g %%)\n", d, t, d*100.0/t);
		return 0;
	}

	void impl_file_transfer_syn::download(const char* remote_path, const char* local_path)
	{
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &my_fwrite);
		
		m_bfile_or_buffer = true;
		m_file = fopen(local_path, "wb");
		if(!m_file)
		{
			RAISE_EXCEPTION("");
			return;
		}
		
		if(!this->s_progress.IsEmpty() )
		{
			curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, this);
			curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, &my_progress_func);
		}

		curl_easy_perform(m_curl);
	}

	void impl_file_transfer_syn::upload(const char* local_path, const char* remote_path)
	{

	}

	i_buffer* impl_file_transfer_syn::download_buff(const char* remote_path)
	{
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &my_fwrite);

		h_filesystem* hf;
		get(hf);
		i_buffer* p_ret = hf->create_buff("", 0);
		
		m_bfile_or_buffer = false;
		if(!p_ret)
		{
			RAISE_EXCEPTION("");
			return 0;
		}
		m_buffer = p_ret;
		p_ret->add_ref();
		
		//curl_easy_setopt(m_curl, CURLOPT_)

		if(!this->s_progress.IsEmpty() )
		{
			curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, this);
			curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, &my_progress_func);
		}

		curl_easy_perform(m_curl);
	}

	void impl_file_transfer_syn::upload_buff(i_buffer* buff, const char* remote_path)
	{

	}


	//接口导出
	impl_h_file_transfer::impl_h_file_transfer()
	{
		curl_global_init(CURL_GLOBAL_DEFAULT);
		
	}

	impl_h_file_transfer::~impl_h_file_transfer()
	{

		curl_global_cleanup();
	}

	i_file_transfer_syn* impl_h_file_transfer::create_file_transfer(const char* url)
	{
		i_file_transfer_syn* p_file_transfer = new impl_file_transfer_syn(url);
		return p_file_transfer;
	}

}



BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	detect_memory_leaks(true);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}


#include "../head/M_interface.h"

M_IMPL(ns_base::h_file_transfer, ns_base::impl_h_file_transfer);//2. 接口实现
M_OPEN();//3. 模块建立

