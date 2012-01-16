
#include <string>
#include <vector>

#include "../head/smart_ptr.h"
#include "../head/exception.h"

#include "impl.h"
#include <map>
#include "../filesystem/interface.h"




#include "../head/utility_new.h"

namespace ns_base
{
	static std::stringstream mssOut;

	std::map<lua_State*,  impl_lua_project*> g_lua_state2env;

	lua_State* impl_lua::get_state()
	{
		return m_state;
	}

	void impl_lua::do_string(const char* cmd)
	{
		load_string(cmd);
		do_script();
	}

	const std::string& getLuaErrorString( int aiErr )
	{
		static std::string aErrString;

		switch( aiErr )
		{
		case LUA_ERRRUN:
			aErrString = "LUA_ERRRUN";
			break;
		case LUA_ERRFILE:
			aErrString = "LUA_ERRFILE";
			break;
		case LUA_ERRSYNTAX:
			aErrString = "LUA_ERRSYNTAX";
			break;
		case LUA_ERRMEM:
			aErrString = "LUA_ERRMEM";
			break;
		case LUA_ERRERR:
			aErrString = "LUA_ERRERR";
			break;
		default:
			aErrString = "Unknown";
			break;
		}

		return( aErrString );
	}

	//生成一个function放到栈顶
	void impl_lua::load_string(const char* strCmd)
	{
		int iRet = luaL_loadstring(m_state,strCmd );
		if( iRet != 0 )
		{
			std::string errorMsg;

			errorMsg = lua_tostring( m_state, -1 );
			std::string strCmdShort = std::string(strCmd).substr(0, 32);

			mssOut.str( "" );
			mssOut << strCmdShort 
				<< "\n    lua 出错类型: "
				<< getLuaErrorString( iRet )
				<< ".\n    错误信息: " << errorMsg;

			RAISE_EXCEPTION( (mssOut.str().c_str()) );
		}
	}

	void impl_lua::load_file(const char* fname)
	{
		// Now load the script
		int s = luaL_loadfile( m_state, fname );

		if(s)
		{
			std::string errorMsg;
			errorMsg = lua_tostring( m_state, -1 );
			mssOut.str( "" );
			mssOut << "load_file: "
				<< fname << "    lua 出错类型: "
				<< getLuaErrorString( s ) << ".\n"
				<< "    错误信息: " << errorMsg;

			RAISE_EXCEPTION(mssOut.str().c_str() );
		}
	}

	void impl_lua::load_buffer(const char* name, i_buffer* buff)
	{
		long s = luaL_loadbuffer(m_state, (const char*)buff->ptr(), buff->size(), name );

		if(s>0)
		{
			std::string errorMsg;

			errorMsg = lua_tostring( m_state, -1 );

			mssOut.str( "" );
			mssOut << "加载错误: "
				<< name << "    lua 出错类型: "
				<< getLuaErrorString( s ) << ".\n"
				<< "    错误信息: " << errorMsg;

			RAISE_EXCEPTION(mssOut.str().c_str() );
		}
	}

	void impl_lua::do_script()
	{
		int s = lua_pcall( m_state, 0, LUA_MULTRET, 0 );

		if( s > 0 )
		{
			std::string errorMsg;

			errorMsg = lua_tostring( m_state, -1 );

			mssOut.str( "" );
			mssOut << "    lua 出错类型: "
				<< getLuaErrorString( s ) << ".\n"
				<< "    错误信息: " << errorMsg;

			RAISE_EXCEPTION(mssOut.str().c_str() );
		}
	}


	void impl_lua::root_section()//根结点
	{
		lua_settop(m_state, 0);
		lua_getglobal(m_state, "_G");
	}

	bool impl_lua::leave_section()//向上
	{
		if(lua_gettop(m_state) == 1) return false;
		lua_pop(m_state, 1);
		return true;
	}

	int impl_lua::get_idx_count()
	{
		if(!lua_istable(m_state, -1) )
		{
			return -1;
		}
		return lua_objlen(m_state, -1);
	}

