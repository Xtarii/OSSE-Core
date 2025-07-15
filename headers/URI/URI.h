#ifndef OSSE_URI
#define OSSE_URI

#include <sstream>
#include <string>

namespace OSSE {
    /**
    * URI Structure
    *
    * Simple URI object containing
    * information about the URI.
    *
    * ```cpp
    * URI uri = URI::parse("https://example.com/");
    * // uri.host      - example.com
    * // uri.path      - /
    * // uri.protocol  - https
    * ```
    */
    struct URI {
        private:
            std::string
                /**
                 * URI Query
                 *
                 * Any extra data that is provided
                 * with the `URI`
                 */
                query_,
                /**
                 * URI Path
                 */
                path_,
                /**
                 * URI Protocol
                 *
                 * The Protocol used for communication
                 */
                protocol_,
                /**
                 * URI Host
                 *
                 * A `domain` or `IP` that represents
                 * the `address` of the Host
                 */
                host_,
                /**
                 * URI Port
                 */
                port_,
                /**
                 * URI Fragment
                 */
                fragment_;

            /**
             * Construct a new URI object
             *
             * @param protocol Protocol, example `http` or `https`
             * @param host Host, this is a domain or IP address
             * @param port Port, the port used
             * @param path Path
             * @param query URI Query arguments
             * @param fragment Fragment
             */
            URI(
                std::string protocol,
                std::string host,
                std::string port,
                std::string path,
                std::string query,
                std::string fragment
            );

            /**
             * Construct a new empty URI object
             */
            URI() {}





        public:
            /**
            * Parses URI string into URI object
            *
            * @param uri URI string reference
            * @return Parsed URI object
            */
            static URI parse(std::string &uri);



            /**
            * String version of this URI object
            *
            * @return URI object as string
            */
            std::string toString() {
                std::stringstream stream("");

                stream
                    << "{\n"
                    << "\tProtocol: \"" << (protocol_.empty() ? "[NONE]" : protocol_) << "\",\n"
                    << "\tHost: \"" << host_ << "\",\n"
                    << "\tPort: \"" << (port_.empty() ? "[NONE]" : port_) << "\",\n"
                    << "\tPath: \"" << path_ << "\",\n"
                    << "\tQuery: \"" << (query_.empty() ? "[NONE]" : query_) << "\",\n"
                    << "\tFragment: \"" << (fragment_.empty() ? "[NONE]" : fragment_) << "\",\n"
                    << "}";
                return stream.str();
            }



            /**
             * Constructs domain string
             *
             * Creates a domain with the `protocol` and `host`
             * that is specified in the `URI`.
             *
             * @return Domain string
             */
            std::string domain() {
                std::stringstream stream;

                bool hasProtocol = !protocol_.empty();

                stream
                    << (hasProtocol ? protocol_ + "://" : "")
                    << host_
                    << (port_.empty() ? "" : ":") << (port_.empty() ? "" : port_)
                    << (hasProtocol ? "/" : "");
                return stream.str();
            }

            /**
             * Constructs URI with domain and `path`
             *
             * @param path The Path to append to domain
             * @return URI string
             */
            std::string asPath(std::string path) {
                std::stringstream stream;

                stream
                    << (protocol_.empty() ? "" : protocol_ + "://")
                    << host_
                    << path;
                return stream.str();
            }

            /**
             * Constructs full URI string
             *
             * Creates a URI string with the data
             * provided when this object was constructed.
             *
             * @return URI string
             */
            std::string fullURI() {
                std::stringstream stream;

                stream
                    << (protocol_.empty() ? "" : protocol_ + "://")
                    << host_
                    << (port_.empty() ? "" : ":" + port_)
                    << path_
                    << (query_.empty() ? "" : query_)
                    << (fragment_.empty() ? "" : fragment_);
                return stream.str();
            }
    };
}

#endif // OSSE_URI
