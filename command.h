#pragma pack(push, 1)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

struct FLAG_ELEM{
    std::string flag;
    std::string content;
    FLAG_ELEM(std::string flag,std::string content){
        this->flag = flag;
        this->content = content;
    }
    FLAG_ELEM(std::string flag){
        this->flag = flag;
        this->content = "";
    }
};


//using std::stringstream = std::stringstream;

struct COMMAND_PROCESSOR{
    std::string line;
    std::string command;
    std::vector<FLAG_ELEM> flags;
    std::vector<std::string> args;
    int argc(){ return _args; }
    int flagc(){ return _flags; }

    bool has_flag(std::string s){
      for(int i=0;i<flags.size();i++){
        if(flags[i].flag == s) return true;
      }
      return false;
    }
    std::string get_flag(std::string s){
      for(int i=0;i<flags.size();i++){
        if(flags[i].flag == s) return flags[i].content;
      }
      return "";
    }
    bool get_flag(std::string s, std::string& e){
      for(int i=0;i<flags.size();i++){
        if(flags[i].flag == s) {
          e = flags[i].content;
          return true;
        }
      }
      return false;
    }

    int process(std::string input){
      _args =0;
      _flags =0;
        line = input;
        std::stringstream ss(input);
        ss>>command;
        std::string part;
        std::string aux;
        std::string aux2;
        while(ss >> part){
            reset:
            bool ismulti = false;
            if(part[0] == '-'){ // flag
                if(ss >> aux){
                    if(aux[0] == '-'){ // one part flag
                        FLAG_ELEM fe(part);
                        flags.push_back(fe);
                        _flags ++ ;
                        part = aux;
                        goto reset;
                    }else{ // two part flag
                        if(aux[0] == '\"' || part[0] == '\''){  // multiple
                            ismulti = true;
                            aux2 = "";
                            do{
                                aux2+=aux;
                                size_t pos = aux.size();
                                if(aux[ pos - 1 ] == '\"') break; // end of block
                                aux2+=" ";
                            }while(ss >> aux);
                            aux = aux2;
                        }
                        if(ismulti) aux = aux.substr(1,aux.size()-2);
                        FLAG_ELEM fe(part,aux);
                        flags.push_back(fe);
                        _flags ++ ;
                    }
                }else { // one part at end
                    FLAG_ELEM fe(part);
                    flags.push_back(fe);
                    _flags ++ ;
                }
            } else { // arg
                if(part[0] == '\"' || part[0] == '\''){ // multiple
                    ismulti = true;
                    aux = "";
                    do{
                        aux+=part;
                        std::size_t pos = part.size();
                        if(part[ pos - 1 ] == '\"') break; // end of block
                        aux+=" ";
                    }while(ss >> part);
                    part = aux;
                }
                if(ismulti) part = part.substr(1,part.size()-2);
                args.push_back(part);
                _args ++ ;
            }
        }
        return 0;
    }


    private:
    int _args ;
    int _flags;
};


#pragma pack(pop)