	bool impl_lua::enter_section(const char* key)
	{
		if(!lua_istable(m_state, -1) )
		{
			return false;
		}

		lua_pushstring(m_state, key);
		lua_gettable(m_state, -2);
		if(!lua_istable(m_state, -1) )
		{
			lua_pop(m_state, 1);
			return false;
		}
		return true;
	}

	bool impl_lua::enter_section_idx(int idx)
	{
		if(!lua_istable(m_state, -1) )
		{
			return false;
		}

		lua_pushnumber(m_state, idx);
		lua_gettable(m_state, -2);
		if(!lua_istable(m_state, -1) )
		{
			lua_pop(m_state, 1);
			return false;
		}
		return true;
	}

	bool impl_lua::get_bool(const char* key, bool& out)
	{
		if(!lua_istable(m_state, -1) )
		{
			return false;
		}

		lua_pushstring(m_state, key);
		lua_gettable(m_state, -2);
		if(!lua_isboolean(m_state, -1) )
		{
			lua_pop(m_state, 1);
			return false;
		}
		out = lua_toboolean(m_state, -1);
		lua_pop(m_state, 1);
		return true;
	}

	bool impl_lua::get_bool_idx(int idx, bool& out)
	{
		if(!lua_istable(m_state, -1) )
		{
			return false;
		}

		lua_pushinteger(m_state, idx);
		lua_gettable(m_state, -2);
		if(!lua_isboolean(m_state, -1) )
		{
			lua_pop(m_state, 1);
			return false;
		}
		out = lua_toboolean(m_state, -1);
		lua_pop(m_state, 1);
		return true;
	}

	bool impl_lua::get_int(const char* key, int& out)
	{
		if(!lua_istable(m_state, -1) )
		{
			return false;
		}

		lua_pushstring(m_state, key);
		lua_gettable(m_state, -2);
		if(!lua_isnumber(m_state, -1) )
		{
			lua_pop(m_state, 1);
			return false;
		}
		out = lua_tointeger(m_state, -1);
		lua_pop(m_state, 1);
		return true;
	}

	bool impl_lua::get_int_idx(int idx, int& out)
	{
		if(!lua_istable(m_state, -1) )
		{
			return false;
		}

		lua_pushinteger(m_state, idx);
		lua_gettable(m_state, -2);
		if(!lua_isnumber(m_state, -1) )
		{
			lua_pop(m_state, 1);
			return false;
		}
		out = lua_tointeger(m_state, -1);
		lua_pop(m_state, 1);
		return true;
	}

	bool impl_lua::get_double(const char* key, double& out)
	{
		if(!lua_istable(m_state, -1) )
		{
			return false;
		}

		lua_pushstring(m_state, key);
		lua_gettable(m_state, -2);
		if(!lua_isnumber(m_state, -1) )
		{
			lua_pop(m_state, 1);
			return false;
		}
		out = lua_tonumber(m_state, -1);
		lua_pop(m_state, 1);
		return true;
	}

	bool impl_lua::get_double_idx(int idx, double& out)
	{
		if(!lua_istable(m_state, -1) )
		{
			return false;
		}

		lua_pushinteger(m_state, idx);
		lua_gettable(m_state, -2);
		if(!lua_isnumber(m_state, -1) )
		{
			lua_pop(m_state, 1);
			return false;
		}
		out = lua_tonumber(m_state, -1);
		lua_pop(m_state, 1);
		return true;
	}

	const char* impl_lua::get_string(const char* key)
	{
		static std::string ret = "";
		if(!lua_istable(m_state, -1) )
		{
			return 0;
		}

		lua_pushstring(m_state, key);
		lua_gettable(m_state, -2);
		if(!lua_isstring(m_state, -1) )
		{
			lua_pop(m_state, 1);
			return 0;
		}
		ret = lua_tostring(m_state, -1);
		lua_pop(m_state, 1);
		return ret.c_str();
	}

