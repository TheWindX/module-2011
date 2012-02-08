
#include <climits>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "data_struct.h"

void tester(int sz)
{

	ns_util::array<int> stk(4);
	for(int i = 0; i<sz; ++i)
	{
		int val = rand()%100;
		stk.push(val);
		printf("push: %d, sz: %d, up:%d, low:%d\n", val, stk.size(), stk.m_uper, stk.m_lower );
	}

	for(int i = 0; i<sz; ++i)
	{
		int val = stk.pop();
		printf("pop: %d, sz: %d, up:%d, low:%d\n", val, stk.size(), stk.m_uper, stk.m_lower );
	}
}


int main1(int argc, char** argv)
{
	srand(time(0) );


	using namespace ns_util;

	tester(33);

	return 0;
}



int main2(int argc, char** argv)
{
	using namespace ns_util;
	ns_util::st_map<int, int> m;
	assert(m.first() == false);
	m.insert(3, 4);
	assert(m.get_key() == 3);
	assert(m.get_val() == 4);
	assert(m.first() == true);
	m.erase(3);
	assert(m.first() == false);
	assert(m.insert(3, 3) );
	assert(m.insert(3, 4) == false );
	m.insert(5, 4);
	m.insert(2, 4);
	m.first();
	m.next();
	assert(m.get_key() == 3);
	assert(m.get_val() == 3);
	m.next();
	assert(m.next() == false);

	
	return 0;
}





int main6(int argc, char** argv)
{
	using namespace ns_util;
	array<int> ns;

	ns.push(1);
	ns.push(2);
	ns.push(3);
	ns.push(4);
	ns.push(5);
	
	ns.erase(4);

	ns.insert(3, 6);

	u32 idx = ns.find(2);
	ns.erase(idx);
	ns.insert(idx, 100);

	for(u32 i = 0; i<ns.size(); ++i)
	{
		printf("%d: %d\n", i, ns.at(i) );
	}

	return 0;
}


#include "list.h"


int main10(int argc, char** argv)
{
	ns_util::st_list<int> ls;
	ls.append_after(10);
	ls.append_after(20);
	ls.append_after(30);
	ns_util::st_list<int>::iterator it = ls.find(20);
	it->insert_after(25);
	it->insert_before(15);

	it = ls.erase(20);
	it = ls.erase(it);
	//it = ls.erase(it);


	



	ls.append_before(0);

	for(it = ls.first(); it; it = ls.next() )
	{
		printf("%d\n", it->m_value);
	}

	ls.clear();
	ls.append_after(100);
	for(it = ls.first(); it; it = ls.next() )
	{
		printf("%d\n", it->m_value);
	}
	
	return 0;
}




#include "singleton.h"
struct st_a{int m_val;};
int main12(int argc, char** argv)
{
	ns_util::st_singleton<st_a>::instance().m_val = 3;
	printf("val: %d\n", ns_util::st_singleton<st_a>::instance().m_val);
	return 0;
}



void tester12(int sz)
{

	ns_util::array<int> stk(4);
	for(int i = 0; i<sz; ++i)
	{
		int val = rand()%100;
		stk.resize(stk.size()+1 );
		stk.top() = val;
		printf("push: %d, sz: %d, up:%d, low:%d\n", val, stk.size(), stk.m_uper, stk.m_lower );
	}

	for(int i = 0; i<sz; ++i)
	{
		int val = stk.top();
		stk.resize(stk.size()-1 );
		printf("pop: %d, sz: %d, up:%d, low:%d\n", val, stk.size(), stk.m_uper, stk.m_lower );
	}
}


#include "misc.h"
#include <string>

int main14(int argc, char** argv)
{
	ns_util::st_str_pool p;
	char* s = p.reg("asdfjlksadf");
	char* s1 = p.reg(std::string("asdfjlksadf").c_str() );
	char* s2 = p.reg("txt");
	char* s3 = p.reg( (std::string("t")+"xt").c_str() );
	char* s4 = p.reg( (std::string("t")+"xt1").c_str());
	return 0;
}

#include "easy_set.h"
int main15(int argc, char** argv)
{
	ns_util::st_set<int> s;
	assert(s.first() == false);
	s.insert(3);
	s.insert(4);
	s.insert(5);
	assert(false == s.insert(5) );
	assert(5 == s.get() );
	s.first();
	assert(3 == s.get() );
	s.next();
	assert(4 == s.get() );
	s.next();
	assert(5 == s.get() );
	assert(s.next() == false);
	
	return 0;
}

