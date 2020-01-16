#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <fstream>

#include "list_dir.hpp"
#include "exception.hpp"

void WPP::list_dir(WPP::Request& req, WPP::Response& res) {
    unsigned char isFile = 0x8, isFolder = 0x4;
    struct dirent *dir;
    int status;
    struct stat st_buf;

    // Mime


    char* actual_path;
    char* base_path = realpath(req.params.c_str(), NULL);
    std::string new_path = "";
    actual_path = realpath(req.params.c_str(), NULL);

    if(req.query.find("open") != req.query.end()) {
        new_path += req.query["open"];
        strcat(actual_path, new_path.c_str());
    }

    // prevent directory traversal
    char* effective_path = realpath(actual_path, NULL);
    if ((effective_path != NULL) && (strncmp(base_path, effective_path, strlen(base_path)) != 0)) {
        free(actual_path);
        actual_path = base_path;
        new_path = "";
    }
    free(effective_path);
    effective_path = NULL;

    status = stat(actual_path, &st_buf);

    if (status != 0)  {
        res.code = StatusCode::not_found;
        res.phrase = "Not Found";
        res.type = "text/plain";
        res.send("Not found");
    } else if (S_ISREG (st_buf.st_mode)) {
        size_t ext_pos = std::string(actual_path).find_last_of(".");
        auto ext_iter = mime.find(std::string_view(actual_path).substr(ext_pos + 1));
        if(ext_iter != mime.end()){
            res.type = ext_iter->second;
        }
        else {
            res.type = "application/octet-stream";
        }
        std::ifstream ifs(actual_path);
        copy(std::istreambuf_iterator<char>(ifs),std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(res.body));
    } else if (S_ISDIR (st_buf.st_mode)) {
        DIR* dir_d = opendir(actual_path);

        if (dir_d == NULL) throw WPP::Exception("Unable to open / folder");

        std::stringstream out;
        out << "<title>" << new_path << "</title>" << std::endl;
        out << "<table>";

        while((dir = readdir(dir_d))) {
            out << "<tr><td><a href=\"" << req.path << "?open=" << new_path << "/" << dir->d_name << """\">";

            if (dir->d_type == isFolder) {
                out << "[" << dir->d_name << "]";
            } else {
                out << " " << dir->d_name << "";
            }

            out << "</a></td></tr>";
        }

        out << "</table>";

        res.send(out.str().c_str());
    }

    if (actual_path != base_path) {
        free(actual_path);
    }
    free(base_path);
}