	const char* impl_lua::get_string_idx(int idx)
	{
		static std::string ret = "";
		if(!lua_istable(m_state, -1) )
		{
			return 0;
		}

		lua_pushinteger(m_state, idx);
		lua_gettable(m_state, -2);
		if(!lua_isstring(m_state, -1) )
		{
			lua_pop(m_state, 1);
			return 0;
		}
		ret = lua_tostring(m_state, -1);
		lua_pop(m_state, 1);
		return ret.c_str();
	}

	//注册函数
	void impl_lua::reg_lib(lua_CFunction lib)
	{
		lib(m_state);
	}

	void impl_lua::reg_func(const char* func_name, lua_CFunction func)
	{
		lua_register(m_state , func_name, func);
	}

	void impl_lua::reg_funcs(luaL_reg funcs[])
	{
		for (size_t i = 0; ;  ++i)	
		{
			if(funcs[i].name[0] == 0 || funcs[i].func == NULL)
				break;
			lua_register(m_state , funcs[i].name, funcs[i].func);
		}
	}

	enum E_TYPE
	{
		e_bool = 0,
		e_int,
		e_double,
		e_string,
	};

	struct st_arg_in
	{
		E_TYPE m_type;
		
		std::string m_string;
		union
		{
			bool m_b;
			int m_int;
			double m_double;
		};
	};

	struct st_arg_out
	{
		E_TYPE m_type;

		union
		{
			bool* m_b;
			int* m_int;
			double* m_double;
			char* m_string;
		};
	};

	struct st_arg_list
	{
		std::vector<st_arg_in> m_in;
		std::vector<st_arg_out> m_out;
	};

	static st_arg_list g_list;

	void impl_lua::push_in_para_bool(bool p)
	{
		st_arg_in arg;
		arg.m_type = e_bool;
		arg.m_b = p;
		g_list.m_in.push_back(arg);
	}

	void impl_lua::push_in_para_int(int p)
	{
		st_arg_in arg;
		arg.m_type = e_int;
		arg.m_int = p;
		g_list.m_in.push_back(arg);
	}

	void impl_lua::push_in_para_double(double p)
	{
		st_arg_in arg;
		arg.m_type = e_double;
		arg.m_double = p;
		g_list.m_in.push_back(arg);
	}

	void impl_lua::push_in_para_string(const char* p)
	{
		st_arg_in arg;
		arg.m_type = e_string;
		arg.m_string = p;
		g_list.m_in.push_back(arg);
	}

	void impl_lua::push_out_para_bool(bool& p)
	{
		st_arg_out arg;
		arg.m_type = e_bool;
		arg.m_b = &p;
		g_list.m_out.push_back(arg);
	}

	void impl_lua::push_out_para_int(int& p)
	{
		st_arg_out arg;
		arg.m_type = e_int;
		arg.m_int = &p;
		g_list.m_out.push_back(arg);
	}

	void impl_lua::push_out_para_double(double& p)
	{
		st_arg_out arg;
		arg.m_type = e_double;
		arg.m_double = &p;
		g_list.m_out.push_back(arg);
	}

	void impl_lua::push_out_para_string(char* p)
	{
		st_arg_out arg;
		arg.m_type = e_string;
		arg.m_string = p;
		g_list.m_out.push_back(arg);
	}