#include "symbol.h"
int main16(int argc, char** argv)
{
	using namespace ns_util;

	st_path g(0, "a", false);
	st_path* p = g.reg_branch("b.c.d");

	std::string str = p->full_name();
	assert(str == "a.b.c.d");
	str = p->upper()->full_name();
	assert(str == "a.b.c");

	st_path g1;
	str = g1.part_name();
	assert(str == "");
	str = g1.full_name();
	assert(str == "");
	p = g1.reg_branch("x.xx.xxx.xxxx");
	str = p->full_name();
	assert(str == "x.xx.xxx.xxxx");
	str = p->part_name();
	assert(str == "xxxx");
	assert(p->is_branch() == true);

	p = g1.reg_leaf("x.xx.abc");
	assert(p->is_branch() == false);

	p = g1.reg_leaf("x.xx");
	assert(p->first() );
	assert(p->next() );
	assert(p->next() == 0);
	bool b = g1.find("x.xx.xxx.t1", p);
	assert(b == false);
	str = p->full_name();
	assert(str == "x.xx.xxx");

	st_global g2;
	g2.moudle_enter();
	g2.module_path("");
	g2.get_root()->reg_branch("a.b.c");
	
	assert(g2.find_path("a.b", p) );
	st_path* p1 = g2.get_root()->first()->first();
	assert(p == p1);

	g2.using_path("a.b");
	assert(g2.find_path("c", p) );
	p1 = g2.get_root()->first()->first()->first();
	assert(p == p1);
	g2.moudle_exit();

	
	st_scope* s = new st_scope(0, &g2);
	s = s->enter();
	st_path* pp = s->reg_name("a.b")->g.path;

	st_var* v1 = s->reg_name("va");
	assert(v1->m_type == e_local);
	s->reg_name("vb");
	s->reg_name("vc");

	s = s->enter();
	st_var* v2 = s->reg_name("va");
	assert(v1->m_type == e_ref);
	assert(v2->m_type == e_ref);
	assert(v2->r.ref == v1);
	assert(0 == strcmp(v1->r.name, "va") );
	s->reg_name("vd");
	st_path* pp1 = s->find_name("a.b.c")->g.path;
	assert(pp == pp1->upper() );
	s = s->exit();
	s = s->exit();
	assert(s->m_upper == 0);
	

	st_symbols syms;
	syms.enter();
	syms.module_path("a.b.c");
	syms.export_symbol("ga");
	syms.export_symbol("gb");
	syms.export_symbol("gc");
	syms.module_path("a");
	syms.export_symbol("ga");
	st_var* v3 =syms.find_name("ga");
	assert(v3->m_type == e_global);
	const char* n = v3->g.path->full_name();
	assert(strcmp(n, "a.ga") == 0);
	v3 = syms.reg_name("b.c");
	assert(v3);
	assert(v3->m_type == e_global);
	assert(std::string("a.b.c") == v3->g.path->full_name() );

	v3 = syms.find_name("_x");
	assert(v3 == 0);
	
	v3 = syms.reg_name("la");
	syms.reg_name("la2");
	syms.reg_name("la3");
	st_var* v4 = syms.reg_name("la");
	assert(v3 == v4);
	v4 = syms.find_name("la");
	assert(v3 == v4);
	syms.enter();
	v3 = syms.reg_name("ld");
	assert(v3->m_type = e_local);
	v3 = syms.reg_name("la");
	assert(v3->m_type = e_ref);
	assert(std::string("la") == v3->r.name);
	syms.exit();
	v4 = syms.reg_name("la");
	assert(v3->m_type = e_ref);
	assert(v3 != v4);
	assert(v3->r.ref == v4);
	syms.exit();
	
	syms.print();

	return 0;
}

int main17(int argc, char** argv)
{
	using namespace ns_util;
	st_symbols symbs;
	return 0;
}

#include "vm.h"

