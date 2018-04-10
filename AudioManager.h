#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "thirdparty/include/FFHeader.h"

class AudioPCM;

bool operator==(const AudioPCM& l, const AudioPCM& r);

class AudioPCM
{
public:
	AudioPCM() = default;
	AudioPCM(const std::string& name);
	AudioPCM(const AudioPCM& other);
	AudioPCM& operator=(AudioPCM other);
	AudioPCM(AudioPCM&& other);
	~AudioPCM();
	friend void swap(AudioPCM& first, AudioPCM& second);

public:
	std::string getName() const { return mName; }
	size_t getSize() const { return mSize; }
	std::vector<uint8_t> getBuffer() const { return mBuffer; }

private:
	int readFilePackets();

private:
	std::string mName;
	size_t mSize = 0;
	std::vector<uint8_t> mBuffer;

private:
	AVFormatContext* FormatContext = nullptr;
	AVInputFormat* InputFormat = nullptr;
};

namespace std
{
	template<>
	struct hash<AudioPCM>
	{
		typedef AudioPCM argument_type;
		typedef size_t result_type;

		size_t operator()(const AudioPCM& x) const
		{
			std::hash<std::string> hash_fn;
			return hash_fn(x.getName());
		}
	};
}

class AudioManager
{
public:
	~AudioManager() = default;
	static AudioManager& GetInstance() {
		static AudioManager instance;
		return instance;
	}

	void addAudioList(const std::vector <std::string>& filenames);
	AudioPCM getAudio(const std::string& filename) const;

private:
	AudioManager() = default;

private:
	std::unordered_set<AudioPCM> mAudioSet;

};