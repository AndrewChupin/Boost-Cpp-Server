

#include "request_handler.hpp"
#include <fstream>
#include <iostream>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

namespace http {
    namespace server {

        request_handler::request_handler(const std::string &doc_root)
                : doc_root_(doc_root) {
        }


        void request_handler::handle_request(const request &req, reply &rep) {
            // Decode url to path.
            std::string request_path;
            if (!url_decode(req.uri, request_path)) {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }

            // Request path must be absolute and not contain "..".
            if (request_path.empty() || request_path[0] != '/'
                || request_path.find("..") != std::string::npos) {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }


            std::cout<< "Request path " << request_path << std::endl;
            auto handler = routes.at(request_path);

            if (!handler) {
                rep = reply::stock_reply(reply::not_found);
                return;
            }

            // Fill out the reply to be sent to the client.
            rep.status = reply::ok;
            rep.content = handler();
            rep.headers.resize(2);
            rep.headers[0].name = "Content-Length";
            rep.headers[0].value = std::to_string(rep.content.size());
            rep.headers[1].name = "Content-Type";
            std::string html = "html";
            rep.headers[1].value = mime_types::extension_to_type(html);
        }


        bool request_handler::url_decode(const std::string &in, std::string &out) {
            out.clear();
            out.reserve(in.size());
            for (std::size_t i = 0; i < in.size(); ++i) {
                if (in[i] == '%') {
                    if (i + 3 <= in.size()) {
                        int value = 0;
                        std::istringstream is(in.substr(i + 1, 2));
                        if (is >> std::hex >> value) {
                            out += static_cast<char>(value);
                            i += 2;
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else if (in[i] == '+') {
                    out += ' ';
                } else {
                    out += in[i];
                }
            }
            return true;
        }


        void request_handler::define_route(route &route_pair) {
            routes.insert(route_pair);
        }


    } // namespace server
} // namespace http