//int main19(int argc, char** argv)
//{
//	using namespace ns_util;
//	using namespace ns_core;
//
//	st_vm_cor rt;
//	rt.init();
//	u32 idx = rt.c_function_begin();
//
//	//code begin
//	/************************************************************************/
//	/* 
//	i:0,
//	k:1,
//	i = 5;
//	k = 0;
//	c1:
//		k = k+i;
//		i = i-1
//		
//		if false(i == 0) goto c1;
//
//	print(k);
//	*/
//	/************************************************************************/
//	rt.c_push_int(100000);
//	rt.c_pop_local(0);
//	rt.c_push_int(0);
//	rt.c_pop_local(1);
//	
//	u32 c1 = rt.c_apply_begin();
//	rt.c_push_local(1);
//	rt.c_push_local(0);
//	//rt.c_push_global("std.core.add");
//	rt.c_apply();
//	rt.c_pop_local(1);
//
//	rt.c_apply_begin();
//	rt.c_push_local(0);
//	rt.c_push_int(-1);
//	//rt.c_push_global("std.core.add");
//	rt.c_apply();
//	rt.c_pop_local(0);
//	
//	rt.c_apply_begin();
//	rt.c_push_local(0);
//	rt.c_push_int(0);
//	//rt.c_push_global("std.equal_num");
//	rt.c_apply();
//	rt.c_goto_false(c1);
//
//	rt.c_apply_begin();
//	rt.c_push_local(1);
//	//rt.c_push_global("std.sys.print");
//	rt.c_apply();
//
//	rt.c_ret_begin();
//	rt.c_ret();
//	//code end
//
//
//	st_function_code code(idx, 0, 2);
//	st_function_value* f = rt.e_function(&rt, &code);
//	rt.m_evals.pop(); 
//	rt.apply_begin();
//	rt.apply_function(f);
//	rt.eval();
//
//	return 0;
//}


int main20(int argc, char** argv)
{
	using namespace ns_util;
	using namespace ns_core;

	st_vm_cor rt;
	rt.init();

	//code begin
	/************************************************************************/
	/* 
	a = function (a1, a2)
		return a1+a2
	end;

	print(a(3, 4) );
	*/
	/************************************************************************/
	u32 idx1 = rt.c_function_begin();
	rt.c_pop_local(0);
	rt.c_pop_local(1);
	rt.c_ret_begin();
	rt.c_apply_begin();
	rt.c_push_local(0);
	rt.c_push_local(1);
	////rt.c_push_global("std.core.add");
	rt.c_apply();
	rt.c_ret();
	
	u32 idx2 = rt.c_function_begin();
	rt.c_push_function(idx1, 2, 2);
	rt.c_pop_local(0);//a = function...
	rt.c_apply_begin();
	rt.c_apply_begin();
	rt.c_push_int(3);
	rt.c_push_int(4);
	rt.c_push_local(0);
	rt.c_apply();
	//rt.c_push_global("std.sys.print");
	rt.c_apply();
	rt.c_ret_begin();
	rt.c_ret();
	//////////////////////////////////////////////////////////////////////////
	//
	st_function_code cfunc(idx2, 0, 1);
	st_function_value f(&rt, &cfunc);
	rt.apply_begin();
	rt.apply_function(&f);


	rt.eval();

	return 0;
}

//int main21(int argc, char** argv)
//{
//	using namespace ns_util;
//	using namespace ns_core;
//
//	st_vm_cor rt;
//	rt.init();
//	
//	//code begin
//	/************************************************************************/
//	/* 
//	global t = function(x)
//	if x == 0 then return 0;//x = 0L
//	else
//	return x+t(x-1)
//	end
//
//	t(50)
//	*/
//	/************************************************************************/
//	rt.m_symbols.enter();
//	rt.m_symbols.export_symbol("gf");
//	rt.m_symbols.exit();
//	u32 f_idx = rt.c_function_begin();
//	rt.c_pop_local(0);
//	rt.c_apply_begin();
//	rt.c_push_local(0);
//	rt.c_push_int(0);
//	//rt.c_push_global("std.equal_num");
//	rt.c_apply();
//	u32 idx2 = rt.c_goto_false(13);//todo goto t1;
//	rt.c_ret_begin();
//	rt.c_push_int(0);
//	rt.c_ret();
//	//t1:
//	u32 idx4 = rt.c_ret_begin();
//	rt.c_apply_begin();
//	u32 idx3 = rt.c_push_local(0);
//	rt.c_apply_begin();
//	rt.c_apply_begin();
//	rt.c_push_local(0);
//	rt.c_push_int(-1);
//	//rt.c_push_global("std.core.add");
//	rt.c_apply();
//	//rt.c_push_global("gf");
//	rt.c_apply();
//	//rt.c_push_global("std.core.add");
//	rt.c_apply();
//	rt.c_ret();
//
//	u32 f_idx2 = rt.c_push_function(f_idx, 1, 1);
//	rt.c_pop_global("gf");
//	rt.c_function_begin();
//	rt.c_apply_begin();
//	rt.c_apply_begin();
//	rt.c_push_int(100);
//	//rt.c_push_global("gf");
//	rt.c_apply();
//	//rt.c_push_global("std.sys.print");
//	rt.c_apply();
//	rt.c_ret_begin();
//	u32 idx5 = rt.c_ret();
//
//	
//	
//	//////////////////////////////////////////////////////////////////////////
//	//
//	rt.m_codes[idx2].m_num = idx4;
//	st_function_code cfunc(f_idx2, 0, 1);
//	st_function_value f(&rt, &cfunc);
//	rt.apply_begin();
//	rt.apply_function(&f);
//
//
//	rt.set_dbg(true);
//	//rt.set_dbg_step(true);
//	rt.add_break(idx5);
//	rt.eval();
//	
//	return 0;
//}


