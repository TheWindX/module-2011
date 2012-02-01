#include "impl.h"

#include "../head/exception.h"
#include "../head/smart_ptr.h"
#include "../head/utility_new.h"



namespace ns_base
{
	std::vector<std::string*> m_string_pool;

	std::string& alloc_string(const char* str)
	{
		h_filesystem* hf;
		get(hf);

		m_string_pool.push_back(new std::string(str) );
		return *m_string_pool.back();
	}

	//返回当前路径
	const char* impl_path_iter::get_path()
	{
		fs::directory_iterator end_itr;
		if(m_it != end_itr)
		{
			std::string& g_str_ret = alloc_string("");
			g_str_ret = m_it->path().string();
			return g_str_ret.c_str();
		}
		return 0;
	}

	//如果返回 0, 迭代完成
	void impl_path_iter::next()
	{
		m_it++;
	}

	bool impl_path_iter::is_directory()
	{	
		return fs::is_directory(m_it->path() );
	}

	//指针
	void* impl_buffer::ptr()
	{
		return &m_buff[0];
	}
	//大小
	long impl_buffer::size()
	{
		return m_buff.size();
	}

	void impl_buffer::resize(long sz)
	{
		m_buff.resize(sz);
	}

	void impl_buffer::write(const char* ptr, long len)
	{	
		long sz = m_buff.size();
		long new_sz = sz+len;
		m_buff.resize(new_sz);

		memcpy(&m_buff[sz], ptr, len );
	}

	size_t impl_read_file::read(void* buffer, size_t sz_to_read)
	{
		if(m_file == 0)
			return 0;

		return fread(buffer, 1, sz_to_read, m_file);
	}

	i_buffer* impl_read_file::read_all()
	{
		if(m_file == 0)
			return 0;

		const size_t sz_chunk = 1024;
		impl_buffer* p_buff = new impl_buffer;
		p_buff->m_buff.resize(m_sz_file);
		
		void* p_idx = &(p_buff->m_buff[0]);
		size_t rlen = 0;
		do
		{
			rlen = fread(p_idx, sizeof(char), sz_chunk, m_file);
			p_idx = (char*)p_idx+rlen;
		}while(rlen>0 && rlen == sz_chunk);
		return p_buff;
	}

	bool impl_read_file::seek(long final_pos, bool relative)
	{
		if (m_file == 0)
			return 0;

		return fseek(m_file, final_pos, relative ? SEEK_CUR : SEEK_SET) == 0;
	}

	size_t impl_read_file::size() const
	{
		return m_sz_file;
	}

	size_t impl_read_file::pos() const
	{
		return ftell(m_file);
	}

	impl_read_file::impl_read_file(const char* file_name)
	{
		m_file_name = file_name;
		m_file = fopen(file_name, "rb");

		if (m_file)
		{
			fseek(m_file, 0, SEEK_END);
			m_sz_file = ftell(m_file);
			fseek(m_file, 0, SEEK_SET);
		}
	}

	impl_read_file::~impl_read_file()
	{
		if(m_file)
			fclose(m_file);
	}

	size_t impl_write_file::write(const void* buffer, size_t sz_to_write)
	{
		if (m_file == 0)
			return 0;

		return fwrite(buffer, 1, sz_to_write, m_file);
	}

	bool impl_write_file::seek(long final_pos, bool relative)
	{
		if (m_file == 0)
			return 0;

		return fseek(m_file, final_pos, relative ? SEEK_CUR : SEEK_SET) == 0;
	}

	size_t impl_write_file::pos() const
	{
		return ftell(m_file);
	}

	impl_write_file::impl_write_file(const char* file_name, bool append)
	{
		m_file_name = file_name;

		m_file = fopen(file_name, append ? "ab" : "wb");
		if (m_file)
		{
			fseek(m_file, 0, SEEK_END);
			m_sz_file = ftell(m_file);
			fseek(m_file, 0, SEEK_SET);
			return;
		}
		else
		{
			RAISE_EXCEPTION("");
		}
	}
	impl_write_file::~impl_write_file()
	{
		if(m_file)
			fclose(m_file);
	}


	impl_fs_pak::impl_fs_pak(const char* location)
	{
		h_filesystem* hf;
		get(hf);
		this->m_loaction = location;
	}

	impl_fs_pak::~impl_fs_pak()
	{
		std::map<std::string, i_buffer*>::iterator it = m_cache.begin();
		for(;it != m_cache.end(); ++it)
		{
			i_buffer* buff = it->second;
			buff->release();
		}
	}

	bool impl_fs_pak::exist(const char* cpath)
	{
		using namespace ns_common;

		//TODO, 优化流程
		h_filesystem* hf;
		get(hf);

		std::string str_path = hf->append(m_loaction.c_str(), cpath);
		str_path = hf->system_complete(str_path.c_str() );

		std::map<std::string, i_buffer*>::iterator it = m_cache.find(str_path );
		if(it != m_cache.end())
		{
			return true;
		}
		bool ret = hf->exists(str_path.c_str() );
		return ret;
	}