	void impl_lua::call_function(const char *func)
	{			
		int topidx = lua_gettop(m_state);
		lua_getglobal(m_state, func);  /* get function */
		if( lua_isfunction( m_state, -1 ) )
		{
			for(size_t i = 0; i < g_list.m_in.size(); ++i)
			{
				st_arg_in& p = g_list.m_in[i];
				switch (p.m_type)
				{
				case e_bool:
					lua_pushboolean(m_state, p.m_b);
					break;
				case e_int:
					lua_pushinteger(m_state, p.m_int);
					break;
				case e_double:
					lua_pushnumber(m_state, p.m_double);
					break;
				case e_string:
					lua_pushstring(m_state, p.m_string.c_str() );
					break;
				default:
					g_list.m_in.clear();
					g_list.m_out.clear();
					lua_settop(m_state, topidx);
					RAISE_EXCEPTION("");
					break;
				}
			}

			if (lua_pcall(m_state, g_list.m_in.size(), g_list.m_out.size(), 0) != 0)  /* do the call */
			{
				mssOut.str( "" );
				mssOut <<"执行脚本函数时出错 "
					<< func << " : " << lua_tostring(m_state, -1);
				lua_settop(m_state, topidx);
				g_list.m_in.clear();
				g_list.m_out.clear();
				RAISE_EXCEPTION(mssOut.str().c_str() );
			}

			int nres = -g_list.m_out.size();
			for(size_t i = 0; i<g_list.m_out.size(); ++i)
			{
				st_arg_out& p = g_list.m_out[i];
				switch (p.m_type)
				{
				case e_bool:
					if(!lua_isboolean(m_state, nres) )
					{
						g_list.m_in.clear();
						g_list.m_out.clear();
						lua_settop(m_state, topidx);
						RAISE_EXCEPTION("");
					}
					*p.m_b = lua_toboolean(m_state, nres);
					break;
				case e_int:
					if(!lua_isnumber(m_state, nres) )
					{
						g_list.m_in.clear();
						g_list.m_out.clear();
						lua_settop(m_state, topidx);
						RAISE_EXCEPTION("");
					}
					*p.m_int = lua_tointeger(m_state, nres);
					break;
				case e_double:
					if(!lua_isnumber(m_state, nres) )
					{
						g_list.m_in.clear();
						g_list.m_out.clear();
						lua_settop(m_state, topidx);
						RAISE_EXCEPTION("");
					}
					*p.m_double = lua_tonumber(m_state, nres);
					break;
				case e_string:
					if(!lua_isstring(m_state, nres) )
					{
						g_list.m_in.clear();
						g_list.m_out.clear();
						lua_settop(m_state, topidx);
						RAISE_EXCEPTION("");
					}
					strcpy(p.m_string, lua_tostring(m_state, nres) );
					break;
				default:
					g_list.m_in.clear();
					g_list.m_out.clear();
					lua_settop(m_state, topidx);
					RAISE_EXCEPTION("");
				}
				nres++;
			}
		}
		else
		{
			g_list.m_in.clear();
			g_list.m_out.clear();
			lua_settop(m_state, topidx);
			RAISE_EXCEPTION("not a function!");
		}
		//clean
		g_list.m_in.clear();
		g_list.m_out.clear();
		lua_settop(m_state, topidx);
	}


	//全局变量
	void impl_lua::add_string_global(const char* key, const char* val)
	{
		lua_pushstring( m_state, val);
		lua_setglobal( m_state, key );
	}
	const char* impl_lua::get_string_global(const char* key)
	{
		static std::string sOutput;

		lua_getglobal( m_state, key );

		if( lua_isstring( m_state, -1 ) )
		{
			sOutput = lua_tostring( m_state, -1 );
		}
		else
		{
			RAISE_EXCEPTION("get no string type");
			sOutput = "";
		}

		lua_pop(m_state, 1);

		return( sOutput.c_str() );
	}

	void impl_lua::add_number_global(const char* key, double val)
	{
		lua_pushnumber( m_state, val);
		lua_setglobal( m_state, key);
	}

	double impl_lua::get_number_global(const char* key)
	{
		static double fOutput;

		lua_getglobal( m_state, key );

		if( lua_isnumber( m_state, -1 ) )
		{
			fOutput = (double)lua_tonumber( m_state, -1 );
		}
		else
		{
			RAISE_EXCEPTION("");
			fOutput = 0;
		}

		lua_pop( m_state, 1 );

		return( fOutput );
	}