int main22(int argc, char** argv)
{
	using namespace ns_util;
	using namespace ns_core;

	st_vm_cor rt;
	rt.init();
	
	//code begin
	/************************************************************************/
	/* 
	local t = function(x)
	if x == 0 then return 0;//x = 0L
	else
	return x+t(x-1)
	end

	t(50)
	*/
	/************************************************************************/
	u32 f_idx = rt.c_function_begin();
	rt.c_pop_local(0);
	rt.c_apply_begin();
	rt.c_push_local(0);
	rt.c_push_int(0);
	//rt.c_push_global("std.equal_num");
	rt.c_apply();
	u32 idx2 = rt.c_goto_false(13);//todo goto t1;
	rt.c_ret_begin();
	rt.c_push_int(0);
	rt.c_ret();
	//t1:
	u32 idx4 = rt.c_ret_begin();
	rt.c_apply_begin();
	u32 idx3 = rt.c_push_local(0);
	rt.c_apply_begin();
	rt.c_apply_begin();
	rt.c_push_local(0);
	rt.c_push_int(-1);
	////rt.c_push_global("std.core.add");
	rt.c_apply();
	rt.c_push_ref(0);
	rt.c_apply();
	////rt.c_push_global("std.core.add");
	rt.c_apply();
	rt.c_ret();

	u32 f_idx2 = rt.c_push_function(f_idx, 1, 1);
	rt.c_pop_ref(0);//ref
	rt.c_function_begin();
	rt.c_apply_begin();
	rt.c_apply_begin();
	rt.c_push_int(100);
	rt.c_push_ref(0);//ref
	rt.c_apply();
	//rt.c_push_global("std.sys.print");
	rt.c_apply();
	rt.c_ret_begin();
	u32 idx5 = rt.c_ret();

	
	
	//////////////////////////////////////////////////////////////////////////
	//
	rt.m_codes[idx2].m_num = idx4;

	st_function_code* code1 = rt.m_codes[f_idx2].get<st_function_code*>();
	code1->add_ref(0);


	st_function_code cfunc(f_idx2/* todo */, 0, 1);
	cfunc.add_ref(U32_NA);
	st_function_value f(&rt, &cfunc );
	rt.apply_begin();
	rt.apply_function(&f);


	//rt.set_dbg(true);
	//rt.set_dbg_step(true);
	//rt.add_break(idx5);
	rt.eval();
	
	return 0;
}

int main23(int argc, char** argv)
{
	using namespace ns_util;
	using namespace ns_core;

	st_vm_cor rt;
	rt.init();
	//code begin
	/************************************************************************/
	/* 
	x = 125(x(0R) )
	t = function(p)//t(0L)
		return p+x//p(0L), x(0R)
	end

	print(t(100) )
	*/
	/************************************************************************/
	u32 f_idx = rt.c_function_begin();
	rt.c_pop_local(0);
	rt.c_ret_begin();
	rt.c_apply_begin();
	rt.c_push_local(0);
	rt.c_push_ref(0);
	////rt.c_push_global("std.core.add");
	rt.c_apply();
	rt.c_ret();

	u32 f_idx2 = rt.c_function_begin();
	rt.c_push_int(5);
	rt.c_pop_ref(0);
	u32 idx = rt.c_push_function(f_idx, 1, 1);
	rt.c_pop_local(0);

	rt.c_apply_begin();
	rt.c_apply_begin();
	rt.c_push_int(100);
	rt.c_push_local(0);
	rt.c_apply();
	//rt.c_push_global("std.sys.print");
	rt.c_apply();
	

	rt.c_ret_begin();
	rt.c_ret();

	
	
	//////////////////////////////////////////////////////////////////////////
	//
	st_function_code cfunc(f_idx2/* todo */, 0, 1);
	cfunc.add_ref(U32_NA);
	st_function_value f(&rt, &cfunc );
	rt.apply_begin();
	rt.apply_function(&f);

	st_function_code* code1 = rt.m_codes[idx].get<st_function_code*>();
	code1->add_ref(0);


	//rt.set_dbg(true);
	//rt.set_dbg_step(true);
	//rt.add_break(idx5);
	rt.eval();
	
	return 0;
}

