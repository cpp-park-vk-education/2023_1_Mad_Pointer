#pragma once

#include <exception>
#include <fstream>
#include <string>
#include <vector>

namespace Logs {
    class FileSink {
    public:
        FileSink(const std::string& filename, size_t bufferSize = 4096u) : m_buffer(bufferSize), m_output(filename), m_offset(0u) {
            if (!m_output.is_open()) {
                throw std::runtime_error("File was not created");
            }
        }

        void write(const std::string& data) {
            const size_t dataSize = data.size();
            if (dataSize + m_offset >= m_buffer.size()) {
                flush();
            }

            std::copy(begin(data), end(data), begin(m_buffer) + m_offset);
            m_offset += dataSize;
        }

        ~FileSink() {
            flush();
        }

    private:
        void flush() {
            if (m_offset != 0u) {
                m_output.write(m_buffer.data(), m_offset);
                m_offset = 0u;
            }
        }

    private:
        std::vector<char> m_buffer;
        std::ofstream m_output;
        size_t m_offset;
    };
}  // namespace Logs