	void impl_lua::add_bool_global(const char* key, bool val)
	{
		lua_pushboolean( m_state, val);
		lua_setglobal( m_state, key);
	}
	bool impl_lua::get_bool_global(const char* str_name)
	{
		static bool bOutput;

		lua_getglobal( m_state, str_name );

		if( lua_isboolean( m_state, -1 ) )
		{
			bOutput = (bool)lua_toboolean( m_state, -1 );
		}
		else
		{
			RAISE_EXCEPTION("");
			bOutput = false;
		}

		lua_pop( m_state, 1 );

		return( bOutput );
	}

	//表里面的变量
	void impl_lua::add_string_in_table(const char* table_name, const char* key, const char* val)
	{
		lua_getglobal(  m_state, table_name);
		lua_pushstring( m_state, key );
		lua_pushstring( m_state, val );
		lua_settable(   m_state, -3 );

		lua_pop( m_state, 1 );//TODO?
	}
	const char* impl_lua::get_string_in_table(const char* table_name, const char* key)
	{
		static std::string	returnString;

		lua_getglobal(  m_state, table_name);
		lua_pushstring( m_state, table_name );
		lua_gettable( m_state, -2 );  // table "me" is at position -2 on stack

		if( lua_isstring( m_state, -1 ) )
		{
			returnString = lua_tostring( m_state, -1 );
			lua_pop( m_state, 2 );

			return( returnString.c_str() );
		}
		else
		{
			lua_pop( m_state, 2 );

			mssOut.str("");
			mssOut << "Not a string!\n"
				<< "    table name  = " << table_name << "\n"
				<< "    key name    = " << key << "\n";

			RAISE_EXCEPTION(mssOut.str().c_str() );
			//throw( ns_script::ScriptException( mssOut.str().c_str() ) );
		}
	}

	void impl_lua::add_number_in_table(const char* table_name, const char* key, double val)
	{
		lua_getglobal(  m_state, table_name );
		lua_pushstring( m_state, key );
		lua_pushnumber( m_state, val );
		lua_settable(   m_state, -3 );

		lua_pop( m_state, 1 );
	}
	double impl_lua::get_number_in_table(const char* table_name, const char* key)
	{
		static double dValue;

		lua_getglobal(  m_state, table_name );
		lua_pushstring( m_state, key );
		lua_gettable( m_state, -2 );  // table "me" is at position -2 on stack

		if( lua_isnumber( m_state, -1 ) )
		{
			dValue = lua_tonumber( m_state, -1 );
			lua_pop( m_state, 2 );

			return( dValue );
		}
		else
		{
			lua_pop( m_state, 2 );

			mssOut.str("");
			mssOut << "Not a number!\n"
				<< "    table name  = " << table_name << "\n"
				<< "    key name    = " << key << "\n";

			RAISE_EXCEPTION(mssOut.str().c_str() );
			//throw( ns_script::ScriptException( mssOut.str().c_str() ) );
		}
	}

	void impl_lua::add_bool_in_table(const char* table_name, const char* key, bool val)
	{
		lua_getglobal(  m_state, table_name );
		lua_pushstring( m_state, key );
		lua_pushboolean( m_state, val );
		lua_settable(   m_state, -3 );

		lua_pop( m_state, 1 );
	}
	bool impl_lua::get_bool_in_table(const char* table_name, const char* key)
	{
		static bool bret;

		lua_getglobal(  m_state, table_name );
		lua_pushstring( m_state, key );
		lua_gettable( m_state, -2 );  // table "me" is at position -2 on stack

		if( lua_isboolean( m_state, -1 ) )
		{
			bret = lua_toboolean( m_state, -1 );
			lua_pop( m_state, 2 );

			return( bret );
		}
		else
		{
			lua_pop( m_state, 2 );

			mssOut.str("");
			mssOut << "Not a bool!\n"
				<< "    table name  = " << table_name << "\n"
				<< "    key name    = " << key << "\n";

			RAISE_EXCEPTION(mssOut.str().c_str() );
			//throw( ns_script::ScriptException( mssOut.str().c_str() ) );
		}
	}

	bool impl_lua::exists( const char* key)
	{
		return( exists_in_table_str("_G", key ) );
	}

