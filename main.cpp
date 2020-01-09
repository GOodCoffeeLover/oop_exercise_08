#include<iostream>
#include<vector>
#include "figures"
#include "factory"
#include "redactor"

void print_menu(){
	std::cout
	<<"1. Print menu"<<std::endl
	<<"2. Save document"<<std::endl
	<<"3. Load documet"<<std::endl
	<<"4. New document (clear current document)"<<std::endl
	<<"5. Insert figure"<<std::endl
	<<"6. Remove figure"<<std::endl
	<<"7. Undo"<<std::endl
	<<"8. Redo"<<std::endl
	<<"9. Do action with figures"<<std::endl
	<<"0. Exit"<<std::endl;
}

bool is_num( std::string& str){
	for(char c: str)
		if(!( ((c>='0') && (c<='9')) || (c=='-') || (c=='.') ) )
			return false;
	return true;
}


typedef  int work_type;

work_type get_num(){
	std::string buf;
	std::cin>>buf;
	if(is_num(buf))
		return atoi(buf.c_str());
	else
		throw std::logic_error("wrong input");
}

int main(){
	print_menu();
	Redactor<work_type> redactor;
	while(true){
	try{
	std::cout<<">>"<<std::flush;
	switch(get_num()){
		case 0: 
			return 0;
		case 1:
			print_menu();
			break;
		case 2:{
			std::string file_path;
			std::cout<<"Input file name/path"<<std::endl<<">>"<<std::flush;
			std::cin>>file_path;
			redactor.save(file_path);
			break;
		}
		case 3:{
			std::string file_path;
			std::cout<<"Input file name/path"<<std::endl<<">>"<<std::flush;
			std::cin>>file_path;
			redactor.load(file_path);
			break;
		}
		case 4:{
			redactor.New();
			break;
		}
		case 5:{
			std::cout<<"input position for inserting figure"<<std::endl<<">>"<<std::flush;
			unsigned long long pos=get_num();
			std::cout
			<<"Chose figure for insert: "<<std::endl
			<<"1. Square (2 vertex)"<<std::endl
			<<"2. Rectangle (3 vertex)"<<std::endl
			<<"3. Trapeze (4 vertex)"<<std::endl<<">>"<<std::flush;
			switch(get_num()){
				case 1:
					redactor.insert(pos, 
						std::vector<std::pair<work_type, work_type>>{
							std::pair<work_type, work_type>{get_num(), get_num()},
							std::pair<work_type, work_type>{get_num(), get_num()}
					});
					break;
				case 2:
					redactor.insert( pos, 
						std::vector< std::pair<work_type, work_type> > {
							std::pair<work_type, work_type>{get_num(), get_num()},
							std::pair<work_type, work_type>{get_num(), get_num()},
							std::pair<work_type, work_type>{get_num(), get_num()}
					});
					break;
				case 3:
					redactor.insert(pos,
						std::vector<std::pair<work_type, work_type>>{
							std::pair<work_type, work_type>{get_num(), get_num()},
							std::pair<work_type, work_type>{get_num(), get_num()},
							std::pair<work_type, work_type>{get_num(), get_num()},
							std::pair<work_type, work_type>{get_num(), get_num()}
					});
					break;
			}
			break;
		}
		case 6:{
			std::cout<<"input figure position for removing"<<std::endl<<">>"<<std::flush;
			redactor.remove(get_num());
			break;
		}
		case 7:
			redactor.undo();
			break;
		case 8:
			redactor.redo();
			break;
		case 9:{
			std::cout<<"Choose input figure number for action or -1 for all figure "<<std::endl<<">>"<<std::flush;
			int pos =get_num();
			std::cout<<"Choose action:"<<std::endl
			<<"0. print all squares"<<std::endl
			<<"1. print all centers"<<std::endl
			<<"2. print full information about figure"<<std::endl
			<<">>"<<std::flush;
			if(pos == -1)
				redactor.do_for_all(get_num());
			else
				redactor.do_for_one(pos, get_num());
			break;
		}
		
			
	}
	}catch(std::logic_error& e){
		std::cerr<<"logic error: "<<e.what()<<std::endl;
	}catch(std::runtime_error& e){
		std::cerr<<"runtime error: "<<e.what()<<std::endl;
	}
	}
	
	//return 0;
}
