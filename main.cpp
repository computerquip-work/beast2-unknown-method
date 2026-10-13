#include <boost/beast2/http_worker.hpp>
#include <boost/capy/test/read_stream.hpp>
#include <boost/capy/test/run_blocking.hpp>
#include <boost/capy/test/write_stream.hpp>

namespace capy = boost::capy;
namespace http = boost::http;

int main()
{
    capy::test::read_stream input;
    capy::test::write_stream output;
    input.provide("CUSTOM /records HTTP/1.1\r\n"
                  "Host: localhost\r\nConnection: close\r\n\r\n");
    boost::beast2::http_worker worker(
        {},
        http::make_parser_config(http::parser_config(true)),
        http::make_serializer_config(http::serializer_config{}));
    worker.stream = capy::any_read_stream(&input);
    worker.rp.res_body = http::any_buffer_sink(worker.serializer.sink_for(output));
    capy::test::run_blocking()(worker.do_http_session());
    return !output.data().starts_with("HTTP/1.1 501 ");
}
