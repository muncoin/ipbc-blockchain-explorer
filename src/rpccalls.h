//
// Created by mwo on 13/04/16.
//

#ifndef CROWXMR_RPCCALLS_H
#define CROWXMR_RPCCALLS_H

#include "monero_headers.h"

namespace xmreg
{

    using namespace cryptonote;
    using namespace crypto;
    using namespace std;


    using request = cryptonote::COMMAND_RPC_GET_TRANSACTION_POOL::request;
    using response = cryptonote::COMMAND_RPC_GET_TRANSACTION_POOL::response;
    using http_simple_client = epee::net_utils::http::http_simple_client;


    class rpccalls
    {

        string deamon_url {"http:://127.0.0.1:18081"};
        uint64_t timeout_time {200000};

    public:

        uint64_t
        get_current_height()
        {
            COMMAND_RPC_GET_HEIGHT::request   req;
            COMMAND_RPC_GET_HEIGHT::response  res;

            http_simple_client m_http_client;

            // perform RPC call to deamon to get
            // its transaction pull
            boost::mutex m_daemon_rpc_mutex;

            m_daemon_rpc_mutex.lock();

            bool r = epee::net_utils::invoke_http_json_remote_command2(
                    deamon_url + "/getheight",
                    req, res, m_http_client, 200000);

            m_daemon_rpc_mutex.unlock();

            if (!r)
            {
                cerr << "Error connecting to Monero deamon at "
                     << deamon_url << endl;
                return 0;
            }
            else
            {
                cout << "rpc call /getheight OK: " << endl;
            }

            return res.height;

        }

        //@TODO not finished
        vector<block>
        get_blocks(uint64_t start_height)
        {

            vector<block> blocks;

            COMMAND_RPC_GET_BLOCKS_FAST::request req;
            COMMAND_RPC_GET_BLOCKS_FAST::response res;

            req.start_height = start_height;


            http_simple_client m_http_client;

            // perform RPC call to deamon to get
            // its transaction pull
            boost::mutex m_daemon_rpc_mutex;

            m_daemon_rpc_mutex.lock();

            bool r = epee::net_utils::invoke_http_json_remote_command2(
                    deamon_url + "/getblocks.bin",
                    req, res, m_http_client, 200000);

            m_daemon_rpc_mutex.unlock();

            if (!r)
            {
                cerr << "Error connecting to Monero deamon at "
                     << deamon_url << endl;
                return blocks;
            }

            const std::list<block_complete_entry>& blocks_entries = res.blocks;

            for (const auto& be: blocks_entries)
            {
               // blocks.push_back(block_)
            }

            return blocks;




        }


    };


}



#endif //CROWXMR_RPCCALLS_H