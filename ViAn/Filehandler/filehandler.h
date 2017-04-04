#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#define WINDOWS 1
#define UNIX 2
#ifdef _WIN32
    #include <windows.h>
    #include "stringhelper.h"
#endif
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include <sstream>
#include "project.h"
#include "dir.h"
#include <algorithm>



enum WRITE_OPTION{APPEND, OVERWRITE};
typedef int FH_ERROR; // file handler error code
typedef int ID;
struct Project; // fix for include issue
struct ProjFiles;
class FileHandler
{
public:
    FileHandler();
    //
    //  Project manipulation
    //
    std::string work_space;
    void set_workspace(std::string new_work_space);
    Project* open_project(std::string dirpath);
    Project* create_project(std::string proj_name);
    FH_ERROR delete_project(Project* proj);
    Project* load_project(std::string full_project_path);
    Project* load_project(std::string proj_name, std::string dir_path);
    void save_project(ID id);
    void save_project(Project* proj);
    // Video operations
    void remove_video_from_project(ID proj_id, ID vid_id);
    ID add_video(Project* proj, std::string file_path);
    //directory manipulation
    //varying implementation
    ID create_directory(std::string dir_path);
    FH_ERROR delete_directory(ID id);

    //file manipulation

    ID create_file(std::string file_name, ID dir_id);
    FH_ERROR delete_file(ID id);
    void write_file(ID id, std::string text, WRITE_OPTION opt = WRITE_OPTION::APPEND);
    void read_file(ID id,  std::string& buf, int lines_to_read = -1);

    friend bool operator==(ProjFiles& pf, ProjFiles& pf2);
    friend bool operator==(Project& proj, Project& proj2);

    bool proj_equals(Project& proj, Project& proj2);
    bool projfiles_equal(ProjFiles& pf, ProjFiles& pf2);
    bool dirs_equal(ID id, ID id2);
    bool files_equal(ID id, ID id2);
    // thread safe read operations for maps


    std::string get_dir(ID id);
    Project* get_project(ID id);
    std::string get_file(ID id);

    // Last error
    FH_ERROR last_error;

private:

    void update_proj_files(Project* proj); // used to update existing project files and maps
    // thread safe add operations for maps
    ID add_file(std::string file_path);
    void add_project(std::pair<ID,Project*> pair);

    ID add_dir(std::string dir_path);
    ID load_project_file(std::string file_path, std::stringstream& proj_file_stream);
    void load_proj_files(std::string str);
    //add used for loading project from file
    void add_file(ID id , std::string file_path);

    /**
     * @brief m_projects, m_fileMap, m_dirMap
     * map structures for keeping track of projects, files and directories.
     */
    std::map<ID,Project*> projects;
    std::map<ID, std::string> file_map;
    std::map<ID, std::string> dir_map;
    /**
     * @todo implement smarter lock mechanism to avoid overhead
     * of only 1 reader/writer at a time
     * @brief dirMapLock, fileMapLock, projMapLock
     */
    std::mutex dir_map_lock; // lock for handling directory write/read
    std::mutex file_map_lock;// lock for handling file write/read
    std::mutex proj_map_lock;// lock for handling project write/read
    ID project_id; //counter for project ids
    ID file_id; //counter for file ids
    ID dir_id; //counter for directory ids

};

#endif // FILEHANDLER_H