	bool impl_lua::exists_in_table_str( const char* table_name, const char* key)
	{
		// 1. Put the table on the top of the stack:
		lua_getglobal(  m_state, table_name );

		// 2. Put the index key in the table onto the stack:
		lua_pushstring( m_state, key );

		// 3. Get aTable[ aName ] and put it on top of the stack.
		//    The value pushed onto the stack in step 2 is popped,
		//    but the table value pushed in step 1 remains.
		lua_gettable(   m_state, -2 );

		// We now have two items on the stack:
		// 1. The "aTable" table
		// 2. The value of aTable[ aName ], which is on the stack's top.

		if( lua_type( m_state, -1 ) != LUA_TNIL )
		{
			lua_pop( m_state, 2 );
			return( true );
		}
		else
		{
			lua_pop( m_state, 2 );
			return( false );
		}
	}
	bool impl_lua::exists_in_table_num( const char* table_name, const int index)
	{
		// 1. Put the table on the top of the stack:
		lua_getglobal(  m_state, table_name );

		// 2. Put the index key in the table onto the stack:
		lua_pushnumber( m_state, index );

		// 3. Get aTable[ aName ] and put it on top of the stack.
		//    The value pushed onto the stack in step 2 is popped,
		//    but the table value pushed in step 1 remains.
		lua_gettable(   m_state, -2 );

		// We now have two items on the stack:
		// 1. The "aTable" table
		// 2. The value of aTable[ aName ], which is on the stack's top.

		if( lua_type( m_state, -1 ) != LUA_TNIL )
		{
			lua_pop( m_state, 2 );
			return( true );
		}
		else
		{
			lua_pop( m_state, 2 );
			return( false );
		}
	}


	const char* impl_lua::dump_stack()
	{
		int i;
		int top = lua_gettop(m_state);
		static std::string	sOutput;

		mssOut.str( "" );

		for (i = 1; i <= top; i++) 
		{  
			/* repeat for each level */
			int t = lua_type(m_state, i);

			switch (t) 
			{
			case LUA_TSTRING:  /* strings */
				mssOut << "'" << lua_tostring(m_state, i) << "'";
				break;

			case LUA_TBOOLEAN:  /* booleans */
				mssOut << (lua_toboolean(m_state, i) ? "true" : "false");
				break;

			case LUA_TNUMBER:  /* numbers */
				mssOut << lua_tonumber(m_state, i);
				break;

			default:  /* other values */
				mssOut << lua_typename(m_state, t);
				break;
			}

			mssOut << "  ";  /* put a separator */
		}

		mssOut << std::endl;  /* end the listing */

		sOutput = mssOut.str();

		return( sOutput.c_str() );
	}


	static int catch_lua_error(lua_State* st)
	{
		RAISE_EXCEPTION("lua panic!");
		return 0;
	}



	//增加pak索引目录列表, 按顺序
	void impl_lua_project::add_pak(i_pak* pak)
	{
		pak->add_ref();
		if(m_pak_stk.size() == 0)
		{
			m_pak_stk.push_back(pak);
			m_paths_stk.push_back("./");
		}
		m_paks.push_back(pak);
	}

	//增加lua引用, 按顺序
	void impl_lua_project::add_include_path(const char* path)
	{
		m_includes.push_back(path);
	}

	//增加dll引用, 按顺序
	void impl_lua_project::add_lib_path(const char* path)
	{
		m_libs.push_back(path);
	}

	//lua entry
	int lua_include(lua_State* st);
	i_lua* impl_lua_project::create_lua(const char* path)
	{
		h_script* hs;
		get(hs);

		i_lua* p_lua = hs->create_lua();
		
		//查找路径
		lua_State* st = p_lua->get_state();
		reg_state(st);

		lua_pushstring(st, path);
		lua_include(st);

		return p_lua;
	}

