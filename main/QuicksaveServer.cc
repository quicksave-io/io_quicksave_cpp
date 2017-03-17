// This file is a part of quicksave project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#include "server/QuicksaveHandler.h"
#include <Config.h>
#include <unistd.h>
#include <bean/DoneTaskBean.h>
#include <folly/Memory.h>
#include <folly/io/async/EventBaseManager.h>
#include <gflags/gflags.h>
#include <mq/queue.h>
#include <proxygen/httpserver/HTTPServer.h>
#include <proxygen/httpserver/RequestHandlerFactory.h>

using folly::EventBase;
using folly::EventBaseManager;
using folly::SocketAddress;

using Protocol = proxygen::HTTPServer::Protocol;

class QuicksaveHandlerFactory : public proxygen::RequestHandlerFactory
{
public:
    void onServerStart(folly::EventBase* evb) noexcept override
    {
    }

    void onServerStop() noexcept override
    {
    }

    proxygen::RequestHandler* onRequest(proxygen::RequestHandler*, proxygen::HTTPMessage*) noexcept override
    {
        return new QuicksaveHandler();
    }
};

void consumeBean(DoneTaskBean bean)
{
    std::cout << "Got callback from " << bean.name << std::endl;
}

void engine_thread()
{
    Queue::consume<DoneTaskBean>(consumeBean);
}

int main(int argc, char* argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();

    std::vector<proxygen::HTTPServer::IPConfig> IPs = {
        {SocketAddress(FLAGS_ip, FLAGS_http_port, true), Protocol::HTTP},
        {SocketAddress(FLAGS_ip, FLAGS_spdy_port, true), Protocol::SPDY},
        {SocketAddress(FLAGS_ip, FLAGS_h2_port, true), Protocol::HTTP2},
    };

    if (FLAGS_threads <= 0)
    {
        FLAGS_threads = sysconf(_SC_NPROCESSORS_ONLN);
        CHECK(FLAGS_threads > 0);
    }

    proxygen::HTTPServerOptions options;
    options.threads = static_cast<size_t>(FLAGS_threads);
    options.idleTimeout = std::chrono::milliseconds(60000);
    options.shutdownOn = {SIGINT, SIGTERM};
    options.enableContentCompression = false;
    options.handlerFactories = proxygen::RequestHandlerChain()
                                   .addThen<QuicksaveHandlerFactory>()
                                   .build();
    options.h2cEnabled = true;

    proxygen::HTTPServer server(std::move(options));
    server.bind(IPs);

    // Start HTTPServer mainloop in a separate thread
    std::thread t([&]() {
        server.start();
    });

    std::thread engine(engine_thread);
    engine.join();

    t.join();
    return 0;
}
