#include <cassert>



#include "singleton.h"
#include "proto_code.h"
#include "proto_value.h"

#include "primarys.h"
#include "vm.h"
#include "interface.h"

#define TYPE_CHECK(v, T) (assert((v).m_tag == singleton<T>::instance().m_tag) );
namespace ns_core
{
	namespace ns_primary
	{
		u32 _pause(st_vm* rt)
		{
			system("pause");
			return 0;
		}

		u32 print(st_vm* rt)
		{	
			u32 sz = rt->get_eval_size();

			std::string str = "";
			for(u32 i = 0; i != sz; ++i)
			{
				st_value v = rt->get_eval(i);
				str += rt->m_proto_values[v.m_tag]->to_string(v, rt);
				str += "\t";
			}
			printf("%s\n", str.c_str() );
			return 0;
		}

		u32 minus(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(0);
			assert(v1.m_tag == singleton<st_v_int>::instance().m_tag);
			v1.m_num = 0-v1.m_num;
			return 1;
		}

		u32 add(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(0);
			st_value& v2 = rt->get_eval(1);
			assert(v1.m_tag == singleton<st_v_int>::instance().m_tag);
			assert(v2.m_tag == singleton<st_v_int>::instance().m_tag);
			s32 ret = v1.get<s32>()+v2.get<s32>();
			v1.set(ret);
			return 1;
		}

		u32 sub(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(0);
			st_value& v2 = rt->get_eval(1);
			assert(v1.m_tag == singleton<st_v_int>::instance().m_tag);
			assert(v2.m_tag == singleton<st_v_int>::instance().m_tag);
			s32 ret = v1.get<s32>()-v2.get<s32>();
			v1.set(ret);
			return 1;
		}

		u32 mul(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(0);
			st_value& v2 = rt->get_eval(1);
			assert(v1.m_tag == singleton<st_v_int>::instance().m_tag);
			assert(v2.m_tag == singleton<st_v_int>::instance().m_tag);
			s32 ret = v1.get<s32>()*v2.get<s32>();
			v1.set(ret);
			return 1;
		}

		u32 div(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(0);
			st_value& v2 = rt->get_eval(1);
			assert(v1.m_tag == singleton<st_v_int>::instance().m_tag);
			assert(v2.m_tag == singleton<st_v_int>::instance().m_tag);
			s32 ret = v1.get<s32>()/v2.get<s32>();
			v1.set(ret);
			return 1;
		}

		u32 mod(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(0);
			st_value& v2 = rt->get_eval(1);
			assert(v1.m_tag == singleton<st_v_int>::instance().m_tag);
			assert(v2.m_tag == singleton<st_v_int>::instance().m_tag);
			s32 ret = v1.get<s32>()%v2.get<s32>();
			v1.set(ret);
			return 1;
		}

		u32 equal_num(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(-2);
			st_value& v2 = rt->get_eval(-1);
			if(v1.get<u32>() == v2.get<u32>() )
			{
				v1 = st_v_bool::make_value(true);
			}
			else
				v1 = st_v_bool::make_value(false);

			return 1;
		}

		u32 GT_num(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(-2);
			st_value& v2 = rt->get_eval(-1);
			if(v1.get<u32>() > v2.get<u32>() )
			{
				v1 = st_v_bool::make_value(true);
			}
			else
				v1 = st_v_bool::make_value(false);

			return 1;
		}

		u32 LT_num(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(-2);
			st_value& v2 = rt->get_eval(-1);
			if(v1.get<u32>() < v2.get<u32>() )
			{
				v1 = st_v_bool::make_value(true);
			}
			else
				v1 = st_v_bool::make_value(false);

			return 1;
		}

		u32 null_array(st_vm* rt)
		{	
			rt->m_evals.push(st_v_array::make_value() );
			return 1;
		}

		u32 array_push(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(-2);
			st_value& v2 = rt->get_eval(-1);
			array<st_value>* v_arr = v1.get<array<st_value>* >();
			v_arr->push(v2);
			return 1;
		}

		u32 array_cor(st_vm* rt)
		{
			u32 sz = rt->get_eval_size();

			st_value& v_null_arr = rt->get_eval(0);
			array<st_value>* v_arr = v_null_arr.get<array<st_value>* >();
			for(u32 i = 1; i<sz; ++i)
			{
				st_value& v = rt->get_eval(i);
				v_arr->push(v);
			}
			return 1;
		}

		u32 null_map(st_vm* rt)
		{
			rt->m_evals.push(st_v_map::make_value(rt) );
			return 1;
		}

		u32 map_insert(st_vm* rt)
		{
			u32 sz = rt->get_eval_size();
			if(sz == 1){}
			else if(sz == 2) 
			{
				st_value& v_map = rt->get_eval(0);
				st_value& v1 = rt->get_eval(1);
				st_value v2 = st_v_null::make_value();
				st_map<st_value, st_value, st_value_cmp>* v_map1 = v_map.get<st_map<st_value, st_value, st_value_cmp>* >();
				v_map1->insert(v1, v2);
			}
			else if(sz == 3) 
			{
				st_value& v_map = rt->get_eval(0);
				st_value& v1 = rt->get_eval(1);
				st_value& v2 = rt->get_eval(2);
				st_map<st_value, st_value, st_value_cmp>* v_map1 = v_map.get<st_map<st_value, st_value, st_value_cmp>* >();
				v_map1->insert(v1, v2);
			}
			return 1;
		}

