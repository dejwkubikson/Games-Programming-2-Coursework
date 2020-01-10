#include "Audio.h"

Audio::Audio()
{
	// Open sound card
	device = alcOpenDevice(NULL);
	if (device == NULL)
	{
		std::cout << "cannot open sound card" << std::endl;
	}

	context = alcCreateContext(device, NULL);

	if (context == NULL)
	{
		std::cout << "cannot open context" << std::endl;
	}

	alcMakeContextCurrent(context);
}

Audio::~Audio()
{
	// Deleting all audio sources and buffers
	for (unsigned int i = 0; i < datas.size(); i++)
	{
		alDeleteSources(1, (unsigned int*)&datas[i].sourceID);
		if (datas[i].bufferID != -1)
		{
			alDeleteBuffers(1, (unsigned int*)&datas[i].bufferID);
			delete[] datas[i].buffer;
		}
	}
	alcDestroyContext(context);
	// Closing the audio device
	alcCloseDevice(device);
}

bool Audio::isBigEndian()
{
	// Checking if the computer stores bytes in big endian (significant values stored first) or the other way around - small endian
	int a = 1;
	return !((char*)&a)[0];
}

int Audio::convertToInt(char* buffer, int length)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < length; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i < length; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

char* Audio::loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
	// Loading WAV audio file
	char buffer[4];
	std::ifstream in(fn, std::ios::binary);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 4); //WAV
	in.read(buffer, 4);	//fmt
	in.read(buffer, 4); //16 bit
	in.read(buffer, 2); //1
	in.read(buffer, 2);
	chan = convertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToInt(buffer, 2);
	in.read(buffer, 4);
	in.read(buffer, 4);
	size = convertToInt(buffer, 4);
	char* soundData = new char[size];
	in.read(soundData, size);
	return soundData;
}

unsigned int Audio::loadSound(const char* filename)
{
	// Loading sound
	bool found = false;
	unsigned int sourceID, bufferID;
	char* soundData = NULL;
	for (unsigned int i = 0; i < datas.size(); i++)
	{
		if (datas[i].name == filename && datas[i].bufferID != -1)
		{
			bufferID = datas[i].bufferID;
			found = true;
			break;
		}
	}
	if (!found)
	{
		int channel, sampleRate, bps, size;
		soundData = loadWAV(filename, channel, sampleRate, bps, size);
		unsigned int format;
		alGenBuffers(1, &bufferID);

		if (channel == 1)
		{
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else
			{
				format = AL_FORMAT_STEREO16;
			}

		}

		alBufferData(bufferID, format, soundData, size, sampleRate);
	}
	alGenSources(1, &sourceID);
	alSourcei(sourceID, AL_BUFFER, bufferID);
	alSourcef(sourceID, AL_REFERENCE_DISTANCE, 1.0f);
	datas.push_back(data(sourceID, (!found ? bufferID : -1), soundData, filename));
	return sourceID;
}

void Audio::playSound(unsigned int id, glm::vec3& pos)
{
	// Plays sound at specified vector3 position
	alSource3f(id, AL_POSITION, pos.x, pos.y, pos.z);
	alSourcePlay(id);
}
void Audio::stopSound(unsigned int id)
{
	alSourceStop(id);
}
void Audio::setlistener(glm::vec3& pos, glm::vec3& camLookAt)
{
	// Sets the listener of the audio.
	alListener3f(AL_POSITION, pos.x, pos.y, -pos.z);
	float orinet[6] = { camLookAt.x,camLookAt.y,camLookAt.z,0,1,0 };
	alListenerfv(AL_ORIENTATION, orinet);
}