	int lua_include(lua_State* st)
	{
		const char* path = lua_tostring(st, 1);
		std::map<lua_State*, impl_lua_project*>::iterator it = g_lua_state2env.find(st);
		if(it != g_lua_state2env.end() )
		{
			impl_lua_project* proj = it->second;
			i_pak* pak_out = 0;
			std::string path_out = "";
			bool b = proj->find_include(path, pak_out, path_out);
			if(!b) goto end;
			
			proj->push(pak_out, path_out);
			i_buffer* buff = pak_out->get_buffer(path_out.c_str() );
			
			if(!buff) goto end;

			h_script* hs;
			get(hs);

			int err = luaL_loadbuffer(st, (const char*)buff->ptr(), buff->size(), path_out.c_str() );
			if(err != 0)
			{
				lua_error(st);
			}
			err = lua_pcall(st, 0, 0, 0);
			if(err != 0)
			{	
				lua_error(st);
			}
			proj->pop();
			return 0;
		}
end:
		std::string err_msg(path);
		err_msg += " 未找到";
		lua_pushstring(st, err_msg.c_str() );
		lua_error(st);

		return 0;
	}

	int lua_import(lua_State* st)
	{
		//
		const char* path = lua_tostring(st, 1);
		std::map<lua_State*, impl_lua_project*>::iterator it = g_lua_state2env.find(st);
		if(it != g_lua_state2env.end() )
		{
			impl_lua_project* proj = it->second;
			std::string path_out;
			if(!proj->find_lib(path, path_out) ) goto end;
			
			h_filesystem* hf;
			get(hf);

			std::string interface_name = hf->stem(path_out.c_str() );
			interface_name = std::string("luaopen_")+interface_name;

			HMODULE m = LoadLibrary(path_out.c_str() );
			if(m)
			{
				lua_CFunction foo = (lua_CFunction)GetProcAddress(m, interface_name.c_str() ); 
				//TODO 错误处理
				if(foo)
					return foo(st);
				else
				{
					std::string err_msg(path );
					err_msg += std::string(" ")+interface_name+" 接口未找到";
					lua_pushstring(st, err_msg.c_str() );
					lua_error(st);
					return 0;
				}
			}
		}
end:
		std::string err_msg(path );
		err_msg += std::string(" ")+" 未找到";
		lua_pushstring(st, err_msg.c_str() );
		lua_error(st);
		return 0;
	}

	int lua_add_lib_path(lua_State* st)
	{
		//
		const char* path = lua_tostring(st, 1);
		std::map<lua_State*, impl_lua_project*>::iterator it = g_lua_state2env.find(st);
		if(it != g_lua_state2env.end() )
		{
			impl_lua_project* proj = it->second;
			proj->add_lib_path(path);
		}

		std::string err_msg(path );
		err_msg += std::string(" ")+" 未找到";
		lua_pushstring(st, err_msg.c_str() );
		lua_error(st);
		
		return 0;
	}

	int lua_add_sys_path(lua_State* st)
	{
		//
		const char* path = lua_tostring(st, 1);
		std::map<lua_State*, impl_lua_project*>::iterator it = g_lua_state2env.find(st);
		if(it != g_lua_state2env.end() )
		{
			impl_lua_project* proj = it->second;
			proj->add_include_path(path);
		}

		std::string err_msg(path );
		err_msg += std::string(" ")+" 未找到";
		lua_pushstring(st, err_msg.c_str() );
		lua_error(st);

		return 0;
	}

	//使得第三方state得到lua_project功能, 非侵入式, 要注意project生命期
	void impl_lua_project::reg_state(lua_State* st)
	{
		g_lua_state2env[st] = this;
		lua_register(st, "include", &lua_include);
		lua_register(st, "import", &lua_import);
		lua_register(st, "add_lib_path", &lua_add_lib_path);
		lua_register(st, "add_include_path", &lua_add_sys_path);
	}

	impl_lua_project::impl_lua_project()
	{

	}

	impl_lua_project::~impl_lua_project()
	{
		//清除所有
		for(size_t i = 0; i<m_paks.size(); ++i)
		{
			i_pak* p = m_paks[i];
			p->release();
		}
	}

