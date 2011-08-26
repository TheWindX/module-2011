

#pragma once


namespace ns_path
{
	enum
	{
		e_path = 0,
		e_entity,
	};

	struct st_node
	{
		int m_id;
		int m_type;
		std::string m_name;
		st_node* m_up;
		st_node* m_low;
		st_node* m_left;
		st_node* m_right;

		st_node()
		{
			m_id = 0;m_type = e_path;m_name = "";m_up = 0; m_low = 0; m_left = 0; m_right = 0;
		}
	};

	typedef st_node st_path;
	typedef st_node st_entity;

	
	enum
	{
		e_is_not_entity = 0,
		e_is_not_path,
		e_no_exist,

		e_add_yet,
		
		e_no_only_path_or_entity,
	};
	struct st_path_service
	{	
		st_path* reg_path(st_path* up, std::string name);
		st_entity* reg_entity(st_path* up, std::string name);

		std::string get_node_string(st_node* path);


		bool add_path(st_path* path);
		void reset_path();
		st_path* get_path(const std::string& pname);
		st_entity* get_entity(const std::string& pname);
		int get_error();



		int m_last_error;
		int m_id_count;
		st_node* m_root;
		std::vector<st_path*> m_search_path;

		st_path_service();
		~st_path_service();
	private:
		st_node* get_node_in_path(st_path* path, const std::string& name);
	};



}