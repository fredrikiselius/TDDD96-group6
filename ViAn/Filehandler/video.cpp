#include "video.h"
/**
 * @brief Video::Video
 */
Video::Video()
{
    this->id = -1;
    this->file_path = "";
}
/**
 * @brief Video::Video
 * @param id
 * @param filepath
 */
Video::Video(std::string file_path){
    this->file_path = file_path;
    this->id = -1;
}
/**
 * @brief operator >>
 * @param is
 * @param vid
 * @return stringstream
 */
std::stringstream& operator>>(std::stringstream& is, Video& vid){    
    is >> vid.file_path;
    return is;
}
/**
 * @brief operator <<
 * @param os
 * @param vid
 * @return used for writing project to file
 */
std::stringstream& operator<<(std::stringstream& os, const Video& vid){
    os << vid.file_path.c_str() << " ";
    return os;
}
/**
 * @brief operator ==
 * @param v1
 * @param v2
 * @return if videos the same TRUE
 */
bool operator==(Video v1, Video v2){
    return v1.file_path == v2.file_path;
}