int main24(int argc, char** argv)
{
	using namespace ns_util;
	using namespace ns_core;

	st_vm_cor rt;
	rt.init();
	//code begin
	/************************************************************************/
	/* 
	x = 100;//x(0R)

	t = function(p)//t(0L),
		//x(0R), p(1R)
		return function() return x+p;//x(0R), p(1R)
	end

	print(t(100)() )
	*/
	/************************************************************************/
	u32 f_idx3 = rt.c_function_begin();
	rt.c_ret_begin();
	rt.c_apply_begin();
	rt.c_push_ref(0);
	rt.c_push_ref(1);
	//rt.c_push_global("std.core.add");
	rt.c_apply();
	rt.c_ret();


	u32 f_idx2 = rt.c_function_begin();
	rt.c_pop_ref(1);
	rt.c_ret_begin();
	u32 idx3 = rt.c_push_function(f_idx3, 0, 0);
	rt.c_ret();

	u32 f_idx1 = rt.c_function_begin();
	rt.c_push_int(100);
	rt.c_pop_ref(0);
	
	u32 idx2 = rt.c_push_function(f_idx2, 1, 1);
	rt.c_pop_local(0);
	
	rt.c_apply_begin();

	rt.c_apply_begin();
	
	rt.c_apply_begin();
	rt.c_push_int(100);
	rt.c_push_local(0);
	rt.c_apply();

	rt.c_apply();

	//rt.c_push_global("std.sys.print");
	rt.c_apply();

	rt.c_ret_begin();
	rt.c_ret();
	
	
	//////////////////////////////////////////////////////////////////////////
	//
	st_function_code cfunc(f_idx1/* todo */, 0, 1);
	cfunc.add_ref(U32_NA);//x
	st_function_value f(&rt, &cfunc );
	rt.apply_begin();
	rt.apply_function(&f);


	st_function_code* code2 = rt.m_codes[idx2].get<st_function_code*>();
	code2->add_ref(0);//x
	code2->add_ref(U32_NA);//p

	st_function_code* code3 = rt.m_codes[idx3].get<st_function_code*>();
	code3->add_ref(0);//x
	code3->add_ref(1);//p


	//rt.set_dbg(true);
	//rt.set_dbg_step(true);
	//rt.add_break(idx5);
	rt.eval();
	
	return 0;
}

#include "context.h"
int main25(int argc, char** argv)
{	
	//g_ctx.load_string("function(){return;};");
	g_ctx.load_file("test.txt");
	//g_ctx.	get_vm_cor().set_dbg(true);
	//g_ctx.get_vm_cor().set_dbg_step(true);
	
	
	//¥Ú”°
	//g_ctx.get_vm_cor().m_symbols.print();
	//ns_core::ns_ast::st_function* f = dynamic_cast<ns_core::ns_ast::st_function*>(g_ctx.get_ast_root() );
	g_ctx.print_codes();
	system("pause");
	g_ctx.run();
	system("pause");
	int i = 0;

	return 0;
}

#include "debug.h"
#include <iostream>
int main26(int, char**)
{
	ns_core::ns_debug::st_debug d;
	std::string str_test = "asdfasdf\n\
asdfjkasjdflajsdf\n\
asdfasdfasf";

	d.m_src_text.reset(str_test.c_str(), str_test.size() );
	d.m_src_text.analyze();
	std::cout<<d.m_src_text.get_line(0)<<std::endl;
	std::cout<<d.m_src_text.get_line(1)<<std::endl;
	std::cout<<d.m_src_text.get_line(2)<<std::endl;

	std::cout<<d.m_src_text.get_line_by_pos(27)<<std::endl;
	
	system("pause");
	return 0;
}

#include "debug.h"
#include "easy_set.h"

int main(int, char**)
{
	//g_ctx.load_string("function(){return;};");
	g_ctx.load_file("test.txt");
	//g_ctx.	get_vm_cor().set_dbg(true);
	//g_ctx.get_vm_cor().set_dbg_step(true);


	//¥Ú”°
	//g_ctx.get_vm_cor().m_symbols.print();
	//ns_core::ns_ast::st_function* f = dynamic_cast<ns_core::ns_ast::st_function*>(g_ctx.get_ast_root() );
	g_ctx.print_codes();
	system("pause");
	g_ctx.run();
	system("pause");
	int i = 0;
}