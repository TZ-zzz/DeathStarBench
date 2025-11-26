#ifndef TRACE_COLLECTOR_H
#define TRACE_COLLECTOR_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <vector>
#include <string>
#include <map>

// Include the Thrift-generated types so we can access struct members
#include "../../gen-cpp/social_network_types.h" 

using namespace social_network;

class TraceCollector {
public:
    static TraceCollector& GetInstance() {
        static TraceCollector instance;
        return instance;
    }

    // =================================================================
    // 1. LOG INPUT: TEXT REQUEST (Incoming to this service)
    // =================================================================
    void LogTextRequest(int64_t req_id, 
                        const std::string& text, 
                        const std::map<std::string, std::string>& carrier) {
        
        std::lock_guard<std::mutex> lock(_mutex_text);
        std::ofstream out("/tmp/traces/text_service_req" + std::to_string(req_id) + ".bin", std::ios::binary | std::ios::app);
        
        if (!out.is_open()) return;

        // Write Request ID
        out.write(reinterpret_cast<const char*>(&req_id), sizeof(req_id));

        // Write Text Body
        WriteString(out, text);

        // Write Carrier Headers (Context)
        WriteMap(out, carrier);
        
        out.close();
    }

    // =================================================================
    // 2. LOG OUTPUT: URL SHORTENER RESULTS (Dependency Response)
    // =================================================================
    void LogUrlResult(int64_t req_id, const std::vector<Url>& urls) {
        std::lock_guard<std::mutex> lock(_mutex_url);
        std::ofstream out("/tmp/traces/url_responses" + std::to_string(req_id) + ".bin", std::ios::binary | std::ios::app);
        if (!out.is_open()) return;

        // Write Request ID (The Key)
        out.write(reinterpret_cast<const char*>(&req_id), sizeof(req_id));

        // Write Vector Size
        uint32_t count = urls.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));

        // Write Each Url Struct
        for (const auto& u : urls) {
            WriteString(out, u.shortened_url);
            WriteString(out, u.expanded_url);
        }
        out.close();
    }

    // =================================================================
    // 3. LOG OUTPUT: USER MENTION RESULTS (Dependency Response)
    // =================================================================
    void LogUserMentionResult(int64_t req_id, const std::vector<UserMention>& mentions) {
        std::lock_guard<std::mutex> lock(_mutex_mention);
        std::ofstream out("/tmp/traces/mention_responses" + std::to_string(req_id) + ".bin", std::ios::binary | std::ios::app);
        if (!out.is_open()) return;

        // Write Request ID
        out.write(reinterpret_cast<const char*>(&req_id), sizeof(req_id));

        // Write Vector Size
        uint32_t count = mentions.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));

        // Write Each UserMention Struct
        for (const auto& m : mentions) {
            // Note: In DSB, user_id is often int64, but sometimes string depending on version. 
            // Checking standard thrift: 1: i64 user_id, 2: string username
            out.write(reinterpret_cast<const char*>(&m.user_id), sizeof(m.user_id));
            WriteString(out, m.username);
        }
        out.close();
    }

    // // =================================================================
    // // 4. LOG FINAL OUTPUT: TEXT SERVICE RETURN (Result of this service)
    // // =================================================================
    // void LogTextResult(int64_t req_id, const TextServiceReturn& ret) {
    //     std::lock_guard<std::mutex> lock(_mutex_text_resp);
    //     std::ofstream out("/tmp/traces/text_service_resp.bin", std::ios::binary | std::ios::app);
    //     if (!out.is_open()) return;

    //     // Write Request ID
    //     out.write(reinterpret_cast<const char*>(&req_id), sizeof(req_id));

    //     // Write Result Text
    //     WriteString(out, ret.text);

    //     // Write Urls (Vector of Structs)
    //     uint32_t url_count = ret.urls.size();
    //     out.write(reinterpret_cast<const char*>(&url_count), sizeof(url_count));
    //     for (const auto& u : ret.urls) {
    //         WriteString(out, u.shortened_url);
    //         WriteString(out, u.expanded_url);
    //     }

    //     // Write User Mentions (Vector of Structs)
    //     uint32_t mention_count = ret.user_mentions.size();
    //     out.write(reinterpret_cast<const char*>(&mention_count), sizeof(mention_count));
    //     for (const auto& m : ret.user_mentions) {
    //         out.write(reinterpret_cast<const char*>(&m.user_id), sizeof(m.user_id));
    //         WriteString(out, m.username);
    //     }

    //     out.close();
    // }

private:
    std::mutex _mutex_text;
    std::mutex _mutex_url;
    std::mutex _mutex_mention;
    std::mutex _mutex_text_resp;

    TraceCollector() {}

    // --- Helpers ---

    void WriteString(std::ofstream& out, const std::string& str) {
        uint32_t len = str.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0) out.write(str.c_str(), len);
    }

    void WriteMap(std::ofstream& out, const std::map<std::string, std::string>& map) {
        uint32_t size = map.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& pair : map) {
            WriteString(out, pair.first);
            WriteString(out, pair.second);
        }
    }
};

#endif