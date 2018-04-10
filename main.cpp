#include "AudioManager.h"

int main()
{
	avcodec_register_all();
	av_register_all();
	//avformat_network_init();

	AudioPCM("test.mp3");
}