	bool impl_lua_project::find_include(const char* path, i_pak*& pak_out, std::string& path_out)
	{
		using namespace ns_common;
		i_pak* cpak = current_pak();
		std::string cpath = current_path();

		h_filesystem* hf;
		get(hf);
		
		//smart_ptr<i_path> cp = hf->create_path(cpath.c_str() );
		//smart_ptr<i_path> ncp = cp->clone();
		//ncp->append(path);

		std::string str_path = hf->append(cpath.c_str(), path);

		if(cpak->exist(str_path.c_str() ) )
		{
			//相对路径存在
			pak_out = cpak;
			path_out = str_path;
			return true;
		}

		//相对路径不存在, 相对includes路径
		for(size_t i = 0; i<m_paks.size(); ++i)
		{
			i_pak* cpak = m_paks[i];
			for(size_t ii = 0; ii<m_includes.size(); ++ii)
			{
				std::string str_path = m_includes[ii];
				str_path = hf->append(str_path.c_str(), path);
				
				if(cpak->exist(str_path.c_str() ) )
				{
					pak_out = cpak;
					path_out = str_path;
					return true;
				}
			}
		}
		
		//绝对路径
		for(size_t i = 0; i<m_paks.size(); ++i)
		{
			i_pak* cpak = m_paks[i];

			if(cpak->exist(path ) )
			{
				pak_out = cpak;
				path_out = str_path;
				return true;
			}
		}

		return false;

	}

	bool impl_lua_project::find_lib(const char* path, std::string& path_out)
	{
		//在所有lib path中查找;
		using namespace ns_common;
		using namespace ns_base;
		h_filesystem* hf;
		get(hf);
		
		for(size_t i = 0; i<m_libs.size(); ++i)
		{
			std::string str_path = m_libs[i];
			
			path_out = hf->append(str_path.c_str(), path);

			if(hf->exists(path_out.c_str() ) )
			{
				return true;
			}
		}

		//在绝对路径查找;
		path_out = path;
		if(hf->exists(path_out.c_str() ) )
		{
			return true;
		}

		return false;
	}


	i_lua* impl_h_script::create_lua()
	{
		impl_lua* ret = new impl_lua;
		ret->m_state = lua_open();
		luaL_openlibs(ret->m_state);
		//luaopen_base( mlState );
		//luaopen_table( mlState );
		////luaopen_io( mlState );
		//luaopen_string( mlState );
		//luaopen_math( mlState );

		lua_atpanic( ret->m_state, &catch_lua_error );

		//------------------------------------------------------------
		// Now clear the stack.  Various things are left on the stack
		// from the above operations, and we don't need them.  It
		// is perfectly acceptable (and correct?) to pop them off
		// so that the stack is empty.
		//------------------------------------------------------------
		int numPops = lua_gettop( ret->m_state );
		lua_pop( ret->m_state, numPops );

		return ret;

	}

	i_lua* impl_h_script::create_lua_from_file(const char* fname)
	{
		using namespace ns_common;
		
		h_filesystem* hf;
		get(hf);

		smart_ptr<i_read_file> fin =  hf->create_read_file(fname);
		smart_ptr<i_buffer> buff = fin->read_all();
		return create_lua_from_buffer(fname, buff.get() );
	}

	i_lua* impl_h_script::create_lua_from_buffer(const char* name, i_buffer* buff)
	{
		impl_lua* p_lua = (impl_lua*)create_lua();
		p_lua->load_buffer(name, buff);
		p_lua->do_script();
		return p_lua;
	}

	i_lua* impl_h_script::create_lua_from_string(const char* name, const char* str)
	{
		impl_lua* p_lua = (impl_lua*)create_lua();
		p_lua->load_string(str);
		p_lua->do_script();
		return p_lua;
	}

	i_lua_project* impl_h_script::create_lua_project()
	{
		i_lua_project* ret = new impl_lua_project;
		return ret;
	}
};


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

M_IMPL(ns_base::h_script, ns_base::impl_h_script);//2. 接口实现
M_OPEN();//3. 模块建立


