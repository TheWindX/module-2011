
#pragma once

#include "vm_data.h"

namespace ns_core
{
	using namespace ns_base;
	struct st_vm_env : public st_vm_data
	{
		st_value& get_global(u32 idx){return m_globals[idx]; }
		u32 get_local_size(){return m_locals.size()-m_cur_eval_tag; }
		st_value& get_local(u32 idx){return m_locals[m_cur_local_tag+idx]; }
		st_value& get_eval(s32 idx){if(idx<0)return m_evals[m_evals.size()+idx]; else return m_evals[m_cur_eval_tag+idx]; }
		u32 get_eval_size(){return m_evals.size()-m_cur_eval_tag; }
		void set_eval_top(u32 idx){m_evals.resize(m_cur_eval_tag+idx); }
		u32 get_ref_size(){ if(m_cur_func->m_refs)return m_cur_func->m_refs->size();else return 0; }
		st_value& get_ref(u32 idx){return *(st_value*)m_cur_func->m_refs->at(idx).m_val; }//ȡ���õı���
		st_value& get_ref_raw(u32 idx){return m_cur_func->m_refs->at(idx); }//���ñ���
	};

	struct i_functor;
	struct st_vm_plugs : public st_vm_env
	{
		u32 reg_proto_code(i_code_proto* code);
		u32 reg_proto_value(i_value_proto* value);
		i_code_proto* get_code_proto(u32 tag_id);
		i_value_proto* get_value_proto(u32 tag_id);

		//ע�ᵽȫ�ַ��ű��ȫ�ֱ�����
		u32 reg_function(const char* func_name, f_proto func);
		u32 reg_function(const char* func_name, i_functor* f);
		ns_core::st_sym_var* reg_global(const char* func_name);//ע��ȫ�ַ�����

		void clear();//TODO, ���ע�� proto, ��primary_function
	};

	struct i_debug// exception: break int
	{
		virtual bool is_step() = 0;//�Ƿ�ÿһ����ϵ�
		virtual u32 get_break_idx() = 0;//��öϵ�λ��
		virtual void next_break() = 0;//��������һ���ϵ�
		virtual void reset() = 0;//����debug, //���� break indexs

		virtual u32 on_code(st_vm* vm) = 0;//�ڶϵ�ʱ����,���ضϵ㴦��״̬��Ĭ��Ϊ0
	};

	struct st_vm_eval : public st_vm_plugs
	{	
		i_debug* m_debug;

		st_vm_eval(){m_debug = 0;}
		void set_debug(i_debug* dbg){m_debug = dbg;};
		u32 eval(bool _continue = false);//��ֵ

		void apply_begin();
		void apply_function(st_function_value* func);
		void apply_primary(f_proto pfunc);
		void apply_instant();//ֱ��ִ�� ջ���� function(��primary)

		void ret_begin();
		void ret(bool byield = false);
	};

	struct st_vm_state : public st_vm_eval
	{
		//for debug
		u32 s_cur_pc();
		st_code s_cur_code();
		u32 s_eval_size();
		st_value s_eval_value(u32 idx);
		u32 s_local_size();
		st_value s_local_value(u32 idx);
		u32 s_ref_size();
		st_value s_ref_value(u32 idx);
		st_value s_ref_raw(u32 idx);
	};

	struct i_context;
	struct st_vm : public st_vm_state
	{
		//u32 get_code_num();
		//get_code_size() has been shown
		st_vm();
		i_context* m_ctx;
		i_context* get_i_context(){return m_ctx; }
		std::string code_to_string(u32 idx);
	};
}