	i_buffer* impl_fs_pak::get_buffer(const char* path)
	{
		using namespace ns_common;
		//TODO, 优化流程
		h_filesystem* hf;
		get(hf);

		std::string str_path;
		str_path = hf->append(m_loaction.c_str(), path);
		str_path = hf->system_complete(str_path.c_str() );

		std::map<std::string, i_buffer*>::iterator it = m_cache.find(str_path.c_str() );

		if(it != m_cache.end())
		{
			return it->second;
		}

		if(hf->is_directory(str_path.c_str() ) )
		{
			RAISE_EXCEPTION("");
			return 0;
		}
		
		smart_ptr<i_read_file> fin = hf->create_read_file(str_path.c_str() );
		if(!fin.get() )
		{
			RAISE_EXCEPTION("");
			return 0;
		}

		i_buffer* buff = fin->read_all();


		m_cache.insert(std::make_pair(str_path, buff) );
		return buff;
	}

	//接口导出

	//模块所在的路径
	const char* impl_filesystem::get_module_path()
	{
		std::string& g_str_ret = alloc_string("");
		char path[1024];
		DWORD sz_ret = GetModuleFileName(0, path, 1024);
		if(ERROR_INSUFFICIENT_BUFFER == sz_ret)
		{	
			return 0;
		}
		g_str_ret = path;
		return g_str_ret.c_str();
	}

	//工作路径
	const char* impl_filesystem::get_work_directory()
	{
		std::string& g_str_ret = alloc_string("");
		char path[1024];
		size_t sz = ::GetCurrentDirectory(1024, path);
		if(sz == 0) return 0;
		g_str_ret = path;
		return g_str_ret.c_str();
	}

	//创造buff
	i_buffer* impl_filesystem::create_buff(const char* buff, long sz)
	{
		impl_buffer* p_ret = new impl_buffer;
		p_ret->m_buff.insert(p_ret->m_buff.end(), buff, buff+sz);
		return p_ret;
	}

	bool impl_filesystem::make_directories(const char* path)
	{
		return fs::create_directories(path);
	}

	//读文件
	i_read_file* impl_filesystem::create_read_file(const char* path)
	{	
		return new impl_read_file(path);
	}

	//写文件
	i_write_file* impl_filesystem::create_write_file(const char* path, bool append)
	{
		return new impl_write_file(path, append);
	}

	//将目录作为一个pak使用
	i_pak* impl_filesystem::create_pak(const char* location)
	{
		i_pak* p = new impl_fs_pak(location);
		if(!p)
		{
			RAISE_EXCEPTION("");
		}
		return p;
	}



	//字串
	const char* impl_filesystem::append(const char* path, const char* branch)
	{
		fs::path m_path = path;
		m_path /= branch;

		return m_path.string().c_str();
	}

	//转为完整路径
	const char* impl_filesystem::system_complete(const char* path)
	{
		fs::path m_path = path;
		m_path = fs::system_complete(m_path);
		return m_path.string().c_str();
	}
	//是否存在
	bool impl_filesystem::exists(const char* path)
	{
		fs::path m_path = path;
		return fs::exists(m_path);
	}
	//是否目录
	bool impl_filesystem::is_directory(const char* path)
	{
		fs::path m_path = path;
		return fs::is_directory(m_path);
	}
	////目录迭代
	//const char* impl_filesystem::first(const char* path)
	//{
	//	fs::path m_path = path;

	//	static fs::directory_iterator end_itr;
	//	m_it = fs::directory_iterator(m_path);
	//	if(m_it == end_itr) return 0;

	//	std::string& g_str_ret = alloc_string("");
	//	g_str_ret = m_it->path().string();

	//	return g_str_ret.c_str();
	//}

	//const char* impl_filesystem::next()
	//{	
	//	std::string& g_str_ret = alloc_string("");
	//	static fs::directory_iterator end_itr;
	//	if(++m_it == end_itr) return 0;
	//	g_str_ret = m_it->path().string();

	//	return g_str_ret.c_str();
	//}

	//解析
	const char* impl_filesystem::extension(const char* path)
	{
		fs::path m_path = path;
		std::string& g_str_ret = alloc_string("");
		g_str_ret = m_path.extension();
		return g_str_ret.c_str();
	}

	const char* impl_filesystem::leaf(const char* path)
	{
		fs::path m_path = path;
		std::string& g_str_ret = alloc_string("");
		g_str_ret = m_path.leaf();
		return g_str_ret.c_str();
	}

	const char* impl_filesystem::stem(const char* path)
	{
		fs::path m_path = path;
		std::string& g_str_ret = alloc_string("");
		g_str_ret = m_path.stem();
		return g_str_ret.c_str();
	}

	const char* impl_filesystem::parent_path(const char* path)
	{
		fs::path m_path = path;
		std::string& g_str_ret = alloc_string("");
		g_str_ret = m_path.parent_path().string();
		return g_str_ret.c_str();
	}

	const char* impl_filesystem::normalize(const char* path)
	{
		fs::path m_path = path;
		m_path = m_path.normalize();
		return m_path.string().c_str();
	}

	i_path_iter* impl_filesystem::create_path_iter(const char* path)
	{
		if(is_directory(path) )
		{
			fs::directory_iterator it = fs::directory_iterator(path);			
			return new impl_path_iter(it);
		}
		return 0;
	}


	//模块资源释放
	void impl_filesystem::release()
	{
		for(size_t i = 0; i<m_string_pool.size(); ++i)
		{
			delete m_string_pool[i];
		}
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

M_IMPL(ns_base::h_filesystem, ns_base::impl_filesystem);//2. 接口实现
M_OPEN();//3. 模块建立

