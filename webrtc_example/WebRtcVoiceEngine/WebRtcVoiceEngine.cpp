// WebRtcVoiceEngine.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "media/engine/webrtcvoiceengine.h"
#include "modules/audio_device/include/audio_device.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "logging/rtc_event_log/rtc_event_log.h"

int main()
{
	rtc::scoped_refptr<webrtc::AudioDeviceModule> pADM = webrtc::AudioDeviceModule::Create(webrtc::AudioDeviceModule::kWindowsCoreAudio);
	rtc::scoped_refptr<webrtc::AudioEncoderFactory> pAEF = webrtc::CreateBuiltinAudioEncoderFactory();
	rtc::scoped_refptr<webrtc::AudioDecoderFactory> pADF = webrtc::CreateBuiltinAudioDecoderFactory();
	rtc::scoped_refptr<webrtc::AudioProcessing> pAPM = webrtc::AudioProcessingBuilder().Create();


	std::shared_ptr<cricket::WebRtcVoiceEngine> pEngine(new cricket::WebRtcVoiceEngine(pADM.get(), pAEF.get(), pADF.get(), nullptr, pAPM.get()) );
	RTC_CHECK(pEngine.get());

	pEngine->Init();
	webrtc::RtcEventLogNullImpl event_log;
	std::unique_ptr<webrtc::Call> call(
		webrtc::Call::Create(webrtc::Call::Config(&event_log)));
	cricket::VoiceMediaChannel* channel = pEngine->CreateChannel(
		call.get(), cricket::MediaConfig(), cricket::AudioOptions());

	auto codecs = pEngine->recv_codecs();

	//webrtc::WebRtcVoiceEngine();
    return 0;
}

