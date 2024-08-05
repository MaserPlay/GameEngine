////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_SOUNDFILE_HPP
#define SFML_SOUNDFILE_HPP

#include <string>
#include <memory>


/// \brief Provide read and write access to sound files
class SoundFile
{
public :

    /// \brief Default constructor
    ///
    SoundFile() = default;

    /// \brief Destructor
    ///
    ~SoundFile() = default;

    /// \brief Get the number of channels used by the sound
    ///
    /// \return Number of channels (1 = mono, 2 = stereo)
    ///
    unsigned int getChannelCount() const;

    /// \brief Get the sample rate of the sound
    ///
    /// \return Sample rate, in samples per second
    ///
    unsigned int getSampleRate() const;

    /// \brief Open a sound file for reading
    ///
    /// \param filename Path of the sound file to load
    ///
    void openRead(const std::string& filename);

    /// \brief Open a sound file in memory for reading
    ///
    /// \param data        Pointer to the file data in memory
    /// \param sizeInBytes Size of the data to load, in bytes
    ///
    void openRead(const void* const data,const std::size_t sizeInBytes);
    /// \brief Open a sound file for reading
    ///
    /// \param std::istream IStream the sound file to load
    ///
    void openRead(std::istream& is);

    short* getOpenAlData() const;

    int getOpenAlDataSize() const;

private :


    /// \brief Data and callbacks for opening from memory
    struct sFile
    {
        char* ChunkID = new char[5]; //Contains the letters "RIFF" in ASCII form (0x52494646 big-endian form).
        unsigned short ChunkSize {}; // 36 + SubChunk2Size, or more precisely:4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)This is the size of the rest of the chunkfollowing this number.  This is the size of theentire file in bytes minus 8 bytes for the two fields not included in this count: ChunkID and ChunkSize.
        char* Format = new char[5]; //Contains the letters "WAVE" (0x57415645 big-endian form).
        struct fmt{
            char* Subchunk1ID = new char[5];
            unsigned short Subchunk1Size {};
            unsigned short AudioFormat {};
            unsigned short NumChannels {};
            unsigned int SampleRate {};
            unsigned long ByteRate {};
            unsigned long BlockAlign {};
            unsigned short BitsPerSample {};
            size_t ExtraParamSize {};
            void* ExtraParams {};
            ~fmt(){delete Subchunk1ID;}
        };
        std::unique_ptr<fmt> _fmt {new fmt{}};
        struct data{
            char* Subchunk2ID = new char[5];
            unsigned long Subchunk2Size {};
            void* Data = new char[5];
            ~data(){delete Subchunk2ID;}
        };
        std::unique_ptr<data> _data {new data{}};
        ~sFile(){delete ChunkID; delete Format;}
    };

public:
    const std::unique_ptr<sFile> &getMFile() const {
        return m_file;
    }
    unsigned short getBitsPerSample() const;

private:
    std::unique_ptr<sFile> m_file {};       ///< Memory reading info
};


#endif // SFML_SOUNDFILE_HPP
