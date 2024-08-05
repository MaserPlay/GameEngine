
#include "SoundFile.hpp"
#include "SystemAdapter.h"
#include <cstring>
#include <cctype>
#include <fstream>
#include <sndfile.h>
#include <memory>
#include <sstream>

#define STestErr(b) \
if (b){ \
SPDLOG_ERROR(#b);   \
throw std::ios::failure{#b}; \
}

unsigned int SoundFile::getChannelCount() const
{
    return m_file->_fmt->NumChannels;
}


unsigned int SoundFile::getSampleRate() const
{
    return m_file->_fmt->SampleRate;
}


void SoundFile::openRead(const std::string& filename)
{
    SPDLOG_INFO("opening {} file", filename);
    std::ifstream ifs{filename, std::ifstream::in | std::ios::binary};
    openRead(ifs);
    ifs.close();
}


void SoundFile::openRead(const void* const data,const std::size_t sizeInBytes)
{
    std::stringstream ss{ std::ios::binary};
    ss.write((char *) data, sizeInBytes);
    openRead(ss);
}
void SoundFile::openRead(std::istream& is){
    STestErr(!is)
    is.exceptions(std::ios_base::badbit | std::ios_base::failbit | std::ios_base::eofbit);
    m_file = std::make_unique<sFile>();

    is.read(m_file->ChunkID, 4);
    m_file->ChunkID[4] = '\0';
    is.read(reinterpret_cast<char *>(&m_file->ChunkSize), 4);
    is.read(m_file->Format, 4);
    m_file->Format[4] = '\0';

    //_fmt subchunk
    is.read(m_file->_fmt->Subchunk1ID, 4);
    m_file->_fmt->Subchunk1ID[4] = '\0';
    is.read(reinterpret_cast<char *>(&m_file->_fmt->Subchunk1Size), 4);
    is.read(reinterpret_cast<char *>(&m_file->_fmt->AudioFormat), 2);
    is.read(reinterpret_cast<char *>(&m_file->_fmt->NumChannels), 2);
    is.read(reinterpret_cast<char *>(&m_file->_fmt->SampleRate), 4);
    is.read(reinterpret_cast<char *>(&m_file->_fmt->ByteRate), 4);
    is.read(reinterpret_cast<char *>(&m_file->_fmt->BlockAlign), 2);
    is.read(reinterpret_cast<char *>(&m_file->_fmt->BitsPerSample), 2);
    if (m_file->_fmt->AudioFormat != 1){
        is.read(reinterpret_cast<char *>(&m_file->_fmt->ExtraParamSize), 2);
        is.read(reinterpret_cast<char *>(m_file->_fmt->ExtraParams), m_file->_fmt->ExtraParamSize);
    }

    //_data subchunk
    is.read(m_file->_data->Subchunk2ID, 4);
    m_file->_data->Subchunk2ID[4] = '\0';
    is.read(reinterpret_cast<char *>(&m_file->_data->Subchunk2Size), 4);
    m_file->_data->Data = malloc(m_file->_data->Subchunk2Size);
    is.read(reinterpret_cast<char *>(m_file->_data->Data), m_file->_data->Subchunk2Size);

    //test it
    STestErr(strcmp(m_file->ChunkID, "RIFF") != 0)
    STestErr(m_file->ChunkSize != (4 + (8 + m_file->_fmt->Subchunk1Size) + (8 + m_file->_data->Subchunk2Size)))
    STestErr(strcmp(m_file->Format, "WAVE") != 0)
    STestErr(strcmp(m_file->_fmt->Subchunk1ID, "fmt ") != 0)
//    STestErr(m_file->_fmt->Subchunk1Size)
    STestErr(m_file->_fmt->AudioFormat != 1) // Compression
    STestErr((unsigned long) m_file->_fmt->SampleRate * (unsigned long) m_file->_fmt->NumChannels * (unsigned long) (m_file->_fmt->BitsPerSample / 8) != m_file->_fmt->ByteRate)
    STestErr((unsigned long) m_file->_fmt->NumChannels * (unsigned long) (m_file->_fmt->BitsPerSample / 8) != m_file->_fmt->BlockAlign)

    STestErr(strcmp(m_file->_data->Subchunk2ID, "data") != 0)
}

short *SoundFile::getOpenAlData() const {
    return static_cast<short *>(m_file->_data->Data);
}

int SoundFile::getOpenAlDataSize() const {
    return m_file->_data->Subchunk2Size;
}
unsigned short SoundFile::getBitsPerSample() const {
    return m_file->_fmt->BitsPerSample;
}


#undef STestErr