		u32 insert(st_vm* rt)
		{
			u32 sz = rt->get_eval_size();
			assert(sz>0);
			st_value& vf = rt->get_eval(0);
			if(vf.m_tag == singleton<st_v_map>::instance().m_tag)
			{
				st_map<st_value, st_value, st_value_cmp>* m = vf.get<st_map<st_value, st_value, st_value_cmp>* >();
				if(sz == 1)
				{
					return 0;
				}
				else if(sz == 2)
				{	
					st_value& v1 = rt->get_eval(1);
					m->insert(v1, st_v_null::make_value() );
				}
				else//sz > 2
				{
					st_value& v1 = rt->get_eval(1);
					st_value& v2 = rt->get_eval(2);
					m->insert(v1, v2 );
				}
			}
			else if(vf.m_tag == singleton<st_v_array>::instance().m_tag)
			{
				array<st_value>* vs = vf.get<array<st_value>* >();
				if(sz == 1)
				{
					return 0;
				}
				else if(sz == 2)
				{	
					st_value& v1 = rt->get_eval(1);
					assert(v1.m_tag == singleton<st_v_int>::instance().m_tag);
					if(v1.m_num>vs->top_idx() )//TODO, 数组越界
					{
						assert(false);
					}

					vs->at(v1.m_num) = st_v_null::make_value();
				}
				else//sz > 2
				{
					st_value& v1 = rt->get_eval(1);
					st_value& v2 = rt->get_eval(2);

					assert(v1.m_tag == singleton<st_v_int>::instance().m_tag);
					if(v1.m_num>vs->top_idx() )//TODO, 数组越界
					{
						assert(false);
					}

					vs->at(v1.m_num) = v2;
				}
			}

			return 0;
		}

		//index(m, k)
		u32 index(st_vm* rt)
		{
			u32 sz = rt->get_eval_size();
			assert(sz>0);
			st_value& vf = rt->get_eval(0);
			if(vf.m_tag == singleton<st_v_map>::instance().m_tag)
			{
				st_map<st_value, st_value, st_value_cmp>* m = vf.get<st_map<st_value, st_value, st_value_cmp>* >();
				if(sz == 1)
				{
					return 0;
				}
				else//sz > 1
				{
					st_value& v1 = rt->get_eval(1);
					bool b = m->find(v1);
					if(b)
					{
						st_value v = m->get_val();
						vf = v;
						return 1;
					}
					else
					{
						vf = st_v_null::make_value();
						return 1;
					}
				}
			}
			else if(vf.m_tag == singleton<st_v_array>::instance().m_tag)
			{
				array<st_value>* vs = vf.get<array<st_value>* >();
				if(sz == 1)
				{
					return 0;
				}
				else
				{	
					st_value& v1 = rt->get_eval(1);
					assert(v1.m_tag == singleton<st_v_int>::instance().m_tag);
					if(v1.m_num>vs->top_idx() )//TODO, 数组越界
					{
						assert(false);
					}

					vf = vs->at(v1.m_num);
					return 1;
				}
			}

			return 0;
		}


		u32 a_push(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(-2);
			st_value& v2 = rt->get_eval(-1);
			TYPE_CHECK(v1, st_v_array);
			
			array<st_value>* vs = v1.get<array<st_value>* >();
			vs->push(v2);
			return 0;
		}

		u32 a_pop(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(-1);
			TYPE_CHECK(v1, st_v_array);
			array<st_value>* vs = v1.get<array<st_value>* >();
			//TODO, check size
			assert(vs->size() != 0);

			v1 = vs->pop();
			return 1;
		}

		u32 a_size(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(-1);

			if(v1.m_tag == singleton<st_v_array>::instance().m_tag)
			{
				array<st_value>* vs = v1.get<array<st_value>* >();

				v1 = st_v_int::make_value(vs->size() );
				return 1;
			}
			else if(v1.m_tag == singleton<st_v_map>::instance().m_tag)
			{
				st_map<st_value, st_value, st_value_cmp>* m = v1.get<st_map<st_value, st_value, st_value_cmp>* >();
				v1 = st_v_int::make_value(m->size() );
				return 1;
			}
			else
			{
				assert(false);
				return 0;
			}
		}

		u32 _type(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(-1);
			i_value_proto* vp = rt->get_value_proto(v1.m_tag);
			v1 = st_v_string::make_value(vp->get_name() );//TODO 用string pool
			return 1;
		}
	
		u32 print_symbol(st_vm* rt)
		{
			rt->m_symbols.print();
			return 0;
		}

		u32 _include(st_vm* rt)
		{
			st_value& v1 = rt->get_eval(-1);
			TYPE_CHECK(v1, st_v_string);
			rt->m_evals.pop();

			ns_base::ns_c_toy::h_c_toy* hct;get(hct);
			
			char* str = v1.get<char*>();
			hct->load_file(str);
			hct->run();
			return 0;
		}
	}
}
